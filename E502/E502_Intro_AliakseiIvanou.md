SELF INTRO

1. DOCUMENT INFORMATION

Request ID: E502
Candidate: Aliaksei Ivanou, presented in the CV as Alex I.
Target role: Senior C++ Developer with Ceph or NetApp, Kubernetes and infrastructure experience
CV source: E502 Aliaksei Ivanou (13, C++).pdf
Source request: E502_Request_AliakseiIvanou.md
Preparation language: English
Delivery format: Domain-based spoken introduction with a detailed latest-project section
Estimated spoken duration: 5–6 minutes

2. TARGET POSITIONING

Software Engineer with more than fourteen years of commercial experience, specializing in C and C++ on Linux, backend development, distributed service communication, storage integration and embedded systems.

3. INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou. I am a Software Engineer with more than fourteen years of commercial experience. My main focus is C and C++ on Linux, including backend development, distributed services and integration with object storage. I also have extensive experience with MATLAB algorithms for image analysis.

The easiest way to describe my background is through the domains in which I have worked.

The first domain is telecommunications and embedded Linux. Since May 2024, I have worked as a Software Engineer on SIP Desk Phone Platform for Audio and Video Communication. The platform combines a C++17 and Qt application, a customized Linphone SDK, WebRTC, a Windows provisioning tool and a Yocto-based Linux system on NXP i.MX hardware. My work spans call handling, SDK integration, video conferencing, provisioning and device-side configuration. I will return to this project after the domain overview.

The second domain is satellite data and cloud storage. From April 2022 to April 2024, I worked as a Software Engineer on Remote Sensing Satellites Database. Ruby on Rails supported catalogue, search and metadata workflows, with PostgreSQL storing structured records. I also developed C++ ingestion components using POSIX streaming I/O, memory buffers and multithreaded validation for large imagery and telemetry archives.

For storage, I integrated Ceph RGW through the S3 API, including pre-signed URLs, and worked with Ceph services in Kubernetes using Rook Operator and Ceph CSI for RBD. I investigated storage performance through I/O latency, throughput, OSD behavior and BlueStore utilization. Python scripts supported validation and health checks, while Prometheus and Grafana provided monitoring. This project is particularly relevant to a role combining C++ with storage and infrastructure.

The third domain is UAV and satellite image processing. From March 2020 to March 2022, I worked as a Software Engineer on Software Modules for UAV. I combined MATLAB algorithm development with C++ processing components for debayering, format conversion, stabilization and image fusion. I also worked on efficient frame buffers and tested results with representative sensor data.

From January 2018 to February 2020, I worked as a Software Engineer on Software for Processing and Analysis of Satellite Earth Observation Images. My work included brightness normalization, image-resolution analysis, quantization-range prediction, frame processing and an ADPCM-based compression algorithm with multiple quantizers.

The fourth domain is library systems. From January 2015 to December 2017, I worked as a Software Engineer on Library System. I developed C backend modules, socket-based communication and Scala API endpoints, and worked with Java, MySQL and PostgreSQL. I integrated AWS S3 storage for digital collections and implemented streaming upload and byte-range download workflows for large objects. I also worked on database access, compatibility with existing components, release preparation and code review.

The fifth domain is oil and gas. From August 2012 to December 2014, I worked as a Software Engineer on Corporate System for the Oil and Gas Industry. I developed and maintained C++11 backend components and integrated LevelDB for telemetry and event data alongside relational storage. I worked on database access, LevelDB cache and compaction tuning, web integration with JavaScript and jQuery, and maintenance of inherited code.

I would now like to explain my latest SIP desk-phone project in more detail.

The product supports audio-only phones and devices with cameras. It includes a native application, a web management interface, provisioning tools and embedded system customization. Everyday workflows include SIP registration, incoming and outgoing calls, video, hold, transfer, conferences, phonebook access and remote configuration.

A major part of my work was refactoring the Qt Widgets call flow toward clearer MVC and MVVM-style boundaries. I separated UI rendering from call state, user actions, media negotiation and Linphone SDK integration, while preserving existing interface behavior and QObject signal compatibility. I also hardened video and conference behavior for held calls, second-line calls, remote hangups, stale overlays and active video-stream switching.

At the SDK level, I extended customized liblinphone backend logic for SIP failover and backup-server connectivity. I also developed WebRTC conferencing UI and signaling flows, including conference creation and joining, participant lists, invitation dialogs, video layouts and audio and video controls.

Another area was the Windows provisioning tool. I migrated a WinForms configuration utility from .NET Framework 4.8 to .NET 8, unified project file formats across the device ecosystem and implemented provisioning workflows using SNMP, DHCP, TFTP and SQLite.

On the device side, I collaborated on Yocto and BitBake customization, NXP i.MX embedded Linux integration and service configuration. The environment included systemd, CMake, gdb, Valgrind and Qt Test. Across these domains, my focus has been implementing and integrating C and C++ components, following data across system boundaries and maintaining existing products. That combination connects my embedded and application work with the storage and Kubernetes experience relevant to this opportunity.

4. EXPECTED FOLLOW-UP TOPICS

- C++ ingestion, POSIX streaming and multithreaded validation of large files.
- Ceph RGW integration through the S3 API and pre-signed URLs.
- Rook Operator, Ceph CSI and RBD in Kubernetes.
- Storage diagnosis using latency, throughput, OSD behavior and BlueStore.
- AWS S3 streaming upload and byte-range download in the library system.
- Qt call-flow refactoring and Linphone SDK failover integration.
- WebRTC conference flows and video-call edge cases.
- Provisioning with .NET 8, SNMP, DHCP, TFTP and SQLite, and Yocto device integration.
