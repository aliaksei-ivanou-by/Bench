# Bench Request Preparation

This repository stores one preparation package per bench request. Each package is based on the request-specific CV and reconciled with the verified career records in the `Summary` repository.

## Directory structure

Each request directory uses the same layout:

```text
E###/
  E### Candidate Name (...).pdf
  E###_Profile_CandidateName.md
  E###_Intro_CandidateName.md
  E###_Legend_CandidateName.md
  E###_Responsibilities_CandidateName.md
```

The reusable source files are in `_Template/`.

## Document roles

| Document | Purpose |
|---|---|
| `Profile` | Single source of truth for target role, CV facts, verified facts, positioning, dates, and high-risk claims. |
| `Intro` | One interview-ready opening answer tailored to the request. |
| `Legend` | Detailed project narratives, ownership boundaries, technical stories, and follow-up material. |
| `Responsibilities` | Line-by-line reconciliation of every CV responsibility with verified experience. |

## Required consistency

All three preparation documents must agree with the request profile on:

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

1. Copy the `_Template` directory contents into the new request directory and replace `REQUEST_ID` and `CandidateName` in filenames.
2. Fill in the Profile first. Do not draft the other documents before dates, role, project order, and risk claims are reconciled.
3. Draft the Intro from the target role backward: lead with the most relevant recent evidence, then establish the career progression.
4. Draft the Legend project by project using the same project names and order as the CV.
5. Reconcile every CV responsibility in the Responsibilities report. Preserve the original wording, then provide the corrected wording and scope boundary.
6. Run the final consistency checklist in `_Template/README.md`.

## Formatting convention

Preparation artifacts use plain text inside `.md` files so they can be pasted into Google Docs without cleanup. They use capitalized section labels, blank lines, numbered sections, and `•` bullets. Markdown heading markers, emphasis markers, backticks, and tables are avoided inside the artifacts.

`README.md` files may use normal Markdown because they are repository documentation rather than Google Docs content.

