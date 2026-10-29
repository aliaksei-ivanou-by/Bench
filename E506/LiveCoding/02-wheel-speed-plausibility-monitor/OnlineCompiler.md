RUNNING WHEEL SPEED MONITOR IN AN ONLINE COMPILER

1. WHAT YOU NEED

The exercise uses C++17, Google Test and Google Mock. Pasting the test file alone into an empty online compiler is insufficient: it also needs the component header, implementation and linked libraries. The adjacent OnlineCompiler.cpp combines the current WheelSpeedMonitor.h, reference WheelSpeedMonitor.cpp, WheelSpeedMonitorTest.cpp and a main function that runs the tests.

On 29 October 2026 this file was checked through Compiler Explorer using x86-64 GCC 13.2, -std=c++17 and Google Test trunk: all 13 tests ran and passed. Trunk changes over time; library availability and the site's interface can change too.

2. RUN IN COMPILER EXPLORER

1. Open https://godbolt.org/ and select C++.
2. Open OnlineCompiler.cpp from this folder in your IDE, copy it in full and replace the source editor contents on the site.
3. Add an execution pane using Add new... → Executor or Compiler Execution Only. If one is already open, use it. A regular compiler pane showing assembly does not by itself mean the tests have run.
4. In the execution pane select x86-64 GCC 13.2 and enter -std=c++17 in Compiler options.
5. In the same pane open Libraries, find Google Test and select trunk. It includes Google Test and Google Mock headers and libraries. Wait for the library setup. If a separate compiler pane is open, its library selection may not apply to the execution pane.
6. Use the compile or execute control in the Executor pane if automatic execution is disabled. Wait for Compiler output and program output. The tests do not need stdin.
7. Check the program output for [  PASSED  ] 13 tests. Four are separate invocations of one parameterized test. A zero exit code means success; if you see [  FAILED  ], inspect the test message.

3. HOW TO PRACTISE

To start from an empty project, open OnlineSteps/Guide.md: it describes 25 snapshots that add tests and logic in sequence. Each snapshot can be pasted into Executor as a complete file.

OnlineCompiler.cpp contains the contract first, then implementation, tests and main. For practice, change only the WheelSpeedMonitor implementation in the online editor and rerun the tests. For example, temporarily change the 1.5 threshold to 1.0: the exact-boundary test alone may not detect that error in a single cycle, so inspect which checks actually fail and discuss the missing coverage. Restore the original value after the experiment.

OnlineCompiler.cpp is a standalone copy, not an automatically updated view of the three source files. If the exercise source or tests change, update the copy separately. For normal local development use the original files and CMake described in the exercise README; OnlineCompiler.cpp is not part of the CMake build.

4. TROUBLESHOOTING

- gmock/gmock.h or gtest/gtest.h: No such file or directory — check that Google Test trunk is selected in the execution pane and the language is C++.
- cannot find -lgtest or -lgmock, undefined reference — check the Google Test library and Linux x86-64 GCC 13.2 selection. Trunk linked in the verified configuration; version 1.10.0 could not find -lgtestd and -lgmockd during the check.
- undefined reference to main — copy all of OnlineCompiler.cpp, including its final main function. Do not add a second main.
- Errors about optional or nested namespaces — check -std=c++17.
- No [ RUN ] or [ PASSED ] lines — check the program output in Executor: successful compilation is not the same as executing tests.
- If output differs, check the library version, GCC and file contents; the service may have changed since the check.

OnlineGDB supports multiple source files, but availability of the required Google Test and Google Mock libraries in its environment has not been verified for this exercise. The tested path here uses Compiler Explorer.

Sources: https://godbolt.org/ and https://godbolt.org/api/libraries/c++ — Compiler Explorer interface and library catalogue; checked 29 October 2026.
