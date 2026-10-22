SELF INTRO

DOCUMENT INFORMATION

Request ID: E506
Candidate: Aliaksei Ivanou
Target role: Senior C++ Engineer / Hands-on Technical Lead
CV source: E506 Aliaksei Ivanou (13, C++).pdf
Source request: E506_Request_AliakseiIvanou.md
Preparation language: English
Delivery format: Intermediary screening version followed by a domain-based full version with a detailed latest-project section
Estimated duration: 4–5 minutes for the screening version; 10–12 minutes for the full version
Document status: Interview-ready

PURPOSE

This is a domain-based opening self-introduction for a Senior C++ Engineer interview. It presents the candidate’s experience through aerospace and embedded systems, telecommunications, industrial sensor processing, library platforms, and oil-and-gas software, then explains the latest satellite project in detail.

TARGET POSITIONING

Aliaksei is a C/C++ software engineer with more than thirteen years of commercial experience and a strong focus on embedded systems, real-time behavior, hardware-software integration, and maintenance of established production codebases. C++ is his core engineering expertise. His product background includes onboard satellite communication software, UAV sensor-processing and 3D-reconstruction systems, embedded SIP desk phones and conferencing devices, long-lived library transaction platforms, and industrial telemetry systems. His most relevant strengths for this role are recent modern C++ work, requirements-based verification, GoogleTest and GoogleMock, GCOV and LCOV coverage analysis, Linux and RTOS development, cross-layer debugging, and disciplined work with code review and target hardware.

INTERMEDIARY SCREENING SCRIPT

Hello, my name is Aliaksei Ivanou. I am a software engineer with more than thirteen years of commercial experience, and C++ is my core engineering expertise. I specialize in embedded, real-time, and hardware-integrated systems. Across my career I have worked on satellite and UAV software, embedded SIP and conferencing devices, a long-lived library transaction platform, and industrial telemetry products.

The project that is most relevant to this opportunity is my current assignment, where I work as an Embedded Software Engineer on onboard communication software for an Earth-observation satellite. The software runs under VxWorks on a fault-tolerant LEON3FT SPARC V8 target. It processes mission-defined telecommands and telemetry and exchanges data with payload controllers over an internal CAN network.

My personal scope includes C and C++ telecommand and telemetry components, CAN communication components, VxWorks tasks, and message-queue-based inter-task communication. I test timing behavior under simulated bus traffic because correctness depends not only on packet logic but also on task scheduling, queue behavior, and message arrival patterns.

Verification is a major part of my work. For bounded behavior I use an SDD → TDD loop: requirement, technical specification and acceptance criteria, executable GoogleTest or GoogleMock contracts, implementation, and then coverage, review, traceability, and target evidence. I analyze line and branch coverage with GCOV and LCOV and trace cases to functional requirements in IBM DOORS and Jira.

I keep test boundaries explicit. Unit tests cover parsing, state, validation, errors, and boundaries with external dependencies mocked. Component and integration tests cover queues, serialization, retries, timeouts, and real software interfaces. The hardware bench covers scheduler timing, bus load, and target integration. Electrical CAN behavior, payload firmware, VxWorks internals, and final system-safety acceptance require evidence outside the component’s unit-test boundary.

For compliance, the project uses ECSS practices, MISRA C++ rules, Coverity in GitLab CI, traceability, and target validation. Its requirements-to-design and matching unit-to-system verification flow follows V-model reasoning, although I do not claim direct ISO 26262, ISO 13849, IEC 61508, or ASPICE delivery. Under ISO 26262, ASIL must come from the item definition and HARA: a diagnostic-only function may be QM, while an erroneous steering or braking command in an S3, E4, C3 scenario can lead to an ASIL D safety goal.

I also have strong experience maintaining large existing codebases rather than working only on greenfield development. On an embedded SIP desk-phone platform, I worked across C++17, Qt, Linphone SDK, Yocto Linux, and physical ARM64 devices, including asynchronous state, failover, provisioning, and difficult integration defects. On a long-lived library platform, I shared responsibility for a mature C backend and diagnosed issues across C, Java, Scala, databases, and Linux services.

My strongest positioning is as a hands-on senior engineer. I agree requirements and ownership boundaries early, split work into code, test, and evidence tasks, and surface assumptions, blockers, and interface risks in daily coordination. I reduce high-impact risks through a focused prototype or fault-injection test, a second reviewer, staged bench validation, and an explicit rollback or containment path. I can guide this work while remaining directly involved in C++ development and verification. The strongest overlap with this opportunity is modern C++, GoogleTest, requirements-based testing, coverage analysis, distributed real-time behavior, established-code maintenance, and disciplined verification.

INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou.

I am a software engineer with more than thirteen years of commercial experience. My main specialization is C and C++ development for embedded, real-time, and hardware-integrated systems. I have worked with Linux, VxWorks, and FreeRTOS environments, and my recent work has combined modern C++, automated testing, coverage analysis, requirements traceability, static analysis, and validation on target hardware.

The easiest way to describe my background is through the domains in which I have worked.

The first domain is aerospace and sensor-based systems. Since December 2024, I have worked as an Embedded Software Engineer on Onboard Communication Software for an Earth Observation Satellite. The software runs under VxWorks on a fault-tolerant LEON3FT SPARC V8 target and processes telecommands and telemetry while exchanging data with payload controllers over CAN. Earlier, from March 2019 to June 2022, I worked as a Software Engineer on UAV-Based 3D Reconstruction Software for Large-Scale Objects. I worked with optical and laser sensor data, GNSS PPS synchronization, RTK GNSS and IMU trajectory estimates, PCL, Open3D, and a Software-in-the-Loop environment that reproduced flight paths and sensor behavior. These projects taught me to treat timing, data integrity, physical interfaces, and validation against real or realistically simulated conditions as part of the software design.

The second domain is embedded telecommunications. From June 2022 to December 2024, I worked as a Software Engineer on the SIP Desk Phone Platform for Audio and Video Communication. The stack included C++17, Qt, Linphone SDK, SIP and RTP, Yocto-based embedded Linux, and a Windows provisioning tool. I worked on call and account state, refactored legacy call flows toward clearer domain, presentation, and SDK-integration boundaries, implemented and integrated primary and backup SIP-server behavior, and handled difficult call and video edge cases. I also contributed to provisioning workflows and validated behavior on physical ARM64 devices, where a visible problem could come from the application, the SDK, generated configuration, Linux services, media hardware, or the network.

The third domain is long-lived enterprise software. From September 2016 to March 2019, I worked as a Software Engineer on the Library Management System, a product with more than forty years of history. I was one of three C developers sharing responsibility for the C backend and also made targeted Java and Scala changes when a feature crossed component boundaries. The system used Java data services, PostgreSQL and residual MySQL models, Scala APIs, Linux environments in AWS, Jenkins, and Bitbucket. My work included features, legacy-code refactoring, code reviews, and investigation of native defects with logs, gdb, and core dumps. It gave me strong experience changing mature software without breaking established user workflows or cross-language contracts.

The fourth domain is industrial telemetry and oil-and-gas software. From June 2013 to September 2016, I worked as a Software Engineer on the Corporate System for the Oil and Gas Industry. The product processed operational sensor data in C++, stored and retrieved it through relational databases, and exposed user-facing behavior through JavaScript. My tasks combined feature development, defect correction, simplification of inherited logic, and removal of obsolete components. The important engineering principle was to trace one value through processing, persistence, and presentation so that a local correction did not create inconsistent behavior elsewhere.

I would now like to explain my latest satellite project in more detail.

The product is onboard communication flight software for an Earth remote-sensing satellite. Its responsibility is to receive and process mission-defined telecommands, produce telemetry, and exchange messages with payload controllers over an internal CAN network. Because it runs on a fault-tolerant LEON3FT target under VxWorks, correctness is not limited to the packet-processing logic: task behavior, inter-task communication, bus traffic, timing, and the final target environment all have to work together.

My first area of responsibility was the C and C++ implementation of telecommand and telemetry processing using mission-defined PUS packet formats and handling rules. I also developed communication components for CAN-based exchange with the payload controllers. At the RTOS level, I implemented and tested VxWorks tasks and message-queue communication and evaluated their timing behavior under simulated bus traffic. This was important because a component could be logically correct in isolation and still fail when message arrival rates, task scheduling, and queue behavior interacted.

My second major area was verification. I used specification-driven development leading into test-driven development, or an SDD → TDD cycle, for behavior that could be defined through an observable contract. A business or system requirement was refined into a technical specification with inputs, outputs, preconditions, state transitions, timing assumptions, error behavior, and acceptance criteria. Before or alongside implementation, I turned that contract into GoogleTest and GoogleMock cases. The implementation was complete only after the expected behavior passed, negative and boundary cases were covered, review findings were resolved, and the evidence remained linked to the originating requirement. This approach does not force every exploratory or hardware-dependent task into a unit-test-first shape.

The test boundary depended on the verification level. Unit tests covered packet parsing and formation, validation, state transitions, error mapping, boundary values, malformed input, and timeout decisions, with mocks for time, RTOS services, CAN access, and payload dependencies. Component tests covered serialization, queue contracts, retry and response-correlation behavior across real component interfaces. Integration tests exercised task interaction and end-to-end communication scenarios in the software environment. Flight-bench tests covered scheduler timing, bus traffic, target integration, and hardware-dependent behavior. A line or branch coverage number did not prove requirement coverage: I reviewed uncovered branches, justified defensive or unreachable paths, and checked that every applicable functional requirement had positive, negative, boundary, and failure-path evidence. Electrical bus behavior, payload-controller firmware, VxWorks internals, and final system-safety acceptance were outside my component boundary and required evidence from the responsible hardware, platform, payload, and system-verification teams.

The project flow also mapped naturally to the V-model. On the left side, system needs were decomposed into software requirements, architecture, component contracts, and detailed behavior. On the right side, unit tests verified detailed behavior, component and integration tests verified interfaces and architecture, and the target bench verified system interaction. IBM DOORS and Jira links kept the two sides connected so that a change in a requirement triggered review of the affected implementation, tests, and evidence.

The actual project followed ECSS-E-ST-40C and ECSS-E-ST-70-41C PUS practices rather than automotive standards. I therefore do not claim direct project delivery under ISO 26262, ISO 13849, IEC 61508, or ASPICE. I do understand how the engineering discipline transfers. In ISO 26262, the ASIL belongs to a safety goal established through the item definition and hazard analysis using severity, exposure, and controllability; it should not be guessed from a source file or job title. A diagnostic or communication feature that cannot influence vehicle safety may be QM. A function capable of producing an erroneous steering or braking command in an S3, E4, C3 scenario can lead to an ASIL D safety goal. That higher integrity level drives stronger bidirectional traceability, review independence, unit and integration verification, structural-coverage evidence, controlled tool use, configuration management, and documented handling of deviations.

MISRA compliance was part of the normal implementation loop. We used a project-approved subset of MISRA C++ rules, ran Coverity through GitLab CI, reviewed each new finding, corrected real defects, and documented narrowly scoped deviations instead of adding unexplained suppressions. The same control model can be implemented with clang-tidy or SonarQube in another toolchain: select and version the ruleset, run fast checks locally, make the agreed severity a CI quality gate, review the delta rather than hiding legacy debt, and record the reason, owner, and scope of any accepted deviation. Coverity was the analyzer used on this project; I would not present clang-tidy or SonarQube as project tools that were not there.

The core team had approximately nine engineers, with payload and qualification specialists joining integration sessions. I worked with the technical lead on design and review, the requirements engineer on traceability, and the BSP, verification, hardware-in-the-loop, and payload engineers on target investigations. We aligned interfaces and acceptance criteria before implementation, used merge requests and peer review for changes, and kept daily coordination focused on decisions, blockers, assumptions, and new evidence. I treated a risk as something that needed an owner and a reduction action: clarify an ambiguous requirement, build a small prototype, add fault injection, request an independent review, reproduce the case under load, or reserve a bench session early. A change was done only when code, tests, traceability, static analysis, review, documentation, and the necessary target evidence were complete.

Finally, I supported flight-bench validation on the target hardware. When a test failed, the investigation had to separate packet-format logic, CAN communication, VxWorks task behavior, queue timing, and target integration. That combination of host-side automated testing, static analysis, coverage data, requirements traceability, coordinated risk reduction, and hardware-bench validation gave us a much stronger verification chain than relying on any one technique alone.

Across these domains, the common theme is hands-on C and C++ engineering in systems where reliability depends on understanding the whole execution path. I am comfortable entering an existing codebase, tracing behavior across software and hardware boundaries, implementing focused corrections, building tests around requirements, reviewing changes, and validating the result in the real operating environment. That is the experience I would bring to this Senior C++ role.

INTERMEDIARY SCREENING ANSWER STYLE

- Start with the one project that has the strongest overlap instead of retelling the entire CV chronologically.
- Give the product context in one or two sentences, then state personal ownership, tools, and verification evidence.
- When asked about a project, include team structure and the exact boundary between personal work and adjacent work.
- Use one concrete example for maintenance, testing, or debugging, then stop and let the interviewer choose the next level of detail.
- Keep the first answer accessible to a delivery or recruitment manager; introduce low-level C++, RTOS, and testing detail only when it supports a specific point.
- Distinguish direct experience from adjacent experience, especially for automotive standards and formal Technical Lead ownership.

LIKELY INTERMEDIARY SCREENING QUESTIONS AND SHORT ANSWERS

1. Which project is the most relevant to this opportunity?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. This is my current assignment and the strongest match because I develop C and C++ communication components under VxWorks, including mission-defined telecommand and telemetry processing, CAN communication with payload controllers, RTOS tasks, and message queues. I also own a substantial part of the verification work through GoogleTest, GoogleMock, GCOV, LCOV, requirements traceability, MISRA C++, Coverity, and flight-bench validation.

2. What exactly is your personal responsibility on that project?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. My personal scope covers implementation and testing of the communication components: packet handling, CAN message exchange, VxWorks task behavior, and inter-task communication. I create unit, component, and integration tests, investigate coverage gaps, connect tests to requirements in IBM DOORS and Jira, resolve static-analysis findings, and support target-hardware investigations when CAN or timing behavior differs from the host test environment. The satellite bus, payload firmware, and VxWorks platform itself remain outside my ownership.

3. How large was the team, and what was your exact role?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. The core team was approximately nine engineers, with payload and qualification specialists joining integration sessions. It included a technical lead, embedded C and C++ engineers, a systems and requirements engineer, a BSP and driver engineer, a verification engineer, a hardware-in-the-loop engineer, payload-controller engineers, and a project manager. My role was Embedded Software Engineer. I personally implemented and verified the onboard communication components and worked most closely with the technical lead on design and review, the requirements engineer on traceability, and the target and payload engineers on CAN and bench investigations. We kept communication efficient by agreeing interface ownership and acceptance criteria before implementation, using merge requests for reviewable changes, and using daily coordination to surface blockers, changed assumptions, and integration risks rather than repeating task status.

4. Do you have experience maintaining an existing codebase rather than developing from scratch?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. I work within an established flight-software architecture with existing PUS processing, CAN communication, VxWorks task boundaries, coding rules, and verification requirements. Before correcting or extending a path, I trace the requirement, message ownership, task and queue interaction, error reporting, and existing test evidence; then I make a focused change and repeat host, coverage, static-analysis, and target-bench checks as appropriate. The Library Management System strengthens this point because I also worked as one of three C developers on a decades-old C89 transaction engine and changed it through focused diagnosis, mandatory review, integration testing, and QA.

5. What is your practical GoogleTest and coverage experience?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. I use an SDD → TDD loop for bounded behavior: requirement, technical contract and acceptance criteria, executable GoogleTest or GoogleMock cases, implementation, then coverage, review, traceability, and target evidence. Unit tests cover parsing, state, validation, error paths, and boundaries with RTOS, time, CAN, and payload dependencies mocked. Component tests cover queue, serialization, retry, timeout, and correlation contracts. Integration and bench tests cover real task interaction, bus load, scheduler timing, and target behavior. GCOV and LCOV provide line and branch coverage, but I also check requirement coverage and explain defensive or unreachable paths. Electrical CAN behavior, payload firmware, operating-system internals, and system-level safety acceptance remain outside the unit-test boundary.

6. What experience do you have with distributed real-time systems?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. VxWorks tasks exchange data through bounded message queues while the flight computer communicates with payload controllers over CAN. I test timing, queue pressure, timeout and retry behavior, late and duplicate responses, and recovery under simulated bus traffic, then repeat hardware-dependent scenarios on the target bench. The SIP desk-phone project is a secondary example: it involved asynchronous behavior across the device application, liblinphone, SIP infrastructure, Linux services, provisioning, and physical media hardware.

7. Do you have safety-critical or formal-process experience?

Relevant project: Onboard Communication Software for an Earth-Observation Satellite. The project uses ECSS-E-ST-40C and ECSS-E-ST-70-41C PUS, project-specific MISRA C++ rules, IBM DOORS and Jira traceability, Coverity, coverage targets, independent verification, and target-hardware evidence. Its requirements-to-design-to-implementation flow and the matching unit-to-integration-to-system verification flow are close to V-model reasoning. My practical contribution is to connect a requirement to implementation, automated or bench tests, coverage, findings, and the final observable result. I do not present this as direct ISO 26262, ISO 13849, IEC 61508, or ASPICE project experience. For ISO 26262, I would derive ASIL from the item definition and HARA rather than invent it for an undisclosed component: a non-safety diagnostic function can be QM, while an erroneous steering or braking command in an S3, E4, C3 scenario can lead to an ASIL D safety goal and therefore much stronger traceability, independence, verification, structural coverage, and change control. For coding-standard compliance, the actual tool was Coverity in CI; the same gated ruleset, finding review, and documented-deviation process can be implemented with clang-tidy or SonarQube, but I would not claim those tools as part of this project.

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
5. Which of ISO 26262, ISO 13849, IEC 61508, ASPICE, and V-model experience are mandatory rather than advantageous?
6. What tools are used for requirements management, traceability, static analysis, and test execution in addition to GCOV and LCOV?
7. What environment and task format will be used for the sixty-minute live C++ coding exercise?
