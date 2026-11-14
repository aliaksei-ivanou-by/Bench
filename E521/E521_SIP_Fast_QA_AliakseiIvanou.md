SIP PROJECT: FAST Q&A

Request: E521
Project: SIP-BASED PHONE SOFTWARE
Candidate: Aliaksei Ivanou

SECTION 1. PROJECT AND OWNERSHIP

QUESTION SIP-01. Can you briefly describe the project?

Answer: I worked on SIP desk phones with audio-only and camera models. The product used C++17, Qt, Linphone SDK and Yocto Linux on NXP i.MX. My main work was the application, SDK, server failover, settings and device debugging. I also worked on recipes, packages and startup.

QUESTION SIP-02. What existed before your team joined?

Answer: We received a basic Yocto skeleton without Linphone SDK, WebRTC or mediasoup. Our team added those components, their dependencies and the settings needed to run them. We inherited the board platform, then integrated the phone stack. My work was one part of that team effort.

QUESTION SIP-03. Which parts did you personally implement?

Answer: I implemented registration monitoring and primary/backup switching in the SDK, connected its APIs to the application and added a backup authentication domain. I also worked on Qt calls/accounts, provisioning, recipes and device tests. I did not own the whole product alone.

QUESTION SIP-04. How was responsibility divided within the team?

Answer: Our team grew from three to four C++ engineers. We worked with customer developers, a project manager, a web developer and QA. I focused on the phone application, SDK, provisioning and integration. Another developer owned the web frontend and REST implementation. Adding the stack to Yocto was team work.

QUESTION SIP-05. Did you own the BSP and board bring-up?

Answer: I mainly worked above new-board bring-up: application, SDK, recipes, packages and services. I used the existing BSP and investigated problems where the application met the platform. That is different from independently creating the kernel, bootloader and all board support.

SECTION 2. YOCTO AND STACK INTEGRATION

QUESTION SIP-06. Why did the product need Yocto?

Answer: We needed a complete image with matching applications, libraries, services, settings and model files. Yocto described how to build and include them. Copying one executable helped debugging, but it did not replace testing the actual firmware on the phone.

QUESTION SIP-07. How do you integrate Linphone SDK into a Yocto image?

Answer: Choose the SDK version and suitable recipes, then fix source versions, dependencies and cross-build settings. Install the outputs into staging and split them into packages. The application gets headers and libraries through its sysroot. Include runtime packages in the image, then test registration, calls and media on hardware.

QUESTION SIP-08. What is the difference between DEPENDS and RDEPENDS?

Answer: DEPENDS lists recipes needed to build the component. RDEPENDS lists packages needed when it runs on the phone. Yocto detects many shared-library dependencies automatically. Plugins and data may need explicit entries. A recipe name and its package names can differ.

QUESTION SIP-09. How do you keep the SDK build reproducible?

Answer: Fix source and layer revisions, dependencies and feature choices. SRC_URI lists source inputs and SRCREV pins Git sources. Check archives and licenses. Cache speeds up the work but does not replace these rules. Check that the build works without a developer-only workspace.

QUESTION SIP-10. What is tricky about the Linphone SDK build?

Answer: The SDK may build several components itself. All nested builds must use the device compiler and libraries. Avoid hidden downloads and accidental use of computer libraries. Choose the approach for the actual SDK release instead of assuming one CMake switch works everywhere.

SECTION 3. BUILD AND RUNTIME DIAGNOSIS

QUESTION SIP-11. The recipe builds, but the library is missing on target. What do you check?

Answer: I follow the file through do_install, package contents, image selection and the installed phone image. If the library exists but cannot load, I check architecture, loader, dependencies and permissions. Repeating compilation does not fix every installation problem.

QUESTION SIP-12. How do you fix installed-vs-shipped QA errors?

Answer: The recipe installed a file into staging but did not assign it to a package. Fix FILES or the install path, or stop installing an unwanted file. I would not disable the check globally because it can reveal a genuinely missing file.

QUESTION SIP-13. How do you detect accidental host dependencies?

Answer: I inspect configure logs, compiler, sysroot and actual link libraries. A computer library may not work on ARM64. Device dependencies and tools that execute on the build computer need separate handling. With CMake, I also inspect cached settings and nested builds.

QUESTION SIP-14. How would you build the application outside BitBake?

Answer: I would generate and install the matching image SDK, source its setup script and use its toolchain in a fresh build directory. Check the architecture and libraries. This helps development but does not replace the recipe or final image test.

QUESTION SIP-15. Why can the Qt application run manually but fail at boot?

Answer: A service may use a different user, environment, directory or startup conditions. I check files, libraries, its unit and logs. For graphics, Weston/Wayland and its socket matter. Find the real missing condition instead of adding an arbitrary delay.

QUESTION SIP-16. Does After=network.target guarantee SIP connectivity?

Answer: No. After= sets order but does not start a dependency or test a server. Even network-online cannot guarantee that the PBX stays reachable. The application and SDK still need failure handling and reconnection.

SECTION 4. SIP REGISTRATION AND FAILOVER

QUESTION SIP-17. What did your registration watchdog do?

Answer: I implemented registration monitoring and primary/backup switching in our customized SDK. Registration, active-server choice and authentication had to agree, then be shown correctly in the application. This was a software registration watchdog, not a hardware watchdog or the entire SIP stack.

QUESTION SIP-18. Why move server switching from Qt into the SDK?

Answer: The first Qt version duplicated SDK registration decisions. I reverted it and moved the main logic into the SDK. The application then followed SDK state instead of running another switching loop. This added fork maintenance but left one owner of registration behavior.

QUESTION SIP-19. How did you validate failover and failback?

Answer: On physical phones I reproduced primary-server loss and recovery. I compared SDK registration, active-server reports, SIP logs, authentication and UI. I also checked saved settings. I describe these tested scenarios rather than claim an unmeasured universal switching time.

QUESTION SIP-20. Does registration failover preserve an ongoing call?

Answer: Not automatically. Registration recovery and keeping an ongoing call are different requirements. Calls also have dialog and media state, and behavior depends on the PBX and network. Test ongoing calls separately; successful backup registration is not enough.

QUESTION SIP-21. Why can a different realm break backup authentication?

Answer: For the MD5 mechanism used here, HA1 = MD5(username:realm:password). A different realm changes the hash, so the primary value cannot simply be reused on backup. I worked on backup-domain and realm/HA1 support. HA1 selection was later disabled and stayed disabled at project end.

QUESTION SIP-22. What did you change in SIP realm discovery?

Answer: The probe needed to read challenges from different servers. I added WWW-Authenticate and Proxy-Authenticate handling, continued header lines and different realm formats. This avoided depending on one PBX response. It was a parser for the needed fields, not a full SIP stack.

SECTION 5. QT, CONCURRENCY AND MEDIA

QUESTION SIP-23. How did you connect asynchronous SDK events to the UI?

Answer: I separated models, controllers, sessions and services. SDK events updated state and the screen showed it. Event order and object lifetime matter: a callback can arrive after a screen or call closes. Widgets should not independently decide telephony state.

QUESTION SIP-24. What was the scope and status of the Qt refactor?

Answer: I gradually separated sessions, services, SDK adapters and presentation while preserving UI behavior and QObject signals. Focused tests and phone checks helped catch regressions. The broad refactor was completed as internal work, not a fully released customer feature.

QUESTION SIP-25. How would you handle callbacks crossing Qt threads?

Answer: First I would identify the callback thread and the receiving QObject thread. Send UI changes to the GUI thread through a suitable queued connection. Check receiver lifetime, argument types and late events. An asynchronous SDK operation does not make direct widget access safe.

QUESTION SIP-26. A call connects but has no audio or video. Where do you start?

Answer: I separate call setup from working audio/video. Identify the failing direction: capture or playback, local or remote. Then inspect SDK state, network, devices, settings and rendering. On the project I compared logs and repeated scenarios on the phone.

QUESTION SIP-27. What was your responsibility in WebRTC/mediasoup conferencing?

Answer: The team added WebRTC and mediasoup. My main work was the phone client and room behavior, UI, media integration and debugging. My contribution to the initial Node.js server was limited. I did not own the later server rewrite.

SECTION 6. VALIDATION, PROVISIONING AND LESSONS

QUESTION SIP-28. What did automated tests cover, and what needed hardware?

Answer: Qt Test checked specific logic, models, controllers and call sessions. Real audio, camera, GPIO, boot and SDK integration still needed a phone. Local tests protected particular changes; they did not prove complete coverage of the phone or every conference path.

QUESTION SIP-29. What did you do in the provisioning tool?

Answer: I migrated WinForms from .NET Framework 4.8 to .NET 8 and developed discovery, settings, DHCP/TFTP and project persistence. I used explicit project state instead of serializing the UI tree. I checked save, reopen and regenerated settings. Old BinaryFormatter files remained incompatible with the JSON reader.

QUESTION SIP-30. What is your strongest engineering lesson from this project?

Answer: The clearest lesson was moving failover from Qt to the SDK. I gave up the first approach when it duplicated state. The application then followed the SDK. The wider lesson was to identify the state owner and check the whole path from settings through SDK and UI to the device.

SECTION 7. CV AND UPDATE FOLLOW-UP QUESTIONS

QUESTION SIP-31. Were the old update.sh packages full firmware images?

Answer: No. They already updated selected files, but each update.sh was written by hand. The newer .NET workflow read the phone version and built a suitable package from saved releases. Full reflashing was a separate procedure.

QUESTION SIP-32. What exactly did recovery restore?

Answer: The phone’s exact old application, matching libraries, scripts, resources, permissions and active-release choice. Settings had to stay compatible or be restorable. This was application-stack rollback, not A/B rootfs or repair of a non-booting board.

QUESTION SIP-33. How do you explain the GPIO responsibility precisely?

Answer: The CV covers handset events, RGB LED, QThread, a singleton and deadlock/leak fixes. The key ideas are one GPIO owner, event delivery to the UI and clean shutdown. I cannot reliably name the exact original lock sequence or leaking allocation without the implementation.

QUESTION SIP-34. Which memory optimization can you defend?

Answer: I can explain feature choices, compiler settings and how to check memory, but I do not invent exact historic flags or percentages. Binary size and RAM use differ. Compare the same calls and media on the same phone and check that required functions still work.

QUESTION SIP-35. Did you own the whole web diagnostics download implementation?

Answer: No. Another developer owned the web frontend and REST code. My confirmed work includes comparing application, SIP and system logs and adding active-proxy diagnostics. I explain categories, journal limits and bundle sanitization separately from the full scope of my personally evidenced implementation.

QUESTION SIP-36. How would you demonstrate a useful Qt state test?

Answer: I would feed controlled events into a session/controller and check state and signals. After remote termination, a late media event must not reactivate the call. QSignalSpy helps observe signals, but it does not test physical audio or every conference path.

QUESTION SIP-37. How do you separate SIP, SDP and actual media?

Answer: SIP controls signaling and SDP describes media settings. Actual audio/video also depends on transport, devices and rendering. Successful setup does not prove working media. I look for the first part of that chain that fails.

QUESTION SIP-38. What did SNMP, DHCP, TFTP and SQLite each do?

Answer: SNMP read device information, DHCP options helped locate provisioning data, TFTP transferred files and SQLite stored tool data. I compared generated settings with phone behavior and checked project persistence. TFTP alone does not provide encryption or authentication.
