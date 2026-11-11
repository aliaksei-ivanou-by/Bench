PROJECT LEGEND
Candidate: Aliaksei Ivanou

1. SIP-BASED PHONE SOFTWARE
Period: 05.2022–present
Role: Software Engineer
Status: current
Project environment from the CV: C++17, C#, JavaScript, Embedded Linux, Yocto, Qt Designer, .ui, systemd, CMake, qmake, GCC, gdb, Valgrind, Qt Test, Qt Creator, GStreamer, Qt 5.15.7, Qt Widgets, QSS, .NET 8, Node.js, WinForms, V4L2, Qt DBus, Qt WebSockets, WebRTC, Qt Multimedia, Linphone-SDK, liblinphone, mediasoup, libmediasoupclient, SQLite, SDP, SIP, RTP, SNMP, DHCP, TFTP, BitBake, NXP i.MX, Asana, Git, GitLab, Qt Model/View.

CONTEXT, ARCHITECTURE AND TEAM

An enterprise desk-phone platform provides audio and video calling, conferences and centrally managed configuration. Office users interact with the phone; administrators provision and maintain fleets. The existing product combines a C++17 and Qt Widgets application, a customized Linphone SDK, embedded Linux built with Yocto/BitBake for NXP i.MX, and a Windows WinForms provisioning utility.

The Qt application converts user actions into SDK operations and maps asynchronous SIP, call and media events back to models and screens. Device settings and generated provisioning files connect the application and SDK; audio, video, GPIO and the graphical environment depend on the target image and services. The browser interface and its REST implementation belonged to another developer.

Our delivery team grew from three to four C++ engineers. The customer team typically included a project manager, two to four C++ developers, a web developer and two to four QA engineers. People worked across distributed locations; I coordinated application and SDK changes with the customer developers and device scenarios with QA. My role was a hands-on software engineer; an additional internal People Lead group was separate from the customer project team.

I worked on call and account models, SDK-side registration watchdog and failover, application integration, provisioning and target diagnosis. The inherited platform and BSP were shared foundations, not a platform I built alone. Tests included focused Qt Test and MSTest checks, review, SIP and system logs, gdb/gdbserver and physical-phone scenarios. The broad call-architecture refactor was completed as internal engineering work.

PROJECT STORIES

1.1. Registration failover

The phone needed to remain registered when the primary SIP server failed and return when it recovered. Storing two addresses alone was insufficient: the SDK, active-server display, credentials and generated configuration had to agree. I first tried rotation in the Qt application, but reverted it because registration lifecycle and asynchronous retries were owned by the SDK. I implemented a watchdog and failover/failback state machine in the customized liblinphone, exposed active and backup server information, integrated those APIs into the application and aligned settings and provisioning. I also changed AuthInfo to carry the backup domain for differing authentication realms. We checked server loss and recovery, registration, authentication and displayed state on phones, using SIP logs and active-proxy diagnostics. The integrated SDK approach made server selection visible across layers; it also required maintaining project-specific SDK changes.

1.2. Image and startup integration

A Qt application can appear broken when its actual dependency is missing from the image or the graphical service is not ready. With an inherited Yocto platform, replacing the image stack would have been disproportionate; I worked inside existing layers, adapting packaging and startup configuration. I traced the path from BitBake recipe and installed files through the model-specific image to systemd and the Weston/Wayland environment, using build output, target logs and remote debugging. Checks on the physical ARM device established whether files, services, display and hardware were available at the right point. The lesson was to locate the failing boundary before changing application code; a successful cross-build alone cannot establish that the complete device starts correctly.

1.3. Call architecture

Call state was spread across inherited Qt Widgets flows while SDK callbacks could arrive asynchronously. A direct rewrite risked breaking existing interactions and QObject signal connections, so I decomposed the code incrementally into sessions, services, SDK adapters and presentation boundaries. I kept existing UI behavior in view while moving callers and used focused tests and device scenarios to check state transitions. Held calls, remote hangup and media changes illustrated why UI state could not be treated as the source of truth. The broader restructuring was completed internally; the practical result was a clearer boundary for reasoning about call state and regression.

EXPANDED TASK ANSWERS

1.1. Call handling architecture

I separated call/session state and SDK interaction from rendering and user actions. This made asynchronous events easier to trace and let the existing UI consume a clearer model; the larger refactor remained internal.

1.2. BitBake builds for SDK and dependencies

I adapted inherited recipes and packaging for the customized SDK and dependencies on the i.MX target. I checked build output and target behavior; the platform and its cross-compilation foundations already existed. I authored and maintained custom BitBake recipes for cross-compiling the modified Linphone SDK and its dependencies for NXP i.MX ARM, including build-flag configuration to optimize the embedded memory footprint.

1.3. Incremental Qt Widgets decomposition

I moved responsibilities toward domain, presentation and SDK integration boundaries in reviewable steps, preserving interaction and QObject connections. Focused tests and call scenarios helped identify regressions during migration.

1.4. Yocto layers and SDK packaging

I worked within existing meta-layers on recipes, dependencies and image contents for liblinphone and related components. I verified that the resulting packages were present and usable on target rather than treating a completed build as sufficient. I developed custom Yocto recipes and .bbappend files in dedicated meta-layers to enable liblinphone cross-compilation.

1.5. Video and conference edge cases

I worked with call and conference UI state around held and second calls, remote hangups and media changes. I checked the relationship between SDK events and visible state in device scenarios, where event order and teardown can differ. The work covered held calls, second-line calls, remote hangups, stale overlays and switching the active video stream.

1.6. SIP backup and authentication

I implemented SDK registration watchdog and failover/failback, integrated the APIs and added a backup-domain field to AuthInfo. I checked authentication and state when switching servers. The SDK changes included support for authorization with different HA1 hashes for primary and backup servers when their realms differed.

1.7. WebRTC conferencing

I integrated and debugged the phone-side WebRTC/mediasoup conference path, including the relationship between joining, participant state and media. My server contribution was limited to the initial server; another team handled the later server work. The phone-side work covered conference creation and joining, incoming invitations, participant rosters, SIP/IP/phonebook add dialogs, status strip, controls, video tiles and audio/video device controls.

1.8. GPIO and hardware integration

I worked on Qt application integration with GPIO and hardware events, using target scenarios and logs to diagnose behavior. Hardware event delivery and object lifetime had to be considered alongside asynchronous UI work. I reworked the libgpiod C++ layer for handset hook-switch edge events and the RGB status LED, moving event handling to a dedicated QThread, implementing a thread-safe singleton, and correcting a mutex deadlock and memory leak.

1.9. Provisioning utility

I migrated the inherited WinForms utility from .NET Framework 4.8 to .NET 8 and worked on discovery and configuration using SNMP, DHCP, TFTP and SQLite. I checked generated settings against the phone; older encrypted BinaryFormatter files are not compatible with the later JSON reader. The work also unified project file formats across the device ecosystem.

1.10. Device diagnostics

I used application, SIP and system logs and added active-proxy diagnostics to make failover state observable. Reproduction required matching the device, firmware, account and network conditions; logs were correlated with target behavior. I implemented categorized QLoggingCategory output to journald with size limits to protect flash, and a downloadable diagnostics bundle containing journal entries, liblinphone logs, sanitized configuration and SIP traces.

1.11. Qt Test coverage

I added and maintained focused Qt Test checks for local logic, models and controllers, including call-session changes. The tests covered the extracted call-state and conference domain layer. These checks supported refactoring, while physical devices remained necessary for media, hardware and boot scenarios.

1.12. Yocto and target services

I adapted inherited image recipes, packages and startup services and debugged integration on i.MX devices. I traced dependencies across image contents, systemd, the graphical environment and application instead of assuming every failure was a Qt defect.

FOLLOW-UP TOPICS

SDK registration and authentication; Qt signals and object lifetime; BitBake packaging and target sysroots; systemd and Wayland startup; physical-device testing.

2. LIBRARY SYSTEM
Period: 05.2019–04.2022
Role: Software Engineer
Status: completed
Project environment from the CV: C, Java 11, Scala, gdb, MySQL, PostgreSQL, Amazon Web Services, Git, Bitbucket.

CONTEXT, ARCHITECTURE AND TEAM

An established library-management product supported catalogue and other library workflows. The system combined a C89 backend with Java data services, Scala APIs and a user interface, using PostgreSQL and remaining MySQL models. Requests and failures could cross several processes and language boundaries.

Three C developers, including me, shared backend work; the delivery team also had three Java developers, four QA engineers, a business analyst and a project manager/Scrum master. The customer group had three, later four developers, a development manager and a product owner. The distributed team worked across Belarus, Poland, Ukraine and other locations.

I implemented features, fixes and refactoring in C, occasionally changing Java and Scala when a task crossed boundaries. I used service logs, gdb, core dumps and Valgrind on Linux hosts. QA performed regression checks; changes required review from the assigned delivery and customer reviewers. Existing Bitbucket, Jenkins and deployment workflows supported builds and validation.

PROJECT STORIES

2.1. Cross-service defect investigation

A user-visible failure could appear in a Java or Scala layer while the cause was in inherited C code. Changing the visible endpoint first risked masking the cause. I reproduced the workflow, correlated logs across service boundaries and narrowed the failing C path before using gdb, a core dump or Valgrind where memory behavior was involved. Fixed-size C buffers and legacy assumptions made boundary conditions important. I made a focused change, submitted it for review and worked with QA on the affected workflow and regression. This method provided an evidence-based fix without assuming that the layer reporting the symptom owned the defect.

EXPANDED TASK ANSWERS

2.1. Legacy defects and performance

I investigated complex defects in the C backend with logs and native debugging, then made focused changes to preserve established behavior. Performance claims were evaluated within the task rather than as a system-wide benchmark. I optimized and maintained the codebase by resolving complex defects and implementing performance improvements.

2.2. Service communication

I followed requests through existing interfaces between C, Java and Scala and changed the relevant components when a feature crossed those boundaries. I coordinated integration and checked end-to-end behavior with logs and QA. I developed backend and frontend features for socket-based communication.

2.3. C backend contribution

As one of three C developers I implemented features, fixes and refactoring in the shared C89 codebase. I coordinated changes and review with the team. I led development efforts as a key C contributor, driving implementation of critical features and solutions.

2.4. Scala API

I made occasional task-specific Scala API and Swagger changes, including calls into C-side behavior. I checked that the interface and backend agreed and relied on review and integration testing. I refactored the Scala API to improve maintainability and scalability.

2.5. Build and deployment workflow

I used existing Jenkins builds and nightly or on-demand deployments on AWS Linux hosts for development and validation. I inspected build results and environment behavior; I worked with AWS pipelines to automate CI/CD processes for smoother deployments and shorter development cycles.

2.6. Database-backed workflows

I worked on application behavior connected to Java data services using PostgreSQL and remaining MySQL models. I traced data across service boundaries when a task required it and checked the resulting workflow. I modified database tables and improved schema design to support new features and updated workflows.

2.7. Task estimation

I estimated my own work in a two-week sprint process, accounting for investigation, implementation, review and QA. Grooming and daily communication helped revise scope as details became clear.

2.8. Code reviews

Changes were reviewed by assigned colleagues and customer developers; required reviewers approved before merging. I used review to check behavior, maintainability and integration assumptions and to share knowledge.

2.9. Legacy refactoring

I refactored inherited C code in small changes alongside features and fixes, preserving service compatibility and established workflows. Review, builds and QA regression helped control the risk.

FOLLOW-UP TOPICS

C89 buffers and memory; gdb and Valgrind; cross-service diagnosis; Scala/C integration; review and regression.

3. 3D RECONSTRUCTION SOFTWARE FOR INDUSTRIAL APPLICATIONS
Period: 03.2019–05.2019
Role: Software Engineer
Status: completed
Project environment from the CV: C++, Visual Studio, PCL, Open3D, Git.

CONTEXT, ARCHITECTURE AND TEAM

An industrial measurement R&D prototype combined several standard 2D laser profile scanners to produce a 3D model. Its users were internal measurement and research engineers evaluating reconstruction quality on Windows workstations.

Each scanner produced profiles in its local coordinates. The C++17/Qt application loaded or acquired profiles, transformed them into a common frame using scanner geometry, and used PCL for point-cloud filtering, downsampling, alignment and reconstruction. Open3D supported comparison and visualization. Scanner hardware, firmware and mechanical mounting belonged to other specialists.

I worked in a small R&D group alongside software, research, optics and hardware engineers. I implemented the application-side pipeline and coordinated geometric assumptions with the engineers working on the setup. Recorded datasets, intermediate visualization and known physical dimensions supported repeatable checks; the outcome was an R&D prototype rather than a claim of a released product.

PROJECT STORIES

3.1. Combining scanner views

Separate profiles could not simply be concatenated: an error in sensor position or orientation appeared as doubled or smeared surfaces. Rather than judge only the final mesh, I made the coordinate transformation and intermediate cloud inspectable, using measured setup geometry and recorded inputs. After bringing profiles into a shared frame, I applied PCL processing and compared intermediate and final results visually and against known dimensions. Filtering and downsampling balanced point density with an interactive desktop working set; missing coverage remained a physical limitation. This made geometric errors visible before later processing could hide them.

EXPANDED TASK ANSWERS

3.1. Multi-sensor reconstruction

I transformed 2D sensor profiles into a common 3D frame and assembled a model for engineers to inspect. Calibration assumptions and incomplete coverage affected the result, so I checked stages on recorded inputs.

3.2. PCL processing

I used PCL for filtering, downsampling, alignment and surface reconstruction. I compared intermediate clouds to avoid treating an error in input geometry as a reconstruction-algorithm problem.

3.3. Open3D evaluation

I integrated Open3D alongside PCL for visualization and analysis during evaluation. This gave engineers another view of the data and reconstruction without making it the primary pipeline.

3.4. Visual Studio development

I used Visual Studio for C++ development and debugging of the Windows prototype. Recorded datasets and stage-by-stage inspection made repeated checks practical.

FOLLOW-UP TOPICS

Coordinate transforms and sensor geometry; PCL processing stages; filtering versus detail; prototype validation.

4. SOFTWARE MODULES FOR UAV
Period: 08.2017–12.2018
Role: Software Engineer
Status: completed
Project environment from the CV: MATLAB, PostgreSQL, Git, Bitbucket.

CONTEXT, ARCHITECTURE AND TEAM

The optical payload of a UAV required useful imagery from sensor output despite platform motion and different image formats. Internal instrument and test engineers used the algorithms and evaluated output; the flight crew owned aircraft operations.

I developed MATLAB algorithms for debayering, conversion, stabilization and image fusion. The image pipeline connected sensor output, color reconstruction, alignment and downstream analysis. I also worked on IMU-to-camera calibration and frame-centre coordinates; the flight-software group owned target implementation.

I worked with researchers, optical, electronics, mechanical and software engineers in a Minsk design organization. Responsibilities were divided by discipline; I owned algorithm design and verification and operated the optical payload during more than 30 UAV test flights. Reference imagery, calibration checks and flight data complemented each other.

PROJECT STORIES

4.1. Stabilization and flight validation

Motion and misalignment could make otherwise valid sensor data difficult to interpret, while flight opportunities were limited. I developed and evaluated stabilization and fusion algorithms in MATLAB on representative imagery, then compared behavior with data from actual payload operation. IMU-to-camera alignment mattered because correct sensor readings alone did not guarantee correct frame-centre coordinates. I worked with the relevant engineers on calibration and operated the optical payload during test flights. The resulting checks connected algorithm output to physical conditions; further target implementation remained with the flight-software group.

EXPANDED TASK ANSWERS

4.1. UAV image-processing modules

I developed MATLAB algorithms for the optical system, combining sensor processing with verification on representative data. I coordinated algorithm handover with the engineers responsible for the rest of the instrument.

4.2. Debayering

I designed and evaluated conversion of Bayer sensor samples into a color image. I inspected image quality and artifacts on reference data so reconstruction choices could be compared.

4.3. Image format conversion

I worked on image-format conversion within the MATLAB processing workflow. Correct interpretation of input and output data was necessary for later stages to consume the image consistently.

4.4. Image stabilization

I developed and evaluated stabilization algorithms to reduce motion-induced distortion in real-time UAV video. I used representative imagery and flight-test observations to judge whether the correction preserved useful detail.

4.5. Image fusion

I designed and verified image-fusion algorithms in MATLAB, combining information from multiple sensors to improve detail and contrast for target analysis. Alignment and comparable inputs were necessary before combining information; I evaluated output against reference imagery and the needs of the optical workflow.

FOLLOW-UP TOPICS

Bayer patterns; stabilization and alignment; fusion inputs; calibration and flight-test validation.

5. REMOTE SENSING SATELLITES DATABASE
Period: 03.2016–03.2017
Role: Software Engineer
Status: completed
Project environment from the CV: Ruby, Ruby on Rails, PostgreSQL, MS Access.

CONTEXT, ARCHITECTURE AND TEAM

The project provided internal engineers with a shared reference database of remote-sensing satellites, missions and instrument parameters. Before a queryable reference system, relevant information was spread across documents and spreadsheets.

I designed and implemented a Ruby on Rails web application backed by PostgreSQL. Users could work with structured satellite records and retrieve parameters through the interface. The system also integrated MS Access for legacy data support and migration.

I worked in the same Minsk research organization with engineers who supplied and used the reference information. My responsibility was the web application and database; subject specialists supplied domain context. I checked records and application workflows with representative data and user feedback.

PROJECT STORIES

5.1. Making reference data queryable

Engineers needed satellite and mission parameters without repeatedly searching scattered documents. I chose a structured PostgreSQL database with a Rails interface, representing the reference data as records that users could maintain and query. I worked with domain specialists to understand the parameters, implemented the application and checked representative records and workflows. The benefit was a shared, queryable reference source; it was a satellite-parameter system rather than an imagery archive.

EXPANDED TASK ANSWERS

5.1. Rails web interface

I built a Rails interface for maintaining and retrieving satellite reference records. I checked that user workflows and displayed fields corresponded to the underlying data.

5.2. PostgreSQL reference database

I designed the PostgreSQL-backed data structure for satellite and mission parameters and used it from the Rails application. Structured records made the information queryable; no quantified retrieval improvement is claimed.

5.3. Existing data environment

The organization also had historical MS Access databases. I built the Rails/PostgreSQL reference database and arranged satellite information for its users. I integrated MS Access for legacy data support, migration and compatibility with existing systems.

FOLLOW-UP TOPICS

Reference-data modelling; Rails and PostgreSQL; user workflows and data validation.

6. SOFTWARE FOR PROCESSING AND ANALYSIS OF SATELLITE EARTH OBSERVATION IMAGES
Period: 08.2012–03.2016
Role: Software Engineer
Status: completed
Project environment from the CV: C++, MATLAB, System Tool Kit, CMake, Visual Studio, PostgreSQL, MS Access, Jira, Git.

CONTEXT, ARCHITECTURE AND TEAM

Earth-observation instruments produced detector data that required radiometric and geometric processing, bandwidth-efficient transmission and evaluation of image quality. Internal instrument, imaging and test engineers used the results; mission data users depended on image fidelity.

I designed MATLAB algorithms for frame stitching and brightness matching, automated linear-resolution assessment, image-type prediction and an ADPCM-family compression method. A multi-detector focal plane produced image segments; the processing path corrected and matched them, while compression had to fit the onboard compute and downlink budget. The flight-software group implemented algorithms on the target.

I worked in a Minsk research department with optical, electronics, software and test engineers. My contribution was algorithm design and verification, while hardware and flight software belonged to their specialists. Reference imagery, known targets, comparison with existing analysis and flight-test imagery provided validation.

PROJECT STORIES

6.1. Compression under an onboard budget

Downlink capacity required lossy compression, but the available onboard computation ruled out approaches that were too expensive even if they offered better quality per bit. I designed and verified a differential predictive algorithm in the ADPCM family in MATLAB, achieving a 3–4x compression ratio within the documented constraints. A later image-type prediction and adaptive-quantization step improved quality at a matched ratio. I compared results on reference images and passed the algorithm and verification to the flight-software group for target implementation. The tradeoff was between fidelity, ratio and computation, not a search for the most complex codec.

6.2. Stitching and resolution

A frame consisted of segments from different detectors; geometric alignment alone left visible brightness discontinuities. I combined feature-based alignment with radiometric matching and checked the result against reference imagery. Separately, manual resolution assessment made flight-test analysis dependent on the operator. I defined and implemented automated assessment in MATLAB and compared it with known targets and existing manual analysis. The results were a more consistent stitched image and repeatable measurements; both demonstrate why validation must address the physical imaging chain as well as the algorithm.

EXPANDED TASK ANSWERS

6.1. Brightness and detector correction

I worked on radiometric correction and matching across detector segments as part of stitching. I compared seams and reference imagery, since correct geometry alone did not eliminate brightness differences.

6.2. Linear resolution assessment

I developed automated resolution assessment in MATLAB for flight-test imagery. I checked repeatability against known targets and manual analysis; the work reduced dependence on the individual operator. I applied the sharp edge method to linear-resolution analysis.

6.3. Image sharpness and quality

I assessed achieved image resolution using repeatable criteria and representative targets. I compared results with reference data rather than inferring image quality from a single visual impression. I developed algorithms for image sharpness and edge clarity to support resolution measurement.

6.4. Image characteristics and quantization

I worked on predicting image type and adapting quantization to image characteristics. I assessed quality at a matched compression ratio to make the comparison meaningful. The task included analysing Earth-observation data and estimating the albedo range to predict quantization ranges and support sensor calibration.

6.5. Automated quantization adaptation

I implemented image-type prediction and adaptive quantization in MATLAB. Reference images and comparison under the same compression conditions supported the evaluation. I automated the prediction of quantization ranges to streamline the workflow.

6.6. ADPCM-family compression

I designed and verified a differential predictive compression algorithm in MATLAB for a limited onboard compute budget. The documented ratio was 3–4x; the flight-software team implemented the target version. The compression design used ADPCM with multiple quantizers to support different data sizes.

FOLLOW-UP TOPICS

Radiometric versus geometric alignment; resolution validation; adaptive quantization; ADPCM and onboard compute constraints.
