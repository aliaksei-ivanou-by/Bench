# Bench Request Preparation

This repository stores one interview-preparation package per candidate CV. A role request may be supplied, but it is optional. Intro and Legend are built from the selected CV. Responsibilities compares that CV with the sibling `Summary` repository so the interview answer reflects the candidate's real, defensible scope.

Agent instructions and the complete authoring workflow are defined in `AGENTS.md`.

## Directory structure

Every package contains the CV, three bilingual artifact pairs and a bilingual `Tech` collection. A bilingual Request pair is added only when a request was supplied:

```text
<request-id>/
  <source-cv>.pdf
  <request-id>_Request_<CandidateName>.md       # only when a request exists
  <request-id>_Request_<CandidateName>_RU.md    # only when a request exists
  <request-id>_Intro_<CandidateName>.md
  <request-id>_Intro_<CandidateName>_RU.md
  <request-id>_Legend_<CandidateName>.md
  <request-id>_Legend_<CandidateName>_RU.md
  <request-id>_Responsibilities_<CandidateName>.md
  <request-id>_Responsibilities_<CandidateName>_RU.md
  Tech/
    _Index.md
    _Index_RU.md
    <Technology>.md
    <Technology>_RU.md
```

Profile and Request Analysis files may remain in older packages and may be created when explicitly requested, but they are not default artifacts in the current workflow. Reusable source files are in `Templates/`.

## Current request packages

| Request | Target role | Request source | Named customer / final client | Package status |
|---|---|---|---|---|
| `E468` | Senior C++ Developer | YER Experts GmbH | Deloitte is the named requester; final product owner is undisclosed | Full preparation package plus request and customer analysis |
| `E469` | Broadband Triage Engineer | 5V Video | Deutsche Telekom | Full preparation package plus request and customer analysis |
| `E474` | Senior Windows IoT Hardening Expert | Timspark | Final client is undisclosed | Full preparation package plus request and customer analysis |
| `E482` | Senior Embedded C++ and Real-Time Graphics Engineer | BrightBox Group | Acron Aviation, according to the supplied account context | Full preparation package; the Intro combines the BrightBox pre-screen and the Acron customer interview in one stage-tagged question set; unsupported graphics, personal RTOS-platform, bus, sensor-fusion, and formal-compliance claims are explicitly bounded |
| `E496` | GNC Engineer | Direct Samara Aerospace vacancy | Samara Aerospace | Full preparation package completed, including official customer research and requirement-to-evidence analysis; fit is weak for direct day-one GNC ownership and conditional for an adjacent aerospace algorithm and embedded C++ profile |
| `E506` | Senior C++ Engineer / Hands-on Technical Lead | Internal bench request supplied for InterVenture | InterVenture; the autonomous-driving product owner or final end customer is undisclosed | Bilingual Request, Intro, Legend and Responsibilities completed; the Intro is calibrated to the observed intermediary format and contains three spoken variants: a 60–75-second answer after a team-lead introduction, a 90–105-second standalone screening intro and a 3–4-minute client technical intro, followed by a full domain-based reference version covering five CV projects across four domains; the standalone screening variant keeps SDD and TDD concise and prioritizes direct GoogleTest and GoogleMock experience, requirements-based test levels, coverage and target verification, while the longer variants explain the complete flow from specification and acceptance criteria through implementation, refactoring, coverage and traceability; the variants also explain the standards and process used on the real satellite project: ECSS space-software engineering, PUS packet services, project-approved MISRA C++ rules, Coverity checks and V-model mapping from requirements to unit, integration and target evidence; the Intro prioritizes C++ versus embedded C, testing levels and direct GoogleTest experience, with three observed high-probability intermediary questions, ten likely client follow-ups, explicit test boundaries, standards compliance, team communication and risk management, plus seven questions for the intermediary; the Intro presents project experience without spoken project dates; the SIP Intro and Legend describe the incremental clarification of feature requirements and the primary/backup server example; the Legend covers all five CV projects with stable team compositions, fifteen detailed engineering stories and thirty-eight expanded responsibility answers; the Responsibilities reconcile all thirty-eight CV items and assess all thirty-eight request items: fourteen covered, seventeen partially covered and seven not covered; full-match factual enrichment is limited to the SIP, library and oil-and-gas projects; paired LiveCoding preparation provides a sixty-minute V-model and TDD flow, one fully worked GoogleTest and GoogleMock automotive exercise, five additional practice tasks and explicit ISO 26262, ASIL and HARA positioning; six bilingual self-contained exercise folders include detailed bilingual reasoning from task intake through verification and provide step-by-step briefs, agreed requirements, mocks, test scenarios, implementation order, verification boundaries and completion criteria, plus C++17 contracts, GoogleTest and GoogleMock suites, reference implementations and CMake builds |
| `fake1` | C++ Software Engineer, generic | No request provided | Not provided | Complete core EN/RU package: domain-based Intro; eight-project Legend with team composition, 27 eight-part stories and 48 seven-part expanded task answers; all sections of the four Cloud Native Encoding Platform stories are presented as synchronized interview-ready bullets covering context, problem, impact, alternatives, decisions, actions, validation and causal results; the stories include four localized graphical before-and-after diagrams in editable SVG and presentation-ready PNG formats for JSON-RPC migration, cloud upload reliability, FFmpeg latency and encoder-worker synchronization; a 13-question interview Q&A block follows the fourth cloud story and covers architecture, C++/Java/Kotlin boundaries, personal ownership, end-to-end flow, gRPC migration, worker fencing, media synchronization, upload SLA, latency, manifest recovery, observability and scale; seven projects are verified full matches built from `Summary` with CV titles, periods and roles kept, while Cloud Native Encoding Platform remains a constructed CV-based narrative; Responsibilities reconciles all 48 CV items with 8 confirmed, 28 partially confirmed and 12 unsupported items; project-scoped Tech contains 48 synchronized EN/RU topics for Cloud Native Encoding Platform only, by explicit candidate request; technologies exclusive to projects 2–8 are not covered; no Request files were created |

## Document roles

| Document | Purpose |
|---|---|
| `Request` | Optional bilingual normalization of a supplied request: role, engagement, responsibilities, requirements, technologies and constraints. It is not created when no request exists. |
| `Intro` | Bilingual domain-based opening answer: career domains and project examples followed by a detailed latest-project narrative. |
| `Legend` | Bilingual detailed project narratives built from the selected CV: team composition, architecture, ownership, technical reasoning, delivery stories and expanded answers for every CV task. Missing narrative detail is completed with realistic, internally consistent facts that do not contradict the CV. |
| `Responsibilities` | Bilingual line-by-line reconciliation of every CV responsibility against the factual `Summary` repository. When a request exists, it also marks every requested responsibility and requirement as covered, partially covered or not covered by the candidate's supported real experience. |
| `Tech` | Bilingual interview theory for the technologies in scope, with one topic per file, a synchronized index, project context that repeats only Legend claims, interview questions and dated official sources. The normal scope is the complete selected CV plus a supplied request; an explicitly requested narrower scope must be stated in both indexes and in the package status. |
| `Profile` | Optional or legacy positioning artifact created only when explicitly requested. |
| `Request Analysis` | Optional or legacy customer and requirement analysis created only when explicitly requested. |

## Required consistency

All English and Russian artifacts must agree on:

- candidate name used in the interview;
- target role and positioning;
- project order;
- CV dates and roles;
- personal ownership boundaries;
- technologies and metrics;
- team composition, locations, grades, names and individual stacks;
- tense: current assignment, completed assignment, or time between assignments;
- customer confidentiality.

The English and Russian versions must have the same section order, project order, number of stories, expanded task answers and responsibility items. After changing either language, update the other in the same task.

## Evidence and request-coverage vocabulary

- `CONFIRMED`: `Summary` directly supports the CV responsibility and its scope.
- `PARTIALLY CONFIRMED`: the work is supported, but the CV broadens its technology, ownership, seniority or outcome.
- `NOT SUPPORTED`: `Summary` contains no evidence that the candidate performed the stated responsibility.
- `FACTUAL CORRECTION`: the project is real, but `Summary` establishes a materially different date, role or employment context.

- `COVERED`: the CV and `Summary` contain direct, defensible evidence for the requested responsibility or requirement.
- `PARTIALLY COVERED`: `Summary` supports adjacent or narrower experience but not the complete requested scope.
- `NOT COVERED`: `Summary` contains no defensible evidence for the requested responsibility or requirement.

These statuses are used only when a request exists. Without a request, Responsibilities provides interview-ready answers for the CV responsibilities without request-fit labels.

## Workflow for a new package

1. Create the package directory and place the selected CV in it.
2. Extract every project, period, role, responsibility, technology and metric from the CV. Resolve the sibling `Summary` repository for the later Responsibilities comparison.
3. Determine whether a request exists. If it does, create synchronized English and Russian Request files. If it does not, create no Request file.
4. Create the English Intro by grouping experience into domains, naming representative projects and then expanding the latest project. Create the Russian mirror with the same content.
5. Create the English Legend project by project. Include detailed architecture, team composition, locations, grades, individual stacks, stable names, ownership, engineering challenges and complete project stories explaining why each action was taken. Create the Russian mirror.
6. Create Responsibilities by taking every item from the selected CV and checking it against the relevant `Summary` career documents. Record whether the item is confirmed, only partially confirmed, unsupported or factually different; use only the supported scope in the interview answer. When a request exists, classify every requested responsibility and requirement as `COVERED`, `PARTIALLY COVERED` or `NOT COVERED` from the reconciled real experience.
7. Create `Tech/_Index.md` and `Tech/_Index_RU.md`, then one synchronized EN/RU theory pair for every technology in scope. Use dated official documentation for version-specific or changing facts and repeat only Legend-supported project claims.
8. Synchronize both languages: same projects, order, counts, dates, roles, technologies, metrics, names, stories and outcomes.
9. Remove placeholders, draft labels, human-review notes and repository-generation commentary from interview artifacts.
10. Run the consistency checklist in `Templates/README.md`, update this README and inspect `git status`.

## Research rules

- Perform public customer or domain research only when it is part of the requested package.
- Prefer the named customer's, vendor's, standards body's, or product owner's official sources.
- Record the research date because company and product information changes.
- Keep a raw URL beside every external fact used in a preparation artifact.
- Label interpretations as inference; never present them as customer-confirmed facts.
- If the end client or product is not named, record it as undisclosed instead of guessing.
- Public research supplies customer and domain context. It does not prove the candidate's personal experience.

## Formatting convention

Preparation artifacts use plain text inside `.md` files so they can be pasted into Google Docs without cleanup. Every standard artifact has synchronized English and Russian versions. They use capitalized section labels, blank lines, numbered sections, and hyphen bullets (`- `). Markdown heading markers, emphasis markers, backticks, and tables are avoided inside the artifacts.

`README.md` files may use normal Markdown because they are repository documentation rather than Google Docs content.
