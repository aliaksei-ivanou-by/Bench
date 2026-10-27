DOCUMENT INFORMATION

Request ID: E506
Candidate: Alex I.
Target role: Senior C++ Engineer / Hands-on Technical Lead
Artifact: Live-coding preparation
Language: English
Source: E506 request and candidate-supplied interview hypothesis

PURPOSE

This document prepares a repeatable sixty-minute C++ live-coding flow for a requirements-based automotive exercise. The expected task is not primarily an algorithm puzzle. It is more likely to involve a small process model, explicit interfaces, GoogleTest and GoogleMock, negative behavior, failure handling and traceability from an agreed specification to tests and implementation.

PRACTICE EXERCISE FOLDERS

Six self-contained exercises with step-by-step requirements, mocks, tests, implementation guidance and verification boundaries are indexed in LiveCoding/README.md. Each folder contains synchronized English and Russian README files and can be used independently as a timed mock interview.

EVIDENCE BOUNDARY

ISO 26262 and ASIL are preparation topics in this file, not claims of direct candidate project experience. The interview-ready position is: I have worked in formal, safety-oriented aerospace development and requirements-based verification, but I have not worked on a production project governed by ISO 26262. During live coding, I can apply a supplied V-model and safety process, make assumptions explicit and derive code and tests from agreed requirements.

The currently published ISO baseline is the 2018 edition. A third edition is under development, so the actual client baseline and tailoring rules take precedence.

LIKELY SIXTY-MINUTE FLOW

Minutes 0–5: Understand the item and the observable behavior

- Restate the problem in one sentence.
- Identify the system boundary, caller, dependencies and actuator or output.
- Ask what malfunction is safety-relevant and what the safe state is.
- Ask for units, valid ranges, timing, freshness and reset behavior.
- Ask whether the component is cyclic, event-driven or both.
- Ask whether dynamic allocation, exceptions, threads or blocking calls are allowed.
- Ask whether ASIL and safety requirements are already assigned or whether an illustrative HARA discussion is expected.
- Record unresolved points as explicit assumptions. Do not silently invent behavior.

Minutes 5–10: Write a compact specification

- Give each requirement a stable identifier such as REQ-AEB-001.
- Define inputs, outputs, preconditions and invariants.
- Define normal, boundary, invalid, stale and dependency-failure behavior.
- Define the safe state and recovery conditions.
- Define which side effects must happen once, may repeat or must never happen.
- Obtain verbal agreement before coding.

Minutes 10–15: Define interfaces and test seams

- Keep the decision logic small and deterministic.
- Inject time, sensors, actuators, diagnostics and transport through interfaces.
- Mock external boundaries, not value objects or private implementation details.
- Prefer explicit result types and status values over hidden global state.
- Make units visible in names or strong types.

Minutes 15–30: Write tests first

- Start with one positive requirement test.
- Add boundary tests at exact thresholds.
- Add invalid, missing and stale-input tests.
- Add dependency-failure and safe-state tests.
- Add temporal tests for debounce, timeout, hysteresis or repeated calls.
- Verify required interactions and forbidden actuator calls.
- Keep every test linked to at least one requirement identifier.

Minutes 30–45: Implement the minimum specified behavior

- Implement only behavior justified by the agreed requirements.
- Keep validation and state transitions explicit.
- Avoid speculative abstractions and extra features.
- Run the suite after every small change.
- Refactor only while all tests remain green.

Minutes 45–55: Strengthen the evidence

- Review uncovered branches and explain whether each is reachable.
- Add missing negative and boundary cases.
- Check repeated execution, idempotency and reset behavior.
- Check numeric overflow, NaN, invalid enums and timestamp wrap or ordering where relevant.
- Explain what unit tests cannot prove and which integration or target test would provide the next level of evidence.

Minutes 55–60: Close the V-model loop

- Map each requirement to tests and implementation.
- Summarize safe-state behavior and remaining assumptions.
- State the integration and system tests that would follow.
- Mention review, static analysis, compiler warnings and coverage evidence.
- If the item is safety-related, explain that the ASIL comes from HARA and allocated safety requirements, not from the C++ class itself.

WHAT TO SAY WHILE WORKING

- Before I write code, I want to agree on the observable contract.
- I do not want to guess the safe state. What should the component command when an input is missing or stale?
- I will write this as REQ-003 so the test name and implementation decision are traceable.
- I am mocking time because freshness is part of the behavior, not because the clock implementation is interesting.
- This test proves the unit contract. A real actuator, scheduler or bus still requires integration and target-level evidence.
- Line coverage is useful for finding gaps, but requirements and decision coverage matter more than reaching an arbitrary percentage.
- I am not adding that branch because no approved requirement defines the behavior.

V-MODEL MAPPING FOR LIVE CODING

Left side, decomposition:

- Item and hazardous event: supplied by the interviewer or discussed as an assumption.
- Safety goal: high-level statement preventing or controlling the hazardous behavior.
- Functional and technical safety requirement: required behavior and safe state.
- Software safety requirement: observable contract of the component.
- Interface and detailed design: C++ types, ports, states and algorithms.

Bottom:

- Implementation with project coding rules, warnings enabled and no unjustified behavior.

Right side, verification and validation:

- Unit tests verify detailed decisions, ranges and state transitions.
- Component tests verify the component through mocked or simulated boundaries.
- Integration tests verify real interfaces, scheduling, serialization and dependency behavior.
- Target tests verify timing, hardware, drivers and the actual execution environment.
- System validation checks that the implemented item satisfies the safety goal in representative vehicle situations.

The live-coding exercise can demonstrate the software-requirement, unit and component parts of this chain. It cannot by itself prove vehicle-level safety.

ISO 26262 AND ASIL DISCUSSION

ASIL classification belongs to the hazardous event at item level. It is derived during hazard analysis and risk assessment from:

- Severity: potential harm if the hazardous event occurs.
- Exposure: how often the relevant operational situation occurs.
- Controllability: how likely the driver or other road users can avoid the harm.

The result may be QM or ASIL A, B, C or D. ASIL D represents the highest integrity level in this scale. The class is then allocated through safety goals and safety requirements. A software class does not independently become ASIL D because its name contains brake or steering.

ASIL exercise flow:

1. Define the item and vehicle-level function.
2. Name one malfunctioning behavior, not only a component failure.
3. Combine it with a concrete operational situation.
4. Describe the hazardous event and possible harm.
5. Discuss Severity, Exposure and Controllability with explicit assumptions.
6. Use the client-provided classification table to obtain a provisional ASIL.
7. State a safety goal.
8. Derive a software requirement and its verification method.

Illustrative high-criticality assumption:

- Item: automatic emergency braking.
- Malfunctioning behavior: maximum braking without a valid obstacle.
- Operational situation: motorway driving at high speed with traffic behind.
- Training assumptions supplied by the interviewer: S3, E4 and C3.
- Provisional training result: ASIL D.
- Example safety goal: unintended emergency braking shall be prevented or controlled so that the vehicle does not create an unreasonable collision risk.

Illustrative QM contrast:

- Item: decorative cabin ambient lighting.
- Malfunctioning behavior: selected color is not applied.
- No safety-relevant harm is identified under the stated operating assumptions.
- Training result: QM, while ordinary quality requirements still apply.

Do not memorize an ASIL answer without the scenario. The same function can produce different hazardous events and classifications under different speed, traffic, driver-control and exposure assumptions.

REUSABLE SPECIFICATION TEMPLATE

Problem statement:

- Component responsibility.
- External inputs and outputs.
- Execution model.

Assumptions agreed with interviewer:

- Units and valid ranges.
- Timing and freshness.
- Safe state.
- Recovery and reset.
- Error-reporting policy.
- Allocation and exception constraints.

Requirements:

- REQ-001: Positive behavior.
- REQ-002: Boundary behavior.
- REQ-003: Invalid or missing input behavior.
- REQ-004: Timeout or stale-data behavior.
- REQ-005: Dependency-failure behavior.
- REQ-006: Repetition, idempotency or state-transition behavior.

Test matrix:

- One ordinary positive case.
- Exact lower and upper boundaries.
- Just below and just above each threshold.
- Missing input.
- Invalid enum, NaN, infinity or out-of-range number where applicable.
- Stale timestamp.
- Dependency returns failure or throws if exceptions are part of the contract.
- Duplicate event or repeated tick.
- Recovery after the fault disappears.
- Forbidden actuator interaction.

Traceability closeout:

- Requirement identifier.
- Test names.
- Implementation function or state transition.
- Next integration or target-level evidence.

MOCKING BOUNDARIES

Good mock candidates:

- Clock or monotonic time source.
- Sensor or perception input port.
- Actuator command port.
- Diagnostic-event sink.
- Persistent state or transport boundary.
- Scheduler callback when timing is part of the contract.

Do not mock by default:

- Plain value objects.
- Pure calculation functions.
- Standard containers.
- Private methods.
- Every internal collaborator merely to increase the mock count.

A mock should make an external contract controllable or observable. Excessive interaction testing makes refactoring harder and can test implementation order instead of required behavior.

FULLY WORKED EXERCISE 1 — AUTOMATIC EMERGENCY BRAKING REQUEST GATE

Prompt

Implement a cyclic C++ component that reads the latest perception sample and decides whether to send an emergency-braking request. Use GoogleTest and GoogleMock. The component must never request braking from invalid or stale data.

Questions to ask before coding

- What speed, confidence and time-to-collision thresholds apply?
- Are thresholds inclusive?
- What makes a sample stale?
- What is the safe behavior for missing, malformed or stale data?
- Does driver override suppress braking?
- Should a repeated tick resend the same command?
- How is actuator failure reported?
- Are exceptions and dynamic allocation allowed in the cyclic path?
- Is hysteresis or debounce required?
- Which ASIL and safety requirement are allocated to this component?

Interviewer-approved assumptions for this practice version

- The method tick() runs every ten milliseconds.
- Emergency braking is allowed when vehicle speed is at least 5.0 m/s, confidence is at least 0.90 and time to collision is at most 1.20 seconds.
- A sample older than 100 milliseconds is stale.
- Driver override suppresses the request.
- Missing, non-finite, out-of-range or stale data results in no braking request and one diagnostic report for the tick.
- Desired deceleration is supplied by perception but must be finite and clamped to the range 0.0 to 8.0 m/s².
- Every valid hazardous sample produces one actuator request. Idempotency across ticks is outside this version unless the interviewer adds it.
- If the actuator rejects the request, the component reports ActuatorRejected.

Requirements

- REQ-AEB-001: A fresh hazardous sample meeting all inclusive thresholds and without driver override shall produce one bounded braking request.
- REQ-AEB-002: A non-hazardous sample shall produce no braking request.
- REQ-AEB-003: Driver override shall suppress the braking request.
- REQ-AEB-004: Missing or stale input shall produce no braking request and shall report the corresponding diagnostic.
- REQ-AEB-005: NaN, infinity or values outside the agreed physical ranges shall produce no braking request and shall report InvalidSample.
- REQ-AEB-006: Desired deceleration above 8.0 m/s² shall be clamped to 8.0 m/s².
- REQ-AEB-007: Rejection by the actuator shall report ActuatorRejected.

Suggested interfaces

    using Milliseconds = std::chrono::milliseconds;
    using TimePoint = std::chrono::steady_clock::time_point;

    struct PerceptionSample {
        double vehicleSpeedMps;
        double confidence;
        double timeToCollisionSec;
        double desiredDecelerationMps2;
        bool driverOverride;
        TimePoint timestamp;
    };

    enum class Fault {
        MissingSample,
        StaleSample,
        InvalidSample,
        ActuatorRejected
    };

    class IPerceptionPort {
    public:
        virtual ~IPerceptionPort() = default;
        virtual std::optional<PerceptionSample> latest() = 0;
    };

    class IClock {
    public:
        virtual ~IClock() = default;
        virtual TimePoint now() const = 0;
    };

    class IBrakePort {
    public:
        virtual ~IBrakePort() = default;
        virtual bool request(double decelerationMps2) = 0;
    };

    class IDiagnostics {
    public:
        virtual ~IDiagnostics() = default;
        virtual void report(Fault fault) = 0;
    };

    class AebRequestGate {
    public:
        AebRequestGate(IPerceptionPort&, IClock&, IBrakePort&, IDiagnostics&);
        void tick();
    };

Test order

1. REQ-AEB-001 — requests braking for an ordinary hazardous sample.
2. REQ-AEB-001 — accepts values exactly on all three thresholds.
3. REQ-AEB-002 — no request when confidence is just below 0.90.
4. REQ-AEB-002 — no request when time to collision is just above 1.20.
5. REQ-AEB-002 — no request when speed is just below 5.0.
6. REQ-AEB-003 — driver override forbids actuator interaction.
7. REQ-AEB-004 — missing sample reports MissingSample and forbids actuator interaction.
8. REQ-AEB-004 — sample at 100 milliseconds is accepted; a sample older than that is stale.
9. REQ-AEB-005 — parameterized invalid inputs cover NaN, infinity, negative speed, confidence outside zero to one and non-positive time to collision.
10. REQ-AEB-006 — excessive deceleration is clamped to 8.0.
11. REQ-AEB-007 — actuator rejection produces the diagnostic.

Representative GoogleMock expectations

    EXPECT_CALL(perception, latest())
        .WillOnce(Return(validHazardousSample));
    EXPECT_CALL(clock, now())
        .WillOnce(Return(now));
    EXPECT_CALL(brake, request(DoubleEq(4.0)))
        .WillOnce(Return(true));
    EXPECT_CALL(diagnostics, report(_)).Times(0);

For an invalid input:

    EXPECT_CALL(perception, latest())
        .WillOnce(Return(invalidSample));
    EXPECT_CALL(brake, request(_)).Times(0);
    EXPECT_CALL(diagnostics, report(Fault::InvalidSample));

Implementation order

- Read the sample once.
- Handle missing input.
- Read the clock once and evaluate freshness.
- Validate every numeric field with std::isfinite and agreed ranges.
- Apply driver override and hazard thresholds.
- Clamp requested deceleration.
- Call the actuator once.
- Report rejection if required.

ASIL discussion

The gate does not assign its own ASIL. Start from two separate malfunctioning behaviors: unintended braking and failure to request braking. For the training scenario of unintended maximum braking at motorway speed, the interviewer supplies S3, E4 and C3, producing a provisional ASIL D exercise. The corresponding software requirements, independence expectations and verification rigor come from the allocated safety process. The unit tests above are necessary evidence but are not sufficient vehicle-level validation.

V-model evidence beyond the unit test

- Component test with a real serialized perception message.
- Integration test with the brake-command transport and diagnostic manager.
- Timing test under the target scheduler.
- Fault injection for stale, delayed, malformed and duplicated messages.
- Vehicle or HIL validation of braking and driver-override behavior.
- Trace links from safety requirement to tests, code review, coverage and results.

EXERCISE 2 — DUAL WHEEL-SPEED SENSOR PLAUSIBILITY MONITOR

Prompt

Model a cyclic monitor receiving primary and secondary wheel-speed values. A disagreement beyond a threshold for three consecutive cycles shall enter Degraded state. Five consecutive plausible cycles shall recover to Available. Missing, stale or non-finite data shall enter Degraded immediately.

Required mocks

- Two sensor ports.
- Monotonic clock.
- Diagnostic sink.
- Availability output port.

Important tests

- Both values equal and valid.
- Difference exactly on the threshold.
- Difference just above the threshold for one, two and three cycles.
- Counter reset when one plausible cycle interrupts the sequence.
- Immediate degradation for missing, stale, NaN or infinity.
- Recovery only after exactly five consecutive plausible cycles.
- No repeated availability notification when the state does not change.

ASIL discussion

Ask what vehicle function consumes the speed and what hazardous event results from an incorrect value. A display-only speed estimate and a value used for braking or stability control do not receive the same classification. Do not assign an ASIL until the operational situation and S, E and C assumptions are provided.

EXERCISE 3 — STEERING COMMAND LIMITER

Prompt

Implement a component that accepts a requested steering torque and emits a bounded command. It must enforce absolute torque and rate-of-change limits, reject stale or non-finite requests and suppress assistance when the driver-override signal is active.

Required mocks

- Command input port.
- Clock.
- Steering actuator.
- Diagnostic sink.

Important tests

- Ordinary command inside both limits.
- Exact positive and negative torque boundaries.
- Positive and negative rate limits using controlled time.
- Zero or negative elapsed time.
- NaN and infinity.
- Stale command.
- Driver override.
- Actuator rejection.
- State update only after an accepted command.

ASIL discussion

Unintended steering at speed may produce a high-severity hazardous event, but classification still depends on the defined item, operational situation, exposure and controllability. Ask whether the required safe reaction is zero torque, controlled ramp-down or transition to another controller; do not invent it.

EXERCISE 4 — BATTERY THERMAL PROTECTION SUPERVISOR

Prompt

Implement a small state machine with Normal, CoolingRequested and ShutdownRequested states. It reads two temperature sensors, validates plausibility, applies hysteresis and commands cooling or shutdown through mocked ports.

Required mocks

- Two temperature sensors.
- Clock or cycle source.
- Cooling actuator.
- Shutdown request port.
- Diagnostic sink.

Important tests

- Normal operation below the cooling threshold.
- Cooling starts exactly at the threshold.
- Hysteresis prevents rapid toggling.
- Shutdown starts at the critical threshold.
- Disagreement between sensors.
- One failed sensor versus both failed sensors.
- Stale and non-finite values.
- Actuator failure and safe-state behavior.
- Recovery rules after temperature falls.

ASIL discussion

Separate nominal over-temperature protection from malfunctioning E/E behavior. Ask what harm the software malfunction can create, how frequently the relevant driving or charging situation occurs and whether the driver can control it. The class cannot be inferred from the word battery alone.

EXERCISE 5 — PARKING-ASSIST WARNING COORDINATOR

Prompt

Combine distance updates from four sensors and emit the nearest valid obstacle band. Inputs expire after a timeout. Invalid sensors are excluded, but the component shall report degraded coverage and shall not announce a safe distance when all sensors are invalid.

Required mocks

- Four sensor ports or one indexed sensor interface.
- Clock.
- Warning-output port.
- Diagnostic sink.

Important tests

- Select nearest valid obstacle.
- Exact band boundaries.
- One invalid sensor with remaining coverage.
- All sensors invalid.
- Stale data.
- Out-of-order timestamps.
- Duplicate samples.
- Warning changes only when the observable band changes.
- Recovery of one sensor after degradation.

ASIL discussion

The ASIL depends on whether this is advisory parking assistance or an input to automatic vehicle motion. Ask who retains control, the maximum speed and the defined safe reaction. The same sensor logic can be QM in one item and safety-related in another.

EXERCISE 6 — CABIN AMBIENT-LIGHT CONTROLLER AS A QM CONTRAST

Prompt

Implement a controller that selects a requested cabin-light color, falls back to a default for unsupported values and stores the last accepted preference. Use mocks for the light driver and persistence.

Required mocks

- Light-driver port.
- Preference store.
- Diagnostic or logging sink if required by the specification.

Important tests

- Supported color.
- Unsupported enum or malformed value.
- Driver rejection.
- Persistence failure.
- Repeated selection of the active color.
- Startup with no stored preference.

ASIL discussion

Under the stated assumptions, failure to apply a decorative color has no identified safety-relevant harm, so this is a QM exercise. The coding and testing discipline still applies, but the absence of an ASIL does not mean the feature has no quality requirements.

COMMON INTERVIEW TRAPS

- Starting implementation before agreeing on the safe state.
- Guessing units or threshold inclusivity.
- Calling every automotive component ASIL D.
- Saying that unit tests prove ISO 26262 compliance.
- Treating line coverage as requirements coverage.
- Testing only successful behavior.
- Mocking private methods and implementation order.
- Forgetting NaN, infinity, stale timestamps and repeated events.
- Using sleep in tests instead of an injected clock.
- Adding dynamic allocation, exceptions or threads without asking whether they are allowed.
- Hiding an assumption inside code instead of stating it.
- Overengineering the design until no working vertical slice remains.

SELF-REVIEW CHECKLIST

- Can every production branch be traced to an agreed requirement?
- Does every requirement have at least one test?
- Are positive, negative, boundary and failure cases present?
- Are all safety-relevant dependencies controllable through mocks or fakes?
- Is the safe state explicit?
- Are time and units explicit?
- Are repeated calls and state transitions deterministic?
- Are forbidden side effects verified?
- Are compiler warnings treated as defects?
- Is the implementation smaller than the specification rather than broader than it?
- Can I name the integration and target tests that unit tests cannot replace?
- Can I explain the ASIL discussion without claiming direct ISO 26262 project experience?

OFFICIAL SOURCES

- ISO 26262 standards package and the roles of Parts 1–10: https://www.iso.org/publication/PUB200262.html
- ISO 26262-3:2018, concept phase, item definition, HARA and functional safety concept: https://www.iso.org/standard/68385.html
- ISO 26262-6:2018, product development at the software level: https://www.iso.org/standard/68388.html
- ISO 26262-9:2018, ASIL-oriented and safety-oriented analyses: https://www.iso.org/standard/68391.html
- ISO 26262-10:2018, guidelines on ISO 26262: https://www.iso.org/standard/68392.html

Research date: 2026-10-27.
