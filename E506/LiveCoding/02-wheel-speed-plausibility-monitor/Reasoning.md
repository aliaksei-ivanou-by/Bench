DUAL WHEEL-SPEED MONITOR — REASONING

1. UNDERSTAND THE TASK

I restate the goal: compare two speed readings and publish availability, not decide which sensor is correct. I ask who consumes the status, what units and clock are used, whether missing data differs from disagreement, and whether outputs repeat every cycle. These answers determine the state machine and its external effects.

2. AGREE THE CONTRACT

Values must be finite and in [0, 100] m/s. Age 50 ms is allowed; 51 ms is stale. A future timestamp is invalid. An absolute difference <= 1.5 m/s is plausible. Three consecutive disagreements enter Degraded; one plausible reading resets that counter. Missing, stale or invalid input degrades immediately. Five consecutive plausible cycles recover Available; a bad cycle interrupts recovery. Publish status only on transition. The initial state is Available without an initial notification.

3. DERIVE STATE AND FLOW

Inject both sensors, the monotonic clock, status output and diagnostic sink. Keep separate bad and recovery counters. Each tick reads the sensors once, then handles missing input, timestamp validity, freshness and numeric range before comparing speeds. An unusable input reports a diagnostic, resets counters and enters Degraded immediately. A transition helper publishes only a changed status. Repeated invalid ticks may still report diagnostics: only status publication is deduplicated.

For example, differences 1.6, 1.6 and 1.6 produce Degraded on the third cycle. A 1.5 between them resets the streak. Once degraded, four plausible cycles are insufficient; the fifth recovers. Any unusable or implausible sample interrupts recovery. Keeping counters distinct prevents one history from contaminating the other.

4. TEST AND IMPLEMENT IN INCREMENTS

Start with equal inputs and no status publication; add the exact 1.5 boundary. Feed sequential samples to the same instance and inspect the status and calls after each tick. Add bad-count reset, each missing sensor, 50/51 ms, future time, NaN, infinity, out-of-range values, four versus five recovery cycles and interrupted recovery. Verify no repeated status output with strict mocks. Link REQ-WSP-001–009 to evidence; the 20 ms period requires target verification. Run the existing suite from the README.

5. EXPLAIN THE BOUNDARY

Unit tests check the decision given samples. Integration must establish sensor identity, units and timestamp conversion; target tests cover scheduling and sensor rates. The consumer and hazardous event must be known before discussing ASIL. The reference freshness check avoids signed overflow even for extreme timestamps.

6. FIRST CONVERSATION WITH THE INTERVIEWER

Say: “I understand that I report plausibility and availability, not an estimated speed. I will clarify faults and recovery before choosing state.” Draw two inputs into one monitor and two outputs: status and diagnostics. Ask whether a one-cycle discrepancy immediately changes status, whether an invalid reading follows the same path, what resets each counter and whether an initial status is published. Confirm that an injected monotonic clock shares an origin with both sample timestamps.

Write the three decisions separately: input usability, agreement between two usable values, and transition from current status. This prevents treating a missing sensor as merely one more disagreement. Agree that age 50 ms and difference 1.5 m/s are accepted. Ask how future timestamps and output failures are handled; the provided interface has no status-output acknowledgement.

7. MANUALLY TRACE THE STATE

Start in Available with bad = 0 and recovery = 0. A valid difference of 1.6 increments bad to 1; the next increments it to 2; the third resets the bad counter and changes the status to Degraded, publishing once. Instead, if the third difference is 1.5, reset bad to 0 and remain Available. A missing sample on any cycle immediately reports MissingSample and enters Degraded, resetting both counters.

While Degraded, valid agreement increments recovery; after four cycles remain Degraded, and on the fifth publish Available once. A disagreement before the fifth resets recovery to 0. Missing or stale data also resets the streak and reports its fault, even when already degraded. A status transition helper prevents duplicate status publications, but it does not suppress repeat diagnostic reports.

8. BUILD THE TEST MATRIX

First configure fixed time and equal valid values, invoke tick and assert Available without a publish. Test difference exactly 1.5 separately from 1.5001. With one monitor instance, supply three consecutive bad pairs and assert both the intermediate status and a single final publish. Insert a good cycle after two bad ones to test reset; use a new sequence to reach three.

Test absence of each sensor, a sample at 50 ms and one at 51 ms, future timestamps, NaN, infinity, negative and over-100 values. After forcing Degraded, test four good pairs, the fifth pair, and a bad pair that interrupts recovery. Use StrictMock or explicit Times(0) to show no duplicate status call, and assert diagnostic calls independently. Map these observations to REQ-WSP-002–009; the external 20 ms schedule belongs to REQ-WSP-001 and needs target evidence.

9. IMPLEMENT AND FINISH

Create named constants, read each sensor, reject missing values, then read the clock and validate timestamps and numeric ranges. Only then compute the absolute difference. In Available, clear recovery and update bad; in Degraded, clear bad and update recovery. Centralize entering a new status and publishing it; reset the appropriate counters for immediate faults. Run a focused test after each branch, then the full suite. Explain that a passing mock test does not verify real sensor transport, clock conversion or scheduling jitter.

10. EXISTING TESTS: REASON AND RESULTING CODE

This is a suggested learning sequence, not the actual history. The names are in tests/WheelSpeedMonitorTest.cpp; code references describe solution/WheelSpeedMonitor.cpp.

- EqualValuesKeepAvailableWithoutNotification checks the initial state and prohibits unnecessary output. Initialize status_ to Available, read valid inputs and leave the state unchanged. A transition helper should return when the next state equals the current state.
- ExactDifferenceLimitIsPlausible catches an accidental strict comparison. Compute fabs(primary - secondary) <= 1.5, after validation, and leave the monitor Available.
- ThirdConsecutiveBadCycleDegrades distinguishes a sustained fault from one noisy cycle. Maintain bad_cycles_, increment it only for implausible usable pairs and enter Degraded on the third; publish the transition once.
- PlausibleCycleResetsBadCounter catches accumulation of nonconsecutive errors. Reset bad_cycles_ on a plausible cycle while Available, so two old failures cannot combine with a later failure.
- MissingSensorDegradesImmediately distinguishes absence from ordinary disagreement. Before accessing either optional, report MissingSample, reset both counters and enter Degraded. The existing test checks one missing-sensor case; test the other port as an additional case.
- FiftyMillisecondSampleIsAccepted and FiftyOneMillisecondSampleIsStale lock the inclusive freshness boundary. Reject only an age greater than 50 ms. The reference separately rejects future timestamps; these two tests do not independently exercise that branch.
- InvalidValueDegradesImmediately is parameterized over invalid values. Validate finiteness and the 0–100 m/s range before computing disagreement; report InvalidSample and use the immediate-degradation path. Inspect the test parameters before asserting a particular value is covered.
- FifthPlausibleCycleRecovers demonstrates consecutive recovery, not simply a single good reading. Keep recovery_cycles_ separately; increment for plausible pairs in Degraded, switch on the fifth and reset it. A separate interrupted-recovery test would make the reset rule more explicit.
- RepeatedDegradedCyclesDoNotRepublishStatus protects the output side effect. Centralize status changes in enter and publish only when next differs; diagnostic reporting can still occur on repeated faults.

11. RED–GREEN EXAMPLE

Start with the equal-values test and a minimal Available path. Add exact difference, then three bad cycles, then the reset by a good cycle. Next introduce missing and invalid input and the shared immediate-fault helper. Add freshness checks, then the separate recovery counter and notification suppression. After each new test, explain its failure and the smallest change that addresses the requirement; if the behavior already passes, retain the test as regression evidence without inventing a code change. Finish by running the full suite and pointing out untested future-time, both-port and interrupted-recovery cases where applicable.
