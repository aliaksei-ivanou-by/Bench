CODING-GUIDELINE REVIEW OF THE LIVE-CODING EXERCISES

1. BASELINE AND SCOPE

The six exercises use C++17. The working review baseline is MISRA C++:2023, subject to the actual project's selected rules and deviations. Review scope is the component headers and reference implementations, the combined online copy of the wheel-speed monitor, and the teaching snapshots. Google Test, Google Mock and the test portions of the snapshots are host-side test infrastructure; they have not been assessed as production code.

2. SPECIFIC CHANGES

- AEB, wheel speed, steering, battery and parking: freshness checks avoid signed overflow when comparing timestamps across the full signed range. They retain the agreed inclusive age boundaries. The helper requires a nonnegative age limit and a timestamp no later than now; the caller establishes those conditions.
- Steering: an elapsed interval that cannot be represented by the signed time type is rejected as InvalidTime before subtraction. This edge case is now part of the exercise contract.
- Wheel speed: counters and their limits use fixed-width unsigned types and unsigned constants. Parking sensor count and indexes use unsigned constants appropriate to their unsigned types.
- Ambient light: the color-validation switch has an explicit default path and a single return; an unsupported value remains rejected.
- Wheel-speed online snapshots: conditional statement bodies use braces; freshness logic and the final online copy are synchronized with the reference behavior. Red snapshots remain deliberately failing tests and must not be treated as completed production code.

3. EVIDENCE AND LIMITATIONS

Tests cover extreme timestamp ranges, the negative-time freshness boundary and unrepresentable steering elapsed time. Host-side execution with UndefinedBehaviorSanitizer checks exercised paths for undefined behavior; it does not establish guideline compliance or target behavior. Integration still needs to validate clock origin, resolution, rollover policy, task timing, output semantics and physical interfaces.

No licensed MISRA C++:2023 rule text, project-specific guideline enforcement plan, configured MISRA analyzer or target-library conformance evidence was available for this review. A full audit is therefore outstanding: it includes applicable rules and directives, deviations, compiler and standard-library behavior, dynamic-memory and exception policy, interface contracts and any third-party components in the intended target scope. No MISRA compliance claim is made for these exercises.

Reference: MISRA Compliance:2020, https://www.misra.org.uk/app/uploads/2021/06/MISRA-Compliance-2020.pdf
