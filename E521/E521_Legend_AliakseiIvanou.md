PROJECT LEGEND
Candidate: Aliaksei Ivanou

1. SIP-BASED PHONE SOFTWARE
Period: 05.2022–present
Role: Software Engineer
Status: current
Project environment from the CV: C++17, C#, JavaScript, Embedded Linux, Yocto, Qt Designer, .ui, systemd, CMake, qmake, GCC, gdb, Valgrind, Qt Test, Qt Creator, GStreamer, Qt 5.15.7, Qt Widgets, QSS, .NET 8, Node.js, WinForms, V4L2, Qt DBus, Qt WebSockets, WebRTC, Qt Multimedia, Linphone-SDK, liblinphone, mediasoup, libmediasoupclient, SQLite, SDP, SIP, RTP, SNMP, DHCP, TFTP, BitBake, NXP i.MX, Asana, Git, GitLab, Qt Model/View.

CONTEXT, ARCHITECTURE AND TEAM

Before our team joined, there was a basic Yocto platform skeleton. It did not include Linphone SDK, WebRTC or mediasoup. Our team added those components to the phone image, including their build dependencies, packages and the settings needed to run them. My personal contribution covered application/SDK work, BitBake metadata, packaging, image integration and testing on the device; the stack integration was a team effort.

An enterprise desk-phone platform provides audio and video calling, conferences and centrally managed configuration. Office users interact with the phone; administrators provision and maintain fleets. The existing product combines a C++17 and Qt Widgets application, a customized Linphone SDK, embedded Linux built with Yocto/BitBake for NXP i.MX, and a Windows WinForms provisioning utility.

The Qt application converts user actions into SDK operations and maps asynchronous SIP, call and media events back to models and screens. Device settings and generated provisioning files connect the application and SDK; audio, video, GPIO and the graphical environment depend on the target image and services. The browser interface and its REST implementation belonged to another developer.

Our delivery team grew from three to four C++ engineers. The customer team typically included a project manager, two to four C++ developers, a web developer and two to four QA engineers. People worked across distributed locations; I coordinated application and SDK changes with the customer developers and device scenarios with QA. My role was a hands-on software engineer; an additional internal People Lead group was separate from the customer project team.

I worked on call and account models, SDK-side registration watchdog and failover, application integration, provisioning and debugging on the device. The inherited platform and BSP were shared foundations, not a platform I built alone. Tests included focused Qt Test and MSTest checks, review, SIP and system logs, gdb/gdbserver and physical-phone scenarios. The broad call-architecture refactor was completed as internal engineering work.

PROJECT STORIES

1.1. Registration failover

The phone needed to remain registered when the primary SIP server failed and return when it recovered. Storing two addresses alone was insufficient: the SDK, active-server display, credentials and generated configuration had to agree. I first tried rotation in the Qt application, but reverted it because registration lifecycle and asynchronous retries were owned by the SDK. I implemented a watchdog and failover/failback state machine in the customized liblinphone, exposed active and backup server information, integrated those APIs into the application and aligned settings and provisioning. I also changed AuthInfo to carry the backup domain for differing authentication realms. We checked server loss and recovery, registration, authentication and displayed state on phones, using SIP logs and active-proxy diagnostics. The integrated SDK approach made server selection visible across layers; it also required maintaining project-specific SDK changes.

The alternative at the UI layer was attractive because it was close to the displayed account settings, but it duplicated decisions already made by the SDK and made asynchronous recovery difficult to reason about. Moving the state machine into the SDK centralized registration behavior; the tradeoff was carrying and testing a customized SDK. The device checks had to cover transitions in both directions, since successful failover alone would not establish correct recovery.

1.2. Image and startup integration

A Qt application can appear broken when its actual dependency is missing from the image or the graphical service is not ready. We retained the initial Yocto skeleton and extended it with Linphone SDK, WebRTC and mediasoup. My work included packaging and startup integration for the resulting phone image. I traced the path from BitBake recipe and installed files through the model-specific image to systemd and the Weston/Wayland environment, using build output, target logs and remote debugging. Checks on the physical ARM device established whether files, services, display and hardware were available at the right point. The lesson was to locate the failing boundary before changing application code; a successful cross-build alone cannot establish that the complete device starts correctly.

An alternative would have been to debug only the application or replace the existing image structure, but either could miss the package or service boundary and increase the scope of the change. Following the existing image path allowed a focused integration change, at the cost of checking several layers and a physical device. The same symptom must be compared with boot and service evidence before attributing it to application logic.

1.3. Call architecture

Call state was spread across inherited Qt Widgets flows while SDK callbacks could arrive asynchronously. A direct rewrite risked breaking existing interactions and QObject signal connections, so I decomposed the code incrementally into sessions, services, SDK adapters and presentation boundaries. I kept existing UI behavior in view while moving callers and used focused tests and device scenarios to check state transitions. Held calls, remote hangup and media changes illustrated why UI state could not be treated as the source of truth. The broader restructuring was completed internally; the practical result was a clearer boundary for reasoning about call state and regression.

Keeping the existing widget-centered flow would avoid migration work but retain the coupling between presentation and SDK state. A complete rewrite would enlarge the regression surface, so the incremental boundary was the practical compromise. Tests and call scenarios had to verify both the new state path and unchanged user interactions; the internal status of the broad refactor remains distinct from a released feature.

1.4. From manually prepared update.sh packages to version-aware incremental updates

SITUATION

- Routine updates already used partial packages installed by update.sh. Each package contained selected programs, libraries, scripts or resources, and its script was prepared by hand. Full firmware installation was a separate reflashing procedure. Later, we moved routine updates into the .NET Autoprovisioning Manager, which used each phone’s installed version.

PROBLEM AND WHY IT MATTERED

- The problem was the assumptions hidden in each manual script. A package made for one starting version could miss files or install incompatible ones on another phone. We needed a common way to choose the right update and return that particular phone to its previous software if installation failed.

ALTERNATIVES AND DECISION

- We could keep separate manual scripts for every version change or require intermediate upgrades. Instead, the Windows tool read the installed version and device/platform identity. It then built a package for that phone and the selected target release. The main improvement was choosing and preparing the correct update automatically, not replacing full images with small packages.

PACKAGE GENERATION

- The build system kept the exact files and inventories of released versions. The package builder compared the installed release with the target release. It included additions, replacements and deletions, omitted unchanged files and used complete files or useful binary deltas. The signed manifest listed versions, compatibility, paths, operations, permissions and file checksums. Deltas also required the exact old-file checksum. It reused built files rather than compiling C++ for every phone.

PERSONAL ACTIONS AND TEAM COORDINATION

- I extended the .NET workflow to read the installed version, start package creation, track delivery and show the result after reconnecting. I agreed the package format with the phone/build engineers. A separate updater on the phone checked the package and old files, then prepared the full new release in staging. A mismatched old file required a suitable complete-file package or recovery. The phone kept operation state even if the Windows tool closed.

ACTIVATION AND RECOVERY

- Before switching, the phone kept its exact old program, matching libraries, scripts, resources, permissions and links. It waited until no call was active, blocked conflicting call actions, stopped the application and activated the new release. Failed local startup or SDK initialization caused rollback; the administrator could also request it. The recovery copy stayed until the next update replaced that recovery point. Settings stayed separate and compatible, or had their own restoration path. Saved operation state supported recovery after reboot. An unbootable base system still required a separate recovery procedure.

VALIDATION

- We tested different starting versions, wrong file checksums, full files and deltas, interrupted transfers, low storage and startup failure. We checked reboot during installation and manual rollback. Recovery had to restore the actual old files, permissions and SIP settings, not just the displayed version. The Windows tool reconnected to read the final result. A PBX outage was checked separately from local application health.

RESULT AND LESSON

- Updates remained partial, but packages were now built for each phone’s starting version instead of hand-written scripts for each case. The administrator could see the target and recovery versions. Correct version checks, a complete compatible file set and tested recovery made the process reliable. Binary deltas saved transfer where useful; full reflashing remained a separate operation.

EXPANDED TASK ANSWERS

1.1. Call handling architecture

- I separated call state, user actions, media negotiation, SDK access and screen drawing. The aim was an MVC/MVVM-style structure in which widgets display state instead of owning telephony decisions.

- SDK adapters pass events to call sessions and services. Controllers request operations and the UI follows the result. A stable call identity helps reject late events after a call ends. Cleanup must remain safe if requested twice.

- I changed the code in small steps and checked the existing signals and user actions. The broader refactor was completed as internal architecture work, not as a fully released feature.

1.2. BitBake builds for SDK and dependencies

- Our starting Yocto skeleton had no Linphone SDK, WebRTC or mediasoup. The team added them. I authored and maintained BitBake recipes for the modified SDK and its dependencies on NXP i.MX ARM, including build settings intended to reduce its memory footprint.

- The compiler must use device headers and libraries from the recipe sysroot, not libraries from the build computer. I checked the build, packages and application on the phone.

- A smaller binary, a smaller image and lower RAM use are different results. Compare the same call/media workload and check required codecs and features after changing options. I do not attach an unmeasured percentage or invent a historic flag set.

1.3. Incremental Qt Widgets decomposition

- I gradually moved legacy Qt Widgets call handling into call logic, presentation and SDK integration. Existing user behavior and QObject signal connections had to keep working.

- For each step, I introduced the new interface, moved its caller and removed the replaced connection. I checked signal arguments, direct or queued delivery, duplicate notifications and object lifetime.

- Hold, answer, hangup and late callbacks were useful checks. This allowed the structure to change without silently changing the phone’s behavior.

1.4. Yocto layers and SDK packaging

- I developed recipes and .bbappend files in product meta-layers to cross-build liblinphone and connect it to the image. The initial board platform already existed; the phone and conferencing stack was added by our team.

- I checked source versions, layer dependencies, selected recipes and whether each append actually applied. Build dependencies supply headers and libraries; runtime packages must supply the files used on the device.

- I inspected package contents and started the consuming application on the phone. A successful recipe build alone did not prove that its library, plugins and resources had reached the image.

1.5. Video and conference edge cases

- I worked on held calls, second incoming calls, remote hangups, stale overlays and switching the active video stream. The screen had to follow the call and media state reported by the SDK.

- The difficult cases were overlapping changes: a remote hangup while another call screen opens, or a participant leaving while the conference updates. Cleanup must detach old video bindings and ignore events from a finished session.

- I reproduced these sequences on phones and compared SDK state with the screen. I checked intermediate transitions as well as the final screen, since a brief incorrect state could still allow a wrong user action.

1.6. SIP backup and authentication

- I implemented the registration watchdog and primary/backup failover and failback in the customized SDK, then connected its APIs to the application and settings. I also added a backup domain to AuthInfo and implemented support for different HA1 values when the primary and backup servers used different realms.

- Registration, selected server and credentials must change together. A 401/407 challenge is not by itself a reason to switch servers. I checked loss, recovery, authentication and displayed state on the phone.

- Recovering registration does not automatically preserve an ongoing call. HA1 support was implemented, but selectable HA1 mode was disabled in later releases and remained disabled at project end.

1.7. WebRTC conferencing

- My main work was the phone-side WebRTC/mediasoup integration: create/join, invitations, participant lists, SIP/IP/phonebook add dialogs, status and control panels, video tiles and audio/video controls. My initial Node.js server contribution was limited; I did not own the later rewrite.

- The native C++ phone uses libmediasoupclient. Mediasoup forwards media as an SFU rather than mixing everyone into one server video. The UI must follow participant and stream changes.

- I checked joining, leaving, rejected invites and media cleanup on the phone. Successful room signaling did not prove that camera, audio and video display worked.

1.8. GPIO and hardware integration

- I reworked the GPIO layer using the libgpiod C++ API for handset switch events and the RGB LED. I moved event handling to a dedicated QThread, implemented a thread-safe singleton and fixed a mutex deadlock and memory leak.

- The worker reports handset state to Qt without blocking the UI. It reads the initial state, handles later edges and uses the board’s signal polarity. Waiting must be limited or interruptible so shutdown can finish.

- Safe singleton creation does not make all methods safe. Check lock order, waiting while locked and object cleanup. I explain those mechanisms without inventing the exact historic faulty allocation or lock sequence.

1.9. Provisioning utility

- I migrated the WinForms tool from .NET Framework 4.8 to .NET 8 and developed discovery, configuration and provisioning using SNMP, DHCP, TFTP and SQLite. I also unified the supported project-file formats across the device ecosystem.

- SNMP reads device information, DHCP options help locate provisioning data, TFTP transfers files and SQLite stores tool data. The generated settings must match what the phone applies.

- I used explicit project state for save/load and checked save, reopen and regenerated configuration. Old encrypted BinaryFormatter files were not readable by the later JSON reader; supported-format consistency was not universal legacy compatibility.

1.10. Device diagnostics

- I used application, SIP and system logs and added active-proxy diagnostics for failover. I implemented QLoggingCategory output to journald with storage limits and a support bundle containing journal entries, liblinphone logs, sanitized settings and SIP traces for download through the web interface.

- Categories help select useful messages, but journal capture still needs a configured logging path. Storage limits bound retained logs, not all flash writes. Verbosity and message rate matter too.

- The bundle needs a time/size limit, firmware identity and removal of passwords, keys and authentication data. I coordinated device diagnostics with the separately owned web download implementation; I did not own the whole web interface.

1.11. Qt Test coverage

- I added Qt Test checks for extracted call-state and conference logic, alongside focused model/controller and session tests. These tests supported the refactor; real media and hardware still needed device checks.

- A useful case holds a call, terminates it remotely and delivers a late media event. The session must stay terminated and must not emit a new active-state notification. Conference cases include repeated participant removal and leaving during join.

- Controlled adapter events isolate the logic. Signal observation and event-loop-aware waiting avoid arbitrary sleeps. A local test result is separate from validation of the complete SDK and phone.

1.12. Yocto and target services

- I contributed recipes, packages, model-specific image contents and startup services for i.MX devices. I checked the path from build settings to installed files, systemd, Weston/Wayland and application startup using logs and remote debugging.

- Before comparison, I recorded the phone model, image and application/SDK versions. Missing libraries, wrong service order and an unavailable display socket can look like Qt faults.

- Our old update.sh packages were already partial. The later .NET workflow built packages for each detected source version and kept the exact previous software for recovery. This did not mean ownership of the entire BSP, A/B rootfs or a confirmed UART flashing method.

FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION L1-01. Why does registration recovery belong beside SDK registration state?

Answer: The SDK already owns account registration and its transitions. A second Qt-side retry/switch loop can disagree with the active server and authentication state. In this project I implemented the SDK watchdog/failover state machine and made application/provisioning state follow its APIs.

More detail: Keeping another switch loop in Qt meant it could act while the SDK was already retrying or processing authentication. The two layers could disagree about the active server. Putting the decision beside registration removed that competing owner. The cost was maintaining and testing project-specific changes in the SDK fork.

QUESTION L1-02. How do Qt signals affect object and thread lifetime?

Answer: Signals do not make arbitrary shared data thread-safe or keep every referenced object alive. Queued delivery follows receiver affinity and needs a functioning event loop. I make ownership and teardown explicit so late SDK events cannot update an obsolete session or screen.

More detail: If the worker waits forever for a handset event, it may never process a queued stop command. I would give the wait a timeout or a wake-up path. Then I would stop new work, wait for thread exit and delete resources. I would test shutdown with no GPIO events as well as during activity.

QUESTION L1-03. How do BitBake packaging and the target sysroot relate?

Answer: Declared build dependencies populate the recipe's target sysroot; do_install stages produced files and packaging assigns them to runtime packages. The image must select those packages. I separate compile-time availability from the files and services actually installed on the phone.

More detail: I would follow one SDK file from installation staging into its package and then the image. Headers may correctly go into a development package, while runtime libraries belong on the phone. I would check that split rather than put everything into one package. Finally I would start the consuming application on the device.

QUESTION L1-04. Why can the application fail after the compositor service starts?

Answer: Service ordering does not necessarily mean the Wayland socket and runtime environment are ready. I check the running unit, service user, socket, installed dependencies and application logs, then reproduce startup on the actual image. An arbitrary delay is weaker than an explicit readiness condition.

More detail: For the graphical application, I would compare the service user and display environment with a working manual launch. Weston may have started while the required socket is still unavailable. Hardware permissions are another separate check. I would fix the missing condition instead of granting broad privileges or adding a blind delay.

QUESTION L1-05. What must be tested on a physical phone?

Answer: Boot ordering, real GPIO, camera, audio routes, USB and provisioning depend on the complete device. Qt tests isolate deterministic logic, while device scenarios check effective settings, SDK/UI state and media behavior. Passing one level does not establish the other.

More detail: A local test can confirm that remote hangup ends a model, but cannot verify the physical microphone path. I would keep separate device checks for boot, media and GPIO. Each result needs the tested image identity. That makes later regressions comparable to a known build.

QUESTION L1-06. How did you separate smaller binaries from lower runtime memory?

Answer: I distinguish image/package size from process memory and compare the same target call/media workload. Feature selection and optimization flags need regression checks; stripping symbols mainly affects artifacts. I do not attach an unmeasured percentage to the CV claim.

More detail: Removing an unused feature may remove code and dependencies, while removing a required codec breaks calls. I would compare the same target workload before and after a change. Matching symbols should remain available outside the production image. I would report only measured size or memory results.

QUESTION L1-07. Why can a dedicated GPIO thread still hang at shutdown?

Answer: The worker may be waiting in a blocking GPIO operation rather than its Qt event loop. I need bounded waiting or a wake-up mechanism, cooperative stop and correct destruction order. Waiting for the worker while holding a mutex it needs can deadlock.

More detail: A key failure to investigate is a worker that cannot leave its GPIO wait during shutdown. I would check its timeout or wake-up path and the order of cleanup. Singleton initialization does not solve concurrent method access. The precise old lock or allocation defect still needs its implementation history.

QUESTION L1-08. How do you make logs useful without exposing SIP credentials?

Answer: Correlate timestamps, call/session identity and active-server state, but remove passwords, authentication material, keys and sensitive configuration. Bound time and output size and inspect the actual exported archive. Category names alone do not sanitize message payloads.

More detail: Build a bundle for a known incident and inspect the resulting archive, not only the collector code. Check application logs, SDK traces and copied configuration for secrets. Missing files should be reported as partial collection. The support user needs enough context to correlate events without receiving credentials.

QUESTION L1-09. Give a concrete state-layer test example.

Answer: A controlled event sequence holds a session, ends it remotely and then delivers a stale media event. Assertions check that the session stays terminated and no new active-state notification appears. The conference equivalent checks repeated participant removal. This is distinct from testing physical media.

More detail: I would check both the final state and the number and arguments of the important signals. A duplicate callback must not create a second active session. Waiting should process the relevant event loop rather than rely on a long sleep. Hardware tests remain necessary for the actual media and device path.

QUESTION L1-10. What changed when manual update.sh packages were replaced?

Answer: They were already partial updates. The new workflow queried each phone version and constructed the matching source-to-target package from released artifacts. Recovery retained that phone’s exact previous executable, libraries, scripts and metadata rather than restoring an arbitrary factory release.

More detail: The new package was built from the detected starting release and chosen target release using saved artifacts. It did not compile a new C++ program for each phone. File checks prevented applying a delta to an unexpected base. The phone then owned installation and recovery even if the Windows connection disappeared.

QUESTION L1-11. Which layers do SIP, SDP and media troubleshooting cover?

Answer: Registration and call signaling are separate from the negotiated media description and actual transport/capture/rendering. A successful call setup is not proof of working audio/video. I correlate SDK state and logs with the phone-side media path before assigning the defect to the PBX or UI.

More detail: I would first separate registration and call acceptance from actual media. Then I would compare the agreed media settings with the selected codecs, endpoints and local devices. That helps locate whether capture, transmission or rendering is failing. One successful signaling message is not enough to prove the conversation works.

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

One option was to patch the layer that reported the error; the alternative was to follow the request across services until the evidence identified the cause. I used the latter because the reporting and failing components could differ. It required more initial investigation, but the result was a reviewable change at the responsible boundary and a regression scenario that exercised the whole workflow.

EXPANDED TASK ANSWERS

2.1. Legacy defects and performance

I investigated complex defects in the C backend with logs and native debugging, then made focused changes to preserve established behavior. Performance claims were evaluated within the task rather than as a system-wide benchmark. I optimized and maintained the codebase by resolving complex defects and implementing performance improvements.

A symptom in a long-lived service can come from data handling, a native memory error or an expensive path rather than the screen where it appears. I traced the request through logs and used native debugging to isolate the C path, checking boundary conditions such as fixed-size buffers. A change needs both the original reproducer and regression coverage; a performance improvement needs a comparable workload before and after. The result is a focused fix whose effect can be distinguished from unrelated system behavior.

2.2. Service communication

I followed requests through existing interfaces between C, Java and Scala and changed the relevant components when a feature crossed those boundaries. I coordinated integration and checked end-to-end behavior with logs and QA. I developed backend and frontend features for socket-based communication.

A socket-based request crosses a client/server boundary and then the existing C, Java or Scala service interfaces. The message contract and error handling must remain compatible on both sides; short reads, disconnects and unexpected responses are representative cases to consider. End-to-end checking follows a request through frontend, backend and logs instead of assuming that a successful connection means the workflow succeeded. That boundary is the key to integrating a new feature without breaking existing clients.

2.3. C backend contribution

As one of three C developers I implemented features, fixes and refactoring in the shared C89 codebase. I coordinated changes and review with the team. I led development efforts as a key C contributor, driving implementation of critical features and solutions.

Leading a feature in the shared C codebase means clarifying behavior with the team, identifying affected modules and breaking the change into reviewable work. In C89, fixed-size buffers, error paths and existing conventions need care because a small local change can affect a legacy interface. Review, build and QA regression connect the code change to the user workflow. The practical result is delivery of a critical feature with the shared team, rather than a claim of sole ownership of the whole product.

2.4. Scala API

I made occasional task-specific Scala API and Swagger changes, including calls into C-side behavior. I checked that the interface and backend agreed and relied on review and integration testing. I refactored the Scala API to improve maintainability and scalability.

The Scala endpoint is a boundary between an external request and C-side behavior, so refactoring must preserve the request and response contract. Separating endpoint concerns makes the code easier to follow, but error handling and compatibility with callers remain important. I used review and integration checks on the affected request path; the lesson is that maintainability gains must not silently change the API.

2.5. Build and deployment workflow

I used existing Jenkins builds and nightly or on-demand deployments on AWS Linux hosts for development and validation. I inspected build results and environment behavior; I worked with AWS pipelines to automate CI/CD processes for smoother deployments and shorter development cycles.

The delivery path links source control, builds, deployment and checks on AWS-hosted Linux environments. Automation must make failures visible and preserve a reproducible artifact and configuration; a passing build alone does not prove that an application starts correctly after deployment. Existing Jenkins builds and environment checks provided the feedback path, and QA exercised the affected workflow. The useful distinction is between improving an application delivery workflow and owning the entire infrastructure.

2.6. Database-backed workflows

I worked on application behavior connected to Java data services using PostgreSQL and remaining MySQL models. I traced data across service boundaries when a task required it and checked the resulting workflow. I modified database tables and improved schema design to support new features and updated workflows.

A workflow change can require both the service contract and the database schema to evolve. The safe boundary is to account for existing data, null or missing values and compatibility with the application version that reads the tables. Checking representative old and new records and the corresponding service workflow helps catch mismatches. The result is a schema that supports the feature while preserving the established data path.

2.7. Task estimation

I estimated my own work in a two-week sprint process, accounting for investigation, implementation, review and QA. Grooming and daily communication helped revise scope as details became clear.

An estimate includes understanding an inherited code path, implementation, review, integration and QA rather than only coding time. Cross-service changes introduce uncertainty because the visible symptom may not identify the failing component. I discussed scope in grooming and adjusted the estimate when investigation exposed additional dependencies. The lesson is to make uncertainty visible early and revise the plan as evidence improves.

2.8. Code reviews

Changes were reviewed by assigned colleagues and customer developers; required reviewers approved before merging. I used review to check behavior, maintainability and integration assumptions and to share knowledge.

Review covers correctness, compatibility, error handling and whether the change is understandable to the next maintainer. For cross-language changes, reviewers also need to inspect assumptions at the service boundary and the proposed regression checks. Discussion with delivery and customer developers exposes different knowledge of the same system; required approvals make review part of delivery. The result is shared understanding as well as an additional defect filter.

2.9. Legacy refactoring

I refactored inherited C code in small changes alongside features and fixes, preserving service compatibility and established workflows. Review, builds and QA regression helped control the risk.

Legacy refactoring starts by identifying behavior and callers before moving code, particularly where C modules interact with Java and Scala services. Small changes make it easier to compare behavior and isolate a regression; boundary and error handling need to remain compatible. Builds, reviews and QA scenarios validate the affected workflows. The lesson is that better structure is valuable only when the established behavior remains dependable.

FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION L2-01. How do you investigate a C89 buffer defect?

Answer: Track capacity, current length, initialization and the terminating null together. Reproduce the exact input and inspect each copy/format operation rather than increasing buffer sizes blindly. Validate the final output and adjacent cases after correcting the owning operation.

QUESTION L2-02. When do you use gdb and when Valgrind?

Answer: gdb inspects execution state, stacks and values in a live process or core dump. Valgrind Memcheck detects executed invalid-memory and uninitialized-value paths with additional overhead. I use logs to locate the path, then choose the tool for the hypothesis rather than treating either as a storage benchmark.

QUESTION L2-03. How do you locate a fault across services?

Answer: Follow one user operation through Scala/API, C processing and Java data services using correlated logs and payload interpretation. Identify the first incorrect value before changing a consumer that merely displays it. Recheck the complete operation after the owning layer is fixed.

QUESTION L2-04. What matters at the Scala-to-C boundary?

Answer: Request mapping, value representation, errors and returned data must agree between runtimes. I reused existing C behavior through a Scala request and updated Swagger instead of duplicating domain logic. Integration checks validate the contract beyond either component compiling independently.

QUESTION L2-05. How did review and regression protect legacy changes?

Answer: I used focused changes, mandatory delivery/customer review and developer/integration/QA checks on representative workflows. The C code had no unit-test suite to claim as protection. Reproducing the original defect and checking neighboring behavior were therefore especially important.

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

A single final-mesh view would be simpler, but it would not show whether the fault came from calibration, merging or reconstruction. Inspecting the transformed profiles and intermediate cloud added steps for the engineer while making the source of doubling visible. The comparison used the same data and known geometry; incomplete physical coverage could not be repaired merely by changing the mesh algorithm.

EXPANDED TASK ANSWERS

3.1. Multi-sensor reconstruction

I transformed 2D sensor profiles into a common 3D frame and assembled a model for engineers to inspect. Calibration assumptions and incomplete coverage affected the result, so I checked stages on recorded inputs.

Each laser profile begins in a sensor-local plane, so combining sensors requires applying their mounting geometry to obtain a common 3D frame. Wrong poses can create doubled surfaces, while occlusion leaves regions with no observations at all. I inspected intermediate clouds on recorded datasets and compared geometry with known dimensions before assessing the reconstructed model. The result was an inspectable prototype in which errors could be localized by stage.

3.2. PCL processing

I used PCL for filtering, downsampling, alignment and surface reconstruction. I compared intermediate clouds to avoid treating an error in input geometry as a reconstruction-algorithm problem.

PCL operates on the merged point cloud after coordinate transformation. Filtering removes unsuitable points, downsampling limits data volume, and alignment and reconstruction prepare a surface for inspection; changing their order or parameters can remove useful detail. I compared intermediate and final clouds on the same datasets to distinguish geometry problems from processing effects. The tradeoff is between detail, noise and the amount of data the workstation can handle.

3.3. Open3D evaluation

I integrated Open3D alongside PCL for visualization and analysis during evaluation. This gave engineers another view of the data and reconstruction without making it the primary pipeline.

Visualization allows an engineer to inspect whether adjacent sensor views agree and whether filtering removes valid geometry. Open3D provided an additional analysis view alongside the PCL processing path; data must retain the same coordinate frame and units when compared. Using the same recorded input makes discrepancies easier to investigate. The benefit is a clearer comparison of intermediate and reconstructed results.

3.4. Visual Studio development

I used Visual Studio for C++ development and debugging of the Windows prototype. Recorded datasets and stage-by-stage inspection made repeated checks practical.

The Windows desktop build brought C++ application and point-cloud libraries together in one debugging environment. Breakpoints and inspection of intermediate data help locate whether a defect enters during loading, transformation or later processing. Replaying recorded datasets supports repeatable comparisons and avoids relying on live hardware for every iteration. This improves diagnostic speed without implying a measured performance gain.

FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION L3-01. How do profiles from several scanners become one cloud?

Answer: Each scanner has a local coordinate frame. Apply the measured mounting transform into a common frame with consistent units, orientation and axis conventions, then combine the transformed points. A pose error can create doubled surfaces that later meshing cannot reliably repair.

QUESTION L3-02. Which PCL stages did the pipeline use?

Answer: Transformation establishes common geometry; filtering and downsampling control unsuitable points and density, followed by alignment/reconstruction as needed. I inspected intermediate clouds rather than judging only a final mesh. Parameters were compared on the same recorded inputs.

QUESTION L3-03. How do you balance filtering with geometric detail?

Answer: A stronger filter or larger downsampling scale reduces work and noise but can remove real edges or thin features. Compare retained geometry and known dimensions at several settings, not only point count. Missing physical observations remain a coverage limitation, not a filtering problem.

QUESTION L3-04. What did prototype validation establish?

Answer: Recorded datasets, known geometry and intermediate visualization made the reconstruction inspectable and repeatable. Open3D provided an additional comparison view alongside PCL. This demonstrated the prototype's behavior; it did not establish an invented accuracy metric or released production system.

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

Using only laboratory imagery would make iteration easier but would miss vibration, sensor alignment and actual flight conditions. Conversely, waiting for every flight to evaluate an idea would make feedback too slow. Combining representative images, calibration checks and flight observations balanced repeatability with realism. The interpretation remains bounded by the available flight data and the separate responsibility for target software.

EXPANDED TASK ANSWERS

4.1. UAV image-processing modules

I developed MATLAB algorithms for the optical system, combining sensor processing with verification on representative data. I coordinated algorithm handover with the engineers responsible for the rest of the instrument.

The optical pipeline has to turn sensor data into usable imagery and pass it to the next processing or analysis stage. I worked on the algorithms in MATLAB, checking representative inputs and sharing expected behavior with the engineers responsible for the instrument. Invalid or poorly aligned inputs can affect every later stage, so intermediate results matter. The result is an algorithm and verification basis that can be handed to the flight-software team.

4.2. Debayering

I designed and evaluated conversion of Bayer sensor samples into a color image. I inspected image quality and artifacts on reference data so reconstruction choices could be compared.

A Bayer sensor records one color component at each pixel, so the missing components need to be estimated from neighboring samples. Pattern orientation, image boundaries and high-contrast edges can create color artifacts if interpreted incorrectly. I compared the reconstructed color image with representative reference data and inspected artifacts rather than judging only a single pixel. The result supports a usable color image for subsequent analysis.

4.3. Image format conversion

I worked on image-format conversion within the MATLAB processing workflow. Correct interpretation of input and output data was necessary for later stages to consume the image consistently.

Different stages may expect different pixel layouts, dimensions or numeric ranges. Conversion must preserve the meaning of the sensor data, including how the receiving stage interprets channels and values. Representative inputs and inspection before and after conversion help catch truncation or a mismatch in format. The lesson is to make the input/output contract explicit so a later image artifact is not mistaken for an algorithm failure.

4.4. Image stabilization

I developed and evaluated stabilization algorithms to reduce motion-induced distortion in real-time UAV video. I used representative imagery and flight-test observations to judge whether the correction preserved useful detail.

Stabilization estimates or compensates motion so that successive frames remain easier to interpret. Large movement, poor visual detail and changing scene content can make alignment less reliable, and the correction must not discard useful image detail. Representative sequences and observations from flight tests connect algorithm behavior to real movement. The design tradeoff is stable output while retaining usable detail within the processing constraints.

4.5. Image fusion

I designed and verified image-fusion algorithms in MATLAB, combining information from multiple sensors to improve detail and contrast for target analysis. Alignment and comparable inputs were necessary before combining information; I evaluated output against reference imagery and the needs of the optical workflow.

Fusion combines complementary sensor information, but the inputs first have to be placed in comparable spatial and temporal correspondence. Misalignment can produce doubled or misleading features, and contrast changes should not be confused with new information. I assessed the output on representative and reference imagery, including whether the result supported the intended visual analysis. The lesson is that registration and validation matter as much as the combination itself.

FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION L4-01. What does debayering reconstruct?

Answer: A Bayer sensor samples one colour component per location, so missing colour values must be estimated from neighboring samples according to the correct pattern. I compare edges and representative raw data against references; incorrect pattern or channel interpretation can create false colour even when dimensions are valid.

QUESTION L4-02. How do alignment and stabilization differ?

Answer: Alignment estimates a geometric relationship between images; stabilization uses motion information to reduce unwanted frame-to-frame variation. Reliable evaluation separates actual scene changes from platform motion. I inspect intermediate results and representative sequences rather than accepting a smooth-looking final video alone.

QUESTION L4-03. What must be true before image fusion is useful?

Answer: Inputs need compatible geometry, timing and value interpretation. Misalignment, motion or inconsistent sensor response can turn extra input into ghosting or false detail. Compare the fused image with each source and known references; more contrast alone does not prove better recognition.

QUESTION L4-04. How do calibration and flight tests complement algorithm tests?

Answer: Synthetic and reference images isolate algorithm behavior; calibration checks geometry against physical references. Flight tests include the real optics, acquisition and platform motion. In this work I also operated the optical payload, which helped connect processed imagery with actual instrument conditions.

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

Continuing with separate documents would avoid application development but leave search and maintenance dependent on manually locating each source. A shared relational database and web interface made fields queryable and maintainable, at the cost of defining a data model and keeping records consistent. Representative records and user workflows were checked with domain engineers. For legacy Access data, a migration approach can be evaluated through field mapping and representative-record checks.

EXPANDED TASK ANSWERS

5.1. Rails web interface

I built a Rails interface for maintaining and retrieving satellite reference records. I checked that user workflows and displayed fields corresponded to the underlying data.

The Rails interface exposes structured satellite and mission records to users who need to find or maintain parameters. Input validation and clear mapping between fields and stored data matter because an incorrect value can mislead later analysis. I checked representative records and application workflows with the engineers using the data. The outcome was a shared interface to information that had previously been scattered across documents.

5.2. PostgreSQL reference database

I designed the PostgreSQL-backed data structure for satellite and mission parameters and used it from the Rails application. Structured records made the information queryable; no quantified retrieval improvement is claimed.

PostgreSQL stores structured satellite specifications and supports queries from the Rails application. Data modelling must keep relationships and units understandable, while query changes should be assessed using representative records rather than a bare claim of speed. I checked that the application retrieved the expected parameters and that the workflow remained usable. The outcome is a queryable reference database; no measured speedup is asserted.

5.3. Existing data environment

The organization also had historical MS Access databases. I built the Rails/PostgreSQL reference database and arranged satellite information for its users. I integrated MS Access for legacy data support, migration and compatibility with existing systems.

Legacy Access records needed to remain useful alongside the PostgreSQL-backed application. Migration requires mapping fields and types, handling missing or duplicate records and comparing representative values before and after transfer. A practical check is to compare record counts and sample records and then exercise the Rails workflow; this illustrates a possible migration check. The intended result is usable legacy information in the new workflow without silently changing its meaning.

FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION L5-01. How would you model satellite reference data?

Answer: Identify entities such as satellites, missions, instruments and their parameters, then define relationships, units and constraints. A relational model preserves these connections better than flattened free text. The database is a reference-data system; this does not imply an imagery archive or object-storage platform.

QUESTION L5-02. How do Rails and PostgreSQL divide responsibility?

Answer: Rails handles request/controller and user workflows while PostgreSQL stores relational data and enforces database constraints. Application validation improves feedback but is not a substitute for uniqueness, foreign-key or transaction guarantees needed at the data boundary.

QUESTION L5-03. How do you validate a catalogue workflow?

Answer: Check creation, editing, search and retrieval with representative parameters, invalid values and related records. Validate units and relationships as well as form acceptance, and verify the stored result. Query correctness and a usable interface are distinct from an unmeasured retrieval-speed claim.

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

Transform-based approaches could offer better quality per bit, but their compute cost conflicted with the onboard budget. Differential predictive compression was selected for its smaller computational footprint; the tradeoff was accepting lossy reconstruction and validating quality at the required ratio. MATLAB reference comparisons provided evidence for the algorithm, while the flight-software team owned implementation on the target.

6.2. Stitching and resolution

A frame consisted of segments from different detectors; geometric alignment alone left visible brightness discontinuities. I combined feature-based alignment with radiometric matching and checked the result against reference imagery. Separately, manual resolution assessment made flight-test analysis dependent on the operator. I defined and implemented automated assessment in MATLAB and compared it with known targets and existing manual analysis. The results were a more consistent stitched image and repeatable measurements; both demonstrate why validation must address the physical imaging chain as well as the algorithm.

A geometry-only correction was a plausible first approach, but it could not address different detector responses; radiometric matching addressed the remaining brightness step. For resolution, retaining manual assessment would preserve expert flexibility but also operator dependence. Automation traded some manual discretion for a defined, repeatable criterion, checked against known targets and previous analysis. These were separate improvements connected by the same need for trustworthy image quality.

EXPANDED TASK ANSWERS

6.1. Brightness and detector correction

I worked on radiometric correction and matching across detector segments as part of stitching. I compared seams and reference imagery, since correct geometry alone did not eliminate brightness differences.

Adjacent detector segments may be geometrically aligned and still show a brightness seam because their responses differ. Radiometric correction and matching address the value difference, while geometric stitching addresses position. I compared intermediate seams and reference imagery so that a correction did not hide a misalignment or remove real image structure. The outcome is a more consistent composite image and a clearer separation of geometric and radiometric defects.

6.2. Linear resolution assessment

I developed automated resolution assessment in MATLAB for flight-test imagery. I checked repeatability against known targets and manual analysis; the work reduced dependence on the individual operator. I applied the sharp edge method to linear-resolution analysis.

A sharp-edge analysis uses a suitable edge in the image to characterize how the imaging chain transitions between light and dark. Edge selection, noise and sampling influence the result, so repeatability and comparison with known targets are important. The automated MATLAB workflow was evaluated against reference targets and prior manual analysis. The benefit is a more consistent resolution assessment across images and operators.

6.3. Image sharpness and quality

I assessed achieved image resolution using repeatable criteria and representative targets. I compared results with reference data rather than inferring image quality from a single visual impression. I developed algorithms for image sharpness and edge clarity to support resolution measurement.

Sharpness and edge clarity describe how well detail is preserved, but the result depends on the selected region and image quality. A representative edge or target and consistent processing make comparisons meaningful; noise or compression artifacts can otherwise distort the judgment. I used repeatable assessment and reference imagery to compare outputs. The lesson is to connect a numerical result to the physical target and the conditions under which the image was acquired.

6.4. Image characteristics and quantization

I worked on predicting image type and adapting quantization to image characteristics. I assessed quality at a matched compression ratio to make the comparison meaningful. The task included analysing Earth-observation data and estimating the albedo range to predict quantization ranges and support sensor calibration.

The chosen quantization range affects both information loss and the compressed representation. The range prediction relates Earth-observation data and albedo to image characteristics, and image-type prediction supports adaptive quantization. Dark, bright or atypical scenes are important cases because a range suited to one image may clip or underuse values in another. Comparing image quality at a matched compression ratio provides a meaningful basis for evaluating the choice.

6.5. Automated quantization adaptation

I implemented image-type prediction and adaptive quantization in MATLAB. Reference images and comparison under the same compression conditions supported the evaluation. I automated the prediction of quantization ranges to streamline the workflow.

Automation connects image classification or input characteristics to the selection of a quantization range, reducing repeated manual work. It needs a defined response to an atypical image and consistent inputs so that the same conditions produce comparable output. Reference imagery and matched compression conditions help distinguish a real quality improvement from a change in compression ratio. The result is a repeatable workflow for evaluating adaptive quantization.

6.6. ADPCM-family compression

I designed and verified a differential predictive compression algorithm in MATLAB for a limited onboard compute budget. The documented ratio was 3–4x; the flight-software team implemented the target version. The compression design used ADPCM with multiple quantizers to support different data sizes.

ADPCM encodes a prediction error rather than each original sample independently, and quantization trades reconstruction fidelity for fewer bits. The onboard constraint made computational cost a central factor; multiple quantizers and adaptation affect the quality/rate tradeoff. Reference-image comparison at the same ratio and checks of reconstructed output are essential because compression is lossy. The documented 3–4x ratio is an outcome of the algorithm work; the separate flight-software group implemented it for the target.

FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION L6-01. How do geometric and radiometric correction differ?

Answer: Geometric alignment makes corresponding scene features coincide; radiometric matching reduces inconsistent brightness or response across detectors/frames. A seam can remain after either one alone. I inspect spatial discontinuities and brightness steps separately before judging the assembled image.

QUESTION L6-02. How do you validate image-resolution measurements?

Answer: Use a defined criterion, suitable known targets and consistent processing conditions, then check repeatability and agreement with independent reference analysis. Noise, target orientation and preprocessing affect the estimate. Repeating a calculation is useful only if the measurement assumptions are also controlled.

QUESTION L6-03. Why adapt quantization to image content?

Answer: Smooth and textured regions tolerate quantization error differently. Adapting quantization can preserve more useful detail for the same encoded size, but comparison must hold compression ratio and reference scenes constant. Raising bitrate is a different change from improving quality at a matched ratio.

QUESTION L6-04. Why choose ADPCM-family coding under a compute constraint?

Answer: It encodes prediction residuals with quantization and state updates rather than requiring a costly transform for every block. Encoder/decoder state must remain consistent. The choice trades compression efficiency against feasible computation and memory, with reference reconstruction and difficult scenes used for validation.
