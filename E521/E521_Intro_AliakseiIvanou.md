SELF INTRO

1. DOCUMENT INFORMATION

Request ID: E521
Candidate: Aliaksei Ivanou, presented in the CV as Alex I.
Target role: Senior C++ Engineer – Yocto Linux
CV source: E521 Aliaksei Ivanou (13, C++).pdf
Source request: E521_Request_AliakseiIvanou.md
Preparation language: English
Delivery format: Domain-based spoken introduction with a detailed latest-project section
Estimated spoken duration: 5–6 minutes

2. INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou. I am a software engineer with more than fourteen years across engineering and research and development. My main focus is C and C++ development, and my recent work combines C++17, Qt and embedded Linux with Yocto. Earlier in my career I developed image-processing algorithms in MATLAB.

I will describe my background through the domains I have worked in and then explain my latest embedded project in more detail.

The first domain is telecommunications and embedded devices. Since May 2022, I have worked as a Software Engineer on SIP-Based Phone Software, a desk-phone platform for audio and video communication. My work spans the C++ and Qt application, a customized Linphone SDK, device provisioning and integration with a Yocto-based Linux system on NXP i.MX hardware. I will return to the platform after the domain overview.

The second domain is library systems and long-lived backend software. From May 2019 to April 2022, I worked as a Software Engineer on Library System. I was one of three C developers sharing responsibility for an established C89 backend. I implemented features, fixes and refactoring across C, occasionally changing Java or Scala. I traced failures through service logs and used gdb, core dumps and Valgrind on Linux. PostgreSQL and MySQL supported the data services.

The third domain is industrial measurement. From March to May 2019, I worked as a Software Engineer on 3D Reconstruction Software for Industrial Applications. I developed a C++ prototype that combined profiles from multiple 2D laser scanners into a point cloud. I used Point Cloud Library for reconstruction and Open3D for comparison and visualization, checking intermediate stages against recorded data.

The fourth domain is aerospace and UAV imaging. From August 2017 to December 2018, I worked as a Software Engineer on Software Modules for UAV, developing MATLAB algorithms for debayering, format conversion, stabilization and image fusion. I verified algorithms on representative imagery and participated in UAV flight tests as an optical-payload operator.

From March 2016 to March 2017, I worked as a Software Engineer on Remote Sensing Satellites Database. I built a Ruby on Rails and PostgreSQL reference database for querying satellite and mission parameters.

From August 2012 to March 2016, I worked as a Software Engineer on Software for Processing and Analysis of Satellite Earth Observation Images. My MATLAB work included frame stitching, radiometric matching, image-type prediction, automated resolution assessment and an ADPCM-family compression algorithm. For onboard compression, I designed and verified the algorithm against a limited computation budget; the flight-software team handled implementation on the target.

I would now like to explain the SIP phone project in more detail, because it is the closest match to this role.

The product supports audio-only and camera-enabled phones. Its software includes a Qt application, a customized SIP SDK, provisioning tools and an embedded Linux image. User-visible state depends on generated configuration, device settings, the SDK and application models. I worked across those boundaries primarily as a C++ and Qt developer.

For example, I implemented the registration watchdog and primary/backup failover and failback in the customized liblinphone SDK, then integrated its APIs into the application and provisioning paths. I initially tried switching servers in the Qt layer, but moved the state machine into the SDK because registration lifecycle state belonged there. I checked server loss and recovery, authentication and the displayed state on physical devices. I also refactored call handling toward clearer session, service, adapter and presentation boundaries; the broader refactor was completed as internal architecture work.

On the Linux side, the product already used Yocto and BitBake. I worked within its inherited layers and adapted recipes and packaging for the Qt application, SDK and media dependencies, model-specific image contents, scripts and runtime services. The complete image brought together the application and its dependencies on the NXP i.MX target. My contribution was integration within that existing platform, including the BSP boundary, rather than ownership of the entire BSP or building a distribution from scratch.

A useful example is device startup. The application depended on the graphical environment, installed files, services and hardware being ready. A symptom that looked like a Qt failure could come from a missing file, service ordering or an unavailable Wayland socket. I investigated with logs, gdb and gdbserver and checked behavior on physical phones. Component tests helped with isolated logic, but complete boot, audio, video and hardware behavior needed target validation.

I also migrated the WinForms provisioning tool from .NET Framework 4.8 to .NET 8 and developed configuration and discovery workflows with SNMP, DHCP and TFTP. The generated settings had to match what the phone actually applied.

Across these domains, my common approach is to understand the complete data or control path, make focused changes within an existing system and validate them at the appropriate boundary. For this role, I would bring hands-on C++ development, Yocto image integration and embedded Linux diagnosis, together with experience working across application, SDK, services and physical hardware.

3. EXPECTED FOLLOW-UP TOPICS

- BitBake recipes, dependencies, packages and image contents within inherited layers.
- Cross-compilation, host and target dependencies, and sysroot boundaries.
- Scope of NXP i.MX integration and the ownership boundary for BSP, kernel and bootloader.
- systemd ordering, compositor readiness and diagnosis of target startup failures.
- SIP registration failover, SDK state ownership and application integration.
- Qt call-state refactoring and the internal status of the broader architecture work.
- Qt Test, component checks and scenarios requiring physical-device validation.
- Provisioning configuration, .NET migration and supported project-file compatibility.
