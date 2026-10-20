Kong Gateway

1. TECHNOLOGY PROFILE

Category: Networking and protocols
Relevant scope: API gateway named in the wider microservice platform environment.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

Kong Gateway is a reverse-proxy and API gateway that routes client traffic to upstream services and applies plugins for authentication, rate limiting, transformation and observability.

3. CORE CONCEPTS AND INTERNAL MODEL

- Routes match incoming requests and forward them to Services and upstream targets.
- Plugins can run globally or at scoped entities, so ordering and scope matter.
- Declarative or database-backed modes provide different configuration workflows.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Keep gateway policy thin, version configuration, apply least privilege to admin APIs and test timeout and retry interaction with application clients. Preserve trace context and original request identity safely.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

An API gateway centralizes cross-cutting controls but can become a bottleneck and policy monolith. Cloud-native gateways reduce operations; service meshes address east-west traffic; direct ingress is simpler for small systems.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Gateway retries can multiply application retries.
- A publicly reachable admin API is critical exposure.
- Transformations that diverge from service contracts complicate debugging.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

Kong was part of the project environment; Kong configuration and operations were outside the candidate's stated scope.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does Kong Gateway solve here?
Answer: Kong Gateway is a reverse-proxy and API gateway that routes client traffic to upstream services and applies plugins for authentication, rate limiting, transformation and observability.

2. Which internal concepts matter most?
Answer: Routes match incoming requests and forward them to Services and upstream targets. Plugins can run globally or at scoped entities, so ordering and scope matter.

3. What would you make explicit in a production design?
Answer: Keep gateway policy thin, version configuration, apply least privilege to admin APIs and test timeout and retry interaction with application clients. Preserve trace context and original request identity safely.

4. What is the main tradeoff or alternative?
Answer: An API gateway centralizes cross-cutting controls but can become a bottleneck and policy monolith. Cloud-native gateways reduce operations; service meshes address east-west traffic; direct ingress is simpler for small systems.

5. Which failure would you test first?
Answer: Gateway retries can multiply application retries. In this project context, kong was part of the project environment; Kong configuration and operations were outside the candidate's stated scope.

9. SOURCES

Research date: 2026-10-20.

- https://developer.konghq.com/gateway/
- https://developer.konghq.com/gateway/entities/
