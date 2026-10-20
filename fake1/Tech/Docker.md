Docker

1. TECHNOLOGY PROFILE

Category: Build and tooling
Relevant scope: Container images and local or CI execution for the cloud-native platform.

2. WHAT IT IS AND WHICH PROBLEM IT SOLVES

Docker packages an application and its user-space dependencies into an immutable image and runs that image as an isolated process. Images are layered; containers add a writable layer and share the host kernel.

3. CORE CONCEPTS AND INTERNAL MODEL

- A Dockerfile describes image construction; BuildKit executes and caches the build graph.
- Registries distribute content-addressed layers and manifests.
- Namespaces and cgroups provide isolation and resource control but are not a virtual-machine security boundary by themselves.

The interview focus is not only terminology. A strong answer connects the abstraction to lifecycle, failure semantics, data ownership and the boundary at which the technology stops providing guarantees.

4. TYPICAL USAGE

Use multi-stage builds, minimal non-root runtime images, pinned base-image digests and a clear distinction between build-time and runtime secrets. Emit one process per container unless a deliberate supervisor design is needed.

A useful workflow is to make configuration versioned, keep inputs and outputs observable, test the failure path deliberately and preserve enough diagnostics to reproduce a result outside production.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Containers improve reproducibility and deployment portability but do not erase kernel, architecture or network differences. Virtual machines offer a stronger isolation boundary; native packages can be simpler on fixed hosts.

Selection should follow workload and operational constraints rather than popularity: latency, throughput, consistency, portability, team ownership and recovery requirements all matter.

6. COMMON PITFALLS, PERFORMANCE AND SECURITY

- Running as root and mounting host sockets expands blast radius.
- Mutable tags make rollbacks and incident reconstruction ambiguous.
- Large contexts and invalid layer ordering destroy cache efficiency.

Performance claims require a defined workload, warm-up policy, percentile or deadline target and an unchanged correctness baseline. Security claims require explicit identity, authorization, secret handling and dependency provenance.

7. USE IN THE CANDIDATE'S PROJECT

Project: Cloud Native Encoding Platform, April 2025 – present.

Docker was the container format used with Kubernetes and minikube. Container-platform ownership was outside the candidate's stated scope.

8. LIKELY INTERVIEW QUESTIONS

1. What problem does Docker solve here?
Answer: Docker packages an application and its user-space dependencies into an immutable image and runs that image as an isolated process. Images are layered; containers add a writable layer and share the host kernel.

2. Which internal concepts matter most?
Answer: A Dockerfile describes image construction; BuildKit executes and caches the build graph. Registries distribute content-addressed layers and manifests.

3. What would you make explicit in a production design?
Answer: Use multi-stage builds, minimal non-root runtime images, pinned base-image digests and a clear distinction between build-time and runtime secrets. Emit one process per container unless a deliberate supervisor design is needed.

4. What is the main tradeoff or alternative?
Answer: Containers improve reproducibility and deployment portability but do not erase kernel, architecture or network differences. Virtual machines offer a stronger isolation boundary; native packages can be simpler on fixed hosts.

5. Which failure would you test first?
Answer: Running as root and mounting host sockets expands blast radius. In this project context, docker was the container format used with Kubernetes and minikube. Container-platform ownership was outside the candidate's stated scope.

9. SOURCES

Research date: 2026-10-20.

- https://docs.docker.com/get-started/docker-overview/
- https://docs.docker.com/build/
