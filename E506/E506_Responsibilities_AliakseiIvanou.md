RESPONSIBILITIES

DOCUMENT INFORMATION

Request ID: E506
Candidate: Alex I.
Target role: Senior C++ Engineer / Hands-on Technical Lead
CV source: E506 Aliaksei Ivanou (13, C++).pdf
Reality source: Summary/Interview project records, Career Overview and Recruiter Brief
Source request: E506_Request_AliakseiIvanou.md
Preparation language: English
Document status: Interview-ready

PURPOSE

This document reconciles every responsibility in the selected CV with the factual Summary repository. The CV wording remains visible, while every supported scope statement and interview answer uses only defensible real experience. The final section evaluates every responsibility, must-have, nice-to-have and Technical Lead expectation in the E506 request.

EVIDENCE STATUS

CONFIRMED — Summary directly supports the CV responsibility and its stated scope.

PARTIALLY CONFIRMED — Summary supports the underlying work, but the CV broadens the technology, ownership, seniority, project context or outcome.

NOT SUPPORTED — Summary contains no evidence that the candidate performed the stated responsibility.

FACTUAL CORRECTION — Summary supports a related project but establishes a materially different date, role, employment context or other fact. Project-level corrections are stated separately from responsibility status.

CV RESPONSIBILITIES COMPARED WITH REAL EXPERIENCE

PROJECT 1. ONBOARD COMMUNICATION SOFTWARE FOR AN EARTH OBSERVATION SATELLITE

CV period: December 2024 - present
CV role: Embedded Software Engineer
Project reconciliation: FACTUAL CORRECTION — Summary records Innowise employment from December 2024, onboarding and technical preparation through April 2025, an Embedded SIP Desk Phone Platform assignment from May 2025 to August 2026, and time between assignments from September 2026. Summary contains real satellite and UAV optical-imaging work from August 2012 to January 2020, but no onboard communication assignment, VxWorks, LEON3FT, PUS or CAN flight-software ownership.
Summary source: Summary/Interview/Career Overview.md; Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Responsibility 1. PUS telecommand and telemetry processing

Status: NOT SUPPORTED

Original CV wording

Implemented C/C++ telecommand and telemetry processing components using mission-defined PUS packet formats and handling rules.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Project Snapshot; Ownership Boundaries; System Architecture and Integration Boundaries.
- No supporting evidence in Summary for PUS, telecommand or telemetry component implementation.

Supported real scope

The supported satellite work was image-processing algorithm design in MATLAB for optoelectronic payloads, including frame stitching, compression, quantization, resolution assessment and calibration. A separate flight-software group owned onboard implementation.

Difference from the CV wording

The CV replaces image-processing R&D and a MATLAB-to-flight-software handover boundary with direct C/C++ PUS flight-software ownership. ECSS-E-ST-70-41C PUS, packet handling and onboard command processing are not supported.

Interview-ready answer

I have professional satellite-payload experience, but it was image-processing algorithm work rather than PUS telecommand and telemetry software. I designed and verified algorithms mainly in MATLAB and supported their handover to the separate onboard software team.

Detailed explanation

At PELENG I worked in the research department on optical-payload algorithms under onboard computation and downlink constraints. My responsibility covered algorithm design, MATLAB implementation, reference-image validation, calibration and formal documentation. I did not implement the command-and-data-handling flight software or its packet protocols.

Relevant follow-up topics

- MATLAB reference algorithms and the handover boundary to flight software.
- Onboard compression under computation and downlink constraints.
- Why PUS and telecommand ownership must not be claimed.

Responsibility 2. CAN communication with payload controllers

Status: NOT SUPPORTED

Original CV wording

Developed and tested C/C++ communication components for message exchange with payload controllers over the onboard CAN network.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Ownership Boundaries; External Integrations.
- No supporting evidence in Summary for onboard CAN development.

Supported real scope

The real aerospace work integrated image algorithms with optical instruments, detector data, navigation-board information and flight-test workflows. Hardware, onboard electronics and flight-software communication were owned by other groups.

Difference from the CV wording

Summary does not support CAN framing, drivers, payload-controller protocols or C/C++ communication components. Working with instrument and navigation data is adjacent hardware-facing experience, not CAN ownership.

Interview-ready answer

I have worked across software and physical-instrument boundaries, but I have not implemented an onboard CAN communication stack. My direct embedded communication experience is SIP and device integration on an embedded Linux phone.

Detailed explanation

On the aerospace project I consumed detector and navigation data and worked with optics, electronics and test engineers. On the SIP project I integrated a Qt application with a customized Linphone SDK, Linux services and physical ARM64 devices. Neither record establishes CAN development.

Relevant follow-up topics

- Hardware-software fault isolation on physical products.
- SIP and embedded-device integration as the supported communication scope.
- Clear distinction between consuming sensor data and owning a bus protocol.

Responsibility 3. VxWorks tasks and message queues

Status: NOT SUPPORTED

Original CV wording

Implemented and tested VxWorks tasks and inter-task communication using message queues, evaluating timing behavior under simulated bus traffic.

Summary evidence

- Summary/Interview/Career Overview.md — Timeline and Project Assignments.
- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — System Architecture; Qt and Threading Concepts.
- No supporting evidence in Summary for VxWorks.

Supported real scope

The supported concurrency work is C++17 and Qt on embedded Linux: Qt signals and slots, QObject ownership, queued connections, asynchronous Linphone callbacks and device-side state coordination.

Difference from the CV wording

VxWorks, RTOS task creation, RTOS message queues and simulated CAN timing are not present in Summary. Qt asynchronous behavior is relevant but not equivalent to verified VxWorks real-time work.

Interview-ready answer

I have hands-on asynchronous and multithreaded embedded C++ experience on a Qt and Yocto Linux product, but I cannot claim professional VxWorks task or message-queue implementation.

Detailed explanation

The desk-phone application mapped asynchronous registration, call, media and device events into stable Qt models and controllers. I worked with thread affinity, queued signal delivery, object lifetime and event ordering on physical devices. That experience supports concurrency reasoning, while the RTOS-specific claim remains unsupported.

Relevant follow-up topics

- QObject ownership and queued connections.
- Asynchronous SIP state and event ordering.
- Difference between embedded Linux concurrency and hard real-time RTOS scheduling.

Responsibility 4. GoogleTest, GoogleMock, GCOV and LCOV

Status: NOT SUPPORTED

Original CV wording

Developed GoogleTest/GoogleMock unit, component, and integration tests for C/C++ communication components, analyzing line and branch coverage using GCOV/LCOV against project verification targets.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Delivery, Testing and Quality; Autoprovisioning Manager testing.
- Summary/Interview/2022-2024. Integrated Library System.md — Delivery, Testing and Quality.
- No supporting evidence in Summary for professional GoogleTest, GoogleMock, GCOV or LCOV use.

Supported real scope

Summary supports focused Qt Test coverage, approximately seventy MSTest methods in the provisioning-tool repository, scenario-based testing on physical phones, Scala-side integration automation on the library platform and independent QA regression.

Difference from the CV wording

The testing mindset and unit/integration validation are real, but the named GoogleTest, GoogleMock, GCOV and LCOV toolchain and coverage-target ownership are not supported by project evidence.

Interview-ready answer

My project testing experience is with Qt Test, MSTest, integration scenarios and physical-device validation. I understand GoogleTest concepts and can work with the framework, but I would not present the CV's professional GoogleMock and GCOV/LCOV history as verified experience.

Detailed explanation

On the SIP project I added and updated call-session tests, worked with targeted Qt Test suites, and validated cross-layer scenarios on ARM64 phones. The provisioning tool had MSTest coverage for generation, validation, ZIP handling and related logic. The mature C89 library backend had no unit-test harness and relied on integration automation, QA, deployments and review.

Relevant follow-up topics

- Test seams for asynchronous SDK integration.
- Qt Test and MSTest experience.
- How to transfer existing testing practice to GoogleTest without overstating prior use.

Responsibility 5. MISRA C++ and Coverity

Status: NOT SUPPORTED

Original CV wording

Applied project-specific MISRA C++ coding guidelines and resolved Coverity findings reported through the GitLab CI pipeline.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Toolchain and Delivery Process.
- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Cross-Cutting Requirements and formal documentation process.
- No supporting evidence in Summary for MISRA C++ or Coverity findings.

Supported real scope

The supported quality practices are GitLab merge requests and CI, code review, compiler and runtime diagnosis, formal aerospace documentation, and careful validation of high-consequence algorithm behavior.

Difference from the CV wording

MISRA rule application and Coverity finding resolution are not established. GitLab CI usage alone is not evidence of either practice.

Interview-ready answer

I have worked with code review, CI and disciplined validation in embedded and aerospace environments, but I do not have verified professional MISRA C++ or Coverity experience in Summary.

Detailed explanation

My supported work includes reviewable incremental changes, GitLab pipelines, target-device testing and formal algorithm documentation. I can discuss how I would triage static-analysis findings, but I would describe that as engineering reasoning rather than a completed MISRA or Coverity project.

Relevant follow-up topics

- Review and CI practices on the SIP platform.
- Bounds and initialization defects in the C89 library system.
- Honest boundary around safety coding standards.

Responsibility 6. DOORS and Jira traceability

Status: NOT SUPPORTED

Original CV wording

Traced verification test cases to functional requirements in IBM DOORS and Jira across the development lifecycle.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — stage-gate process, formal documentation and Success Criteria.
- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Jira-based delivery and architecture documentation.
- No supporting evidence in Summary for IBM DOORS or bidirectional requirement-to-test traceability.

Supported real scope

The aerospace work used instrument requirements, staged engineering documentation and flight-test validation. Later commercial projects used Jira, tests, reviews and reproducible acceptance scenarios.

Difference from the CV wording

Formal requirements awareness and documentation are supported, but a DOORS traceability matrix connecting requirements, code, tests and evidence is not.

Interview-ready answer

I have worked from formal instrument requirements and maintained engineering documentation and Jira-based delivery evidence, but I cannot claim hands-on IBM DOORS or formal bidirectional traceability.

Detailed explanation

At PELENG, algorithm design proceeded through documented stages and had to satisfy image-quality, computation and verification criteria. On later projects I connected tasks, code review, tests and reproducible scenarios operationally. Those practices are adjacent to traceability but do not establish the requested tool or formal method.

Relevant follow-up topics

- Stage-gate aerospace documentation.
- Jira, tests and review evidence on commercial projects.
- How existing practices would map into a formal traceability process.

Responsibility 7. Flight-bench validation

Status: PARTIALLY CONFIRMED

Original CV wording

Supported flight-bench validation sessions, helping isolate CAN bus and timing issues against target hardware.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Flight Tests; Contributions; Outcomes.

Supported real scope

Summary confirms participation in satellite in-orbit testing and more than thirty UAV test flights as an optical-payload operator, including imaging planning, calibration, payload operation and validation of calculated coordinates against known ground positions.

Difference from the CV wording

Real flight-test participation is supported, but not a communication flight bench, CAN analysis, VxWorks timing or LEON3FT target debugging.

Interview-ready answer

I participated in satellite and UAV flight testing for optical payloads, including more than thirty UAV flights, but my role was payload operation, calibration and image-quality validation rather than CAN or flight-computer timing diagnosis.

Detailed explanation

Flight opportunities were scarce, so I prepared analysis tools and imaging plans before campaigns, operated the optical payload and compared output with known geometry and positions. Problems were traced through sensor alignment, calibration, image processing and operating conditions. This is real hardware and flight validation, with a different technical boundary from the CV claim.

Relevant follow-up topics

- Payload operation during UAV test flights.
- IMU-to-camera calibration and coordinate validation.
- Difference between instrument validation and avionics communication debugging.

PROJECT 2. SIP DESK PHONE PLATFORM FOR AUDIO AND VIDEO COMMUNICATION

CV period: June 2022 - December 2024
CV role: Software Engineer
Project reconciliation: FACTUAL CORRECTION — Summary records this assignment from May 2025 to August 2026 within Innowise employment that began in December 2024. The supported role is C++/Qt engineer working across the application, customized Linphone SDK, Yocto integration and Windows provisioning tooling.
Summary source: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md; Summary/Interview/Career Overview.md

Responsibility 1. MVC and MVVM-style SIP call handling

Status: CONFIRMED

Original CV wording

Refactored SIP call handling toward a cleaner MVC/MVVM-style architecture by separating UI rendering from call state, user actions, media negotiation, and Linphone-SDK integration logic.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Application Architecture; Late-Project Call Architecture Refactor.

Supported real scope

Summary confirms work on Qt MVC/MVVM-style models and controllers and personal implementation of the CallSession, registry, service and Linphone-adapter refactor that separated runtime state and SDK access from presentation.

Difference from the CV wording

No material difference. The accurate phrasing is MVC/MVVM-style separation rather than a claim of a pure textbook framework implementation.

Interview-ready answer

I refactored the embedded Qt call architecture by introducing explicit CallSession state, a session registry, call lifecycle and runtime services, and Linphone-facing adapters. This reduced direct presentation access to mutable SDK objects and made asynchronous call state easier to test and reason about.

Detailed explanation

The inherited CoreManager and CallModel paths combined lifecycle, SDK access and UI-facing behavior. I migrated callers in small reviewable steps, routed commands and notifications through service and session boundaries, removed obsolete paths and updated tests and architecture documentation. The goal was clearer ownership without disrupting a live communications product.

Relevant follow-up topics

- Incremental refactoring of stateful Qt code.
- Session identity and ownership of SDK objects.
- Testability across asynchronous callbacks.

Responsibility 2. Legacy Qt Widgets decomposition

Status: CONFIRMED

Original CV wording

Incrementally decomposed legacy Qt Widgets call-flow code into clearer domain, presentation, and SDK-integration boundaries while preserving existing UI behavior and QObject signal compatibility.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Late-Project Call Architecture Refactor; Qt and Threading Concepts; Representative Call-Architecture Story.

Supported real scope

Summary confirms a progressive migration from legacy CallModel paths to sessions, services, adapters and state snapshots, using Qt signals, slots, QObject ownership and queued connections while preserving working flows.

Difference from the CV wording

No material difference. The work was completed internal architecture work, and compatibility was maintained through incremental migration and updated tests rather than a one-step replacement.

Interview-ready answer

I decomposed the legacy Qt call flow incrementally, preserving existing user behavior while moving ownership into explicit domain and service boundaries. I kept QObject lifetime and signal delivery visible and removed each obsolete path after its consumers had migrated.

Detailed explanation

The main risk was two competing representations of call state during migration. State snapshots and adapters prevented presentation code from repeatedly querying mutable Linphone objects, while small changes and focused tests protected call flows. Architecture documentation recorded the new boundary for other developers.

Relevant follow-up topics

- QObject lifetime and queued signal delivery.
- Compatibility during incremental migration.
- Avoiding dual sources of truth.

Responsibility 3. Video-call and conference UI edge cases

Status: CONFIRMED

Original CV wording

Hardened video-call and conference UI behavior for edge cases such as held calls, second-line calls, remote hangups, stale overlays, and active video stream switching.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Call and Telephony Layer; Video and Conferencing; Key Engineering Challenges.

Supported real scope

Summary confirms active, held, transferred and conference flows, second-line behavior, video upgrade and downgrade, remote requests, media and rendering lifecycle, and prevention of inconsistent UI controls and state.

Difference from the CV wording

No material difference. The exact visual symptom varied, but the stated class of asynchronous call, media and UI lifecycle problems is directly supported.

Interview-ready answer

I worked on call and video controllers that kept the UI aligned with Linphone and media state through hold, second-line, transfer, conference, remote termination and video transitions. I diagnosed signaling and rendering separately because a session could be established while camera or native-window handling still failed.

Detailed explanation

One visible call crossed Linphone callbacks, Qt thread delivery, controllers, hardware controls, video windows and target-image dependencies. I followed stable session identity and lifecycle state, cleaned up terminal paths and verified the result on physical devices with application, SIP and system logs.

Relevant follow-up topics

- Signaling success versus media success.
- Video-window and camera lifecycle.
- State consistency during overlapping call transitions.

Responsibility 4. Linphone failover customization

Status: CONFIRMED

Original CV wording

Contributed to Linphone-SDK (liblinphone) backend customization for SIP failover and backup-server connectivity, improving device reliability.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Primary and Backup SIP Server Behavior; Project Snapshot; Contribution Status.

Supported real scope

Summary explicitly confirms personal implementation of the SDK registration watchdog and primary/backup failover and failback state machine, the application integration, active-proxy diagnostics and an AuthInfo backup-domain change.

Difference from the CV wording

No material difference. Reliability is expressed through repeatable registration and recovery scenarios rather than an invented numerical availability metric.

Interview-ready answer

I implemented the registration watchdog and primary/backup failover and failback logic in the customized Linphone SDK, integrated its APIs into the Qt application and provisioning path, and added backup-domain authentication handling and diagnostics.

Detailed explanation

An initial application-level switching approach duplicated protocol state and was reverted. Moving recovery into the SDK kept registration, retry and active-server state together. Validation covered primary loss, backup registration, recovery, restart, authentication realms, persisted configuration and UI consistency on physical phones.

Relevant follow-up topics

- Why failover belongs in the SDK layer.
- Realm-dependent SIP Digest authentication.
- Failback, persistence and device-side diagnostics.

Responsibility 5. WebRTC conferencing UI flows

Status: CONFIRMED

Original CV wording

Developed WebRTC video-conferencing UI flows: conference creation and join, incoming invite screens, participant roster, status strip, control panel, video tile layout, and audio/video device controls.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Video and Conferencing; Call and Telephony Layer; System Architecture.

Supported real scope

Summary confirms phone-side video and conference UI and controller behavior, WebRTC conference joining and room/client lifecycle, participant models, local and remote rendering, camera selection, media controls and mediasoupclient/libwebrtc integration.

Difference from the CV wording

The exact UI element names are implementation-level descriptions, but the complete phone-side conference-flow scope is supported. Server ownership was limited to an early contribution; the phone-side C++ integration was primary.

Interview-ready answer

I developed the phone-side WebRTC and video-conference flows in C++ and Qt, including session lifecycle, participant presentation, rendering, camera and media controls, and integration with mediasoupclient and libwebrtc on ARM64.

Detailed explanation

The application had to coordinate SIP or conference state with camera availability, native windows, frame conversion and target-image dependencies. I worked mainly on the device side and validated behavior on camera-equipped physical phones. I do not claim ownership of the later conference-server rewrite.

Relevant follow-up topics

- Phone-side WebRTC and mediasoup integration.
- Conference ownership on device versus PBX.
- ARM64 media debugging and rendering lifecycle.

Responsibility 6. Project formats and provisioning workflows

Status: PARTIALLY CONFIRMED

Original CV wording

Unified project file formats across the device ecosystem, and implemented provisioning workflows using SNMP, DHCP, TFTP, and SQLite.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Autoprovisioning Manager; .NET 8 Migration; Project Compatibility Matrix; DHCP and TFTP Provisioning.

Supported real scope

Summary confirms major implementation of the provisioning manager, SNMP discovery and querying, DHCP options 66 and 67, TFTP distribution, SQLite persistence, ZIP and configuration generation, and replacement of fragile UI-tree persistence with an explicit JSON Project model inside the encrypted .cuman container.

Difference from the CV wording

The supported project format was the final .cuman Project/JSON schema. Pre-.NET 8 and intermediate formats remained unsupported, so the work did not unify all project formats across the entire ecosystem.

Interview-ready answer

I implemented major provisioning workflows around SNMP, DHCP, TFTP, SQLite and generated configuration archives. I also replaced fragile control-tree persistence with an explicit Project model and JSON schema, while clearly rejecting unsupported older formats rather than claiming universal compatibility.

Detailed explanation

The project model preserved SIP accounts, backup-server fields, BLF state and device settings. Save, reopen and configuration regeneration formed the semantic round trip. The tool generated common and MAC-specific archives and provided diagnostics for discovery and delivery. Compatibility boundaries remained explicit.

Relevant follow-up topics

- Explicit persistence models versus UI-tree serialization.
- DHCP/TFTP fleet provisioning.
- Schema compatibility and unsupported legacy formats.

Responsibility 7. Yocto and i.MX embedded Linux integration

Status: CONFIRMED

Original CV wording

Collaborated on Yocto/BitBake customization, i.MX embedded Linux target integration, and device-side service configuration for hardware-software integration.

Summary evidence

- Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Yocto and Embedded Linux Platform Integration; Firmware Startup and Runtime Readiness.

Supported real scope

Summary confirms work with the inherited Yocto platform, BitBake recipes and metadata, application and SDK packaging, ARM64 i.MX target integration, systemd services, Wayland/Weston readiness, runtime files and physical-device debugging.

Difference from the CV wording

No material difference. Yocto was an inherited foundation that the candidate adapted and integrated; it was not a greenfield platform selection or sole BSP ownership.

Interview-ready answer

I adapted Yocto and BitBake recipes and image contents for the Qt application, customized SDK, media dependencies and runtime services on an ARM64 i.MX phone, and diagnosed startup and hardware-dependent failures on physical devices.

Detailed explanation

Application success depended on package contents, paths, scripts, systemd ordering, the Weston socket, media devices and model-specific assets. I traced failures across build metadata, installed filesystem state, boot logs and application behavior and validated complete images rather than only desktop binaries.

Relevant follow-up topics

- BitBake recipes and target sysroots.
- systemd and Wayland readiness.
- Full-image validation on physical ARM64 devices.

PROJECT 3. UAV-BASED 3D RECONSTRUCTION SOFTWARE FOR LARGE-SCALE OBJECTS

CV period: March 2019 - June 2022
CV role: Software Engineer
Project reconciliation: FACTUAL CORRECTION — the CV combines two real but separate records. Summary documents MATLAB-based satellite and UAV optical-imaging work at PELENG from August 2012 to January 2020 and a short C++17, Qt, PCL and Open3D industrial 3D-scanning engagement from 23 March to 19 May 2020. It does not document one UAV-based C++ reconstruction platform spanning 2019-2022.
Summary source: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md; Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md; Summary/Interview/Career Overview.md

Responsibility 1. UAV image-processing and acquisition modules

Status: PARTIALLY CONFIRMED

Original CV wording

Developed software modules for digital image processing systems used in Unmanned Aerial Vehicles, forming the data acquisition layer for aerial 3D reconstruction of large structures.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — UAV Processing Modules; Project Snapshot; Contributions.
- Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md — Project Snapshot and Architecture.

Supported real scope

Summary confirms MATLAB modules for UAV optical-system debayering, image format conversion, stabilization and image fusion. It separately confirms C++17/Qt software that reconstructed 3D geometry from several industrial 2D laser profile scanners.

Difference from the CV wording

The two scopes are merged in the CV. Summary does not support a C++ UAV acquisition layer or aerial 3D reconstruction of buildings and industrial facilities.

Interview-ready answer

I developed UAV optical-image processing modules in MATLAB and, in a separate commercial C++ project, built a staged 3D reconstruction pipeline for industrial laser scanners. I would not combine them into one UAV 3D platform.

Detailed explanation

The UAV work covered debayering, stabilization, fusion, conversion, calibration and flight testing. The RIFTEK prototype used C++17, Qt, PCL and Open3D to transform several scanner profiles into one point cloud and surface. Both are relevant to sensing and reconstruction, but their periods, hardware and implementation stacks differ.

Relevant follow-up topics

- MATLAB UAV image-processing modules.
- C++ industrial point-cloud reconstruction.
- Why the two projects must remain separate.

Responsibility 2. PPS-based sensor alignment

Status: PARTIALLY CONFIRMED

Original CV wording

Aligned laser, camera, and navigation data using GNSS PPS-based timing and sensor timestamps.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — IMU and Camera Calibration; UAV Flight Testing.
- Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md — Sensor Pose and Coordinate Transformation.

Supported real scope

Summary confirms IMU-to-camera geometric calibration and frame-centre coordinate calculation on the UAV project, and transformation of multiple laser-scanner outputs from known sensor poses in the industrial 3D project.

Difference from the CV wording

GNSS PPS synchronization, cross-sensor timestamp alignment and one combined laser-camera-navigation pipeline are not supported.

Interview-ready answer

I calibrated the UAV IMU and camera geometry and validated calculated frame-centre coordinates, and separately worked with known laser-scanner poses in a 3D reconstruction pipeline. I have no verified PPS timestamp-synchronization implementation.

Detailed explanation

The UAV calibration corrected the relationship between the inertial/navigation board and the optical axis so image coordinates corresponded to ground positions. The industrial project applied known sensor transforms and diagnosed doubled surfaces caused by pose error. Both are spatial alignment work, not proof of PPS timing ownership.

Relevant follow-up topics

- IMU-to-camera extrinsic calibration.
- Sensor-coordinate transformations.
- Difference between geometric and temporal synchronization.

Responsibility 3. EKF-derived RTK GNSS and IMU trajectory integration

Status: PARTIALLY CONFIRMED

Original CV wording

Integrated EKF-derived RTK GNSS/IMU trajectory estimates and sensor streams into the data ingestion pipeline.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — UAV Architecture; IMU and Navigation Board; Ownership Boundaries.

Supported real scope

Summary confirms use of IMU and navigation-board information, geometric calibration against the camera and frame-centre coordinate computation.

Difference from the CV wording

Summary does not support EKF implementation or integration, RTK GNSS, trajectory estimation, covariance handling or a C++ ingestion pipeline.

Interview-ready answer

I integrated navigation-board and IMU information into optical-payload coordinate calculations and calibrated it against the camera. I would not describe that as EKF or RTK trajectory integration because those details are not verified.

Detailed explanation

The work ensured that the coordinates calculated for the image centre matched known ground positions. My responsibility was the calibration and image-processing side; flight-control estimation and navigation algorithms belonged outside my documented scope.

Relevant follow-up topics

- Navigation-board data in frame georeferencing.
- Calibration against known ground positions.
- Honest boundary around EKF and RTK GNSS.

Responsibility 4. PCL and Open3D point-cloud processing

Status: PARTIALLY CONFIRMED

Original CV wording

Processed and inspected the resulting point clouds with PCL and Open3D, filtering and downsampling large-area scans and visualizing them for review.

Summary evidence

- Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md — Tech Stack; Contributions; Testing and Validation.

Supported real scope

Summary directly confirms C++17, Qt, PCL and Open3D use for filtering, downsampling, registration, normals, surface reconstruction and stage-by-stage visualization of real multi-scanner data.

Difference from the CV wording

The technical work is real, but it belonged to a short industrial metrology prototype using fixed production laser scanners, not an aerial UAV project or large-area scan campaign.

Interview-ready answer

In a separate industrial 3D-scanning project, I used PCL and Open3D to transform, filter, downsample, inspect and reconstruct point clouds from several 2D laser profile scanners. The system was a fixed metrology prototype, not UAV mapping.

Detailed explanation

I split the pipeline into inspectable stages, used known mounting geometry as the primary transform and treated registration as refinement. Validation used fixed recorded datasets, per-sensor isolation, known geometry, cross-library comparison and direct inspection of intermediate clouds.

Relevant follow-up topics

- PCL filtering and voxel downsampling tradeoffs.
- Sensor-pose error and doubled surfaces.
- Measurement correctness versus visual quality.

Responsibility 5. Capture-format conversion tools

Status: PARTIALLY CONFIRMED

Original CV wording

Created conversion tools between the payload's capture formats and the formats used downstream in the reconstruction pipeline.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — UAV Processing Modules.
- Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md — staged pipeline and data handling.

Supported real scope

Summary confirms image-format conversion for the UAV optical system and conversion and staging of industrial scanner data inside the C++ reconstruction prototype.

Difference from the CV wording

It does not establish one payload-capture-to-UAV-3D format toolchain or the specific upstream and downstream formats described by the CV project.

Interview-ready answer

I implemented image-format conversion on the UAV optical project and handled staged scanner-data conversion in a separate C++ reconstruction prototype. I would explain them as two distinct data pipelines.

Detailed explanation

In both projects, conversion made the next algorithmic stage consume a stable representation and allowed intermediate output to be inspected. The verified records do not preserve a unified payload schema, versioned manifest or aerial reconstruction format contract.

Relevant follow-up topics

- UAV image-format conversion.
- Inspectable intermediate representations in 3D processing.
- Data-contract discipline without inventing format names.

Responsibility 6. Software-in-the-Loop with simulated UAV paths

Status: NOT SUPPORTED

Original CV wording

Built a Software-in-the-Loop environment that ran payload software against simulated UAV flight paths, letting the team validate reconstruction pipelines without booking real flights.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Systems Tool Kit and Flight-Test Planning.
- Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md — What I Would Improve Today.
- No supporting evidence in Summary for a SIL environment.

Supported real scope

Summary confirms Systems Tool Kit use for orbit and imaging planning, real UAV flight tests and replay of fixed recorded scanner datasets. Synthetic data is recorded as a future improvement for the industrial 3D project.

Difference from the CV wording

Planning and dataset replay are not a Software-in-the-Loop rig. Simulated UAV flight paths and execution of payload software against them are unsupported.

Interview-ready answer

I used STK for imaging planning and replayed fixed datasets for 3D-pipeline validation, but I have not built the UAV Software-in-the-Loop environment described in the CV.

Detailed explanation

The strongest supported simulation-adjacent work is pre-flight planning and repeatable offline processing. A synthetic dataset with known geometry and poses was explicitly identified as something I would add today, which confirms it should not be presented as completed project work.

Relevant follow-up topics

- STK imaging and orbit planning.
- Recorded-dataset replay.
- Proposed synthetic-data validation versus completed SIL work.

Responsibility 7. Point-cloud sensor emulation

Status: NOT SUPPORTED

Original CV wording

Emulated point-cloud sensors inside the SIL rig, generating synthetic laser returns with realistic noise and drop-outs to exercise the reconstruction stack against edge cases.

Summary evidence

- Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md — What I Would Improve Today.
- No supporting evidence in Summary for sensor emulation or noise and dropout models.

Supported real scope

The industrial 3D work used real scanner data, fixed datasets, per-sensor isolation and known-geometry objects. Synthetic data with known poses is documented as a future improvement.

Difference from the CV wording

No sensor simulator, synthetic laser-return generator, stochastic noise model or dropout injection is verified.

Interview-ready answer

I tested the reconstruction pipeline with real recorded scanner data and known-geometry objects. I have not implemented a point-cloud sensor emulator with synthetic noise and dropouts.

Detailed explanation

The real validation focused on identifying errors from sensor pose, transformation, filtering and reconstruction stages. Today I would add synthetic truth data and explicit noise models, but that is a proposed improvement rather than past delivery.

Relevant follow-up topics

- Fixed-dataset regression.
- Known-geometry validation.
- How a future simulator should separate pose, noise and dropout effects.

Responsibility 8. Flight-control and surveying collaboration

Status: PARTIALLY CONFIRMED

Original CV wording

Paired with the flight control and surveying teams to agree sensor mounting, capture patterns and acceptance criteria for each scan campaign.

Summary evidence

- Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Team; Sensor Alignment; Flight Tests; Imaging Planning.

Supported real scope

Summary confirms collaboration in a multidisciplinary instrument organization, participation in image-sensor alignment, IMU-to-camera calibration, STK imaging planning and more than thirty UAV flights as payload operator.

Difference from the CV wording

It does not identify flight-control or surveying teams, aerial 3D scan campaigns or ownership of their acceptance criteria.

Interview-ready answer

I worked with optics, electronics, mechanics, software and test engineers on sensor alignment, imaging planning and UAV flight tests. I did not own flight-control or surveying acceptance criteria for 3D scan campaigns.

Detailed explanation

My role connected algorithm assumptions with instrument geometry and field evidence. I helped calibrate the optical payload, planned imaging opportunities, operated the payload during flights and validated image and coordinate results. Flight crew and airframe operation remained outside my responsibility.

Relevant follow-up topics

- Multidisciplinary optical-instrument development.
- Flight-test preparation and payload operation.
- Ownership boundary with flight operations.

PROJECT 4. LIBRARY MANAGEMENT SYSTEM

CV period: September 2016 - March 2019
CV role: Software Engineer
Project reconciliation: FACTUAL CORRECTION — Summary records the assignment from March 2022 to April 2024. The candidate entered as a Junior C++ Software Engineer, was promoted to middle grade in May 2022 and continued as C++ Software Engineer after relocating internally to EPAM Systems Poland in August 2022.
Summary source: Summary/Interview/2022-2024. Integrated Library System.md; Summary/Interview/Career Overview.md

Responsibility 1. Main C contributor to the transaction engine

Status: PARTIALLY CONFIRMED

Original CV wording

Served as the main C contributor on the core transaction engine, delivering circulation and cataloguing features the client’s largest sites depended on.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — Project Snapshot; Team, Role and Ownership; Contributions.

Supported real scope

Summary confirms primary work across the shared C89 backend as one of three C developers, including new functionality, defect correction and refactoring across circulation, cataloguing and other library workflows.

Difference from the CV wording

The candidate was not the sole or main C owner, and dependence by the client's largest sites is not documented. Responsibility for the C codebase was shared.

Interview-ready answer

I was one of three C developers sharing responsibility for a mature C89 backend. I implemented features, fixed defects and refactored modules while preserving circulation, cataloguing and cross-language behavior.

Detailed explanation

The C backend was invoked by Scala APIs and used Java data services for PostgreSQL and residual MySQL models. A C change therefore had to remain compatible with APIs, desktop workflows and database services. I worked across modules rather than owning the whole transaction engine alone.

Relevant follow-up topics

- Shared ownership of a large C89 codebase.
- Circulation and cataloguing workflows.
- Scala-to-C and C-to-Java boundaries.

Responsibility 2. Memory and concurrency defects under GDB

Status: PARTIALLY CONFIRMED

Original CV wording

Diagnosed and resolved long-standing defects in the legacy C codebase, tracing memory and concurrency issues under gdb against production-like datasets.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — C Defects; Delivery, Testing and Quality; Representative Stories.

Supported real scope

Summary confirms long-lived C defects involving fixed-size character arrays, invalid or uninitialized memory, multilingual processing and native crashes, diagnosed with logs, SSH, GDB, core dumps and Valgrind where appropriate.

Difference from the CV wording

Memory-defect diagnosis is directly supported, but a retained concurrency-defect case and the specific phrase production-like datasets are not.

Interview-ready answer

I diagnosed native C failures with service logs, GDB and core dumps and fixed bounds, length and initialization problems in fixed-size character-array code. I would not claim a specific concurrency case without supporting evidence.

Detailed explanation

A visible web or desktop symptom could originate in C, another service or runtime state. I followed logs across the request path, then used native tools once the problem reached the C process. Validation checked both crash removal and preservation of complete output across boundary and multilingual cases.

Relevant follow-up topics

- GDB and core-dump workflow.
- Fixed-size buffers and multilingual text.
- Cross-service log correlation before native debugging.

Responsibility 3. Scala API refactoring

Status: PARTIALLY CONFIRMED

Original CV wording

Refactored existing Scala API code to improve maintainability and scalability.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — Scala API and Swagger; Add a Scala API Request Backed by C.

Supported real scope

Summary confirms a targeted Scala API request, request handling, C integration, returned-data mapping and Swagger documentation, plus occasional cross-component Scala work.

Difference from the CV wording

Broad refactoring for scalability and ownership of the Scala API subsystem are not supported. The work was task-specific and reused C domain behavior.

Interview-ready answer

I made a targeted Scala and Swagger change that exposed an API operation backed by existing C processing. I preserved request, response and error semantics without duplicating the domain rules in Scala.

Detailed explanation

The task crossed the Scala-to-C boundary. I implemented the request path and mapping, connected it to the native operation and validated the complete API behavior. Java and Scala remained secondary contribution areas; C was the primary one.

Relevant follow-up topics

- Scala API backed by C logic.
- Swagger contract updates.
- Avoiding duplicated domain behavior.

Responsibility 4. Jenkins and AWS deployment automation

Status: PARTIALLY CONFIRMED

Original CV wording

Automated build and deployment by wiring Jenkins builds into AWS CodeDeploy releases onto EC2, with artifacts versioned in S3, removing manual steps from each release and shortening development cycles.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — Build and Deployment; Tech Stack; Role Boundaries.

Supported real scope

Summary confirms regular use of Jenkins builds on AWS EC2 Linux, automatic nightly and selected on-demand deployments through an internal board, artifacts, separate developer and QA environments and diagnosis on deployed hosts.

Difference from the CV wording

Summary does not support personal Jenkins administration, CodeDeploy wiring, S3 artifact-versioning ownership, removal of manual steps or a measured shorter cycle.

Interview-ready answer

I used the existing Jenkins and AWS Linux delivery pipeline, corrected component build and integration problems and validated nightly or on-demand deployments. I did not design the CodeDeploy and S3 automation described in the CV.

Detailed explanation

My responsibility was to make C and cross-language changes buildable and diagnosable in the shared process. Jenkins, AWS infrastructure and deployment administration belonged to the platform owners. Successful delivery required checking build results, deployed behavior and QA workflows.

Relevant follow-up topics

- Jenkins builds and AWS EC2 development environments.
- Nightly and on-demand deployment workflow.
- Component deployability versus pipeline ownership.

Responsibility 5. Database table and schema changes

Status: NOT SUPPORTED

Original CV wording

Modified database tables to support new feature implementations, improving schema design to align with updated system workflows.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — Database Boundaries; Role Boundaries.
- No supporting evidence in Summary for schema or table modification.

Supported real scope

Summary confirms application-level integration with PostgreSQL and residual MySQL through Java data services, including diagnosis of database-backed workflows and mapping behavior.

Difference from the CV wording

Database migration, administration and schema ownership were outside the candidate's responsibility. A Java desktop table column was a UI feature, not a database-table change.

Interview-ready answer

I worked with database-backed behavior through Java data services and debugged PostgreSQL and MySQL paths, but I cannot claim that I modified the database schema on this project.

Detailed explanation

When a C workflow needed data, it called a Java service that owned database access. I followed requests and responses across that boundary and occasionally changed Java for complete tasks. The MySQL-to-PostgreSQL migration had happened before my assignment.

Relevant follow-up topics

- Java-mediated database access.
- PostgreSQL and residual MySQL workflow diagnosis.
- Difference between data integration and schema ownership.

Responsibility 6. Cross-company code review

Status: CONFIRMED

Original CV wording

Conducted thorough code reviews across both the in-house and the client's teams, holding the line on standards and spreading context on legacy subsystems.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — Development Process; Code Review; Outcomes.

Supported real scope

Summary confirms mandatory cross-company review by EPAM and customer developers, personal review contributions, onboarding support and technical interviews.

Difference from the CV wording

No material difference. Review was a shared process rather than unilateral authority over standards.

Interview-ready answer

I reviewed changes in a mandatory cross-company process involving delivery-team and customer engineers. I focused on C memory safety, error behavior, compatibility and cross-language contracts and also supported onboarding and technical interviews.

Detailed explanation

Every added reviewer had to approve a change. Review evidence included reproduction steps, logs, integration behavior and the affected C, Java or Scala contract. This spread context and reduced reliance on one owner in a long-lived system.

Relevant follow-up topics

- Review of legacy C safety and compatibility.
- Cross-language contract review.
- Onboarding and knowledge distribution.

Responsibility 7. Estimation of C-side tasks

Status: NOT SUPPORTED

Original CV wording

Estimated C-side tasks, keeping milestones realistic for a system carrying four decades of accumulated behavior.

Summary evidence

- Summary/Interview/2022-2024. Integrated Library System.md — Development Process and Team Responsibilities.
- No supporting evidence in Summary for estimation ownership or milestone management.

Supported real scope

Summary confirms participation in two-week sprints, daily stand-ups, grooming, demos, retrospectives and technical sessions, plus independent delivery of C work.

Difference from the CV wording

Planning participation does not establish responsibility for estimating C work or keeping milestones realistic.

Interview-ready answer

I participated in sprint planning and delivered work independently in a mature C system, but Summary does not support a specific claim that I owned C-side estimation or milestones.

Detailed explanation

The defensible story is about discovering cross-language scope early, communicating technical risk and completing changes through review and QA. A formal estimation-ownership claim should not be used.

Relevant follow-up topics

- Sprint planning in a mature product.
- Identifying integration risk before implementation.
- Boundary between technical input and planning ownership.

PROJECT 5. CORPORATE SYSTEM FOR THE OIL AND GAS INDUSTRY

CV period: June 2013 - September 2016
CV role: Software Engineer
Project reconciliation: FACTUAL CORRECTION — Summary records this assignment from October 2021 to January 2022 as the candidate's first EPAM project while employed as a Junior C++ Software Engineer. The supported system was a C++17 industrial data-processing application with JavaScript, MySQL, Microsoft SQL Server and an Azure-hosted runtime, not an embedded field-device platform.
Summary source: Summary/Interview/2021. Oil and Gas Corporate System.md; Summary/Interview/Career Overview.md

Responsibility 1. Real-time sensor acquisition

Status: PARTIALLY CONFIRMED

Original CV wording

Developed a real-time C++ data acquisition module for pressure, flow, and temperature sensors, using periodic sampling and timing-aware processing.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Project Snapshot; Architecture; Data and Failure Boundaries.

Supported real scope

Summary confirms C++17 processing and application workflows for sensor-derived industrial data, including tracing measurements through calculation, persistence and presentation.

Difference from the CV wording

Direct acquisition, periodic sampling, timing guarantees and sensor-side implementation are not supported. The verified scope begins at the corporate application's ingestion and processing boundary.

Interview-ready answer

I developed and corrected C++17 application logic that processed sensor-derived oil-and-gas data and kept it consistent through MySQL and the JavaScript layer. I did not own the real-time sensor acquisition module.

Detailed explanation

The work involved customer-requested features, defect correction and cross-layer data consistency. When a value was wrong, I traced it from application input through C++ logic, storage, reload and user-visible output and fixed the layer that owned the divergence.

Relevant follow-up topics

- Industrial data processing in C++17.
- Data lineage through MySQL and JavaScript.
- Application boundary versus device acquisition.

Responsibility 2. CAN and RS-485 hardware bring-up

Status: NOT SUPPORTED

Original CV wording

Interfaced directly with field hardware over CAN and RS-485, bringing up sensor boards on the bench and tracing signal-level faults together with the instrumentation engineers.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Role Boundaries.
- No supporting evidence in Summary for CAN, RS-485, board bring-up or signal-level diagnosis.

Supported real scope

The project integrated sensor-derived data at the application level. Sensor and acquisition infrastructure were adjacent platform areas outside the candidate's responsibility.

Difference from the CV wording

All hardware-bus, board-bring-up and instrumentation-engineer details are unsupported.

Interview-ready answer

My oil-and-gas role was application-side C++ development and data-flow diagnosis. I did not bring up CAN or RS-485 sensor boards on that project.

Detailed explanation

I could identify when a record arriving at the application boundary was inconsistent and provide reproducible evidence, but field hardware and acquisition systems were owned by other teams. That distinction must remain explicit.

Relevant follow-up topics

- Reproducible evidence at an integration boundary.
- Application-side handling of industrial measurements.
- No direct field-bus ownership.

Responsibility 3. On-device checksums and redundant storage

Status: NOT SUPPORTED

Original CV wording

Implemented on-device protection of critical measurement data, combining checksums with redundant storage so telemetry survived power loss and link outages at remote sites.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Role Boundaries and Persistence.
- No supporting evidence in Summary for on-device storage, checksums or power-loss recovery.

Supported real scope

Summary confirms application-level correctness across C++ processing, MySQL and JavaScript-visible values.

Difference from the CV wording

Device firmware, redundant storage, checksums, remote-site link recovery and telemetry persistence are not supported.

Interview-ready answer

I worked on application and database consistency for sensor-derived data, not on-device checksums or redundant storage.

Detailed explanation

The integrity work I can defend is comparing incoming application data, calculated state, persisted rows and displayed values and preventing an application or mapping defect from producing misleading output. That is distinct from power-loss-safe firmware storage.

Relevant follow-up topics

- Application-level data integrity.
- Database write and reload consistency.
- Firmware-storage boundary.

Responsibility 4. Embedded C++ reliability and error handling

Status: PARTIALLY CONFIRMED

Original CV wording

Developed embedded C++ components following project-specific reliability and error-handling requirements, taking documented failure scenarios into account.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — C++17 Feature Development and Maintenance; Quality Priorities.

Supported real scope

Summary confirms C++17 feature and defect work, focused refactoring, error diagnosis and preservation of application behavior in an established enterprise system.

Difference from the CV wording

The system was not an embedded runtime, and Summary does not establish project-specific reliability requirements or documented device failure scenarios.

Interview-ready answer

I improved reliability and error behavior in an inherited C++17 application, but it was enterprise software running in Azure rather than embedded firmware.

Detailed explanation

I reproduced defects, traced them through processing, persistence and presentation, corrected the owning code and supported independent regression testing. Small reviewable changes were preferred to broad redesign during the short assignment.

Relevant follow-up topics

- Focused correction in inherited C++.
- Cross-layer error diagnosis.
- Enterprise runtime versus embedded firmware.

Responsibility 5. Telemetry ingestion and normalization services

Status: PARTIALLY CONFIRMED

Original CV wording

Engineered the back-end services that ingested and normalized field telemetry, keeping ingestion stable as the number of monitored wells grew.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Architecture; Database-Backed Workflows; Contributions.

Supported real scope

Summary confirms C++ application processing of sensor-derived operational data and consistency through MySQL and user-facing behavior.

Difference from the CV wording

Ownership of backend service architecture, telemetry ingestion scaling and growth in monitored wells is not supported.

Interview-ready answer

I maintained C++ processing and database-backed workflows for sensor-derived operational data. I can explain normalization and data consistency at the application level, but not a measured telemetry-ingestion scaling result.

Detailed explanation

Assigned work crossed parsing, calculation, MySQL storage and JavaScript presentation. The engineering value was keeping one meaning across those representations and producing reproducible defect scenarios for an external QA team.

Relevant follow-up topics

- Normalization and units at the application boundary.
- MySQL-backed data workflows.
- No supported well-count or throughput metric.

Responsibility 6. Internal web frontend

Status: PARTIALLY CONFIRMED

Original CV wording

Built the internal web front end with JavaScript, HTML and jQuery, giving field and office staff a shared view of live readings and equipment status.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — JavaScript Contributions; Role Boundaries.

Supported real scope

Summary confirms JavaScript changes when a feature or defect crossed the native and user-facing layers, with HTML and jQuery in the project stack.

Difference from the CV wording

The candidate did not build or own the entire frontend, and live-reading product scope is broader than the documented occasional JavaScript contribution.

Interview-ready answer

My primary role was C++17, and I made JavaScript changes when a complete feature or defect crossed into the user-facing layer. I did not build the whole web frontend.

Detailed explanation

I followed values from C++ processing into the JavaScript-visible representation, changed both sides when required and validated the full workflow. This prevented a backend correction from leaving inconsistent displayed behavior.

Relevant follow-up topics

- C++ and JavaScript contract.
- Cross-layer feature delivery.
- Primary and secondary technology ownership.

Responsibility 7. Legacy maintenance, defects and performance

Status: PARTIALLY CONFIRMED

Original CV wording

Maintained and enhanced the existing codebase by resolving bugs, optimizing performance, and reducing technical debt.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Volume of Work; Legacy-Code Simplification; Outcomes.

Supported real scope

Summary confirms more than four user-requested features, more than twenty defect fixes, focused C++ refactoring and reduction of maintenance surface during the assignment.

Difference from the CV wording

Defect correction and technical-debt reduction are supported; no retained performance benchmark or specific optimization result is documented.

Interview-ready answer

I maintained an inherited C++17 codebase, delivered more than four features, fixed more than twenty defects and simplified difficult areas. I would not add a performance claim without a concrete measurement.

Detailed explanation

I traced affected workflows, kept changes narrow, removed unnecessary complexity and supported external QA regression. The short assignment rewarded complete, demonstrable changes rather than open-ended rewrites.

Relevant follow-up topics

- Fast onboarding into an unfamiliar C++ system.
- Incremental technical-debt reduction.
- Metrics that are supported and those that are not.

Responsibility 8. Removing outdated legacy components

Status: CONFIRMED

Original CV wording

Removed outdated legacy components, modernizing the system to improve reliability and maintainability.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Legacy-Code Simplification; Representative Safe-Modernization Story.

Supported real scope

Summary confirms tracing dependencies, separating supported behavior from obsolete paths, simplifying active logic and removing components no longer needed, followed by regression validation.

Difference from the CV wording

No material difference. The supported outcome is a smaller maintenance surface and preserved behavior; no numerical reliability improvement is claimed.

Interview-ready answer

I removed obsolete components and paths only after tracing their callers and data flow, moved required behavior into the active path and worked with external QA to verify that established workflows remained intact.

Detailed explanation

Deletion was treated as an architectural change, not cosmetic cleanup. The work was attached to requested features or defects so the surviving behavior had explicit acceptance evidence and the cleanup remained reviewable.

Relevant follow-up topics

- Dependency analysis before deletion.
- Regression protection for legacy cleanup.
- Behavior preservation during modernization.

Responsibility 9. Firmware and protocol coordination

Status: NOT SUPPORTED

Original CV wording

Coordinated with the hardware team on firmware and protocol changes, keeping the device and server sides in step across releases.

Summary evidence

- Summary/Interview/2021. Oil and Gas Corporate System.md — Team, Role and Ownership; Role Boundaries.
- No supporting evidence in Summary for hardware-team or firmware coordination.

Supported real scope

Summary confirms distributed collaboration with five C++ developers, an external QA team in India and US customer representatives around application behavior, defects and validation.

Difference from the CV wording

The collaboration was application and QA delivery, not firmware, device-protocol or hardware-release coordination.

Interview-ready answer

I coordinated C++ and JavaScript changes and reproducible validation across development, external QA and the customer, but I did not coordinate firmware or hardware protocols on this project.

Detailed explanation

My cross-team work focused on clear reproduction steps, complete input and database state, expected behavior and regression results. Sensor hardware and acquisition infrastructure remained outside my role.

Relevant follow-up topics

- Distributed development and QA handoff.
- Reproducible cross-layer defects.
- Hardware and firmware ownership boundary.

REAL EXPERIENCE MISSING OR UNDERSTATED IN THE CV

Item 1. Embedded SIP product ownership across application, SDK, firmware image and provisioning

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Project Snapshot; Contributions; Outcomes
Related CV project: SIP Desk Phone Platform for Audio and Video Communication

Interview use

Lead with the personally implemented Linphone registration watchdog and failover and failback state machine, the CallSession and CallService refactor, major Autoprovisioning Manager implementation and cross-layer diagnosis on physical ARM64 phones. These are stronger and more defensible than broad platform-ownership language.

Item 2. Hands-on M1 and People Lead responsibility

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — M1 / People Lead Responsibilities; Summary/Interview/Career Overview.md — Timeline
Related CV project: No direct project responsibility; concurrent internal role from October 2025

Interview use

Present the role as hands-on technical guidance and people development for a separate internal group that grew from four to six engineers, while approximately eighty percent of time remained individual-contributor work. Do not turn it into ownership of the customer project's architecture, work distribution or delivery.

Item 3. Real aerospace algorithm and flight-test work

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Contributions; Flight Tests; Outcomes
Related CV projects: Onboard Communication Software and UAV-Based 3D Reconstruction, but with materially different scope

Interview use

Use the supported aerospace story: MATLAB image-processing algorithms for flown optical payloads, design under onboard computation and downlink constraints, calibration, formal documentation, satellite in-orbit testing and more than thirty UAV flights. Keep it separate from unsupported VxWorks, PUS, CAN, EKF and SIL claims.

Item 4. Long-lived C89 product and cross-language diagnosis

Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md — Architecture; Contributions; Delivery and Testing
Related CV project: Library Management System

Interview use

Emphasize shared responsibility as one of three C developers, native memory diagnosis, mandatory cross-company review and end-to-end debugging across Scala, C, Java and PostgreSQL or MySQL. This supports inherited-code and distributed-system questions without claiming primary ownership.

REQUEST COVERAGE

COVERED — reconciled evidence directly supports the requested item.

PARTIALLY COVERED — evidence supports relevant adjacent or narrower experience, but not the complete requested scope.

NOT COVERED — Summary contains no defensible evidence for the requested item.

Request item 1. Review existing C++ code and identify corrections or improvements based on test results and code-review findings

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: SIP project, Responsibilities 1-7; Oil and Gas project, Responsibilities 7-8
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Development Workflow, Testing and Debugging; Summary/Interview/2021. Oil and Gas Corporate System.md — Development Process

Coverage explanation

Summary directly supports review and correction of inherited C++17 and Qt code, reproduction of failures, focused refactoring, tests, merge-request review and on-device validation.

Interview-ready response

I routinely start by reproducing the behavior, tracing ownership and existing evidence, then propose a focused correction and validate the complete affected path. I used this approach in the SIP application and SDK and in the inherited oil-and-gas C++ system.

Request item 2. Implement safe, maintainable corrections in an existing C++ codebase

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: SIP project, Responsibilities 1-4 and 7; Oil and Gas project, Responsibilities 7-8
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Call Architecture Refactor; Summary/Interview/2021. Oil and Gas Corporate System.md — Legacy-Code Simplification

Coverage explanation

The CallSession and service migration, Linphone failover work and removal of obsolete oil-and-gas paths show controlled correction inside established systems.

Interview-ready response

I make incremental, reviewable changes, keep ownership explicit, remove the old path after migration and validate adjacent behavior. That approach allowed me to modernize call-state code and legacy industrial C++ without a risky rewrite.

Request item 3. Write unit and integration tests with GoogleTest

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: Satellite project, Responsibility 4, not supported; SIP project testing is the adjacent real experience
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Testing and Quality; Autoprovisioning Manager tests

Coverage explanation

Unit, integration and scenario testing are supported through Qt Test, MSTest, cross-component scenarios and physical-device validation. Professional GoogleTest use is not supported.

Interview-ready response

My production testing experience is with Qt Test, MSTest and integration scenarios on physical embedded devices. I can transfer those fixture, isolation and boundary-testing practices to GoogleTest, but I would not claim the CV's professional GoogleTest history as verified.

Request item 4. Derive and implement tests against functional and technical safety requirements

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: Satellite project, Responsibility 6, not supported; real aerospace algorithms and flight validation are adjacent
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Requirements, Success Criteria and Flight Tests

Coverage explanation

Summary supports engineering from instrument requirements and formal validation criteria, but not safety-requirement test derivation in modern C++ or a formal requirement-to-test matrix.

Interview-ready response

I designed aerospace algorithms against instrument, image-quality, computation and downlink requirements and validated them on reference and flight-test data. I have not owned formal functional-safety test derivation for an automotive C++ system.

Request item 5. Improve and analyze test coverage using GCOV and LCOV

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Satellite project, Responsibility 4, not supported
Summary evidence: No supporting evidence in Summary for professional GCOV or LCOV use

Coverage explanation

Summary contains testing and regression evidence but no line or branch coverage work with GCOV or LCOV.

Interview-ready response

I understand how line and branch reports guide missing tests, but I do not have verified professional GCOV or LCOV experience to present for this role.

Request item 6. Maintain bidirectional traceability between requirements, implementation, tests and verification evidence

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: Satellite project, Responsibility 6, not supported
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — formal stage-gate documentation; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Jira, tests and architecture documentation

Coverage explanation

Formal engineering documentation, requirement-driven algorithms, Jira, tests and review evidence are supported, but bidirectional traceability and DOORS are not.

Interview-ready response

I have maintained design documentation and connected tasks, code, tests and acceptance scenarios in practice. I have not operated a formal bidirectional DOORS traceability process.

Request item 7. Create and maintain technical documentation required by the client's engineering process

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Satellite project, Responsibility 6 as adjacent wording; SIP project, Responsibilities 1-2
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — formal design documentation; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — architecture documentation

Coverage explanation

Summary directly supports staged aerospace design documents and updated architecture documentation accompanying the call-system refactor.

Interview-ready response

I have produced formal algorithm and design documentation in aerospace R&D and maintained architecture documentation for a substantial C++ call-state refactor. I treat documentation as part of the implementation and handover boundary.

Request item 8. Conduct formal code reviews and resolve findings consistently

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Library project, Responsibility 6
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md — mandatory cross-company review; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — GitLab merge requests and review

Coverage explanation

Mandatory review across delivery and customer teams and GitLab merge-request review are directly supported.

Interview-ready response

I review for ownership, bounds, error behavior, compatibility and cross-component effects, and I resolve findings with corresponding evidence. On the library platform every added reviewer had to approve the change.

Request item 9. Improve memory-allocation behavior and strengthen compiler-warning and error-handling paths

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: Library project, Responsibility 2; Oil and Gas project, Responsibility 4
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md — fixed-size array and memory defects; Summary/Interview/2021. Oil and Gas Corporate System.md — defect correction

Coverage explanation

Memory bounds, initialization, native crashes and error behavior are supported. Systematic allocation analysis and compiler-warning remediation are not documented.

Interview-ready response

I have corrected C memory and initialization defects with GDB, core dumps and Valgrind and strengthened error paths in inherited C++. I would not claim a dedicated allocation-optimization or compiler-warning program.

Request item 10. Work within established verification, validation and delivery processes

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: SIP, Library and Oil and Gas projects
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Delivery, Testing and Quality; Summary/Interview/2022-2024. Integrated Library System.md — Delivery Process

Coverage explanation

The record includes target-device scenarios, independent QA, mandatory review, Jenkins deployments, sprint processes and formal aerospace validation.

Interview-ready response

I am used to entering an established process and producing the evidence it expects: focused developer checks, integration scenarios, review, deployment and independent QA or hardware validation.

Request item 11. Participate in daily technical coordination with the client and wider engineering team

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Library project, Responsibility 6; all real commercial projects
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md — daily stand-ups and customer technical sessions; Summary/Interview/2021. Oil and Gas Corporate System.md — distributed delivery

Coverage explanation

Daily stand-ups, sprint ceremonies, customer technical sessions and collaboration across US, India, Kazakhstan and European teams are supported.

Interview-ready response

English has been my working language in distributed teams since 2021. I am comfortable with daily coordination, direct technical discussion, concise status reporting and evidence-based handoff across organizations.

Request item 12. Guide implementation decisions, distribute technical work and maintain quality while remaining hands-on

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: No direct CV responsibility; supported by the separate M1 role
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — M1 / People Lead Responsibilities

Coverage explanation

Summary supports hands-on technical guidance, problem decomposition, development planning and support for a four-to-six-person internal group while approximately eighty percent hands-on. It does not support ownership of customer-project architecture, work distribution or delivery quality.

Interview-ready response

From October 2025 I combined roughly eighty percent hands-on engineering with an internal M1 and People Lead role, helping engineers break down problems and develop professionally. I can support a hands-on lead function, but I would not claim prior ownership of a customer's full technical delivery.

Request item 13. Senior or higher engineering grade

Type: MUST-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Overall CV positioning
Summary evidence: Summary/Interview/Recruiter Brief.md — Are you a senior by title; Summary/Interview/Career Overview.md — Timeline

Coverage explanation

The candidate has broad hands-on scope and People Lead responsibilities, but Summary explicitly records the formal grade as middle and says senior was never formally awarded.

Interview-ready response

My formal grade is middle, not Senior. My scope includes more than five years of commercial C++, embedded product ownership and a hands-on People Lead component, so I can demonstrate senior-level behaviors without misrepresenting the title.

Request item 14. At least five to six years of professional software-development experience

Type: MUST-HAVE
Coverage: COVERED
Related CV item: Overall CV timeline
Summary evidence: Summary/Interview/Career Overview.md — Timeline and Career Shape; Summary/Interview/Recruiter Brief.md — Experience Summary

Coverage explanation

Summary records software engineering and R&D from August 2012 and commercial C++ work from 2020, with formal C++ employment from September 2021.

Interview-ready response

I have fourteen years across software engineering and R&D and more than five years of commercial C++ work, including embedded, enterprise and native systems.

Request item 15. At least five years of modern C++ or equivalent depth

Type: MUST-HAVE
Coverage: COVERED
Related CV item: SIP and Oil and Gas projects; industrial 3D project in Summary
Summary evidence: Summary/Interview/Recruiter Brief.md — How many years of C++; Summary/Interview/Career Overview.md — Timeline

Coverage explanation

Summary records more than six years of C++ practice and five years of commercial work across RIFTEK, EPAM and Innowise, including C++17.

Interview-ready response

I have more than six years of C++ practice and five years in commercial C++ work, most recently C++17 and Qt on an embedded Linux product.

Request item 16. Recent projects predominantly involve C++ development

Type: MUST-HAVE
Coverage: COVERED
Related CV item: SIP Desk Phone Platform
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Role and Contributions; Summary/Interview/Career Overview.md — recent assignments

Coverage explanation

The most recent assignment was primarily C++17 and Qt, with additional SDK, Yocto and C# integration. The preceding EPAM work was C89 and C++17.

Interview-ready response

My recent product work has been predominantly native development: C++17 and Qt on the SIP platform, preceded by C89 and C++17 enterprise systems.

Request item 17. Practical GoogleTest experience for unit and integration tests

Type: MUST-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Satellite project, Responsibility 4, not supported
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Qt Test and MSTest; Summary/Interview/Career Overview.md — C++ assessment materials

Coverage explanation

Practical unit and integration testing is supported, but the professional project frameworks were Qt Test and MSTest rather than GoogleTest.

Interview-ready response

I have practical automated-test design in Qt Test and MSTest and integration validation across SDK, device and provisioning boundaries. I can use GoogleTest, but I would describe the framework-specific production experience accurately.

Request item 18. Experience with distributed real-time systems

Type: MUST-HAVE
Coverage: COVERED
Related CV item: SIP project, Responsibilities 1-5
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Scope, Architecture, Call and Telephony Layer

Coverage explanation

The embedded SIP phone is a real-time communications endpoint whose behavior crosses device application, SDK, PBX, media, Linux services and hardware, with asynchronous state and timing-sensitive interaction.

Interview-ready response

My strongest example is the embedded SIP platform, where registration, calls and media were distributed across the Qt application, Linphone SDK, PBX, Linux services and physical hardware. I handled asynchronous state, failover and device-side validation.

Request item 19. Experience with requirements-based testing

Type: MUST-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Unsupported satellite Responsibilities 4 and 6; real aerospace project in Summary
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — requirements, success criteria and flight tests

Coverage explanation

The candidate designed and validated algorithms against instrument and image-quality requirements, but formal requirement-derived software tests and traceability are not documented.

Interview-ready response

I have tested aerospace algorithms against formal instrument constraints and flight-test acceptance behavior. I have not maintained the complete requirement-to-test traceability expected in this automotive role.

Request item 20. Strong code-review experience

Type: MUST-HAVE
Coverage: COVERED
Related CV item: Library project, Responsibility 6
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md — mandatory cross-company review; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — GitLab reviews

Coverage explanation

The record directly supports regular review in mature C/C++ systems across company boundaries.

Interview-ready response

I have reviewed C and C++ changes for memory safety, ownership, error handling, compatibility and cross-component effects in both mandatory customer review and GitLab merge-request workflows.

Request item 21. English B2 or higher with direct client communication

Type: MUST-HAVE
Coverage: COVERED
Related CV item: CV language section
Summary evidence: Summary/Interview/Recruiter Brief.md — Languages

Coverage explanation

Summary records English at B2 and professional use since 2021 across distributed teams in the US, India and Europe.

Interview-ready response

My English is B2 and has been my daily professional working language since 2021 for technical discussion, review, planning and customer-facing collaboration.

Request item 22. Work independently and effectively inside an engineering team

Type: MUST-HAVE
Coverage: COVERED
Related CV item: All supported commercial projects
Summary evidence: Summary/Interview/Career Overview.md — Cross-Cutting Themes; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — Role and Team

Coverage explanation

The candidate independently delivered cross-layer features and defects while collaborating with multidisciplinary and distributed teams.

Interview-ready response

I take a task from investigation through implementation and evidence, while bringing in adjacent owners early when a failure crosses SDK, firmware, database, device or customer boundaries.

Request item 23. Full-time forty-hour availability and daily check-ins

Type: MUST-HAVE
Coverage: PARTIALLY COVERED
Related CV item: No project responsibility
Summary evidence: Summary/Interview/Recruiter Brief.md — Status and Availability

Coverage explanation

Summary confirms a one-month notice period, employment search and extensive daily-stand-up experience. It does not explicitly record acceptance of this exact forty-hour contract and start date.

Interview-ready response

I am seeking a full-time role and can work with daily coordination after my one-month notice period. The exact start date and contract arrangement should be agreed for this engagement.

Request item 24. Physical location inside the European Union

Type: MUST-HAVE
Coverage: NOT COVERED
Related CV item: No project responsibility
Summary evidence: Summary/Interview/Recruiter Brief.md — Status and Availability; Summary/Interview/Career Overview.md — location note

Coverage explanation

The candidate is currently in Minsk, Belarus. He holds a Polish national D visa and plans to return to Warsaw, but is not physically inside the EU at present.

Interview-ready response

I am currently in Minsk and therefore do not meet an immediate EU-location condition. I hold a valid Polish national D visa and can return to Warsaw within one month of an accepted offer.

Request item 25. Readiness for a live C++ and testing exercise

Type: MUST-HAVE
Coverage: PARTIALLY COVERED
Related CV item: General C++ and testing background
Summary evidence: Summary/Interview/Career Overview.md — C++ assessment and live-coding preparation resources; Summary/Interview/Certificates and Continuing Education.md — validated C++ assignment

Coverage explanation

Summary documents structured C++ assessment preparation and a reviewed Catch2 extension assignment, but readiness for the client's exact environment remains an interview commitment rather than past project evidence.

Interview-ready response

I am prepared to write and discuss C++ and tests live. My strongest practical areas are modern C++, ownership, asynchronous state, test design and debugging; I would confirm the compiler and framework before the session.

Request item 26. Professional safety-critical software experience

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Real satellite and UAV optical work, not the unsupported onboard communication project
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — Criticality, Constraints and Validation

Coverage explanation

The candidate designed algorithms for flown satellite instruments under irreversible onboard and mission constraints, but Summary does not assign a formal safety-critical classification or functional-safety lifecycle.

Interview-ready response

I have high-consequence aerospace experience on optical payload algorithms and flight validation, where onboard mistakes could not be patched after launch. I would describe it as safety-oriented aerospace work, not formal functional-safety certification experience.

Request item 27. V-model development

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Real satellite and UAV optical work
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — stage-gate and documentation-heavy engineering process

Coverage explanation

Summary supports staged design, formal documentation, handover and flight validation, but does not explicitly identify the process as a V-model.

Interview-ready response

I worked in a formal stage-gate instrument-development process with requirements, design documentation, implementation, handover and flight validation. I would not label it V-model without the process record doing so.

Request item 28. ISO 26262

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary

Coverage explanation

No automotive functional-safety work under ISO 26262 is recorded.

Interview-ready response

I have no direct ISO 26262 project experience. My adjacent background is formal aerospace algorithm development and high-consequence hardware validation.

Request item 29. ISO 13849

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary

Coverage explanation

No machinery-safety work under ISO 13849 is recorded.

Interview-ready response

I have not applied ISO 13849 professionally.

Request item 30. IEC 61508

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary

Coverage explanation

No IEC 61508 safety lifecycle experience is recorded.

Interview-ready response

I have not worked under IEC 61508.

Request item 31. ASPICE processes

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary

Coverage explanation

No Automotive SPICE process experience is recorded.

Interview-ready response

I have no direct ASPICE project experience.

Request item 32. Automotive or autonomous-driving verification and validation

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary

Coverage explanation

The professional domains are aerospace optical systems, embedded telecommunications, library software and oil-and-gas applications, not automotive or autonomous driving.

Interview-ready response

I have not worked on automotive or autonomous-driving software. The closest transferable experience is aerospace validation, embedded-device testing and distributed real-time communication.

Request item 33. Guide a C++ team while remaining hands-on

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: No direct CV responsibility; separate M1 role
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — M1 / People Lead Responsibilities

Coverage explanation

Summary supports a four-to-six-person internal group, technical guidance and approximately eighty percent hands-on delivery, but not customer-project technical-lead authority over a C++ team.

Interview-ready response

I have a hands-on People Lead role for a small internal engineering group while remaining primarily an individual contributor. I can guide problem decomposition and development, but I would be stepping into broader project-level C++ lead ownership.

Request item 34. Remain actively involved in C++ implementation, testing and code review

Type: TECHNICAL LEAD EXPECTATION
Coverage: COVERED
Related CV item: SIP project and Library project
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — M1 responsibilities and project contributions; Summary/Interview/2022-2024. Integrated Library System.md — review

Coverage explanation

The M1 role retained approximately eighty percent hands-on delivery, and the project records support implementation, testing and review.

Interview-ready response

My leadership style is hands-on. Even with M1 responsibilities, roughly eighty percent of my time remained implementation work, and I continued testing, reviewing and diagnosing product behavior.

Request item 35. Guide technical implementation rather than operate only as a people manager

Type: TECHNICAL LEAD EXPECTATION
Coverage: PARTIALLY COVERED
Related CV item: Separate M1 role and SIP technical contributions
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — M1 responsibilities; Technical Ownership Boundaries

Coverage explanation

The candidate provided technical guidance and made hands-on design contributions, but Summary explicitly says he did not own the customer project's technical direction.

Interview-ready response

I guide engineers through problem decomposition and technical decisions while remaining a hands-on developer. My prior role was not ownership of the full customer architecture, so broader implementation leadership would be an expanded responsibility.

Request item 36. Help interpret requirements and maintain consistent verification practices

Type: TECHNICAL LEAD EXPECTATION
Coverage: PARTIALLY COVERED
Related CV item: Real aerospace documentation and SIP testing
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — requirements and documentation; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — testing and M1 responsibilities

Coverage explanation

Requirement interpretation, technical mentoring and repeatable validation are supported separately, but team-wide ownership of a formal verification practice is not.

Interview-ready response

I can help turn requirements into bounded implementation and observable test scenarios and make evidence consistent across a team. I have not yet owned a formal automotive verification framework.

Request item 37. Coordinate difficult technical decisions and review safety-sensitive changes

Type: TECHNICAL LEAD EXPECTATION
Coverage: PARTIALLY COVERED
Related CV item: SIP failover and real aerospace work
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — failover decisions and technical guidance; Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md — high-consequence algorithms

Coverage explanation

The candidate coordinated difficult cross-layer decisions and worked on high-consequence aerospace algorithms, but did not review automotive safety-sensitive C++ changes as a lead.

Interview-ready response

I have coordinated difficult SDK, application, provisioning and device decisions and have aerospace experience where errors had mission consequences. Formal safety-change review in automotive would be new scope.

Request item 38. Maintain delivery quality while supporting other senior engineers

Type: TECHNICAL LEAD EXPECTATION
Coverage: PARTIALLY COVERED
Related CV item: Separate M1 role
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md — M1 / People Lead Responsibilities

Coverage explanation

Summary supports helping engineers with day-to-day work, growth, assessments and difficult problems while remaining hands-on. It does not support delivery-quality ownership for a team of senior engineers.

Interview-ready response

I have supported engineers and maintained my own delivery quality in a hands-on People Lead role. I would be ready to extend that into shared team quality, but I would not claim that exact prior authority.

FINAL COVERAGE SUMMARY

CV responsibilities reconciled: 38 of 38
Confirmed: 8
Partially confirmed: 17
Not supported: 13
Factual corrections: 0 responsibility-level; 5 project-level corrections
Request items assessed: 38 of 38
Request items covered: 14
Request items partially covered: 17
Request items not covered: 7
