PARKING-ASSIST WARNING COORDINATOR — REASONING

1. RESTATE AND ASK

This is an advisory coordinator for four sensors, not automatic braking. I ask about units, valid ranges, freshness, ordering, lost sensors, exact warning bands, initial publication and repeated outputs. A missing sensor must not silently mean an empty parking area.

2. FIX THE CONTRACT

A usable sample has a valid acquisition flag, finite distance in [0.10, 5.00] m, timestamp no later than now, age <= 200 ms and timestamp no older than the last accepted timestamp for that sensor. Equal timestamps are allowed and do not replace stored time. Select the minimum usable distance: <= 0.30 m Critical, <= 0.80 Near, <= 1.50 Caution, otherwise Clear. No usable sample means Unknown. Coverage is Full only when all four are usable; otherwise Degraded. Warning and coverage are independent outputs, published initially and subsequently on change.

3. DERIVE THE ALGORITHM

Read monotonic time once, then each indexed sensor once. Validate each before using its distance. Keep the last accepted timestamp per sensor, updating it only for a usable newer sample; a rejected old sample must not roll history back. Count usable samples and track their minimum. When the count is zero, choose Unknown explicitly instead of classifying an infinity sentinel as Clear. Derive coverage separately from the count. Store the last published values as optionals so an unpublished state is distinct from a published Unknown or Degraded.

For example, distances 0.30, 1.0, invalid and 2.0 m yield Critical and Degraded. Four failures yield Unknown and Degraded. Repeating the result adds no calls. If the fourth sensor recovers, coverage can change to Full while warning stays Critical; publishing both unconditionally would violate the contract.

4. TEST AND IMPLEMENT IN STAGES

Start with four clear samples and expect the first publication on both ports. Vary sensor order, test every exact threshold and a value just above it, physical limits, 200/201 ms and future time. Add one and four unusable sensors, NaN, acquisition failure, older and duplicate timestamps, recovery and unchanged outputs. Check each port independently with strict mocks. Link REQ-PAS-001–012 to tests and add hysteresis only if agreed. Run the supplied suite.

5. STATE THE LIMITS

Integration checks indexing, units and timestamps; target tests scheduling; vehicle tests check sensor geometry and driver perception. Classification depends on the actual function and hazard, not the name parking assist. Production needs bounded timestamps or checked subtraction to avoid signed overflow.
