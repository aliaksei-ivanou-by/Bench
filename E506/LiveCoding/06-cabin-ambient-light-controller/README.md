# Cabin Ambient-Light Controller

## Goal

Implement a small C++ controller that restores a preferred cabin-light color, applies driver requests and persists successful changes. This is the QM contrast exercise: the engineering flow remains disciplined even when the function is not safety-related.

Use GoogleTest and GoogleMock to specify ordering, failure behavior and state consistency. The task tests requirements discipline more than algorithm knowledge.

## Suggested files

- `AmbientLightController.h`
- `AmbientLightController.cpp`
- `AmbientLightControllerTest.cpp`

## Code package

- `include/AmbientLightController.h` defines driver, storage and diagnostic ports.
- `tests/AmbientLightControllerTest.cpp` verifies call order, state and partial failure.
- `solution/AmbientLightController.cpp` contains the reference solution.
- `CMakeLists.txt` builds the reference solution by default.

To practise, create `work/AmbientLightController.cpp` and configure this directory with:

```text
cmake -S . -B build -DAMBIENT_LIGHT_IMPLEMENTATION="$PWD/work/AmbientLightController.cpp"
cmake --build build
ctest --test-dir build --output-on-failure
```

The tests make the apply-before-save contract and partial-success policy observable.

## Step 1: Establish the system boundary

The controller owns color validation, active state and coordination between the light driver and preference storage. Hardware access, persistent storage and diagnostics are external dependencies.

Clarify these points before coding:

- Which colors are supported?
- What is the startup default?
- Does an unsupported stored value prevent startup?
- Must hardware application happen before persistence?
- What state is reported if hardware succeeds but persistence fails?
- Should repeated requests for the active color touch hardware or storage?
- May the storage or driver throw exceptions, or do they return status values?

## Step 2: Agree the requirements

- REQ-LGT-001: Supported colors are `WarmWhite`, `White`, `Blue` and `Red`.
- REQ-LGT-002: The default color is `WarmWhite`.
- REQ-LGT-003: On initialization, a supported stored preference is applied to the light driver.
- REQ-LGT-004: If no preference exists, the default is applied and then persisted after successful hardware application.
- REQ-LGT-005: An unsupported stored value is reported, replaced by the default and handled like a missing preference.
- REQ-LGT-006: A driver-requested supported color is applied to hardware before it is persisted.
- REQ-LGT-007: If hardware application fails, the active state remains unchanged, nothing is persisted and `DriverFailure` is reported.
- REQ-LGT-008: If persistence fails after successful hardware application, the new color remains active and `PersistenceFailure` is reported.
- REQ-LGT-009: Requesting the already active color returns success without calling the driver or storage.
- REQ-LGT-010: A successful change updates the active color and clears the relevant transient diagnostic.

The interviewer must agree whether a persistence failure changes the public return value. For this exercise, the operation returns failure because the requested durable change was only partially completed.

## Step 3: Define interfaces and mocks

Create minimal interfaces for:

- a light driver with `apply(Color)`;
- a preference store with `load()` and `save(Color)`;
- a diagnostic reporter.

The controller exposes `initialize()`, `setColor(Color)` and `activeColor()`. Avoid a global singleton and hidden file-system access.

## Step 4: Write tests before implementation

Cover at least these scenarios:

1. A supported stored preference is applied at startup.
2. A missing preference applies and then persists `WarmWhite`.
3. An unsupported stored value is diagnosed and replaced by `WarmWhite`.
4. A supported driver request calls hardware before storage.
5. A successful request updates the active color.
6. A hardware failure does not call storage and does not change active state.
7. A persistence failure after hardware success keeps the new active color and reports the failure.
8. A request for the active color calls neither dependency.
9. An unsupported runtime request is rejected without side effects.
10. A later successful save clears the persistence-failure diagnostic.

Use an ordered expectation for the apply-before-save contract. Verify state after each failure, not only the returned status.

## Step 5: Implement

- Represent supported colors with a closed enum.
- Centralize validation and default selection.
- During initialization, choose the stored valid value or the default.
- Apply hardware before updating active state or saving preference.
- After hardware success, update active state and then attempt persistence.
- Make the partial-success policy visible in the return type and tests.
- Avoid calls when the requested color is already active.

## Step 6: Explain verification boundaries

- Unit tests prove selection, call order, state changes and dependency-failure behavior.
- Integration tests must verify serialization, storage recovery and the real driver API.
- Target tests must verify startup sequencing and actual lamp behavior.
- Product tests should verify perceived color, brightness consistency and persistence across a power cycle.

## Quality-classification prompt

Based on the stated boundary, incorrect ambient-light color affects comfort rather than vehicle safety, so QM is a reasonable provisional conclusion. Still ask whether color is reused for safety warnings or driver-state alerts. If it is, the item boundary and hazard analysis change before any classification is accepted.

The point is not that QM permits casual development. Requirements, testable interfaces, negative tests and change control are still expected; the safety lifecycle and evidence burden differ.

## Completion criteria

- All ten requirements are represented by tests.
- Hardware application precedes persistence.
- Every failure path has an explicit state outcome.
- Repeated requests do not produce side effects.
- Unsupported values are deterministic.
- The QM rationale and its assumptions are stated clearly.

## Optional extensions

- Persist brightness together with color.
- Add a retry queue for preference writes.
- Add schema-version migration for stored preferences.
- Replace the boolean result with a typed result describing full success and partial success.
