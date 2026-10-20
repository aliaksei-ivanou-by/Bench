# Package Template Checklist

The current workflow creates interview material from the selected CV, uses the sibling `Summary` repository to validate Responsibilities, and, when available, processes a supplied role request. Read the root `AGENTS.md` before starting.

## Standard files

Always create these bilingual pairs:

- `REQUEST_ID_Intro_CandidateName.md`
- `REQUEST_ID_Intro_CandidateName_RU.md`
- `REQUEST_ID_Legend_CandidateName.md`
- `REQUEST_ID_Legend_CandidateName_RU.md`
- `REQUEST_ID_Responsibilities_CandidateName.md`
- `REQUEST_ID_Responsibilities_CandidateName_RU.md`

Create these files only when a request was supplied:

- `REQUEST_ID_Request_CandidateName.md`
- `REQUEST_ID_Request_CandidateName_RU.md`

Do not create placeholder Request files for a CV-only package.

`Profile` and `Request Analysis` are optional or legacy artifacts. Create them only when explicitly requested, always as bilingual pairs:

- `REQUEST_ID_Profile_CandidateName.md`
- `REQUEST_ID_Profile_CandidateName_RU.md`
- `REQUEST_ID_Request_Analysis_CandidateName.md`
- `REQUEST_ID_Request_Analysis_CandidateName_RU.md`

## Authoring order

1. Inspect and fully extract the selected CV; this CV is the only experience source for Intro and Legend.
2. Request EN and RU, only when a request exists.
3. Intro EN and RU.
4. Legend EN and RU.
5. Responsibilities EN and RU, reconciling each CV item with the relevant `Summary` career documents.
6. Bilingual and package-level validation.

## Intro checklist

- [ ] Opens with the candidate's name, experience and primary specialization.
- [ ] Uses the selected CV for candidate experience; for a verified full-match project it uses the complete relevant `Summary` project record, and no claim is imported from another CV or from an unrelated project.
- [ ] Groups experience by domains.
- [ ] Gives representative project examples for every domain.
- [ ] Expands the latest project in detail.
- [ ] Gives additional emphasis to request-relevant experience when a request exists.
- [ ] Reads naturally as a five-to-six-minute spoken answer.
- [ ] English and Russian versions contain the same facts, domains, projects and metrics.

## Legend checklist

- [ ] Uses every CV project in the original order.
- [ ] Uses the selected CV as its project basis and, for every verified full-match project, the complete relevant `Summary` project record; added narrative detail remains compatible with both and keeps the CV title, period and role.
- [ ] Where the CV is concise, completes architecture, implementation, team and situation details with a realistic, internally consistent narrative rather than leaving gaps or review notes.
- [ ] Contains product and business context for every project.
- [ ] Describes system architecture, components, data flow and integrations.
- [ ] Describes team size, roles, grades, locations and the stack owned by each role.
- [ ] Uses stable names consistently when project-member names are included.
- [ ] Separates the candidate's personal ownership from team responsibilities.
- [ ] Contains at least one detailed project story per project.
- [ ] Every story explains the situation, problem, why it mattered, alternatives, why the selected approach was chosen, actions, validation and result.
- [ ] Every CV responsibility has an expanded technical answer.
- [ ] Expanded answers cover architecture or algorithm, implementation, edge cases, validation and outcome.
- [ ] English and Russian versions have identical project, story and task counts.

## Responsibilities checklist

- [ ] Every CV responsibility appears exactly once and is checked against `Summary`.
- [ ] English preserves the original CV wording.
- [ ] Russian provides a faithful translation.
- [ ] Every item has one evidence status: `CONFIRMED`, `PARTIALLY CONFIRMED`, `NOT SUPPORTED` or `FACTUAL CORRECTION`.
- [ ] Every item cites the relevant `Summary` path or explicitly states that no supporting evidence exists there.
- [ ] Every item has an interview-ready answer and detailed explanation limited to the real scope supported by `Summary`.
- [ ] Every difference between CV wording and supported reality is stated directly and without a pending-review note.
- [ ] If a request exists, every requested responsibility and requirement appears exactly once in the coverage section.
- [ ] Coverage uses only `COVERED`, `PARTIALLY COVERED` and `NOT COVERED`.
- [ ] Every coverage result cites the relevant CV item and `Summary` evidence.
- [ ] English and Russian coverage statuses are identical.

## Request checklist

- [ ] Request files exist only when a request was supplied.
- [ ] Both English and Russian files contain all material role facts.
- [ ] Role summary, responsibilities, requirements, technologies, engagement terms and constraints are normalized.
- [ ] Raw CRM, IMS, email or messenger noise is not copied into the package.
- [ ] The request is treated as opportunity data, not proof of candidate experience.

## Final bilingual consistency checklist

- [ ] Every standard artifact exists in English and Russian.
- [ ] Both languages use the same target role or generic positioning.
- [ ] Both languages use the same project order.
- [ ] Dates, roles, technologies, metrics and names match.
- [ ] Team composition and personal ownership match.
- [ ] Project-story structure and causal reasoning match.
- [ ] Intro and Legend agree with the selected CV and with each other.
- [ ] Responsibilities reports CV-versus-reality differences directly; those findings are not silently copied back into the CV-based Intro or Legend.
- [ ] No unresolved placeholders remain outside the reusable templates.
- [ ] No `TODO`, `TBD`, `VERIFY`, draft status, human-review request or “not stated in the CV” note remains in an interview artifact.
- [ ] Artifacts contain no Markdown headings, emphasis, code fences or tables.
- [ ] Text files use UTF-8 without BOM and CRLF line endings.
- [ ] `git diff --check` passes.
- [ ] Root `README.md` reflects the package state.
