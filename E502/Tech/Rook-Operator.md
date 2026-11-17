Rook-Operator

1. CATEGORY AND VERSION
Category: Kubernetes storage operator
Versions: Project-specific versions are not established.

2. PURPOSE

Rook uses Kubernetes operator reconciliation to manage declared storage resources. CephCluster and related custom resources describe desired state; the operator works with Kubernetes resources to realize and monitor it.

3. INTERNALS AND DESIGN

Desired state and actual Ceph health are different observations. A reconciliation can fail because of Kubernetes scheduling, storage devices, permissions, credentials or Ceph itself. Inspect events and operator logs together with CephCluster status and daemon health. An upgrade requires compatible versions, capacity and recovery planning; this is a general investigation approach, not evidence of a particular upgrade.

An operator extends Kubernetes with custom resources and reconciliation logic. Rook observes desired Ceph configuration and acts through Kubernetes resources to bring actual state toward it. A CephCluster resource represents a cluster configuration, while related resources describe storage services. Reconciliation is asynchronous; submitting a resource does not prove that Ceph daemons, network, devices and clients are healthy.

A Rook-managed deployment still depends on the underlying Ceph quorum, OSDs, capacity and network. Operator, Ceph and CSI are separate investigation boundaries: a healthy operator cannot by itself confirm a healthy pool or mounted PVC. Upgrades and device selection require version-specific planning, recovery capacity and tests for the actual cluster; the project’s specific versions are not established.

4. TYPICAL USAGE AND DIAGNOSIS

Inspect operator logs, custom resource status, events, Ceph daemon pods and cluster health when deployment or recovery stalls. CSI configuration and available defaults depend on the Rook and Ceph versions.

kubectl get cephcluster -A; kubectl describe cephcluster <name>

The operator watches desired-state objects and reconciles corresponding resources. If configuration is accepted but the cluster remains unhealthy, inspect custom-resource status and events, operator logs, daemon placement and Ceph health in that order as appropriate. An operator can manage deployment behavior without making application and cluster operations the same responsibility. Version compatibility, physical devices and recovery strategy must be checked for the actual environment.

Scenario: the CephCluster resource exists but a storage service is unavailable. Inspect resource status and Kubernetes events, operator logs and daemon scheduling, then check Ceph health and the affected client path. If PVC provisioning is the only failure, inspect CSI separately. Preserve the observed state and confirm the installed version before applying operational changes.

5. STRENGTHS AND LIMITATIONS

Rook automates reconciliation of declared resources but requires Kubernetes and storage expertise. An externally managed Ceph cluster or a managed storage service may fit other operational constraints.

6. RISKS AND FAILURE MODES

A running operator pod does not prove the cluster is healthy. Device selection, upgrades and failure domains affect data safety; validate manifests against the installed release.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5 and 18.

8. INTERVIEW QUESTIONS

1. What does an operator do?
It reconciles actual resources toward a declared desired state.

2. What is CephCluster?
A Rook custom resource describing a Ceph cluster configuration.

3. Does an operator running prove Ceph is healthy?
No; inspect daemons, quorum, OSDs and cluster health.

4. Why check events?
They can show scheduling, permissions or resource failures affecting reconciliation.

5. Is CSI the same as Rook?
No; Rook manages storage resources while CSI provides the orchestrator-to-storage driver interface.

6. What affects OSD deployment?
Available devices, configuration, scheduling and permissions among other factors.

7. Why pin compatible versions?
Operator, Ceph and CSI behavior and support depend on their versions.

8. What is the first step before an upgrade?
Check compatibility, cluster health, capacity and a tested recovery plan.

9. SOURCES

Research date: 2026-11-17
- https://rook.io/docs/rook/latest/CRDs/Cluster/ceph-cluster-crd/
- https://rook.io/docs/rook/latest/Troubleshooting/ceph-csi-common-issues/
