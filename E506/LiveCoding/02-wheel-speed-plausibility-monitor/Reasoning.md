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

Unit tests check the decision given samples. Integration must establish sensor identity, units and timestamp conversion; target tests cover scheduling and sensor rates. The consumer and hazardous event must be known before discussing ASIL. For extreme timestamps, production code also needs bounded clock values or checked subtraction to prevent signed overflow.
