JSON-RPC

1. TECHNOLOGY PROFILE

Category: Networking and protocols
Relevant scope: Legacy inter-process communication protocol replaced by gRPC and Protobuf.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

JSON-RPC 2.0 is a transport-agnostic request/response protocol using JSON objects. A request has jsonrpc, method, optional params and an id; a notification omits the id; responses contain either result or error.

3. CORE CONCEPTS AND INTERNAL MODEL

- The specification defines message shape but not transport, discovery, schema or authentication.
- Batch requests group independent calls but do not imply transactionality.
- Errors carry a numeric code, message and optional data.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Validate the version and message shape, keep method contracts documented, bound payload sizes and define timeout, idempotency and transport behavior outside the base specification. Reject ambiguous mixed result/error responses.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

JSON-RPC is simple, readable and easy to debug, but lacks a built-in typed schema and generated compatibility contract. REST is resource-oriented; gRPC is typed and efficient; messaging decouples producers and consumers.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- String method names and dynamic params defer errors to runtime.
- Notifications provide no application-level response.
- Large JSON payloads increase allocation and serialization cost.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

The platform used JSON-RPC IPC before the candidate introduced a parallel gRPC/Protobuf path and retired methods incrementally after equivalence and performance checks.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does JSON-RPC solve here?
Answer: JSON-RPC 2.0 is a transport-agnostic request/response protocol using JSON objects. A request has jsonrpc, method, optional params and an id; a notification omits the id; responses contain either result or error.

2. Which internal concepts matter most?
Answer: The specification defines message shape but not transport, discovery, schema or authentication. Batch requests group independent calls but do not imply transactionality.

3. What would you make explicit in a production design?
Answer: Validate the version and message shape, keep method contracts documented, bound payload sizes and define timeout, idempotency and transport behavior outside the base specification. Reject ambiguous mixed result/error responses.

4. What is the main tradeoff or alternative?
Answer: JSON-RPC is simple, readable and easy to debug, but lacks a built-in typed schema and generated compatibility contract. REST is resource-oriented; gRPC is typed and efficient; messaging decouples producers and consumers.

5. Which failure would you test first?
Answer: String method names and dynamic params defer errors to runtime. In this project context, the platform used JSON-RPC IPC before the candidate introduced a parallel gRPC/Protobuf path and retired methods incrementally after equivalence and performance checks.

9. SOURCES

Research date: 2026-10-20.

- https://www.jsonrpc.org/specification
