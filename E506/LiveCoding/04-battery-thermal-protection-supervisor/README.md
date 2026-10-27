# Battery Thermal Protection Supervisor

## Goal

Implement a small C++ supervisor that reads two battery-temperature sensors, requests cooling when the battery becomes hot and requests shutdown when safe temperature supervision is no longer possible.

The exercise is intended for a sixty-minute requirements-first session with GoogleTest and GoogleMock. Do not start from implementation. Clarify the behavior, record the requirements, define interfaces, write tests and only then add production code.

## Suggested files

- `BatteryThermalSupervisor.h`
- `BatteryThermalSupervisor.cpp`
- `BatteryThermalSupervisorTest.cpp`

## Code package

- `include/BatteryThermalSupervisor.h` defines sensor, output and diagnostic ports.
- `tests/BatteryThermalSupervisorTest.cpp` covers hysteresis, plausibility, latching and reset.
- `solution/BatteryThermalSupervisor.cpp` contains the reference solution.
- `CMakeLists.txt` builds the reference solution by default.

To practise, create `work/BatteryThermalSupervisor.cpp` and configure this directory with:

```text
cmake -S . -B build -DBATTERY_THERMAL_IMPLEMENTATION="$PWD/work/BatteryThermalSupervisor.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

The tests treat shutdown as latched and require an explicit valid reset.
The reference solution treats successful return from each void output call as command acceptance; transport-level acknowledgement is an integration concern outside this unit boundary.

## Step 1: Establish the system boundary

The supervisor owns decision logic and state transitions. It does not own sensor acquisition, cooling hardware, the shutdown mechanism or system time. Represent those dependencies as injected interfaces.

Clarify these points before coding:

- Are temperatures expressed in degrees Celsius?
- What values are physically valid?
- How old may a sample be?
- How much disagreement between sensors is acceptable?
- What happens when only one sensor is usable?
- Is shutdown latched, and how is it reset?
- Must output commands be repeated on every cycle or only when the state changes?

## Step 2: Agree the requirements

- REQ-BAT-001: `evaluate()` is called every 100 ms.
- REQ-BAT-002: A sensor sample is valid from -40 to 150 degrees Celsius inclusive.
- REQ-BAT-003: A sample older than 250 ms is stale and unusable.
- REQ-BAT-004: When both samples are usable and differ by no more than 5 degrees, the supervisor uses the higher temperature.
- REQ-BAT-005: At 55 degrees or above, the state becomes `CoolingRequested`.
- REQ-BAT-006: Cooling remains requested until the evaluated temperature is 50 degrees or below.
- REQ-BAT-007: At 70 degrees or above, the state becomes `ShutdownRequested`.
- REQ-BAT-008: If one sensor is unusable, the supervisor uses the other sensor and reports `DegradedSensing`.
- REQ-BAT-009: If both sensors are unusable, or two usable sensors differ by more than 5 degrees, the supervisor requests shutdown and reports `SensorFault`.
- REQ-BAT-010: `ShutdownRequested` is latched. It may be cleared only by an explicit reset when both sensors are usable, agree within 5 degrees and are at or below 50 degrees.
- REQ-BAT-011: Hardware commands are emitted only when the requested operating state changes.

Record any changed number as an agreed requirement. Do not hide a guessed threshold in the implementation.

## Step 3: Define interfaces and mocks

Create minimal interfaces for:

- two temperature-sensor inputs returning value, timestamp and validity;
- a monotonic clock;
- a cooling-control output;
- a shutdown-request output;
- diagnostic reporting.

Mock every side-effecting dependency. Keep threshold evaluation and state transitions deterministic.

## Step 4: Write tests before implementation

Cover at least these scenarios:

1. Two agreeing cool samples keep the state `Normal`.
2. Exactly 55 degrees requests cooling.
3. Cooling remains active between 50 and 55 degrees.
4. Exactly 50 degrees returns from cooling to normal.
5. Exactly 70 degrees requests shutdown.
6. One invalid sensor uses the other and reports degraded sensing.
7. A sample exactly 250 ms old is accepted and one 251 ms old is stale.
8. Two unusable sensors request shutdown.
9. A 5-degree disagreement is accepted and a larger disagreement requests shutdown.
10. A latched shutdown does not clear on a normal evaluation cycle.
11. Reset is rejected while either sample is hot, stale, invalid or implausible.
12. A valid reset clears the latch and applies the resulting state once.

For output mocks, verify both required calls and forbidden calls. Repeated evaluations in the same state must not repeat hardware commands.

## Step 5: Implement

- Read the clock and both samples once per evaluation.
- Validate range and freshness separately for each sample.
- Handle the latched shutdown path before normal temperature transitions.
- Select the higher value only after plausibility succeeds.
- Apply shutdown, cooling-enter and cooling-exit thresholds in an explicit order.
- Change internal state only after the required output interaction succeeds, or define and test another failure policy with the interviewer.

## Step 6: Explain verification boundaries

- Unit tests prove thresholds, hysteresis, sensor selection, latching and call behavior.
- Integration tests must verify sensor units, timestamps, transport errors and output protocols.
- Target tests must verify the 100 ms schedule, clock behavior and real I/O timing.
- System tests must verify that cooling and shutdown produce the required battery-level response.

## ASIL prompt

Ask whether this supervisor only protects availability or prevents a hazardous thermal event. Severity, exposure and controllability depend on the vehicle item and operating situation. Discuss a provisional classification only after those assumptions are stated; do not assign an ASIL to the class name alone.

## Completion criteria

- Eleven requirements are represented by tests.
- Boundary values and stale-data behavior are explicit.
- Hysteresis prevents rapid cooling-state oscillation.
- Sensor loss and disagreement lead to deterministic behavior.
- Shutdown latching and reset conditions are tested.
- Output calls are controlled and observable.

## Optional extensions

- Add a configurable debounce period for sensor disagreement.
- Add an `EmergencyShutdown` threshold independent of plausibility.
- Replace raw floating-point values with strong temperature and duration types.
- Add persisted diagnostic counters without coupling them to the decision logic.
