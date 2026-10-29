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

Integration and target tests must cover timestamp origin, transport, scheduling and actuator behavior; vehicle tests establish physical response. Unintended braking and failure to brake are different hazards. ASIL requires item-level HARA and allocated requirements. In production, constrain the timestamp range or use checked subtraction to avoid signed overflow; do not treat the exercise's missing-data behavior as universally safe.
