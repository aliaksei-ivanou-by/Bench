SELF INTRO

SECTION 1. DOCUMENT INFORMATION

Request ID: E521
Candidate: Aliaksei Ivanou, presented in the CV as Alex I.
Target role: Senior C++ Engineer – Yocto Linux
CV source: E521 Aliaksei Ivanou (13, C++).pdf
Source request: E521_Request_AliakseiIvanou.md
Preparation language: English
Delivery format: Domain-based spoken introduction with a detailed latest-project section
Estimated spoken duration: 5–6 minutes

SECTION 2. INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou. I am a software engineer with more than fourteen years across engineering and research and development. My main focus is C and C++ development, and my recent work combines C++17, Qt and embedded Linux with Yocto. Earlier in my career I developed image-processing algorithms in MATLAB.

I will describe my background through the domains I have worked in and then explain my latest embedded project in more detail.

The first domain is telecommunications and embedded devices. I work as a Software Engineer on SIP-Based Phone Software, a desk-phone platform for audio and video communication. My work spans the C++ and Qt application, a customized Linphone SDK, device provisioning and integration with a Yocto-based Linux system on NXP i.MX hardware. I will return to the platform after the domain overview.

The second domain is library systems and long-lived backend software. I worked as a Software Engineer on Library System. I was one of three C developers sharing responsibility for an established C89 backend. I implemented features, fixes and refactoring across C, occasionally changing Java or Scala. I traced failures through service logs and used gdb, core dumps and Valgrind on Linux. PostgreSQL and MySQL supported the data services.

The third domain is industrial measurement. I worked as a Software Engineer on 3D Reconstruction Software for Industrial Applications. I developed a C++ prototype that combined profiles from multiple 2D laser scanners into a point cloud. I used Point Cloud Library for reconstruction and Open3D for comparison and visualization, checking intermediate stages against recorded data.

The fourth domain is aerospace and UAV imaging. I worked as a Software Engineer on Software Modules for UAV, developing MATLAB algorithms for debayering, format conversion, stabilization and image fusion. I verified algorithms on representative imagery and participated in UAV flight tests as an optical-payload operator.

I worked as a Software Engineer on Remote Sensing Satellites Database. I built a Ruby on Rails and PostgreSQL reference database for querying satellite and mission parameters.

I worked as a Software Engineer on Software for Processing and Analysis of Satellite Earth Observation Images. My MATLAB work included frame stitching, radiometric matching, image-type prediction, automated resolution assessment and an ADPCM-family compression algorithm. For onboard compression, I designed and verified the algorithm against a limited computation budget; the flight-software team handled implementation on the target.

I would now like to explain the SIP phone project in more detail, because it is the closest match to this role.

The product supports audio-only and camera-enabled phones. Its software includes a Qt application, a customized SIP SDK, provisioning tools and an embedded Linux image. User-visible state depends on generated configuration, device settings, the SDK and application models. I worked across those boundaries primarily as a C++ and Qt developer.

For example, I implemented the registration watchdog and primary/backup failover and failback in the customized liblinphone SDK, then integrated its APIs into the application and provisioning paths. I initially tried switching servers in the Qt layer, but moved the state machine into the SDK because registration lifecycle state belonged there. I checked server loss and recovery, authentication and the displayed state on physical devices. I also refactored call handling toward clearer session, service, adapter and presentation boundaries; the broader refactor was completed as internal architecture work.

On the Linux side, the product already used Yocto and BitBake. I worked within its inherited layers and adapted recipes and packaging for the Qt application, SDK and media dependencies, model-specific image contents, scripts and runtime services. The complete image brought together the application and its dependencies on the NXP i.MX target. My contribution was integration within that existing platform, including the BSP boundary, rather than ownership of the entire BSP or building a distribution from scratch.

A useful example is device startup. The application depended on the graphical environment, installed files, services and hardware being ready. A symptom that looked like a Qt failure could come from a missing file, service ordering or an unavailable Wayland socket. I investigated with logs, gdb and gdbserver and checked behavior on physical phones. Component tests helped with isolated logic, but complete boot, audio, video and hardware behavior needed target validation.

I also migrated the WinForms provisioning tool from .NET Framework 4.8 to .NET 8 and developed configuration and discovery workflows with SNMP, DHCP and TFTP. The generated settings had to match what the phone actually applied.

Across these domains, my common approach is to understand the complete data or control path, make focused changes within an existing system and validate them at the appropriate boundary. For this role, I would bring hands-on C++ development, Yocto image integration and embedded Linux diagnosis, together with experience working across application, SDK, services and physical hardware.

SECTION 3. FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION INTRO-01. What did you do with BitBake recipes and image contents?

Answer: I adapted recipe metadata, packaging, dependencies and service integration within the inherited Yocto build. I trace a component from compilation through install staging and packages into the deployed image; a successful recipe build alone does not prove the file is on the phone.

QUESTION INTRO-02. How do you keep host and target dependencies separate?

Answer: Build-time tools execute on the host, while application headers/libraries and output must match the target ABI/sysroot. I inspect the selected compiler, dependency metadata and actual link inputs. Accidentally finding a host library can produce a build that is unusable on the device.

QUESTION INTRO-03. Where was your i.MX/BSP ownership boundary?

Answer: My work covered application/SDK integration, recipes, image contents, services and target diagnosis within the inherited platform. This does not imply that I designed the entire BSP, performed independent board bring-up or owned every kernel and bootloader change.

QUESTION INTRO-04. How would you diagnose a Qt application failing at boot?

Answer: Check deployed files/libraries and service configuration, then user/environment, ordering and compositor/socket readiness. Compare logs from systemd, the application and graphical runtime. Reproduce on the phone and use remote debugging when the failure reaches the process rather than adding an arbitrary startup delay.

QUESTION INTRO-05. Why move SIP failover from Qt into the SDK?

Answer: Registration lifecycle and effective active-server state belonged in liblinphone. I reverted an initial Qt-level switching attempt, implemented the SDK watchdog/failover/failback and integrated its APIs into application/provisioning. Server-loss/recovery checks compared authentication, SDK state and visible phone behavior.

QUESTION INTRO-06. What was the status of the Qt architecture refactor?

Answer: I separated call sessions, services, SDK adapters and presentation while preserving existing interaction and signal boundaries. The broader refactor was completed as internal architecture work. I distinguish that engineering result from functionality already released to the customer.

QUESTION INTRO-07. What can Qt Test check without physical hardware?

Answer: It can check isolated state transitions, validation and model/controller behavior with controlled inputs. Real camera/audio/GPIO, complete startup and SDK/device integration still need target scenarios. I keep these validation levels separate instead of presenting local tests as complete phone coverage.

QUESTION INTRO-08. What did the .NET provisioning migration have to preserve?

Answer: The tool's configuration/discovery workflow and generated settings had to remain meaningful to the phone, not merely compile on .NET 8. Supported Project/JSON round trips were checked; the older encrypted BinaryFormatter payload is incompatible with the later reader, so I do not claim universal legacy-file compatibility.
