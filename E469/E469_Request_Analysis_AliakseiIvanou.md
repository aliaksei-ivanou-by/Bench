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
Analysis status: Reviewed

EVIDENCE RULES

VERIFIED REQUEST FACT means the information is recorded in the reviewed and normalized Request document.
VERIFIED PUBLIC FACT means the information is supported by an official public source listed below.
CONFIRMED CANDIDATE EVIDENCE means the information is supported by the verified career repository.
INFERENCE means a useful interpretation that has not been confirmed by the customer.
OPEN QUESTION means information that must be obtained from the recruiter or customer.
GAP means a requested capability that is not supported by verified candidate evidence.

EXECUTIVE ASSESSMENT

Overall fit: PARTIAL, WITH MAJOR DOMAIN GAPS
Recommendation: QUALIFY THE SCREENING GATES BEFORE SUBMISSION

The candidate is strong in C and C++, embedded Linux, source-level debugging, logs, networked device behavior, provisioning, recovery logic, and cross-layer fault isolation on physical endpoints. This is credible transferable evidence for third-level triage.

The request, however, asks for direct broadband gateway and access-network experience: TR-069, TR-181, DSL, GPON, FTTH, packet capture, and preferably RDK-B, OpenWrt, prplOS, and Wi-Fi mesh. Those areas are not supported by the verified career repository. The most recent endpoint was a SIP desk phone rather than a residential gateway, and the verified work did not include an operator broadband support organization. The CV also states English B2 while the request asks for C1.

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
Workload: Full-time is implied by the role but not separately stated in the source fields
Location: Fully remote; no location restrictions stated
Working time: EU time zones
Duration: Twelve months with extensions expected; a separate field says one to two years
English requirement: C1
Submission deadline in the source: 2026-09-08
Deadline status at research date: Passed; current availability of the request must be reconfirmed

CUSTOMER CHAIN

Request source or staffing intermediary: 5V Video
Named final client: Deutsche Telekom
Product owner and internal Deutsche Telekom unit: Not disclosed
Specific CPE platform, hardware vendor, software stack, and access network: Not disclosed

The request explicitly names Deutsche Telekom as the final client. It does not confirm whether the engineer would join a Telekom team directly, work through a managed service, or support a vendor-owned CPE platform.

CUSTOMER AND DOMAIN RESEARCH

Research item 1
Verified public fact: 5V Video presents itself as a specialist talent provider and shows RDK-related partnerships and an RDK-B staffing case study. Its public Vantiva case study describes supplying RDK-B developers, embedded engineers, QA engineers, and Wi-Fi testers for a broadband gateway project.
Interview implication: The intermediary is likely to screen for exact RDK and broadband vocabulary before the customer interview. A strong general embedded profile may not pass if direct RDK-B or TR-069 experience is a hard filter.
Sources:
https://www.weare5vvideo.com/
https://www.weare5vvideo.com/video/case-study/accelerating-rdk-b-delivery-for-vantiva

Research item 2
Verified public fact: Deutsche Telekom's 2025 annual report records approximately 15.1 million retail broadband lines in Germany and 21.0 million fiber-optic-based retail and wholesale lines at year end. It also describes an ongoing shift from DSL to FTTH and a target of passing around 2.5 million additional homes per year with fiber.
Interview implication: Triage may span a large installed base and mixed access generations. Reproducibility, clean fault-domain isolation, and vendor-ready evidence are likely more important than one-off debugging heroics.
Sources:
https://report.telekom.com/annual-report-2025/management-report/development-of-business-in-the-operating-segments/germany.html
https://report.telekom.com/annual-report-2025/management-report/group-strategy/investments.html

Research item 3
Verified public fact: Deutsche Telekom's support material covers a family of Speedport routers, active firmware releases, DSL and fiber compatibility, external and integrated fiber modems, and mesh-capable products.
Interview implication: The role may involve multiple device models, firmware branches, and access arrangements. The exact product family must be confirmed instead of assuming Speedport or any particular vendor.
Sources:
https://www.telekom.de/hilfe/geraete/router/speedport/smart-serie
https://www.telekom.de/hilfe/internet-telefonie/glasfaser/kompatible-router

Research item 4
Verified public fact: Broadband Forum describes TR-069 or CWMP as a remote-management platform for service providers to recognize, provision, and maintain CPE across its lifecycle. TR-181 Device:2 defines a device data model for TR-069 and USP-enabled endpoints, including interfaces, routing, bridging, statistics, and diagnostic tests.
Interview implication: Knowing the distinction matters: TR-069 is the management protocol and RPC behavior, while TR-181 is the managed object and parameter model. Both are direct gaps in the verified experience.
Sources:
https://broadband-forum.org/public/certifications/bbf-069-certification/
https://device-data-model.broadband-forum.org/

Research item 5
Verified public fact: RDK-B documentation describes a layered broadband architecture with application, middleware, and hardware-abstraction layers. The platform is componentized and supports access technologies including DSL, GPON, and LTE.
Interview implication: A triage engineer must determine whether a fault belongs to an application or manager component, common middleware, the HAL, the platform or driver layer, or the external network. This is structurally similar to the candidate's cross-layer debugging method, although the RDK-B components themselves are new.
Source: https://developer.rdkcentral.com/documentation/documentation/rdk_broadband_documentation/architecture/

Research item 6
Verified public fact: OpenWrt describes itself as a Linux distribution for embedded network devices and exposes configuration, service, logging, and network-diagnostic workflows. prpl Foundation describes prplOS as an open-source carrier-grade networking-device stack built around open standards and interfaces.
Interview implication: Embedded Linux fundamentals transfer, but OpenWrt UCI and netifd, prplOS APIs, and their platform-specific diagnostics require direct preparation.
Sources:
https://openwrt.org/docs/start
https://prplfoundation.org/

ROLE OUTCOME

Success means taking an escalation that first- and second-line support could not resolve, making it reproducible, gathering the right device and network evidence, isolating the failing layer, and either implementing and validating a fix or producing a defect report that a vendor can act on without repeating the investigation. Repeated issues should become diagnostic playbooks and feedback to engineering and support.

MUST-HAVE REQUIREMENT MAPPING

Requirement 1: Proven third-level or escalation engineering in a broadband or CPE environment
Priority: MUST-HAVE
Candidate evidence: Third-level technical investigation across a networked embedded SIP endpoint, customized SDK, application, provisioning, Linux services, firmware image, and hardware. The candidate reproduced customer and QA issues and validated recovery on physical devices.
Match: ADJACENT
Boundary or risk: The endpoint was a SIP phone, not a broadband gateway. The verified role was engineering with escalation responsibility, not employment in an operator's L3 broadband support function.
Safe interview wording: I performed third-level technical investigation on a networked embedded endpoint and owned faults through reproduction, fault-domain isolation, code or configuration changes, and validation. I have not worked directly in a broadband gateway support organization.

Requirement 2: Strong C++ and embedded Linux
Priority: MUST-HAVE
Candidate evidence: C++17 and Qt on ARM64 embedded Linux, customized liblinphone integration, Yocto and BitBake, systemd, Wayland and Weston, device services, firmware packaging, and target-device diagnosis.
Match: STRONG
Boundary or risk: The application domain was SIP telephony rather than a router or residential gateway.
Safe interview wording: My strongest recent experience is C++17 on an ARM64 embedded Linux product, including application, SDK, image integration, services, and real-device debugging.

Requirement 3: Genuine code-level debugging with gdb, log analysis, and packet capture
Priority: MUST-HAVE
Candidate evidence: gdb and gdbserver, source-level C and C++ debugging, application, SIP, and system logs, Linux core dumps, Valgrind, generated configuration, and reproducible physical-device scenarios.
Match: PARTIAL TO STRONG
Boundary or risk: Verified evidence supports gdb and logs. Hands-on packet-capture analysis with tcpdump or Wireshark is not established and must not be claimed from the tailored CV alone.
Safe interview wording: I have strong source-level and log-based debugging experience on embedded Linux. Packet capture is a preparation area rather than a verified project strength.

Requirement 4: TR-069 and TR-181
Priority: MUST-HAVE
Candidate evidence: No verified project use. The closest experience is SNMP-based discovery and querying, DHCP and TFTP provisioning, device configuration generation, SIP authentication, and endpoint management.
Match: GAP
Boundary or risk: Adjacent provisioning protocols do not equal CWMP, an Auto Configuration Server, or the TR-181 data model.
Safe interview wording: I have worked on automated endpoint discovery and provisioning, but not on TR-069 or TR-181. I understand the distinction and am preparing their main flows and data model.

Requirement 5: DSL, GPON, and FTTH
Priority: MUST-HAVE
Candidate evidence: General TCP/IP, DHCP, VLAN, device networking, WAN interruption and recovery scenarios, and physical networked endpoints.
Match: GAP
Boundary or risk: No verified access-network engineering with DSL synchronization, PON states, ONT or OLT behavior, optical levels, or operator provisioning.
Safe interview wording: My network experience is endpoint and product-side. I do not claim hands-on DSL, GPON, or FTTH access-network operations.

Requirement 6: Work independently across vendor and operator teams
Priority: MUST-HAVE
Candidate evidence: Worked across an outsourcing team and customer engineers, QA, firmware, application, and external SIP or PBX boundaries; documented findings and took assigned technical work through validation.
Match: PARTIAL
Boundary or risk: Direct ownership of defects across operator and CPE-vendor organizations is not established.
Safe interview wording: I am comfortable working across team and component boundaries and producing evidence that lets the owning party act. I would not claim prior ownership of an operator-to-vendor escalation process.

Requirement 7: Distributed team across time zones
Priority: MUST-HAVE
Candidate evidence: Cross-company remote collaboration is supported by the recent projects.
Match: PARTIAL
Boundary or risk: The exact number of time zones and any on-call schedule are not verified.
Safe interview wording: I have worked remotely across company boundaries and can keep investigations traceable through written evidence, status, and handover. I would confirm the required hours and on-call model.

Requirement 8: English C1
Priority: MUST-HAVE
Candidate evidence: The request-specific CV states English B2.
Match: GAP
Boundary or risk: Do not claim a certified or documented C1 level.
Safe interview wording: My documented level is B2; the customer should assess whether my working communication meets the role.

RESPONSIBILITY ALIGNMENT

Responsibility 1: Own escalated broadband faults from reproduction through root cause
Alignment: Strong investigation method, adjacent domain.
Evidence: Customer and QA issue reproduction, cross-layer fault isolation, code and configuration changes, and physical-device validation.
Boundary: No direct broadband-gateway escalation history.

Responsibility 2: Debug CPE firmware, gateway software, and access-network components at code level
Alignment: Strong embedded endpoint and firmware-side debugging; access-network gap.
Evidence: Qt application, customized SDK, Yocto image, services, device runtime, and hardware.
Boundary: No verified gateway or access-network component ownership.

Responsibility 3: Analyze logs, packet captures, and device telemetry
Alignment: Strong logs and configuration evidence; packet capture and operator telemetry gaps.
Evidence: Application, SIP, system and boot logs, state diagnostics, configuration artifacts, and device scenarios.
Boundary: Do not claim Wireshark, tcpdump, or telemetry-platform experience without separate verification.

Responsibility 4: Raise and evidence defects to platform and hardware vendors
Alignment: Transferable but not directly proven in the same organizational model.
Evidence: Fault-domain isolation, ownership boundaries, reproducible scenarios, and work across customer and component teams.
Boundary: Direct vendor ticket ownership and hardware-vendor escalation are not verified.

Responsibility 5: Feed recurring fault patterns back to engineering and support
Alignment: Strong engineering habit.
Evidence: Architecture notes, repeatable scenarios, compatibility fixes, release notes, tests, and explicit boundary documentation.
Boundary: No metric for reduced recurrence or support volume is available.

Responsibility 6: Build repeatable diagnostic steps
Alignment: Strong.
Evidence: Reproduction-first workflow, logs, configuration capture, focused tests, physical-device validation, and reusable interview documentation derived from repository evidence.
Boundary: Customer-specific runbooks remain to be learned.

NICE-TO-HAVE REQUIREMENT MAPPING

Requirement 1: RDK-B
Candidate evidence: No verified exposure.
Match: GAP
Preparation bridge: Study CCSP or component services, message bus, persistent storage, provisioning and management components, HAL boundaries, RDK logs, and common fault domains.

Requirement 2: OpenWrt
Candidate evidence: No verified project use.
Match: GAP
Preparation bridge: Embedded Linux and network-service experience will help, but UCI, netifd, ubus, procd, opkg, logread, and OpenWrt image workflows are new.

Requirement 3: prplOS
Candidate evidence: No verified project use.
Match: GAP
Preparation bridge: Learn its relationship to carrier-grade CPE, open APIs, Broadband Forum models, OpenWrt, and prplMesh.

Requirement 4: Wi-Fi mesh, EasyMesh, and roaming
Candidate evidence: No verified project experience.
Match: GAP
Preparation bridge: Learn controller and agent roles, backhaul versus fronthaul, topology, steering, roaming symptoms, channel and interference evidence, and client-specific behavior.

Requirement 5: Prior work with a tier-one operator
Candidate evidence: No verified work for a tier-one telecom operator.
Match: GAP

KEY RISKS AND NON-CLAIMS

1. No verified TR-069 or TR-181 project experience.
2. No verified DSL, GPON, FTTH, OLT, or ONT work.
3. No verified RDK-B, OpenWrt, prplOS, EasyMesh, or Wi-Fi roaming work.
4. No verified packet-capture workflow with Wireshark or tcpdump.
5. The recent CPE-like device was a SIP endpoint, not a broadband gateway.
6. No verified tier-one operator engagement.
7. English is documented as B2 rather than C1.
8. Broadband Triage Engineer is the target role, not the formal job title.
9. The source submission deadline has passed.
10. The specific Deutsche Telekom unit, platform, vendors, and on-call expectations are unknown.

INTERVIEW POSITIONING

Lead with:

• End-to-end technical investigation and evidence-driven fault isolation.
• C++17, embedded Linux, gdb and gdbserver, logs, core dumps, services, and physical-device validation.
• WAN interruption and recovery, SIP registration watchdog, failover and failback, and provisioning consistency.
• Yocto image integration, systemd and startup diagnosis, and hardware-adjacent debugging.
• Clear ownership boundaries and ability to produce a reproducible defect package.

Do not claim:

• Direct broadband gateway or access-network experience.
• TR-069 or TR-181 implementation or operations.
• DSL, GPON, or FTTH troubleshooting.
• RDK-B, OpenWrt, prplOS, EasyMesh, or roaming experience.
• Packet-capture expertise unless independently confirmed.
• Prior work for a tier-one operator.
• English C1 as a documented fact.

LIKELY INTERVIEW QUESTIONS

1. Walk through an L3 incident from escalation to closure.
Answer direction: Use a SIP registration, failover, or target-startup incident. Separate symptom, reproduction, evidence, fault domains, code or configuration change, validation, and handover. State that the domain was a SIP endpoint.

2. How do you decide whether a problem is in the device, firmware, network, or remote service?
Answer direction: Establish known-good comparisons, preserve timestamps and configuration, test layer boundaries, correlate logs, change one variable at a time, and require evidence before transferring ownership.

3. What are TR-069 and TR-181?
Answer direction: Explain the management protocol versus the data model at a high level and state that this is prepared knowledge, not project experience.

4. How would you troubleshoot a CPE that is online but not manageable?
Answer direction: Work from physical and access state through IP addressing, routing, DNS and time, ACS reachability and TLS, CWMP session evidence, identity and provisioning data, and TR-181 status. Mark this as a theoretical workflow.

5. How do you create a vendor-ready defect?
Answer direction: Minimal reproduction, device and firmware identity, configuration delta, synchronized timestamps, logs and packet evidence, expected versus actual behavior, suspected component, impact, and clean retest criteria.

6. What is your packet-capture experience?
Answer direction: State the verified gap. Do not replace it with general network knowledge.

QUESTIONS TO ASK THE CUSTOMER

1. Which Deutsche Telekom business unit and deployment is this role supporting?
2. Which CPE models, silicon vendors, firmware branches, and platform stack are in scope?
3. Is the stack RDK-B, OpenWrt, prplOS, a proprietary platform, or a mixture?
4. Which access technologies are active: DSL or VDSL, GPON, XGS-PON, FTTH with an external ONT, or others?
5. Is direct TR-069 and TR-181 experience a mandatory hiring gate, or can strong embedded triage experience be accepted?
6. Which ACS, USP controller, telemetry, ticketing, log, and packet-capture systems are used?
7. Does the engineer have source and build access, or is the role evidence and vendor escalation only?
8. What are the boundaries between operator, CPE vendor, chipset vendor, access-network team, and support organization?
9. What are the service-level targets, severity model, on-call expectations, and handover hours?
10. What does a complete defect package look like for this program?
11. Is English C1 formally required or assessed through the interview?
12. Is the contract still open after the stated submission deadline?

PREPARATION PRIORITIES

1. Build a precise TR-069 and TR-181 mental model: CPE, ACS, Inform, connection request, RPCs, faults, parameter paths, interface stacking, diagnostics, and relationship to USP.
2. Learn the access chain and failure indicators for DSL, GPON, and FTTH, including CPE, modem or ONT, OLT or DSLAM, link state, authentication, addressing, routing, and service activation.
3. Practice packet capture on a Linux router lab: DHCP, DNS, ARP or neighbor discovery, TCP resets and retransmissions, ICMP, PPPoE if available, and a management-session trace.
4. Learn RDK-B architecture and logging at a component and HAL level.
5. Build a small OpenWrt lab and practice UCI, ubus, netifd, procd, logread, interface state, DHCP, firewall, and package or image basics.
6. Read prplOS and prplMesh architecture at a high level.
7. Prepare one incident report and one diagnostic runbook in a vendor-ready format.
8. Confirm the English gate and exact platform before deep preparation.

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

6. Deutsche Telekom fiber-compatible routers
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

Proceed only if the customer accepts a candidate with strong embedded triage fundamentals but without direct broadband management and access-network experience. If TR-069, TR-181, DSL, GPON, FTTH, and packet capture are strict evidence-based must-haves, the candidate is not currently a close match.
