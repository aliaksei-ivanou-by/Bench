STEERING COMMAND LIMITER — REASONING

1. UNDERSTAND AND CLARIFY

I restate the task: accept a requested steering-assistance torque and send a limited command. This does not replace a steering controller or prove vehicle response. I ask about units, absolute and rate limits, elapsed time, freshness, override, initial state and actuator rejection.

2. RECORD THE CONTRACT

Torque must be finite and at most 50 ms old. The absolute limit is ±3.0 Nm and the rate limit is 50 Nm/s using monotonic elapsed time. Nonpositive elapsed time, future or stale data and invalid torque cause a diagnostic and no actuator call. After validation, driver override sends zero assistance without rate limiting. This is the agreed exercise behavior, not a universal steering safety rule. Initial accepted torque is zero; the constructor receives initial time. Only actuator success updates accepted torque and time.

3. DERIVE THE CALCULATION

Suppose the last accepted torque is 0 Nm, elapsed time is 20 ms and the requested torque is 3 Nm. Convert 20 ms to 0.020 s; 50 x 0.020 gives an allowed delta of 1 Nm. Clamp the request to [-1, 1], then to [-3, 3], resulting in 1 Nm. A -3 Nm request gives -1 Nm. With 100 ms elapsed, the rate limit permits 5 Nm and the absolute limit yields 3 Nm. Avoid integer division that loses fractions of a second. After actuator rejection, the next calculation uses the previous accepted time and torque.

4. GROW THE IMPLEMENTATION WITH TESTS

Use the given source, clock, actuator and diagnostics interfaces. Read the command and time once, validate before arithmetic, apply override or the limits in the agreed order, call the actuator once and update state only on success. Start with a successful ordinary command and assert both output and state. Add positive and negative rate limits, variable elapsed time, ±3 boundaries, 50/51 ms, zero and backward time, NaN, infinity, override and rejected actuator. Follow rejection with another tick to prove that the accepted reference state stayed unchanged. Check forbidden calls and map REQ-SCL-001–008 to tests; run the existing suite.

5. DISCUSS VERIFICATION

Integration checks units and actuator protocol; target tests check jitter and deadlines; HIL or vehicle tests check override and real steering response. Discuss ASIL only with an item and hazard. Production time handling needs bounded timestamps or checked subtraction: monotonic time alone does not prevent signed overflow.

6. FROM TASK TO FIRST IMPLEMENTATION

Say: “I will first define how elapsed time and previous accepted output affect the command.” Draw source → limiter → actuator, with clock and diagnostics injected. Ask whether a rejected actuator request advances the stored command or time, whether override bypasses the rate limit, whether future timestamps are invalid, and what initial value and time to use. Record the agreed answers before touching the code.

Sketch one tick: read command; reject absence; obtain now; require now > last accepted time; reject future, stale or non-finite command; calculate delta = 50 × (now - last accepted time) / 1000.0; clamp relative to last accepted torque, then to ±3.0. For override, send zero after validation. Update accepted torque and time only after a true actuator result. For example 20 ms permits 1 Nm change; name units to avoid treating milliseconds as seconds.

7. WHY THE EXISTING TESTS EXIST AND WHAT THEY DRIVE

This is a proposed learning order, not commit history. Tests are in SteeringCommandLimiterTest.cpp and the described branches are in the reference solution.

- OrdinaryCommandPassesBothLimits establishes a successful call and accepted state. Wire dependencies and implement the accepted path; otherwise an implementation that rejects everything could pass negative tests.
- ExactAbsoluteBoundariesAreAccepted checks that ±3 are allowed. AbsoluteLimitClampsLargeCommand checks values beyond the limit. Add std::clamp with -3 and 3; arrange sufficient elapsed time in these tests so the rate limit does not hide the absolute limit.
- PositiveAndNegativeRateAreLimited checks both directions from the previous accepted torque. Add a symmetric interval based on maximum delta. VariableElapsedTimeChangesAllowedDelta verifies conversion from milliseconds to seconds and prevents a fixed-per-tick limit.
- ZeroElapsedTimeIsRejected and NegativeElapsedTimeIsRejected protect against division or rate calculations using a nonpositive interval. Compare now with last accepted time, report InvalidTime and return without actuator interaction.
- NonFiniteTorqueIsRejected is parameterized for non-finite inputs. Add std::isfinite before clamping, report InvalidCommand and return. Verify which values the parameter list actually supplies.
- FreshnessBoundaryIsInclusive and CommandPastFreshnessBoundaryIsRejected distinguish 50 from 51 ms. Reject age > 50; separately reject timestamps in the future. The two freshness tests alone do not prove the future branch.
- DriverOverrideCommandsImmediateZero requires bypassing the rate clamp and sending zero even when that is a larger change than the usual limit. It still occurs after time and input validation.
- ActuatorFailurePreservesAcceptedState forces false from the actuator and checks retained state. Report ActuatorRejected and move both state assignments after the success check. A second tick can further prove the old state remains the reference.

8. RED–GREEN AND VERIFICATION

Begin with the ordinary command, then add absolute limits, rate limits and elapsed-time boundaries. Add invalid inputs and freshness, then override and actuator failure. For each failing test identify the violated observable behavior, make the smallest change, run again and refactor while green. If an earlier change already passes a new case, keep it as regression evidence. After the suite, explain that unit mocks do not prove actuator transport, actual handover, target deadlines or vehicle steering behavior.
