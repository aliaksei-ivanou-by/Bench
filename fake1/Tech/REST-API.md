REST API

1. TECHNOLOGY PROFILE

Category: Networking and protocols
Relevant scope: HTTP resource API in the wider platform environment and for output policy configuration.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

REST is an architectural style centered on resources, representations, a uniform interface and stateless interactions. In practical HTTP APIs, methods, status codes, headers, media types, caching and links define behavior.

3. CORE CONCEPTS AND INTERNAL MODEL

- Resource identifiers should be stable and independent of a particular operation.
- HTTP method safety and idempotency guide retries and caching.
- Representations are versioned contracts; status codes describe protocol-level outcomes.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Model nouns rather than RPC verbs, validate inputs, make pagination and errors consistent, use conditional requests where useful and publish an OpenAPI contract if the organization adopts it.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

REST/JSON is accessible and browser-friendly but verbose and less strongly typed than generated RPC. gRPC suits internal low-latency contracts; GraphQL offers client-shaped queries; events suit asynchronous workflows.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Retrying non-idempotent requests duplicates actions.
- Breaking representation changes without versioning harm clients.
- Returning 200 with embedded errors defeats HTTP semantics and observability.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

Cloud-connector priority profiles were exposed through the platform REST API; broader API ownership was outside the candidate's stated scope.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does REST API solve here?
Answer: REST is an architectural style centered on resources, representations, a uniform interface and stateless interactions. In practical HTTP APIs, methods, status codes, headers, media types, caching and links define behavior.

2. Which internal concepts matter most?
Answer: Resource identifiers should be stable and independent of a particular operation. HTTP method safety and idempotency guide retries and caching.

3. What would you make explicit in a production design?
Answer: Model nouns rather than RPC verbs, validate inputs, make pagination and errors consistent, use conditional requests where useful and publish an OpenAPI contract if the organization adopts it.

4. What is the main tradeoff or alternative?
Answer: REST/JSON is accessible and browser-friendly but verbose and less strongly typed than generated RPC. gRPC suits internal low-latency contracts; GraphQL offers client-shaped queries; events suit asynchronous workflows.

5. Which failure would you test first?
Answer: Retrying non-idempotent requests duplicates actions. In this project context, cloud-connector priority profiles were exposed through the platform REST API; broader API ownership was outside the candidate's stated scope.

9. SOURCES

Research date: 2026-10-20.

- https://ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm
- https://www.rfc-editor.org/rfc/rfc9110
