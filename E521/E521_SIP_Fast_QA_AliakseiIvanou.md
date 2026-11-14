SIP PROJECT: FAST Q&A

Request: E521
Project: SIP-BASED PHONE SOFTWARE
Candidate: Aliaksei Ivanou

SECTION 1. PROJECT AND OWNERSHIP

QUESTION SIP-01. Can you briefly describe the project?

Answer: I worked on SIP desk phones with audio-only and camera models. The product used C++17, Qt, Linphone SDK and Yocto Linux on NXP i.MX. My main work was the application, SDK, server failover, settings and device debugging. I also worked on recipes, packages and startup.

More detail: The difficult part was keeping several views of the same phone behavior consistent. An administrator could generate settings, the SDK could change registration state and the screen had to show the effective result. A locally correct change could still fail after deployment. That is why the work crossed application, SDK, image and physical-device checks.

QUESTION SIP-02. What existed before your team joined?

Answer: We received a basic Yocto skeleton without Linphone SDK, WebRTC or mediasoup. Our team added those components, their dependencies and the settings needed to run them. We inherited the board platform, then integrated the phone stack. My work was one part of that team effort.

More detail: The starting board software did not already solve the phone’s telephony and conferencing needs. We had to make the added components build together, enter the right packages and work after boot. This required more than linking a library on a developer computer. The final check was the behavior of the complete phone image.

QUESTION SIP-03. Which parts did you personally implement?

Answer: I implemented registration monitoring and primary/backup switching in the SDK, connected its APIs to the application and added a backup authentication domain. I also worked on Qt calls/accounts, provisioning, recipes and device tests. I did not own the whole product alone.

More detail: The failover work is a useful way to explain that division. I implemented SDK behavior and its application integration, while other parts of the product remained shared or separately owned. I also had to keep configuration and provisioning consistent with that behavior. I would describe those concrete changes before discussing general platform knowledge.

QUESTION SIP-04. How was responsibility divided within the team?

Answer: Our team grew from three to four C++ engineers. We worked with customer developers, a project manager, a web developer and QA. I focused on the phone application, SDK, provisioning and integration. Another developer owned the web frontend and REST implementation. Adding the stack to Yocto was team work.

More detail: Changes often crossed team boundaries even when the feature looked local. An account option could affect the UI, generated configuration and SDK authentication. We coordinated those interfaces and checked scenarios with QA. I would keep team delivery separate from personal authorship when describing a finished feature.

QUESTION SIP-05. Did you own the BSP and board bring-up?

Answer: I mainly worked above new-board bring-up: application, SDK, recipes, packages and services. I used the existing BSP and investigated problems where the application met the platform. That is different from independently creating the kernel, bootloader and all board support.

More detail: For example, a missing library or incorrect service setup can stop the phone application even with a working kernel. My integration work followed those failures through installed files and runtime services. I could investigate the hardware boundary without claiming to have designed the board. That distinction keeps the technical discussion tied to work I can explain.

SECTION 2. YOCTO AND STACK INTEGRATION

QUESTION SIP-06. Why did the product need Yocto?

Answer: We needed a complete image with matching applications, libraries, services, settings and model files. Yocto described how to build and include them. Copying one executable helped debugging, but it did not replace testing the actual firmware on the phone.

More detail: For a phone application, check both the executable package and its service unit. The unit must point to the installed path and have the intended enablement policy. Then boot the image without manually preparing the environment. This verifies the whole installation path, not only compilation.

QUESTION SIP-07. How do you integrate Linphone SDK into a Yocto image?

Answer: Choose the SDK version and suitable recipes, then fix source versions, dependencies and cross-build settings. Install the outputs into staging and split them into packages. The application gets headers and libraries through its sysroot. Include runtime packages in the image, then test registration, calls and media on hardware.

More detail: Take one missing file and follow it from ${D} to its output package and then to the image. This identifies the stage that lost it. A development header may correctly belong to -dev rather than the runtime package. Fix the assignment instead of placing every file into one package.

QUESTION SIP-08. What is the difference between DEPENDS and RDEPENDS?

Answer: DEPENDS lists recipes needed to build the component. RDEPENDS lists packages needed when it runs on the phone. Yocto detects many shared-library dependencies automatically. Plugins and data may need explicit entries. A recipe name and its package names can differ.

More detail: For example, the application needs SDK headers while building, but the phone needs runtime library packages. A generator used during compilation runs on the build computer instead. Identify which side needs each item. This prevents both missing device packages and accidental host-library use.

QUESTION SIP-09. How do you keep the SDK build reproducible?

Answer: Fix source and layer revisions, dependencies and feature choices. SRC_URI lists source inputs and SRCREV pins Git sources. Check archives and licenses. Cache speeds up the work but does not replace these rules. Check that the build works without a developer-only workspace.

More detail: The old release used for a delta must be the exact file that was distributed. A fresh build from the same tag may differ because of tools or packaging. Keep the released files and their checksums. Use those records to reject a delta when the phone’s starting files do not match.

QUESTION SIP-10. What is tricky about the Linphone SDK build?

Answer: The SDK may build several components itself. All nested builds must use the device compiler and libraries. Avoid hidden downloads and accidental use of computer libraries. Choose the approach for the actual SDK release instead of assuming one CMake switch works everywhere.

More detail: For an SDK component using CMake, start from the cmake class and inspect its generated configure command. Add only project-specific settings and missing dependencies. Check nested builds for the same toolchain. Reimplementing standard build steps can silently lose cross-compilation support.

SECTION 3. BUILD AND RUNTIME DIAGNOSIS

QUESTION SIP-11. The recipe builds, but the library is missing on target. What do you check?

Answer: I follow the file through do_install, package contents, image selection and the installed phone image. If the library exists but cannot load, I check architecture, loader, dependencies and permissions. Repeating compilation does not fix every installation problem.

More detail: For a phone that cannot load Linphone, compare the executable’s required libraries with the image contents. Check exact names, compatibility and plugin/data paths. A library in the build directory is not the same as a library installed on the phone. Confirm the actual deployed release before rebuilding.

QUESTION SIP-12. How do you fix installed-vs-shipped QA errors?

Answer: The recipe installed a file into staging but did not assign it to a package. Fix FILES or the install path, or stop installing an unwanted file. I would not disable the check globally because it can reveal a genuinely missing file.

More detail: Take one missing file and follow it from ${D} to its output package and then to the image. This identifies the stage that lost it. A development header may correctly belong to -dev rather than the runtime package. Fix the assignment instead of placing every file into one package.

QUESTION SIP-13. How do you detect accidental host dependencies?

Answer: I inspect configure logs, compiler, sysroot and actual link libraries. A computer library may not work on ARM64. Device dependencies and tools that execute on the build computer need separate handling. With CMake, I also inspect cached settings and nested builds.

More detail: For example, the application needs SDK headers while building, but the phone needs runtime library packages. A generator used during compilation runs on the build computer instead. Identify which side needs each item. This prevents both missing device packages and accidental host-library use.

QUESTION SIP-14. How would you build the application outside BitBake?

Answer: I would generate and install the matching image SDK, source its setup script and use its toolchain in a fresh build directory. Check the architecture and libraries. This helps development but does not replace the recipe or final image test.

More detail: For an external application build, source the SDK environment and check its compiler and sysroot. A code generator running on the computer needs a host-compatible executable instead. Do not reuse an old desktop CMake cache. Validate the produced binary against the libraries actually installed on the phone.

QUESTION SIP-15. Why can the Qt application run manually but fail at boot?

Answer: A service may use a different user, environment, directory or startup conditions. I check files, libraries, its unit and logs. For graphics, Weston/Wayland and its socket matter. Find the real missing condition instead of adding an arbitrary delay.

More detail: For example, Weston may have started but the application may lack its socket path or permissions. Compare the service user and display-related environment with a working launch. Check device access separately. Avoid granting broad privileges just to make one startup symptom disappear.

QUESTION SIP-16. Does After=network.target guarantee SIP connectivity?

Answer: No. After= sets order but does not start a dependency or test a server. Even network-online cannot guarantee that the PBX stays reachable. The application and SDK still need failure handling and reconnection.

More detail: A phone can have an address while its configured PBX is unreachable. Treat initial network setup and later server availability separately. Let the application report registration state and retry as designed. Otherwise an unrelated server outage may be mistaken for a boot failure.

SECTION 4. SIP REGISTRATION AND FAILOVER

QUESTION SIP-17. What did your registration watchdog do?

Answer: I implemented registration monitoring and primary/backup switching in our customized SDK. Registration, active-server choice and authentication had to agree, then be shown correctly in the application. This was a software registration watchdog, not a hardware watchdog or the entire SIP stack.

More detail: Registration supervision needed one consistent view of which server was active. The SDK reported that state and the application used it for display and configuration. I checked server-loss and recovery behavior instead of treating two stored addresses as a complete solution. The exact retry timing should be taken from the implementation, not invented for the interview.

QUESTION SIP-18. Why move server switching from Qt into the SDK?

Answer: The first Qt version duplicated SDK registration decisions. I reverted it and moved the main logic into the SDK. The application then followed SDK state instead of running another switching loop. This added fork maintenance but left one owner of registration behavior.

More detail: Keeping another switch loop in Qt meant it could act while the SDK was already retrying or processing authentication. The two layers could disagree about the active server. Putting the decision beside registration removed that competing owner. The cost was maintaining and testing project-specific changes in the SDK fork.

QUESTION SIP-19. How did you validate failover and failback?

Answer: On physical phones I reproduced primary-server loss and recovery. I compared SDK registration, active-server reports, SIP logs, authentication and UI. I also checked saved settings. I describe these tested scenarios rather than claim an unmeasured universal switching time.

More detail: I checked both directions: moving to backup and returning after primary recovery. The visible account state had to match the SDK and authentication context, not merely show a successful request. Persistence mattered too, so restart could not silently undo the configuration. Those checks were performed on phones because the whole runtime participated.

QUESTION SIP-20. Does registration failover preserve an ongoing call?

Answer: Not automatically. Registration recovery and keeping an ongoing call are different requirements. Calls also have dialog and media state, and behavior depends on the PBX and network. Test ongoing calls separately; successful backup registration is not enough.

More detail: A phone can register successfully on a backup while an earlier call still depends on its original dialog and media path. Those are not the same state. A separate test would keep a call active while the relevant failure occurs and observe signaling and media. I would report that result separately from registration recovery.

QUESTION SIP-21. Why can a different realm break backup authentication?

Answer: For the MD5 mechanism used here, HA1 = MD5(username:realm:password). A different realm changes the hash, so the primary value cannot simply be reused on backup. I worked on backup-domain and realm/HA1 support. HA1 selection was later disabled and stayed disabled at project end.

More detail: The stored hash therefore has meaning only with the matching username and realm. Switching a server address without the corresponding authentication context can fail even when the password is unchanged. I worked on that connection between backup settings and SDK authentication. I also distinguish that implementation from the later release decision to disable HA1 selection.

QUESTION SIP-22. What did you change in SIP realm discovery?

Answer: The probe needed to read challenges from different servers. I added WWW-Authenticate and Proxy-Authenticate handling, continued header lines and different realm formats. This avoided depending on one PBX response. It was a parser for the needed fields, not a full SIP stack.

More detail: A useful regression set includes different parameter orders, continued lines and the supported forms of realm quoting. It should also cover absent or unusable challenge data. The probe needs a clear failure instead of producing an apparently valid hash from the wrong realm. Passing those cases does not imply compatibility with every possible SIP implementation.

SECTION 5. QT, CONCURRENCY AND MEDIA

QUESTION SIP-23. How did you connect asynchronous SDK events to the UI?

Answer: I separated models, controllers, sessions and services. SDK events updated state and the screen showed it. Event order and object lifetime matter: a callback can arrive after a screen or call closes. Widgets should not independently decide telephony state.

More detail: A GPIO worker and the UI can access the same object, so a valid pointer does not make concurrent access safe. Identify who changes each field and who deletes the object. Pass commands or protect shared state consistently. Test shutdown while an event is being delivered.

QUESTION SIP-24. What was the scope and status of the Qt refactor?

Answer: I gradually separated sessions, services, SDK adapters and presentation while preserving UI behavior and QObject signals. Focused tests and phone checks helped catch regressions. The broad refactor was completed as internal work, not a fully released customer feature.

More detail: The existing screens and signal connections limited how much could safely change at once. I moved responsibilities gradually and checked that the same user actions still had the same result. Late callbacks and teardown were important because an old screen could outlive a call transition. Internal completion of the refactor remained separate from customer release status.

QUESTION SIP-25. How would you handle callbacks crossing Qt threads?

Answer: First I would identify the callback thread and the receiving QObject thread. Send UI changes to the GUI thread through a suitable queued connection. Check receiver lifetime, argument types and late events. An asynchronous SDK operation does not make direct widget access safe.

More detail: For example, a worker waiting forever for a handset edge may never read a queued stop command. Give that wait a timeout or a wake-up path. Stop new work, finish the current operation and wait for thread exit before deletion. Test stopping while no GPIO event arrives.

QUESTION SIP-26. A call connects but has no audio or video. Where do you start?

Answer: I separate call setup from working audio/video. Identify the failing direction: capture or playback, local or remote. Then inspect SDK state, network, devices, settings and rendering. On the project I compared logs and repeated scenarios on the phone.

More detail: For example, an incoming video call can be established while local capture or rendering still fails. I would check each direction and component rather than change SIP registration first. The UI should show effective SDK/media state and release old bindings during teardown. Repeating the scenario on a physical phone separates device behavior from a desktop-only result.

QUESTION SIP-27. What was your responsibility in WebRTC/mediasoup conferencing?

Answer: The team added WebRTC and mediasoup. My main work was the phone client and room behavior, UI, media integration and debugging. My contribution to the initial Node.js server was limited. I did not own the later server rewrite.

More detail: Joining a room, showing a participant and receiving useful media are separate steps. Leaving during an update or rejecting an invite also needs correct cleanup. I concentrated on how the native phone client and UI followed those changes. I keep that detailed phone-side work separate from ownership of the complete server implementation.

SECTION 6. VALIDATION, PROVISIONING AND LESSONS

QUESTION SIP-28. What did automated tests cover, and what needed hardware?

Answer: Qt Test checked specific logic, models, controllers and call sessions. Real audio, camera, GPIO, boot and SDK integration still needed a phone. Local tests protected particular changes; they did not prove complete coverage of the phone or every conference path.

More detail: A unit test can confirm that a remote hangup ends a call model. It cannot show that the handset microphone is routed correctly. Keep a small device checklist for boot, media and hardware. Record the tested image so a later result can be compared with the same build.

QUESTION SIP-29. What did you do in the provisioning tool?

Answer: I migrated WinForms from .NET Framework 4.8 to .NET 8 and developed discovery, settings, DHCP/TFTP and project persistence. I used explicit project state instead of serializing the UI tree. I checked save, reopen and regenerated settings. Old BinaryFormatter files remained incompatible with the JSON reader.

More detail: A saved project was useful only if reopening it regenerated the intended phone configuration. Explicit state made missing fields and defaults easier to see than serializing live controls. I checked the supported format through save/open and output behavior. I did not present the incompatible old BinaryFormatter files as automatically migrated.

QUESTION SIP-30. What is your strongest engineering lesson from this project?

Answer: The clearest lesson was moving failover from Qt to the SDK. I gave up the first approach when it duplicated state. The application then followed the SDK. The wider lesson was to identify the state owner and check the whole path from settings through SDK and UI to the device.

More detail: The same lesson applied outside SIP switching. A generated setting, a saved value and the SDK’s effective state could differ even though each individual component appeared correct. I compared them through a complete device scenario. That helped locate the first disagreement instead of fixing only the screen that exposed it.

SECTION 7. CV AND UPDATE FOLLOW-UP QUESTIONS

QUESTION SIP-31. Were the old update.sh packages full firmware images?

Answer: No. They already updated selected files, but each update.sh was written by hand. The newer .NET workflow read the phone version and built a suitable package from saved releases. Full reflashing was a separate procedure.

More detail: The new package was built from the detected starting release and chosen target release using saved artifacts. It did not compile a new C++ program for each phone. File checks prevented applying a delta to an unexpected base. The phone then owned installation and recovery even if the Windows connection disappeared.

QUESTION SIP-32. What exactly did recovery restore?

Answer: The phone’s exact old application, matching libraries, scripts, resources, permissions and active-release choice. Settings had to stay compatible or be restorable. This was application-stack rollback, not A/B rootfs or repair of a non-booting board.

More detail: Before activation, record the exact previous release and preserve its complete matching files. Keep a way to select them again after failure. Check shared settings as well as binaries. Recovery is incomplete if the old executable returns but can no longer read the data it needs.

QUESTION SIP-33. How do you explain the GPIO responsibility precisely?

Answer: The CV covers handset events, RGB LED, QThread, a singleton and deadlock/leak fixes. The key ideas are one GPIO owner, event delivery to the UI and clean shutdown. I cannot reliably name the exact original lock sequence or leaking allocation without the implementation.

More detail: For example, a worker waiting forever for a handset edge may never read a queued stop command. Give that wait a timeout or a wake-up path. Stop new work, finish the current operation and wait for thread exit before deletion. Test stopping while no GPIO event arrives.

QUESTION SIP-34. Which memory optimization can you defend?

Answer: I can explain feature choices, compiler settings and how to check memory, but I do not invent exact historic flags or percentages. Binary size and RAM use differ. Compare the same calls and media on the same phone and check that required functions still work.

More detail: For example, removing an unused feature can reduce its code and dependencies, but removing a required codec breaks calls. Compare the same device workload before and after. Keep symbols for diagnosis outside the production image. Report only the size or memory change that was actually measured.

QUESTION SIP-35. Did you own the whole web diagnostics download implementation?

Answer: No. Another developer owned the web frontend and REST code. My confirmed work includes comparing application, SIP and system logs and adding active-proxy diagnostics. I explain categories, journal limits and bundle sanitization separately from the full scope of my personally evidenced implementation.

More detail: A useful support bundle has enough timing and version information to connect a reported incident with the device state. That does not require sending passwords or full sensitive configuration. Missing log sources should be visible as a partial collection. The separate web owner still controls the web interface that makes the bundle downloadable.

QUESTION SIP-36. How would you demonstrate a useful Qt state test?

Answer: I would feed controlled events into a session/controller and check state and signals. After remote termination, a late media event must not reactivate the call. QSignalSpy helps observe signals, but it does not test physical audio or every conference path.

More detail: I would check both the final state and the number and arguments of the important signals. A duplicate callback must not create a second active session. Waiting should process the relevant event loop rather than rely on a long sleep. Hardware tests remain necessary for the actual media and device path.

QUESTION SIP-37. How do you separate SIP, SDP and actual media?

Answer: SIP controls signaling and SDP describes media settings. Actual audio/video also depends on transport, devices and rendering. Successful setup does not prove working media. I look for the first part of that chain that fails.

More detail: An account can register and a call can be accepted while media has a separate failure. Compare the description that was negotiated with the selected codecs, endpoints and local devices. Then locate whether capture, transmission or rendering stops working. This prevents one successful signaling message from being treated as proof that the whole conversation works.

QUESTION SIP-38. What did SNMP, DHCP, TFTP and SQLite each do?

Answer: SNMP read device information, DHCP options helped locate provisioning data, TFTP transferred files and SQLite stored tool data. I compared generated settings with phone behavior and checked project persistence. TFTP alone does not provide encryption or authentication.

More detail: For example, successful device discovery does not prove that the phone downloaded or applied its configuration. Check discovery, file generation, delivery and effective phone settings separately. SQLite persistence adds another check: reopening a saved project should keep the intended values. Network trust and access controls must be considered because TFTP does not provide them itself.
