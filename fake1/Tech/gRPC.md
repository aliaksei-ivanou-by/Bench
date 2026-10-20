gRPC

1. TECHNOLOGY PROFILE

Category: Networking and protocols
Relevant scope: Typed cross-language service communication replacing legacy JSON-RPC IPC.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

gRPC is an RPC framework built around service definitions and generated client and server APIs. With Protocol Buffers it supports unary, client-streaming, server-streaming and bidirectional-streaming methods, commonly transported over HTTP/2.

3. CORE CONCEPTS AND INTERNAL MODEL

- A stub hides transport details but the call still has network failure semantics.
- Deadlines, cancellation, metadata, interceptors and status codes form the operational contract.
- Streaming introduces flow control and lifetime management beyond a unary request.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Set a deadline on every external call, propagate cancellation, retry only idempotent operations on selected transient statuses and use interceptors for consistent auth and telemetry. Test mixed client/server versions.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

gRPC gives typed APIs, code generation and efficient binary transport. Browser support and human readability are weaker than REST/JSON, and schema governance is mandatory. Async messaging is better when temporal decoupling is required.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Retries without idempotency duplicate side effects.
- Missing deadlines create resource leaks during partial failure.
- Mapping every internal error to UNKNOWN destroys diagnosability.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

The candidate designed an incremental JSON-RPC-to-gRPC migration with parallel adapters, per-method switching, shadow comparison, typed error mapping and OpenTelemetry observation. Reported results were about 40 percent lower serialization overhead and 60 percent smaller requests.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does gRPC solve here?
Answer: gRPC is an RPC framework built around service definitions and generated client and server APIs. With Protocol Buffers it supports unary, client-streaming, server-streaming and bidirectional-streaming methods, commonly transported over HTTP/2.

2. Which internal concepts matter most?
Answer: A stub hides transport details but the call still has network failure semantics. Deadlines, cancellation, metadata, interceptors and status codes form the operational contract.

3. What would you make explicit in a production design?
Answer: Set a deadline on every external call, propagate cancellation, retry only idempotent operations on selected transient statuses and use interceptors for consistent auth and telemetry. Test mixed client/server versions.

4. What is the main tradeoff or alternative?
Answer: gRPC gives typed APIs, code generation and efficient binary transport. Browser support and human readability are weaker than REST/JSON, and schema governance is mandatory. Async messaging is better when temporal decoupling is required.

5. Which failure would you test first?
Answer: Retries without idempotency duplicate side effects. In this project context, the candidate designed an incremental JSON-RPC-to-gRPC migration with parallel adapters, per-method switching, shadow comparison, typed error mapping and OpenTelemetry observation. Reported results were about 40 percent lower serialization overhead and 60 percent smaller requests.

9. SOURCES

Research date: 2026-10-20.

- https://grpc.io/docs/what-is-grpc/core-concepts/
- https://grpc.io/docs/guides/
