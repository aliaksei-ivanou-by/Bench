REQUEST AND CUSTOMER ANALYSIS

DOCUMENT INFORMATION

Request ID: E468
Internal request reference: R-22530
Candidate: Aliaksei Ivanou
Target role: Senior C++ Developer
CV source: E468 Aliaksei Ivanou (13, C++).pdf
Request document: E468_Request_AliakseiIvanou.md
Profile source: E468_Profile_AliakseiIvanou.md
Research date: 2026-09-22
Analysis status: Rebuilt against the submitted CV and the request

SOURCES OF TRUTH

This analysis is built from two sources only:

1. E468_Request_AliakseiIvanou.md, the normalized request.
2. The submitted CV, E468 Aliaksei Ivanou (13, C++).pdf.

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

Overall fit against the submitted CV: PARTIAL
Recommendation: QUALIFY THE SCREENING GATES BEFORE SUBMISSION

Read against the request, the submitted CV is strong on exactly four must-haves: seniority as presented, CMake, debugging, and a structured engineering narrative. It is adequate on modern C++ and on desktop development. It is silent on three must-haves that sit at the centre of the role: in-depth IT security, multithreading, and highly parallel or performance-sensitive desktop delivery. Not one of those three words appears anywhere in the CV, including the skills matrix.

Two further must-haves are present as matrix entries rather than as demonstrated work: Conan appears with one year, and MSVC appears only indirectly through Visual Studio with five years and a last use of 2021, while the CV also shows Windows with one year and a last use of 2021.

The formal gates are the hardest part. The request asks for German at B2 or fluent and English at C1. The CV lists English B2, Polish B1, and Swedish A2, and no German at all. The request also asks that CV projects run for at least two years; six of the eight projects in the submitted CV are shorter than that.

The honest positioning is a strong C++ systems and legacy-modernization engineer with excellent debugging and build experience, submitted against a security-focused Windows desktop role whose security, parallelism, and language gates the CV does not currently answer.

REQUEST FACTS

Role: Senior C++ Developer
Seniority: Senior
Industry: Information Technologies
Named requester: Deloitte
Request source or intermediary: YER Experts GmbH
Requested headcount: 16 consultants
Start: ASAP
Stated assignment duration: Four to five months; a separate request field says three to six months
Capacity: Full-time
Working time: CET
Project language: English
Language requirement: English C1 or fluent, German B2 or fluent
Submission deadline in the source: 2026-09-04
Deadline status at research date: Passed; current availability of the request must be reconfirmed
CV instruction: Projects in the submitted CV should be at least two years long

SUBMITTED CV AS PRESENTED

Name as printed: Aliaksei Ivanou
Headline: Software Engineer
Opening statement: Senior software engineer with 14+ years of commercial experience
Languages: English B2, Polish B1, Swedish A2
Domains: Telecommunications, Library Systems, Oil and Gas Industry, UAV Systems, Aerospace Systems

Projects, in CV order, with the periods and role labels the CV prints:

1. SIP Desk Phone Platform for Audio and Video Communication, 05.2025 – till now, Senior Software Engineer, 16 months
2. Library System, 03.2022 – 04.2025, Senior Software Engineer, 37 months
3. Corporate System for the Oil and Gas Industry, 10.2021 – 12.2021, Software Engineer, 2 months
4. Home Accounting Software, 07.2020 – 07.2021, Software Engineer, 12 months
5. 3D Reconstruction Software for Industrial Applications, 03.2020 – 05.2020, Software Engineer, 2 months
6. Software Modules for UAV, 08.2018 – 12.2019, Software Engineer, 16 months
7. Remote Sensing Satellites Database, 03.2016 – 03.2017, Software Engineer, 12 months
8. Software for Processing and Analysis of Satellite Earth Observation Images, 08.2012 – 03.2016, Software Engineer, 43 months

Skills-matrix entries that the request depends on:

C++ 6 years, last used 2026
C 3 years, last used 2025
C# 1 year, last used 2026
CMake 6 years, last used 2026
Conan 1 year, last used 2026
GDB 4 years, last used 2026
Valgrind 1 year, last used 2026
Qt Test 1 year, last used 2026
Visual Studio 5 years, last used 2021
ReSharper C++ 1 year, last used 2021
Windows 1 year, last used 2021
Embedded Linux 1 year, last used 2026
Qt, Qt Widgets, QSS, Qt Designer, Qt Creator, Qt Model/View, each 1 year, last used 2026

Terms the request uses that do not appear anywhere in the submitted CV: security, vulnerability, CVE, threading, multithreading, concurrency, parallel, performance optimization as a named skill, MSVC, C++14, C++20, BSI, IT-Grundschutz, AI coding agent, German.

CUSTOMER CHAIN

Request source or staffing intermediary: YER Experts GmbH
Named customer or requester: Deloitte
Final client or product owner: Not disclosed
Product: A C++ desktop application with a security and stability focus; no product name, architecture, business domain, or end user is disclosed

The request says it comes from Deloitte. It does not establish whether Deloitte owns the product, delivers a work package for another organization, or is assembling consultants for an undisclosed end client. Any statement beyond that would be inference.

CUSTOMER AND DOMAIN RESEARCH

Research item 1
Verified public fact: YER Germany describes itself as a personnel and recruiting provider for specialized roles and projects in IT, engineering, technology, energy, mobility, and other sectors. It offers permanent placement, temporary staffing, freelance placement, and contract models.
Interview implication: Expect at least two audiences. An intermediary will screen the CV for explicit keywords, and a delivery or technical interview will look for evidence. With sixteen consultants requested, the first pass is likely to be mechanical, which makes the missing security, multithreading, and German keywords in the CV a real filter risk.
Source: https://www.yer.de/de/

Research item 2
Verified public fact: Deloitte Germany describes Enterprise Security as covering technical cybersecurity across classic IT, OT, edge, and cloud, including security architecture and application security across the lifecycle.
Interview implication: The role may value evidence that connects code-level fixes to repeatable engineering controls, documentation, quality assurance, and architecture rather than treating security as a one-off bug fix. The exact Deloitte offering and end client are not confirmed.
Source: https://www.deloitte.com/de/de/services/consulting/services/cyber.html

Research item 3
Verified public fact: BSI Standard 200-1 describes an information-security management system. BSI Standard 200-2 defines the IT-Grundschutz methodology, and BSI Standard 200-3 addresses risk analysis based on IT-Grundschutz.
Interview implication: If BSI is discussed, separate organizational security management and risk treatment from low-level C++ secure coding. Framework knowledge must not be presented as implementation experience, and the CV offers no baseline to build such a claim on.
Sources:
https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Grundschutz/International/bsi-standard-2001_en_pdf.pdf?__blob=publicationFile&v=2
https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Grundschutz/International/bsi-standard-2002_en_pdf.pdf?__blob=publicationFile&v=2

Research item 4
Verified public fact: Anthropic documents Claude Code as an agentic development tool that can inspect a project, edit files, execute commands, and use configurable permission controls. Anthropic advises reviewing proposed code and commands and using controlled permissions for sensitive repositories.
Interview implication: A credible answer describes a governed workflow: constrain scope, protect secrets, inspect the plan and the diff, run tests and static analysis, and keep human ownership of the result. This is preparation knowledge. The CV contains no AI-agent entry.
Sources:
https://docs.anthropic.com/en/docs/claude-code/getting-started
https://docs.anthropic.com/en/docs/claude-code/security

Research item 5
Verified public fact: Conan 2 supports CMake through generated dependency configuration and toolchain files. The documented normal flow runs conan install before the CMake configure and build steps.
Interview implication: The CV shows Conan with one year and a 2026 last use, so the interviewer is entitled to ask a working question. The profile, toolchain, CMakeDeps, CMakeToolchain, and lockfile workflow must be prepared well enough to answer without inventing project history.
Source: https://docs.conan.io/2/integrations/cmake.html

ROLE OUTCOME

Success most likely means becoming productive quickly in an existing Windows-oriented C++ product, reproducing security and stability defects, locating the responsible code path, implementing controlled fixes, and validating them with quality assurance and architecture stakeholders. Because sixteen consultants are requested, a standardized environment, parallel workstreams, and consistent delivery practices are plausible, but that is inference rather than a confirmed fact.

MUST-HAVE REQUIREMENT MAPPING

Requirement 1: Several years of experience as a Senior C++ Developer
Request wording: Several years as a Senior C++ Developer
CV evidence: The CV headline says senior software engineer with 14+ years of commercial experience. The CV prints the role label Senior Software Engineer on the two most recent projects, which run from 03.2022 to the present, that is four and a half years. C++ is shown with six years and a 2026 last use.
Match: COVERED BY CV
Interview risk: The CV asserts fourteen-plus years of commercial experience while the same CV gives C++ six years. Expect the question of what the other eight years were. Answer with the career shape the CV itself shows: algorithm and research work in MATLAB in the satellite and UAV period, then C and C++ delivery.
Safe interview wording: I have been working at senior scope on C++ products since 2022. My overall engineering and research career runs from 2012, and my C++ depth is the six years shown in my skills summary.

Requirement 2: Strong modern C++ covering C++14, C++17 and C++20
Request wording: C++14, C++17 and C++20
CV evidence: C++17 is named in two project environments, the SIP desk phone platform and the oil and gas corporate system. The other native projects list C++ without a standard version. C++14 and C++20 do not appear anywhere in the CV.
Match: PARTIAL
Interview risk: Two of the three requested standards are not evidenced by the document the customer is reading. A question about C++20 features has no anchor in the CV.
Safe interview wording: The standard named in my CV is C++17, which I used on the embedded phone platform and the oil and gas system. I work with modern ownership, explicit lifetimes, standard-library facilities and incremental modernization of inherited code, and I can discuss where C++20 facilities would change those choices.

Requirement 3: Desktop application development, ideally highly parallel or performance-sensitive
Request wording: Desktop application development; highly parallel or performance-sensitive applications preferred
CV evidence: Four desktop-shaped deliverables are present: the native phone application with Qt Widgets, a WinForms configuration utility migrated to .NET 8, a home accounting application built with FLTK and SQLite, and a 3D reconstruction application built in Visual Studio. Windows appears in the matrix with one year and a last use of 2021.
Match: PARTIAL FOR DESKTOP, NOT IN CV FOR HIGHLY PARALLEL
Interview risk: The CV contains no statement about parallelism, throughput, latency or profiling, and no threading technology in the matrix. The desktop work it does show is either embedded Linux with Qt or short older Windows projects.
Safe interview wording: My recent desktop work is a Qt Widgets application on embedded Linux plus a Windows .NET provisioning tool. I would not describe my background as years of highly parallel Windows desktop development, and I would rather show how I reason about state and lifetime in an event-driven application.

Requirement 4: In-depth IT-security experience
Request wording: In-depth IT-security experience; identify, investigate and remediate vulnerabilities
CV evidence: None. The submitted CV contains no security responsibility, no vulnerability or CVE wording, no security tooling, and no security entry in the skills matrix.
Match: NOT IN CV
Interview risk: This is the central theme of the request and the largest single gap. Anything said here will be heard as new information that the CV did not support.
Safe interview wording: My CV does not present a security role, and I will not claim one. My relevant experience is security-aware product engineering in a networked device: authentication and credential handling, encrypted transport and certificate settings, provisioning trust boundaries, and safe maintenance of mature native code. I would be joining a vulnerability-remediation programme rather than bringing one.

Requirement 5: Strong multithreading knowledge
Request wording: Strong multithreading knowledge
CV evidence: None as printed. The CV describes call-state handling, media negotiation and SDK integration on the phone platform, but no threading, concurrency, synchronization or asynchronous execution wording, and no threading technology in the matrix.
Match: NOT IN CV
Interview risk: A senior C++ interview will go here early. The CV gives the interviewer nothing to open with, so the whole answer has to be carried live.
Safe interview wording: The concurrency in my recent product was event-driven: asynchronous SDK callbacks, cross-thread signal delivery, object ownership and lifetime across threads, cancellation and clean shutdown. That is different from high-throughput data-parallel or lock-free work, and I would keep that distinction explicit.

Requirement 6: Strong debugging ability
Request wording: Strong debugging
CV evidence: GDB with four years and a 2026 last use, Valgrind, gdb inside three project environments, Qt Test, and repeated CV wording about resolving complex bugs, tracing defects and investigating legacy behaviour across C, Java, Scala and database layers.
Match: COVERED BY CV
Interview risk: None material. Windows crash-dump and WinDbg work is not shown, which matters because the target product is Windows-oriented.
Safe interview wording: I start from reproduction and evidence, isolate the failing boundary, then use logs, source-level debugging and targeted tests to confirm the root cause and the fix. My debugging is strongest on Linux and embedded targets.

Requirement 7: Practical CMake knowledge
Request wording: CMake
CV evidence: CMake with six years and a 2026 last use, and CMake inside four project environments.
Match: COVERED BY CV
Interview risk: None. This is the cleanest formal match in the package.
Safe interview wording: I have used CMake across native C++ applications and libraries and in mixed build environments where qmake or Yocto orchestrated the final product.

Requirement 8: Practical Conan knowledge
Request wording: Conan
CV evidence: Conan appears in the skills matrix with one year and a 2026 last use, and in the environment of the SIP desk phone platform.
Match: PRESENT IN CV AS A ONE-YEAR ENTRY
Interview risk: HIGH. The CV puts Conan on the table, so the interviewer may ask a working question, and the detailed project record behind this CV does not support hands-on Conan use. The dependency mechanisms actually described in the same CV are Yocto and BitBake on the embedded side and CMake elsewhere.
Safe interview wording: Conan appears in my skills summary as part of the project environment rather than as an area I owned. The dependency reproducibility I personally worked with came from Yocto and BitBake on the device side and from CMake on the native applications. I have prepared the Conan 2 flow, and I would rather be precise about that than overstate the entry.

Requirement 9: Practical MSVC knowledge
Request wording: MSVC
CV evidence: MSVC is not named. Visual Studio appears with five years and a last use of 2021, ReSharper C++ with one year and a last use of 2021, and Windows with one year and a last use of 2021. Visual Studio is the environment of the home accounting and 3D reconstruction projects.
Match: PARTIAL
Interview risk: The CV shows the IDE, not the compiler toolset, and dates the Windows-native work at 2021 or earlier. Against a current Windows desktop product this reads as lapsed rather than current.
Safe interview wording: I used Visual Studio for Windows-native C++ development and debugging, most recently on the industrial 3D work and my desktop application. I would confirm the exact toolset in your project rather than claim MSVC-version-specific experience.

Requirement 10: Structured and analytical problem solving with a strong quality focus
Request wording: Structured, analytical approach and high quality standard
CV evidence: Repeated CV responsibilities for task estimation, thorough code review within the delivery and client teams, controlled refactoring of legacy code, removal of obsolete components, and incremental hardening of call flows.
Match: COVERED BY CV
Interview risk: Avoid invented metrics. The CV contains no quality numbers.
Safe interview wording: I make a change traceable from symptom to root cause to validation, and in inherited systems I prefer small reversible changes with focused tests and review.

NICE-TO-HAVE REQUIREMENT MAPPING

Requirement 1: Claude Code or comparable AI coding-agent experience
CV evidence: None.
Match: NOT IN CV
Safe interview wording: I can describe how I would use an agent under restricted repository permissions, protected secrets, explicit task scope, diff review, tests and static analysis, with human ownership of the result. I would not present that as prior delivery.

Requirement 2: BSI IT-Grundschutz or a comparable information-security framework
CV evidence: None.
Match: NOT IN CV
Safe interview wording: I am familiarising myself with the 200-series structure and can connect it to risk and control discussions. I have not implemented an IT-Grundschutz programme.

Requirement 3: Regulated environments or healthcare
CV evidence: None. The CV domain line lists Telecommunications, Library Systems, Oil and Gas Industry, UAV Systems and Aerospace Systems.
Match: NOT IN CV
Safe interview wording: My delivered domains are the ones in my CV. I have not worked inside a regulated quality system.

Requirement 4: A technical degree
CV evidence: Computer Science and Software Engineering.
Match: COVERED BY CV

REQUIREMENTS THE CV DOES NOT ADDRESS

These are the request items with no anchor at all in the submitted document. They are the list the recruiter should be qualified against before the candidate invests preparation time.

1. In-depth IT security and vulnerability remediation.
2. Multithreading.
3. Highly parallel or performance-sensitive desktop delivery.
4. C++14 and C++20 as named standards.
5. MSVC as a named toolset.
6. German at any level.
7. Claude Code or a comparable AI coding agent.
8. BSI IT-Grundschutz.
9. Regulated or healthcare domain.

FORMAL SCREENING RISKS

1. German. The request asks for B2 or fluent German. The CV lists English B2, Polish B1 and Swedish A2, and no German. This is the hardest gate and it is visible on page one of the CV.
2. English. The request asks for C1. The CV states B2.
3. Project duration. The request asks for CV projects of at least two years. In the submitted CV only two of eight projects reach twenty-four months: the library system at thirty-seven months and the satellite imaging work at forty-three months. The remaining six run sixteen, two, twelve, two, sixteen and twelve months. If the intermediary applies this rule mechanically the CV fails the format check before the content is read.
4. Timeline breaks. The CV shows a gap between 03.2017 and 08.2018, and shorter breaks in 2019, 2020, 2021 and 2022. Prepare the explanation that the CV lists selected projects rather than continuous employment.
5. Deadline. The stated submission deadline of 2026-09-04 has passed and availability must be reconfirmed.
6. Volume. Sixteen consultants implies keyword-level pre-screening, which amplifies risks one to three.

CV CLAIMS THAT CREATE INTERVIEW RISK

These are printed in the submitted CV, so they cannot be withdrawn, but the depth behind them will not survive detailed questioning. Each one needs the boundary formulation from the profile and responsibilities documents.

1. Conan in the matrix and in the phone-platform environment.
2. GStreamer and V4L2 in the matrix and in the phone-platform environment.
3. ReSharper C++ in the matrix and in the oil and gas environment.
4. Refactored existing Scala API code to improve maintainability and scalability.
5. Worked with AWS pipelines, automating CI/CD processes.
6. Led development efforts as a key contributor in C language.
7. Developed new backend and frontend features for socket-based communication.
8. Modified database tables and improved schema design.
9. The Senior Software Engineer label on the library system project.
10. Fourteen-plus years of commercial experience in the opening line.

INTERVIEW POSITIONING

Lead with what the CV itself supports:

• C++17 and Qt work on a stateful embedded product, and C89 delivery in a mature multi-language platform.
• Cross-layer debugging from visible behaviour through SDK, configuration, services, firmware and hardware, backed by the GDB, Valgrind and gdb entries in the CV.
• CMake across six years and four projects.
• Safe refactoring and stabilization of inherited code, with estimation and cross-company code review.
• Desktop delivery in three different stacks: Qt Widgets, WinForms with .NET 8, and FLTK.

Do not claim:

• A security role, vulnerability-remediation ownership, BSI implementation or penetration testing.
• Years of highly parallel or performance-critical desktop development.
• Conan project ownership, GStreamer pipelines, direct V4L2 programming.
• German proficiency, or English above the documented B2.
• Production use of an AI coding agent.
• Fourteen years of commercial C++ development.

LIKELY INTERVIEW QUESTIONS

1. Your CV says fourteen-plus years but six years of C++. What were the other years?
Answer direction: Use the CV itself. The satellite and UAV period was algorithm research and development, mainly in MATLAB. Commercial C and C++ delivery starts with the 2020 and 2021 projects and continues through the library system and the phone platform.

2. What security work have you personally done?
Answer direction: State plainly that the CV does not present a security role. Then give the concrete security-adjacent surfaces from the same CV: SIP authentication and provisioning, encrypted transport and certificate settings, device configuration trust boundaries, and safe maintenance of mature native code.

3. How have you handled multithreading?
Answer direction: Event-driven concurrency: asynchronous SDK callbacks, cross-thread signal delivery, object ownership and lifetime, cancellation, shutdown, and keeping the UI thread free. Separate this explicitly from data-parallel and lock-free work.

4. Describe a difficult C++ stability problem.
Answer direction: Use asynchronous call or registration state from the phone platform. Reproduction, state-boundary diagnosis, ordering and lifetime reasoning, incremental fix, validation on the device.

5. What is your Conan experience?
Answer direction: Name the boundary first, then compare with the Yocto, BitBake and CMake dependency work the same CV shows, then describe the prepared Conan 2 flow.

6. How current is your Windows and MSVC work?
Answer direction: Be accurate about the CV dates. Visual Studio and Windows are shown at 2021 and earlier; the recent native work is Qt on embedded Linux and C# on Windows.

7. How would you investigate a suspected vulnerability in legacy C++?
Answer direction: Reproduce safely, define the trust boundary, inspect input and ownership paths, use compiler warnings and sanitizers where available, build a minimal test, fix the root cause, assess compatibility, and document residual risk.

QUESTIONS TO ASK THE CUSTOMER

1. Is Deloitte the product owner, the delivery organization, or an intermediary for another end client?
2. What is the application domain, and why is it considered security-sensitive?
3. Which Windows versions, MSVC toolset, CMake version and Conan major version are used?
4. What kind of parallelism is central: user interface and background tasks, multithreaded services, CPU data parallelism, or low-latency processing?
5. Which security requirements are mandatory: BSI IT-Grundschutz, ISO 27001, secure-coding rules, static analysis, software bill of materials, or a vulnerability-management process?
6. Is German genuinely required for daily work, or preferred for some stakeholders only?
7. What does the sixteen-consultant structure look like: one team, several workstreams, or separate product modules?
8. What is the expected balance between feature development, vulnerability remediation, test automation and documentation?
9. How may AI coding agents access source code, and what review, logging, data-residency and approval controls apply?
10. Is the two-year project-duration instruction a hard formatting rule for the submission?
11. Is the request still open after the stated submission deadline?

PREPARATION PRIORITIES

1. Resolve the German and English gates with the recruiter before investing further. They are visible on the first page of the CV and they are binary.
2. Confirm whether the two-year project rule is enforced, because six of the eight submitted projects do not meet it.
3. Build one honest security answer: trust boundaries, input validation, memory safety, dependency risk, tests, review and residual-risk documentation, with an explicit statement that this is engineering practice and not a security-role history.
4. Build one concurrency answer from the phone platform: callback ordering, cross-thread delivery, ownership, cancellation, shutdown. Rehearse the boundary against data-parallel work.
5. Complete a small Conan 2 and CMake exercise covering profiles, CMakeToolchain, CMakeDeps, lockfiles, Debug and Release, and MSVC on Windows, so the one-year matrix entry can be answered without inventing history.
6. Refresh MSVC diagnostics, warning levels, AddressSanitizer availability, crash dumps and common undefined-behaviour patterns.
7. Learn the purpose and relationship of BSI Standards 200-1, 200-2 and 200-3 without claiming implementation experience.
8. Prepare a governed AI-agent workflow and keep prepared knowledge separate from prior use.

PUBLIC SOURCES

1. YER Germany
https://www.yer.de/de/

2. Deloitte Germany Cyber
https://www.deloitte.com/de/de/services/consulting/services/cyber.html

3. BSI Standard 200-1
https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Grundschutz/International/bsi-standard-2001_en_pdf.pdf?__blob=publicationFile&v=2

4. BSI Standard 200-2
https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Grundschutz/International/bsi-standard-2002_en_pdf.pdf?__blob=publicationFile&v=2

5. Anthropic Claude Code setup
https://docs.anthropic.com/en/docs/claude-code/getting-started

6. Anthropic Claude Code security
https://docs.anthropic.com/en/docs/claude-code/security

7. Conan 2 CMake integration
https://docs.conan.io/2/integrations/cmake.html

FINAL DECISION NOTES

Submit only after the recruiter confirms that German, English C1, in-depth IT security, multithreading depth and the two-year project rule are not automatic rejection criteria. If all ten must-haves are applied strictly against the submitted CV, this request is a weak fit despite a genuinely strong C++, debugging and build-systems foundation.
