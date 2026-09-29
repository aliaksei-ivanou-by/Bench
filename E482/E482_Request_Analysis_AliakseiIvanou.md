REQUEST AND CUSTOMER ANALYSIS

DOCUMENT INFORMATION

Request ID: E482
Candidate: Aliaksei Ivanou
Target role: Senior Embedded C++ and Real-Time Graphics Engineer
CV source: E482 Aliaksei Ivanou (8, C++) BrightBox.pdf
Request document: E482_Request_AliakseiIvanou.md
Profile source: E482_Profile_AliakseiIvanou.md
Research date: 2026-09-29
Analysis status: Interview-ready with a conditional no-go on a strict graphics gate

EVIDENCE RULES

VERIFIED REQUEST FACT: Recorded in the reviewed and normalized Request document.
VERIFIED PUBLIC FACT: Supported by an official public source listed in this document.
CONFIRMED CANDIDATE EVIDENCE: Supported by the verified career repository.
INFERENCE: A useful interpretation that has not been confirmed by the customer.
OPEN QUESTION: Information that must be obtained from the recruiter or customer.
GAP: A requested capability that is not supported by verified candidate evidence.

EXECUTIVE ASSESSMENT

Overall fit: WEAK for the exact graphics-centered profile; PARTIAL for an embedded, simulation-middleware, image-processing, or 3D-data stream
Recommendation: QUALIFY BEFORE PROCEEDING

The request was reopened specifically to add 3D rendering and graphics to an already senior C++ profile. That makes the graphics requirement a probable selection gate rather than a secondary preference. The verified career record does not support production Vulkan, OpenGL, Direct3D, OpenSceneGraph, GLSL, HLSL, shader, graphics-engine, or Image Generator work.

The candidate does have a credible adjacent combination: C++17 and Qt on embedded Linux and physical ARM64 devices; a commercial C++ point-cloud and surface-reconstruction prototype; and a substantial earlier period of satellite and UAV image-processing research and development. This combination can be relevant to simulation middleware, 3D-data processing, hardware integration, visual-system diagnosis, or a role willing to train the renderer stack. It is not equivalent to several years of senior real-time-rendering delivery.

The submitted BrightBox CV closes the graphics gap on paper by introducing unsupported OpenGL, GLSL, OpenSceneGraph, LiDAR, OpenMP, SIMD, driver, and performance claims and by overstating personal STM32, RTOS-platform, and formal standards ownership. FreeRTOS was present in the UAV system, MISRA familiarity is real, and the aerospace lifecycle was V-model-style; those points must be presented with their actual ownership boundaries. The preparation strategy is to qualify the stream before submission, lead with confirmed adjacent evidence, and state the rendering gap before detailed graphics questions expose it.

There is a second possible gate: the candidate is currently in Minsk, while the request says EU only. He has a valid Polish national D visa, previous Warsaw employment, and a concrete return plan, but BrightBox must confirm whether physical presence in the EU is required at submission or only by the start date.

REQUEST FACTS

Role: Senior Embedded C++ and Real-Time Graphics Engineer
Seniority: Senior- or Senior
Industry and domain: Commercial aviation, full-flight simulators, visual and display systems, real-time simulation software, site installation, aftermarket upgrades, and obsolescence replacement
Engagement: 1 FTE; stated duration 1–3 months; EU only; on-site work and/or travel may be required; source time-zone field says “-1 Warsaw”
Languages: C++ through C++20, C, C#; English B2+
Submission deadline: Not disclosed
Team size or requested headcount: 5 positions; the wider software organisation is approximately 20 engineers, while an individual programme may have only 2–3 software engineers
Initial delivery context: Aftermarket work on fielded simulators, including component or software replacement, upgrades, new configurations, and obsolescence changes
Working model: High autonomy, dependable delivery, early risk escalation, and technical support for programme-manager or customer discussions
Tooling constraint: AI coding tools are not permitted on protected programme code, documentation, or technical information

CUSTOMER CHAIN

Request source or intermediary: Innowise internal staffing request
Named customer: BrightBox Group
Final client or product owner: Acron Aviation, according to the supplied account context
Confidence and boundary: The Innowise to BrightBox to Acron chain is a request fact, not independently confirmed by a public announcement. Official BrightBox material confirms an on-demand engineering and delivery-partner model. Official Acron Aviation material confirms the commercial aviation and flight-simulation domain. No official public source found in this review confirms this specific staffing relationship, project, team, aircraft stream, or codebase.

CUSTOMER AND DOMAIN RESEARCH

Research item 1
Verified public fact: BrightBox describes itself as a provider of on-demand software, data, and digital engineers. Its published process includes AI-assisted matching, human interviews, technical tests or challenges, final client interviews, onboarding, and ongoing alignment.
Interview implication: The initial BrightBox interview is likely to validate both exact keyword depth and the ability to integrate quickly. A tailored CV that names OpenGL or OpenSceneGraph can trigger direct technical testing before the final client stage.
Source: https://www.brightboxgrp.com/skills/software-data-digital-engineers

Research item 2
Verified public fact: BrightBox’s delivery-partner page describes individuals, pods, and squads supplied through pre-vetted consultancies and engineering organisations.
Interview implication: The request’s five positions may represent several streams or a scalable team rather than five identical renderer seats. Confirm the intended stream before deciding fit.
Source: https://www.brightboxgrp.com/become-a-delivery-partner

Research item 3
Verified public fact: Acron Aviation describes its business as commercial aviation technology spanning avionics, flight-data intelligence, training systems, training services, and support. Its public site states that it has more than 350 flight simulators in operation worldwide.
Interview implication: The environment is a long-lived product and support domain, not a short graphics demo. Reliability, configuration control, compatibility, validation, and customer-specific aircraft variants are likely to matter alongside rendering performance.
Source: https://acronaviation.com/

Research item 4
Verified public fact: Acron Aviation’s Training Systems division publicly offers Full Flight Simulators, Virtual Flight Decks, training hardware, training software, and aftermarket support. Its Reality7e Full Flight Simulator is described as a modular platform.
Interview implication: The phrase “simulation visual systems” may refer to several boundaries: the Image Generator, cockpit and avionics display simulation, simulation middleware, training applications, device integration, or support and upgrade work. The exact boundary must be established.
Source: https://acronaviation.com/training-systems/

Research item 5
Verified public fact: Acron’s official structured Training Systems page identifies Acron Aviation as the parent company, notes the former L3Harris Commercial Aviation Solutions affiliation, and lists Full Flight Simulators, certified training devices, Reality7e, classroom or procedure devices, and aftermarket upgrades.
Interview implication: The supplied description of Acron as connected to L3Harris is historically plausible, but Acron is now the public brand. Use the current name unless the interviewer uses the legacy name for a specific system.
Source: https://acronaviation.com/ai-information/training-systems/

Research item 6
Verified public fact: Acron’s Virtual Flight Deck product simulates aircraft systems and flight-deck panels, controls, indicators, and displays with real-time interaction and uses real-time simulation models based on OEM aircraft and avionics data where available.
Interview implication: “Visualisation” in this organisation can mean more than photorealistic outside-world rendering. Some positions may center on interactive cockpit systems and displays, which could make C++ application, state, UI, and integration experience more relevant. This is an inference until the stream is confirmed.
Source: https://acronaviation.com/training-systems/training-software/virtual-flight-deck/

Research item 7
Verified public fact: Acron publicly reported an Airbus A320neo full-flight-simulator milestone and states that the same training centre supports Airbus A320 and Boeing 737NG type-rating activity as well as Upset Prevention and Recovery Training.
Interview implication: The supplied A320, B737, and UPRT context is consistent with Acron’s public product and training footprint, but it does not prove which programme this request supports.
Source: https://acronaviation.com/newsroom/acron-aviation-installs-new-airbus-a320neo-full-flight-simulator-at-london-training-center-marking-100th-a320-device-milestone/

ROLE OUTCOME

Success most likely means becoming productive quickly in an established C++ simulation codebase, taking autonomous ownership of a bounded aftermarket work package, understanding the boundary between simulation state, scene or display state, rendering, hardware, and verification, and delivering the change without destabilizing a customer-accepted system. The engineer must make delivery risks visible early and explain technical constraints and options to programme stakeholders. For a rendering stream, success would also require practical command of the current graphics API, shader language, scene representation, CPU and GPU synchronization, frame-time diagnosis, and reproducible visual or hardware-in-the-loop validation.

This outcome is an inference from the request, short stated duration, five-position scale, supplied team context, and public Acron product domain. It is not a customer-confirmed job description.

MUST-HAVE REQUIREMENT MAPPING

Requirement 1: Senior- or Senior-level software engineering
Priority: MUST-HAVE
Candidate evidence: Technical lead of an engineering sub-group that grew from four to six, architecture and integration decisions, reviews, onboarding and mentoring, interview support, and predominantly hands-on C++ delivery.
Match: PARTIAL
Boundary or risk: Formal grade is middle, not senior. Senior was not awarded by the employer.
Safe interview wording: My formal grade is middle. The senior-level evidence is the scope I carried: architecture decisions, cross-layer delivery, review and mentoring while remaining hands-on.

Requirement 2: At least 5–6 years of relevant experience
Priority: MUST-HAVE
Candidate evidence: More than six years of C and C++ practice, including five years in commercial C/C++ employment, plus earlier algorithm research and development.
Match: STRONG if the requirement is C/C++ breadth; PARTIAL if it means five years of real-time graphics
Boundary or risk: No five-year rendering, RTOS, or simulator track.
Safe interview wording: I have more than six years of C and C++ practice and five years in commercial C/C++ roles. My graphics-API experience is not at that level.

Requirement 3: Strong C++ through C++20
Priority: MUST-HAVE
Candidate evidence: Commercial C++17 at RIFTEK, EPAM, and Innowise; commercial C89; a personal C++20 application; modern C++ study and interview preparation.
Match: STRONG ADJACENT
Boundary or risk: No verified commercial codebase whose baseline was C++20.
Safe interview wording: My commercial work is primarily C++17 and C89. I used C++20 in my own application and study, so I would separate language knowledge from commercial version adoption.

Requirement 4: Direct 3D rendering and graphics capability
Priority: MUST-HAVE and probable gate
Candidate evidence: C++ point-cloud processing, surface reconstruction, 3D visualization through PCL and Open3D, image-processing algorithms, geometric calibration, and physical-system validation.
Match: GAP for real-time rendering; ADJACENT for 3D data and imaging
Boundary or risk: No verified renderer, shader, scene graph, draw-pipeline, GPU-resource, or frame-pacing work.
Safe interview wording: I have direct 3D-data and image-processing experience, but I have not shipped a real-time graphics renderer.

Requirement 5: Vulkan, OpenGL 4.6, Direct3D, or comparable low-level graphics API
Priority: MUST-HAVE unless the customer says otherwise
Candidate evidence: None in the verified career record.
Match: GAP
Boundary or risk: The submitted CV names OpenGL 4.x, but the underlying work does not support that claim.
Safe interview wording: I am preparing the graphics concepts and can build a focused exercise, but I have no production project in these APIs.

Requirement 6: OpenSceneGraph
Priority: MUST-HAVE or strong preference, depending on stream
Candidate evidence: None. PCL and Open3D are different libraries for different tasks.
Match: GAP
Boundary or risk: The submitted UAV project’s OpenSceneGraph SIL environment is unsupported.
Safe interview wording: I used PCL and Open3D for point-cloud work. OpenSceneGraph would be a new framework for me.

Requirement 7: GLSL or HLSL and shader stages
Priority: MUST-HAVE or strong preference
Candidate evidence: None in production or verified personal projects.
Match: GAP
Boundary or risk: Fluent prepared explanations could be mistaken for delivered experience.
Safe interview wording: I understand the purpose of vertex, fragment, geometry, and compute stages at a conceptual level, but I have not authored production shaders.

Requirement 8: Object-oriented design and software architecture
Priority: MUST-HAVE
Candidate evidence: Qt application architecture, explicit SDK or application state ownership, call-session and service extraction, explicit provisioning project-state models, and a four-layer personal application.
Match: STRONG
Boundary or risk: Not every project was greenfield or architected solely by the candidate.
Safe interview wording: My strongest examples are moving SIP recovery into the SDK layer that owned the state and replacing UI-tree persistence with explicit project-state models.

Requirement 9: Multithreaded and concurrent systems
Priority: MUST-HAVE
Candidate evidence: QThread, Qt Concurrent, queued events, asynchronous SIP and WebRTC callbacks, background Windows operations, and cross-thread state and shutdown concerns.
Match: PARTIAL TO STRONG
Boundary or risk: No verified lock-free ring-buffer implementation, hard-real-time scheduler work, or GPU command-generation architecture.
Safe interview wording: I have direct application-level concurrency and asynchronous-state experience. Lock-free and hard-real-time claims would be prepared knowledge, not project evidence.

Requirement 10: Debugging, root-cause analysis, and performance engineering
Priority: MUST-HAVE
Candidate evidence: Logs, gdb or gdbserver, core dumps, Valgrind in the toolchain, physical-device scenarios, cross-runtime Linux diagnosis, stage-by-stage point-cloud inspection, and algorithm selection under a fixed onboard computation budget.
Match: STRONG ADJACENT
Boundary or risk: No production GPU profiler, renderer capture, or shader-optimization case.
Safe interview wording: My method is measurement-first and cross-layer. I have not used RenderDoc, Nsight, or PIX on a production renderer.

Requirement 11: Flight-simulation or visual-system experience
Priority: MUST-HAVE or strong preference
Candidate evidence: Aerospace optical systems, UAV flight tests, imaging and calibration, hardware-in-the-loop style validation, and 3D reconstruction.
Match: ADJACENT
Boundary or risk: No flight simulator, aircraft-system model, cockpit display, Image Generator, weather-effects, or training-device delivery.
Safe interview wording: My aerospace experience is optical-payload and imaging work, not flight-simulator software.

Requirement 12: Windows, Linux, and RTOS
Priority: MUST-HAVE across the broad profile
Candidate evidence: Direct Windows application development, Linux and embedded Yocto production work, plus a UAV project whose onboard subsystem used FreeRTOS.
Match: PARTIAL
Boundary or risk: FreeRTOS project exposure is real, but personal RTOS-kernel, STM32 board-support, porting, driver, interrupt, scheduler, and schedulability ownership is not established.
Safe interview wording: Windows and Linux are direct. The UAV system used FreeRTOS, while my main ownership was imaging, calibration, integration, and flight-test validation rather than the RTOS platform itself.

Requirement 13: Embedded systems and hardware interfaces
Priority: MUST-HAVE or strong preference
Candidate evidence: Yocto image work, ARM64 phones, systemd, Weston, U-Boot environment, GPIO, udev, media hardware, scanner hardware, and earlier field-installed GNSS terminals.
Match: STRONG ADJACENT
Boundary or risk: Application and integration depth is stronger than firmware or driver ownership.
Safe interview wording: I am comfortable across application, firmware-image, service, peripheral, network, and hardware boundaries on embedded Linux.

Requirement 14: Pre-boot, low-level driver, or filesystem-extension development
Priority: Role-dependent
Candidate evidence: U-Boot environment handling, kernel or driver integration points and patches, and image filesystem integration.
Match: GAP TO LIMITED ADJACENT
Boundary or risk: No bootloader, complete driver, or filesystem-extension ownership.
Safe interview wording: I worked at those integration boundaries, but I did not own a bootloader, driver, or filesystem extension.

Requirement 15: Testing, TDD, verification, and hardware rigs
Priority: MUST-HAVE
Candidate evidence: Qt Test, MSTest, GoogleTest on personal work, recorded point-cloud datasets, reference imagery, flight tests, physical-phone scenarios, separate QA teams, formal algorithm validation, and a V-model-style aerospace lifecycle linking requirements and design to verification and validation.
Match: STRONG ADJACENT
Boundary or risk: Strict test-first delivery and xUnit are unsupported; no Acron rig or ETM or ATM experience.
Safe interview wording: I combine focused automated tests with replayable datasets and physical-device validation. I have not used the client’s simulator acceptance procedures.

Requirement 16: English B2+
Priority: MUST-HAVE
Candidate evidence: English has been the professional working language since 2021 across distributed teams.
Match: PARTIAL TO MATCH
Boundary or risk: Current stated level is B2 and no B2 certificate was issued; the “+” must be demonstrated in the interview.
Safe interview wording: My current working level is B2 and I have used English professionally for several years.

Requirement 17: EU-only location with on-site or travel availability
Priority: MUST-HAVE
Candidate evidence: Valid Polish national D visa from 26 September 2026 to 25 September 2027, two previous years of legal employment in Warsaw, and a return plan with one month’s notice.
Match: OPEN QUESTION
Boundary or risk: Current physical location is Minsk, outside the EU.
Safe interview wording: I can relocate to Warsaw after my notice period, but I need confirmation that location is assessed at project start rather than submission.

NICE-TO-HAVE REQUIREMENT MAPPING

Requirement: C
Priority: NICE-TO-HAVE
Candidate evidence: More than two years on a production C89 backend plus embedded-C study.
Match: STRONG
Boundary or risk: Not firmware C.
Safe interview wording: My strongest C evidence is a long-lived production C89 backend and native debugging on Linux.

Requirement: C#
Priority: NICE-TO-HAVE
Candidate evidence: Major .NET 8 and WinForms provisioning-tool work plus earlier short C# maintenance.
Match: STRONG SUPPORTING
Boundary or risk: C++ remains the main specialization.
Safe interview wording: C# is a substantial secondary language from the provisioning application.

Requirement: UML
Priority: NICE-TO-HAVE
Candidate evidence: Architecture can be explained with diagram types; no verified formal UML deliverable in the current source.
Match: VERIFY OR GAP
Boundary or risk: The submitted UML claims are unsupported.
Safe interview wording: I use diagrams to explain architecture, but I would not claim an established UML deliverable history without evidence.

Requirement: Security software development
Priority: NICE-TO-HAVE in the profile narrative
Candidate evidence: Certificates, TLS-related settings, SIP Digest, secure-media options, AES project-container behavior, and trust-boundary reasoning.
Match: LIMITED ADJACENT
Boundary or risk: No security product, penetration test, security certification, or hardened cryptographic design.
Safe interview wording: My work was security-related integration and configuration, not security-software specialization.

Requirement: Git, SVN, TortoiseSVN, Sourcetree, Confluence, Jira, Docker
Priority: NICE-TO-HAVE
Candidate evidence: Strong Git, GitLab, Bitbucket, Jira, Jenkins or GitLab CI use; Docker coursework.
Match: PARTIAL
Boundary or risk: SVN, TortoiseSVN, Sourcetree, Confluence, and Docker production ownership are not established.
Safe interview wording: I lead with the tools I used directly and label Docker as coursework.

Requirement: Academic graphics, parallel processing, architecture, communications, electronics, vision, and image processing
Priority: NICE-TO-HAVE
Candidate evidence: Radiophysics degree with programming, electronics, communications, digital signal processing, computational experiment, optics, satellite communication and navigation; professional computer-vision and image-processing work.
Match: STRONG in imaging, communications, electronics, and applied computation; GAP or unverified for formal computer-graphics and parallel-processing coursework
Boundary or risk: Do not invent transcript subjects.
Safe interview wording: My degree and career strongly support imaging, physics, electronics and communications. Computer graphics was not the named specialization on my transcript.

KEY RISKS AND NON-CLAIMS

1. The direct real-time-rendering requirement is unsupported by verified experience.
2. The CV’s OpenGL, GLSL, OpenSceneGraph, shader, LOD, atmosphere, lighting and tile-streaming claims are unsupported.
3. FreeRTOS was present in the UAV system, but the CV overstates personal STM32, RTOS-platform, MAVLink, LiDAR, RTK GNSS, EKF, PPS and SIL ownership.
4. The CV’s OpenMP, SSE, AVX2, lock-free ring-buffer and forty-minute performance result are unsupported.
5. MISRA familiarity and MISRA-aware engineering are confirmed, and the aerospace lifecycle was V-model-style. Full MISRA-compliance ownership, exact ECSS delivery, end-to-end safety-critical C++, GTest on aerospace projects, TLS or OpenSSL transfer and AES imagery storage remain unsupported.
6. The SIP-project dates are incorrect by approximately twenty months at the start and remain marked current after the verified assignment ended.
7. The satellite-platform project described for 2020–2023 is not a verified project and overlaps unrelated employment and assignments.
8. The UAV and 3D entry combines two separate projects and adds an unsupported stack.
9. Formal senior title is not verified.
10. Current location is outside the EU.
11. Current stated English is B2, while the request says B2+.
12. A short 1–3 month assignment is a poor environment in which to learn a renderer stack from zero unless the intended stream is not graphics-centered.

INTERVIEW POSITIONING

Lead with:

• Embedded C++17 and Qt on Yocto Linux and physical ARM64 devices.
• The C++ multi-scanner point-cloud and 3D-reconstruction project.
• Satellite and UAV image-processing algorithms under physical and computation constraints.
• Cross-layer diagnosis across application, SDK, configuration, firmware image, service, network, peripheral and hardware boundaries.
• Clear ownership boundaries and a measurement-first approach to performance and reliability.

Do not claim:

• Production Vulkan, OpenGL, Direct3D, OpenSceneGraph, GLSL, HLSL, shaders or graphics-engine development.
• Flight-simulator, cockpit-display, Image Generator, weather-rendering or aircraft-system-model ownership.
• Personal STM32, RTOS-kernel, porting, scheduler, interrupt, driver, MAVLink, LiDAR, RTK GNSS, EKF, PPS-synchronization or SIL development. FreeRTOS project exposure itself is confirmed.
• OpenMP, SIMD intrinsics, lock-free pipeline implementation or the submitted performance metrics.
• Full MISRA-compliance-programme ownership, exact named ECSS delivery, end-to-end safety-critical C++, formal UML, aerospace GTest suites or the submitted security stack. MISRA familiarity and V-model-style aerospace work are confirmed.
• Complete Linux driver ownership.
• Current EU residence or a formally awarded senior grade.

LIKELY INTERVIEW QUESTIONS

1. Describe the OpenGL rendering pipeline and the shaders you wrote.
Answer direction: State immediately that no production OpenGL or shader work is verified. Bridge to direct coordinate-transform, point-cloud, image-processing and C++ systems evidence, then describe prepared rendering knowledge only if invited.

2. How did your quadtree LOD and asynchronous tile streaming work?
Answer direction: Do not invent an implementation. State that the submitted platform description overstates the verified work; the actual satellite work was MATLAB image processing and STK-assisted planning.

3. What did you build in OpenSceneGraph?
Answer direction: Nothing verified. Explain PCL and Open3D usage, then say OpenSceneGraph would be new.

4. Tell us about your FreeRTOS task model and STM32 interrupt design.
Answer direction: FreeRTOS was present in the UAV system, but the candidate’s main ownership was imaging, calibration, integration, and flight-test validation. Do not invent STM32 board-support, interrupt, task-model, driver, or scheduler ownership. Direct embedded product ownership is strongest on Yocto Linux and i.MX ARM64.

4A. How did MISRA and the V-model apply to your aerospace work?
Answer direction: Describe practical MISRA familiarity and the V-model-style flow from requirements and algorithm design through documentation, implementation handover, verification with reference and real data, flight tests, and in-orbit validation. Do not claim ownership of a complete compliance matrix, qualified tools, formal deviations, DO-178C certification, or the exact ECSS standards named in the submitted CV.

5. How did the EKF fuse GNSS and IMU, and how did you deskew LiDAR?
Answer direction: Do not defend the CV claim. The verified work was IMU-to-camera calibration and frame-centre coordinate computation; no EKF or LiDAR pipeline.

6. How did you eliminate frame drops with a lock-free ring buffer?
Answer direction: No verified implementation. Discuss direct Qt concurrency and asynchronous state ownership, and separate any SPSC-queue knowledge as prepared knowledge.

7. How did you optimize rendering or processing?
Answer direction: Use the satellite compression decision under a fixed compute budget, the point-cloud downsampling and stage-observability tradeoff, or embedded diagnosis. Do not use the under-forty-minute metric.

8. Did you write the Linux drivers on the phone?
Answer direction: Worked with kernel and driver integration points, patches, GPIO and physical-device behavior; did not own complete drivers for the named peripherals.

9. Why are the project dates different from your career history?
Answer direction: Give the verified dates directly. The SIP assignment was May 2025 to August 2026; satellite and UAV optical work was part of August 2012 to January 2020 employment; industrial 3D reconstruction was March to May 2020.

10. Are you senior?
Answer direction: Formal grade is middle; explain technical-lead scope without changing the title.

11. Are you located in the EU?
Answer direction: Currently Minsk; valid Polish national D visa; previous Warsaw employment; can return after one month’s notice; ask whether presence by start is sufficient.

12. What makes you relevant despite the rendering gap?
Answer direction: The combination of embedded C++, 3D geometry and point clouds, aerospace imaging, constrained algorithms and hardware-facing diagnosis. State that it supports an adjacent stream, not a senior renderer claim.

QUESTIONS TO ASK THE CUSTOMER

1. Is direct production use of one named graphics API a strict day-one requirement?
2. Which of the five roles is this profile being considered for?
3. Is the work centered on an outside-world Image Generator, cockpit and avionics displays, simulation middleware, embedded devices, or verification?
4. Which graphics API, shader language, scene-graph framework, operating system and GPU are in the target codebase?
5. How is simulation state transferred to the visual system: shared memory, datapools, UDP, TCP, or another bus?
6. What are the frame-rate, latency, determinism and display-synchronization targets?
7. Which tasks are expected in the first four to six weeks?
8. Is the current need feature development, porting, performance optimization, defect diagnosis, test automation, or acceptance support?
9. How are recorded scenarios, software-only simulation, rigs and acceptance tests divided?
10. Which requirements in the broad specification are hard filters for this exact stream?
11. Does the location rule apply at submission or start, and where is on-site attendance required?
12. What does the one-to-three-month duration represent?

PREPARATION PRIORITIES

1. Obtain a hard answer on whether graphics-API production experience is mandatory. No preparation effort can convert the existing career record into several years of renderer delivery.
2. Memorize the boundary statement for OpenGL, GLSL and OpenSceneGraph and deliver it before technical detail.
3. Rehearse the RIFTEK 3D story: coordinate frames, point-cloud assembly, PCL pipeline, visual diagnosis and the doubled-surface defect.
4. Rehearse the PELENG performance story: choose an ADPCM-family compression algorithm because it fit the onboard compute budget, then improve quality at the same compression ratio.
5. Rehearse the embedded-state story: put registration failover in the SDK layer that owned the state and validate it on real devices.
6. Review coordinate spaces, matrices, normal transformation, depth, culling, blending, shader stages, frame budgets and CPU or GPU synchronization as prepared knowledge.
7. Review TCP, UDP, shared-memory snapshot semantics, sequence numbers, timestamps, staleness and replay.
8. Prepare a precise FreeRTOS scope answer and review deadline, jitter, priority inversion, task communication, and bounded-operation concepts without implying RTOS-platform ownership.
9. Rehearse one concise MISRA and V-model answer that separates practical engineering discipline and lifecycle participation from full compliance, certification, tool-qualification, and deviation authority.
10. Prepare log, trace, dump and replay diagnosis for a watchdog-constrained environment.
11. If time and recruiter feedback justify it, build a small C++ renderer and label it as a preparation exercise, not production experience.
12. Prepare the verified project timeline and do not improvise around the CV periods.
13. Resolve the EU-location rule before a client interview.

PUBLIC SOURCES

1. BrightBox software, data and digital engineers
https://www.brightboxgrp.com/skills/software-data-digital-engineers

2. BrightBox delivery-partner model
https://www.brightboxgrp.com/become-a-delivery-partner

3. Acron Aviation company and capability overview
https://acronaviation.com/

4. Acron Aviation Training Systems
https://acronaviation.com/training-systems/

5. Acron Aviation official structured Training Systems information
https://acronaviation.com/ai-information/training-systems/

6. Acron Aviation Virtual Flight Deck
https://acronaviation.com/training-systems/training-software/virtual-flight-deck/

7. Acron Aviation A320 Full Flight Simulator milestone and training context
https://acronaviation.com/newsroom/acron-aviation-installs-new-airbus-a320neo-full-flight-simulator-at-london-training-center-marking-100th-a320-device-milestone/

FINAL DECISION NOTES

Proceed only after BrightBox confirms that the intended stream can accept strong adjacent C++ systems, 3D-data, imaging and embedded experience without prior production graphics-API work. If the role is a true senior renderer or Image Generator position requiring immediate Vulkan, OpenGL, Direct3D, OpenSceneGraph and shader productivity, the verified profile is a no-go.

If the stream is simulation middleware, interactive cockpit systems, 3D-data processing, embedded integration, display control, or verification, the fit may improve materially. In that case the submitted CV still remains high risk and the interview must use the corrected wording in this package.
