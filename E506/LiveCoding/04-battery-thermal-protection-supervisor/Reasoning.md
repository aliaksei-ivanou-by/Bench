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

Integration verifies units, timestamps and output protocol; target tests timing; system tests actual thermal response and shutdown. ASIL depends on the vehicle item and hazard. The reference freshness check avoids signed overflow for extreme timestamps.

6. FROM THE INTERVIEW QUESTION TO A STATE MACHINE

Restate the boundary and ask how to handle one failed sensor, two failed sensors, disagreement, cooling hysteresis, shutdown latch and reset. Confirm threshold inclusivity and whether output calls acknowledge success. Draw Normal, CoolingRequested and ShutdownRequested; record arrows before implementation. At 54 °C the prior state matters: Normal stays Normal, CoolingRequested stays cooling. At 70 °C shutdown takes priority. The existing void output interface cannot report transport failure.

7. WHY THE EXISTING TESTS EXIST AND WHAT THEY DRIVE

This is a learning sequence, not a claim about commit history. The tests are in BatteryThermalSupervisorTest.cpp and the code is in the reference solution.

- CoolPlausiblePairKeepsNormalState establishes the initial state and avoids unnecessary hardware commands. Read the pair, classify it usable and leave Normal unchanged.
- CoolingUsesEnterAndExitHysteresis checks 55 °C entry, retained cooling between thresholds and exit at 50 °C. Add explicit state-dependent branches; a single threshold would chatter and fail the intermediate case.
- ShutdownThresholdIsInclusive checks priority and the exact 70 °C boundary. Evaluate shutdown before cooling and transition to ShutdownRequested at >= 70.
- SingleUsableSensorReportsDegradedSensing checks that one failure is different from two. In observation classify usable sensors independently, select the survivor and report DegradedSensing instead of automatically shutting down.
- SampleAtFreshnessLimitIsUsable and TwoStaleSamplesRequestShutdown check 250 ms and the two-unusable path. Include age <= 250 in isUsable; if neither reading passes, return Fault and report SensorFault before shutdown.
- FiveDegreeDisagreementIsAccepted and LargerDisagreementRequestsShutdown distinguish the inclusive 5 °C boundary. Compare only usable pairs and choose the higher reading when they agree; otherwise return Fault.
- LatchedShutdownIgnoresNormalEvaluation prevents an ordinary cool sample from silently clearing shutdown. Return early from evaluate while latched. ResetIsRejectedAboveSafeTemperature requires a fresh reset observation and rejects a maximum temperature above 50 °C; ValidResetClearsShutdownLatch requires a plausible pair at or below 50 and clears the output once.
- RepeatedCoolingStateDoesNotRepeatOutput protects against repeated hardware commands. Put output changes in transitionTo and return when the state is unchanged. The current test names do not by themselves prove every reset failure mode; add targeted cases for stale and disagreement where needed.

8. RED–GREEN AND VERIFICATION

Start with a valid cool pair, add 55/50 hysteresis, then shutdown at 70. Add usability and disagreement, then latch and reset, finally duplicate-output protection. Run each new failing test, explain the missing branch, implement the smallest change and rerun. Where a previous change already satisfies the test, keep it as evidence without inventing an edit. Integration must still check real sensor units, output acknowledgement and timing; system testing must check actual thermal behavior.
