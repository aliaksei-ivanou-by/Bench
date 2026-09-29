PROJECT LEGEND

DOCUMENT INFORMATION

Request ID: E482
Candidate: Aliaksei Ivanou
Preferred interview name: Alex
Target role: Senior Embedded C++ and Real-Time Graphics Engineer
CV source: E482 Aliaksei Ivanou (8, C++) BrightBox.pdf
Source request: E482_Request_AliakseiIvanou.md
Source profile: E482_Profile_AliakseiIvanou.md
Source analysis: E482_Request_Analysis_AliakseiIvanou.md
Companion document: E482_Intro_AliakseiIvanou.md
Preparation language: English
Document status: Interview-ready with consistent technical narratives
Last updated: 2026-09-29

PURPOSE

This document contains the detailed project narratives for the interview. It is reference material for follow-up questions, not one continuous speech.

HOW TO USE THE LEGEND

Start every project answer with the short summary. Expand only the sections relevant to the interviewer's question. A complete answer should distinguish product context, personal contribution, result, and ownership boundary.

This legend is aligned with the Intro document: the opening answer, the challenge stories (section 8) and the boundary statements (sections 7, 13) must be told the same way in both. If a detail is changed here, change it in the Intro as well.

PRIVATE CONSISTENCY NOTES

• Title. Use "Senior Software Engineer" for the professional profile and "Software Engineer" for the role on each project. Present seniority through scope: ownership of integration problems, architecture decisions, cross-team code review and mentoring two engineers.
• Timeline. September 2018 - March 2020 UAV (about 1.5 years); March 2020 - September 2023 satellite platform (about 3.5 years); September 2023 - present SIP phone. Use "8+ years" in the opening. The SIP project is always in the present tense.
• Durations may be spoken; give exact months only if asked. Do not add employer names unless disclosure has been cleared.
• Reconstruction versus simulation. Open3D and PCL belong to the reconstruction stage; OpenSceneGraph belongs to the SIL rig and scene visualization. Keep this split precise.
• Atmosphere and lighting models belong to the satellite globe view.
• Compute shaders were used for GPU-side LiDAR ray generation and scene intersection in the UAV SIL rig.
• Node.js provided a small local API layer for the phone's web-management pages and configuration operations. JavaScript, HTML and CSS remain supporting-level work, not a front-end specialization.
• Tests on the provisioning application: MSTest is the legacy suite that was preserved during the .NET 8 migration; xUnit is used for new test-first work. Keep this split consistent.
• C on the SIP project. C is not listed in the SIP environment line, but Linux kernel drivers are written in C. If asked, say so plainly.
• MISRA static analysis used Helix QAC; findings were triaged into defects, documented deviations and false positives.
• OpenMP and SIMD result: "several hours to under 40 minutes". Do not convert it into a percentage or a precise speed-up factor.
• Mentoring: exactly two engineers, on real-time Linux and the media path.
• Real gaps against the role: ARINC 429, AFDX, CAN; DO-178C. State them once, plainly, using the boundary statements at the end of this document.

PROJECT 1. SIP-BASED PHONE SOFTWARE

Period: September 2023 - present
Role: Software Engineer
Scope: device-stack and provisioning development, cross-team code review, mentoring two engineers

Short project summary

A SIP desk-phone platform for audio and video calls, with camera-enabled and audio-only models, managed centrally by enterprise customers as a device fleet. I work across the whole device stack in C++17 on NXP i.MX8M Mini — Linux peripheral drivers on a Yocto image, V4L2 and GStreamer media services, the customized Linphone middleware and the Qt Widgets call UI — and on the server-side C# provisioning application, which I built and migrated to .NET 8. My most visible results are SIP failover inside liblinphone, WebRTC conferencing on the device, reduced media-path latency spikes and prevention of audio/video degradation under conferencing load, and a reproducible Docker-based Yocto CI.

Product and business context

The product is an enterprise desk phone. Customers deploy it in fleets and expect it to behave like an appliance: it must register reliably, survive server outages, handle everyday call workflows (registration, video calls, hold, transfer, conferencing, phonebook) and be configured remotely without touching each device.

This creates two sides of the product. On the device there is an embedded Linux image, the phone application and customized telephony and media components. On the administrator side there is a Windows configuration and provisioning application and web management, which roll out firmware and settings to the fleet. A defect in either side is visible to the customer as "the phone does not work", so the engineering focus is on robustness on the physical device and on predictable provisioning.

System architecture and main components

• Hardware: NXP i.MX8M Mini (ARM64) board; camera-enabled and audio-only models; peripherals such as the handset hook switch, keypad backlight and camera privacy shutter.
• Embedded Linux image built with Yocto and BitBake; systemd services for the phone application and media services.
• Linux drivers for the phone peripherals: GPIO/input drivers with interrupt-driven events and debounce for the hook switch and privacy shutter, and an LED/PWM interface for the keypad backlight; device-tree descriptions and kernel changes are integrated through the Yocto layer.
• Media services: V4L2 camera capture, GStreamer pipelines, libyuv frame conversion between camera, encoder and renderer formats.
• Telephony middleware: customized Linphone-SDK (liblinphone) for SIP, SDP and RTP, extended with the SIP failover and backup-server logic.
• Conferencing: WebRTC conferencing through mediasoupclient and libwebrtc, alongside Linphone media callbacks.
• Phone application: Qt and Qt Widgets call UI styled with QSS, refactored toward an MVC/MVVM-style structure.
• Web management: JavaScript, HTML and CSS pages on the device, with a small Node.js service exposing local configuration operations to the pages.
• Server side: C# WinForms configuration and provisioning application, migrated from .NET Framework 4.8 to .NET 8; firmware and settings rollout over SNMP, DHCP and TFTP; device inventory in SQLite.
• Engineering infrastructure: Docker-based GitLab CI with a reproducible Yocto/BitBake build container; Qt Test suites on every merge request; xUnit and MSTest on the Windows side; documentation in Confluence; work tracked in Jira.

My role and ownership

I am a hands-on engineer across the device stack and the server-side tool. I personally own:

• the peripheral Linux drivers (hook switch, keypad backlight, camera privacy shutter);
• the refactoring of call handling in the Qt application and its UML documentation;
• video calling and the WebRTC conferencing flows on the device;
• scheduling and buffer optimization in the media path;
• the SIP failover and backup-server logic in liblinphone;
• the C# configuration and provisioning application (built it) and its .NET 8 migration;
• the unified configuration file format across device models;
• the Docker-based GitLab CI with the Yocto build container.

In addition I lead code reviews across the device and tooling teams and mentored two engineers who joined the device team, on real-time Linux and the media path.

Main contributions

Call-handling refactor. I refactored the Qt Widgets call handling toward a cleaner MVC/MVVM-style structure. CallModel owns call and media state, a controller/view-model translates user actions into SDK operations, and widgets render state and emit user intents. Queued Qt signals and slots isolate asynchronous callbacks. I documented the result with UML class and sequence diagrams and covered the state transitions with Qt Test. The migration was incremental: one call flow at a time moved behind the new interfaces while the running product remained usable.

Video calling and WebRTC conferencing. I integrated video calling on the ARM64 device: Linphone media callbacks, camera selection, libyuv frame conversion and the mediasoupclient/libwebrtc rendering paths. On top of that I developed the conferencing user flows: conference creation and join, incoming invite screens, participant roster, video tile layout and audio and video device controls.

Media-path latency. Under conferencing load, audio and video degraded and latency spiked. I optimized scheduling and buffer management in the media path so the device stayed stable under that load (details in Key engineering challenges).

Peripheral drivers. I wrote and maintain GPIO/input drivers for the handset hook switch and camera privacy shutter and an LED/PWM driver for the keypad backlight. Device-tree entries define GPIOs, polarity and debounce; user space consumes input events and brightness controls, while the Yocto layer carries the kernel configuration, patches and image integration.

SIP failover. I extended the liblinphone backend with SIP failover and backup-server connectivity (the representative story below).

Provisioning application. I built the C# configuration application that administrators run on the server PC: it prepares device profiles, rolls out firmware and settings to phone fleets over SNMP, DHCP and TFTP, and keeps device inventory in SQLite. I then migrated it from .NET Framework 4.8 to .NET 8, replacing BinaryFormatter project persistence with explicit JSON state models while preserving firmware-facing provisioning output and MSTest coverage.

Unified configuration formats. I unified the configuration file formats so every phone model reads the same profile structure.

CI and TDD. I set up Docker-based CI in GitLab with a reproducible Yocto/BitBake build container that runs the Qt Test suites on every merge request. I applied TDD to call-state and provisioning logic, writing Qt Test and xUnit cases before implementation.

Key engineering challenges

State across layers. Registration, call state and media state cross the Qt UI, liblinphone, media services and network. The refactor gave call and media state one model visible to the UI, while registration recovery remained inside liblinphone, where timers, authentication and proxy state are owned. This removed competing recovery logic between the UI and SDK.

Real-time media on embedded Linux. Conferencing runs capture, conversion, encoding, decoding, rendering, SIP signalling and UI on one ARM64 SoC. Timestamped queue-depth logs showed that extra copies, format conversions and growing video queues caused frame age to increase under load. I introduced bounded reusable buffer pools, dropped stale video frames instead of displaying them late, removed redundant conversions and gave audio and capture work higher scheduling priority. Repeated multi-party calls showed stable queue depth and no audible or visible degradation.

Changing a mature product. The provisioning application and the Qt application were already in use. Both the .NET 8 migration and the call-handling refactor had to preserve existing behavior: firmware-facing output, configuration compatibility and user workflows. The approach was incremental change behind tests, never a big-bang rewrite.

Hardware and image integration. Some defects exist only in the complete Yocto image on the physical phone — service ordering in systemd, device nodes, driver state — and not in a standalone component. Diagnosis has to be done on the real device.

Representative investigation or delivery story

Situation: The phone needed reliable connectivity when its primary SIP server was unavailable.

Task: Implement SIP failover and backup-server connectivity in the telephony backend.

Actions: I implemented an explicit state machine in liblinphone. Consecutive registration timeouts or transport errors moved the account from the primary proxy to the configured backup. While on backup, a low-frequency probe checked the primary; fail-back happened only after a stable successful registration. The application received the active-server state through a small API, provisioning supplied both domains and credentials, and transition logs recorded the trigger, target and result.

Result: Primary loss, backup registration, primary recovery, authentication failure and repeated network interruption behaved predictably on physical phones. Recovery no longer depended on UI state, and the transition logs made field diagnosis straightforward.

Testing, validation, and diagnostics

• Qt Test for call-state logic, xUnit for new provisioning logic, MSTest preserved on the legacy provisioning suite; tests written before implementation where TDD applied.
• Every merge request builds in the Docker Yocto container and runs the Qt Test suites.
• Validation on physical ARM64 phones: call scenarios, conferencing load, server-loss and recovery scenarios.
• Diagnostics combine application and systemd logs, SIP and media traces, GDB for target-side state and backtraces, Valgrind on debug builds, kernel messages and device-node checks for peripherals, plus repeated scenarios with controlled configuration.

Outcome and main lesson

The phone is more robust under server outages and conferencing load, the provisioning tool runs on a supported .NET with safe persistence, all models share one configuration structure and the build is reproducible in CI.

Main lesson: recovery logic belongs beside the state it controls. Keeping registration timers, authentication and active-proxy state in liblinphone prevents the UI and SDK from becoming competing state machines.

Scope boundaries

• Not claimed: SIP server or PBX infrastructure, or the conferencing server (SFU) side; my work is the device client and provisioning.
• Not claimed: hardware design or board schematics; my work is drivers and integration of existing peripherals.
• Not claimed: the NXP vendor BSP, bootloader and base kernel bring-up; my work starts at peripheral drivers, recipes, services and product integration on top of the provided BSP.
• Web management front end is supporting-level work, not a specialization.
• Product priorities and release decisions are owned by product and project management; I provide technical evidence and options.

Likely follow-up questions

• Why was failover implemented in liblinphone? — It owns registration timers, authentication and active-proxy state; implementing recovery there avoids a second state machine in Qt.
• How does the phone detect that the primary server is down, and when does it fail back? — Consecutive registration timeouts or transport errors trigger backup; periodic probes return to primary only after stable registration.
• What did the call-handling refactor change in the class structure, and how did it improve testability? — Model owns call and SDK state; widgets render; logic covered by Qt Test.
• What caused the latency spikes, how did you measure them and how did you prove the fix? — Extra copies, conversions and growing queues; timestamped queue-depth logs; repeated conferencing load with stable frame age after bounded buffers and stale-frame dropping.
• What type of Linux driver is each peripheral, and how does user space read its state?
• How does V4L2 capture hand frames to GStreamer, Linphone and libwebrtc, and where does libyuv conversion happen?
• Why was BinaryFormatter a problem, and how did you prove that provisioning output did not change after the migration? — Obsolete and unsafe in modern .NET; JSON models; existing MSTest suite and identical firmware-facing output.
• How is the Yocto build kept reproducible in Docker? — The image pins host packages and toolchain dependencies, layer revisions are fixed, and sstate/download caches improve speed without changing build inputs.
• What did you teach the two engineers you mentored?
• What do you look for in code review across the device and tooling teams? — Ownership, failure behavior, compatibility, testability, not only style.

PROJECT 2. SATELLITE IMAGERY PROCESSING AND 3D VISUALIZATION PLATFORM

Period: March 2020 - September 2023
Role: Software Engineer
Scope: processing chain and 3D visualization components; safety-critical C++ under MISRA C++:2008; project work under ECSS processes

Short project summary

A ground-segment platform that turns raw Earth observation imagery into seamless, radiometrically consistent mosaics and shows them on an interactive 3D globe together with satellite orbits and imaging swaths. I developed the registration and mosaicking chain and the MTF/RER image-quality assessment, rendered multi-gigapixel rasters in OpenGL 4.x with a quadtree LOD scheme and asynchronous tile streaming, wrote GLSL shaders for cloud masks and overlays, and integrated orbit data from STK. I parallelized the processing chain with OpenMP and SIMD, bringing a full-scene mosaic from several hours to under forty minutes. Safety-critical C++ components followed MISRA C++:2008, and the project used ECSS-E-ST-40C and ECSS-Q-ST-80C processes.

Product and business context

The users are analysts and mission planners. Before imagery is released to customers they need to inspect large survey areas, check that the imaging coverage is complete and verify image quality. The platform therefore has two jobs: produce accurate, seamless products and let people inspect them interactively at any scale.

Because it is space-sector software, every processed product has verified accuracy, and development follows a formal lifecycle: requirements, design documentation, reviews, coding standards, product assurance and verification evidence.

System architecture and main components

• Ingest and raster I/O: GDAL for GeoTIFF and project raster formats, geotransforms, coordinate-system metadata, windowed reads and tile-pyramid generation.
• Registration: gradient-based interest points matched by normalized cross-correlation, RANSAC rejection of outliers and an affine transform for aligned strips.
• Radiometric normalization and mosaicking: per-band gain and offset from overlap statistics, low-error seam placement and feathered blending across overlaps.
• Image-quality assessment: edge targets, MTF and RER metrics used by QA for each imaging campaign.
• 3D globe viewer: OpenGL 4.x renderer with a quadtree tile pyramid, screen-space LOD, asynchronous GDAL loading, a bounded GPU upload queue and an LRU tile cache; GLSL shaders for cloud masks, raster overlays, atmosphere and lighting.
• Orbit and swath display: ephemeris and access data pulled from STK through its Connect interface and rendered as orbits and imaging swaths on the globe.
• Performance layer: OpenMP static scheduling across independent raster tiles and SSE/AVX2 vectorization of aligned per-band buffers; results compared with a scalar reference within the established numerical tolerance.
• Security: TLS/OpenSSL for image transfer; AES encryption for stored imagery.
• Verification: GTest regression suites; geometric accuracy against reference ground control points.
• Process and tooling: MISRA C++:2008 for safety-critical components; ECSS design documentation with UML; CMake, Visual Studio, Linux and Windows; Jira, Confluence, SVN.

My role and ownership

I was a hands-on developer on both the processing chain and the rendering side. I personally developed:

• registration and mosaicking of overlapping strips;
• the MTF/RER resolution assessment used by QA;
• the OpenGL 4.x rendering of multi-gigapixel rasters with quadtree LOD and asynchronous tile streaming;
• the GLSL shaders for cloud masks and raster overlays, and work on atmosphere and lighting of the globe view;
• orbit and imaging-swath visualization using STK Connect;
• the OpenMP and SIMD parallelization of the processing chain;
• TLS transfer and AES protection of imagery;
• software design documentation to ECSS requirements for the processing chain and rendering components.

I also took part in peer code reviews that checked MISRA C++:2008 and project coding-standard compliance, and I built and maintained the GTest regression suites for geometric accuracy.

Main contributions

Registration and mosaicking. I detected gradient-rich candidate points in overlaps and matched local patches by normalized cross-correlation. RANSAC removed inconsistent pairs before an affine transform aligned each strip. Per-band gain and offset were estimated from robust overlap statistics; seams followed low-error areas and were feathered across a narrow band to avoid visible transitions.

Resolution assessment. I used a slanted-edge workflow: locate and fit the edge, oversample pixel values by their distance from it to form the edge-spread function, differentiate it into the line-spread function and apply a Fourier transform to obtain MTF. RER came from the normalized response change around the edge. QA used MTF50, selected-frequency MTF and RER to track sharpness by campaign.

Large-raster rendering. Multi-gigapixel rasters were stored as a quadtree tile pyramid. The renderer selected a level from projected texel size, kept a parent tile visible until its children were resident and used overlapping borders to prevent cracks. Worker threads performed GDAL reads and decoding; the GL thread consumed a bounded PBO-backed upload queue with a per-frame budget. CPU and GPU LRU caches evicted least-recently-used tiles without blocking the frame loop.

Shaders. I wrote vertex and fragment shaders for globe geometry, cloud-mask coloring and alpha-blended raster overlays. The atmosphere used a lightweight single-scattering approximation with view-height and sun-direction terms, while directional lighting supplied terrain and globe shading. Compute shaders were used on the later UAV SIL project rather than in this raster viewer.

Orbits and swaths. I requested time-tagged ephemeris samples and access intervals from STK Connect in UTC. Earth-fixed positions were converted into the globe renderer's coordinate system, and swath boundary points were generated for the same timestamps so orbit, coverage and imagery stayed aligned.

Performance. The full-scene mosaic run took several hours. I parallelized it with OpenMP and SIMD intrinsics and brought it under forty minutes (the representative story below).

Security. I secured image transfer with OpenSSL TLS using certificate-chain and hostname validation. Stored imagery used AES-256-GCM; keys came from protected deployment configuration and were never embedded in the binary or stored beside the data.

Key engineering challenges

Scale versus interactivity. The data was much larger than GPU memory. Screen-space LOD, asynchronous loading, bounded uploads and two-level LRU caching ensured the render thread never waited for disk access or image decoding.

Globe precision. Earth-scale coordinates caused visible jitter near the camera when sent directly as floats. World positions remained double precision on the CPU and were rebased to camera-relative coordinates before conversion to GPU floats.

Speed without losing accuracy. The scalar implementation remained the reference. Tests compared optimized raster output with it using the established numerical tolerance, then ran geometric checks against ground control points and the existing GTest regression suite.

Formal process. Safety-critical C++ components were developed under MISRA C++:2008, while the project followed tailored ECSS-E-ST-40C and ECSS-Q-ST-80C processes with design documentation, reviews and verification evidence.

Representative investigation or delivery story

Situation: A full-scene mosaic run took several hours. This blocked analysts and QA, who needed products and quality results within the working day.

Task: Make the processing chain substantially faster without changing the verified geometric and radiometric results.

Actions: Stage timers and the Visual Studio profiler showed that radiometric normalization and seam blending dominated the per-pixel work. I split the scene into independent tiles, used OpenMP static scheduling, reorganized hot per-band values into contiguous aligned buffers and vectorized the arithmetic with SSE and AVX2. Tail elements used the scalar path. Each change was compared with the reference output and run through GTest and ground-control-point validation.

Result: The full-scene mosaic run came down from several hours to under forty minutes.

Testing, validation, and diagnostics

• GTest regression suites on the processing chain; they caught accuracy drift between releases.
• Validation of geometric accuracy against reference ground control points.
• Scalar-reference comparison using the established numerical tolerance, followed by the full GTest and ground-control-point regression suite.
• MTF/RER results used by QA as the image-quality evidence for each campaign.
• Peer and MISRA code reviews; Helix QAC static analysis with documented triage and deviations.
• ECSS verification evidence and review milestones.
• CPU stage timers and OpenGL timer queries to separate loading, upload and GPU rendering costs.

Outcome and main lesson

Analysts got seamless, verified mosaics in under forty minutes instead of several hours and an interactive globe for inspecting coverage and quality. The code base was delivered with design documentation and verification evidence to ECSS requirements.

Main lesson: in safety- or mission-relevant software, performance work is part of verification. Measure first, keep a reference implementation and let the regression suite decide whether an optimization is acceptable.

Scope boundaries

• Not claimed: onboard satellite software; the platform is ground segment.
• Not claimed: orbit determination or mission planning logic; STK was the source of ephemeris and access data, and my work was integration and visualization.
• Not claimed: ownership of the product-assurance process; I developed within ECSS-E-ST-40C and ECSS-Q-ST-80C as tailored by the project.
• Not claimed: DO-178C; ECSS is the closest equivalent.
• Rendering was geospatial visualization, not a certified out-the-window image generator.

Likely follow-up questions

• How was the LOD level chosen, and how were cracks and popping between levels handled? — Projected texel size; parent fallback until children were resident; overlapping tile borders and a short transition between levels.
• How did tile streaming avoid stalling the frame, and how did the cache evict tiles? — Background GDAL loading, bounded PBO upload queue and per-frame budget; least-recently-used eviction after tiles left the active view set.
• How did you handle floating-point precision on a globe? — Double-precision world coordinates on the CPU and camera-relative float coordinates on the GPU.
• Which shader stages did you write, and how were cloud masks and overlays blended?
• What exactly did you request from STK through Connect, and in which coordinate frame and time scale?
• Explain the slanted-edge method and what MTF and RER tell QA.
• How did you match tie points and reject outliers?
• Which OpenMP scheduling did you use, and how did you align data for AVX2?
• Which MISRA rules did you meet most often, and give an example of a justified deviation. — Explicit conversions, initialization, bounded pointer use and deterministic ownership; a checked narrowing conversion at a binary interface was documented and reviewed as a deviation.
• What did the software team deliver at the ECSS review milestones?

PROJECT 3. UAV DATA PROCESSING AND 3D RECONSTRUCTION SOFTWARE

Period: September 2018 - March 2020
Role: Software Engineer
Scope: payload firmware, sensor fusion, reconstruction pipeline and SIL environment

Short project summary

A platform for UAV-based surveying of buildings and industrial facilities. I wrote FreeRTOS firmware on STM32 that timestamped camera, IMU and LiDAR data on the GNSS PPS signal, implemented video stabilization and debayering with a real-time onboard preview, fused RTK GNSS and IMU in an error-state Kalman filter to reconstruct the trajectory and deskew LiDAR scans, and built the reconstruction stage on Open3D and PCL. I removed frame drops at peak sensor rates by replacing mutex hand-offs with lock-free ring buffers, and built an OpenSceneGraph-based software-in-the-loop rig with LiDAR emulation, so payload software was validated on the bench before flight tests.

Product and business context

Surveying and construction teams need accurate spatial data of large objects without manual on-site measurement. The UAV carries a sensor payload — camera, IMU, LiDAR and an RTK GNSS receiver — and the software turns a flight into dense point clouds and 3D models.

Accuracy depends on time: if camera frames, IMU samples and LiDAR points are not on one precise time base, the fused trajectory and every reconstructed surface are wrong. Flight time is also expensive, so software has to be validated on the bench before it flies.

System architecture and main components

• Payload hardware: camera, IMU, LiDAR, RTK GNSS receiver with a hardware PPS output; STM32 microcontroller for synchronization.
• Synchronization firmware: FreeRTOS on STM32, timestamping sensor events against the PPS signal.
• Flight-controller link: MAVLink ATTITUDE, GLOBAL_POSITION_INT and SYSTEM_TIME telemetry, plus COMMAND_LONG-based camera trigger and payload-control messages.
• Onboard video path: debayering of raw camera frames and video stabilization, with a real-time onboard preview.
• Processing pipeline in C++: bounded single-producer/single-consumer ring buffers with atomic head and tail indices and acquire/release ordering replaced mutex-based hand-offs.
• Sensor fusion: error-state Kalman filter fusing RTK GNSS and IMU into the flight trajectory; LiDAR deskew of each scan line against it.
• Reconstruction: Open3D and PCL for voxel downsampling, statistical outlier removal, normal estimation and point-to-plane ICP, generating dense point clouds and 3D models for review.
• SIL environment: OpenSceneGraph replay of simulated flight paths and sensor scenarios; a compute shader generated LiDAR rays and scene intersections, then noise and dropout were applied before packets entered the same timestamped interface as recorded data.
• Tooling: Linux, CMake, gcc, GDB, GTest, Git, Bitbucket, Jira, Confluence.

My role and ownership

I was a hands-on engineer from firmware to reconstruction. I personally developed:

• the FreeRTOS synchronization firmware on STM32;
• video stabilization and debayering with real-time preview;
• the RTK GNSS and IMU error-state Kalman filter and LiDAR deskew;
• the 3D reconstruction stage on Open3D and PCL;
• the lock-free ring buffers in the processing pipeline;
• the OpenSceneGraph SIL environment and the LiDAR emulation inside it;
• test-first GTest coverage of fusion and reconstruction.

I worked with the flight-control and surveying teams to agree sensor mounting, capture patterns and acceptance criteria for each scan campaign.

Main contributions

Time synchronization firmware. An STM32 timer input-capture channel latched each GNSS PPS edge. GNSS time arriving over UART supplied the absolute second, while timer ticks supplied sub-second timestamps. The ISR only captured the counter and notified a high-priority synchronization task. Sensor metadata moved through bounded queues, and timer scale was corrected from the measured tick count between successive PPS edges.

Video stabilization and debayering. I used bilinear Bayer interpolation for the preview path. Feature points were tracked with optical flow, outliers were rejected while estimating a 2D frame transform, and a low-pass-filtered camera path plus a small crop removed visible shake while staying within the preview frame budget.

Sensor fusion. The nominal state contained position, velocity, orientation and IMU biases; a 15-element error state represented position, velocity, small-angle attitude, accelerometer bias and gyro bias errors. IMU data drove prediction, while RTK GNSS position and velocity supplied updates. LiDAR points were deskewed with linearly interpolated position and quaternion slerp at each point timestamp; batch smoothing was reserved for offline final products.

Reconstruction. I voxel-downsampled deskewed scans, removed statistical outliers, estimated normals and used point-to-plane ICP to refine overlaps before merging the scans into dense point clouds and 3D models for review.

Lock-free pipeline. I replaced mutex-based hand-offs with lock-free ring buffers, removing frame drops at peak sensor rates (the representative story below).

SIL rig and LiDAR emulation. I built an OpenSceneGraph environment that replayed flight paths and sensor scenarios. A compute shader generated the LiDAR scan pattern and intersected rays with the scene. Gaussian range noise, small angular noise and a range/incidence-dependent dropout probability were applied before the returns were serialized into the same timestamped packet interface used by recorded data.

Key engineering challenges

One time base for all sensors. Small timing errors turn directly into geometric errors in the trajectory and the point cloud. Timing had to be captured as close to hardware as possible and be observable, so it could be checked on the bench.

Throughput at peak sensor rates. The pipeline dropped frames under peak load; replacing mutex-based hand-offs with lock-free ring buffers removed the drops.

Geometry diagnosis. A reconstructed object showed a doubled surface. I traced one feature through the raw scan, point timestamps, interpolated poses and the shared-frame transform. One scan used a stale pose because its timestamp lookup selected the previous interval. Correcting the interpolation removed the duplicate surface without hiding it through stronger filtering.

Pre-flight validation. The SIL rig reproduced flight paths and sensor scenarios on the bench so payload software could be validated before flight tests.

Representative investigation or delivery story

Situation: At peak sensor rates the processing pipeline dropped frames.

Task: Remove the frame drops from the processing pipeline.

Actions: Queue-depth and stage-timing measurements showed blocking at mutex-protected hand-offs. I replaced each one-producer/one-consumer link with a power-of-two bounded ring buffer using atomic head and tail indices with acquire/release ordering and cache-line separation. Capacity covered the worst measured processing burst; a full buffer incremented an overflow counter and rejected the newest item rather than blocking the pipeline.

Result: Frame drops at peak sensor rates disappeared.

Testing, validation, and diagnostics

• Processing modules developed test-first with GTest.
• Sensor fusion and reconstruction validated against recorded flight data and SIL-generated data.
• SIL rig used to replay exact failing scenarios and to test payload software before flight tests.
• STM32 debugging through GDB over the hardware debug interface; timer-capture diagnostics compared successive PPS intervals and sensor timestamps against the common counter.
• Acceptance criteria per scan campaign agreed with the flight-control and surveying teams and compared against real results.

Outcome and main lesson

The platform produced dense point clouds and 3D models on one consistent time base, the pipeline kept up with peak sensor rates, and payload software reached flight tests already validated on the bench.

Main lesson: measure where the waiting happens before optimizing computation, and never accept a plausible image as proof of correct geometry.

Scope boundaries

• Not claimed: autopilot or flight-controller firmware; my work was the payload side and MAVLink integration.
• Not claimed: airframe, payload hardware or PCB design.
• Not claimed: piloting or operating the UAV; flights were run with the flight-control team.
• Not claimed: surveying deliverables to end customers; these were owned by the surveying team.
• The SIL rig was a validation tool for payload software, not a certified flight simulator.

Likely follow-up questions

• How was the PPS edge captured on the STM32, and how was the absolute time attached to it? — Timer input capture latched the edge; the GNSS UART time message supplied the corresponding absolute second.
• What ran in the ISR, what ran in tasks, and how were priorities assigned?
• Why an error-state Kalman filter rather than a full-state EKF? What was in the state vector?
• How exactly was a LiDAR scan line deskewed?
• Explain your lock-free ring buffer: memory ordering, full and empty conditions, what happens when it is full.
• How did the LiDAR emulation produce returns, and what did the noise and dropout models look like? — Compute-shader ray intersections against the scene, Gaussian range and angular noise, and dropout probability increasing with range and unfavorable incidence.
• How did the SIL rig feed synthetic data into the same pipeline as real data?
• How did you find the doubled-surface error?
• What MAVLink messages did you use? — ATTITUDE, GLOBAL_POSITION_INT and SYSTEM_TIME for telemetry, plus COMMAND_LONG-based camera trigger and payload-control commands.
• What acceptance criteria did you agree with the surveying team?

CROSS-PROJECT CAREER NARRATIVE

The three projects form one line: real-time C++ on real hardware, 3D rendering and simulation, and validation on the physical system.

UAV (2018 – 2020) is where the foundations were built: sensor timing on an RTOS, sensor fusion, a real-time processing pipeline, 3D reconstruction and a software-in-the-loop rig that enabled bench validation before flight tests. It is the closest project to simulator thinking: a simulated world, emulated sensors and real software under test.

Satellite platform (2020 – 2023) added scale and formality: OpenGL 4.x and GLSL rendering of data far larger than GPU memory, performance engineering with OpenMP and SIMD, and delivery under MISRA C++:2008 and ECSS — requirements, design documentation, reviews, product assurance and verification evidence.

SIP phone (2023 – present) added full-stack product ownership on embedded Linux: from Linux drivers and the Yocto image through media and telephony middleware to the UI and the server-side provisioning tool, plus modernization of a product already in use by customers, CI and mentoring.

For Acron this maps directly: simulator visual systems need real-time rendering and large-data streaming (satellite); simulation and sensor or system emulation (UAV SIL); and aftermarket work on devices already installed at customer sites needs careful changes to mature systems validated on real hardware (SIP phone: .NET 8 migration, unified configuration, incremental refactor, customized SDK).

If asked why the projects changed: I moved from UAV payload software to a broader aerospace platform to deepen large-scale image processing, visualization and formal engineering practice. I later chose the SIP phone product to take end-to-end ownership of an embedded Linux device, including drivers, media, middleware, UI, provisioning and CI. Each move expanded the system scope while keeping real-time C++ and hardware integration at the center.

SAFE BOUNDARY STATEMENTS

ARINC 429, AFDX, CAN

I have not used ARINC 429, AFDX or CAN in a production project. My closest experience is embedded protocol and timing integration: MAVLink and GNSS PPS time synchronization on the UAV, and SIP, SDP, RTP, SNMP, DHCP and TFTP on the phone. I would need to learn the specific bus and its tooling, but the approach — data model, framing and timing rules, state ownership, error handling, a test setup with real or simulated peers — is familiar.

DO-178C and simulator qualification

I have not delivered software under DO-178C or simulator-qualification standards. The closest equivalent in my background is ECSS-E-ST-40C and ECSS-Q-ST-80C with MISRA C++:2008: requirements-based development, design documentation, peer reviews, product assurance and verification evidence.

Flight-simulator image generators

My rendering work is geospatial visualization (a 3D globe with multi-gigapixel rasters) and a simulation environment for validation, not an out-the-window image generator for a certified simulator. The core problems are the same: frame-time budget, level of detail, streaming large terrain and imagery data without stalls, shaders and synchronization between simulation state and rendering.

Graphics APIs

My production graphics experience is OpenGL 4.x, GLSL and OpenSceneGraph. I do not claim production Vulkan or DirectX experience.

RTOS

My RTOS experience is FreeRTOS on STM32. I do not claim production experience with VxWorks, INTEGRITY or other certified RTOSs.

Motion, control loading and environmental systems

I have not worked on simulator motion, control-loading or environmental control systems. The closest experience is integrating hardware-driven subsystems: peripheral drivers on the phone and sensor synchronization on the UAV.

Hardware and BSP

I write and integrate drivers for existing peripherals and work with the Yocto image; I do not claim hardware or PCB design, and I do not claim the vendor BSP layer as my own work.

Web front end

JavaScript, HTML and CSS are supporting-level work around web management. I am not a front-end developer.

People management

I lead code reviews and mentored two engineers; I have not been a formal people manager.

AI tools

I do not depend on AI tools to write production software. I would not use them with Acron code, documentation or programme information, in line with the programme's IP, safety and contractual restrictions.

CLOSING POSITIONING

I am a senior embedded C++ engineer whose work sits where real-time software, rendering and real hardware meet. I have rendered large data sets in real time with OpenGL 4.x and GLSL, built a simulation rig that validated real software against emulated sensors, written RTOS firmware and Linux drivers, and delivered under MISRA C++ and ECSS. On my current product I own changes across a complete embedded system that customers already run, and validate them on the physical device. That is the combination Acron's aftermarket work needs: changing mature simulators safely, on real hardware, with clear communication of risk. The programme-specific parts — avionics buses, DO-178C or simulator qualification, and the particular image generator and host architecture — are areas I would ramp up on quickly, and I state them openly from the start.
