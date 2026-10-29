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

Integration checks indexing, units and timestamps; target tests scheduling; vehicle tests check sensor geometry and driver perception. Classification depends on the actual function and hazard, not the name parking assist. The reference freshness check avoids signed overflow for extreme timestamps.

6. TURN THE REQUEST INTO DECISIONS

Restate that the component is advisory and ask what happens with one and with four unusable sensors. Agree the exact band boundaries, timestamp origin, duplicate and out-of-order behavior, and first versus repeated publication. Draw four indexed inputs, one clock and two independent outputs. Write the algorithm in four steps: validate each sample, select the nearest usable distance, derive warning and coverage independently, and publish each only when needed.

For example, 0.30 m, 1.0 m, an invalid sample and 2.0 m produce Critical and Degraded. If the faulty sensor recovers but the minimum stays 0.30 m, only coverage changes. If all sensors fail, select Unknown explicitly; an initial infinite minimum must never accidentally become Clear.

7. WHY THE EXISTING TESTS EXIST AND WHAT THEY DRIVE

This is a suggested learning sequence, not commit history. Tests are in ParkingAssistCoordinatorTest.cpp; the described behavior is in the reference implementation.

- FourClearSamplesPublishClearAndFull establishes the first observable publication. Keep last-published warning and coverage as optionals; initial internal values alone must not suppress the first outputs.
- NearestSampleWinsRegardlessOfIndex guards against selecting the first or last sensor. Iterate all four usable samples and update the minimum independently of index.
- DistanceMapsToExpectedWarning is parameterized over warning bands. Implement comparisons in order <= 0.30, <= 0.80 and <= 1.50, then Clear. Inspect the parameters to see which exact and adjacent values are covered.
- PhysicalRangeBoundariesAreUsable checks inclusive 0.10 and 5.00. Validate finite distance and range before it affects the minimum. SampleAtFreshnessBoundaryIsUsable checks the accepted 200 ms limit; an additional stale case can directly exercise rejection above it.
- OneInvalidSensorKeepsWarningAndDegradesCoverage proves two outputs have different meaning. Count usable sensors separately from the nearest distance. AllInvalidSensorsPublishUnknownNotClear adds the zero-count branch and prevents an unsafe-looking Clear on missing information.
- OutOfOrderSampleIsRejectedWithoutCorruptingTimestamp protects per-sensor history. Store an accepted timestamp for each index and do not update it on an unusable or older sample; equal timestamps are allowed. A separate duplicate-time case can verify that rule explicitly.
- RepeatedStateProducesNoExtraOutputs requires independent last-published states and comparisons before each call. SensorRecoveryRestoresFullCoverage verifies that recovery can publish coverage even if warning is unchanged.

8. RED–GREEN AND VERIFICATION

Start with first Clear/Full publication, then minimum and bands, then usability and coverage, then timestamp history and change-only output. Explain each test failure before the smallest production edit and rerun. If earlier code already makes a case green, keep it as regression evidence. Integration verifies real sensor indexes and clock conversion, target verifies timing, and vehicle tests verify actual geometry and warnings.
