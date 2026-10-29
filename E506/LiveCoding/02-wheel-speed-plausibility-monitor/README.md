# Exercise 2: Dual Wheel-Speed Sensor Plausibility Monitor

## Goal

Implement a cyclic state machine that compares primary and secondary wheel-speed inputs and exposes `Available` or `Degraded` status.

## Business context and purpose

Vehicle functions can use wheel-speed information to make decisions or inform the driver. If a reading is missing, stale or inconsistent with another reading of the same quantity, a consumer needs to know whether it can still rely on that input. Otherwise, it may continue operating with misleading information or stop a function unnecessarily.

This exercise models a small availability monitor for two comparable measurements of the same wheel speed. It checks data quality and agreement, then tells a downstream component whether the input is `Available` or `Degraded`. For example, a missing sample causes an immediate degraded status; a brief disagreement is tolerated, while three consecutive disagreements cause degradation. Five consecutive plausible cycles are required for recovery. These thresholds are agreed exercise values, not universal vehicle requirements.

For a product team, the potential value is a clear contract between sensor data and its consumers: failures become visible, transient discrepancies are less likely to trigger repeated state changes, and diagnostics can help investigation. The component can support decisions about availability and service, but the exercise does not establish actual business savings, fault-detection rates or vehicle-safety outcomes.

The monitor does not identify which sensor is correct, produce a trusted speed estimate, repair a sensor or decide how braking, stability control or a dashboard should react. Its output is useful only if the consuming function has a defined response to both statuses. Agreement alone does not prove accuracy: both sensors can share the same error. In a real product, the sensor architecture, operating conditions, fault response and thresholds must be specified and validated at system level.

For the interview, this is useful because a compact business problem leads to concrete engineering choices: input validation, freshness, consecutive-cycle counters, recovery, diagnostics, output behavior and tests. The exercise does not assign an ASIL to the monitor; that depends on the actual vehicle function, hazard and allocated safety requirements.

Timebox: 60 minutes.

Suggested files:

- `WheelSpeedMonitor.h`
- `WheelSpeedMonitor.cpp`
- `WheelSpeedMonitorTest.cpp`

## Code package

- [Online compiler instructions](./OnlineCompiler.md) and standalone OnlineCompiler.cpp.

- [Detailed reasoning from task intake to verification](./Reasoning.md).

- `include/WheelSpeedMonitor.h` defines the state-machine contract and ports.
- `tests/WheelSpeedMonitorTest.cpp` covers thresholds, counters, failures and recovery.
- `solution/WheelSpeedMonitor.cpp` contains the reference solution.
- `CMakeLists.txt` builds the reference solution by default.

To practise, create `work/WheelSpeedMonitor.cpp` and configure this directory with:

```text
cmake -S . -B build -DWHEEL_SPEED_IMPLEMENTATION="$PWD/work/WheelSpeedMonitor.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

The public header and tests remain unchanged while the implementation is replaced.

## How the README maps to OnlineSteps

The [step-by-step guide](./OnlineSteps/Guide.md) maps the stages below to runnable files: questions and requirements come before code, 01a–02 build data and mocks progressively, and 03–17 alternate tests with implementation. After the final step, discuss V-model verification levels separately.

## Step 1: Ask before coding

- What are the units and physical range?
- What is the maximum acceptable disagreement?
- Is the threshold inclusive?
- How many bad cycles cause degradation?
- How many good cycles cause recovery?
- Does one missing sensor degrade immediately?
- What is stale data?
- Should repeated status notifications be suppressed?
- Which downstream vehicle function consumes the result?

## Step 2: Agreed requirements

- REQ-WSP-001: `tick()` runs every 20 ms.
- REQ-WSP-002: Values are valid in the inclusive range 0.0–100.0 m/s.
- REQ-WSP-003: A sample older than 50 ms is stale.
- REQ-WSP-004: A difference of at most 1.5 m/s is plausible.
- REQ-WSP-005: Three consecutive implausible cycles enter `Degraded`.
- REQ-WSP-006: One plausible cycle resets the bad-cycle counter before degradation.
- REQ-WSP-007: Missing, stale or non-finite data enters `Degraded` immediately.
- REQ-WSP-008: Five consecutive plausible cycles recover `Available`.
- REQ-WSP-009: Status is emitted only when the observable state changes.

## Step 3: Define mocks

- Primary sensor port.
- Secondary sensor port.
- Monotonic clock.
- Status output port.
- Diagnostic sink.

## Step 4: Build the test matrix

1. Equal valid values keep `Available`.
2. Difference exactly 1.5 m/s remains plausible.
3. Difference just above the threshold for one and two cycles remains `Available`.
4. Third consecutive bad cycle enters `Degraded`.
5. A plausible cycle resets the bad counter.
6. Missing primary or secondary input degrades immediately.
7. A 50 ms sample is accepted and a 51 ms sample is stale.
8. NaN, infinity, negative and over-range values degrade immediately.
9. Recovery happens on the fifth consecutive plausible cycle, not the fourth.
10. No repeated output occurs while state remains unchanged.

## Step 5: Implement explicitly

- Validate each input before comparing values.
- Keep bad and recovery counters separate.
- Centralize state transition and notification.
- Update counters only after the cycle is classified.
- Avoid hidden wall-clock access.

## Step 6: Close the V-model loop

- Unit tests verify counters, thresholds and transitions.
- Integration tests must verify real sensor messages and timestamp conversion.
- Target tests must verify scheduling jitter and sensor-update timing.
- Vehicle-level validation depends on the consumer of the speed estimate.

## ASIL prompt

Do not classify the monitor until the interviewer defines its consumer. Display-only speed, braking input and stability-control input create different hazardous events. Ask for the item, operational situation and S, E and C assumptions.

## Completion criteria

- Ten scenarios pass.
- State changes are deterministic.
- Time is injected.
- Invalid data never appears plausible.
- No duplicate status side effect occurs.

## Optional extensions

- Add sensor-specific fault codes.
- Add asymmetric thresholds.
- Add a third voting sensor.
- Add wrap-safe sequence numbers.

