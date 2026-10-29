# Parking-Assist Warning Coordinator

## Goal

Implement a C++ coordinator that reads four ultrasonic distance sensors and publishes one warning level based on the nearest usable obstacle. The difficult part is not finding a minimum. It is specifying validity, freshness, degraded coverage, boundary behavior and output-call rules.

Use a requirements-first GoogleTest and GoogleMock workflow. Keep this component advisory: it reports a warning but does not control vehicle motion.

## Suggested files

- `ParkingAssistCoordinator.h`
- `ParkingAssistCoordinator.cpp`
- `ParkingAssistCoordinatorTest.cpp`

## Code package

- [Detailed reasoning from task intake to verification](./Reasoning.md).

- `include/ParkingAssistCoordinator.h` defines four-sensor input and two output states.
- `tests/ParkingAssistCoordinatorTest.cpp` covers bands, freshness, ordering and recovery.
- `solution/ParkingAssistCoordinator.cpp` contains the reference solution.
- `CMakeLists.txt` builds the reference solution by default.

To practise, create `work/ParkingAssistCoordinator.cpp` and configure this directory with:

```text
cmake -S . -B build -DPARKING_ASSIST_IMPLEMENTATION="$PWD/work/ParkingAssistCoordinator.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

Warning severity and sensor coverage are intentionally modelled as independent outputs.

## Step 1: Establish the system boundary

The coordinator owns sample validation, nearest-obstacle selection and warning-state transitions. Sensor drivers, time, the warning display and diagnostics are external dependencies.

Clarify these points before coding:

- How many sensors exist, and is their ordering stable?
- What distance unit and physical range are used?
- What makes a sample stale or out of order?
- Are boundary values inclusive?
- What warning is required when all sensors are unavailable?
- Should one failed sensor suppress the complete function or only reduce coverage?
- Should the warning output be called every cycle or only on a state change?

## Step 2: Agree the requirements

- REQ-PAS-001: The coordinator reads four sensor samples on each cycle.
- REQ-PAS-002: A usable distance is from 0.10 m to 5.00 m inclusive.
- REQ-PAS-003: A sample older than 200 ms is stale and unusable.
- REQ-PAS-004: A sample with a timestamp older than the last accepted timestamp for that sensor is out of order and unusable.
- REQ-PAS-005: The warning is based on the smallest distance among usable samples.
- REQ-PAS-006: A distance at or below 0.30 m produces `Critical`.
- REQ-PAS-007: A distance above 0.30 m and at or below 0.80 m produces `Near`.
- REQ-PAS-008: A distance above 0.80 m and at or below 1.50 m produces `Caution`.
- REQ-PAS-009: A distance above 1.50 m produces `Clear`.
- REQ-PAS-010: One or more unusable sensors produce a `DegradedCoverage` diagnostic while the warning is still derived from usable sensors.
- REQ-PAS-011: If no sensor is usable, the warning is `Unknown`, never `Clear`.
- REQ-PAS-012: The warning output is called only when the warning level changes. Diagnostic state is also updated only when it changes.

The treatment of duplicate timestamps must be agreed explicitly. For this exercise, a duplicate is allowed and does not replace the stored timestamp.

## Step 3: Define interfaces and mocks

Create minimal interfaces for:

- indexed access to four distance sensors;
- a monotonic clock;
- a warning-output port;
- a diagnostic-output port.

Each sample should contain distance, timestamp and an acquisition-validity flag. Keep previous accepted timestamps and the last published states inside the coordinator.

## Step 4: Write tests before implementation

Cover at least these scenarios:

1. Four clear samples publish `Clear` once.
2. The nearest usable sample determines the warning regardless of sensor order.
3. Exactly 0.30 m is `Critical`.
4. A value just above 0.30 m is `Near`.
5. Exactly 0.80 m is `Near`, and a value just above it is `Caution`.
6. Exactly 1.50 m is `Caution`, and a value just above it is `Clear`.
7. Exactly 0.10 m and 5.00 m are valid; values outside that range are unusable.
8. A sample exactly 200 ms old is usable and one 201 ms old is stale.
9. One failed sensor reports degraded coverage while remaining sensors still determine the warning.
10. Four unusable sensors publish `Unknown` and never publish `Clear`.
11. An older timestamp is rejected without corrupting the sensor's accepted timestamp.
12. Repeating the same warning and diagnostic state produces no extra output calls.
13. Sensor recovery clears degraded coverage when all four samples become usable.

Use parameterized tests for threshold boundaries if time permits. Use strict mocks for outputs so accidental repeated calls fail the test.

## Step 5: Implement

- Capture the current time once per cycle.
- Read and validate every sensor independently.
- Reject out-of-range, invalid, stale and out-of-order samples before computing the minimum.
- Compute the warning only from usable samples.
- Derive warning state and coverage state separately.
- Publish each state only when it differs from the last published state.
- Update accepted timestamps only according to the agreed duplicate and ordering rules.

## Step 6: Explain verification boundaries

- Unit tests prove validation, minimum selection, thresholds and output suppression.
- Integration tests must verify sensor indexing, units, timestamp origin and communication errors.
- Target tests must verify cycle timing and behavior under realistic sensor-update rates.
- Vehicle tests must verify obstacle geometry, reflections, blind areas and human perception of warnings.

## ASIL prompt

This exercise defines an advisory function, so do not infer an ASIL from the phrase parking assist. Ask whether the output only informs the driver or also controls braking or vehicle motion. The item boundary, hazard, operating speed and controllability can change the classification and the required safe behavior.

## Completion criteria

- All twelve requirements are represented by tests.
- Every threshold has an exact-boundary test.
- Degraded coverage is independent from warning severity.
- All-invalid input produces `Unknown`.
- Out-of-order data does not corrupt state.
- Repeated cycles do not generate unnecessary output calls.

## Optional extensions

- Add per-sensor fault counters and debounce.
- Add sensor mounting positions to the warning output.
- Add hysteresis around distance bands.
- Add a maximum tolerated duration in degraded coverage.
