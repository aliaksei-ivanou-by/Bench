# Exercise 3: Steering Command Limiter

## Goal

Implement a component that validates and limits requested steering-assistance torque before sending it to an actuator.

Timebox: 60 minutes.

Suggested files:

- `SteeringCommandLimiter.h`
- `SteeringCommandLimiter.cpp`
- `SteeringCommandLimiterTest.cpp`

## Code package

- `include/SteeringCommandLimiter.h` defines the command, ports and observable state.
- `tests/SteeringCommandLimiterTest.cpp` covers absolute, rate, time and failure behavior.
- `solution/SteeringCommandLimiter.cpp` contains the reference solution.
- `CMakeLists.txt` builds the reference solution by default.

To practise, create `work/SteeringCommandLimiter.cpp` and configure this directory with:

```text
cmake -S . -B build -DSTEERING_LIMITER_IMPLEMENTATION="$PWD/work/SteeringCommandLimiter.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

The test suite observes both actuator calls and the state retained after rejection.

## Step 1: Ask before coding

- What are the torque units and absolute limit?
- What is the allowed torque rate of change?
- Is the rate based on fixed cycles or elapsed time?
- What is stale input?
- What happens on driver override?
- What is the safe command for invalid time or data?
- Is the last state updated when the actuator rejects a command?
- Are commands sent every cycle or only on change?

## Step 2: Agreed requirements

- REQ-SCL-001: Requested torque must be finite.
- REQ-SCL-002: Input older than 50 ms is stale.
- REQ-SCL-003: Absolute torque is clamped to ±3.0 Nm.
- REQ-SCL-004: Rate of change is limited to 50.0 Nm/s using monotonic elapsed time.
- REQ-SCL-005: Driver override requests 0.0 Nm assistance.
- REQ-SCL-006: Zero or negative elapsed time produces no actuator call and reports `InvalidTime`.
- REQ-SCL-007: Stale or invalid input produces no actuator call and reports a fault.
- REQ-SCL-008: The last accepted command changes only after actuator success.

## Step 3: Define mocks

- Command input port.
- Monotonic clock.
- Steering actuator.
- Diagnostic sink.

## Step 4: Write tests

1. Ordinary command inside both limits.
2. Exact +3.0 and -3.0 Nm boundaries.
3. Commands above and below the absolute limits are clamped.
4. Positive rate limiting.
5. Negative rate limiting.
6. Variable elapsed time changes the allowed delta.
7. Zero and negative elapsed time are rejected.
8. NaN and infinity are rejected.
9. A 50 ms command is accepted and a 51 ms command is stale.
10. Driver override commands zero assistance.
11. Actuator rejection preserves the previous accepted state.

## Step 5: Implement

- Validate input and time first.
- Derive the allowed delta from elapsed time.
- Apply rate limit and then absolute limit in the agreed order.
- Keep the last accepted output as explicit state.
- Update state only after actuator success.

## Step 6: Explain verification boundaries

- Unit tests prove arithmetic, ordering and state transitions.
- Integration tests must verify units and actuator protocol.
- Target tests must verify timing jitter and execution deadlines.
- HIL or vehicle tests must verify driver override and actual steering response.

## ASIL prompt

Unintended steering at speed may have high severity, but the candidate must ask for the item, operating situation and safe reaction. Zero torque, controlled ramp-down and handover to another controller are different requirements and must not be guessed.

## Completion criteria

- Eleven scenarios pass.
- No use of system time is hidden inside the class.
- NaN and invalid time are handled.
- The order of limits is specified and tested.
- Failed actuator calls do not corrupt internal state.

## Optional extensions

- Add command sequence numbers.
- Add separate enable and availability states.
- Add a controlled ramp-down policy.
- Add strong torque and time types.

