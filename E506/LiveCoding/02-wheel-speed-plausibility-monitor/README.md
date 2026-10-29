# Exercise 2: Dual Wheel-Speed Sensor Plausibility Monitor

## Goal

Implement a cyclic state machine that compares primary and secondary wheel-speed inputs and exposes `Available` or `Degraded` status.

## Example of a task brief from an interviewer

The following is a practice dialogue. The first statement is deliberately incomplete so the candidate can clarify the requirements. The numerical rules that follow are the agreed assumptions for this exercise, not general automotive requirements.

### Initial assignment

“Imagine a vehicle system that receives two comparable measurements of the speed of the same wheel: a primary and a secondary input. Another component needs to know whether these inputs are usable and consistent enough to rely on. Please implement a small C++ component that checks the inputs periodically and exposes an availability status.

“The component should distinguish an available state from a degraded state. A short disagreement should not necessarily make the status fluctuate, but a persistent disagreement should be visible. Missing or otherwise unusable data must also be handled. Please discuss your assumptions, implement the agreed behavior and demonstrate it with tests. You have approximately 60 minutes.”

The interviewer has not yet defined the exact thresholds, recovery policy, treatment of timestamps, initial state or output semantics. Ask about them before deciding how to implement the monitor.

### Clarifications given during the discussion

Candidate: “What do the two readings represent, and which value should the component provide to its consumer?”

Interviewer: “They are comparable measurements of the same wheel speed, expressed in meters per second. The component reports availability only. It does not decide which sensor is correct, calculate a speed estimate, or control another vehicle function.”

Candidate: “How does the component receive data and how often does it run?”

Interviewer: “A caller invokes `tick()` every 20 ms. At each tick the component reads each sensor once. A reading may be absent; otherwise it contains a speed and a timestamp in milliseconds. The timestamp and the injected monotonic clock use the same time base. The scheduler and physical sensors are outside this component.”

Candidate: “Which samples are usable?”

Interviewer: “Each speed must be finite and between 0.0 and 100.0 m/s inclusive. A timestamp in the future is invalid. A sample is stale when it is older than 50 ms, so an age of exactly 50 ms is accepted. If either sample is missing, stale, non-finite or outside the range, enter `Degraded` immediately and report a diagnostic.”

Candidate: “What disagreement is acceptable, and how should the status change?”

Interviewer: “When both samples are usable, calculate the absolute difference. At most 1.5 m/s is plausible; a difference above 1.5 m/s is implausible. Begin in `Available`. While available, enter `Degraded` on the third consecutive implausible cycle. A plausible cycle before degradation resets the bad-cycle counter. Do not publish an initial status just because the component was constructed.”

Candidate: “How does recovery work, and should the output be repeated?”

Interviewer: “Once degraded, require five consecutive plausible cycles before returning to `Available`. A disagreement or unusable input interrupts the recovery sequence. Publish a status only when it changes; a repeated fault can still produce a diagnostic. For this exercise the status and diagnostic ports do not acknowledge calls.”

Candidate: “What should I deliver, and how do we verify it?”

Interviewer: “Use C++17 and Google Test/Google Mock. Separate the sensor inputs, monotonic clock, status output and diagnostics so tests can control and observe them. Show ordinary behavior, exact boundaries, invalid inputs, state transitions, recovery and output calls. Explain which checks need integration or target tests. The 20 ms schedule is provided by the caller; a direct unit-test call to `tick()` does not prove that timing.”

### Concrete behavior to implement

- At time 1000 ms, two usable samples timestamped 980 ms with speeds 20.0 and 21.5 m/s differ by exactly 1.5 m/s and remain plausible.
- Starting in `Available`, three consecutive usable pairs differing by 1.6 m/s produce `Degraded` on the third tick. If a plausible pair occurs after the second bad pair, the bad-cycle count resets.
- A missing reading causes `Degraded` on that tick and reports `MissingSample`; repeated missing readings may report that diagnostic again, but do not republish an unchanged status.
- Starting in `Degraded`, four consecutive plausible pairs are not enough to recover; the fifth changes the status to `Available`. An intervening implausible or unusable pair breaks the sequence.

The caller must keep the injected dependencies alive while the monitor uses them. The existing exercise header supplies the interfaces; in an empty project, agree equivalent interfaces first. Any change to thresholds, initial status, diagnostics or recovery behavior requires an explicit agreement and corresponding tests.

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

## Workflow boundaries: SDD → TDD → implementation

1. SDD — specification-driven development. Start when the interviewer describes the problem. Clarify the component boundary, inputs, outputs, timing, failure behavior and exact thresholds; agree the examples and REQ-WSP-001–009. This phase ends for the first implementation increment when its behavior and acceptance conditions are explicit enough to test. A later ambiguity sends us back to the specification and any affected tests.
2. Test preparation. Derive the test matrix and define minimal ports and mocks from the agreed specification. A mock is a test boundary; it does not itself prove the monitor's business behavior. The environment and scaffolding in OnlineSteps 00–02 are preparation, not evidence that the decision logic is complete.
3. TDD — test-driven development. For one small agreed behavior, write a test of an observable outcome and run it against the current implementation. The red phase begins when the test is added and ends when it fails for the expected missing behavior; a compile or setup error is not the intended failure.
4. Implement the same increment. Add the smallest production change required for that test, rerun it and the existing tests until they pass, then refactor while keeping them green. This is the green/refactor part of the TDD cycle, not a separate implementation phase after all tests have been written. The increment ends when its tests pass and the behavior can be traced back to the agreed requirement.
5. Repeat TDD and implementation for the next behavior. For example, in OnlineSteps, 03 is red and 04 is green; 05 is red and 06 is green. Steps 01a–02 include passing setup or demonstration tests, not a demonstrated red-to-green implementation cycle. Step 17 switches to the complete reference and existing suite; it is a final comparison, not a recorded red-to-green sequence for every remaining case.
6. Verification and handoff. Once the agreed unit scenarios pass, review requirement coverage and test gaps, then identify integration, target and vehicle evidence. The 20 ms scheduling requirement cannot be proved by calling `tick()` directly in a unit test.

The order for each increment is: agreed specification → failing test → implementation → passing tests and refactoring. Do not invent missing safety behavior merely to make a test pass.

## Step 1: SDD — ask before coding

- What are the units and physical range?
- What is the maximum acceptable disagreement?
- Is the threshold inclusive?
- How many bad cycles cause degradation?
- How many good cycles cause recovery?
- Does one missing sensor degrade immediately?
- What is stale data?
- Should repeated status notifications be suppressed?
- Which downstream vehicle function consumes the result?

## Step 2: SDD — agree requirements and finish the initial specification

- REQ-WSP-001: `tick()` runs every 20 ms.
- REQ-WSP-002: Values are valid in the inclusive range 0.0–100.0 m/s.
- REQ-WSP-003: A sample older than 50 ms is stale.
- REQ-WSP-004: A difference of at most 1.5 m/s is plausible.
- REQ-WSP-005: Three consecutive implausible cycles enter `Degraded`.
- REQ-WSP-006: One plausible cycle resets the bad-cycle counter before degradation.
- REQ-WSP-007: Missing, stale or non-finite data enters `Degraded` immediately.
- REQ-WSP-008: Five consecutive plausible cycles recover `Available`.
- REQ-WSP-009: Status is emitted only when the observable state changes.

## Step 3: Test preparation — define mocks

- Primary sensor port.
- Secondary sensor port.
- Monotonic clock.
- Status output port.
- Diagnostic sink.

## Step 4: TDD preparation — build the test matrix

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

## Step 5: TDD green and refactor — implement one behavior at a time

- Validate each input before comparing values.
- Keep bad and recovery counters separate.
- Centralize state transition and notification.
- Update counters only after the cycle is classified.
- Avoid hidden wall-clock access.

## Step 6: Verification — close the V-model loop

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

