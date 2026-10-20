OpenTelemetry

1. TECHNOLOGY PROFILE

Category: Observability
Relevant scope: Vendor-neutral metrics and traces across C++ services, FFmpeg stages and RPC boundaries.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

OpenTelemetry defines APIs, SDKs, semantic conventions and the OTLP protocol for traces, metrics and logs. Instrumented code creates signals; SDK processors sample and batch them; collectors receive, transform and export them.

3. CORE CONCEPTS AND INTERNAL MODEL

- A trace contains spans linked by context propagation across process boundaries.
- Metrics use instruments such as counters and histograms with resource and attribute metadata.
- The Collector separates application instrumentation from backend-specific exporters.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Propagate context through gRPC metadata, define stable low-cardinality attributes, sample high-volume spans and batch exports off the hot path. Align resource identity across deployments so metrics and traces correlate.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

OpenTelemetry reduces backend lock-in and correlates signals, but semantic conventions and sampling require governance. Direct Prometheus instrumentation can be simpler for metrics-only services; provider agents may be easier but less portable.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Broken context propagation fragments traces.
- Sensitive identifiers in attributes create privacy risk.
- Always-on per-frame spans can add unacceptable overhead and volume.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

The candidate architected a C++ telemetry interface, connected FFmpeg and queue boundaries, and used OpenTelemetry to link events for a segment while Prometheus and Google Cloud aggregated metrics.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does OpenTelemetry solve here?
Answer: OpenTelemetry defines APIs, SDKs, semantic conventions and the OTLP protocol for traces, metrics and logs. Instrumented code creates signals; SDK processors sample and batch them; collectors receive, transform and export them.

2. Which internal concepts matter most?
Answer: A trace contains spans linked by context propagation across process boundaries. Metrics use instruments such as counters and histograms with resource and attribute metadata.

3. What would you make explicit in a production design?
Answer: Propagate context through gRPC metadata, define stable low-cardinality attributes, sample high-volume spans and batch exports off the hot path. Align resource identity across deployments so metrics and traces correlate.

4. What is the main tradeoff or alternative?
Answer: OpenTelemetry reduces backend lock-in and correlates signals, but semantic conventions and sampling require governance. Direct Prometheus instrumentation can be simpler for metrics-only services; provider agents may be easier but less portable.

5. Which failure would you test first?
Answer: Broken context propagation fragments traces. In this project context, the candidate architected a C++ telemetry interface, connected FFmpeg and queue boundaries, and used OpenTelemetry to link events for a segment while Prometheus and Google Cloud aggregated metrics.

9. SOURCES

Research date: 2026-10-20.

- https://opentelemetry.io/docs/what-is-opentelemetry/
- https://opentelemetry.io/docs/compatibility/prometheus/
