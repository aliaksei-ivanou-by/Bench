Prometheus

1. CATEGORY AND VERSION
Category: Metrics collection
Versions: Project-specific versions are not established.

2. PURPOSE

Prometheus collects and queries time-series metrics identified by names and labels. Scrape targets expose measurements; PromQL can evaluate rates, aggregations and alert conditions.

3. INTERNALS AND DESIGN

The project context connects this topic to archive ingestion, metadata, storage or validation. Identify the component boundary and its inputs and outputs before assigning a failure to it.

A counter normally accumulates events and is interpreted with a rate over time; a gauge represents a value that can rise or fall. Histograms enable distribution-based analysis when the exporter exposes suitable buckets. The scrape interval and query range affect what a dashboard can show, and a missing sample can mean scrape failure rather than zero load. Labels should identify useful dimensions without creating a series for every object or request. During an investigation, match the application time window with RGW, cluster and host observations before proposing a change; metrics establish correlation, not automatically the root cause.

Prometheus collects labeled time series from configured targets and evaluates PromQL queries. A counter generally increases and is commonly analyzed with rate over a time range; a gauge can rise and fall. Histograms support distribution analysis when the exporter publishes appropriate buckets. Labels create series, so unbounded identifiers such as individual object keys can produce high cardinality.

Collection and visualization boundaries matter: a missing series may mean scrape failure, absent exporter output or a query mismatch rather than zero load. Latency, request rate, errors, capacity and recovery metrics need consistent units and time windows. Version and exporter determine which names and labels exist; avoid inventing metrics for an undocumented deployment.

4. TYPICAL USAGE AND DIAGNOSIS

Correlate request rates, errors, latency distributions and resource metrics over a defined period. Check scrape health and target availability before interpreting missing values.

Use PromQL and target status to investigate metrics; account for the actual exporter and version.

Scenario: a dashboard shows higher latency. Check target scrape status and the query, establish the affected time and workload, then correlate application errors, gateway requests and storage/network observations. A metric can support or reject a hypothesis but correlation alone does not identify causality. Validate a proposed fix under comparable conditions and do not infer a numerical improvement without measurement.

Interview question: global Ceph client write latency spikes. Confirm the alert, time range, unit, query and affected clients; verify scrape health. Compare write latency distributions and errors with write IOPS and throughput, then examine the RGW or RBD path as appropriate. Check cluster health, slow operations, PG state, recovery, OSD CPU and memory, device latency and utilization, capacity, network errors and saturation. Determine whether the signal is cluster-wide or concentrated on particular OSDs, nodes or failure domains.

Treat recovery, an overloaded device, network bottleneck, CPU saturation and client-side issues as competing hypotheses. Compare against a baseline at similar request size, concurrency and workload; validate with logs and controlled tests, measuring tail latency as well as throughput. Names, labels and buckets vary by exporter and version. Prometheus evaluates alert rules; Alertmanager groups, routes and sends notifications. No specific incident or fix is asserted.

5. STRENGTHS AND LIMITATIONS

Prometheus supports labeled time-series queries and alerting workflows. Logs and traces provide complementary evidence, particularly when a metric cannot identify an individual request path.

6. RISKS AND FAILURE MODES

High-cardinality labels can increase cost. An average alone can hide tail latency; distinguish counter rates, gauges and histogram interpretation.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 6 and 21.

8. INTERVIEW QUESTIONS

1. Counter versus gauge?
A counter generally accumulates events; a gauge can increase or decrease.

2. Why use rate on counters?
To estimate change per unit time over a selected range.

3. What is label cardinality?
The number of distinct time series created by label combinations.

4. Why avoid object keys as labels?
An unbounded number of keys can create excessive series.

5. Does no sample mean zero?
No; check scrape and query health.

6. What can a histogram provide?
Distribution information using its buckets, subject to the query and configuration.

7. Do metrics alone establish cause?
No; correlate with logs, traces and workload evidence.

8. How compare before and after?
Use comparable workload, time window, metrics and units.

9. How would you investigate a global Ceph write-latency spike?
Confirm query and scrape health, compare latency, errors, IOPS and throughput, then correlate OSD, recovery, disk and network signals over the same interval.

10. What is Alertmanager’s role?
It receives alerts and handles grouping, routing and notification; Prometheus evaluates alerting rules.

9. SOURCES

Research date: 2026-11-17
- https://prometheus.io/docs/concepts/
- https://prometheus.io/docs/concepts/metric_types/
- https://prometheus.io/docs/prometheus/latest/querying/basics/
- https://prometheus.io/docs/alerting/latest/alertmanager/
- https://docs.ceph.com/en/quincy/rados/operations/monitoring/
