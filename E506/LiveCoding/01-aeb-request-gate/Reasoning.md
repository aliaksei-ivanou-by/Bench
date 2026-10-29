AUTOMATIC EMERGENCY BRAKING REQUEST GATE — REASONING

1. UNDERSTAND THE TASK

I restate the assignment: each tick checks an already calculated perception sample and may send a bounded brake request. The component neither detects obstacles nor controls hydraulic brakes. I ask about input units, thresholds, timestamps, driver override, actuator failure and repeated calls. A successful request does not prove actual vehicle braking.

2. AGREE THE RULES

For this exercise, speed >= 5.0 m/s, confidence >= 0.90, collision time <= 1.20 s, age <= 100 ms and no override are required. Invalid, missing or stale input yields one diagnostic and no request. Nonnegative deceleration is capped at 8.0 m/s²; negative values are invalid. Future timestamps are invalid. These values are exercise assumptions, not universal AEB rules. Repeated ticks can repeat requests.

3. DERIVE THE SOLUTION

Inject the source, monotonic clock, actuator and diagnostic sink. Read the sample once; on absence report MissingSample. Read time once; reject a future timestamp, then age above 100 ms. Check all numbers are finite, speed and collision time are nonnegative, confidence is in [0, 1], and desired deceleration is nonnegative. Validation happens before override and thresholds. If all conditions pass, clamp deceleration and call the actuator once; report ActuatorRejected if it returns false. This ordering also determines which diagnostic wins when several faults coexist.

For example, the exact hazard thresholds and an age of 100 ms pass. At 101 ms the actuator must not be called. A valid request for 10 m/s² becomes 8.0. A negative request is rejected rather than clamped. Use the existing header and keep dependencies alive longer than the gate.

4. BUILD TESTS AND CODE IN SMALL STEPS

Start with one valid hazardous sample and an expectation of one actuator call. Add exact thresholds and just-outside values, then missing input, future and stale timestamps, NaN, infinity, invalid ranges and override, checking Times(0) for prohibited calls. Add clamping and actuator rejection. Map REQ-AEB-001–008 to tests; the 10 ms scheduling requirement needs target evidence, not just direct tick calls. Run the suite using the exercise README.

5. EXPLAIN LIMITATIONS

Integration and target tests must cover timestamp origin, transport, scheduling and actuator behavior; vehicle tests establish physical response. Unintended braking and failure to brake are different hazards. ASIL requires item-level HARA and allocated requirements. The reference freshness check avoids signed overflow for extreme timestamps; do not treat the exercise's missing-data behavior as universally safe.

6. WALK THROUGH THE FIRST MINUTES

Start by saying: “I will first clarify the input contract and the behavior on missing data, then describe the decisions and write tests.” Sketch one path: perception source → gate → actuator, with clock and diagnostics as separate dependencies. Ask whether this gate initiates a request or controls braking, and whether a new request is required on each tick. Confirm that the 10 ms schedule is provided by the caller.

Next ask for speed, confidence and collision-time units and exact boundaries. Repeat the answers back as comparisons: speed >= 5.0, confidence >= 0.90 and collision time <= 1.20. Ask if 100 ms is accepted, what future timestamps mean, whether driver override takes precedence, whether negative deceleration is valid and what a false actuator result signifies. Record the agreed answer before starting; do not assume the absence of a sample means that the road is clear.

7. TURN THE CONTRACT INTO A DECISION PATH

Trace one sample through the branches in this order:

- No sample: MissingSample, return without reading the clock or calling the actuator.
- Timestamp after now: InvalidSample; age greater than 100 ms: StaleSample. Both return immediately.
- Non-finite or physically invalid field: InvalidSample and return. Validate before comparison because NaN does not behave like an ordinary number.
- Override or any hazard condition not met: return without a request. These ordinary non-trigger cases are not diagnostics in the supplied contract.
- Otherwise cap the requested deceleration at 8.0, call the actuator and report ActuatorRejected on false.

This sequence is observable when a sample has several faults: the earlier branch decides the diagnostic. Ask the interviewer whether that priority is intended. The clock and sample timestamp must use the same origin and units; otherwise a numerical age check has no meaning.

8. WRITE A FIRST TEST, THEN ADD CONTRASTS

Use a hazardous sample such as speed 20.0, confidence 0.95, collision time 0.8, deceleration 6.0 and timestamp 950 with now equal to 1000. Arrange the source and clock mocks, expect one actuator request of 6.0 returning true, then call tick. The test makes the intended interaction visible. Add a test at 5.0, 0.90, 1.20 and 100 ms simultaneously; then change one input at a time to isolate which condition suppresses the request.

For missing input, expect MissingSample and no actuator call; no clock call is needed. At 101 ms expect StaleSample and no actuator call. Use explicit NaN and infinity cases, a future timestamp, confidence outside [0, 1] and negative numeric values. For override assert no actuator call. Finally test a 12.0 request becomes 8.0 and a rejected request emits ActuatorRejected. Strict mocks catch unintended calls, but explicit Times(0) can make the reason for an important prohibition easier to read.

9. IMPLEMENT AND REVIEW LIVE

Declare named constants with units, wire the existing references in the constructor and implement the early-return path before adding the final actuator call. Keep numerical validation in a small helper if it improves readability; do not mock that helper. Run the current test after each small change, explain a failing assertion, fix the implementation and rerun. Then check all requirement branches and the negative interactions, not only the coverage percentage.

If time remains, explain what is still outside the unit: scheduled 10 ms invocation, timestamps across components, actuator transport, real deceleration and vehicle-level safety. Ask about exception policy, time-range guarantees and acknowledgement semantics before presenting this as production-ready. Avoid adding deduplication or automatic recovery without an agreed requirement.

10. WHY EACH EXISTING TEST EXISTS AND WHAT CODE IT DRIVES

The following is a teaching sequence, not a claim about the actual commit history. Each named test already exists in tests/AebRequestGateTest.cpp; the corresponding solution behavior is in solution/AebRequestGate.cpp.

- HazardousSampleRequestsBraking establishes the basic contract: a valid hazard must reach the actuator with the requested 6.0. Start tick with one source read and the actuator call; return true from the actuator mock. Without this baseline a suite of rejection tests could pass an implementation that never acts.
- ExactHazardThresholdsAreAccepted protects all three inclusive comparisons. Add named speed, confidence and collision-time constants and reject speed below, confidence below, or collision time above them. The test sets several boundaries together, so separate cases can improve fault localization.
- ValuesOutsideHazardThresholdsDoNotRequestBraking checks each decision independently. Add early return if any criterion fails; the strict actuator mock detects an unintended call. This differs from the exact-boundary test: together they distinguish < from <= and > from >=.
- DriverOverrideSuppressesActuatorInteraction requires override to stop the call even for an otherwise hazardous sample. Add override to the decision guard after validation. It does not establish override precedence over malformed input.
- MissingSampleReportsDiagnostic requires checking the optional before dereference. Report MissingSample and return before reading time. The strict mocks also expose unexpected clock or actuator calls.
- SampleAtAgeLimitIsAccepted and SamplePastAgeLimitIsRejected distinguish 100 from 101 ms. Capture now once, subtract the timestamp after checking it is not in the future, and reject only age > 100. The future-timestamp branch exists in the solution; this pair alone does not independently test it.
- InvalidNumericInputIsRejected covers NaN confidence, negative speed and infinite collision time. Add isValid with std::isfinite and the agreed range checks, report InvalidSample and return. Additional negative deceleration, confidence-range and future-time tests would strengthen the suite; do not claim this test covers them all.
- ExcessiveDecelerationIsClamped checks output rather than merely state. Clamp a valid nonnegative desired value into [0, 8] before sending it. Do not clamp negative values before validation.
- ActuatorRejectionIsReported forces the false return path. Check the actuator result and emit ActuatorRejected; do not claim the unit can verify the vehicle's physical response.

11. RED–GREEN EXAMPLE

With a fresh work implementation, first write the missing-sample test and return after reporting it; run the focused test. Next write the normal hazard test, implement the happy path and run again. Add thresholds and age branches, then numeric validation, override, clamp and rejection one at a time. For every red test, state the incorrect observed behavior, make the smallest requirement-backed production change, rerun, and refactor only with the tests green. If an existing test passes without a new edit, explain which earlier branch already satisfies it rather than inventing a change.
