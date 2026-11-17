Ceph-RADOS

1. CATEGORY AND VERSION
Category: Distributed storage foundation
Versions: Project-specific versions are not established.

2. PURPOSE

RADOS stores objects in pools distributed over OSDs. Monitors maintain cluster maps; placement groups and CRUSH map objects to OSDs according to the configured topology and rules. BlueStore is an OSD storage backend. RGW and RBD are separate interfaces built on this foundation.

3. INTERNALS AND DESIGN

Ceph clients use cluster maps and placement rules rather than a single central lookup for every I/O. OSD health and recovery are connected to available capacity, device and network behavior. When investigating a slow operation, compare time windows and workload, then distinguish application-to-RGW symptoms from OSD-side pressure. Replica placement, quorum and recovery status must be read together; a warning by itself does not quantify data loss.

A pool groups objects under a placement and durability policy. Objects map to placement groups, and CRUSH uses the cluster map, weights and rules to select OSDs without a central lookup on every data operation. MONs maintain cluster maps through quorum; OSDs store data and participate in replication or erasure-coded operations. MGR exposes management and monitoring functionality; it does not replace MON quorum. Failure-domain rules matter because placing redundant copies on one host can leave them exposed to the same host failure.

A PG must peer before its participating OSDs agree on its state. Recovery restores desired redundancy after failure; backfill can move data to appropriate OSDs when placement changes. A degraded PG indicates reduced redundancy, while an unavailable or stuck PG requires examination of its specific state and logs. BlueStore is an OSD backend; disk pressure, network and recovery can all affect latency. HEALTH_WARN is a starting point for investigation, not a diagnosis of a particular disk.

4. TYPICAL USAGE AND DIAGNOSIS

Check cluster health, monitor quorum, pool and placement-group state, OSD status and capacity; correlate latency with recovery and network or disk behavior. A healthy response is not a guarantee for every application request.

ceph status; ceph health detail; ceph osd tree

A practical investigation begins with the client symptom and a time window, then examines cluster health, quorum, affected pools and placement groups. Check whether recovery, full or nearly full devices, network errors or a degraded OSD coincide with the symptom. A change in these indicators does not on its own prove causation: compare the affected request path and repeat observations. The exact replication policy, topology and remediation depend on the deployment and are not specified by the CV.

Scenario: users report slow reads while a cluster reports degraded PGs. Establish when the issue began, collect health detail and PG/OSD state, and correlate recovery, capacity, network and device metrics over the same interval. Check the RGW and client path separately; healthy MON quorum and a reachable gateway do not prove that a particular object read is healthy. Compare before and after only under comparable workload. Avoid changing replication or recovery parameters merely to hide a warning.

Interview question: CRUSH and scalability. A client uses the current cluster map and pool/object information to compute the relevant placement group and CRUSH placement. CRUSH maps PGs to OSDs according to the hierarchy, weights and failure-domain rules; it avoids a central per-object location lookup on the RADOS data path. MONs still provide cluster maps and need quorum. Topology changes can cause remapping and recovery traffic, so CRUSH does not guarantee low latency. An external S3 client talks to RGW, which uses the Ceph storage path.

Interview question: an OSD has high CPU and slow I/O. Define the time window and workload; compare OSDs and check cluster health, recovery, capacity, device and network behavior. Examine per-thread CPU, memory trend and relevant logs; CPU and I/O can have different causes. Sampling profiling can identify hot paths with bounded overhead, whereas instrumentation, verbose logging, Valgrind or a debugger may have substantial impact. Use a controlled environment or an approved operational method and verify hypotheses under comparable load.

5. STRENGTHS AND LIMITATIONS

RADOS offers distributed placement and configurable redundancy; it requires monitoring capacity, network and recovery. A managed object service can reduce operational work, but its deployment model and control differ.

6. RISKS AND FAILURE MODES

Replication or erasure coding and failure domains affect durability, capacity and recovery. Do not infer a bottleneck from one metric or change recovery settings without understanding cluster state.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 1 and 16.

8. INTERVIEW QUESTIONS

1. What is the role of a MON?
It maintains cluster maps through monitor quorum.

2. How does an object reach an OSD?
It maps to a PG; CRUSH and the cluster map determine OSD placement according to policy.

3. What is peering?
The PG participants agree on the authoritative state needed to serve the PG.

4. Recovery versus backfill?
Both restore or move PG data; recovery follows missing updates and backfill synchronizes data when placement requires it.

5. What does degraded mean?
The configured redundancy is not fully present; inspect PG state and cause.

6. What is BlueStore?
An OSD storage backend; it is not the S3 gateway.

7. Why do failure domains matter?
They control whether redundant copies share a physical failure boundary.

8. Does HEALTH_OK prove every client request succeeds?
No; application, authentication and network paths still need checking.

9. Why is CRUSH important for scalability?
Clients calculate PG placement using cluster maps and CRUSH, avoiding a central per-object lookup on the RADOS path; network, OSD load and recovery still limit performance.

10. How would you investigate high OSD CPU and slow I/O?
Compare per-thread CPU and memory with cluster recovery, device and network observations; use an appropriately bounded profiling method and verify hypotheses under comparable load.

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/architecture/
- https://docs.ceph.com/en/quincy/rados/operations/placement-groups/
- https://docs.ceph.com/en/quincy/rados/operations/crush-map/
- https://docs.kernel.org/admin-guide/sysctl/kernel.html
