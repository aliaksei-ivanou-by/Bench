Kubernetes

1. TECHNOLOGY PROFILE

Category: Build and tooling
Relevant scope: Orchestration platform for the distributed microservice environment across cloud and local test clusters.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

Kubernetes is a declarative orchestration system. Users submit desired state through API objects; controllers reconcile actual state, while the scheduler assigns Pods to nodes and kubelets manage their containers.

3. CORE CONCEPTS AND INTERNAL MODEL

- Pods are the scheduling unit and share networking and volumes among their containers.
- Deployments manage stateless rollouts; Services provide stable discovery over changing Pod sets.
- Requests, limits, probes, disruption budgets and autoscaling shape availability and resource behavior.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Declare resources and health checks, separate configuration from secrets, make shutdown graceful and treat readiness as the ability to serve real traffic. Test mixed-version rollouts and failure behavior, not only steady state.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Kubernetes standardizes deployment and self-healing across infrastructure but introduces a large control plane and distributed failure modes. Managed container services or simple VM deployment can be better for smaller systems.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Incorrect readiness causes traffic during startup or recovery.
- Missing limits permit noisy-neighbor failures; overly tight limits cause throttling or OOM kills.
- Retries at several layers amplify incidents.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

Kubernetes was part of the broader platform architecture. Mixed-version contract tests and failure-injection scenarios ran in minikube; platform ownership belonged to the principal architect and SRE.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does Kubernetes solve here?
Answer: Kubernetes is a declarative orchestration system. Users submit desired state through API objects; controllers reconcile actual state, while the scheduler assigns Pods to nodes and kubelets manage their containers.

2. Which internal concepts matter most?
Answer: Pods are the scheduling unit and share networking and volumes among their containers. Deployments manage stateless rollouts; Services provide stable discovery over changing Pod sets.

3. What would you make explicit in a production design?
Answer: Declare resources and health checks, separate configuration from secrets, make shutdown graceful and treat readiness as the ability to serve real traffic. Test mixed-version rollouts and failure behavior, not only steady state.

4. What is the main tradeoff or alternative?
Answer: Kubernetes standardizes deployment and self-healing across infrastructure but introduces a large control plane and distributed failure modes. Managed container services or simple VM deployment can be better for smaller systems.

5. Which failure would you test first?
Answer: Incorrect readiness causes traffic during startup or recovery. In this project context, kubernetes was part of the broader platform architecture. Mixed-version contract tests and failure-injection scenarios ran in minikube; platform ownership belonged to the principal architect and SRE.

9. SOURCES

Research date: 2026-10-20.

- https://kubernetes.io/docs/concepts/overview/
- https://kubernetes.io/docs/concepts/workloads/pods/
