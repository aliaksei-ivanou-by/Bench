STEP-BY-STEP WHEEL SPEED MONITOR PRACTICE IN COMPILER EXPLORER

1. HOW TO USE THESE FILES

Imagine that the interviewer has described the task and the project editor is empty. This folder contains 25 standalone source snapshots, from an empty program to the existing full test suite. Each .cpp contains everything needed for one run. This is a teaching sequence, not actual commit history.

Set up Compiler Explorer using the adjacent OnlineCompiler.md: C++ language, Executor pane, x86-64 GCC 13.2, -std=c++17 and Google Test trunk. Open files in number order and replace the entire online editor contents each time. Compare adjacent files in your IDE to see the edits. Each red/green pair contains the same tests; green adds behavior that fixes the expected failure.

All C++ snapshots contain Russian comments explaining the purpose of types, ports, mocks, assertions and branches. Read them alongside the step description; a branch comment describes the current teaching snapshot.

Red means the code builds and a test intentionally fails; a nonzero run exit is expected. Green means every test in that snapshot passes. A compile failure, missing library or a program that never runs is not the expected red. A passing intermediate snapshot proves only the tests added so far, not the entire specification.

2. DISCUSS THE TASK FIRST

Before coding, restate the boundary: the component compares two speed readings and reports Available or Degraded; it does not select the true speed. Clarify units, range, data age, exact disagreement boundary, numbers of consecutive bad and recovery cycles, missing input behavior and publication rules. The agreed practice requirements are in the exercise README.md. If the interviewer changes a condition, agree a new test before changing implementation.

SDD → TDD → IMPLEMENTATION: START AND END OF EACH PHASE

SDD starts with the interviewer's task and ends for the first increment after questions, boundary, examples and REQ-WSP-001–009 are agreed in README steps 1–2. The exercise then prepares ports, mocks and a test matrix: 00–02 check the environment and scaffold. Their passing demonstration tests do not establish a red–green cycle for the monitor's decision logic.

For each increment the TDD red phase starts when the new test is written and ends only when it fails for the expected behavior. The implementation phase starts in the next green snapshot: implement the minimum change and run the new and previous tests until green; then refactor with tests passing. In TDD, green and refactor are part of the same cycle. An unexpected compilation or dependency failure is not red evidence.

- 03 → 04: test equal inputs and dependency reads, then implement the read path.
- 05 → 06: test degradation on the third disagreement, then implement the bad-cycle counter and transition.
- 07 → 08: test interruption of the bad sequence, then reset the counter on a plausible input.
- 09 → 10: test missing input, then add immediate diagnosis and degradation.
- 11 → 12: test stale input, then add timestamp and freshness checks.
- 13 → 14: test NaN, then add numeric validation.
- 15 → 16: test recovery on the fifth good pair, then implement the recovery counter.

Each red file is a starting test plus the previous implementation; each green file is the corresponding implementation increment. The exercise does not show a separate refactor snapshot for each pair: refactor after green where useful, and rerun tests. Step 17 replaces the teaching implementation and tests with the complete reference and existing suite; the remaining tests are not individually demonstrated as red first. It is a final comparison and unit verification point, not proof of target timing or system safety.

If a requirement becomes unclear during a cycle, pause implementation, return to SDD to agree the behavior, and update affected tests. After the full suite, close with requirement coverage and integration, target and vehicle verification as described in README step 6.

HOW FILE NUMBERS MAP TO THE EXERCISE README

- README step 1: ask the questions before running 00-empty.cpp. The file does not answer questions on the interviewer's behalf.
- README step 2: agree REQ-WSP-001–009 before development. Steps 00 and 01 check the environment, not implementation of those requirements.
- README step 3: files 01a–01g gradually introduce data, four port types and mocks; two separate instances of the sensor mock represent primary and secondary. 02-contract-green.cpp assembles the complete fixture.
- README step 4: test-matrix scenarios are introduced progressively together with implementation in steps 03–17. For example, 03/04 covers equal values, 05/06 the third disagreement, 07/08 counter reset, 09/10 missing input, 11/12 stale data, 13/14 NaN and 15/16 recovery. Remaining existing cases appear in 17; useful additional checks are discussed at the end of the guide.
- README step 5: implementation is added in green files after the corresponding red test. Therefore steps 4 and 5 alternate instead of being completed once as large separate blocks.
- README step 6: after 17, map unit evidence to requirements and identify integration, target and vehicle-level checks. These are not automatically performed by the online compiler.

ADDITIONAL SUBSTEPS AFTER 01-GTEST-SMOKE.CPP

01a-sample-green.cpp adds SpeedSample with speed and a std::int64_t timestamp in milliseconds. SampleStoresSpeedAndTimestamp checks that data can be created and read. This is a teaching test of the data structure, not the algorithm. Two tests pass including the smoke test.

01b-status-green.cpp adds Status and Diagnostic enums. StatusValuesAreDistinct shows two distinct statuses. Three tests pass; monitor behavior is not yet tested.

01c-sensor-green.cpp adds ISpeedSensor with read() returning optional<SpeedSample>, and MockSensor. SensorReturnsConfiguredSample configures and reads the mock directly to demonstrate the interface and EXPECT_CALL. Four tests pass. Two instances of the same mock class will later represent the two physical inputs.

01d-clock-green.cpp adds IMonotonicClock and MockClock. ClockReturnsConfiguredTime sets and checks a fixed time of 1000 ms. Five tests pass. This prepares controlled time; it does not yet check sample freshness.

01e-status-output-green.cpp adds IStatusOutput and MockStatusOutput. StatusOutputObservesPublication demonstrates an expectation for publish(Degraded). Six tests pass. In this demonstration the output is called manually, not by the monitor.

01f-diagnostics-green.cpp adds IDiagnosticSink and MockDiagnosticSink. DiagnosticSinkObservesFault demonstrates an expectation for report(MissingSample). Seven tests pass. As in the previous substep, this checks mock setup.

01g-component-green.cpp adds a minimal WheelSpeedMonitor: the constructor stores references to five dependencies, status returns initial Available and tick is empty. Monitor.InitialStateIsAvailable creates two separate sensor mocks and the other dependencies; eight tests pass. Those mocks are not called by this test.

These demonstration tests introduce the interfaces incrementally. The next file, 02-contract-green.cpp, replaces them with a shared fixture and a separate initial-state test, so the test count returns to one. This is a deliberate restructuring of teaching code, not a loss of tests for a completed algorithm.

3. STEPS 00–02: EMPTY ENVIRONMENT AND CONTRACT

00-empty.cpp is the starting point: only main returning 0. Run it: exit code 0, no tests yet. This checks the compiler, not the product.

01-gtest-smoke.cpp adds Google Test and Google Mock includes, one Environment.TestFrameworkRuns test and main with InitGoogleMock and RUN_ALL_TESTS. Expect one passing test. It checks the environment, not the monitor.

02-contract-green.cpp combines the types, ports and mocks introduced in 01a–01g into a WheelSpeedMonitorTest fixture with expectCycle and sample. There are no counters or enter/degradeImmediately helpers yet: they are added alongside the behavior that needs them. tick is empty. InitialStateIsAvailable checks only initial status and passes.

4. STEPS 03–08: CYCLES AND RESET

03-equal-red.cpp adds EqualValuesKeepAvailableWithoutNotification to the previous test. The fixture expects both sensors and the clock to be read; the empty tick does not do that. The run should report a failed test and mock expectations.

04-equal-green.cpp reads both sensors and the clock, guards missing values and leaves status unchanged for now. Both tests pass. The missing-value guard only returns without diagnostics at this stage; it is an incomplete stub fixed at step 10.

05-three-bad-red.cpp adds ThirdConsecutiveBadCycleDegrades: three pairs of 20.0 and 21.6 must publish Degraded once. The previous implementation does not count disagreement, so the test fails.

06-three-bad-green.cpp adds absolute-difference comparison against 1.5, bad_cycles_ and transition through enter on the third bad cycle. Three tests pass. A good cycle does not yet reset accumulated errors.

07-reset-red.cpp adds PlausibleCycleResetsBadCounter: two bad pairs, one good and two more bad pairs must not produce Degraded. The previous code accumulates bad cycles across the good pair and causes an unexpected publish, so the test fails.

08-reset-green.cpp resets bad_cycles_ to 0 for a plausible input. Four tests pass. Compared with 06, the key change is clearing the counter before returning on a good pair.

5. STEPS 09–14: FAILURES AND VALIDATION

09-missing-red.cpp adds MissingSensorDegradesImmediately. The previous guard returns without a diagnostic or publication; the test requires MissingSample and Degraded and fails without intentionally dereferencing an empty optional.

10-missing-green.cpp calls degradeImmediately when either input is absent: both counters reset, MissingSample is reported and enter publishes Degraded only on change. Five tests pass. The enter helper appeared at step 06; degradeImmediately is added now. The recovery counter arrives later, so only bad_cycles_ is reset at this point.

11-stale-red.cpp adds FiftyOneMillisecondSampleIsStale: at now = 1000, timestamp 949 is 51 ms old. The previous code does not yet validate freshness, so the test fails.

12-stale-green.cpp reads the clock once and checks future timestamps and both sample ages: age over 50 ms gives StaleSample and future time gives InvalidSample. Six tests pass. The new test checks 51 ms; the exact 50 ms boundary arrives in the full suite at step 17. The freshness check avoids signed overflow even for extreme timestamp values; the clock origin and units still need a system-level contract.

13-invalid-red.cpp adds the teaching test NaNDegradesImmediately. NaN must not be considered usable and must cause InvalidSample and Degraded. The previous implementation does not check finiteness, so the test fails.

14-invalid-green.cpp adds std::isfinite and the 0–100 m/s range check for both sensors before computing the difference. Failure calls degradeImmediately with InvalidSample. Seven tests pass. At this step NaN is one example; the full parameterized test adds other values later.

6. STEPS 15–17: RECOVERY AND THE FULL SUITE

15-recovery-red.cpp adds FifthPlausibleCycleRecovers. After immediate degradation, four good pairs must keep Degraded and the fifth must publish Available once. Recovery was not implemented, so the final expectation fails.

16-recovery-green.cpp adds a separate recovery_cycles_ and its reset on an immediate fault: while Degraded, good pairs increment the counter, a bad pair resets it and the fifth good pair enters Available. Eight tests pass. The original complete solution also explicitly resets counters in the corresponding transitions.

17-full-suite-green.cpp is a separate copy of OnlineCompiler.cpp with the original contract, complete reference solution and original tests. Expect 15 passing tests: eleven ordinary tests and four parameterized runs, including two timestamp-arithmetic cases. This snapshot replaces the teaching implementation with the reference, adds the remaining existing tests and removes the teaching tests InitialStateIsAvailable and NaNDegradesImmediately; it is therefore not just added lines on step 16. Compare it with 16 and inspect named constants and complete validation.

7. WORKING WITH RED AND GREEN

Before running red, state the test expectation and predict why the current code violates it. Find the missing or unexpected mock call and any incorrect status. Then make the smallest change yourself in the editor, run again and only afterward compare your code with the next green file. If the site runs automatically while pasting, wait until the full file is in place before judging the result.

Finally map tests to REQ-WSP-001–009 and discuss gaps: targeted tests for the other missing sensor, future time and interrupted recovery could strengthen the suite. Mock-based unit tests do not establish the 20 ms scheduler period, real sensors, transport or clock conversion. Do not infer ASIL without defining the system and hazard.
