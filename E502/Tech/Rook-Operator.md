Rook-Operator

1. CATEGORY AND VERSION
Category: Kubernetes storage operator
Versions: Project-specific versions are not established.

2. PURPOSE

Rook uses Kubernetes operator reconciliation to manage declared storage resources. CephCluster and related custom resources describe desired state; the operator works with Kubernetes resources to realize and monitor it.

3. INTERNALS AND DESIGN

Desired state and actual Ceph health are different observations. A reconciliation can fail because of Kubernetes scheduling, storage devices, permissions, credentials or Ceph itself. Inspect events and operator logs together with CephCluster status and daemon health. An upgrade requires compatible versions, capacity and recovery planning; this is a general investigation approach, not evidence of a particular upgrade.

4. TYPICAL USAGE AND DIAGNOSIS

Inspect operator logs, custom resource status, events, Ceph daemon pods and cluster health when deployment or recovery stalls. CSI configuration and available defaults depend on the Rook and Ceph versions.

kubectl get cephcluster -A; kubectl describe cephcluster <name>

The operator watches desired-state objects and reconciles corresponding resources. If configuration is accepted but the cluster remains unhealthy, inspect custom-resource status and events, operator logs, daemon placement and Ceph health in that order as appropriate. An operator can manage deployment behavior without making application and cluster operations the same responsibility. Version compatibility, physical devices and recovery strategy must be checked for the actual environment.

5. STRENGTHS AND LIMITATIONS

Rook automates reconciliation of declared resources but requires Kubernetes and storage expertise. An externally managed Ceph cluster or a managed storage service may fit other operational constraints.

6. RISKS AND FAILURE MODES

A running operator pod does not prove the cluster is healthy. Device selection, upgrades and failure domains affect data safety; validate manifests against the installed release.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5 and 18.

8. INTERVIEW QUESTIONS

1. What is its role?
Kubernetes storage operator.

2. How does it work?
Rook uses Kubernetes operator reconciliation to manage declared storage resources. CephCluster and related custom resources describe desired state; the operator works with Kubernetes resources to realize and monitor it.

3. How would you investigate a failure?
Inspect operator logs, custom resource status, events, Ceph daemon pods and cluster health when deployment or recovery stalls. CSI configuration and available defaults depend on the Rook and Ceph versions.

4. What are the important failure modes?
A running operator pod does not prove the cluster is healthy. Device selection, upgrades and failure domains affect data safety; validate manifests against the installed release.

5. What practical workflow is relevant?
kubectl get cephcluster -A; kubectl describe cephcluster <name>

9. SOURCES

Research date: 2026-11-17
- https://rook.io/docs/rook/latest/CRDs/Cluster/ceph-cluster-crd/
