Ceph-RADOS

1. CATEGORY AND VERSION
Category: Distributed storage foundation
Versions: Project-specific versions are not established.

2. PURPOSE

RADOS stores objects in pools distributed over OSDs. Monitors maintain cluster maps; placement groups and CRUSH map objects to OSDs according to the configured topology and rules. BlueStore is an OSD storage backend. RGW and RBD are separate interfaces built on this foundation.

3. INTERNALS AND DESIGN

Ceph clients use cluster maps and placement rules rather than a single central lookup for every I/O. OSD health and recovery are connected to available capacity, device and network behavior. When investigating a slow operation, compare time windows and workload, then distinguish application-to-RGW symptoms from OSD-side pressure. Replica placement, quorum and recovery status must be read together; a warning by itself does not quantify data loss.

4. TYPICAL USAGE AND DIAGNOSIS

Check cluster health, monitor quorum, pool and placement-group state, OSD status and capacity; correlate latency with recovery and network or disk behavior. A healthy response is not a guarantee for every application request.

ceph status; ceph health detail; ceph osd tree

A practical investigation begins with the client symptom and a time window, then examines cluster health, quorum, affected pools and placement groups. Check whether recovery, full or nearly full devices, network errors or a degraded OSD coincide with the symptom. A change in these indicators does not on its own prove causation: compare the affected request path and repeat observations. The exact replication policy, topology and remediation depend on the deployment and are not specified by the CV.

5. STRENGTHS AND LIMITATIONS

RADOS offers distributed placement and configurable redundancy; it requires monitoring capacity, network and recovery. A managed object service can reduce operational work, but its deployment model and control differ.

6. RISKS AND FAILURE MODES

Replication or erasure coding and failure domains affect durability, capacity and recovery. Do not infer a bottleneck from one metric or change recovery settings without understanding cluster state.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 1 and 16.

8. INTERVIEW QUESTIONS

1. What is its role?
Distributed storage foundation.

2. How does it work?
RADOS stores objects in pools distributed over OSDs. Monitors maintain cluster maps; placement groups and CRUSH map objects to OSDs according to the configured topology and rules. BlueStore is an OSD storage backend. RGW and RBD are separate interfaces built on this foundation.

3. How would you investigate a failure?
Check cluster health, monitor quorum, pool and placement-group state, OSD status and capacity; correlate latency with recovery and network or disk behavior. A healthy response is not a guarantee for every application request.

4. What are the important failure modes?
Replication or erasure coding and failure domains affect durability, capacity and recovery. Do not infer a bottleneck from one metric or change recovery settings without understanding cluster state.

5. What practical workflow is relevant?
ceph status; ceph health detail; ceph osd tree

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/architecture/
