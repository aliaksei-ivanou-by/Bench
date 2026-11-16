E521: PREPARATION REVIEW AND READING MAP

Review date: 2026-11-15; DTB/GPIO answers added 2026-11-16. Role: Senior C++ Engineer – Yocto Linux. Candidate: Aliaksei Ivanou.

01. WHAT WAS REVIEWED

The review covered the selected twelve-page CV, all 32 existing Markdown files in E521, their English/Russian pairing, cited factual project records and the candidate-supplied original recipe snapshot. This reading map is an additional bilingual pair. The original PDF and the downloaded recipe/class/layer files were not changed.

- The CV contains six projects and 39 responsibility bullets. All 39 original items match the English Responsibilities entries after whitespace/punctuation normalization.
- Responsibilities has 39 individual evidence assessments: five CONFIRMED, 32 PARTIALLY CONFIRMED and two NOT SUPPORTED. Date/role corrections are recorded at project level.
- The request has six work items and nine requirements. All 15 are covered once: six COVERED and nine PARTIALLY COVERED.
- The six-project Legend contains ten delivery stories and 39 expanded task answers. Its scope follows the CV; Responsibilities gives the separate factual reconciliation.
- Tech remains limited to the six requested topics, with 150 answered questions. Intro adds eight answers, Legend adds 31 and SIP Fast Q&A now has 48. These existing question banks total 237 answers per language.
- The integration guide has 27 sections. The original-recipe walkthrough explains 455 physical lines: 273 recipe lines, 171 class lines and 11 layer.conf lines.
- English/Russian identifiers, source/configuration examples, evidence statuses and package structure were compared. Formatting and shell syntax checks do not amount to a completed Yocto build.

02. THE MOST IMPORTANT CORRECTIONS

The update story now describes complete changed files selected by comparing releases, explicit removals and omission of unchanged files. It no longer claims historical binary-delta generation or a signed manifest from the word incremental. Those are separate design choices. Recovery is consistent throughout: back up affected files, persist reverse operations, replace files, restore on failure and verify the actual old software.

Qt callback answers now explain callback thread, receiver affinity, deferred argument lifetime and late events instead of drifting into GPIO shutdown examples. The original recipe contributes concrete follow-ups on source pins, unconditional dependencies, /opt staging and runtime aliases. A dead NXP PDF link was replaced; the newer reference is explicitly not treated as the phone’s actual BSP release. The obsolete HOMEPAGE stays in the historical recipe quote with a note that it returned 404.

03. READING ORDER BEFORE THE INTERVIEW

The interview feedback and accepted corrections are recorded in E521_Interview_Debrief_AliakseiIvanou.md. The Intro targets about five minutes, with a compact overview of earlier projects and a concrete Yocto/SIP focus. The storage-layout figure is approximately 16 GB; PoE belongs to the interviewer’s CV.

- First read Request and Profile to keep the role and factual scope clear. The target is embedded Linux/Yocto work, including custom layers, recipes, BSP and image builds.
- Rehearse the Intro once. Keep its earlier-project overview short and spend most detail on the SIP phone.
- Read SIP Fast Q&A sections 1–4 and questions SIP-39 through SIP-48. These connect personal scope to the concrete recipe and the likely technical probes.
- Study Legend stories 1.1 and 1.2: SDK failover and image/startup integration. Be able to trace a symptom across SDK, application, packages and device.
- Use the original walkthrough for R005/R059/R071, R083–R099, R113–R174 and R195–R268. Explain why a setting matters rather than reciting it.
- Use the implementation guide for a runnable learning path. Keep its public QEMU configuration separate from the supplied phone-specific recipe.
- Review Tech in this order: Yocto Project, BitBake, systemd, Embedded Linux, then BSP with NXP i.MX.
- Finish with update recovery and the ownership boundaries in Responsibilities. The recipe snapshot alone does not establish who authored every line.

04. FACTS TO STATE PRECISELY

The defensible hardware description is NXP i.MX ARM64 for the factual phone project. The selected CV does not name the exact SoC or MACHINE. The supplied recipe’s i.MX codec options and Qt compatibility symlink do not uniquely identify the chip or board. Similarly, Kirkstone compatibility in layer.conf does not identify an exact BSP release, kernel commit or bootloader version.

The supplied SDK filename and PV are latest. Its CMake version label is not a source pin. An exact deployed SDK commit must come from the corresponding build/release record; reading this snapshot cannot reconstruct it. The GPIO API version is also not established by the phrase libgpiod C++ API. Explain ownership, blocking waits and cleanup without inventing a 1.x/2.x call sequence or a historical faulty allocation.

The team added Linphone SDK, WebRTC and mediasoup to the initial Yocto skeleton. Personal SDK watchdog/failover work is distinct from ownership of the whole BSP, web frontend or later conferencing-server rewrite. The broad Qt refactor was internal architecture work. HA1 support was implemented, but selection was disabled in the later release history. The supported JSON project format is distinct from the incompatible earlier encrypted BinaryFormatter payload.

English is B2 in the CV and factual profile; C1 is a request requirement. Middle is the recorded formal grade; Senior is the target role. Intro/Legend retain the selected CV’s project chronology, with dates omitted from the spoken Intro by request. Responsibilities records the factual timeline separately. Do not merge the two timelines while answering a date question.

05. COLLECTING CONCRETE BUILD AND DEVICE IDENTITIES

These commands are for an accessible product environment, not outputs already observed in this review. Build metadata and device observations answer different questions. Preserve the image identity and release records; uname alone does not identify the SDK source commit.

BUILD HOST

```bash
bitbake-layers show-layers
bitbake-layers show-recipes linphone-sdk
bitbake-layers show-appends
bitbake -e linphone-sdk | \
    grep -E '^(MACHINE|DISTRO|PV|PR|PKGV|SRCREV|PACKAGECONFIG|S|B|RECIPE_SYSROOT)='
```

TARGET PHONE, WHERE THE INTERFACES ARE AVAILABLE

```bash
uname -a
cat /etc/os-release
cat /proc/cmdline
if [ -r /proc/device-tree/model ]; then
    tr '\000' '\n' < /proc/device-tree/model
fi
if command -v systemctl >/dev/null 2>&1; then
    systemctl --version
fi
```

For SDK and libgpiod versions, use the matching release manifest, package metadata and actual library/build records. A development image may include version-reporting utilities, but their absence is not proof that the library is absent. Do not infer active media acceleration from a build flag alone: inspect the loaded path and validate the relevant workload.

06. QUESTIONS FOR THE INTERVIEWER

- Is the main work application/SDK integration in an existing BSP, or new-board bring-up and kernel/driver ownership?
- Which Yocto release, SoC/board family and vendor layers does the product use?
- Are builds based on independent component recipes or a large SDK superbuild, and which part needs improvement?
- What target hardware, serial access and test environments are available for development?
- How are image releases, partial updates and recovery validated today?
- What are the main acceptance criteria: boot behavior, memory, media reliability, build reproducibility or delivery speed?
- Which CET working hours and English communication tasks are expected?

07. VALIDATION LIMITS

This review checks document consistency, exact CV responsibility coverage, matching question identifiers and code blocks, cited local paths, source snapshot identity, formatting and Bash syntax. It does not execute a full Yocto build, connect to the private SDK repository, run on the phone or establish personal authorship from source presence. Network restrictions and certificate errors are distinguished from confirmed missing URLs.
