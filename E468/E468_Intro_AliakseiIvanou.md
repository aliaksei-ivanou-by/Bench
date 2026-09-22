SELF INTRO

DOCUMENT INFORMATION

Request ID: E468
Candidate: Aliaksei Ivanou
Target role: Senior C++ Developer
CV source: E468 Aliaksei Ivanou (13, C++).pdf
Source request: E468_Request_AliakseiIvanou.md
Source profile: E468_Profile_AliakseiIvanou.md
Source analysis: E468_Request_Analysis_AliakseiIvanou.md
Preparation language: English
Delivery format: Full spoken version
Estimated duration: 7–8 minutes
Document status: Interview-ready

PURPOSE

This is the opening self-introduction for a Senior C++ Developer interview. It presents the complete career progression while leading toward the most recent embedded C++ and Qt experience.

TARGET POSITIONING

C++ Software Engineer with more than fourteen years across software engineering and research and development. The strongest evidence is recent embedded C++ and Qt delivery, safe work in mature C and C++ systems, and an earlier foundation in image-processing algorithms and hardware-facing engineering.

INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou. I am a C++ Software Engineer with more than fourteen years of overall experience across software engineering and research and development.
My main specialization is C and C++ development, but throughout my career I have also worked with Java, Scala, MATLAB, C#, JavaScript, and Ruby. My experience covers embedded systems, telecommunications, multimedia, backend development, desktop applications, image processing, and integration between software and hardware.
My first major software and algorithm-development period started in 2012 in the aerospace and Earth-observation domain. I primarily used MATLAB to develop and verify algorithms for radiometric correction, frame stitching, image sharpness, and automated linear-resolution measurement.
I also worked on image-type prediction and adaptive quantization. Another important task was developing an image-compression algorithm based on adaptive differential pulse-code modulation, or ADPCM. This part of my career gave me a strong background in algorithms, mathematical analysis, image processing, and working under strict computation and downlink constraints.
After that period, I worked on a database of Earth-observation satellites. That project was different from my main algorithmic work because it was a web application based on Ruby on Rails and PostgreSQL. I developed parts of the web interface, worked with the database structure and queries, and supported the migration of legacy data from Microsoft Access.
Later, I participated in a project for processing images received from UAV optical sensors. I developed several MATLAB modules, including a debayer algorithm for converting raw sensor data into full-color images, image-format conversion tools, an image-stabilization algorithm, and an image-fusion algorithm for combining information from multiple sensors.
After that, I moved toward more general C++ development. I worked on 3D reconstruction software that generated 3D models from data received from multiple 2D laser sensors. We used the Point Cloud Library for point-cloud processing and Open3D for visualization and analysis.
I also developed a desktop application for personal financial accounting. It was written in C++ and used FLTK for the graphical interface and SQLite for local data storage. I used CMake for the build system, Google Test for automated testing, and plog for logging and diagnostics. This project gave me experience with the complete lifecycle of a standalone desktop application, including UI development, business logic, database integration, testing, and debugging.
I then worked on a C++17 corporate system for the oil and gas industry. I implemented assigned backend functionality, made supporting JavaScript changes where a workflow crossed into the user-facing layer, fixed defects, estimated tasks, and removed obsolete code in controlled steps.
The next major project in my background was a large library management system with more than forty years of development history.
It was a complex legacy system that combined C, Java 11, Scala, MySQL, and PostgreSQL. I was one of the main contributors working with the C codebase. My responsibilities included investigating and fixing complex defects, implementing new functionality, improving performance, and developing features related to socket-based communication.
I also implemented a targeted Scala API request backed by C processing, made related Java changes when a complete task crossed the native boundary, and worked within existing Jenkins and AWS-hosted Linux build and deployment environments. In addition to development, I estimated tasks and participated in mandatory cross-company code review.
The main challenge on that project was making changes safely. Because the system was mature and had many dependencies, even a small modification could affect existing functionality. Before changing the code, I usually had to investigate the complete execution flow, understand the related database operations and communication logic, and evaluate possible side effects. This experience taught me how to work effectively with large legacy systems while preserving backward compatibility.
My most recent project is an embedded platform for SIP desk phones. The product included models with and without cameras and supported audio calls, video calls, call hold and transfer, conferences, phonebook access, direct IP dialing, remote configuration, and automatic provisioning.
The main technology stack included C++17, Qt 5, Qt Widgets, Embedded Linux, Yocto, Linphone SDK, SIP, SDP, RTP, WebRTC, Qt Multimedia, mediasoup, and libmediasoupclient. The target hardware was based on the NXP i.MX platform.
My main responsibility was the call-handling logic of the native application. One of my major tasks was refactoring the existing call flow toward clearer session, service, SDK-adapter, and presentation boundaries.
Originally, UI rendering, call state, user actions, media negotiation, and direct interaction with Linphone SDK were tightly coupled. This made the code difficult to understand and made changes risky. I separated these responsibilities incrementally into clearer domain, presentation, and SDK-integration layers.
Because this was an existing product, we could not simply rewrite the entire application. The refactoring had to be incremental and preserve existing UI behavior and Qt signal compatibility.
The call and registration flows were event-driven and asynchronous. I worked with SDK callbacks, Qt object ownership, queued signal delivery, and background operations while keeping state transitions visible and testable. This is my strongest concurrency evidence; I do not present it as years of highly parallel Windows desktop development.
I also worked on complex video-call scenarios, including held calls, second-line calls, remote hangups, active video-stream changes, conference layouts, and stale UI state. The main challenge was keeping application state, Linphone SDK state, UI state, and actual media state synchronized.
Another responsibility was phone-side WebRTC conferencing. I worked on conference lifecycle, participant presentation, video-tile layouts, camera selection, rendering, and audio and video controls.
I also implemented a registration watchdog and primary and backup SIP failover and failback behavior in customized liblinphone and integrated the resulting state into the Qt application and provisioning paths.
In addition to the C++ application, I participated in migrating a WinForms provisioning utility from .NET Framework 4.8 to .NET 8. The provisioning functionality used SNMP, DHCP, TFTP, and SQLite. I also worked on Yocto and BitBake integration, systemd service configuration, and application deployment to the embedded NXP i.MX target.
Overall, I would describe myself as an engineer who is comfortable working with complex existing systems. I enjoy investigating difficult problems, understanding how different components interact, and improving the architecture without breaking existing behavior.
My strongest areas are C and C++, debugging, legacy-code modernization, multimedia and networking integration, and communication between software and hardware. I am especially interested in projects where performance, reliability, and maintainability are important.
My direct security experience is narrower than a dedicated cybersecurity role. It includes security-aware work around authentication context, certificates, TLS and secure-media settings, provisioning trust boundaries, and safe maintenance of mature native code. I have not owned BSI IT-Grundschutz implementation or a broad vulnerability-remediation program.
At this stage of my career, I am looking for technically challenging work where I can use my C++ and system-development experience, contribute to architectural decisions, and continue working with complex products and modern technologies.

INTERVIEW BOUNDARIES

• The E468 CV is the source of truth for this interview. Periods, project order, role labels, and technology lists follow the CV.
• Fourteen-plus years refers to overall software-engineering and R&D experience, not fourteen years of commercial C++ employment.
• The CV lists selected projects rather than continuous employment. If asked about the break between March 2017 and August 2018, or about the shorter breaks, explain that the 2012–2020 entries are workstreams inside one continuous employment.
• If an interviewer asks to reconcile real assignment dates, answer directly: the library assignment ended in April 2024, the SIP assignment began in May 2025, and employment continued between assignments.
• For GStreamer, V4L2, Conan, and ReSharper C++: do not defend the CV entry and do not disown the CV. Say that it was part of the project environment, state exactly what I did myself, and name the boundary.
• The submitted CV presents the latest SIP project as May 2025 – present. The opening script deliberately avoids giving a conflicting end date.
• The submitted CV labels the two latest project roles as Senior Software Engineer. Do not add a different formal grade to the spoken introduction; explain concrete scope and ownership instead.
• Scala work was targeted API integration, and AWS work used existing build and deployment infrastructure.
• Do not claim hands-on GStreamer, direct V4L2 API work, Conan, or broad WebRTC server ownership.
• The documented English level is B2, not C1, and German is not listed.
• Do not claim BSI IT-Grundschutz implementation, a dedicated cybersecurity role, production Claude Code use, or years of highly parallel Windows desktop development.

EXPECTED FOLLOW-UP TOPICS

• Incremental call-subsystem refactoring in Qt.
• SIP registration watchdog and primary and backup failover and failback.
• Legacy C89 debugging with gdb, logs, and core dumps.
• Yocto image integration and target-device validation.
• ADPCM-family compression and automated image-quality measurement.
