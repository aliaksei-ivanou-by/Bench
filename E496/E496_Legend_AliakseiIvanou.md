PROJECT LEGEND

DOCUMENT INFORMATION

Request ID: E496
Candidate: Aliaksei Ivanou
Target role: GNC Engineer
CV source: E496 Aliaksei Ivanou (7, MATLAB, C++).pdf
Source request: E496_Request_AliakseiIvanou.md
Source profile: E496_Profile_AliakseiIvanou.md
Source analysis: E496_Request_Analysis_AliakseiIvanou.md
Preparation language: English
Document status: Interview-ready; checked against Responsibilities and the completed Request Analysis

PURPOSE

This document contains the detailed project narratives behind the request-specific CV. It is reference material for follow-up questions, not one continuous speech. The narratives emphasize evidence relevant to physical modelling, scientific computing, aerospace systems, measured-data validation, model-to-software boundaries, embedded C++, and research discipline without presenting adjacent experience as professional GNC or control-system work.

HOW TO USE THE LEGEND

Start every project answer with the short summary. Expand only the sections relevant to the interviewer's question. A complete answer should distinguish product context, personal contribution, result, and ownership boundary.

For this request, state the GNC boundary before answering a detailed control question. Use the verified project story as adjacent evidence only after making clear what was not done. Prepared theory or a future learning exercise must never be presented as delivered project experience.

PRIVATE CONSISTENCY NOTES

• The two aerospace entries in the CV are workstreams from one PELENG employment period, August 2012 to January 2020. They are not later projects from 2019 to 2022 and must not be counted twice.
• The SIP desk-phone assignment ended in August 2026. Innowise employment continues, and the candidate has been between customer assignments since September 2026.
• The candidate's PELENG title was Design Engineer and Research Engineer, not Software Engineer, GNC Engineer, or Controls Engineer.
• The candidate owned image-processing algorithms, calibration, reference implementations, and verification. A separate flight-software group owned the code running on onboard hardware.
• UAV image stabilization corrected imagery affected by platform motion; it did not control the vehicle.
• Image fusion and IMU-to-camera calibration do not establish Kalman filtering, navigation-state estimation, or a general sensor-fusion framework.
• Phone-side media integration does not establish active-noise-cancellation or audio-control-loop design.
• The candidate attended Summer Space Schools at Samara State Aerospace University. No relationship with Samara Aerospace is established.

REQUEST-SPECIFIC EVIDENCE ORDER

1. Lead with the UAV optical-system story when asked about sensors, calibration, physical validation, or errors between subsystems.
2. Lead with the satellite compression and MATLAB-to-onboard stories when asked about modelling, constrained algorithms, simulation-to-runtime transfer, or verification.
3. Use the academic foundation for Monte Carlo, physical modelling, spacecraft-control coursework, and research method, while stating that it is academic evidence.
4. Use the embedded SIP project for C++, asynchronous state, embedded Linux, hardware integration, and diagnosis, not for ANC or control theory.
5. Use the library system for production C, disciplined work in a mature system, cross-component diagnosis, and review only when those engineering foundations are relevant.

PROJECT 1. EMBEDDED SIP DESK-PHONE PLATFORM

CV period: May 2025 – till now
Verified period: May 2025 – August 2026 within Innowise employment from December 2024 – present
CV role: Software Engineer
Verified role: C++ Software Engineer, middle grade; hands-on engineer with internal People Lead responsibilities from October 2025
Project status: FACTUAL CORRECTION and NARROWER SCOPE

Short project summary

From May 2025 to August 2026, I worked as a C++/Qt engineer on an embedded SIP desk-phone platform running Yocto Linux on ARM64 hardware. The platform combined a native phone application, a customized Linphone SDK, firmware integration, physical audio and video devices, and Windows provisioning tooling. My strongest contributions were call and account architecture, implementation and integration of primary/backup SIP registration behavior, major work on the provisioning tool, and cross-layer diagnosis on physical devices.

Product and business context

The product was a family of enterprise SIP desk phones supporting registration, calls, contacts, BLF and speed dial, hold and transfer, audio and video conferencing, web management, and centralized provisioning. Two device models shared the same codebase and firmware foundation, with model-specific display and camera behavior.

The engineering problem was not one isolated application. Correct behavior depended on the agreement of Qt UI state, Linphone callbacks and SDK state, SIP server behavior, generated configuration, Yocto image contents, system services, media libraries, and physical peripherals.

System architecture and main components

• C++17 and Qt 5.15 phone application with stateful call, account, settings, and presentation logic.
• Customized Linphone and liblinphone layer for SIP registration, authentication, calls, and project-specific failover behavior.
• SIP and RTP communication plus phone-side WebRTC and mediasoup integration for supported conferencing paths.
• Yocto and BitBake image integration for ARM64 NXP i.MX hardware, services, libraries, assets, and device configuration.
• C# and WinForms Autoprovisioning Manager migrated from .NET Framework 4.8 to .NET 8.
• SNMP discovery, DHCP and TFTP provisioning, SQLite-backed tooling, and generated device configuration.
• Physical-device testing supported by application, SIP, SDK, service, and system logs plus remote debugging.

My role and ownership

I worked mainly in the C++/Qt application and customized Linphone integration, but tasks often crossed into the SDK, Yocto metadata, firmware layout, provisioning tool, services, and target-device runtime. I personally implemented the project-specific registration watchdog and primary/backup failover and failback state machine in customized Linphone, integrated its APIs into the application and provisioning paths, and made a related backup-domain authentication change.

I also substantially developed the Windows Autoprovisioning Manager, including its .NET 8 migration, explicit project-state persistence, configuration generation, discovery, and provisioning workflows. My phone-side media work concerned integration and diagnosis. I did not own upstream Linphone, the complete WebRTC server, audio DSP, jitter-buffer algorithms, or active noise cancellation.

Main contributions

• Implemented the SDK-side registration watchdog and primary/backup failover and failback behavior.
• Integrated active-server and backup-server state into the C++/Qt application, diagnostics, settings, and provisioning paths.
• Refactored call behavior toward explicit sessions, services, adapters, and presentation boundaries while preserving the inherited Qt application.
• Developed and debugged phone-side video, conferencing, and media integration using Qt, Linphone, WebRTC, and mediasoup-related components.
• Migrated the Windows provisioning tool from .NET Framework 4.8 to .NET 8 and replaced hidden UI-tree persistence with explicit project-state models.
• Worked with Yocto recipes, image contents, startup services, runtime paths, peripherals, and model-specific firmware integration.
• Diagnosed defects that appeared only on physical phones or only when several asynchronous layers interacted.

Key engineering challenges

The core difficulty was authoritative state ownership. A visible registration or call state could be affected by asynchronous SDK callbacks, Qt event delivery, server reachability, authentication context, configuration persistence, and UI lifecycle. Duplicating a state machine in the application made the system harder to reason about because the SDK already owned registration lifecycle state.

The other challenge was observability across layers. A desktop build could not reproduce GPIO, audio and camera routing, complete firmware layout, service ordering, Wayland readiness, real SIP behavior, or timing on the ARM64 device. Diagnosis therefore required evidence from the full target rather than assumptions based on one component.

Representative investigation or delivery story

Situation: Primary and backup SIP-server support initially risked being implemented as competing switching logic in the Qt application while registration state actually belonged to the customized Linphone layer.

Task: Create reliable failover and failback behavior while keeping SDK state, application presentation, authentication context, persisted settings, and diagnostics consistent.

Actions: I reverted the application-owned switching direction, placed the registration watchdog and failover state machine in customized Linphone, exposed the necessary backup and active-server APIs, integrated them into the Qt application, aligned provisioning fields, added diagnostics, and handled the related authentication-domain context.

Result: The product had one authoritative owner for registration switching and an application that consumed and displayed that state instead of competing with it.

Testing, validation, and diagnostics

Validation was scenario-based on physical ARM64 phones. It included primary-server loss, backup registration, recovery and failback, authentication variants, device restart, generated configuration, and UI state. Evidence came from application and SDK logs, SIP traces, service logs, Qt remote debugging, target filesystem inspection, and repeated firmware or component deployment. Focused Qt Test coverage supported suitable application logic, while hardware behavior still required real-device scenarios.

Outcome and main lesson

The strongest lesson was that state should live beside the subsystem that owns its lifecycle. A clean UI model cannot compensate for two components making independent decisions about the same external state. This is relevant to safety and control-oriented systems as an architectural principle, but it is not evidence of control-law design.

Relevance to the GNC request

This project supports embedded C++, asynchronous state, hardware-facing diagnosis, interface definition, and integration from application logic down to a physical target. It can support collaboration with an embedded GNC engineer. It does not support claims about embedded C firmware, MuJoCo, control systems, state estimation, system identification, or active noise cancellation.

Scope boundaries

• The assignment ended in August 2026 and must be described in past tense.
• Phone-side media integration is not ownership of audio DSP, jitter-buffer algorithms, or ANC.
• Yocto integration is not complete BSP, kernel, bootloader, or driver ownership.
• The candidate did not own upstream Linphone or the later conferencing-server rewrite.
• Project state machines concerned SIP registration and application behavior, not physical feedback control.

Likely follow-up questions

• Why did registration failover belong in the SDK rather than in the Qt application?
• How did you validate failover and failback on physical devices?
• Which failures existed only in the complete Yocto image?
• What did you own in the media path, and what remained inside Linphone or WebRTC libraries?
• How would the authoritative-state lesson transfer to a simulator and embedded-controller boundary?

PROJECT 2. SIERRA INTEGRATED LIBRARY SYSTEM

CV period: March 2022 – April 2024
Verified period: March 2022 – April 2024
CV role: Software Engineer
Verified role: Primarily C backend developer; Junior C++ Software Engineer until promotion to middle grade in May 2022, then C++ Software Engineer
Project status: CONFIRMED with several responsibility wordings narrowed

Short project summary

From March 2022 to April 2024, I worked primarily as a C developer on a mature integrated library system. I shared responsibility for the C89 backend with two other C engineers, implemented features and fixes, refactored legacy modules, and occasionally changed Java or Scala components when a task crossed language boundaries. The project strengthened my production C, Linux diagnosis, interface tracing, review, and regression-discipline skills.

Product and business context

The product was a long-lived library-management platform supporting circulation, cataloguing, acquisitions, staff workflows, patron and collection data, APIs, and third-party integrations. Its age and installed base made compatibility more important than broad rewrites.

System architecture and main components

• C89 backend services containing established domain behavior.
• Scala API services that invoked C functionality.
• Java data services and desktop application components.
• PostgreSQL as the main database with residual MySQL-backed models.
• Custom protocols between services.
• Linux environments hosted on AWS EC2.
• Bitbucket, Jenkins, nightly and on-demand deployments, Jira, logs, SSH, gdb, core dumps, and Valgrind.

My role and ownership

My primary role was C backend development across the shared codebase. I independently delivered tasks but did not own the whole architecture or lead the full C stream. Java and Scala changes were task-specific and secondary. I participated in mandatory code review, customer technical sessions, sprint work, onboarding support, and technical interviews.

Main contributions

• Implemented C89 features, defect fixes, and targeted refactoring while preserving established behavior.
• Traced requests across Scala APIs, C services, Java data services, and PostgreSQL or MySQL.
• Added task-specific Java and Scala changes where an end-to-end feature crossed component boundaries.
• Diagnosed native failures through logs, SSH, gdb, core dumps, and Valgrind.
• Worked through the established Jenkins, AWS Linux, nightly, and on-demand integration workflow.
• Participated in cross-company review and regression validation with QA and the business analyst.

Key engineering challenges

The product's behavior crossed several processes and runtimes, so the component displaying a symptom was often not the component that owned the defect. The C code also carried decades of assumptions about buffers, text, time, protocols, and customer workflows. A narrow change could still have a wide regression surface.

Representative investigation or delivery story

Situation: User-visible failures could cross a Scala API, C processing, a Java data service, and a database, with no single debugger covering the full path.

Task: Identify the component that owned the incorrect behavior and deliver a compatible fix without rewriting established interfaces.

Actions: I followed the request through service logs, added targeted logging where the path was unclear, reproduced the issue in the integrated Linux environment, and used gdb, core dumps, or Valgrind when the evidence pointed to native C behavior. When the contract itself had to change, I updated the affected C and Java or Scala sides together and validated through the established deployment and QA process.

Result: Features and defect fixes were delivered across component boundaries while retaining the mature product's compatibility model.

Testing, validation, and diagnostics

The C code did not have a dedicated unit-test suite. Validation combined developer reproduction, logs, Scala-side integration automation, nightly and on-demand deployments to separate developer and QA systems, QA regression, and mandatory review by added EPAM and customer reviewers. Native defects used gdb, core dumps, and Valgrind where appropriate.

Outcome and main lesson

The project taught me to trace observable behavior before choosing the component to change, to treat cross-language payloads as contracts, and to prefer narrow evidence-backed changes in systems where compatibility matters more than architectural purity.

Relevance to the GNC request

The direct domain relevance is limited. The useful evidence is production C, careful reasoning across component boundaries, debugging from observations, and disciplined change control. This project does not supply control theory, embedded firmware, simulation, or aerospace evidence.

Scope boundaries

• Shared responsibility for the C backend is not project-wide technical leadership.
• The candidate used the established Jenkins and AWS deployment process but did not own or redesign the CI/CD platform.
• Task estimation did not include organisation-wide resource allocation.
• The C work was a server-side production system, not embedded C firmware.

Likely follow-up questions

• How did you find a defect across Scala, C, Java, and the database?
• What made changes in C89 risky?
• How did you test C code without a dedicated unit-test suite?
• What did promotion to middle grade reflect?
• Which lessons transfer to changing a high-consequence simulation or control interface?

PROJECT 3. UAV OPTICAL-SYSTEM ALGORITHMS

CV period: August 2021 – December 2022
Verified period: Workstream within the August 2012 – January 2020 PELENG employment
CV role: Software Engineer
Verified role: Design Engineer and Research Engineer in the research department of the Space Research and Design Division
Project status: FACTUAL CORRECTION and NARROWER SCOPE

Short project summary

The UAV work was one workstream within my August 2012 to January 2020 employment in aerospace optical-system R&D. I designed and implemented MATLAB modules for debayering, image stabilization, image fusion, and format conversion, calibrated the relationship between an IMU and the camera, implemented frame-centre coordinate computation, and participated in more than thirty flight tests as an optical-payload operator. This is my closest evidence for sensors, physical calibration, and flight validation, but it was payload imaging rather than vehicle GNC.

Product and business context

The system was an optical payload for an unmanned aerial vehicle. Raw sensor output had to be converted into usable colour imagery, corrected for motion-induced visual effects, combined where appropriate, connected to navigation data, and validated in real flight conditions.

System architecture and main components

• Bayer-pattern image sensor and optical payload.
• MATLAB processing modules for debayering, stabilization, fusion, and format conversion.
• IMU and navigation-board data providing platform attitude and position at an interface boundary.
• Frame-centre coordinate computation for geo-referenced imagery.
• Ground analysis tools and recorded flight data.
• Flight-test workflow involving the payload operator, flight crew, and test engineers.

My role and ownership

I owned the image-processing algorithms and the software and calibration work around them. I implemented the processing modules in MATLAB, calibrated the physical relationship between the IMU and camera, implemented the frame-centre calculation, prepared analysis tooling, and operated the optical payload during flight tests.

The flight crew owned aircraft operation. Other engineering groups owned optics, mechanics, onboard electronics, the navigation board, and the flight-software platform. I did not design an autopilot, attitude controller, estimator, or vehicle dynamics model.

Main contributions

• Implemented debayering from raw sensor data to full-colour imagery.
• Implemented image-format conversion required by the processing chain.
• Developed image stabilization to reduce motion-induced visual distortion.
• Developed image fusion to improve the useful content of the optical output.
• Calibrated IMU-to-camera alignment.
• Implemented frame-centre coordinate computation using the calibrated relationship and navigation data.
• Prepared and reused recorded data for analysis.
• Operated the optical payload during more than thirty UAV flight tests.

Key engineering challenges

Physical systems do not respect nominal geometry perfectly. A small angular mismatch between an IMU and camera can become a large ground-coordinate error. Because both subsystems can be correct in isolation, component tests cannot expose the relationship error. Flight opportunities were also scarce, so the analysis had to be prepared before each campaign and recorded data had to be reused effectively afterwards.

Image stabilization posed a separate boundary problem. The algorithm corrected image motion or distortion in the optical output. It did not command the aircraft or close a feedback loop around vehicle attitude. That distinction must stay explicit in this interview.

Representative investigation or delivery story

Situation: The camera and navigation board each passed their own checks, but the calculated centre of the image frame did not agree with known ground coordinates.

Task: Identify why two correct subsystems produced an incorrect integrated result and restore reliable geo-referencing.

Actions: I treated the interface geometry as the likely owner of the error, calibrated the actual IMU-to-camera alignment rather than trusting nominal mounting values, incorporated the correction into the frame-centre computation, and compared the output with known ground positions.

Result: The calculated frame-centre coordinates agreed with actual ground positions, making the imagery usable for geo-referenced analysis.

Testing, validation, and diagnostics

I used reference targets, recorded imagery, navigation data, intermediate MATLAB visualizations, and comparisons with known ground coordinates. Flight tests supplied the real platform motion, environmental conditions, sensor behavior, and interface errors that could not be reproduced fully from nominal specifications. More than thirty flights provided repeated operational evidence, but the exact number of algorithm-validation runs and numerical error reduction are not recorded and must not be invented.

Outcome and main lesson

The strongest lesson is that integration correctness is a separate property from component correctness. When every component appears healthy, the relationship between them may still be wrong. The engineering response is to identify the missing transform or calibration parameter and validate it against external ground truth.

Relevance to the GNC request

This work is relevant to physical sensors, coordinate relationships, calibration, measured data, flight validation, and errors that live between subsystems. It is adjacent to state estimation and spacecraft attitude work, but it is not evidence of Kalman filtering, navigation-filter design, control laws, plant modelling, or vehicle stabilization.

Scope boundaries

• The verified period is within August 2012 to January 2020, not August 2021 to December 2022.
• The role was Design Engineer and Research Engineer, not Software Engineer or GNC Engineer.
• Image stabilization is not aircraft attitude stabilization.
• Image fusion is not a verified Kalman or navigation sensor-fusion implementation.
• IMU-to-camera calibration is geometric calibration, not state estimation or system identification.
• Hard real-time behavior and latency guarantees are not established.
• Aircraft control, airframe, autopilot, navigation-board design, and flight operations were outside personal ownership.

Likely follow-up questions

• How did you determine that the error was between the IMU and camera?
• What was calibrated, and what was treated as external input?
• How did you validate the corrected frame coordinates?
• What did the image-stabilization algorithm stabilize?
• Why is this not Kalman filtering or vehicle control?
• What did you learn from operating the payload during flight tests?

PROJECT 4. SATELLITE OPTICAL-IMAGING ALGORITHMS

CV period: August 2019 – March 2021
Verified period: Workstreams within the August 2012 – January 2020 PELENG employment
CV role: Software Engineer
Verified role: Design Engineer and Research Engineer in the research department of the Space Research and Design Division
Project status: FACTUAL CORRECTION and NARROWER SCOPE

Short project summary

During the same August 2012 to January 2020 aerospace R&D employment, I designed and validated MATLAB algorithms for satellite imaging payloads. The work included detector-segment stitching, radiometric correction, an ADPCM-family onboard compression design, image-type prediction and adaptive quantization, automated linear-resolution assessment, STK-assisted imaging planning, and satellite in-orbit testing. The strongest connection to the GNC request is disciplined physical modelling and verification under flight-hardware constraints, not attitude-control ownership.

Product and business context

An Earth-observation imaging payload does not produce a finished image directly. A focal plane can contain several detector arrays with different physical response, onboard computation and downlink are limited, and flight-test opportunities are scarce. Algorithms had to compensate for the actual instrument, fit onboard constraints where applicable, and produce behavior that could be verified before and after handover to the flight-software group.

System architecture and main components

• Multi-detector focal plane producing raw image segments.
• Radiometric correction for detector-response differences.
• Geometric and radiometric stitching into continuous imagery.
• Onboard compression boundary using a computationally economical ADPCM-family design.
• Image-type prediction and adaptive quantization.
• Ground decompression and image-quality analysis.
• Automated linear-resolution assessment from flight-test imagery.
• Systems Tool Kit for orbit modelling and imaging planning.
• MATLAB reference algorithms and a separate onboard flight-software implementation boundary.

My role and ownership

I designed, implemented, and verified image-processing algorithms primarily in MATLAB. I owned the reference behavior, analysis, formal design documentation, and verification on reference and real imagery. When an algorithm was destined for onboard execution, the flight-software group owned the target implementation. I supported the handover and compared the resulting behavior with the MATLAB reference.

I did not own the satellite bus, attitude-control system, star-sensor design, onboard electronics, flight-software platform, mission operations, or ground segment.

Main contributions

• Designed and implemented satellite frame stitching combining geometric alignment with radiometric matching.
• Derived and applied correction coefficients for detector-array response differences.
• Designed an ADPCM-family lossy compression approach that achieved approximately 3–4x data reduction within the onboard computation budget.
• Improved quality at a fixed compression ratio through image-type prediction and adaptive quantization.
• Automated linear-resolution assessment from flight-test imagery.
• Used STK for orbit modelling and imaging planning.
• Produced formal design documentation and supported algorithm handover to onboard implementation.
• Participated in satellite flight tests and in-orbit validation.

Key engineering challenges

The binding constraint was onboard computational capacity. Compression quality could not be optimized independently from the hardware budget, and a theoretically better transform-based method was not useful if it could not execute within that envelope. Downlink capacity fixed the required compression, while the irreversibility of lossy processing raised the verification standard.

A second challenge was the MATLAB-to-flight-software boundary. A correct reference algorithm does not guarantee correct target behavior because arithmetic, precision, memory, execution order, and timing differ. The reference therefore had to be specific enough to act as a behavioral contract.

Representative investigation or delivery story

Situation: Satellite imagery needed approximately 3–4x compression for downlink, but the onboard computer had a very limited processing budget.

Task: Select and design a compression approach that achieved the required data reduction with acceptable image quality and could actually run on the target hardware.

Actions: I evaluated algorithm families against both quality and computation, rejected more expensive transform-based approaches for this constraint, and selected differential predictive coding with adaptive quantization. I concentrated the design on prediction and quantizer behavior, tested it on reference imagery, compared results at matched compression ratios, and had artifacts assessed both numerically and by image-quality specialists.

Result: The design achieved approximately 3–4x compression while preserving the image properties required for the mission within the onboard computation envelope.

Testing, validation, and diagnostics

The workflow used reference imagery with known properties, real instrument data, intermediate MATLAB stages, difference images, matched-ratio comparisons, expert assessment for perceptual artifacts, flight-test imagery, and in-orbit results. For algorithms implemented onboard by the flight-software group, reference inputs and expected behavior were used to investigate differences introduced by target arithmetic or constraints.

Outcome and main lesson

The best algorithm is not the one with the strongest isolated metric; it is the one that satisfies the whole physical system. The work also established a lasting habit of treating a model or reference implementation as a testable behavioral contract rather than assuming that its intent survives implementation automatically.

Relevance to the GNC request

This work supports scientific computing, conservation of physical meaning through a processing chain, constrained algorithm design, model verification, test planning, flight evidence, and collaboration across the algorithm-to-embedded boundary. It does not establish MuJoCo, spacecraft rigid-body dynamics, pointing simulation, control laws, momentum management, or GNC Monte Carlo verification.

Scope boundaries

• The verified work belongs to August 2012 to January 2020, not August 2019 to March 2021.
• MATLAB was the primary implementation environment; the CV's C++ implementation claim is not supported by the verified project record.
• The flight-software group owned onboard code.
• STK use concerned orbit modelling and imaging planning, not high-fidelity spacecraft plant dynamics.
• Work on imaging payloads does not establish ownership of the spacecraft attitude-control system or star sensors.
• Compression and image-quality algorithms are not feedback-control algorithms.

Likely follow-up questions

• Why was the ADPCM-family approach selected over transform-based compression?
• How did you validate quality at a fixed compression ratio?
• What changed when an algorithm moved from MATLAB to flight software?
• Which assumptions had to be explicit at the handover boundary?
• How did flight and in-orbit data change the model or algorithm?
• What did you use STK for, and what did you not simulate?

ACADEMIC FOUNDATION RELEVANT TO THE REQUEST

Degree and formal study

The candidate completed a five-year specialist diploma in Radiophysics at Belarusian State University from September 2007 to June 2012, specializing in Satellite Information Systems and Technologies and receiving the qualification Radiophysicist. Relevant transcript evidence includes a 76-hour Ballistics and Small-Spacecraft Control course graded 9/10, information processing in computational experiment, methods of computational experiment, signal processing, electronics, communications, and satellite-domain study.

The degree is longer than a four-year bachelor programme and is technically relevant, but acceptance as a BS or MS equivalent for a US employer must be confirmed rather than asserted.

Monte Carlo and statistical modelling

In a fourth-year precision-agriculture study, the candidate worked through a statistical bioequivalence method that estimated comparison behavior by Monte Carlo simulation from fitted normal distributions. He also implemented expectation-maximization clustering over a Gaussian mixture model in MATLAB and built a synthetic-data harness to verify recovery of known clusters.

The transferable evidence is distributional reasoning, explicit assumptions, sampling design, parameter estimation, simulation, and synthetic ground truth. The domain and purpose were not spacecraft dynamics, pointing, stability, or plant-parameter dispersion.

Physical forward modelling

The diploma thesis examined retrieval of atmospheric ozone vertical profiles from surface spectral irradiance measurements. The candidate extended a parameterized profile model, generated vertical profiles, studied parameter sensitivity, constructed an atmosphere model, and used radiative-transfer modelling to investigate the forward relationship from profile to measured spectrum.

The transferable evidence is physical modelling, parameter influence, observability of an inverse problem, and recognizing when a model cannot represent the case of interest. It is not a rigid-body dynamics model or a controller.

Space-systems study

The candidate attended English-language Summer Space Schools at Samara State Aerospace University in 2011 and 2013. Recorded topics included onboard systems, navigation, orientation and stabilization, flight dynamics and attitude control, GNSS, satellite requirements and architecture, link and power budgets, and nanosatellite design exercises.

This is formal academic exposure only. No affiliation with Samara Aerospace is established, and the courses do not replace professional spacecraft GNC experience.

CROSS-PROJECT CAREER NARRATIVE

The career began with physics, statistics, MATLAB, and satellite-domain study. It then moved into more than seven years of algorithm R&D on real optical instruments, where the candidate learned to design under fixed hardware constraints, validate against measured data, and manage the boundary between a MATLAB reference algorithm and software running onboard.

The next phase moved from research engineering into production C and C++ software. The library system added discipline in mature production code, cross-component diagnosis, review, and Linux operation. The embedded SIP platform then brought the work back to a physical device, adding C++17, asynchronous state, Yocto Linux, target integration, and real-hardware diagnosis.

For the GNC role, this is a coherent adjacent story: physics and space systems, scientific algorithms, flight evidence, reference-to-target verification, and embedded software. The missing step is equally important: the candidate has not yet delivered professional spacecraft control laws, plant models, estimators, system identification, or active-noise-cancellation loops.

SAFE BOUNDARY STATEMENTS

Professional GNC experience

My professional aerospace work was on optical-payload algorithms, calibration, and validation. I studied spacecraft-control topics academically, but I have not owned a professional spacecraft attitude-control or GNC subsystem.

Feedback control and resonant plants

I have not designed feedforward or feedback control for flexible, lightly damped, resonant, or multi-joint plants. My closest transferable experience is modelling physical behavior, calibrating subsystem relationships, and validating algorithms against measured data.

State estimation and Kalman filtering

I implemented image fusion and IMU-to-camera calibration, but I would not describe that as Kalman filtering or navigation-state estimation. Those are direct gaps.

MuJoCo and spacecraft simulation

I have used MATLAB extensively, STK for orbit and imaging planning, and physical forward models in research. I have not built a MuJoCo model or a high-fidelity spacecraft dynamics plant.

Monte Carlo simulation

My verified Monte Carlo work was an academic statistical method using fitted normal distributions. I understand why dispersion testing matters, but I have not run spacecraft pointing or stability campaigns.

System identification

I have calibrated physical relationships and compared model output with real measurements. I have not owned formal system identification or automated on-orbit parameter estimation, so I would treat that as a new discipline rather than relabel calibration work.

Active noise cancellation

My recent embedded work included phone-side media integration. I did not design ANC algorithms or audio feedback loops.

Embedded C and C++

My direct embedded experience is C++17 and Qt on Yocto Linux and ARM64 hardware. My substantial C experience is a production C89 backend, not embedded firmware.

MATLAB and Python

I used MATLAB as my primary algorithm environment for more than seven years, but that experience is historical and I would refresh it. Strong scientific-Python experience is not established by the current record.

Flight software

I owned MATLAB reference algorithms, documentation, and verification. A separate flight-software group owned the onboard implementation.

Degree equivalency

I hold a five-year specialist diploma in Radiophysics with a satellite-systems specialization. I can provide the diploma and transcript, while the employer should determine its US equivalency.

CLOSING POSITIONING

The candidate should be presented as an aerospace algorithm and embedded-software engineer with unusually relevant adjacent foundations and a research method suited to experimental spacecraft development. The honest value proposition is immediate contribution in MATLAB-oriented algorithm structure, physical-model verification, sensor and interface reasoning, measured-data analysis, reference-to-embedded collaboration, and C++ integration, combined with a substantial learning curve in control theory and the request's direct GNC stack.

If Samara Aerospace requires an engineer who can independently design attitude-control laws, Kalman estimators, MuJoCo spacecraft dynamics, resonant-plant controllers, momentum-management algorithms, system-identification experiments, and ANC loops from day one, this profile is not a direct match. If the team is genuinely open to a strong adjacent aerospace researcher and embedded software engineer who can grow into those areas under close collaboration, the evidence in this legend provides a defensible basis for the conversation.
