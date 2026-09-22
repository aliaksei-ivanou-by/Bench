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
Analysis status: Reviewed

EVIDENCE RULES

VERIFIED REQUEST FACT means the information is recorded in the reviewed and normalized Request document.
VERIFIED PUBLIC FACT means the information is supported by an official public source listed below.
CONFIRMED CANDIDATE EVIDENCE means the information is supported by the verified career repository.
INFERENCE means a useful interpretation that has not been confirmed by the customer.
OPEN QUESTION means information that must be obtained from the recruiter or customer.
GAP means a requested capability that is not supported by verified candidate evidence.

EXECUTIVE ASSESSMENT

Overall fit: PARTIAL
Recommendation: QUALIFY BEFORE SUBMISSION

The candidate has credible modern C++, Qt, embedded systems, concurrency-adjacent asynchronous work, CMake, debugging, Visual Studio, and mature-codebase experience. The strongest match is engineering and stabilizing stateful C++ systems under real product constraints. The largest hard gaps are German, Conan, direct Claude Code experience, deep IT-security ownership, and proven delivery of highly parallel Windows desktop applications. English is also stated as B2 in the CV while the request asks for C1 or fluent English.

This should not be positioned as a clean senior security-desktop match. It can be positioned as a strong C++ systems engineer with security-aware product work and excellent cross-layer debugging, provided the customer accepts adjacent rather than direct experience in several must-have areas.

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
Location: Remote, hybrid, or on-site in Hanover; on-site presence is nice to have
Working time: CET
Location restriction: EU only, with VPN-based remote access allowed
Project language: English
Language requirement: English C1 or fluent English and German B2 or fluent German
Submission deadline in the source: 2026-09-04
Deadline status at research date: Passed; current availability of the request must be reconfirmed
CV instruction: Projects in the submitted CV should be at least two years long

The two-year CV instruction is a presentation request, not permission to alter project dates. The verified dates must remain the source of truth in interview preparation.

CUSTOMER CHAIN

Request source or staffing intermediary: YER Experts GmbH
Named customer or requester: Deloitte
Final client or product owner: Not disclosed
Product: A C++ desktop application with a security and stability focus; no product name, architecture, business domain, or end user is disclosed

The request says it comes from Deloitte. It does not establish whether Deloitte owns the product, delivers a work package for another organization, or is assembling consultants for an undisclosed end client. Any statement beyond that would be inference.

CUSTOMER AND DOMAIN RESEARCH

Research item 1
Verified public fact: YER Germany describes itself as a personnel and recruiting provider for specialized roles and projects in IT, engineering, technology, energy, mobility, and other sectors. It offers permanent placement, temporary staffing, freelance placement, and contract models.
Interview implication: Expect at least two audiences: an intermediary screening for explicit keywords and a delivery or technical interview focused on evidence. Availability, location, language, rate, and exact tool matches may be checked before project depth.
Source: https://www.yer.de/de/

Research item 2
Verified public fact: Deloitte Germany describes Enterprise Security as covering technical cybersecurity across classic IT, OT, edge, and cloud, including security architecture and application security across the lifecycle.
Interview implication: The role may value evidence that connects code-level fixes with repeatable engineering controls, documentation, QA, and architecture rather than treating security as a one-off bug fix. The exact Deloitte offering and end client are not confirmed.
Source: https://www.deloitte.com/de/de/services/consulting/services/cyber.html

Research item 3
Verified public fact: BSI Standard 200-1 describes an information-security management system. BSI Standard 200-2 defines the IT-Grundschutz methodology, while BSI Standard 200-3 addresses risk analysis based on IT-Grundschutz.
Interview implication: If BSI is discussed, distinguish organizational security management and risk treatment from low-level C++ secure coding. Knowledge of the framework must not be presented as implementation experience.
Sources:
https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Grundschutz/International/bsi-standard-2001_en_pdf.pdf?__blob=publicationFile&v=2
https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Grundschutz/International/bsi-standard-2002_en_pdf.pdf?__blob=publicationFile&v=2

Research item 4
Verified public fact: Anthropic documents Claude Code as an agentic development tool that can inspect a project, edit files, execute commands, and use configurable permission controls. Anthropic advises users to review proposed code and commands and to use controlled permissions for sensitive repositories.
Interview implication: A credible answer should describe a governed workflow: constrain scope, protect secrets, inspect the plan and diff, run tests and static analysis, and keep human ownership of the result. This is preparation knowledge, not evidence of project use.
Sources:
https://docs.anthropic.com/en/docs/claude-code/getting-started
https://docs.anthropic.com/en/docs/claude-code/security

Research item 5
Verified public fact: Conan 2 supports CMake through generated dependency configuration and toolchain files. Its documented normal flow uses conan install before CMake configure and build.
Interview implication: The candidate should learn the Conan 2 profile, recipe, lockfile, CMakeDeps, and CMakeToolchain workflow before an interview, while clearly stating that prior projects used other dependency mechanisms.
Source: https://docs.conan.io/2/integrations/cmake.html

ROLE OUTCOME

Success probably means becoming productive quickly in an existing Windows-oriented C++ product, reproducing security and stability defects, finding the responsible code path, implementing controlled fixes, and validating them with QA and architecture stakeholders. Because 16 consultants are requested, a standardized environment, parallel workstreams, and consistent delivery practices are plausible, but this is an inference rather than a confirmed fact.

MUST-HAVE REQUIREMENT MAPPING

Requirement 1: Several years as a Senior C++ Developer, ideally in high-performance and highly parallel desktop applications
Priority: MUST-HAVE
Candidate evidence: Recent C++17 and Qt work in a stateful embedded application, C++20 in an independent desktop application, native C++ in an industrial Windows prototype, and mature C89 delivery. The recent project included asynchronous SDK callbacks, queued signal delivery across thread boundaries, background operations, and explicit QObject ownership and teardown.
Match: PARTIAL
Boundary or risk: The verified career record does not support fourteen years of commercial C++ or senior-level ownership throughout. The strongest recent product was embedded Qt, not a highly parallel Windows desktop application.
Safe interview wording: My recent work is modern C++ in a complex event-driven Qt product with asynchronous SDK callbacks, thread boundaries, background operations, and difficult lifetime and state-management problems. I have Windows desktop and Visual Studio experience as well, but I would not describe my background as years of highly parallel Windows desktop development.

Requirement 2: Modern C++14, C++17, and C++20
Priority: MUST-HAVE
Candidate evidence: C++17 in the embedded SIP and oil-and-gas projects and C++20 in the independent personal-finance application.
Match: STRONG
Boundary or risk: Use concrete language and library features actually applied. Do not claim equal production depth in every standard version.
Safe interview wording: I used C++17 in commercial Qt and enterprise projects and C++20 in my independent application. My focus is modern ownership, explicit lifetimes, standard-library use, testability, and incremental modernization of inherited code.

Requirement 3: In-depth IT-security experience
Priority: MUST-HAVE
Candidate evidence: Security-sensitive SIP authentication and provisioning behavior, TLS and SRTP integration boundaries, certificate-related application settings, authentication realm and HA1 handling, analysis of weaknesses in encrypted project storage, and safe maintenance of networked software.
Match: PARTIAL
Boundary or risk: No verified ownership of a product security program, penetration testing, threat-model process, BSI implementation, or CVE-remediation campaign. CVE backporting must not be introduced from another CV because it is not supported by the verified career record.
Safe interview wording: My experience is security-aware product engineering rather than a dedicated security-engineer role. I worked with authentication, encrypted transport, certificate and provisioning paths, identified security boundaries in legacy mechanisms, and validated changes across the product stack.

Requirement 4: Multithreading
Priority: MUST-HAVE
Candidate evidence: queued connections across thread boundaries, asynchronous Linphone callbacks, background discovery and provisioning operations, and explicit QObject ownership and teardown.
Match: PARTIAL TO STRONG
Boundary or risk: This is event-driven and task-oriented concurrency, not evidence of high-throughput parallel algorithms or lock-free programming at scale.
Safe interview wording: My strongest concurrency experience is in asynchronous Qt systems where callback ordering, cross-thread delivery, object lifetime, cancellation, and shutdown correctness matter. I would separate that from claims about large-scale data-parallel computation.

Requirement 5: Debugging
Priority: MUST-HAVE
Candidate evidence: gdb and gdbserver on ARM64 targets, Linux logs, core dumps, Valgrind, Qt remote debugging, Visual Studio, reproducible physical-device scenarios, and cross-component tracing in a mature C89 system.
Match: STRONG
Boundary or risk: Windows crash-dump and WinDbg depth is not established.
Safe interview wording: I normally begin with reproduction and evidence, identify the failing boundary, then use logs, source-level debugging, generated configuration, and targeted tests to confirm the root cause and the fix.

Requirement 6: CMake
Priority: MUST-HAVE
Candidate evidence: CMake in multiple C++ projects, including the independent C++20 application and native industrial work; additional embedded builds used qmake and Yocto or BitBake.
Match: STRONG
Boundary or risk: Do not imply that every recent target used CMake exclusively.
Safe interview wording: I have used CMake for native C++ applications and libraries, and I have also worked in mixed build environments where qmake or Yocto orchestrated the final product.

Requirement 7: Conan
Priority: MUST-HAVE
Candidate evidence: No verified project use. The independent project used pinned Git submodules and CMake FetchContent; embedded dependencies used Yocto and BitBake.
Match: GAP
Boundary or risk: Conan is listed in the CV but unsupported by the verified record.
Safe interview wording: I have not used Conan in a production project. I understand the problem it solves and I am preparing the Conan 2 and CMake workflow, but my actual dependency-management experience was with Yocto and BitBake or CMake-based submodules and FetchContent.

Requirement 8: MSVC
Priority: MUST-HAVE
Candidate evidence: Native C++ development and debugging in Visual Studio on Windows for the industrial reconstruction prototype, plus Windows C# and .NET work.
Match: PARTIAL
Boundary or risk: Visual Studio usage is confirmed; the exact compiler, toolset version, sanitizer use, and depth of MSVC-specific diagnostics should be verified before claiming them.
Safe interview wording: I used Visual Studio for Windows-native development and debugging. I would confirm the exact project toolset rather than invent MSVC-version-specific experience.

Requirement 9: Structured, analytical approach and high quality standard
Priority: MUST-HAVE
Candidate evidence: Incremental refactoring, explicit state boundaries, targeted automated tests, code review, repeatable reproduction, physical-device validation, and explicit ownership and evidence boundaries.
Match: STRONG
Boundary or risk: Avoid invented quality metrics.
Safe interview wording: I make changes traceable from symptom to root cause to validation, and I prefer small reversible changes with focused tests in inherited systems.

Requirement 10: Fluent English and German
Priority: MUST-HAVE
Candidate evidence: The CV states English B2, Polish B1, and Swedish A2. No German is listed.
Match: GAP
Boundary or risk: English C1 and German B2 or fluency are not supported by the supplied CV.
Safe interview wording: My documented English level is B2. I do not claim German proficiency.

NICE-TO-HAVE REQUIREMENT MAPPING

Requirement 1: Claude Code or comparable AI coding agents
Candidate evidence: No verified commercial project use is recorded.
Match: GAP
Boundary or risk: Familiarity developed during preparation must not be presented as delivery experience.
Safe interview wording: I can explain how I would use an agent under repository permissions, review, tests, static analysis, and human approval, but I do not claim prior production use unless separately verified.

Requirement 2: BSI IT-Grundschutz
Candidate evidence: No verified project implementation.
Match: GAP
Safe interview wording: I am familiarizing myself with the 200-series structure and can connect it to risk and control discussions, but I have not implemented an IT-Grundschutz program.

Requirement 3: Regulated or healthcare environment
Candidate evidence: No verified regulated production project. A short 2020 workstream explored a two-scanner setup for a possible medical application.
Match: ADJACENT
Boundary or risk: Exploratory technical work is not regulated medical-device delivery.
Safe interview wording: I had limited exploratory exposure to a medical scanning use case, but not to a medical quality system or regulated release process.

Requirement 4: Technical degree
Candidate evidence: A technical university degree in radiophysics and computer technologies, followed by software-engineering training and professional development.
Match: STRONG
Boundary or risk: Use the actual degree title rather than the simplified CV heading if asked for details.

KEY RISKS AND NON-CLAIMS

1. German is a direct screening gap.
2. The request asks for English C1 while the CV states B2.
3. Conan is unsupported as hands-on project experience.
4. Deep cybersecurity and BSI delivery ownership are not established.
5. Highly parallel Windows desktop development is only adjacent to the verified experience.
6. Claude Code experience is not established.
7. The exact MSVC depth requires confirmation.
8. The source submission deadline has passed.
9. The instruction to show projects of at least two years must not be used to change verified project dates.
10. Deloitte's position in the delivery chain and the final product owner remain unclear.

INTERVIEW POSITIONING

Lead with:

• C++17 and Qt work in a complex stateful product.
• Cross-layer debugging from visible behavior through SDK, configuration, services, firmware, and hardware.
• Safe refactoring and stabilization of inherited code.
• Asynchronous and threaded Qt behavior with explicit ownership and lifecycle control.
• CMake, Visual Studio, gdb, gdbserver, Valgrind, and test-driven validation where evidence exists.
• Security-aware work around authentication, encrypted transport, certificates, and provisioning boundaries.

Do not claim:

• German proficiency.
• English C1 when the documented level is B2.
• Conan project use.
• A dedicated cybersecurity role, BSI implementation, penetration testing, or CVE-remediation ownership.
• Years of highly parallel Windows desktop development.
• Production Claude Code use.
• Fourteen years of commercial C++ experience.

LIKELY INTERVIEW QUESTIONS

1. Describe a difficult C++ stability problem.
Answer direction: Use asynchronous SIP registration or call state, show reproduction, state-boundary diagnosis, lifetime or ordering reasoning, incremental fix, and device validation.

2. How have you handled multithreading?
Answer direction: Explain queued signal delivery across thread boundaries, worker and QObject ownership, cancellation, shutdown, and avoiding UI-thread blocking. Name a specific Qt threading class only if it matches the real implementation. State that this differs from data-parallel or lock-free systems.

3. What security work did you personally own?
Answer direction: Discuss authentication realm and HA1 handling, TLS and SRTP integration boundaries, certificate and provisioning paths, and security tradeoffs. Explicitly state that this was product engineering, not a formal security-program role.

4. How would you investigate a suspected vulnerability in legacy C++?
Answer direction: Reproduce safely, define the trust boundary, inspect input and ownership paths, use compiler warnings and sanitizers where available, create a minimal test, fix the root cause, assess compatibility, and document residual risk.

5. What is your Conan experience?
Answer direction: State the gap directly, then compare it with real Yocto and CMake dependency experience and explain the prepared Conan 2 workflow.

6. How would you use Claude Code in a security-sensitive repository?
Answer direction: Restricted permissions, no secrets, explicit task scope, inspect plan and diff, tests and static analysis, human review, and auditable commits.

QUESTIONS TO ASK THE CUSTOMER

1. Is Deloitte the product owner, the delivery organization, or an intermediary for another end client?
2. What is the application domain and why is it considered regulated or security-sensitive?
3. Which desktop framework, Windows versions, MSVC toolset, CMake version, and Conan major version are used?
4. What kind of parallelism is central: UI and background tasks, multithreaded services, CPU data parallelism, or low-latency processing?
5. Which security requirements and standards are mandatory: BSI IT-Grundschutz, IEC 62304, ISO 27001, secure coding rules, static analysis, SBOM, or vulnerability-management process?
6. Is German truly required for daily work or only preferred for some stakeholders?
7. What does the 16-consultant structure look like: one team, multiple workstreams, or separate product modules?
8. What is the expected balance between feature development, vulnerability remediation, test automation, and documentation?
9. How may AI coding agents access source code, and what review, logging, data-residency, and approval controls apply?
10. Is Hanover presence ever operationally required?

PREPARATION PRIORITIES

1. Rehearse two strong C++ debugging stories and one concurrency story using only confirmed details.
2. Complete a small Conan 2 and CMake exercise covering profiles, CMakeToolchain, CMakeDeps, lockfiles, Debug and Release, and MSVC on Windows.
3. Review MSVC diagnostics, warnings, AddressSanitizer support, crash dumps, and common undefined-behavior patterns.
4. Learn the purpose and relationship of BSI Standards 200-1, 200-2, and 200-3 without claiming implementation experience.
5. Prepare a security answer around trust boundaries, input validation, memory safety, dependency risk, tests, review, and residual-risk documentation.
6. Prepare a controlled AI-agent workflow and be ready to separate knowledge from actual prior use.
7. Resolve the German and English screening requirements before investing in a technical interview.

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

Proceed only after the recruiter confirms that German, English C1, Conan, and direct security depth are not automatic rejection criteria. If all listed must-haves are strict, this request is a weak fit despite the strong C++ and debugging foundation.
