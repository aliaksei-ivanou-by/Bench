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

More detail: For failover, my responsibility included both the SDK change and the application integration. I also aligned settings and provisioning with that behavior. Other product areas remained shared or separately owned. This is the concrete work I can use to explain my contribution.

QUESTION SIP-04. How was responsibility divided within the team?

Answer: Our team grew from three to four C++ engineers. We worked with customer developers, a project manager, a web developer and QA. I focused on the phone application, SDK, provisioning and integration. Another developer owned the web frontend and REST implementation. Adding the stack to Yocto was team work.

More detail: An account option could affect the UI, generated configuration and SDK authentication at the same time. We agreed those interfaces and checked device scenarios with QA. The feature therefore crossed several people’s areas of responsibility. I distinguish that team result from the changes I personally implemented.

QUESTION SIP-05. Did you own the BSP and board bring-up?

Answer: I mainly worked above new-board bring-up: application, SDK, recipes, packages and services. I used the existing BSP and investigated problems where the application met the platform. That is different from independently creating the kernel, bootloader and all board support.

More detail: A missing library or wrong service setup can stop the application while the kernel works correctly. I followed such failures through installed files and services. That required understanding the platform interface, but not designing the board myself. My strongest detail is application and SDK integration on the running phone.

SECTION 2. YOCTO AND STACK INTEGRATION

QUESTION SIP-06. Why did the product need Yocto?

Answer: We needed a complete image with matching applications, libraries, services, settings and model files. Yocto described how to build and include them. Copying one executable helped debugging, but it did not replace testing the actual firmware on the phone.

More detail: For a complete image, I would check that the executable and its service unit both enter the package. The unit must use the installed path and intended startup settings. I would then boot without manually preparing the environment. That tests delivery and startup together instead of only compilation.

QUESTION SIP-07. How do you integrate Linphone SDK into a Yocto image?

Answer: Choose the SDK version and suitable recipes, then fix source versions, dependencies and cross-build settings. Install the outputs into staging and split them into packages. The application gets headers and libraries through its sysroot. Include runtime packages in the image, then test registration, calls and media on hardware.

More detail: I would follow one SDK file from installation staging into its package and then the image. Headers may correctly go into a development package, while runtime libraries belong on the phone. I would check that split rather than put everything into one package. Finally I would start the consuming application on the device.

QUESTION SIP-08. What is the difference between DEPENDS and RDEPENDS?

Answer: DEPENDS lists recipes needed to build the component. RDEPENDS lists packages needed when it runs on the phone. Yocto detects many shared-library dependencies automatically. Plugins and data may need explicit entries. A recipe name and its package names can differ.

More detail: For this application, SDK headers are needed while compiling and SDK libraries when the phone runs. A source generator is different: it executes on the build computer. I would identify the consumer of every dependency. That avoids missing phone packages and accidentally linking computer libraries into ARM software.

QUESTION SIP-09. How do you keep the SDK build reproducible?

Answer: Fix source and layer revisions, dependencies and feature choices. SRC_URI lists source inputs and SRCREV pins Git sources. Check archives and licenses. Cache speeds up the work but does not replace these rules. Check that the build works without a developer-only workspace.

More detail: A repeatable build records layer revisions, SDK and submodule revisions, the toolchain and enabled features. A source revision and a matching version label alone do not guarantee identical output bytes. Updates and rollback separately retain the actual released files, inventories and checksums. Binary deltas are an additional delivery option, not a required part of the partial-update workflow described here.

QUESTION SIP-10. What is tricky about the Linphone SDK build?

Answer: The SDK may build several components itself. All nested builds must use the device compiler and libraries. Avoid hidden downloads and accidental use of computer libraries. Choose the approach for the actual SDK release instead of assuming one CMake switch works everywhere.

More detail: For a CMake SDK component, I would start from the cmake class and inspect its configure command. Then I would add project options and missing dependencies. Nested builds need the same device toolchain. Rewriting standard tasks from scratch risks losing that cross-build setup.

SECTION 3. BUILD AND RUNTIME DIAGNOSIS

QUESTION SIP-11. The recipe builds, but the library is missing on target. What do you check?

Answer: I follow the file through do_install, package contents, image selection and the installed phone image. If the library exists but cannot load, I check architecture, loader, dependencies and permissions. Repeating compilation does not fix every installation problem.

More detail: If Linphone cannot load, I would compare required libraries with the deployed image. I would check exact names, ABI, plugin paths and required data. A file in the build directory is not proof that it reached the phone. I would confirm the running release before deciding to rebuild it.

QUESTION SIP-12. How do you fix installed-vs-shipped QA errors?

Answer: The recipe installed a file into staging but did not assign it to a package. Fix FILES or the install path, or stop installing an unwanted file. I would not disable the check globally because it can reveal a genuinely missing file.

More detail: I would trace the reported path from ${D} to the intended package and image. That shows whether the install location or package assignment is wrong. Some files correctly belong in -dev rather than the runtime package. I would fix the specific rule instead of disabling QA.

QUESTION SIP-13. How do you detect accidental host dependencies?

Answer: I inspect configure logs, compiler, sysroot and actual link libraries. A computer library may not work on ARM64. Device dependencies and tools that execute on the build computer need separate handling. With CMake, I also inspect cached settings and nested builds.

More detail: For each input I would establish whether it belongs to the device build or runs on the computer. SDK headers and link libraries must match ARM64. Build-time generators need executables for the computer. This separation makes an accidental host dependency easier to identify.

QUESTION SIP-14. How would you build the application outside BitBake?

Answer: I would generate and install the matching image SDK, source its setup script and use its toolchain in a fresh build directory. Check the architecture and libraries. This helps development but does not replace the recipe or final image test.

More detail: I would verify the SDK compiler and sysroot before configuring the application. I would use a fresh CMake directory rather than a desktop build cache. The result must match the libraries on the phone. That confirms a useful development build, while the maintained recipe still controls product delivery.

QUESTION SIP-15. Why can the Qt application run manually but fail at boot?

Answer: A service may use a different user, environment, directory or startup conditions. I check files, libraries, its unit and logs. For graphics, Weston/Wayland and its socket matter. Find the real missing condition instead of adding an arbitrary delay.

More detail: For the graphical application, I would compare the service user and display environment with a working manual launch. Weston may have started while the required socket is still unavailable. Hardware permissions are another separate check. I would fix the missing condition instead of granting broad privileges or adding a blind delay.

QUESTION SIP-16. Does After=network.target guarantee SIP connectivity?

Answer: No. After= sets order but does not start a dependency or test a server. Even network-online cannot guarantee that the PBX stays reachable. The application and SDK still need failure handling and reconnection.

More detail: A phone may have an IP address but still be unable to reach its PBX. I would keep initial network setup separate from later server availability. Registration state and retries belong in the application/SDK behavior. Otherwise a server outage can look like a local boot failure.

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

More detail: For example, a call-ended event and a late media event may arrive close together. The handler checks session identity and current state so a completed call cannot become active again. The screen receives effective state through a model or controller. Destruction disconnects the relevant handlers; a pointer having once been valid is not enough.

QUESTION SIP-24. What was the scope and status of the Qt refactor?

Answer: I gradually separated sessions, services, SDK adapters and presentation while preserving UI behavior and QObject signals. Focused tests and phone checks helped catch regressions. The broad refactor was completed as internal work, not a fully released customer feature.

More detail: The existing screens and signal connections limited how much could safely change at once. I moved responsibilities gradually and checked that the same user actions still had the same result. Late callbacks and teardown were important because an old screen could outlive a call transition. Internal completion of the refactor remained separate from customer release status.

QUESTION SIP-25. How would you handle callbacks crossing Qt threads?

Answer: First I would identify the callback thread and the receiving QObject thread. Send UI changes to the GUI thread through a suitable queued connection. Check receiver lifetime, argument types and late events. An asynchronous SDK operation does not make direct widget access safe.

More detail: With a queued connection, delivery runs in the receiver’s thread when that thread processes its event loop. Arguments must be safe to retain for deferred delivery; custom Qt 5 types may require metatype registration. BlockingQueuedConnection is unsafe within the same thread or when it creates a wait cycle. Disconnecting does not automatically retract an already queued event, so session-validity checks remain necessary.

QUESTION SIP-26. A call connects but has no audio or video. Where do you start?

Answer: I separate call setup from working audio/video. Identify the failing direction: capture or playback, local or remote. Then inspect SDK state, network, devices, settings and rendering. On the project I compared logs and repeated scenarios on the phone.

More detail: For example, an incoming video call can be established while local capture or rendering still fails. I would check each direction and component rather than change SIP registration first. The UI should show effective SDK/media state and release old bindings during teardown. Repeating the scenario on a physical phone separates device behavior from a desktop-only result.

QUESTION SIP-27. What was your responsibility in WebRTC/mediasoup conferencing?

Answer: The team added WebRTC and mediasoup. My main work was the phone client and room behavior, UI, media integration and debugging. My contribution to the initial Node.js server was limited. I did not own the later server rewrite.

More detail: Joining a room, showing a participant and receiving useful media are separate steps. Leaving during an update or rejecting an invite also needs correct cleanup. I concentrated on how the native phone client and UI followed those changes. I keep that detailed phone-side work separate from ownership of the complete server implementation.

SECTION 6. VALIDATION, PROVISIONING AND LESSONS

QUESTION SIP-28. What did automated tests cover, and what needed hardware?

Answer: Qt Test checked specific logic, models, controllers and call sessions. Real audio, camera, GPIO, boot and SDK integration still needed a phone. Local tests protected particular changes; they did not prove complete coverage of the phone or every conference path.

More detail: A local test can confirm that remote hangup ends a model, but cannot verify the physical microphone path. I would keep separate device checks for boot, media and GPIO. Each result needs the tested image identity. That makes later regressions comparable to a known build.

QUESTION SIP-29. What did you do in the provisioning tool?

Answer: I migrated WinForms from .NET Framework 4.8 to .NET 8 and developed discovery, settings, DHCP/TFTP and project persistence. I used explicit project state instead of serializing the UI tree. I checked save, reopen and regenerated settings. Old BinaryFormatter files remained incompatible with the JSON reader.

More detail: A saved project was useful only if reopening it regenerated the intended phone configuration. Explicit state made missing fields and defaults easier to see than serializing live controls. I checked the supported format through save/open and output behavior. I did not present the incompatible old BinaryFormatter files as automatically migrated.

QUESTION SIP-30. What is your strongest engineering lesson from this project?

Answer: The clearest lesson was moving failover from Qt to the SDK. I gave up the first approach when it duplicated state. The application then followed the SDK. The wider lesson was to identify the state owner and check the whole path from settings through SDK and UI to the device.

More detail: The same lesson applied outside SIP switching. A generated setting, a saved value and the SDK’s effective state could differ even though each individual component appeared correct. I compared them through a complete device scenario. That helped locate the first disagreement instead of fixing only the screen that exposed it.

SECTION 7. CV AND UPDATE FOLLOW-UP QUESTIONS

QUESTION SIP-31. Were the old update.sh packages full firmware images?

Answer: No. They already updated selected files, but each update.sh was written by hand. The newer .NET workflow read the phone version and built a suitable package from saved releases. Full reflashing was a separate procedure.

More detail: The package was assembled from the starting and selected target releases using saved artifacts. C++ was not recompiled for every phone. Changed files were transferred in full, unchanged files were omitted and removals were explicit. After transfer, the phone performed installation and recovery independently even if the Windows tool disconnected.

QUESTION SIP-32. What exactly did recovery restore?

Answer: Recovery restored the exact previous affected application files, matching libraries, scripts, resources, permissions and version record. Replaced or deleted files came back from backups, and newly added files were removed. Settings had to remain compatible or be restorable. This was file-based rollback, not release-directory switching, A/B rootfs or repair of a non-booting board.

More detail: Before changing files, their original contents and properties were saved together with a reverse-operation journal. Failure undid operations in reverse order and allowed an interrupted step to be repeated. After a reboot, recovery had to run before the ordinary application. Restoring the version label alone was insufficient: actual files and local startup of the previous software were checked.

QUESTION SIP-33. How do you explain the GPIO responsibility precisely?

Answer: The CV covers handset events, RGB LED, QThread, a singleton and deadlock/leak fixes. The key ideas are one GPIO owner, event delivery to the UI and clean shutdown. I cannot reliably name the exact original lock sequence or leaking allocation without the implementation.

More detail: A key failure to investigate is a worker that cannot leave its GPIO wait during shutdown. I would check its timeout or wake-up path and the order of cleanup. Singleton initialization does not solve concurrent method access. The precise old lock or allocation defect still needs its implementation history.

QUESTION SIP-34. Which memory optimization can you defend?

Answer: I can explain feature choices, compiler settings and how to check memory, but I do not invent exact historic flags or percentages. Binary size and RAM use differ. Compare the same calls and media on the same phone and check that required functions still work.

More detail: Removing an unused feature may remove code and dependencies, while removing a required codec breaks calls. I would compare the same target workload before and after a change. Matching symbols should remain available outside the production image. I would report only measured size or memory results.

QUESTION SIP-35. Did you own the whole web diagnostics download implementation?

Answer: No. Another developer owned the web frontend and REST code. My confirmed work includes comparing application, SIP and system logs and adding active-proxy diagnostics. I explain categories, journal limits and bundle sanitization separately from the full scope of my personally evidenced implementation.

More detail: A useful support bundle has enough timing and version information to connect a reported incident with the device state. That does not require sending passwords or full sensitive configuration. Missing log sources should be visible as a partial collection. The separate web owner still controls the web interface that makes the bundle downloadable.

QUESTION SIP-36. How would you demonstrate a useful Qt state test?

Answer: I would feed controlled events into a session/controller and check state and signals. After remote termination, a late media event must not reactivate the call. QSignalSpy helps observe signals, but it does not test physical audio or every conference path.

More detail: I would check both the final state and the number and arguments of the important signals. A duplicate callback must not create a second active session. Waiting should process the relevant event loop rather than rely on a long sleep. Hardware tests remain necessary for the actual media and device path.

QUESTION SIP-37. How do you separate SIP, SDP and actual media?

Answer: SIP controls signaling and SDP describes media settings. Actual audio/video also depends on transport, devices and rendering. Successful setup does not prove working media. I look for the first part of that chain that fails.

More detail: I would first separate registration and call acceptance from actual media. Then I would compare the agreed media settings with the selected codecs, endpoints and local devices. That helps locate whether capture, transmission or rendering is failing. One successful signaling message is not enough to prove the conversation works.

QUESTION SIP-38. What did SNMP, DHCP, TFTP and SQLite each do?

Answer: SNMP read device information, DHCP options helped locate provisioning data, TFTP transferred files and SQLite stored tool data. I compared generated settings with phone behavior and checked project persistence. TFTP alone does not provide encryption or authentication.

More detail: Successful discovery did not by itself prove that the phone downloaded and applied its settings. I would check discovery, file generation, delivery and effective settings separately. Reopening a saved project also had to keep the intended values. TFTP required a trusted delivery environment because it did not provide encryption or authentication itself.

SECTION 8. ORIGINAL RECIPE AND PHONE BEHAVIOR FOLLOW-UPS

QUESTION SIP-39. Which source version does your supplied original recipe actually build?

Answer: The recipe is named latest, but that is only its recipe version. It fetches the configured Git source on main. An explicit LINPHONE_SDK_REV can pin the commit; otherwise DEFAULT_COMMIT is AUTOREV in this snapshot. The version text passed to CMake does not pin the source.

More detail: I would inspect expanded SRCREV, the actual checked-out commit and recorded submodule commits. LINPHONE_SDK_BRANCH is read but the fetch URI uses literal main, so changing that environment variable alone has no effect on the branch. The environment hook must also be passed into BitBake correctly. These observations explain the supplied snapshot, not the exact inputs of every historical release.

QUESTION SIP-40. Does disabling video remove all Qt and video dependencies?

Answer: Not in the supplied recipe. PACKAGECONFIG selects supported feature arguments and their conditional dependencies, but DEPENDS also contains unconditional Qt and codec entries. Removing video does not remove those direct entries automatically. The final feature arguments and source defaults still determine what is compiled.

More detail: The enabled video branch sets X11/XVideo options, while its disabled branch sets ENABLE_VIDEO=NO. I would inspect PACKAGECONFIG_CONFARGS and CMakeCache rather than assume a symmetric switch. The default zxing entry also needs a matching definition from this recipe or an append. Hardware-specific g2d and imxvpuh264 depend on compatible BSP providers, so the phone variant is not a drop-in generic QEMU build.

QUESTION SIP-41. How do the intermediate SDK directory, sysroot and /opt fit together?

Answer: The original recipe uses an intermediate SDK tree under WORKDIR/build/linphone-sdk/desktop. Installation is then arranged under D so the final device path is /opt/belledonne-communications. SYSROOT_DIRS publishes selected installed content to dependent recipes. The application uses that content while compiling; the phone uses separately installed runtime packages.

More detail: I would check the actual generated install command because the custom and standard CMake classes interact. I would then follow one header and one shared library through staging, sysroot and package contents. rpath-link only helps the build-time linker; it does not teach the phone loader where /opt libraries live. The loader path and any required cache handling must be checked separately.

QUESTION SIP-42. Does RPROVIDES:${PN} = "liblinphone" create a liblinphone build provider?

Answer: No. RPROVIDES declares runtime aliases for an output package. PROVIDES names recipe-level build providers. The supplied SDK recipe lists many runtime component aliases, but that does not create independent recipes for all those components. A consuming recipe should use the actual build provider in DEPENDS.

More detail: I would use show-recipes to inspect build providers and pkgdata to inspect output packages. PACKAGES and FILES then determine which files belong to each package. That is also why a successful alias lookup does not prove that the package contains the required .so. Runtime dependency resolution and file presence are separate checks.

QUESTION SIP-43. Should a 401 or 407 response trigger immediate SIP failover?

Answer: No. A 401 or 407 can be a normal authentication challenge. The SDK must use the appropriate challenge and authentication context before deciding that registration failed. Server reachability, rejected credentials and a normal challenge are different conditions. A failover policy should distinguish them instead of rotating servers on every response.

More detail: For the project’s MD5 variant, a stored HA1 must match the username and realm. I would compare the challenge, selected account and active server, then inspect the resulting registration state. I would not invent retry counts or switch delays without the implementation. Successful backup registration also says nothing by itself about preserving an existing call.

QUESTION SIP-44. Can you explain a basic SIP call and the difference between CANCEL and BYE?

Answer: A caller sends INVITE, potentially with an SDP offer. Provisional responses such as 180 or 183 report progress. A successful final response is acknowledged, while the negotiated audio/video follows a media path such as RTP. SIP signaling and actual media therefore need separate observations.

More detail: CANCEL attempts to stop a pending request such as an unanswered INVITE; BYE terminates an established dialog/session. Cancellation can race with a successful answer, so the implementation must handle the actual final state rather than merely close the screen. For a failed call I would correlate dialog/transaction identifiers and SDK events with the UI. This is a protocol explanation, not a claim that I implemented a SIP stack from scratch.

QUESTION SIP-45. How do you keep C++ ownership safe around C SDK objects and Qt callbacks?

Answer: First identify whether an SDK pointer is borrowed or owns a reference. Release an owned reference with the matching SDK API, not an arbitrary delete. A C++ RAII wrapper can make that release explicit. Qt parent ownership is another model and must not compete with an independent owner of the same object.

More detail: For callbacks, I would stop new events, detach callbacks where supported and ensure no in-flight work can access destroyed state. Shared ownership alone does not make mutable objects thread-safe. I would also check what happens if initialization fails halfway or shutdown occurs during a callback. The exact ref/unref contract comes from the SDK version and API being used.

QUESTION SIP-46. Why can replacing only liblinphone.so break a partial update?

Answer: The application, SDK dependencies and plugins form a compatible software set. A library with the expected filename can still expose an incompatible ABI or require different plugins and data. I would build the package from the selected source and target release inventories. The package must include every required change and explicit removal, not only the most visible .so.

More detail: Before installation, retain the previous affected files and metadata for reverse restoration. After installation, verify real files and local application/Core startup before confirming the new version. Package checksums detect corruption or an unexpected file, but do not by themselves prove authenticity. Signatures, binary deltas and A/B slots are separate mechanisms and should not be described as deployed merely because the update is called incremental.

SECTION 9. TECHNICAL SOURCES

Research date: 2026-11-15.

- https://doc.qt.io/archives/qt-5.15/threads-qobject.html
- https://doc.qt.io/archives/qt-5.15/qobject.html
- https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html
- https://www.rfc-editor.org/rfc/rfc3261.html
- https://github.com/BelledonneCommunications/liblinphone/blob/5.3.0/include/linphone/core.h
