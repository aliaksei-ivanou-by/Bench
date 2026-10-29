# E506 Live-Coding Exercises

This directory contains six self-contained C++ practice exercises for the E506 client interview. Each exercise is designed for a requirements-first, GoogleTest/GoogleMock workflow rather than an algorithm puzzle.

## Recommended use

1. Open only the exercise README.
2. Start a sixty-minute timer.
3. Spend the first five minutes asking the listed clarification questions aloud.
4. Write requirement identifiers and obtain an imaginary interviewer agreement.
5. Define interfaces and mocks before implementation.
6. Write positive, boundary, negative and failure tests.
7. Implement only the agreed behavior.
8. Finish by mapping requirements to tests and naming the missing integration and target evidence.
9. Compare your reasoning with the exercise’s bilingual Reasoning files and the detailed guidance in the parent LiveCoding document.

## Code layout

Each exercise contains:

- `include/` — the public contract and dependency interfaces;
- `tests/` — the GoogleTest and GoogleMock executable specification;
- `solution/` — the complete reference implementation;
- `CMakeLists.txt` — a standalone build that uses the reference solution by default and accepts a task-specific implementation path for practice.

The repository does not contain an intentionally incomplete implementation. To practise, create a separate `work` directory inside the selected exercise, implement the declared contract there and pass that source path through the CMake variable documented in the exercise README. This keeps the reference solution unchanged and makes the red-to-green test cycle reproducible.

## Build all reference solutions

Prerequisites are CMake 3.20 or newer and a C++17 compiler. The included `vcpkg.json` declares GoogleTest. Use a vcpkg toolchain, or provide an already installed GoogleTest package that exports `GTest::gmock_main`.

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run these commands from `E506/LiveCoding`. Every exercise may also be configured and built independently from its own directory.

With vcpkg from PowerShell, the configure command is:

```text
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
```

## Exercises

1. [Automatic Emergency Braking Request Gate](./01-aeb-request-gate/README.md)
2. [Dual Wheel-Speed Sensor Plausibility Monitor](./02-wheel-speed-plausibility-monitor/README.md)
3. [Steering Command Limiter](./03-steering-command-limiter/README.md)
4. [Battery Thermal Protection Supervisor](./04-battery-thermal-protection-supervisor/README.md)
5. [Parking-Assist Warning Coordinator](./05-parking-assist-warning-coordinator/README.md)
6. [Cabin Ambient-Light Controller](./06-cabin-ambient-light-controller/README.md)

## Coding guidelines and verification scope

The exercises use C++17 and are reviewed against selected concerns relevant to MISRA C++:2023. Production component code now checks timestamp-age arithmetic without signed overflow, and the steering limiter rejects elapsed intervals that cannot be represented. The ambient-light color switch handles an unsupported value explicitly. Online learning snapshots use compound bodies for single-line selection statements. These changes improve specific properties; they are not a claim of full MISRA compliance.

A compliance claim requires the applicable guideline set, project configuration, qualified enforcement and documented deviations. The licensed MISRA rule text, a configured MISRA checker, compiler and target-specific library evidence were not available for this exercise. Google Test, Google Mock and test-only snapshot code are host-side training infrastructure, not assessed production components. Interfaces, standard-library use, exceptions, time-source assumptions and any other applicable rules still require review under the actual project's ruleset. MISRA Compliance:2020: https://www.misra.org.uk/app/uploads/2021/06/MISRA-Compliance-2020.pdf

## Scope rule

ASIL values are discussion exercises, not candidate-experience claims. A real ASIL comes from item-level HARA and allocated safety requirements. The exercise may provide assumptions, but the candidate should never classify a C++ class from its name alone.

