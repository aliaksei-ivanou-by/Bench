BATTERY THERMAL SUPERVISOR — REASONING

1. UNDERSTAND THE SYSTEM

I restate the task as a stateful decision over two temperatures. It requests cooling or shutdown through ports; it does not measure the battery or prove physical cooling. I ask about units, range, freshness, sensor disagreement, one failed sensor, thresholds, hysteresis, reset and output acknowledgement.

2. AGREE THE RULES

A usable sample is acquisition-valid, finite, in [-40, 150] °C, not in the future and at most 250 ms old. If both are usable and differ by <= 5 °C, use the higher value. One usable sensor is used with DegradedSensing. Neither usable or disagreement above 5 °C requests shutdown and reports SensorFault. Cooling enters at >= 55 °C and exits at <= 50 °C; >= 70 °C has shutdown priority. Shutdown stays latched until explicit reset with two usable, agreeing readings both <= 50 °C. The numbers are exercise assumptions.

3. DERIVE STATE AND TRANSITIONS

Use Normal, CoolingRequested and ShutdownRequested. At 54 °C, Normal remains Normal, while CoolingRequested remains active: the result depends on previous state. This hysteresis prevents switching around a single threshold. Ordinary evaluate returns immediately while shutdown is latched; reset obtains a fresh observation. One good sensor is not enough for reset.

Inject two sensors, clock, cooling and shutdown ports and diagnostics. Read each sensor once per observation and classify it before comparing values. Separate observation from transition. The existing output calls return void: the reference treats their return as command acceptance and cannot detect transport rejection. On leaving cooling it disables cooling before requesting shutdown; on reset it clears shutdown. Hardware commands occur only on transitions, while diagnostics can repeat. If acknowledgements are needed, agree a different interface and tests.

4. BUILD WITH TESTS

Start with Normal and exact 55 °C. Add 54 °C while cooling, exact 50 °C exit, exact 70 °C shutdown, 250/251 ms, range limits, one and two failed sensors, difference 5 °C and just above, and non-finite data. Test the latch across evaluations, rejected reset with hot, stale or disagreeing inputs, valid reset, command order and no repeated output. Map REQ-BAT-001–011 to evidence; verify the 100 ms schedule on target. Run the existing suite.

5. EXPLAIN EVIDENCE

Integration verifies units, timestamps and output protocol; target tests timing; system tests actual thermal response and shutdown. ASIL depends on the vehicle item and hazard. Production needs bounded timestamp values or overflow-safe age arithmetic.
