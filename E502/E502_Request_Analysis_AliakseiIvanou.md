REQUEST ANALYSIS

DOCUMENT INFORMATION

Request ID: E502
Candidate: Aliaksei Ivanou, presented in the CV as Alex I.
Target role: Ceph Developer, revised to Senior C++ Developer with Ceph or NetApp, Kubernetes and infrastructure experience
CV source: E502 Aliaksei Ivanou (13, C++).pdf
Request document: E502_Request_AliakseiIvanou.md
Profile: E502_Profile_AliakseiIvanou.md
Reality source: Summary/Interview/Career Overview.md; Summary/Interview/Recruiter Brief.md; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md; Summary/Interview/2022-2024. Integrated Library System.md; Summary/Interview/2021. Oil and Gas Corporate System.md; Summary/Interview/2020-2021. Independent C++ Engineering Projects.md; Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md; Summary/Interview/Certificates and Continuing Education.md
Analysis date: 2026-11-06
Preparation language: English
Document status: Interview-ready with explicit Ceph, Kubernetes and observability gaps and qualification conditions

PURPOSE

This analysis evaluates the supplied request against the candidate's real, defensible experience. The selected CV is compared with the factual Summary repository, and every requested responsibility and requirement receives one coverage result based on that reconciled evidence rather than on CV wording alone.

The revised profile is the primary basis for the current fit assessment. The original responsibilities and specialist requirements are retained as technical context; their continued applicability to the revised role is not established. The 27 mapped items form a review catalogue across both versions, including overlapping requirements, rather than 27 independent current selection criteria. Internal instructions about CV formatting or project duration are outside this assessment.

EVIDENCE RULES

REQUEST FACT: Recorded in the normalized Request document.
CONFIRMED CANDIDATE EVIDENCE: Supported by the Summary repository.
CV-ONLY CLAIM: Present in the selected CV but not supported by Summary.
INFERENCE: A useful interpretation that the client has not confirmed.
OPEN QUESTION: Information that must be obtained from the intermediary or client.
GAP: A requested capability without defensible Summary evidence.

Coverage vocabulary:

- COVERED: the CV and Summary together contain direct, defensible evidence.
- PARTIALLY COVERED: Summary supports adjacent or narrower experience but not the full requested scope.
- NOT COVERED: Summary contains no defensible evidence.

EXECUTIVE ASSESSMENT

Overall fit: WEAK for the original Ceph Developer request; WEAK TO PARTIAL for the revised versatile C++ and infrastructure profile
Recommendation: QUALIFY BEFORE PROCEEDING; do not present the candidate as Ceph-experienced

The candidate has a defensible base as a C and C++ engineer on Linux: two years as a C89 backend developer on a large production library platform running on AWS EC2 Linux hosts, with log-first cross-service diagnosis, gdb, core dumps and Valgrind; a short C++17 assignment on an Azure-hosted industrial-data system; and fifteen months of C++17 and Qt work on an embedded Linux product, including a customized fork of an open-source SIP SDK, Yocto images, systemd services and target debugging on ARM64 hardware. He also has fourteen years across software engineering and R&D, strong cross-layer diagnosis habits and, since October 2025, People Lead responsibilities for an internal engineering sub-group.

The request's distinguishing core is not supported. Summary contains no evidence of Ceph in any form, NetApp, Kubernetes, Rook, Ceph CSI, Prometheus, Grafana, OpenStack, S3 or Swift object-storage integration, storage performance work, upstream open-source contribution or production Python. The CV project that carries the Ceph, Kubernetes, Python and monitoring claims, Remote Sensing Satellites Database, corresponds in Summary to a Ruby on Rails and PostgreSQL satellite reference database built at PELENG in 2015 and 2016; the Ceph, Kubernetes, C++ ingestion, Python and monitoring content is a CV-only claim, and the CV period of April 2022 to April 2024 falls within the real library-system assignment at EPAM, which ran from March 2022 to April 2024.

The revised request shifts the emphasis from Ceph core development to a versatile developer with "some Ceph experience", which makes the general C++, Linux and diagnosis profile more relevant. It introduces NetApp alongside Ceph and retains Kubernetes, which was already in the original description. Hands-on experience in these storage and orchestration technologies is not supported. Ceph architecture and Kubernetes storage integration are reasonable preparation priorities, but the interview format and question order are unknown. Proceed only if the intermediary confirms that the client will consider a strong C and C++ Linux engineer who learns Ceph and Kubernetes on the project, and submit a CV that does not claim hands-on Ceph operation.

REQUEST FACTS

Role: Ceph Developer, revised to a very strong versatile developer with Ceph or NetApp, Kubernetes, C++ development and infrastructure experience and some Ceph experience
Seniority: Senior
Industry and domain: Information technologies; OpenStack-based cloud infrastructure, distributed storage, Kubernetes
Delivery context: GCID PlusOne Central Engineering team developing and operating external SAP Cloud Infrastructure services
Engagement: Start as soon as possible; end on 31 December 2026 or later with a very likely extension; three to six months in the administrative field
Capacity: 40 hours per week desired, 30 hours per week minimum
Work model: 100% remote in the role description; the location field also mentions onsite presence and/or business travel
Location: EU only
Time zone: CET
Language: English, B2+
Headcount: One
Submission deadline in the request: 17 July 2026

CUSTOMER CHAIN

Request source: Innowise partner channel, regional group DACH3: Partners
Named final client in the request: Nemensis AG, Germany; the intermediary that returned with the changed requirements is not identified by name
Delivery context: GCID PlusOne Central Engineering team, SAP Cloud Infrastructure
Confidence and boundary: The request text describes the team as developing and running external SAP Cloud Infrastructure services for its customers. That the engineer will work inside an SAP cloud-infrastructure organization through Nemensis AG is an inference from the project background; the contracting chain, hiring manager and interview panel are not stated.

CUSTOMER AND DOMAIN CONTEXT

- Request fact: The cloud services are built on OpenStack, and the team develops its own solutions where OpenStack does not provide a suitable one.
  Interview implication: Expect questions on how storage is consumed in OpenStack, for example Cinder volumes on RBD, Glance images, Manila shares and Swift or S3 object storage through RGW. The candidate has no OpenStack experience and should prepare this context as theory.
  Source: E502_Request_AliakseiIvanou.md, Role summary

- Request fact: The team operates the platform in production, runs monitoring services, provides 24-hour follow-the-sun troubleshooting support and operates the control plane.
  Interview implication: Operational diagnosis is part of the role. The candidate's strongest transferable stories are production log-first diagnosis on Linux and cross-layer failure isolation; he has no on-call or SRE rotation experience in Summary.
  Source: E502_Request_AliakseiIvanou.md, Role summary

- Request fact: The original request names contributions to upstream Ceph and internal forks across RGW, RADOS, RBD and CephFS.
  Interview implication: Maintaining internal changes on top of an open-source codebase is directly analogous to the candidate's work in a customized Linphone SDK, where he implemented a registration watchdog and primary/backup failover and failback. This is a transferable fork-maintenance story, not Ceph experience.
  Source: E502_Request_AliakseiIvanou.md, Role summary; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 01

- Request fact: The revised description widens the profile to a strong developer across several technical areas, retaining some Ceph experience and naming NetApp alongside Ceph. The reason for the change and the products actually deployed are not established by the request.

ROLE OUTCOME

Success in this role probably means becoming productive quickly in a large, operating OpenStack cloud: understanding how Ceph and possibly NetApp back the storage services, diagnosing low-level storage and Linux behavior in production, implementing C++ changes in Ceph or surrounding services, integrating storage with Kubernetes through Rook and CSI, improving metrics-based observability and participating in the team's support and review processes. Under the revised profile, breadth and independent problem solving across development and infrastructure matter more than deep specialization in one Ceph daemon.

This outcome is an inference from the request. The proportion of Ceph source-code work, NetApp administration, Kubernetes operations and support duty has not been disclosed.

CV PROJECT RECONCILIATION

Project 1. SIP Desk Phone Platform for Audio and Video Communication
CV period and role: May 2024 – till now; Software Engineer
Summary record: Innowise, May 2025 – August 2026; C++ Software Engineer, middle grade, with internal People Lead responsibilities from October 2025; between assignments since September 2026
Classification: FULL MATCH with FACTUAL CORRECTION of the start date and current status
Request relevance: Embedded Linux, Yocto, systemd, C++17 and Qt, work inside a customized open-source SDK, cross-layer target debugging, GitLab CI
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, sections 01, 04 and 07

Project 2. Remote Sensing Satellites Database
CV period and role: April 2022 – April 2024; Software Engineer
Summary record: PELENG satellite reference database with a web interface, Ruby on Rails and PostgreSQL, February 2015 – February 2016, designed and implemented by the candidate; April 2022 – April 2024 falls within the Sierra library-system assignment at EPAM, March 2022 – April 2024
Classification: NOT FULL MATCH
Request relevance: The CV's C++ ingestion, POSIX streaming I/O, multithreaded validation, Ceph RGW through S3 API, Rook, Ceph CSI and RBD, Ceph performance investigation, Python scripts and Prometheus and Grafana monitoring are CV-only claims. Only the Ruby on Rails and PostgreSQL catalogue work is supported, at a different time and employer.
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md, sections 01 and 13; no Ceph, Kubernetes, Rook, Prometheus, Grafana or S3 evidence anywhere in Summary/Interview

Project 3. Software Modules for UAV
CV period and role: March 2020 – March 2022; Software Engineer
Summary record: UAV optical-system workstream at PELENG within August 2012 – January 2020; debayering, format conversion, stabilization and frame fusion in MATLAB
Classification: FULL MATCH for the work, with FACTUAL CORRECTION of the period; C++ implementation is not supported
Request relevance: Low; memory-aware image processing is adjacent only in a general performance sense
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md, sections 01 and 13

Project 4. Software for Processing and Analysis of Satellite Earth Observation Images
CV period and role: January 2018 – February 2020; Software Engineer
Summary record: PELENG workstreams within August 2012 – January 2020; frame stitching, ADPCM compression, quantization-range prediction and linear-resolution assessment in MATLAB
Classification: FULL MATCH for the work, with FACTUAL CORRECTION of the period; C++ implementation is not supported
Request relevance: Low; design under hard compute constraints and repeatable measurement are transferable habits
Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md, sections 01 and 13

Project 5. Library System
CV period and role: January 2015 – December 2017; Software Engineer
Summary record: Sierra integrated library system, EPAM for Innovative Interfaces, March 2022 – April 2024; primarily C89 backend developer with occasional Java and Scala work; production services on AWS EC2 Linux; Jenkins and Bitbucket
Classification: FULL MATCH with FACTUAL CORRECTION of the period; AWS S3 integration, streaming and byte-range transfers and socket-component design are not supported
Request relevance: Highest among the real projects: production C on Linux, cross-service diagnosis, gdb, core dumps, Valgrind, AWS-hosted production, Agile delivery and multi-reviewer code review
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 01, 03, 04 and 07

Project 6. Corporate System for the Oil and Gas Industry
CV period and role: August 2012 – December 2014; Software Engineer
Summary record: Schlumberger corporate industrial-data system, EPAM, October 2021 – January 2022; Junior C++ Software Engineer; C++17, MySQL and Microsoft SQL Server, Nginx, Microsoft Azure
Classification: FULL MATCH with FACTUAL CORRECTION of the period and C++ standard; LevelDB integration and tuning are not supported
Request relevance: Moderate: C++17 backend work on an Azure-hosted system and safe change inside legacy code
Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md, section 01

RESPONSIBILITY AND REQUIREMENT MAPPING

Request item 1. Design and implement new features in Ceph, including RGW, RADOS, RBD and CephFS

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Ceph RGW integration through S3 API
Summary evidence: No supporting evidence in Summary
Assessment: The candidate has never worked in the Ceph codebase or with a Ceph cluster. The closest real evidence is feature development inside large inherited codebases: the Sierra C89 backend and a customized Linphone SDK, where he implemented new SDK-side behavior.
Interview response: I have not developed Ceph features. My relevant experience is implementing features inside large existing C and C++ codebases, including SDK-level changes in a customized open-source SIP stack, and I would approach Ceph the same way: understand the data path and invariants first, then change the narrowest component.

Request item 2. Optimize the performance, scalability and reliability of the storage system

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Ceph performance investigation; Oil and gas, LevelDB tuning
Summary evidence: No supporting evidence in Summary for storage performance work
Assessment: No storage-system tuning, OSD or BlueStore analysis, LevelDB or RocksDB tuning or benchmark campaigns are recorded. Reliability work on the SIP platform, primary/backup failover and failback, is real but is not storage.
Interview response: I have not tuned a storage system. My reliability example is SIP primary/backup failover that I implemented in the SDK, and my performance habit is to measure the actual path before changing it.

Request item 3. Troubleshoot distributed storage issues and debug low-level system behavior

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: Library System, backend modules and service communication; SIP platform, target integration
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 01, 03 and 04; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, sections 03 and 04
Assessment: Low-level debugging is directly supported: log-first diagnosis across services and language runtimes, gdb and core dumps on AWS EC2 Linux, Valgrind for invalid-memory and initialization defects in C, and gdbserver on ARM64 targets. The distributed-storage part is not supported.
Interview response: Low-level diagnosis is my strongest area. On a production C platform on AWS Linux, a symptom in Java or Scala often led back to a C root cause, and I worked from correlated logs to gdb, core dumps and Valgrind. I have not diagnosed Ceph or other distributed-storage failures.

Request item 4. Participate in upstream Ceph development and community discussions

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary
Assessment: No upstream open-source contribution is recorded. Public GitHub repositories contain the candidate's own C++20 application and Stroustrup exercises. The customized Linphone SDK work was internal to the customer project.
Interview response: I have not contributed upstream to Ceph. I have maintained customer-specific changes in a customized open-source SDK, so I understand the cost of carrying a fork, but I have not gone through an upstream review process.

Request item 5. Integrate Ceph with Kubernetes through Rook and CSI drivers

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Rook Operator and Ceph CSI for RBD
Summary evidence: No supporting evidence in Summary
Assessment: Kubernetes, Rook and Ceph CSI project experience is not supported by Summary. Interview-theory question banks provide preparation material, not evidence that the candidate has mastered these technologies.
Interview response: I have not deployed Ceph with Rook or configured Ceph CSI. This would be new hands-on work for me.

Request item 6. Monitor and improve system observability using telemetry and metrics

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Prometheus and Grafana monitoring
Summary evidence: No supporting evidence in Summary for metrics systems
Assessment: Observability in the real record is log-based: service logs on Sierra, application, SIP and system logs and active-proxy diagnostics on the SIP platform. No Prometheus, Grafana, exporters, alerting or dashboards are recorded.
Interview response: My diagnostic work has been log-centred, including adding diagnostics where a state was invisible. I have not built Prometheus metrics or Grafana dashboards.

Request item 7. Plan and execute development tasks using Agile methodologies

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Oil and gas, task estimation and planning; Library System, release preparation
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04
Assessment: Two-week sprints, daily stand-ups, weekly grooming, demos and retrospectives with Jira on Sierra; Asana-based planning on the SIP platform; estimation of own tasks.
Interview response: I have worked in Scrum with two-week sprints, grooming, demos and retrospectives, and I estimate and plan my own work within that process.

Request item 8. Contribute to technical documentation, design reviews and internal knowledge sharing

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Library System, code reviews; SIP platform, architecture refactoring
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/Career Overview.md, section 02; Summary/Interview/Recruiter Brief.md, section 06
Assessment: All EPAM and customer reviewers had to approve a change on Sierra; Swagger documentation updates; call/account architecture decisions on the SIP platform; onboarding, 1:1s, development planning and interview preparation as People Lead from October 2025.
Interview response: Review and knowledge sharing are part of my routine: multi-reviewer approval on a production platform, architecture discussions on the embedded project and, since October 2025, mentoring and onboarding as People Lead while remaining hands-on.

Request item 9. Very strong developer with experience across various technical areas

Type: MUST-HAVE, REVISED
Coverage: PARTIALLY COVERED
Related CV item: All CV projects
Summary evidence: Summary/Interview/Career Overview.md, sections 02 to 04
Assessment: Breadth is real and unusual: C89 backend, C++17 backend, C++17 and Qt on embedded Linux with Yocto, SIP and WebRTC, C# and .NET 8 tooling, occasional Java, Scala and JavaScript, and seven years of MATLAB algorithm R&D. The formal grade is middle, not senior, and none of the areas is storage or cloud infrastructure.
Interview response: My profile is broad by design: I have worked across C backend services, C++ on embedded Linux, protocol stacks and Windows tooling, and earlier on aerospace algorithms. The common thread is diagnosing systems where behavior depends on several layers at once.

Request item 10. Development experience in C++

Type: MUST-HAVE, REVISED
Coverage: COVERED
Related CV item: SIP platform; Oil and gas; Library System
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 01; Summary/Interview/2021. Oil and Gas Corporate System.md, section 01; Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/2020-2021. Independent C++ Engineering Projects.md, section 01
Assessment: More than six years of C and C++ practice, five of them commercial: C++17 on the SIP platform and the oil-and-gas system, C89 on Sierra and a published C++20 application.
Interview response: C and C++ are my main languages: C++17 and Qt on embedded Linux most recently, C89 on a large production backend before that, and C++17 in an enterprise data system.

Request item 11. Infrastructure experience

Type: MUST-HAVE, REVISED
Coverage: PARTIALLY COVERED
Related CV item: SIP platform, Yocto and device-side service configuration; Library System, deployment workflow
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04; Summary/Interview/2022-2024. Integrated Library System.md, sections 01 and 03
Assessment: Supported infrastructure-adjacent work: Yocto Kirkstone recipes, packaging and systemd service startup; DHCP, TFTP and SNMP provisioning tooling; daily use of AWS EC2 Linux hosts over SSH; Jenkins and GitLab CI as a user. Data-centre, cloud-platform, storage or Kubernetes operations are not supported.
Interview response: My infrastructure experience is at the Linux system level: building device images with Yocto, defining systemd services, provisioning devices over DHCP and TFTP and debugging services on AWS Linux hosts. I have not operated cloud infrastructure or storage clusters.

Request item 12. Ceph or NetApp storage experience, including some Ceph experience

Type: MUST-HAVE, REVISED
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Neither Ceph nor NetApp is recorded. This is the decisive gap for both versions of the request.
Interview response: I do not have hands-on Ceph or NetApp experience. I would need to learn the storage stack on the project, starting from the client's own deployment.

Request item 13. Kubernetes experience

Type: MUST-HAVE, REVISED
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary; Summary/Interview/Certificates and Continuing Education.md records Docker as coursework only
Assessment: No project use of Kubernetes is recorded. Preparation material does not establish the candidate's current theoretical proficiency.
Interview response: I have not run workloads or storage on Kubernetes in a project. I would need to build practical experience with the team's deployment and operating model.

Request item 14. Senior engineering level

Type: MUST-HAVE, SHARED VACANCY CONDITION
Coverage: PARTIALLY COVERED
Related CV item: Professional summary
Summary evidence: Summary/Interview/Recruiter Brief.md, sections 06 and 07; Summary/Interview/Career Overview.md, section 02
Assessment: The formal grade is middle; senior was never awarded. Scope beyond the title includes design decisions and review on the embedded product and People Lead responsibilities for a sub-group that grew from four to six engineers, with roughly 80% hands-on delivery.
Interview response: My grade is middle. My scope has included architecture decisions on an embedded product and, since October 2025, People Lead responsibilities for an internal group of four to six engineers while staying primarily hands-on.

Request item 15. Strong proficiency in C++ and Python, five or more years

Type: MUST-HAVE, ORIGINAL
Coverage: PARTIALLY COVERED
Related CV item: Skills matrix: C++ 11 years, Python 2 years
Summary evidence: Summary/Interview/Recruiter Brief.md, section 07; occasional Python use in Summary/Interview/Vacancy Preparation/Vacancy Preparation. FinDev Senior C++ Engineer, Electronic Bond Trading/Vacancy Preparation. FinDev Senior C++ Engineer, Electronic Bond Trading.md, section 03
Assessment: C++17 work on the embedded and oil-and-gas projects and an independent C++20 application are directly supported. The C89 backend assignment is relevant systems-programming experience, but combining C and C++ duration does not by itself demonstrate five years of proficiency specifically in C++. Five years of Python proficiency and production Python are not established, so the combined requirement is not fully met.
Interview response: C and C++ are my primary languages with more than six years of practice. Python I have used occasionally for scripts, not as a production language.

Request item 16. Hands-on experience with Ceph: RGW, RADOS, RBD or CephFS

Type: MUST-HAVE, ORIGINAL
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Same gap as item 12, stated at component level.
Interview response: I have not worked hands-on with RGW, RADOS, RBD or CephFS.

Request item 17. Solid understanding of Linux internals: I/O, memory management and threading

Type: MUST-HAVE, ORIGINAL
Coverage: PARTIALLY COVERED
Related CV item: Library System; SIP platform
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 03 and 04; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04
Assessment: User-space Linux depth is supported: native memory defects in C with fixed-size buffers, Valgrind, core-dump analysis, processes and logs on Linux hosts, QThread and queued connections across thread boundaries, systemd and an embedded Linux image. Kernel I/O paths, page cache, block layer, direct I/O and NUMA or memory-management tuning are not supported.
Interview response: I work comfortably in Linux user space: native memory defects, core dumps, Valgrind, threads and cross-thread event delivery, services and images. Kernel-level storage I/O tuning I would treat as an area to deepen.

Request item 18. Familiarity with Kubernetes, Rook and Ceph CSI drivers

Type: MUST-HAVE, ORIGINAL
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Same gap as items 5 and 13.
Interview response: I have not used Kubernetes, Rook or Ceph CSI on a project; these would be new practical areas for me.

Request item 19. Experience with Git, GitHub and CI/CD pipelines

Type: MUST-HAVE, ORIGINAL
Coverage: COVERED
Related CV item: Source control systems: Git, GitLab, Bitbucket
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04; Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/Recruiter Brief.md, section 09
Assessment: Git across all commercial projects; GitLab with merge requests and GitLab CI; Bitbucket with Jenkins builds on AWS Linux and nightly or on-demand deployment; public GitHub repositories. Ownership of CI infrastructure is not established.
Interview response: I use Git daily with merge-request review and have worked with GitLab CI and Jenkins pipelines; I have used them rather than owned their infrastructure.

Request item 20. Exposure to large-scale infrastructure or cloud-native environments

Type: MUST-HAVE, ORIGINAL
Coverage: PARTIALLY COVERED
Related CV item: Library System; Oil and gas
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 01 and 02; Summary/Interview/2021. Oil and Gas Corporate System.md, section 01; Summary/Interview/Recruiter Brief.md, section 08
Assessment: Development on production systems hosted on AWS EC2 for a library-software vendor whose installed customer base served more than 9,000 libraries, and on Microsoft Azure for an oil-and-gas corporate system. The library count describes the vendor's customer base, not the deployment scale of the specific Sierra platform or the candidate's services. These are cloud-hosted, not cloud-native Kubernetes environments.
Interview response: I have developed and debugged services running on AWS and Azure for large production systems, but not in a Kubernetes-based cloud-native platform.

Request item 21. Proficiency with observability tools such as Prometheus and Grafana

Type: MUST-HAVE, ORIGINAL
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Same gap as item 6.
Interview response: I have not used Prometheus or Grafana in a project.

Request item 22. English at B2+ level

Type: MUST-HAVE, SHARED VACANCY CONDITION
Coverage: PARTIALLY COVERED
Related CV item: Language proficiency: English B2+
Summary evidence: Summary/Interview/Recruiter Brief.md, section 03
Assessment: English has been the professional working language since 2021 with distributed teams in the US, India and Europe. Summary records B2 as the defensible level, with course certificates through B1 and a B2 course exam result of 60.5/100.
Interview response: English has been my daily working language since 2021, including direct technical communication with customer teams. I would describe my level as B2.

Request item 23. EU location, CET working hours and at least 30 hours per week

Type: MUST-HAVE, SHARED VACANCY CONDITION
Coverage: PARTIALLY COVERED
Related CV item: No direct match
Summary evidence: Summary/Interview/Recruiter Brief.md, sections 02 and 07; Summary/Interview/Career Overview.md, section 02
Assessment: The candidate is available full time, works in a CET-compatible time zone and has been between assignments since September 2026. Summary records him as a Belarusian citizen in Minsk, relocating to Warsaw with a Polish national D visa valid from 26 September 2026 to 25 September 2027. The EU-location requirement is satisfied only once he works from Poland.
Interview response: I am available full time in CET hours. I hold a Polish national D visa and worked in Warsaw for two years before; my working location for the project would be Poland.

Request item 24. Contributions to open-source projects, especially Ceph

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary for open-source contribution; Summary/Interview/Recruiter Brief.md, section 09, records own public repositories only
Assessment: Own public repositories are not open-source project contributions.
Interview response: My public code is my own C++ projects; I have not contributed to an external open-source project.

Request item 25. Experience with cloud platforms: AWS, Azure or OpenStack

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Library System, AWS; Cloud skills
Summary evidence: Summary/Interview/Certificates and Continuing Education.md, section 06; Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/2021. Oil and Gas Corporate System.md, section 01
Assessment: Developer use of AWS EC2 Linux hosts and of an Azure-hosted system; two AWS digital training badges from May 2024, not certifications. No OpenStack.
Interview response: I have worked on systems hosted on AWS and Azure as a developer and hold two AWS training badges. I have not worked with OpenStack.

Request item 26. Familiarity with performance profiling tools and storage benchmarks

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: SIP platform, Valgrind and gdb
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04; Summary/Interview/2022-2024. Integrated Library System.md, section 04
Assessment: Valgrind and debugger-based diagnosis are supported; dedicated profilers such as perf and storage benchmarks such as fio, rados bench or COSBench are not.
Interview response: I use Valgrind and gdb regularly for diagnosis. Storage benchmarking tools would be new for me.

Request item 27. Knowledge of S3 and Swift protocols and object-storage semantics

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: Library System, AWS S3 integration; Remote Sensing Satellites Database, Ceph RGW through S3 API
Summary evidence: No supporting evidence in Summary
Assessment: The S3 integration and pre-signed URL claims are CV-only. AWS coursework covers S3 conceptually.
Interview response: I know the S3 model from AWS training, but I have not integrated S3 or Swift in a project.

COVERAGE SUMMARY

- Review catalogue across the original and revised request: 27 items, including overlapping requirements; the totals below are not a current-role fit percentage.
- COVERED: 4 — items 7, 8, 10 and 19.
- PARTIALLY COVERED: 11 — items 3, 9, 11, 14, 15, 17, 20, 22, 23, 25 and 26.
- NOT COVERED: 12 — items 1, 2, 4, 5, 6, 12, 13, 16, 18, 21, 24 and 27.
- Revised must-haves: one covered, two partially covered, two not covered; both uncovered items, Ceph or NetApp and Kubernetes, define the role.

The current technical-profile assessment is based primarily on items 9 to 13: breadth across technical areas is PARTIALLY COVERED; C++ development is COVERED; infrastructure experience is PARTIALLY COVERED; Ceph or NetApp with some Ceph experience is NOT COVERED; Kubernetes is NOT COVERED. Seniority, English and EU location, CET hours and capacity remain separate vacancy constraints assessed in items 14, 22 and 23, all PARTIALLY COVERED. The original specialist criteria explain possible technical interview topics, but their continued use as selection requirements is not established.

RELEVANT STRENGTHS

1. Production C and C++ on Linux: two years as a C89 backend developer on Sierra with gdb, core dumps and Valgrind on AWS EC2 Linux hosts, plus C++17 on two later systems.
2. Cross-layer diagnosis: tracing failures across Scala, Java and C services and across application, SDK, provisioning, firmware and hardware on the SIP platform.
3. Work inside a customized open-source codebase: SDK-side registration watchdog and primary/backup failover and failback in a customized Linphone SDK, integrated through the application and provisioning paths.
4. Linux system integration: Yocto Kirkstone images, BitBake recipes, systemd services and ARM64 target debugging.
5. Delivery discipline: Agile process, multi-reviewer code review, safe change in inherited code and People Lead responsibilities.

MATERIAL GAPS

1. No Ceph experience in any component, including RGW, RADOS, RBD and CephFS.
2. No NetApp experience.
3. No Kubernetes, Rook or Ceph CSI experience.
4. No Prometheus, Grafana or metrics-based observability experience.
5. No OpenStack experience.
6. No production Python.
7. No storage performance tuning, benchmarking or S3 and Swift integration.
8. No upstream open-source contribution.
9. Formal grade is middle, not senior.

KEY RISKS AND NON-CLAIMS

1. Do not claim deployment, operation, tuning or performance investigation of Ceph; the CV Remote Sensing Satellites Database project is not supported in that form.
2. Do not claim Rook, Ceph CSI, RBD provisioning or Kubernetes operation.
3. Do not claim Prometheus or Grafana monitoring.
4. Do not claim S3 API integration, pre-signed URLs or byte-range object transfers.
5. Do not claim production Python or pytest-based storage validation.
6. Do not claim LevelDB integration or tuning.
7. Do not present Valgrind or gdb use as performance profiling or storage benchmarking.
8. Do not present the customized Linphone SDK fork as upstream open-source contribution.
9. The CV places real projects in different years from the verified record, for example the library system in 2015–2017 instead of 2022–2024 and the oil-and-gas system in 2012–2014 instead of 2021–2022. A public LinkedIn profile and a background check can expose this; the candidate should not be asked to defend dates that contradict his employment record.
10. A storage-team technical interview is likely to ask about OSDs, placement groups, CRUSH, BlueStore, replication versus erasure coding and RBD or RGW internals early; claiming the CV's Ceph project would fail at that point and damage credibility for the rest of the interview.

INTERVIEW POSITIONING

Position the candidate as a C and C++ systems engineer on Linux with strong production diagnosis skills, experience changing large inherited codebases including a customized open-source SDK, and Linux system-integration work with Yocto and systemd. State openly that Ceph, NetApp and Kubernetes would be new hands-on areas, and show readiness with accurate theory of Ceph architecture and Kubernetes storage rather than with claimed experience. The revised request's emphasis on a very strong, versatile developer is the only angle under which this profile is competitive, so the strongest stories are cross-layer diagnosis on Sierra and the SDK-level failover work on the SIP platform.

PREPARATION PRIORITIES

1. Ceph architecture: MON, MGR, OSD, MDS, RADOS, CRUSH, placement groups, replication and erasure coding, BlueStore, RBD, RGW and CephFS; a preparation priority because some Ceph experience remains in the revised profile, with no established interview question order.
2. Kubernetes storage: PersistentVolumes, PersistentVolumeClaims, StorageClasses, CSI architecture, Rook operator model and failure modes.
3. Linux I/O and memory: page cache, direct I/O, fsync semantics, block layer, epoll, threads and synchronization, memory allocation and fragmentation.
4. OpenStack storage services: Cinder, Glance, Manila, Swift and their usual Ceph back ends.
5. Observability: Prometheus data model, exporters, PromQL basics, Grafana dashboards and the Ceph MGR Prometheus module.
6. Object storage semantics: S3 and Swift APIs, consistency, multipart uploads, pre-signed URLs.
7. Two prepared stories: cross-service C diagnosis on Sierra and SDK-side primary/backup failover on the SIP platform.
8. Python basics for automation, so that a short scripting question does not become a blocker.

FINAL ASSESSMENT

The candidate is a credible C and C++ Linux engineer with strong diagnosis skills and a broad background, but the request's defining capabilities, Ceph or NetApp storage and Kubernetes, are not supported by his real experience, and the CV project that claims them does not exist in that form. Under the original Ceph Developer request the fit is weak. Under the revised request the fit becomes weak to partial and depends on whether the client accepts a strong systems developer who will learn Ceph and Kubernetes on the job. Submission is advisable only after the intermediary confirms that condition, the request is still open after its July deadline and the EU-location requirement is met through work from Poland.
