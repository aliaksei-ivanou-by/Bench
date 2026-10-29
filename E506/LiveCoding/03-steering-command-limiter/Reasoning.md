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
