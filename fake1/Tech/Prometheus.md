Prometheus

1. TECHNOLOGY PROFILE

Category: Observability
Relevant scope: Metrics collection and querying for the C++ encoder, queues, RPCs and cloud-output behavior.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

Prometheus is a pull-oriented monitoring system with a multidimensional time-series model. A sample is identified by a metric name and label set; PromQL derives rates, aggregations and alerts from those series.

3. CORE CONCEPTS AND INTERNAL MODEL

- Counters only increase until reset; gauges move both ways; histograms bucket observations.
- Scraping decouples instrumentation from storage and exposes target health.
- Recording rules precompute expensive expressions and alert rules evaluate conditions over time.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Name metrics by observable behavior, keep units explicit, use bounded labels and choose histogram buckets from real SLO boundaries. Compute rates for counters and aggregate histogram buckets without dropping the le label.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Prometheus has a simple data model and strong query language. It is not a general event store and high cardinality is costly. OpenTelemetry provides vendor-neutral instrumentation; managed monitoring reduces operational burden.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- User IDs, file names or segment IDs in labels cause cardinality explosion.
- Missing rate windows make counters misleading.
- Telemetry on the hot path can perturb the system being measured.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

Prometheus aggregated encoder and stage-latency metrics and deadline-success distributions together with sampled OpenTelemetry traces and Grafana dashboards.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does Prometheus solve here?
Answer: Prometheus is a pull-oriented monitoring system with a multidimensional time-series model. A sample is identified by a metric name and label set; PromQL derives rates, aggregations and alerts from those series.

2. Which internal concepts matter most?
Answer: Counters only increase until reset; gauges move both ways; histograms bucket observations. Scraping decouples instrumentation from storage and exposes target health.

3. What would you make explicit in a production design?
Answer: Name metrics by observable behavior, keep units explicit, use bounded labels and choose histogram buckets from real SLO boundaries. Compute rates for counters and aggregate histogram buckets without dropping the le label.

4. What is the main tradeoff or alternative?
Answer: Prometheus has a simple data model and strong query language. It is not a general event store and high cardinality is costly. OpenTelemetry provides vendor-neutral instrumentation; managed monitoring reduces operational burden.

5. Which failure would you test first?
Answer: User IDs, file names or segment IDs in labels cause cardinality explosion. In this project context, prometheus aggregated encoder and stage-latency metrics and deadline-success distributions together with sampled OpenTelemetry traces and Grafana dashboards.

9. SOURCES

Research date: 2026-10-20.

- https://prometheus.io/docs/introduction/overview/
- https://prometheus.io/docs/practices/instrumentation/
