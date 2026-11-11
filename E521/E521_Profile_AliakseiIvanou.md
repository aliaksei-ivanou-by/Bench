PROFILE

1. DOCUMENT INFORMATION

Request ID: E521
Candidate: Aliaksei Ivanou, presented in the CV as Alex I.
Target role: Senior C++ Engineer – Yocto Linux
CV: E521 Aliaksei Ivanou (13, C++).pdf
Request: E521_Request_AliakseiIvanou.md
Factual sources: Summary/Interview/Career Overview.md and the project records cited below.

2. POSITIONING

C++ engineer with more than six years of C++ practice, approximately five in commercial work, within more than fourteen years across engineering and R&D. The strongest match is a physical SIP-phone platform: C++17 and Qt on an inherited Yocto-based embedded Linux image for NXP i.MX ARM64, with BitBake recipe and packaging contributions, systemd startup, target debugging and device-level validation. The primary project role was application and SDK engineering, with platform integration, not sole ownership of a Yocto distribution or BSP.

The request calls for Senior, extensive Yocto including custom layers and BSP customization, and English C1. The supported grade is middle, the directly documented embedded assignment is May 2025–August 2026, and the defensible English level is B2. These are material boundaries for the requested profile.

3. E521 CV PROJECT INVENTORY

1. SIP-BASED PHONE SOFTWARE
CV: May 2022–present; Software Engineer. FULL MATCH with the embedded SIP platform; factual period May 2025–August 2026. C++17/Qt call and account models, customized liblinphone, SIP failover, Windows provisioning, Yocto/BitBake image and service integration on i.MX. The inherited platform included BSP and kernel/U-Boot integration; this does not by itself establish personal ownership of the BSP or a ground-up layer. Source: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, sections 01, 03, 04 and 07.

2. LIBRARY SYSTEM
CV: May 2019–April 2022; Software Engineer. FULL MATCH with Sierra; factual project period March 2022–April 2024. Shared C89 backend work with two C developers, Java data services, Scala APIs, PostgreSQL/MySQL, Linux diagnosis and established Jenkins/AWS deployment processes. Source: Summary/Interview/2022-2024. Integrated Library System.md, sections 01, 03 and 04.

3. 3D RECONSTRUCTION SOFTWARE FOR INDUSTRIAL APPLICATIONS
CV: March–May 2019; Software Engineer. FULL MATCH with industrial laser-scanning work; actual informal commercial engagement 23 March–19 May 2020. C++ prototype, point-cloud processing using PCL and comparison and visualization using Open3D. This was a short engagement, not evidence of a year of full-time PCL or Open3D work. Source: Summary/Interview/2020. Industrial 3D Scanning and Metrology Software.md, sections 01, 03 and 07.

4. SOFTWARE MODULES FOR UAV
CV: August 2017–December 2018; Software Engineer. FULL MATCH for the UAV optical-system work within August 2012–January 2020. MATLAB debayering, image-format conversion, stabilization and fusion; verification against imagery and participation in UAV tests. No C++ UAV implementation is claimed. Source: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md, sections 01, 03 and 07.

5. REMOTE SENSING SATELLITES DATABASE
CV: March 2016–March 2017; Software Engineer. FULL MATCH with the satellite reference database; Summary dates the Rails/PostgreSQL assignment to February 2015–February 2016. Built a searchable reference database for satellite and mission parameters. MS Access appears in the broader environment; a personal MS Access migration is not established by the project record. Source: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md, sections 01 and 13.

6. SOFTWARE FOR PROCESSING AND ANALYSIS OF SATELLITE EARTH OBSERVATION IMAGES
CV: August 2012–March 2016; Software Engineer. FULL MATCH for satellite imaging work within August 2012–January 2020. MATLAB image stitching, radiometric matching, image-type prediction, ADPCM-family compression and automated resolution assessment. The onboard flight-software implementation was a separate team boundary. Source: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md, sections 01, 03 and 07.

4. YOCTO AND EMBEDDED SCOPE

- Worked with inherited Yocto Kirkstone layers and BitBake metadata for the Qt application, SDK and media dependencies, model-specific packaging, scripts, default assets and services.
- Worked on the complete image and service startup, including systemd ordering around the graphical environment; investigated missing files, runtime dependencies and startup behavior on physical devices.
- Integrated with the existing NXP i.MX BSP and platform; kernel and U-Boot changes appear in the project platform. The evidence does not establish personal ownership of BSP design, a custom layer created from scratch, or all kernel and bootloader changes.
- Used gdb/gdbserver, logs and device scenarios. Desktop tests supported isolated logic; complete boot, media, GPIO and hardware integration required target validation.
- Extended customized liblinphone with the registration watchdog and primary/backup failover/failback, then integrated its APIs into the application. SDK ownership is separate from ownership of Yocto platform architecture.

5. CV CLAIM BOUNDARIES

- The CV assigns five years to Yocto and Embedded Linux and places the phone project from May 2022. The supported SIP assignment ran from May 2025 to August 2026; those CV durations are not confirmed by this record.
- Custom recipes and image integration are supported as contributions. Creating a dedicated layer from scratch, independently owning BSP customization and tuning compiler flags to reduce memory footprint are not established.
- The platform uses libgpiod and device logs. The precise GPIO singleton/QThread/deadlock/leak changes and the claimed journald bundle, retention limits and web download are not established by the project record.
- SDK failover and an AuthInfo backup-domain change are supported. HA1 and realm work was implemented, but the selectable HA1 mode was disabled in the later release history; it should not be described as enabled at project end.
- The late Qt call-session refactor was completed as internal architecture work. The browser frontend and device-local REST/API were owned by another developer.
- The .NET 8 migration is supported; legacy encrypted BinaryFormatter project files were not compatible with the later JSON reader. Do not claim universal backward compatibility.

6. FOLLOW-UP TOPICS

- Explain one concrete recipe or packaging change, its dependencies, sysroot, installed files and how the image and target were checked.
- Distinguish inherited layers, personally edited recipes and BSP/kernel/U-Boot ownership.
- Trace a boot failure through image contents, systemd, compositor readiness and device logs.
- Explain cross-compilation, host versus target dependencies and image/package boundaries.
- Discuss C++/Qt ownership, asynchronous state, SDK integration and physical-device testing.
- Present English as B2 and describe daily technical communication; do not claim C1 from the CV.
