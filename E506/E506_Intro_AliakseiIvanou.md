SELF INTRO

DOCUMENT INFORMATION

Request ID: E506
Candidate: Alex I.
Target role: Senior C++ Engineer / Hands-on Technical Lead
CV source: E506 Aliaksei Ivanou (13, C++).pdf
Source request: E506_Request_AliakseiIvanou.md
Preparation language: English
Delivery format: Three spoken intro variants followed by a domain-based reference version with a detailed latest-project section
Estimated duration: Approximately 60–75 seconds after a team-lead introduction; 90–105 seconds as a standalone intermediary intro; 3–4 minutes for the client technical discussion; 10–12 minutes for the detailed reference version
Screening calibration: Actual intermediary group screening held on 2026-10-23
Document status: Interview-ready

PURPOSE

This is a calibrated self-introduction package for a Senior C++ Engineer interview. The short variants match the intermediary’s observed preference for concise answers about C++ versus embedded C, testing levels and direct GoogleTest experience. The detailed reference version presents the candidate’s experience through aerospace and embedded systems, telecommunications, industrial sensor processing, library platforms, and oil-and-gas software, then explains the latest satellite project in detail.

TARGET POSITIONING

Alex is a C/C++ software engineer with more than thirteen years of commercial experience and a strong focus on embedded systems, real-time behavior, hardware-software integration, and maintenance of established production codebases. C++ is his core engineering expertise. His product background includes onboard satellite communication software, UAV sensor-processing and 3D-reconstruction systems, embedded SIP desk phones and conferencing devices, long-lived library transaction platforms, and industrial telemetry systems. His most relevant strengths for this role are recent modern C++ work, a requirements-to-tests workflow in which specification-driven development is followed by test-driven development, GoogleTest and GoogleMock, GCOV and LCOV coverage analysis, Linux and RTOS development, cross-layer debugging, and disciplined work with code review and target hardware.

OBSERVED INTERMEDIARY SCREENING PRIORITIES

- The team lead may introduce the candidate first. In that case, the candidate should add evidence rather than repeat the full career summary.
- The intermediary wants a pragmatic first answer, not a long technical presentation.
- The three highest-priority topics are whether the candidate leans toward C++ or embedded C, which testing levels and frameworks the candidate has used, and whether the GoogleTest experience is direct and hands-on.
- The C++ versus embedded C question is also likely to appear in the final client interview.
- A strong first response takes 45–90 seconds, names one relevant project and one testing example, and then stops for follow-up questions.

INTRO OPTION 1 — 60–75 SECONDS AFTER A TEAM-LEAD INTRODUCTION

Thank you. My name is Alex. I am a software engineer with more than thirteen years of commercial experience. C++ is my primary language; I also use C where the platform, ABI or low-level constraints require it.

My current project is onboard communication software for an Earth-observation satellite. I develop C and C++ components under VxWorks for telecommand and telemetry processing, CAN communication, RTOS tasks and message queues.

Testing is a substantial part of my hands-on work. First, I use specification-driven development to refine a requirement into a technical specification and acceptance criteria. Then I use test-driven development: I write a GoogleTest or GoogleMock test that initially fails because the behavior is not implemented, implement the required behavior, and refactor while keeping all tests passing. GCOV, LCOV and target-bench tests complete the verification. The project also uses European space-software standards, MISRA C++ rules and V-model traceability from requirements to unit, integration and target-bench evidence.

INTRO OPTION 2 — 90–105 SECOND STANDALONE INTERMEDIARY INTRO

Hello, my name is Alex. I am a software engineer with more than thirteen years of commercial experience. My focus is C and C++ for embedded, real-time and hardware-integrated systems. C++ is my primary language and the main focus of my recent work. I also use the C language when the target platform, ABI or an established low-level codebase calls for it.

My most relevant project is my current one. I work on onboard communication software for a satellite. It runs on VxWorks. In practical terms, I implement telecommand and telemetry processing in C and C++. My work also includes CAN communication with payload controllers, RTOS tasks and message-queue interaction. As for our development process, we follow European standards for space software and a project-approved MISRA C++ ruleset. We also use a V-model with requirements traceability.

Testing is always an important part of my work. On the current project, I use GoogleTest and GoogleMock as part of our SDD and TDD workflow. GCOV and LCOV help us identify gaps in line and branch coverage.

Before this project, I also worked with C++17 on embedded Linux. On another project, I shared ownership of a large, mature C backend for a long-running library management platform. My work there included feature development, native debugging with GDB and core dumps, and legacy-code refactoring.

INTRO OPTION 3 — 3–4 MINUTE CLIENT TECHNICAL INTRO

Hello, my name is Alex. I am a C and C++ software engineer with more than thirteen years of commercial experience. My core expertise is hands-on C++ development for embedded, real-time and hardware-integrated systems. I use C where a platform, ABI or mature low-level codebase requires it, but my recent experience and my preference for new application-level logic lean toward C++ because it gives stronger type safety, resource ownership, encapsulation and testability.

The most relevant example is my current work on onboard communication software for an Earth-observation satellite. The system runs under VxWorks on a fault-tolerant LEON3FT SPARC V8 target. I implement C and C++ components for mission-defined telecommand and telemetry processing, CAN communication with payload controllers, RTOS tasks and bounded message queues. The difficult part is that correctness depends on packet logic, message ownership, queue capacity, task scheduling, timeouts and actual bus traffic together.

Verification is part of my implementation work rather than a separate final phase. For bounded behavior, I first apply specification-driven development. It defines what must be built: I refine the requirement into inputs, outputs, preconditions, state transitions, timing assumptions, error behavior and measurable acceptance criteria. I then apply test-driven development. I encode the specification as a GoogleTest or GoogleMock test that initially fails because the behavior is not implemented, implement the minimum behavior needed to make it pass, and refactor while keeping all tests passing. Unit tests cover parsing, validation, state, boundary values and failure paths with RTOS, time, CAN and payload dependencies mocked. Component and integration tests cover real interfaces, serialization, queue behavior, retries, timeouts and response correlation. GCOV and LCOV provide line and branch coverage, while IBM DOORS and Jira maintain the link from requirements to implementation and evidence. Hardware-bench tests then cover scheduler timing, bus load and target-specific behavior that unit tests cannot prove.

The project follows the European space-software engineering standard ECSS-E-ST-40C, the packet-service standard ECSS-E-ST-70-41C, commonly called PUS, and a project-approved MISRA C++ ruleset. The workflow follows V-model logic rather than treating testing as a final phase: system requirements are decomposed into software requirements and component contracts, while unit, component, integration and target tests verify those levels in reverse order. IBM DOORS and Jira preserve bidirectional traceability between each requirement, its implementation, the corresponding test and the resulting evidence.

I also have experience with established codebases. On an embedded SIP desk-phone platform, I worked with C++17, Qt, Linphone SDK, Yocto Linux and physical ARM64 devices, including asynchronous state, failover and difficult cross-layer defects. Earlier, I shared responsibility for a mature C transaction engine and investigated problems across C, Java, Scala, databases and Linux services.

My positioning for this role is a hands-on senior engineer who can understand an existing C++ system, connect requirements to tests, improve coverage, review changes and coordinate technical risks while continuing to write and verify code. The strongest overlap is modern C++, direct GoogleTest experience, distributed real-time behavior, formal verification discipline and maintenance of production code.

DETAILED DOMAIN-BASED REFERENCE INTRO

Hello, my name is Alex.

I am a software engineer with more than thirteen years of commercial experience. My main specialization is C and C++ development for embedded, real-time, and hardware-integrated systems. I have worked with Linux, VxWorks, and FreeRTOS environments, and my recent work has combined modern C++, automated testing, coverage analysis, requirements traceability, static analysis, and validation on target hardware.

The easiest way to describe my background is through the domains in which I have worked.

The first domain is aerospace and sensor-based systems. Since December 2024, I have worked as an Embedded Software Engineer on Onboard Communication Software for an Earth Observation Satellite. The software runs under VxWorks on a fault-tolerant LEON3FT SPARC V8 target and processes telecommands and telemetry while exchanging data with payload controllers over CAN. Earlier, from March 2019 to June 2022, I worked as a Software Engineer on UAV-Based 3D Reconstruction Software for Large-Scale Objects. I worked with optical and laser sensor data, GNSS PPS synchronization, RTK GNSS and IMU trajectory estimates, PCL, Open3D, and a Software-in-the-Loop environment that reproduced flight paths and sensor behavior. These projects taught me to treat timing, data integrity, physical interfaces, and validation against real or realistically simulated conditions as part of the software design.

The second domain is embedded telecommunications. From June 2022 to December 2024, I worked as a Software Engineer on the SIP Desk Phone Platform for Audio and Video Communication. The stack included C++17, Qt, Linphone SDK, SIP and RTP, Yocto-based embedded Linux, and a Windows provisioning tool. I worked on call and account state, refactored legacy call flows toward clearer domain, presentation, and SDK-integration boundaries, implemented and integrated primary and backup SIP-server behavior, and handled difficult call and video edge cases. I also contributed to provisioning workflows and validated behavior on physical ARM64 devices, where a visible problem could come from the application, the SDK, generated configuration, Linux services, media hardware, or the network.

The third domain is long-lived enterprise software. From September 2016 to March 2019, I worked as a Software Engineer on the Library Management System, a product with more than forty years of history. I was one of three C developers sharing responsibility for the C backend and also made targeted Java and Scala changes when a feature crossed component boundaries. The system used Java data services, PostgreSQL and residual MySQL models, Scala APIs, Linux environments in AWS, Jenkins, and Bitbucket. My work included features, legacy-code refactoring, code reviews, and investigation of native defects with logs, gdb, and core dumps. It gave me strong experience changing mature software without breaking established user workflows or cross-language contracts.

The fourth domain is industrial telemetry and oil-and-gas software. From June 2013 to September 2016, I worked as a Software Engineer on the Corporate System for the Oil and Gas Industry. The product processed operational sensor data in C++, stored and retrieved it through relational databases, and exposed user-facing behavior through JavaScript. My tasks combined feature development, defect correction, simplification of inherited logic, and removal of obsolete components. The important engineering principle was to trace one value through processing, persistence, and presentation so that a local correction did not create inconsistent behavior elsewhere.

I would now like to explain my latest satellite project in more detail.

The product is onboard communication flight software for an Earth remote-sensing satellite. Its responsibility is to receive and process mission-defined telecommands, produce telemetry, and exchange messages with payload controllers over an internal CAN network. Because it runs on a fault-tolerant LEON3FT target under VxWorks, correctness is not limited to the packet-processing logic: task behavior, inter-task communication, bus traffic, timing, and the final target environment all have to work together.

My first area of responsibility was the C and C++ implementation of telecommand and telemetry processing using mission-defined PUS packet formats and handling rules. I also developed communication components for CAN-based exchange with the payload controllers. At the RTOS level, I implemented and tested VxWorks tasks and message-queue communication and evaluated their timing behavior under simulated bus traffic. This was important because a component could be logically correct in isolation and still fail when message arrival rates, task scheduling, and queue behavior interacted.

My second major area was verification. For behavior that could be defined through an observable contract, I used specification-driven development followed by test-driven development. During specification-driven development, a business or system requirement was refined into a technical specification with inputs, outputs, preconditions, state transitions, timing assumptions, error behavior and acceptance criteria. During test-driven development, I turned that contract into GoogleTest and GoogleMock cases before or alongside implementation. The implementation was complete only after the expected behavior passed, negative and boundary cases were covered, review findings were resolved, and the evidence remained linked to the originating requirement. I did not force exploratory or hardware-dependent work into a unit-test-first process when a bench or integration test was the appropriate evidence.

The test boundary depended on the verification level. Unit tests covered packet parsing and formation, validation, state transitions, error mapping, boundary values, malformed input, and timeout decisions, with mocks for time, RTOS services, CAN access, and payload dependencies. Component tests covered serialization, queue contracts, retry and response-correlation behavior across real component interfaces. Integration tests exercised task interaction and end-to-end communication scenarios in the software environment. Flight-bench tests covered scheduler timing, bus traffic, target integration, and hardware-dependent behavior. A line or branch coverage number did not prove requirement coverage: I reviewed uncovered branches, justified defensive or unreachable paths, and checked that every applicable functional requirement had positive, negative, boundary, and failure-path evidence. Electrical bus behavior, payload-controller firmware, VxWorks internals, and final system-safety acceptance were outside my component boundary and required evidence from the responsible hardware, platform, payload, and system-verification teams.

The project flow also mapped naturally to the V-model. On the left side, system needs were decomposed into software requirements, architecture, component contracts, and detailed behavior. On the right side, unit tests verified detailed behavior, component and integration tests verified interfaces and architecture, and the target bench verified system interaction. IBM DOORS and Jira links kept the two sides connected so that a change in a requirement triggered review of the affected implementation, tests, and evidence.

The actual project used ECSS-E-ST-40C to structure the software lifecycle from requirements and design through implementation, verification, change control and documented evidence. ECSS-E-ST-70-41C, commonly called PUS, defined the packet-service model used for mission telecommands and telemetry, including the expected service behavior and packet-handling rules. In practical terms, I had to connect each applicable requirement to design decisions, code, reviews, tests and evidence, and keep that chain current when a requirement or interface changed.

MISRA compliance was part of the normal implementation loop. We used a project-approved subset of MISRA C++ rules and ran Coverity through GitLab CI. I reviewed each new finding, corrected real defects and documented narrowly scoped deviations instead of adding unexplained suppressions. The CI check controlled newly introduced issues, while peer review checked whether the code remained understandable, deterministic and consistent with the approved interfaces. This made coding-standard compliance a repeatable development activity rather than a cleanup exercise before release.

The core team had approximately nine engineers, with payload and qualification specialists joining integration sessions. I worked with the technical lead on design and review, the requirements engineer on traceability, and the BSP, verification, hardware-in-the-loop, and payload engineers on target investigations. We aligned interfaces and acceptance criteria before implementation, used merge requests and peer review for changes, and kept daily coordination focused on decisions, blockers, assumptions, and new evidence. I treated a risk as something that needed an owner and a reduction action: clarify an ambiguous requirement, build a small prototype, add fault injection, request an independent review, reproduce the case under load, or reserve a bench session early. A change was done only when code, tests, traceability, static analysis, review, documentation, and the necessary target evidence were complete.

Finally, I supported flight-bench validation on the target hardware. When a test failed, the investigation had to separate packet-format logic, CAN communication, VxWorks task behavior, queue timing, and target integration. That combination of host-side automated testing, static analysis, coverage data, requirements traceability, coordinated risk reduction, and hardware-bench validation gave us a much stronger verification chain than relying on any one technique alone.

Across these domains, the common theme is hands-on C and C++ engineering in systems where reliability depends on understanding the whole execution path. I am comfortable entering an existing codebase, tracing behavior across software and hardware boundaries, implementing focused corrections, building tests around requirements, reviewing changes, and validating the result in the real operating environment. That is the experience I would bring to this Senior C++ role.

INTERMEDIARY SCREENING ANSWER STYLE

- Give the conclusion first and keep the initial answer to approximately 20–45 seconds.
- If the team lead has already introduced the project and domain, do not repeat them; add personal ownership, one tool and one piece of verification evidence.
- For C++ versus embedded C, state the direction immediately: the profile leans toward C++; then explain where C remains the appropriate tool and give one recent example.
- For testing, separate unit, component or integration, and target or system levels instead of saying only that the project had automated tests.
- For GoogleTest, name the direct use: executable requirement contracts, mocks for external dependencies, negative and boundary cases, and coverage analysis.
- Use one concrete example and stop. Add RTOS, CAN, coverage or safety-process detail only when the interviewer asks for it.
- Distinguish direct experience from adjacent experience, especially for automotive standards and formal Technical Lead ownership.

OBSERVED HIGH-PROBABILITY INTERMEDIARY QUESTIONS AND SHORT ANSWERS

1. Would you position yourself more toward C++ or toward embedded C?

My experience leans clearly toward C++. My current satellite work uses C and C++ under VxWorks, and my previous embedded SIP project used C++17, Qt and embedded Linux. I also have substantial C experience from low-level components and a mature C89 backend, so I am comfortable reading, debugging and changing both languages. For new user-space or application-level logic, I normally prefer C++ because its type system, RAII and abstractions make ownership and testing clearer; I choose C when the platform, ABI or existing low-level codebase requires it. For this role, C++ is my core expertise.

2. What unit and integration testing have you done, and which frameworks did you use?

On my current satellite project, I use GoogleTest and GoogleMock for requirements-based unit and component tests. Unit tests cover parsing, validation, state transitions, boundaries and error paths with time, RTOS, CAN and payload dependencies mocked. Component and integration tests cover real interfaces, queues, serialization, retries, timeouts and response correlation. GCOV and LCOV support line and branch coverage analysis, while target-bench tests cover scheduler timing, bus traffic and hardware integration that cannot be proven by host-side tests.

3. Do you have direct hands-on experience with GoogleTest?

Yes. My normal process combines SDD with TDD. During SDD, I refine a requirement into observable behavior and acceptance criteria. During TDD, I turn that specification into a GoogleTest or GoogleMock test that initially fails because the behavior is not implemented, implement the behavior, and then refactor while keeping all tests passing. Mocks isolate RTOS services, time, CAN access and payload dependencies. I then review GCOV and LCOV results and keep the evidence linked to the originating requirement. GoogleTest is part of my implementation process, not only a framework used by a separate quality-assurance team.

LIKELY CLIENT TECHNICAL FOLLOW-UP QUESTIONS AND SHORT ANSWERS

1. Which project is the most relevant to this opportunity?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. This is my current assignment and the strongest match because I develop C and C++ communication components under VxWorks, including mission-defined telecommand and telemetry processing, CAN communication with payload controllers, RTOS tasks, and message queues. I also own a substantial part of the verification work through GoogleTest, GoogleMock, GCOV, LCOV, requirements traceability, MISRA C++, Coverity, and flight-bench validation.

2. What exactly is your personal responsibility on that project?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. My personal scope covers implementation and testing of the communication components: packet handling, CAN message exchange, VxWorks task behavior, and inter-task communication. I create unit, component, and integration tests, investigate coverage gaps, connect tests to requirements in IBM DOORS and Jira, resolve static-analysis findings, and support target-hardware investigations when CAN or timing behavior differs from the host test environment. The satellite bus, payload firmware, and VxWorks platform itself remain outside my ownership.

3. How large was the team, and what was your exact role?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. The core team was approximately nine engineers, with payload and qualification specialists joining integration sessions. It included a technical lead, embedded C and C++ engineers, a systems and requirements engineer, a BSP and driver engineer, a verification engineer, a hardware-in-the-loop engineer, payload-controller engineers, and a project manager. My role was Embedded Software Engineer. I personally implemented and verified the onboard communication components and worked most closely with the technical lead on design and review, the requirements engineer on traceability, and the target and payload engineers on CAN and bench investigations. We kept communication efficient by agreeing interface ownership and acceptance criteria before implementation, using merge requests for reviewable changes, and using daily coordination to surface blockers, changed assumptions, and integration risks rather than repeating task status.

4. Do you have experience maintaining an existing codebase rather than developing from scratch?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. I work within an established flight-software architecture with existing PUS processing, CAN communication, VxWorks task boundaries, coding rules, and verification requirements. Before correcting or extending a path, I trace the requirement, message ownership, task and queue interaction, error reporting, and existing test evidence; then I make a focused change and repeat host, coverage, static-analysis, and target-bench checks as appropriate. The Library Management System strengthens this point because I also worked as one of three C developers on a decades-old C89 transaction engine and changed it through focused diagnosis, mandatory review, integration testing, and QA.

5. What is your practical GoogleTest and coverage experience?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. For bounded behavior, I first use specification-driven development to refine the requirement into a technical contract and acceptance criteria. I then use test-driven development to turn that contract into GoogleTest or GoogleMock cases before implementing and refactoring the behavior. Unit tests cover parsing, state, validation, error paths and boundaries with RTOS, time, CAN and payload dependencies mocked. Component tests cover queue, serialization, retry, timeout and correlation contracts. Integration and bench tests cover real task interaction, bus load, scheduler timing and target behavior. GCOV and LCOV provide line and branch coverage, but I also check requirement coverage and explain defensive or unreachable paths. Electrical CAN behavior, payload firmware, operating-system internals and system-level safety acceptance remain outside the unit-test boundary.

6. What experience do you have with distributed real-time systems?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. VxWorks tasks exchange data through bounded message queues while the flight computer communicates with payload controllers over CAN. I test timing, queue pressure, timeout and retry behavior, late and duplicate responses, and recovery under simulated bus traffic, then repeat hardware-dependent scenarios on the target bench. The SIP desk-phone project is a secondary example: it involved asynchronous behavior across the device application, liblinphone, SIP infrastructure, Linux services, provisioning, and physical media hardware.

7. Do you have safety-critical or formal-process experience?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. The project uses ECSS-E-ST-40C for the space-software lifecycle and ECSS-E-ST-70-41C PUS for telecommand and telemetry packet services. It also uses project-specific MISRA C++ rules, IBM DOORS and Jira traceability, Coverity, coverage targets, independent verification and target-hardware evidence. The V-model is visible in the flow itself: system needs are refined into software requirements, architecture, component contracts and implementation; unit, component, integration and target tests then verify the corresponding levels. My practical contribution is to connect a requirement to implementation, automated or bench tests, coverage, static-analysis findings and the final observable result. For coding-standard compliance, Coverity runs in GitLab CI, new findings are reviewed, defects are corrected, and any accepted deviation needs a narrow documented reason.

8. How strong is your hands-on Linux experience?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. The flight target itself uses VxWorks, while Linux is part of my host-side development and verification environment for CMake builds, GoogleTest and GoogleMock execution, GCOV and LCOV collection, Coverity and GitLab CI workflows, logs, and communication-component diagnostics. The SIP desk-phone project strengthens the Linux side because there I worked directly with Yocto, BitBake, systemd, CMake, ARM64 deployment to an i.MX target, service configuration, networking, remote diagnostics, and hardware-dependent behavior on physical devices.

9. Can you take the hands-on Technical Lead role?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. I take ownership of implementation and verification within the communication component, decompose requirements into code, test, and evidence work, participate in review, and coordinate with the technical lead, requirements, target, verification, and payload engineers. I manage risk by making assumptions and ownership boundaries visible, ranking issues by safety, integration, and delivery impact, and assigning a concrete reduction action such as a prototype, fault injection, additional reviewer, load test, early bench session, or rollback path. Daily coordination is used to escalate changed assumptions and blockers early. The Library Management System adds earlier experience reviewing changes across delivery and customer teams and estimating work that crossed C, Java, Scala, databases, deployment, and QA. My profile is therefore a hands-on senior engineer who can guide technical work while continuing to write and test code; I do not present myself as a management-only lead.

10. Why are you a strong match for this particular request?

Primary relevant project: Onboard Communication Software for an Earth-Observation Satellite. It directly covers recent C and C++, GoogleTest and GoogleMock, unit and integration testing, GCOV and LCOV, requirements-based verification, code review, distributed real-time behavior, VxWorks, CAN, static analysis, and target-hardware debugging. The SIP desk-phone project adds modern C++17, embedded Linux, Yocto, networking, physical-device testing, and incremental modernization of inherited code. The library project adds deep legacy C maintenance, cross-team review, estimation, and native debugging. Together these projects cover the core request without presenting adjacent standards or formal Technical Lead authority as direct experience.

QUESTIONS TO ASK THE INTERMEDIARY

1. What is the expected start date, and is the duration currently planned as six months or as a flexible three-to-six-month engagement?
2. How is the EU-only condition applied: physical residence, work authorization, or the location of the contracting entity?
3. How many of the four to six engineers are expected to act as hands-on Technical Leads?
4. Which autonomous-driving subsystem, target operating system, compiler, and C++ standard are in scope?
5. How is the V-model applied on the client project, and which requirements, design, verification and traceability artifacts are owned by the hands-on Technical Lead?
6. What tools are used for requirements management, traceability, static analysis, and test execution in addition to GCOV and LCOV?
7. What environment and task format will be used for the sixty-minute live C++ coding exercise?
