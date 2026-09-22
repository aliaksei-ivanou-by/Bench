# Bench Request Preparation

This repository stores one preparation package per bench request. Each package is based on the request-specific CV and reconciled with the verified career records in the `Summary` repository.

## Directory structure

Each request directory uses the same layout:

```text
E###/
  E### Candidate Name (...).pdf
  E###_Request_CandidateName.md
  E###_Profile_CandidateName.md
  E###_Request_Analysis_CandidateName.md
  E###_Intro_CandidateName.md
  E###_Legend_CandidateName.md
  E###_Responsibilities_CandidateName.md
```

The reusable source files are in `Templates/`.

## Current request packages

| Request | Target role | Request source | Named customer / final client | Package status |
|---|---|---|---|---|
| `E468` | Senior C++ Developer | YER Experts GmbH | Deloitte is the named requester; final product owner is undisclosed | Full preparation package plus request and customer analysis |
| `E469` | Broadband Triage Engineer | 5V Video | Deutsche Telekom | Full preparation package plus request and customer analysis |
| `E474` | Senior Windows IoT Hardening Expert | Timspark | Final client is undisclosed | Full preparation package plus request and customer analysis |

## Document roles

| Document | Purpose |
|---|---|
| `Request` | Clean English version of the request: role, engagement, responsibilities, requirements, constraints, and open questions. Raw CRM exports are not stored in the package. |
| `Profile` | Single source of truth for target role, CV facts, verified facts, positioning, dates, and high-risk claims. |
| `Request Analysis` | Request facts, customer chain, public customer/domain research, requirement-to-evidence mapping, gaps, interview priorities, and questions. |
| `Intro` | One interview-ready opening answer tailored to the request. |
| `Legend` | Detailed project narratives, ownership boundaries, technical stories, and follow-up material. |
| `Responsibilities` | Line-by-line reconciliation of every CV responsibility with verified experience. |

## Required consistency

All preparation documents must agree with the request profile and request analysis on:

- candidate name used in the interview;
- target role and positioning;
- project order;
- CV dates and verified dates;
- formal role versus target role;
- personal ownership boundaries;
- supported, narrowed, and unsupported technologies;
- tense: current assignment, completed assignment, or time between assignments;
- customer confidentiality.

The CV wording may be recorded for preparation, but the spoken material must not expand an unsupported claim. If the CV conflicts with the verified history, the profile records both values and the Intro and Legend use an interview-safe formulation.

## Status vocabulary

- `CONFIRMED`: supported by the detailed career record.
- `CONFIRMED — NARROWER SCOPE`: the underlying work is real, but the CV wording overstates scope or ownership.
- `UNSUPPORTED`: no evidence of hands-on experience; do not present it as project work.
- `FACTUAL CORRECTION`: the project is real, but a date, role, or employment context differs.
- `VERIFY`: not established by the available sources and requires Aliaksei's confirmation.

## Workflow for a new request

1. Create the request directory and place the request-specific CV in it.
2. Treat the supplied CRM, IMS, email, or messenger request as input data only. Do not copy the raw export into the repository.
3. Copy the six artifact templates from `Templates`, rename them with the request ID and candidate name, and create the normalized English Request first.
4. In the Request, remove internal URLs, personal sales contacts, decorative markers, duplicate fields, Russian service labels, and unrelated system metadata. Preserve all material role facts and record contradictions as alternative fields or open questions.
5. Fill in the Profile by reconciling the request-specific CV with the verified career repository.
6. Complete the Request Analysis from the normalized Request, Profile, verified career evidence, and official public research. Separate request facts, public facts, candidate evidence, inference, open questions, and gaps.
7. Reconcile every CV responsibility in the Responsibilities report. Preserve the original CV wording, then provide corrected wording and a scope boundary.
8. Draft the Legend project by project using the same project names and order as the CV.
9. Draft the Intro from the target role backward: lead with the most relevant confirmed evidence, then establish the career progression.
10. Run the final consistency checklist in `Templates/README.md` and verify that no raw request export remains in the package.

## Research rules

- Prefer the named customer's, vendor's, standards body's, or product owner's official sources.
- Record the research date because company and product information changes.
- Keep a raw URL beside every external fact used in a preparation artifact.
- Label interpretations as inference; never present them as customer-confirmed facts.
- If the end client or product is not named, record it as undisclosed instead of guessing.
- Public research supplies customer and domain context. It does not prove the candidate's personal experience.

## Formatting convention

Preparation artifacts use plain text inside `.md` files so they can be pasted into Google Docs without cleanup. They use capitalized section labels, blank lines, numbered sections, and `•` bullets. Markdown heading markers, emphasis markers, backticks, and tables are avoided inside the artifacts.

`README.md` files may use normal Markdown because they are repository documentation rather than Google Docs content.
