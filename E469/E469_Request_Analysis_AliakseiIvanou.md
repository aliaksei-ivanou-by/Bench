REQUEST AND CUSTOMER ANALYSIS

DOCUMENT INFORMATION

Request ID: E469
Internal request reference: R-22535
Candidate: Aliaksei Ivanou
Target role: Broadband Triage Engineer
CV source: E469 Aliaksei Ivanou (14+, C++).pdf
Request document: E469_Request_AliakseiIvanou.md
Profile source: E469_Profile_AliakseiIvanou.md
Research date: 2026-09-22
Analysis status: Rebuilt against the submitted CV and the request

SOURCES OF TRUTH

This analysis is built from two sources only:

1. E469_Request_AliakseiIvanou.md, the normalized request.
2. The submitted CV, E469 Aliaksei Ivanou (14+, C++).pdf.

Fit is assessed as the match between what the request asks for and what the submitted CV actually shows. The detailed career record is not used to create or remove evidence here. It is used only in the section CV CLAIMS THAT CREATE INTERVIEW RISK, where a CV statement cannot be defended in depth during a technical conversation.

EVIDENCE RULES

REQUEST FACT means the information is recorded in the normalized Request document.
CV FACT means the information is printed in the submitted CV, in a project entry, an environment list, a language line, a domain line, or the professional-skills matrix.
VERIFIED PUBLIC FACT means the information is supported by an official public source listed at the end.
INFERENCE means a useful interpretation that neither the request nor the CV states.
OPEN QUESTION means information that must be obtained from the recruiter or customer.
NOT IN CV means the request asks for something the submitted CV does not mention at all.
INTERVIEW RISK means the CV states it, but the depth behind the statement will not survive detailed questioning.

EXECUTIVE ASSESSMENT

Overall fit against the submitted CV: PARTIAL, WITH THE DOMAIN LAYER MISSING
Recommendation: QUALIFY THE DOMAIN GATES BEFORE SUBMISSION

This CV is tailored well for the first half of the request and not at all for the second half. The first project is titled and written as broadband triage work: it opens with owned third-level investigation of escalated telecom faults, and it names source-level C and C++ SIP stack debugging, WAN and service recovery, liblinphone failover, Yocto and i.MX integration, and provisioning. Against must-haves two, three, four and five the CV reads convincingly.

The second half of the request is the broadband access and management layer, and the CV is silent on all of it. TR-069, TR-181, DSL, GPON, FTTH, RDK-B, OpenWrt, prplOS, Wi-Fi mesh and EasyMesh do not appear anywhere in the document, and neither does TCP/IP as a skills entry. Packet capture is implied once by the phrase network traces, but Wireshark and tcpdump are absent from the matrix.

Two structural points weaken the strongest section. The third-level claim rests on a single project running 04.2025 to the present, which is seventeen months, and the CV prints the role label Software Engineer on every project, with the words senior and lead appearing nowhere in the document, against a contract role the request classes as senior. A third point is smaller but visible: the matrix gives Embedded Linux one year while the request asks for strong embedded Linux.

The honest positioning is a credible embedded telecom triage engineer whose endpoint was a SIP desk phone, submitted against a residential broadband gateway programme whose management and access-network vocabulary the CV does not carry.

REQUEST FACTS

Role: Broadband Triage Engineer
Contract: Contract engagement
Seniority: Senior
Industry: Telecom
Domain: Internet of Things
Solution type: Embedded
Final client: Deutsche Telekom
Request source or intermediary: 5V Video
Requested headcount: One; the source asks to show two or three candidates
Workload: Full-time is implied by the role but not separately stated
Working time: EU time zones
Duration: Twelve months with extensions expected; a separate field says one to two years
English requirement: C1
Submission deadline in the source: 2026-09-08
Deadline status at research date: Passed; current availability of the request must be reconfirmed

SUBMITTED CV AS PRESENTED

Name as printed: Alex I.
Headline: Broadband Triage Engineer
Opening statement: Software engineer with 14+ years of commercial experience
Languages: English B2, Polish B1, Swedish A2
Domains: Telecommunications, Library Systems, Oil and Gas Industry, UAV Systems, Aerospace Systems

Projects, in CV order, with the periods and role labels the CV prints:

1. Embedded Broadband-Connected SIP/VoIP Communications Platform, 04.2025 – till now, Software Engineer, 17 months
2. Library System, 12.2021 – 04.2025, Software Engineer, 40 months
3. Corporate System for the Oil and Gas Industry, 07.2021 – 12.2021, Software Engineer, 5 months
4. Home Accounting Software, 05.2020 – 07.2021, Software Engineer, 14 months
5. 3D Reconstruction Software for Industrial Applications, 12.2019 – 05.2020, Software Engineer, 5 months
6. Software Modules for UAV, 03.2017 – 12.2019, Software Engineer, 33 months
7. Remote Sensing Satellites Database, 03.2016 – 03.2017, Software Engineer, 12 months
8. Software for Processing and Analysis of Satellite Earth Observation Images, 08.2012 – 03.2016, Software Engineer, 43 months

Project 1 responsibilities as printed, because they carry most of the fit:

• Owned 3rd-level investigation of escalated embedded telecom faults across SIP application logic, liblinphone, embedded Linux services, networking and device configuration, from customer-reported symptoms through reproduction, root-cause analysis, remediation and validation.
• Extended and customized Linphone-SDK backend logic to implement SIP failover and backup-server connectivity.
• Debugged C/C++ SIP stack behavior at source level, tracing registration, connection and failover problems through liblinphone state transitions, application logs and network traces.
• Investigated WAN and service connectivity and recovery scenarios involving loss of network reachability, remote-server unavailability and connection interruption.
• Collaborated on Yocto/BitBake customization, i.MX embedded Linux target integration and device-side service configuration.
• Developed WebRTC video-conferencing and signaling flows.
• Autoprovisioning tooling: migrated a WinForms-based configuration utility from .NET Framework 4.8 to .NET 8 and implemented provisioning workflows using SNMP, DHCP, TFTP and SQLite.

Skills-matrix entries that the request depends on:

C++ 7 years, last used 2026
C 3 years, last used 2025
Embedded Linux 1 year, last used 2026
GDB 5 years, last used 2026
Valgrind 1 year, last used 2026
gcc 1 year, last used 2026
Yocto Project 1 year, BitBake 1 year, NXP i.MX 1 year, systemd 1 year, all last used 2026
SIP, SDP, RTP, SNMP, DHCP, TFTP, Qt WebSockets, each 1 year, last used 2026
Linphone-SDK, liblinphone, WebRTC, mediasoup, libmediasoupclient, Qt Multimedia, each 1 year, last used 2026
GStreamer 1 year, V4L2 1 year, last used 2026
Windows 1 year, last used 2021

Terms the request uses that do not appear anywhere in the submitted CV: TR-069, TR-181, CWMP, ACS, USP, DSL, VDSL, GPON, FTTH, ONT, OLT, RDK-B, OpenWrt, prplOS, EasyMesh, Wi-Fi, mesh, roaming, CPE, gateway, router, telemetry, packet capture, Wireshark, tcpdump, TCP/IP, senior, lead.

CUSTOMER CHAIN

Request source or staffing intermediary: 5V Video
Named final client: Deutsche Telekom
Product owner and internal Deutsche Telekom unit: Not disclosed
Specific CPE platform, hardware vendor, software stack and access network: Not disclosed

The request explicitly names Deutsche Telekom as the final client. It does not confirm whether the engineer would join a Telekom team directly, work through a managed service, or support a vendor-owned CPE platform.

CUSTOMER AND DOMAIN RESEARCH

Research item 1
Verified public fact: 5V Video presents itself as a specialist talent provider and shows RDK-related partnerships and an RDK-B staffing case study. Its public Vantiva case study describes supplying RDK-B developers, embedded engineers, quality-assurance engineers and Wi-Fi testers for a broadband gateway project.
Interview implication: The intermediary is likely to screen for exact RDK and broadband vocabulary before the customer interview. The submitted CV contains none of that vocabulary, so a keyword screen is the most likely point of failure, ahead of any technical conversation.
Sources:
https://www.weare5vvideo.com/
https://www.weare5vvideo.com/video/case-study/accelerating-rdk-b-delivery-for-vantiva

Research item 2
Verified public fact: Deutsche Telekom's 2025 annual report records approximately 15.1 million retail broadband lines in Germany and 21.0 million fibre-optic-based retail and wholesale lines at year end, and describes an ongoing shift from DSL to FTTH with a target of passing around 2.5 million additional homes per year.
Interview implication: Triage may span a large installed base and mixed access generations. Reproducibility, clean fault-domain isolation and vendor-ready evidence are likely to matter more than individual debugging feats, which is the part of the profile the CV does support.
Sources:
https://report.telekom.com/annual-report-2025/management-report/development-of-business-in-the-operating-segments/germany.html
https://report.telekom.com/annual-report-2025/management-report/group-strategy/investments.html

Research item 3
Verified public fact: Deutsche Telekom's support material covers a family of Speedport routers, active firmware releases, DSL and fibre compatibility, external and integrated fibre modems, and mesh-capable products.
Interview implication: The role may involve several device models, firmware branches and access arrangements. The exact product family must be confirmed rather than assumed.
Sources:
https://www.telekom.de/hilfe/geraete/router/speedport/smart-serie
https://www.telekom.de/hilfe/internet-telefonie/glasfaser/kompatible-router

Research item 4
Verified public fact: Broadband Forum describes TR-069, also called CWMP, as a remote-management platform for service providers to recognize, provision and maintain customer premises equipment across its lifecycle. TR-181 Device:2 defines a device data model for TR-069 and USP-enabled endpoints, including interfaces, routing, bridging, statistics and diagnostic tests.
Interview implication: The distinction matters. TR-069 is the management protocol and its remote-procedure behaviour, TR-181 is the managed-object and parameter model. Both are absent from the submitted CV, so any discussion is prepared knowledge.
Sources:
https://broadband-forum.org/public/certifications/bbf-069-certification/
https://device-data-model.broadband-forum.org/

Research item 5
Verified public fact: RDK-B documentation describes a layered broadband architecture with application, middleware and hardware-abstraction layers. The platform is componentized and supports access technologies including DSL, GPON and LTE.
Interview implication: A triage engineer must decide whether a fault belongs to an application or manager component, common middleware, the hardware-abstraction layer, the platform or driver layer, or the external network. That decision structure is close to the cross-layer method the CV does describe, even though the components themselves are new.
Source: https://developer.rdkcentral.com/documentation/documentation/rdk_broadband_documentation/architecture/

Research item 6
Verified public fact: OpenWrt describes itself as a Linux distribution for embedded network devices and exposes configuration, service, logging and network-diagnostic workflows. The prpl Foundation describes prplOS as an open-source carrier-grade networking-device stack built around open standards and interfaces.
Interview implication: Embedded Linux fundamentals transfer, but UCI, netifd, ubus, procd and the prplOS interfaces require direct preparation. The CV's one-year Embedded Linux entry does not help here.
Sources:
https://openwrt.org/docs/start
https://prplfoundation.org/

ROLE OUTCOME

Success means taking an escalation that first and second-line support could not resolve, making it reproducible, gathering the right device and network evidence, isolating the failing layer, and either implementing and validating a fix or producing a defect report that a vendor can act on without repeating the investigation. Repeated issues should become diagnostic playbooks and feedback to engineering and support.

MUST-HAVE REQUIREMENT MAPPING

Requirement 1: Proven third-level or escalation-engineering experience in a broadband or CPE environment
Request wording: Own escalated broadband faults from reproduction through root-cause isolation and closure
CV evidence: The first project is titled Embedded Broadband-Connected SIP/VoIP Communications Platform and its opening responsibility is owned third-level investigation of escalated embedded telecom faults, taken from customer-reported symptoms through reproduction, root-cause analysis, remediation and validation. The project runs 04.2025 to the present, that is seventeen months.
Match: PARTIAL
Boundary: The device described in the same CV is a desk phone, not a residential gateway or CPE, and no support organization, severity model or vendor escalation process is named. The third-level claim rests on one project of seventeen months, and the CV prints the role label Software Engineer on it.
Safe interview wording: I have owned third-level technical investigation on a networked embedded endpoint, from an unclear customer symptom through reproduction, fault-domain isolation, correction and recovery validation. The endpoint was a SIP desk phone rather than a broadband gateway, and I worked inside an engineering team rather than an operator support function.

Requirement 2: Strong C++
Request wording: Strong C++
CV evidence: C++ with seven years and a 2026 last use, C++17 in the first project environment, and C with three years. The first project describes source-level debugging of C and C++ SIP stack behaviour.
Match: COVERED BY CV
Safe interview wording: My strongest language is C++, most recently C++17 on the embedded phone platform, with C in a long-lived backend before that.

Requirement 3: Strong embedded Linux
Request wording: Strong embedded Linux
CV evidence: Embedded Linux is in the operating-systems list and in the first project environment, together with Yocto, BitBake, systemd, NXP i.MX, gcc, gdb and qmake. The skills matrix, however, gives Embedded Linux one year, and Yocto, BitBake, systemd and NXP i.MX one year each.
Match: PARTIAL
Boundary: The narrative is strong and the matrix is weak. A reviewer who reads the matrix sees one year against a requirement that says strong.
Safe interview wording: My embedded Linux work is the current project: the Yocto and BitBake image, systemd service ordering, the ARM64 NXP i.MX target, and on-device debugging. The one-year figure in my skills summary reflects that single assignment rather than the depth of the work inside it.

Requirement 4: Genuine code-level debugging with gdb
Request wording: Debug CPE firmware, gateway software and access-network components at code level
CV evidence: GDB with five years and a 2026 last use, gdb in three project environments, Valgrind, and the explicit responsibility of debugging C and C++ SIP stack behaviour at source level through liblinphone state transitions.
Match: COVERED BY CV
Boundary: The debugged software was phone firmware and application code, not gateway or access-network components.
Safe interview wording: I debug at source level on the target device, using gdb on the running system and tracing state transitions inside the SDK rather than stopping at the visible symptom.

Requirement 5: Strong log-analysis skills
Request wording: Analyze logs, packet captures and device telemetry
CV evidence: The first project names application logs as part of the source-level debugging responsibility, and the library project describes tracing behaviour across services.
Match: PARTIAL
Boundary: Logs are mentioned once. There is no log platform, no telemetry system and no log tooling anywhere in the CV.
Safe interview wording: My normal method is log-first: correlate application, SDK and system logs against a reproducible scenario, then add focused diagnostics where the existing evidence is incomplete.

Requirement 6: Practical packet-capture analysis
Request wording: Analyze logs, packet captures and device telemetry
CV evidence: The phrase network traces appears once in a first-project responsibility. Wireshark and tcpdump do not appear in the CV, in any environment list, or in the skills matrix.
Match: NOT IN CV
Boundary: This is a named must-have with a one-word anchor and no tooling behind it.
Safe interview wording: Packet capture is a preparation area for me rather than a documented project strength. My diagnostic evidence has been logs, device state, configuration and source-level debugging.

Requirement 7: Working knowledge of TR-069 and TR-181
Request wording: TR-069 and TR-181
CV evidence: None. The closest items in the CV are SNMP, DHCP and TFTP provisioning and the WinForms autoprovisioning tool, all at one year.
Match: NOT IN CV
Boundary: Endpoint provisioning over SNMP, DHCP and TFTP is not CWMP, an auto-configuration server, or the TR-181 data model.
Safe interview wording: I have built and used automated endpoint discovery and provisioning, but not TR-069 or TR-181. I understand the difference between the management protocol and the data model and I am preparing both.

Requirement 8: Working knowledge of DSL, GPON and FTTH
Request wording: DSL, GPON and FTTH
CV evidence: None. The CV contains no access-network technology at all.
Match: NOT IN CV
Safe interview wording: My network experience is endpoint and product side. I do not claim hands-on DSL, GPON or FTTH access-network work.

Requirement 9: Ability to work independently across vendor and operator teams
Request wording: Produce clear evidence for defects raised to platform and hardware vendors
CV evidence: The library project describes code review and knowledge sharing within the core team and the client's team. The first project describes taking issues from customer-reported symptoms through validation.
Match: PARTIAL
Boundary: Cross-company work is shown, but no operator-to-vendor defect ownership and no formal escalation process.
Safe interview wording: I am used to working across team and company boundaries and to producing evidence that lets the owning party act. I have not owned an operator-to-vendor escalation process.

Requirement 10: Ability to work in a distributed team across time zones
Request wording: Distributed team across time zones
CV evidence: Not stated. The CV names no locations, no team distribution and no working model.
Match: NOT IN CV
Safe interview wording: I have worked remotely across company boundaries and keep investigations traceable through written evidence and handover. I would confirm the required coverage hours and any on-call model.

Requirement 11: English C1
Request wording: English C1
CV evidence: English B2.
Match: BELOW THE REQUIREMENT
Safe interview wording: My documented level is B2. I am comfortable working in English and the customer should assess whether that meets the role.

NICE-TO-HAVE REQUIREMENT MAPPING

Requirement 1: RDK-B exposure
CV evidence: None.
Match: NOT IN CV
Preparation bridge: Component and manager services, message bus, persistent storage, provisioning and management components, hardware-abstraction boundaries, RDK logs and common fault domains.

Requirement 2: OpenWrt exposure
CV evidence: None.
Match: NOT IN CV
Preparation bridge: UCI, netifd, ubus, procd, opkg, logread, interface state, DHCP, firewall and image workflows.

Requirement 3: prplOS exposure
CV evidence: None.
Match: NOT IN CV
Preparation bridge: Its relationship to carrier-grade CPE, open interfaces, Broadband Forum models, OpenWrt and prplMesh.

Requirement 4: Wi-Fi troubleshooting, including mesh, EasyMesh and roaming
CV evidence: None. No wireless technology appears in the CV.
Match: NOT IN CV
Preparation bridge: Controller and agent roles, backhaul against fronthaul, topology, steering, roaming symptoms, channel and interference evidence, client-specific behaviour.

Requirement 5: Prior work with a tier-one telecom operator
CV evidence: None. No customer is named anywhere in the CV.
Match: NOT IN CV

RESPONSIBILITY ALIGNMENT

Responsibility 1: Own escalated broadband faults from reproduction through root cause
CV alignment: Directly claimed in the first project. Domain is adjacent.

Responsibility 2: Debug CPE firmware, gateway software and access-network components at code level
CV alignment: Firmware and application debugging are claimed. Gateway and access-network components are not.

Responsibility 3: Analyze logs, packet captures and device telemetry
CV alignment: Logs yes, packet capture only as the phrase network traces, telemetry not at all.

Responsibility 4: Produce clear evidence for defects raised to platform and hardware vendors
CV alignment: Root-cause analysis and validation are claimed. Vendor defect ownership is not.

Responsibility 5: Feed recurring fault patterns back to engineering and support
CV alignment: Code review and knowledge sharing are claimed; no recurrence or support metric exists.

Responsibility 6: Document findings and create repeatable diagnostic procedures
CV alignment: Reproduction and validation are claimed; no runbook or documentation artefact is named.

REQUIREMENTS THE CV DOES NOT ADDRESS

1. TR-069 and TR-181.
2. DSL, GPON and FTTH.
3. Packet-capture tooling, Wireshark and tcpdump.
4. Device telemetry platforms.
5. RDK-B, OpenWrt and prplOS.
6. Wi-Fi, mesh, EasyMesh and roaming.
7. Tier-one operator experience.
8. Distributed-team and time-zone working model.
9. TCP/IP as a named skills entry, although it is in the request technology summary.

FORMAL SCREENING RISKS

1. English. The request asks for C1 and the CV states B2. This is on the first page.
2. Domain vocabulary. The intermediary's own public material is RDK-B staffing. None of the request's domain keywords appear in the CV, so an automated or keyword screen is the most likely rejection point.
3. Seniority signal. The request is a senior contract role. The CV prints Software Engineer on all eight projects and the words senior and lead appear nowhere in the document.
4. Depth of the key claim. The third-level responsibility rests on one project of seventeen months.
5. Matrix against narrative. Embedded Linux, Yocto, BitBake, systemd, SIP, RTP, SDP and the whole telecom stack are each shown as one year, against a request that asks for strong embedded Linux and proven escalation experience.
6. Headline against project labels. The CV headline reads Broadband Triage Engineer while every project role label reads Software Engineer. If asked, present the headline as the target role rather than a held title.
7. Internal inconsistency. The first project claims migration of a WinForms utility from .NET Framework 4.8 to .NET 8, but .NET and WinForms appear neither in the frameworks list nor in the skills matrix nor in the project environment. Only C# with one year is present.
8. Deadline. The stated submission deadline of 2026-09-08 has passed.

CV CLAIMS THAT CREATE INTERVIEW RISK

1. Network traces in the source-level debugging responsibility, which invites a packet-capture question.
2. GStreamer and V4L2 in the matrix and the first-project environment.
3. ReSharper C++ in the matrix and the oil and gas environment.
4. Owned third-level investigation, where owned must be read as technical ownership of the investigation, not of the support organization, the customer network or the external private branch exchange.
5. Refactored existing Scala API code to improve maintainability and scalability.
6. Worked with AWS pipelines, automating CI/CD processes.
7. Led development efforts as a key contributor in C language.
8. Developed new backend and frontend features for socket-based communication.
9. Modified database tables and improved schema design.
10. Developed WebRTC video-conferencing and signaling flows, which should be scoped to the phone side.
11. Fourteen-plus years of commercial experience in the opening line, against seven years of C++ in the same matrix.

INTERVIEW POSITIONING

Lead with what the CV itself supports:

• Third-level investigation of escalated telecom faults on a physical embedded endpoint, end to end.
• Source-level C and C++ debugging with gdb, on the device, inside a customized SIP stack.
• WAN interruption, remote-server unavailability and recovery validation.
• SIP failover and backup-server behaviour implemented in liblinphone.
• Yocto, BitBake and NXP i.MX image and service integration.
• Provisioning with SNMP, DHCP and TFTP, and the .NET 8 provisioning tool.

Do not claim:

• Broadband gateway or access-network experience.
• TR-069, TR-181, DSL, GPON or FTTH.
• RDK-B, OpenWrt, prplOS, EasyMesh or Wi-Fi roaming.
• Packet-capture expertise.
• Work for a tier-one operator.
• English above the documented B2.
• A senior or lead title, since the CV does not print one.

LIKELY INTERVIEW QUESTIONS

1. Walk me through one third-level incident from escalation to closure.
Answer direction: Use a registration or failover case from the first project. Separate symptom, reproduction, evidence, fault domains, the change, validation and handover. State that the device was a SIP endpoint.

2. Your CV says you owned third-level investigation. What did owned mean?
Answer direction: Technical ownership of the investigation and of the correction in the layer you owned, not ownership of the support organization, service levels, the customer network or the external private branch exchange.

3. How do you decide whether a problem is in the device, firmware, network or remote service?
Answer direction: Known-good comparisons, preserved timestamps and configuration, boundary tests, correlated logs, one variable at a time, and evidence before transferring ownership.

4. What are TR-069 and TR-181?
Answer direction: Management protocol against data model, at a high level, explicitly labelled as prepared knowledge.

5. What is your packet-capture experience?
Answer direction: State the gap directly. Do not substitute general networking knowledge for it.

6. How would you troubleshoot a gateway that is online but not manageable?
Answer direction: Physical and access state, addressing, routing, name resolution and time, management-server reachability and transport security, session evidence, identity and provisioning data, then data-model status. Mark it as a theoretical workflow.

7. How current and how deep is your embedded Linux work?
Answer direction: Be accurate about the CV. It is the current project: Yocto image content, systemd ordering, the ARM64 target, on-device debugging.

QUESTIONS TO ASK THE CUSTOMER

1. Which Deutsche Telekom business unit and deployment does this role support?
2. Which CPE models, silicon vendors, firmware branches and platform stack are in scope?
3. Is the stack RDK-B, OpenWrt, prplOS, proprietary, or a mixture?
4. Which access technologies are active: DSL or VDSL, GPON, XGS-PON, FTTH with an external ONT?
5. Is direct TR-069 and TR-181 experience a mandatory hiring gate, or can strong embedded triage experience be accepted?
6. Which auto-configuration server, telemetry, ticketing, log and packet-capture systems are used?
7. Does the engineer get source and build access, or is the role evidence and vendor escalation only?
8. Where are the boundaries between operator, CPE vendor, chipset vendor, access-network team and support organization?
9. What are the service-level targets, severity model, on-call expectations and handover hours?
10. What does a complete vendor-ready defect package look like for this programme?
11. Is English C1 formally required or assessed in the interview?
12. Is the contract still open after the stated submission deadline?

PREPARATION PRIORITIES

1. Confirm with the intermediary whether the missing broadband vocabulary is an automatic filter, since that decides whether any further preparation is worth the time.
2. Build a precise TR-069 and TR-181 model: customer premises equipment and auto-configuration server, Inform, connection request, remote procedures, faults, parameter paths, interface stacking, diagnostics and the relationship to USP.
3. Learn the access chain and its failure indicators for DSL, GPON and FTTH: endpoint, modem or optical terminal, line state, authentication, addressing, routing and service activation.
4. Practise packet capture in a Linux lab: DHCP, name resolution, address resolution, TCP resets and retransmissions, ICMP, and a management-session trace. This is the one named must-have that can be closed quickly.
5. Learn RDK-B architecture and logging at component and hardware-abstraction level.
6. Build a small OpenWrt lab: UCI, ubus, netifd, procd, logread, interface state, DHCP, firewall, image basics.
7. Read prplOS and prplMesh architecture at a high level.
8. Prepare one incident report and one diagnostic runbook in a vendor-ready format.
9. Prepare the answer for why the CV headline says Broadband Triage Engineer while every project label says Software Engineer.

PUBLIC SOURCES

1. 5V Video
https://www.weare5vvideo.com/

2. 5V Video RDK-B case study
https://www.weare5vvideo.com/video/case-study/accelerating-rdk-b-delivery-for-vantiva

3. Deutsche Telekom 2025 Annual Report, Germany segment
https://report.telekom.com/annual-report-2025/management-report/development-of-business-in-the-operating-segments/germany.html

4. Deutsche Telekom 2025 Annual Report, investments
https://report.telekom.com/annual-report-2025/management-report/group-strategy/investments.html

5. Deutsche Telekom Speedport support
https://www.telekom.de/hilfe/geraete/router/speedport/smart-serie

6. Deutsche Telekom fibre-compatible routers
https://www.telekom.de/hilfe/internet-telefonie/glasfaser/kompatible-router

7. Broadband Forum TR-069 certification overview
https://broadband-forum.org/public/certifications/bbf-069-certification/

8. Broadband Forum TR-181 Device:2
https://device-data-model.broadband-forum.org/

9. RDK-B architecture
https://developer.rdkcentral.com/documentation/documentation/rdk_broadband_documentation/architecture/

10. OpenWrt documentation
https://openwrt.org/docs/start

11. prpl Foundation
https://prplfoundation.org/

FINAL DECISION NOTES

Submit only if the customer accepts an engineer with strong embedded triage fundamentals on a SIP endpoint and no broadband management or access-network background. Against the submitted CV, four of the ten must-haves have no anchor at all, and the strongest claim rests on a single seventeen-month project. If TR-069, TR-181, access technologies and packet capture are strict evidence-based gates, this is not a close match.
