STEP-BY-STEP WHEEL SPEED MONITOR PRACTICE IN COMPILER EXPLORER

1. HOW TO USE THESE FILES

Imagine that the interviewer has described the task and the project editor is empty. This folder contains 18 standalone source snapshots, from an empty program to the existing full test suite. Each .cpp contains everything needed for one run. This is a teaching sequence, not actual commit history.

Set up Compiler Explorer using the adjacent OnlineCompiler.md: C++ language, Executor pane, x86-64 GCC 13.2, -std=c++17 and Google Test trunk. Open files in number order and replace the entire online editor contents each time. Compare adjacent files in your IDE to see the edits. Each red/green pair contains the same tests; green adds behavior that fixes the expected failure.

Red means the code builds and a test intentionally fails; a nonzero run exit is expected. Green means every test in that snapshot passes. A compile failure, missing library or a program that never runs is not the expected red. A passing intermediate snapshot proves only the tests added so far, not the entire specification.

2. DISCUSS THE TASK FIRST

Before coding, restate the boundary: the component compares two speed readings and reports Available or Degraded; it does not select the true speed. Clarify units, range, data age, exact disagreement boundary, numbers of consecutive bad and recovery cycles, missing input behavior and publication rules. The agreed practice requirements are in the exercise README.md. If the interviewer changes a condition, agree a new test before changing implementation.

3. STEPS 00–02: EMPTY ENVIRONMENT AND CONTRACT

00-empty.cpp is the starting point: only main returning 0. Run it: exit code 0, no tests yet. This checks the compiler, not the product.

01-gtest-smoke.cpp adds Google Test and Google Mock includes, one Environment.TestFrameworkRuns test and main with InitGoogleMock and RUN_ALL_TESTS. Expect one passing test. It checks the environment, not the monitor.

02-contract-green.cpp adds SpeedSample, Status and Diagnostic, ports for two sensors, clock, output and diagnostics, the WheelSpeedMonitor class, mocks and test fixture. tick is still empty. InitialStateIsAvailable checks only initial status, does not call tick and passes. The contract is added together for convenient copying; discuss it with the interviewer before this step instead of assuming it was provided.

4. STEPS 03–08: CYCLES AND RESET

03-equal-red.cpp adds EqualValuesKeepAvailableWithoutNotification to the previous test. The fixture expects both sensors and the clock to be read; the empty tick does not do that. The run should report a failed test and mock expectations.

04-equal-green.cpp reads both sensors and the clock, guards missing values and leaves status unchanged for now. Both tests pass. The missing-value guard only returns without diagnostics at this stage; it is an incomplete stub fixed at step 10.

05-three-bad-red.cpp adds ThirdConsecutiveBadCycleDegrades: three pairs of 20.0 and 21.6 must publish Degraded once. The previous implementation does not count disagreement, so the test fails.

06-three-bad-green.cpp adds absolute-difference comparison against 1.5, bad_cycles_ and transition through enter on the third bad cycle. Three tests pass. A good cycle does not yet reset accumulated errors.

07-reset-red.cpp adds PlausibleCycleResetsBadCounter: two bad pairs, one good and two more bad pairs must not produce Degraded. The previous code accumulates bad cycles across the good pair and causes an unexpected publish, so the test fails.

08-reset-green.cpp resets bad_cycles_ to 0 for a plausible input. Four tests pass. Compared with 06, the key change is clearing the counter before returning on a good pair.

5. STEPS 09–14: FAILURES AND VALIDATION

09-missing-red.cpp adds MissingSensorDegradesImmediately. The previous guard returns without a diagnostic or publication; the test requires MissingSample and Degraded and fails without intentionally dereferencing an empty optional.

10-missing-green.cpp calls degradeImmediately when either input is absent: both counters reset, MissingSample is reported and enter publishes Degraded only on change. Five tests pass. The enter and degradeImmediately scaffolding was declared earlier with the contract; the path is now actually used.

11-stale-red.cpp adds FiftyOneMillisecondSampleIsStale: at now = 1000, timestamp 949 is 51 ms old. The previous code does not yet validate freshness, so the test fails.

12-stale-green.cpp reads the clock once and checks future timestamps and both sample ages: age over 50 ms gives StaleSample and future time gives InvalidSample. Six tests pass. The new test checks 51 ms; the exact 50 ms boundary arrives in the full suite at step 17. This code assumes timestamps are in a safe range; production needs an agreed range or checked subtraction without overflow.

13-invalid-red.cpp adds the teaching test NaNDegradesImmediately. NaN must not be considered usable and must cause InvalidSample and Degraded. The previous implementation does not check finiteness, so the test fails.

14-invalid-green.cpp adds std::isfinite and the 0–100 m/s range check for both sensors before computing the difference. Failure calls degradeImmediately with InvalidSample. Seven tests pass. At this step NaN is one example; the full parameterized test adds other values later.

6. STEPS 15–17: RECOVERY AND THE FULL SUITE

15-recovery-red.cpp adds FifthPlausibleCycleRecovers. After immediate degradation, four good pairs must keep Degraded and the fifth must publish Available once. Recovery was not implemented, so the final expectation fails.

16-recovery-green.cpp adds a separate recovery_cycles_: while Degraded, good pairs increment it, a bad pair resets it and the fifth good pair enters Available. Eight tests pass. The original complete solution also explicitly resets counters in the corresponding transitions.

17-full-suite-green.cpp is a separate copy of OnlineCompiler.cpp with the original contract, complete reference solution and original tests. Expect 13 passing tests: nine ordinary tests and four parameterized runs. This snapshot replaces the teaching implementation with the reference, adds the remaining existing tests and removes the teaching tests InitialStateIsAvailable and NaNDegradesImmediately; it is therefore not just added lines on step 16. Compare it with 16 and inspect named constants and complete validation.

7. WORKING WITH RED AND GREEN

Before running red, state the test expectation and predict why the current code violates it. Find the missing or unexpected mock call and any incorrect status. Then make the smallest change yourself in the editor, run again and only afterward compare your code with the next green file. If the site runs automatically while pasting, wait until the full file is in place before judging the result.

Finally map tests to REQ-WSP-001–009 and discuss gaps: targeted tests for the other missing sensor, future time and interrupted recovery could strengthen the suite. Mock-based unit tests do not establish the 20 ms scheduler period, real sensors, transport or clock conversion. Do not infer ASIL without defining the system and hazard.
