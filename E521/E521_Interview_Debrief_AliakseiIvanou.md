E521: INTERVIEW FEEDBACK AND ACCEPTED CORRECTIONS

Review date: 2026-11-16. Sources: the candidate-supplied interview analysis, the candidate’s corrections, the E521 CV and package, and the supplied original SDK recipe.

01. WHAT THE FEEDBACK CAN ESTABLISH

The attached text is an analysis of a recording, not the recording or a complete transcript. Its reported 8.5-minute introduction and numerical ratings are feedback observations, not independently remeasured results. The useful preparation priorities are clearer Yocto examples, more concise earlier-project coverage, definite ownership statements and questions for the interviewer.

02. THE FIVE-MINUTE INTRODUCTION

The candidate’s target is approximately five minutes, replacing the analysis recommendation of a two-minute maximum. The revised script keeps every CV project in a compact domain overview, then gives most time to the SIP product, actual recipe mechanisms, image/runtime diagnosis and SDK failover. It removes the repeated plan announcements and long earlier-project descriptions. The .NET migration and Qt refactor stay brief.

Five minutes is a speaking target, not a duration guaranteed by a word count. Technical names, pauses and follow-up interruptions change the actual time. For a slow delivery, shorten the earlier-project overview first; keep the concrete Yocto explanation. Detailed GPIO, update and storage stories belong in follow-up answers rather than all being added to the opening.

03. STORAGE LAYOUT: ABOUT 16 GB

The candidate corrected the initial layout to approximately 16 GB. The analysis’s 4 GB value is discarded. Total device capacity is not established by that correction, so neither 8 GB nor 32 GB is asserted. Do not silently convert the reported GB figure into an exact GiB measurement.

The reported story is that the original layout did not use all available capacity and the manual extension procedure was turned into a script. A precise implementation explanation distinguishes the partition boundary from the filesystem size. Enlarging one does not automatically enlarge the other. Rootfs versus a separate data partition, the actual tool and whether the image used Wic remain unspecified in the supplied material; they are not filled with an invented implementation.

04. POE IS NOT THE CANDIDATE’S TOPIC

The candidate clarified that the PoE question concerned Vitaly’s CV. It is not a responsibility in the selected E521 CV. PoE power negotiation is excluded from the candidate’s project stories and preparation priorities. No PoE implementation, diagnosis or personal ownership is added to E521.

05. OTHER FEEDBACK THAT NEEDS PRECISE WORDING

- Updates: the established E521 story is manually prepared partial update.sh packages followed by per-phone packages assembled through the .NET provisioning tool. Recovery restores backed-up files and reverses recorded operations. A/B slots, a provisioning server, a binary blob format and the claim that no checks existed are not established by the existing source set.
- Corrupt configuration: the analysis reports a startup self-check that retains a bad file and loads defaults to avoid a restart loop. Treat this as a reported discussion example, not an independently verified code change or proven personal implementation. The actual startup behavior and configuration format determine the technical answer.
- SDK revisions: the supplied recipe has DEFAULT_COMMIT set to AUTOREV. The statement that the fork was pinned to a tag is not established by that snapshot. Exact historical source pins come from release/build records.
- Fork maintenance: rebase and selective backports are possible maintenance methods. The claimed 1–2 thousand changed lines, a particular rebase workflow and actual security cherry-picks need implementation evidence before becoming personal project facts.
- Licensing: the supplied recipe declares AGPL-3.0-or-later. Do not replace that metadata with the analysis’s generic GPLv3 claim. Component licenses, source revision and any commercial arrangement are separate matters; recipe metadata does not prove the customer’s contractual license.
- CI: the factual record supports contribution and integration, not ownership of every pipeline. State the part actually handled; do not turn suggested code review into a historical responsibility without evidence.
- Phone models: do not infer one shared image, two separate MACHINE settings or runtime detection solely from support for audio-only and camera models. Explain the actual product configuration when its metadata is available.

06. HOW TO ANSWER THE NEXT YOCTO QUESTION

Answer the layer being asked about first: source fetching and revision, recipe dependencies, CMake settings, installation, package contents, image selection or target startup. Then give one concrete project example and the observation that checked it. For a recipe question, use the actual SDK recipe; for a failover question, explain the SDK state machine. This avoids replacing a Yocto answer with a different C++ story.

Reading route: Intro, SIP Fast Q&A questions SIP-07 to SIP-16 and SIP-39 to SIP-48, then the original-recipe walkthrough and the implementation example. The Preparation Review contains the role boundaries and questions for the interviewer.
