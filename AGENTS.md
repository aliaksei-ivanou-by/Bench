# AGENTS.md

Instructions for AI agents working in this repository. This repository contains interview-preparation packages built from a selected CV, the candidate's factual `Summary` repository where required, and, when available, a role request.

## Communication

- The candidate communicates in Russian. Answer the candidate in Russian unless asked otherwise.
- Repository documentation is written in English.
- Interview artifacts are always produced in two synchronized versions: English and Russian.
- Do not commit or push unless the candidate explicitly asks.
- Do not send applications, messages or emails and do not contact recruiters or employers.

## Source scope

Each artifact has a fixed source boundary.

- `Intro` starts from the selected CV in the current package. Do not use another CV or another request package. A verified full-match project from the sibling `Summary` repository is the only exception: use all relevant externally usable facts from that real project to enrich and reconcile the corresponding Intro material.
- `Legend` starts from the same selected CV. For a verified full-match project, use all relevant externally usable information from the corresponding `Summary` project document, including context, architecture, data flow, team, personal scope, decisions, stories, testing, deployment, outcomes and limitations. For every other project, the Legend may expand concise CV statements into realistic technical narratives, team structures and project situations, but the expansion must remain compatible with that CV.
- `Responsibilities` starts with every responsibility in the selected CV and checks it against the sibling `Summary` repository. Use `Summary/Interview/Career Overview.md` to locate the relevant period documents, then use those documents and their cited evidence to establish the candidate's real scope.
- A supplied request is the only source for the target role, requested responsibilities, requirements and engagement conditions.
- A request describes the opportunity; it does not prove that the candidate has a requested skill.
- Do not borrow claims from another CV or Bench package.
- Preserve project titles, order, periods, roles, technologies, responsibilities and metrics consistently between the artifacts wherever their source boundary permits them.

Classify a CV project as a verified full match when the project identity is unambiguous and `Summary` describes the same product or system, problem domain, core stack and main body of work. Differences in exact dates or duration, grade or title, legal employer or engagement form (for example informal, contractor or independent work), and a CV that broadens or narrows individual responsibilities do not by themselves prevent a full match; record them in the internal inventory and reconcile them in `Responsibilities`. A project is not a full match when `Summary` has no record of that product or system, describes a different product or domain, or when the CV project is substantially constructed. A technology overlap or a broadly similar domain alone is not enough.

For a verified full match, Intro and Legend keep the CV project title, period and role in project headers and spoken text. `Summary` facts that would contradict those CV fields, such as a different end date, grade or employer, are not stated in Intro or Legend; they appear only in `Responsibilities`. When a CV responsibility goes beyond the `Summary` record, the Legend expanded answer presents the closest defensible version of that work consistent with `Summary` and never asserts a fact that `Summary` contradicts.

For a verified full match, `Summary` is the factual source of detail for `Intro` and `Legend`; prefer its accepted facts over constructed narrative and use the complete relevant project record instead of limiting the artifact to the short CV bullets. Do not expose private evidence, customer secrets, credentials or NDA-protected detail. Do not transfer facts from that real project to any other CV project. A full project match also does not automatically confirm every CV responsibility: `Responsibilities` must still assess every item separately.

For projects that are not verified full matches, `Summary` remains verification evidence for `Responsibilities`, not a source for enriching `Intro` or `Legend`. When the CV and `Summary` differ, keep the CV wording visible in `Responsibilities` and provide the supported real scope, correction or unsupported status from `Summary`.

## Standard package

The standard package contains the source CV and three bilingual artifact pairs:

```text
<request-id>/
  <source-cv>.pdf
  <request-id>_Intro_<CandidateName>.md
  <request-id>_Intro_<CandidateName>_RU.md
  <request-id>_Legend_<CandidateName>.md
  <request-id>_Legend_<CandidateName>_RU.md
  <request-id>_Responsibilities_<CandidateName>.md
  <request-id>_Responsibilities_<CandidateName>_RU.md
```

When a request is supplied, add a bilingual Request pair:

```text
  <request-id>_Request_<CandidateName>.md
  <request-id>_Request_<CandidateName>_RU.md
```

Do not create an empty or placeholder Request when no request was supplied. Profile and Request Analysis are not default artifacts in the current workflow; create them only when the candidate explicitly asks for them.

## Required workflow

Follow this order for every new package.

### 1. Intake and source inventory

1. Resolve the repository root and the target request directory.
2. Identify the source CV selected by the candidate.
3. Determine whether a request was supplied.
4. Extract the CV completely, including every project, period, role, responsibility, technology and metric.
5. Resolve the sibling `Summary` repository and identify the relevant career and project documents for the Responsibilities comparison.
6. Compare every CV project with those factual records and classify it as `FULL MATCH` or `NOT FULL MATCH`, recording the evidence for the decision in the internal inventory.
7. For every `FULL MATCH`, extract the complete relevant externally usable project information from `Summary` before drafting Intro or Legend.
8. Build an internal project-and-responsibility inventory before writing artifacts.

Do not silently substitute a similarly named CV. Do not use `Summary` while drafting Intro or Legend except for a project classified as `FULL MATCH`; never use a partial or merely similar match to enrich them.

### 2. Request branch

If a request was supplied:

1. Create the English and Russian Request files.
2. Normalize the source into role summary, engagement conditions, responsibilities, must-have requirements, nice-to-have requirements, technologies and constraints.
3. Preserve material role facts and resolve formatting noise.
4. Keep the English and Russian versions structurally identical.

If no request was supplied:

1. Do not create Request files.
2. Use generic positioning based on the CV title and strongest domains.
3. Do not create a fictional role request, customer or requirement list.

### 3. Intro

Create the English Intro first and then its Russian mirror.

The Intro is domain-based, following the `fake1` package pattern:

1. Open with the candidate's name, overall experience and primary specialization.
2. Group the career by domains rather than reading the CV project by project without a narrative.
3. For every domain, name one or more representative projects and summarize the candidate's contribution and stack.
4. After the domain overview, explain the latest project in detail. If a request exists and another project is materially more relevant, keep the latest project detailed and give the relevant project additional emphasis.
5. Close with one coherent positioning statement connecting the domains.

For every project classified as `FULL MATCH`, base the Intro description on the complete relevant factual project record from `Summary`, condensed to the length and purpose of the spoken introduction. Do not mention the repository, the match classification or the reconciliation process in the spoken text.

The Intro should normally support a five-to-six-minute spoken answer. It must sound natural when read aloud and must not contain template notes, review instructions or repository terminology.

### 4. Legend

Create the English Legend and then its Russian mirror. The Legend is the most detailed artifact in the package.

For every CV project include:

1. Period, role and project status.
2. A short project summary.
3. Product and business context: users, problem, value and operating environment.
4. System architecture, main components, data flow and external integrations.
5. Team composition:
   - approximate team size;
   - functional roles;
   - seniority or grades;
   - countries or locations from which people worked;
   - the technology stack owned by each role;
   - stable, plausible first names where names improve the spoken narrative.
6. The candidate's personal ownership and interaction with other team members.
7. Main contributions and engineering challenges.
8. Testing, validation, diagnostics, deployment and operational support.
9. Outcome, lessons and likely follow-up questions.

When the CV is concise, expand the Legend with a technically coherent implementation narrative. Added detail must remain compatible with the CV's dates, role, domain, technologies, responsibilities and metrics. Do not introduce a contradictory platform, customer, employer, seniority or numerical result.

For every project classified as `FULL MATCH`, populate all Legend sections from the corresponding factual `Summary` project record. Include all relevant accepted detail needed for interview preparation, not only the facts already repeated in the CV. Preserve documented uncertainty and role boundaries, and do not replace factual team, architecture, testing or outcome information with invented alternatives. After exhausting the matching `Summary` record, fill only genuinely missing required narrative fields with plausible, non-conflicting details under the normal Legend expansion rule.

When the CV does not contain enough detail for a complete interview story, construct realistic and internally consistent project facts: architecture decisions, implementation steps, failure modes, validation methods, team roles, grades, locations, stacks and first names. Treat the CV as the hard boundary: the constructed detail may explain how the listed work could have been delivered, but it must not change what the CV says the candidate did, add a conflicting technology or create a new measurable achievement.

Names and team detail added for narrative continuity must remain consistent throughout the package. Do not use the real identity of a customer employee or recruiter unless the candidate supplied it for that project.

#### Project stories

Every project must contain at least one detailed delivery or investigation story. Important or current projects may contain several.

Each story must explain:

1. Situation — the initial technical and product context.
2. Problem — the concrete failure, limitation or delivery need.
3. Why it mattered — the business, user or operational consequence.
4. Alternatives — the main options considered.
5. Why the selected approach was chosen — technical and delivery tradeoffs.
6. Actions — investigation, architecture, implementation, rollout and coordination.
7. Validation — tests, measurements, monitoring and regression protection.
8. Result — technical and product outcome.

Do not reduce a story to a one-line Situation/Task/Action/Result list. Explain causality: why each important action was necessary and how it led to the result.

#### Expanded task answers

Every responsibility in the CV must also have an expanded Legend answer. Each answer should cover:

- the original task;
- the underlying problem;
- the chosen architecture or algorithm;
- implementation details;
- important edge cases and failure modes;
- validation and diagnostics;
- the result and lesson.

### 5. Responsibilities

Create the English Responsibilities file and then its Russian mirror.

Responsibilities reconcile the selected CV with the candidate's factual `Summary` repository. The CV defines the list and original wording of items to assess; `Summary` defines the real scope that can be defended in an interview. Unlike the Legend's contextual expansion, Responsibilities must not invent team details, implementation facts, technologies, ownership or outcomes.

Every CV responsibility must appear exactly once and include:

1. The original English CV wording in the English file.
2. A faithful Russian translation in the Russian file.
3. One evidence status:
   - `CONFIRMED` — `Summary` directly supports the responsibility and its stated scope;
   - `PARTIALLY CONFIRMED` — the underlying work is supported, but the CV broadens the technology, ownership, seniority or outcome;
   - `NOT SUPPORTED` — `Summary` contains no evidence that the candidate performed the responsibility;
   - `FACTUAL CORRECTION` — `Summary` supports the project but establishes a different date, role, employment context or other material fact.
4. The relevant `Summary` evidence path or `No supporting evidence in Summary`.
5. A concise interview-ready answer using only the supported real scope.
6. A detailed explanation of what was actually done, why and with which supported technology.
7. The gap between the CV wording and reality, when one exists.
8. Relevant follow-up topics.

If a request exists, add complete request coverage based on the reconciled real experience, not on unsupported CV wording:

- `COVERED` — the CV and `Summary` together contain direct, defensible evidence for the requested responsibility or requirement.
- `PARTIALLY COVERED` — `Summary` supports relevant adjacent or narrower experience but not the full requested scope.
- `NOT COVERED` — the requested responsibility or requirement has no defensible support in `Summary`.

Cover every request responsibility and requirement exactly once and cite the relevant CV item and `Summary` evidence. Do not convert an adjacent skill into direct experience.

If no request exists, omit request-coverage statuses and prepare the line-by-line CV-versus-reality reconciliation only.

### 6. Bilingual synchronization

English is the base filename. Russian uses the `_RU` suffix.

The two versions must have:

- identical section order;
- identical project order and count;
- identical responsibility and task count;
- identical dates, roles, technologies, metrics and names;
- the same team composition and personal ownership;
- the same project stories, reasoning and outcomes;
- the same CV-evidence status for every responsibility;
- the same coverage status for every request item.

After changing either language, update the other in the same task. A translation should read naturally in its own language while preserving meaning and level of detail.

## Production-ready writing

Artifacts are final interview material. They must not contain:

- unresolved placeholders;
- `TODO`, `TBD`, `VERIFY` or draft labels;
- statements such as “needs confirmation,” “waiting for human review,” “not stated in the CV,” or “replace with real details”;
- instructions addressed to the candidate inside a spoken answer;
- commentary about how the artifact was generated;
- references to another CV or repository unless explicitly required by the task.

`Responsibilities` may name `Summary` and cite its relative paths because that repository is an explicit source for the CV-versus-reality comparison.

When a field is not needed, omit it instead of leaving a placeholder. Keep confidentiality-sensitive company, customer, repository and production details generic unless the candidate supplied them for use.

## Formatting

Interview artifacts are plain text stored in `.md` files for clean pasting into Google Docs.

- Use capitalized section labels, blank lines, numbered sections and `•` bullets.
- Do not use Markdown heading markers, emphasis markers, code fences or tables inside artifacts.
- Keep project titles and technology names in their standard form.
- Use UTF-8 without BOM and CRLF line endings, matching the repository convention.
- Repository documentation such as `README.md`, `AGENTS.md` and `Templates/README.md` may use normal Markdown.

## Validation checklist

Before finishing:

1. Confirm that Request files exist only when a request was supplied.
2. Confirm that every required artifact has both English and Russian versions.
3. Count projects in both languages and confirm equality.
4. Count Intro domain sections and confirm equivalent coverage.
5. Count Legend stories and expanded task answers and confirm equality.
6. Count CV responsibilities in both Responsibilities files and compare the count with the CV; confirm that each item has a `Summary` evidence status and source path or an explicit absence-of-evidence statement.
7. When a request exists, count request responsibilities and requirements and confirm each has one reality-based coverage result in both languages.
8. Search for unresolved placeholders, draft labels and human-review wording.
9. Check that metrics, dates, roles, names and technologies match between languages.
10. Confirm that every CV project has a recorded `FULL MATCH` or `NOT FULL MATCH` decision and that all `FULL MATCH` Intro and Legend sections use the complete relevant factual project record without borrowing from unrelated projects.
11. Verify UTF-8 without BOM, CRLF line endings, no trailing spaces and no forbidden Markdown markers.
12. Run `git diff --check` and inspect `git status`.
13. Update the package row in the root `README.md`.

Do not commit or push unless explicitly requested. Finish by summarizing the changed files and providing the candidate with the appropriate `git add` and `git commit` commands.
