SELF INTRO

SECTION 1. DOCUMENT INFORMATION

Request ID: E521
Candidate: Aliaksei Ivanou, presented in the CV as Alex I.
Target role: Senior C++ Engineer – Yocto Linux
CV source: E521 Aliaksei Ivanou (13, C++).pdf
Source request: E521_Request_AliakseiIvanou.md
Preparation language: English
Delivery format: Domain-based spoken introduction with a detailed latest-project section
Target spoken duration: approximately 5 minutes

SECTION 2. INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou. I am a Software Engineer with more than fourteen years across engineering and research and development. My main focus is C and C++, especially embedded Linux applications and integration.

My latest domain is telecommunications. On SIP-Based Phone Software, I work on desk phones using C++17, Qt, Linphone SDK and Yocto Linux on NXP i.MX.

My earlier experience covers three other domains. On Library System, I maintained a C89 backend and investigated Linux failures. In industrial measurement, 3D Reconstruction Software for Industrial Applications involved a C++ point-cloud prototype. Earlier, Software Modules for UAV and Software for Processing and Analysis of Satellite Earth Observation Images involved MATLAB imaging algorithms. On Remote Sensing Satellites Database, I built a Rails/PostgreSQL reference database.

The phone project is the closest match to this role, so I will focus on it. It supports audio-only and camera-enabled models, with a native application, telephony SDK, provisioning tools and a Linux image. My main responsibility was application and SDK engineering, including integration and debugging on physical phones.

Before our team joined, there was a basic Yocto skeleton without Linphone SDK, WebRTC or mediasoup. We added those components and their dependencies. I contributed to BitBake recipes, packaging, image contents and startup services within the existing board platform.

For example, the SDK recipe fetched Git sources with submodules, declared target libraries and native build tools, selected features through PACKAGECONFIG and passed the CMake cross-build settings. I checked the installation layout, output packages and runtime dependencies. SDK files were installed under /opt/belledonne-communications. The application needed the SDK headers and libraries in its recipe sysroot, while the image needed the runtime packages. These were separate checks.

A successful build was only the first step. If the application failed after boot, I checked installed files, library paths, the systemd unit and the Weston/Wayland environment. The compositor process could be running while the required socket or service environment was still unavailable. I used logs and remote debugging, then repeated the scenario on the actual phone.

My strongest SDK example is SIP server failover. I implemented registration monitoring and switching between primary and backup servers, including returning to the primary after recovery. I first tried switching in Qt, then moved the state machine into liblinphone because registration belonged there. The application consumed SDK state instead of maintaining another switching loop. I tested server loss, recovery, authentication and the displayed state on devices.

I also separated call handling into sessions, services, SDK adapters and presentation. The wider refactor was completed as internal architecture work. Focused Qt tests supported local logic; audio, video, GPIO and full startup still needed device tests.

Another part of my work was migrating the Windows provisioning tool from .NET Framework 4.8 to .NET 8 and developing discovery and configuration workflows. Generated settings had to agree with the phone's effective behavior.

For this role, I bring hands-on C++ development, Yocto recipe and image integration, and embedded Linux diagnosis. My approach is to follow the complete path from source and build settings to installed software and observable device behavior.

SECTION 3. FOLLOW-UP QUESTIONS AND ANSWERS

QUESTION INTRO-01. What did you do with BitBake recipes and image contents?

Answer: Our team started with a basic Yocto skeleton and added Linphone SDK, WebRTC and mediasoup. I contributed recipe metadata, dependencies, packaging and service integration. I trace a component from compilation through staging and packages into the image and device; a successful recipe build alone does not prove delivery to the phone.

QUESTION INTRO-02. How do you keep host and target dependencies separate?

Answer: Build-time tools execute on the host, while application headers/libraries and output must match the target ABI/sysroot. I inspect the selected compiler, dependency metadata and actual link inputs. Accidentally finding a host library can produce a build that is unusable on the device.

QUESTION INTRO-03. Where was your i.MX/BSP division of responsibility?

Answer: My work covered application/SDK integration, recipes, image contents, services and debugging on the device within the inherited platform. This does not imply that I designed the entire BSP, performed independent board bring-up or owned every kernel and bootloader change.

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
