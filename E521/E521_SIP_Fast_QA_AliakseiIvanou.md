SIP PROJECT: FAST Q&A

Request: E521
Project: SIP-BASED PHONE SOFTWARE
Candidate: Aliaksei Ivanou

SECTION 1. PROJECT AND OWNERSHIP

QUESTION SIP-01. Can you briefly describe the project?

Answer: I worked on an embedded SIP desk-phone platform with audio-only and camera-enabled models. It combined a C++17/Qt application, Linphone SDK, conferencing components and a Yocto Linux image on NXP i.MX. My main work was application and SDK development, including registration failover, configuration integration and device debugging. I also contributed to BitBake recipes, packaging and runtime integration.

QUESTION SIP-02. What existed before your team joined?

Answer: There was a basic Yocto platform skeleton, but it did not include Linphone SDK, WebRTC or mediasoup. Our team added those components and integrated their dependencies, packages and runtime requirements into the phone image. We inherited the platform baseline, not a fully integrated telephony and conferencing stack. My own contribution was part of that team effort.

QUESTION SIP-03. Which parts did you personally implement?

Answer: My strongest personal example is the registration watchdog and primary/backup failover and failback in the customized Linphone SDK, followed by application integration. I also added backup-domain authentication information, worked on Qt call/account architecture and substantially extended the Windows provisioning tool. On the platform side, I contributed recipe metadata, packaging, image contents, service integration and target validation. I distinguish those changes from ownership of the complete product.

QUESTION SIP-04. How was responsibility divided within the team?

Answer: Our delivery team grew from three to four C++ engineers. We worked with customer developers, a project manager, a web developer and QA. My focus was the phone application, customized SDK, provisioning and cross-layer integration. The web frontend and device-local REST implementation belonged to another developer. Adding the phone stack to Yocto was team work; it was not something I delivered entirely alone.

QUESTION SIP-05. Did you own the BSP and board bring-up?

Answer: My main responsibility was above the board bring-up level: application/SDK integration, recipes, packages, image contents, services and device diagnosis. The existing BSP was a foundation for that work. I investigated issues across the application/platform boundary, but I would not describe myself as the sole owner of the kernel, bootloader or complete BSP. Adding Linphone and conferencing to the image is distinct from bringing up a new board.

SECTION 2. YOCTO AND STACK INTEGRATION

QUESTION SIP-06. Why did the product need Yocto?

Answer: The product needed a complete, reproducible image rather than just a Qt executable. The application depended on SDK and media libraries, services, configuration, graphical runtime and model-specific files. Yocto described how those components were built, packaged and selected for the device. Copying a binary could help during debugging, but final validation had to use the intended image and its actual runtime environment.

QUESTION SIP-07. How do you integrate Linphone SDK into a Yocto image?

Answer: I start with the selected SDK release and available metadata, then add or extend recipes in the product layer. Sources, dependencies and cross-build options must be controlled. The build installs outputs into staging, packaging assigns files to runtime and development packages, and the application consumes headers/libraries through its recipe sysroot. Image metadata selects runtime packages. I then check the deployed image and validate registration, calls and media on hardware.

QUESTION SIP-08. What is the difference between DEPENDS and RDEPENDS?

Answer: DEPENDS names recipe providers needed during the build, such as libraries whose headers and link inputs must appear in the recipe sysroot. RDEPENDS names output packages needed at runtime. Shared-library runtime dependencies are often detected automatically, while dynamically loaded plugins or resources may need explicit dependencies. A recipe name and its output package names are not necessarily identical, so I check the actual metadata.

QUESTION SIP-09. How do you keep the SDK build reproducible?

Answer: The important inputs are pinned source revisions, compatible layer revisions, declared dependencies and explicit feature choices. SRC_URI describes inputs and SRCREV pins version-controlled sources; release archives need checksums. License metadata must describe the selected source and enabled components. Downloads and shared state speed up the build, but do not replace those controls. The useful check is whether maintained metadata can reproduce the integration without a developer-only workspace.

QUESTION SIP-10. What is tricky about the Linphone SDK build?

Answer: The SDK can orchestrate builds of several components rather than behave like one simple library. I need to inspect the chosen release and keep nested builds aligned with Yocto toolchain and sysroot settings. Hidden downloads, accidental host libraries and conflicting bundled/system dependencies can undermine reproducibility. Separate recipes or an adapted orchestration may be appropriate; I would choose based on the release and existing platform metadata, not assume one universal CMake switch.

SECTION 3. BUILD AND RUNTIME DIAGNOSIS

QUESTION SIP-11. The recipe builds, but the library is missing on target. What do you check?

Answer: I follow installation, packaging, image selection and deployment. First I check whether do_install placed the file under the intended path in ${D}. Then I inspect package ownership and contents, and whether the image includes that package. Finally I confirm the device runs the intended image. If the library exists but loading fails, I check its architecture, loader, dependent libraries and permissions instead of repeating compilation.

QUESTION SIP-12. How do you fix installed-vs-shipped QA errors?

Answer: The error means files were installed into staging but were not assigned to an output package. I inspect the reported paths, PACKAGES and FILES, then either assign intended files to the correct package or stop installing unwanted files. Development headers and debug information should follow their package roles. I would not disable the QA check globally, because that can hide missing runtime content.

QUESTION SIP-13. How do you detect accidental host dependencies?

Answer: I inspect configure logs, the selected compiler, sysroot and actual link inputs. A library found on the build host is not necessarily suitable for ARM64. The recipe needs declared target dependencies, while tools executed during the build may need native providers. With CMake, I also check cached configuration and nested builds. A successful build does not prove the output matches the target ABI.

QUESTION SIP-14. How would you build the application outside BitBake?

Answer: I would generate and install the SDK for the relevant image, source its environment setup script and configure a fresh application build directory with the SDK toolchain. I would verify target headers, libraries and ABI rather than reuse desktop CMake cache settings. This supports development iteration, but the maintained application recipe and final image still need validation. External SDK compilation and product-image delivery are separate checks.

QUESTION SIP-15. Why can the Qt application run manually but fail at boot?

Answer: The service can have a different user, environment, working directory or available dependencies. I check installed files and libraries, then service configuration and graphical-runtime readiness. On the phone, Wayland/Weston and its socket were relevant boundaries. I correlate system and application logs and use remote debugging when appropriate. An arbitrary startup delay is weaker than identifying the actual missing dependency or readiness condition.

QUESTION SIP-16. Does After=network.target guarantee SIP connectivity?

Answer: No. Ordering and readiness are different. After= defines ordering when units participate in the transaction; it does not itself pull in another unit or verify server reachability. Even configured network-online handling does not guarantee that a SIP server remains reachable. The application and SDK still need recovery behavior. I investigate service relationships and actual network/registration state separately.

SECTION 4. SIP REGISTRATION AND FAILOVER

QUESTION SIP-17. What did your registration watchdog do?

Answer: I implemented project-specific registration supervision and primary/backup failover and failback in the customized SDK. The problem was keeping registration lifecycle and active-server state coherent, not merely storing two addresses. I also integrated the SDK APIs into application/settings paths and added active-proxy diagnostics. This was software supervision of SIP registration, not a claim that I implemented a hardware watchdog or the complete upstream SIP stack.

QUESTION SIP-18. Why move server switching from Qt into the SDK?

Answer: My first Qt-level approach created another owner of state that belonged beside registration. I reverted it and moved the authoritative watchdog and switching behavior into the customized SDK. The application then consumed SDK-reported active/backup state rather than running a competing rotation loop. The tradeoff was maintaining changes in the SDK fork, but the design made lifecycle ownership clearer and reduced disagreement between application and SDK state.

QUESTION SIP-19. How did you validate failover and failback?

Answer: I reproduced primary-server loss and recovery on physical phones with configured primary and backup accounts. I compared SDK registration state, active-server diagnostics, SIP logs, authentication behavior and the UI. Configuration and persistence also mattered, because a temporary runtime success could hide inconsistent saved settings. I describe the result through those repeatable scenarios rather than invent a universal recovery-time guarantee.

QUESTION SIP-20. Does registration failover preserve an ongoing call?

Answer: Not automatically. Registration recovery and continuity of an established call are different requirements. A call also has dialog and media state, and behavior depends on the PBX and network architecture. My confirmed implementation was registration watchdog/failover/failback and its integration. I would validate ongoing-call behavior as a separate scenario rather than infer seamless call preservation from successful backup registration.

QUESTION SIP-21. Why can a different realm break backup authentication?

Answer: For the MD5-based mechanism used here, HA1 is MD5(username:realm:password). Changing the realm changes the hash input, so a primary-server HA1 cannot simply be assumed valid for the backup. I worked on backup-domain authentication information and realm/HA1 functionality. Selectable HA1 mode was later disabled and remained disabled at project end; I distinguish implemented capability from final enabled functionality.

QUESTION SIP-22. What did you change in SIP realm discovery?

Answer: The provisioning probe had to handle authentication challenges from different servers. I added handling for WWW-Authenticate and Proxy-Authenticate, continuation-line unfolding and variations in realm quoting and parameter order. The goal was to avoid binding the probe to one PBX response format. It was a focused parser for the fields we needed, not a replacement for a full SIP implementation or proof of compatibility with every server.

SECTION 5. QT, CONCURRENCY AND MEDIA

QUESTION SIP-23. How did you connect asynchronous SDK events to the UI?

Answer: I worked toward explicit models/controllers and later session/service boundaries. SDK callbacks updated application state, and the UI followed that state rather than owning registration or call lifecycle decisions. Object lifetime and event ordering were important, especially during teardown or screen changes. The purpose was to make transitions understandable and avoid several layers maintaining independent interpretations of the same call.

QUESTION SIP-24. What was the scope and status of the Qt refactor?

Answer: I incrementally separated call handling into session, service, SDK-adapter and presentation responsibilities while preserving existing UI behavior and QObject signal compatibility. A large rewrite would have increased regression risk. Focused tests and device scenarios helped check transitions. The broader refactor was completed as internal architecture work; I do not present that entire restructuring as already released customer functionality.

QUESTION SIP-25. How would you handle callbacks crossing Qt threads?

Answer: I would first establish the callback thread and the receiving QObject thread affinity. UI changes must reach the UI thread through an appropriate queued mechanism, with valid receiver lifetime and any required cross-thread argument types. I also check late events and session teardown. I would not assume that an SDK callback can safely update a widget directly just because the operation itself is asynchronous.

QUESTION SIP-26. A call connects but has no audio or video. Where do you start?

Answer: I separate signaling success from media success and identify the failing direction: capture versus playback, local versus remote, audio versus video. Then I follow SDK/media state, network behavior, device availability, configuration and rendering. My project work involved correlating application, SIP and system logs and reproducing scenarios on the phone. A registration fix is not automatically a media fix, and a desktop reproduction cannot establish hardware behavior.

QUESTION SIP-27. What was your responsibility in WebRTC/mediasoup conferencing?

Answer: Our team added WebRTC and mediasoup integration to the platform. My main scope was the phone-side client/room lifecycle, UI and media integration and debugging. I also made a limited contribution to the initial Node.js server implementation. I did not own the later server rewrite. That distinction matters: adding the stack was a team responsibility, while my strongest implementation detail is on the C++ phone side.

SECTION 6. VALIDATION, PROVISIONING AND LESSONS

QUESTION SIP-28. What did automated tests cover, and what needed hardware?

Answer: Focused Qt Test checks covered local logic, models/controllers and call-session work. Physical devices remained necessary for real audio/camera/GPIO behavior, complete boot, graphical startup and SDK/device integration. I combined those validation levels with logs and remote debugging. I would not call the local tests complete conference-domain or end-to-end phone coverage; they protected specific logic while device scenarios checked integration.

QUESTION SIP-29. What did you do in the provisioning tool?

Answer: I migrated the inherited WinForms application from .NET Framework 4.8 to .NET 8 and substantially extended discovery, configuration generation, DHCP/TFTP delivery and project persistence. I introduced explicit project state instead of treating the control tree as the file format. A useful check was save, reopen and regenerate equivalent configuration. That applied to the supported JSON-based schema; older encrypted BinaryFormatter payloads remained incompatible.

QUESTION SIP-30. What is your strongest engineering lesson from this project?

Answer: The failover change is my clearest example. I first put switching in Qt, recognized that it duplicated SDK-owned lifecycle state, reverted it and implemented the authoritative behavior in the SDK. The application then followed that state. More generally, difficult defects came from disagreement between generated settings, persisted configuration, SDK state, UI and runtime services. I learned to identify the state owner and validate the full path on the device.

SECTION 7. CV AND UPDATE FOLLOW-UP QUESTIONS

QUESTION SIP-31. Were the old update.sh packages full firmware images?

Answer: No. They already delivered selected software files, but each installation script was prepared manually. The later .NET workflow queried the phone version and dynamically assembled the applicable package from released artifacts. Complete reflashing remained a separate procedure.

QUESTION SIP-32. What exactly did recovery restore?

Answer: The phone’s actual pre-update executable, matching libraries, scripts, resources and file metadata, together with the prior activation state. Settings had to stay compatible or have a restoration path. This was application-stack recovery, not a claim of A/B rootfs or repair of an unbootable board.

QUESTION SIP-33. How do you explain the GPIO responsibility precisely?

Answer: The CV scope includes handset edge events, RGB LED, a dedicated QThread, singleton synchronization and deadlock/leak fixes. The architecture needs one hardware owner, non-blocking UI delivery and a bounded stop path. I can explain the ownership and shutdown design, but I cannot reliably name the exact original lock sequence or leaking allocation without revisiting the implementation.

QUESTION SIP-34. Which memory optimization can you defend?

Answer: I can explain feature selection, compiler/build settings and measurement boundaries, but I do not invent an exact flag set or percentage. Binary size and runtime memory differ. A defensible comparison uses the same phone and call/media workload and checks that required functionality survives the change.

QUESTION SIP-35. Did you own the whole web diagnostics download implementation?

Answer: No. The web frontend and REST implementation belonged to another developer. My confirmed work includes correlating application/SIP/system logs and adding active-proxy diagnostics. I can explain category filtering, journal limits and sanitized support bundles, while keeping that broader CV scope distinct from the personally evidenced implementation.

QUESTION SIP-36. How would you demonstrate a useful Qt state test?

Answer: I would feed controlled events into a session/controller and assert both the state and notifications. A good case is remote termination followed by a late media event: the session must remain terminated. QSignalSpy can observe signals, but a passing local test does not prove that physical audio/video or every conference path works.

QUESTION SIP-37. How do you separate SIP, SDP and actual media?

Answer: SIP manages signaling; SDP describes media parameters, while actual audio/video follows its transport and device/rendering path. A successful setup does not prove working media. My debugging approach follows the first failing boundary instead of treating a camera or rendering failure as automatically a SIP defect.

QUESTION SIP-38. What did SNMP, DHCP, TFTP and SQLite each do?

Answer: They served different parts of provisioning: SNMP queried device information, DHCP options supported locating provisioning data, TFTP delivered files, and SQLite backed tool data. I checked generated settings against phone behavior and supported save/open semantics. I would not describe TFTP as authenticated or encrypted delivery.
