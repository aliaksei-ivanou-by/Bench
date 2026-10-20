Secure Reliable Transport (SRT)

1. TECHNOLOGY PROFILE

Category: Media
Relevant scope: Live media transport protocol listed in the project environment.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

SRT is an open-source transport protocol for low-latency, reliable media delivery over unpredictable networks. It runs over UDP and combines sequencing, acknowledgements, retransmission and configurable latency.

3. CORE CONCEPTS AND INTERNAL MODEL

- The latency buffer defines how long late or retransmitted packets may still be useful.
- ARQ retransmits lost packets within that latency budget.
- Caller, listener and rendezvous modes address different connection topologies; encryption can protect payloads.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Size latency from measured RTT and jitter, monitor loss and retransmission, secure passphrases, validate firewall/NAT paths and avoid treating transport recovery as a substitute for application-level continuity checks.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

SRT tolerates packet loss better than raw UDP/RTP while keeping lower latency than file-style transfer. RIST is an interoperable alternative; Zixi is a commercial ecosystem; WebRTC targets real-time interaction.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Too little latency prevents retransmission from arriving in time.
- Too much latency hides network problems and violates product goals.
- Key rotation and passphrase handling are operational security concerns.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

SRT was part of the Cloud Native Encoding Platform environment; implementation or configuration was outside the candidate's stated scope.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does Secure Reliable Transport (SRT) solve here?
Answer: SRT is an open-source transport protocol for low-latency, reliable media delivery over unpredictable networks. It runs over UDP and combines sequencing, acknowledgements, retransmission and configurable latency.

2. Which internal concepts matter most?
Answer: The latency buffer defines how long late or retransmitted packets may still be useful. ARQ retransmits lost packets within that latency budget.

3. What would you make explicit in a production design?
Answer: Size latency from measured RTT and jitter, monitor loss and retransmission, secure passphrases, validate firewall/NAT paths and avoid treating transport recovery as a substitute for application-level continuity checks.

4. What is the main tradeoff or alternative?
Answer: SRT tolerates packet loss better than raw UDP/RTP while keeping lower latency than file-style transfer. RIST is an interoperable alternative; Zixi is a commercial ecosystem; WebRTC targets real-time interaction.

5. Which failure would you test first?
Answer: Too little latency prevents retransmission from arriving in time. In this project context, sRT was part of the Cloud Native Encoding Platform environment; implementation or configuration was outside the candidate's stated scope.

9. SOURCES

Research date: 2026-10-20.

- https://github.com/Haivision/srt
- https://github.com/Haivision/srt/blob/master/docs/features-intro.md
