# Exercise 1: Automatic Emergency Braking Request Gate

## Goal

Implement a cyclic C++ component that reads a perception sample and decides whether to request emergency braking. Invalid, missing or stale data must never produce a brake request.

Timebox: 60 minutes.

Suggested files:

- `AebRequestGate.h`
- `AebRequestGate.cpp`
- `AebRequestGateTest.cpp`

## Code package

- `include/AebRequestGate.h` defines the contract and four dependency interfaces.
- `tests/AebRequestGateTest.cpp` contains the executable requirement scenarios.
- `solution/AebRequestGate.cpp` contains the reference solution.
- `CMakeLists.txt` builds the reference solution by default.

To practise, create `work/AebRequestGate.cpp` against the existing header and tests, then configure this directory with:

```text
cmake -S . -B build -DAEB_IMPLEMENTATION="$PWD/work/AebRequestGate.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

Open the reference solution only after completing the requirements, interfaces and failing tests.

## Step 1: Restate the system boundary

The component does not detect obstacles and does not control hydraulic braking directly. It validates an already calculated perception decision and sends a bounded request through an actuator port.

## Step 2: Ask before coding

- Which speed, confidence and time-to-collision thresholds apply?
- Are threshold values inclusive?
- How old may a sample be?
- What is the safe reaction to missing, invalid or stale data?
- Does driver override suppress assistance?
- What are the physical limits for requested deceleration?
- Should repeated ticks resend the command?
- What happens when the actuator rejects a request?
- Are exceptions or dynamic allocation allowed?
- Which safety requirement and ASIL are allocated to this component?

## Step 3: Use the agreed practice requirements

- REQ-AEB-001: `tick()` runs every 10 ms.
- REQ-AEB-002: Braking is requested when speed is at least 5.0 m/s, confidence is at least 0.90, time to collision is at most 1.20 s and driver override is false.
- REQ-AEB-003: A sample older than 100 ms is stale. Exactly 100 ms is accepted.
- REQ-AEB-004: Missing, stale, non-finite or physically invalid data produces no brake request and one diagnostic event.
- REQ-AEB-005: Desired deceleration is clamped to the inclusive range 0.0–8.0 m/s².
- REQ-AEB-006: Driver override produces no brake request.
- REQ-AEB-007: Actuator rejection reports `ActuatorRejected`.
- REQ-AEB-008: Cross-tick deduplication is outside scope unless explicitly added.

## Step 4: Define interfaces and mocks

Create interfaces for:

- perception sample source;
- monotonic clock;
- brake actuator;
- diagnostic sink.

The decision logic itself should remain deterministic. Do not mock value objects or private methods.

## Step 5: Write the tests first

1. Ordinary hazardous sample requests braking once.
2. Exact speed, confidence and time-to-collision thresholds are accepted.
3. Speed just below the threshold produces no request.
4. Confidence just below the threshold produces no request.
5. Time to collision just above the threshold produces no request.
6. Driver override forbids actuator interaction.
7. Missing sample reports `MissingSample`.
8. A sample at 100 ms is accepted and one at 101 ms is stale.
9. NaN, infinity, negative speed and confidence outside zero to one are rejected.
10. Excessive deceleration is clamped to 8.0 m/s².
11. Actuator rejection produces `ActuatorRejected`.

## Step 6: Implement in requirement order

1. Read the sample once.
2. Handle missing input.
3. Read the clock once and check freshness.
4. Validate all numeric fields with `std::isfinite` and agreed ranges.
5. Apply driver override and hazard thresholds.
6. Clamp deceleration.
7. Call the actuator once.
8. Report rejection if required.

## Step 7: Review the evidence

- Every production branch must map to a requirement.
- Verify forbidden actuator calls with `Times(0)`.
- Review line and branch coverage, but also check requirement coverage.
- Explain that serialization, scheduling, actuator transport and vehicle behavior require integration, HIL and vehicle tests.

## Step 8: ASIL discussion

Discuss unintended braking and failure to brake as separate malfunctioning behaviors. For the practice scenario, the interviewer supplies S3, E4 and C3 for unintended maximum braking at motorway speed, giving a provisional ASIL D exercise. Do not claim that the class itself independently has ASIL D.

## Completion criteria

- Requirements are written before implementation.
- All eleven test scenarios pass.
- No behavior is based on an unstated assumption.
- External dependencies are mocked at their boundaries.
- Safe behavior is explicit.
- The candidate can name the next V-model verification levels.

## Optional extensions

- Add cross-tick idempotency with a sample identifier.
- Add debounce or hysteresis.
- Add a degraded mode after repeated invalid samples.
- Replace raw doubles with strong unit types.

