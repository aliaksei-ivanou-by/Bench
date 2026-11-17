Ceph-CSI

1. CATEGORY AND VERSION
Category: Kubernetes storage driver
Versions: Project-specific versions are not established.

2. PURPOSE

Ceph CSI implements the Kubernetes Container Storage Interface for Ceph-backed storage. The RBD driver provisions and attaches block volumes; StorageClass parameters and secrets connect requests to a cluster and pool.

3. INTERNALS AND DESIGN

For a Pending claim, first read its events and inspect the StorageClass and driver name. If a PV exists but the Pod cannot use it, investigate scheduling, attachment and the CSI node plugin on the selected node. Verify access mode and volume mode before diagnosing a filesystem problem. Cluster connectivity, authorization and pool configuration belong to another boundary. Do not assume a fixed driver name or default settings across releases.

CSI defines controller-side and node-side operations used to integrate a storage system with an orchestrator. In Kubernetes, a StorageClass identifies a provisioner and parameters, a PVC expresses a claim, and a PV represents the volume. With dynamic provisioning, the external provisioner invokes the driver; later stages can include controller attachment and node staging/publishing, depending on driver capabilities. Exact secret names, driver IDs and behavior are release-specific.

The Ceph RBD driver supplies block-backed volumes; the CephFS driver addresses a different file-storage use case. Access modes, volume mode and reclaim policy influence how a workload uses and retains storage. ReadWriteOnce concerns a single node rather than a blanket guarantee of a single Pod. Do not assume an RGW S3 object is automatically exposed as a CSI block volume.

4. TYPICAL USAGE AND DIAGNOSIS

A PVC requests storage, a provisioner creates or selects a PV, and node-side components prepare and mount the volume for the workload. Inspect PVC events, driver controller and node logs, credentials and Ceph health.

kubectl get pvc,pv; kubectl describe pvc <name>

For dynamic provisioning, a StorageClass points to a driver and its required parameters; the PVC requests capacity and access characteristics. A controller-side provisioner and node-side plugin participate in different stages. PVC events and CSI logs can reveal whether creation, attachment or mounting failed. Exact driver names, secrets and capabilities are deployment-specific; use the installed release documentation instead of assuming current defaults apply to an older cluster.

Scenario: a PVC is Pending. Inspect its events and storageClassName, the StorageClass provisioner, controller/provisioner logs, credentials and connectivity to Ceph. WaitForFirstConsumer can intentionally defer provisioning or binding until a consumer is scheduled, so Pending is not always a failure. If the PVC is Bound and the Pod still fails, move to attach, node plugin and mount diagnostics instead of repeating provisioning checks.

Interview question: how Rook and Ceph CSI work together. Rook reconciles Ceph resources declared through Kubernetes custom resources. A StorageClass names a CSI provisioner and supplies parameters; a user creates a PVC. The external-provisioner calls the CSI controller to create a volume, and Kubernetes creates and binds a PV as appropriate. A scheduled Pod then uses node-side CSI operations to prepare and publish the volume. Exact attachment steps depend on driver capabilities and installed versions.

Short answer: Rook manages the Ceph deployment and desired state; CSI connects Kubernetes volume lifecycle operations to Ceph. The controller path handles provisioning, and the node path prepares storage for the Pod. For failure, inspect PVC events and provisioner/controller first, then attachment, node-plugin and mount issues once a PV is bound.

5. STRENGTHS AND LIMITATIONS

CSI standardizes the Kubernetes integration boundary while a driver implements storage-specific behavior. A cloud-provider CSI driver or another storage backend may be appropriate; exact capabilities depend on the installed implementation.

6. RISKS AND FAILURE MODES

Provisioning, attachment, mount and application readiness are distinct stages. Access modes and volume modes have specific semantics; avoid treating an RGW bucket as an RBD PVC.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5 and 18.

8. INTERVIEW QUESTIONS

1. What does CSI standardize?
The interface between the orchestrator and storage drivers.

2. StorageClass, PVC and PV?
Class configures provisioning; PVC requests storage; PV represents a volume.

3. Controller versus node plugin?
They handle different lifecycle operations, including provisioning and node-side preparation.

4. Why can Pending be intentional?
WaitForFirstConsumer can delay binding until scheduling.

5. Does Bound prove a successful mount?
No; attachment and node-side mounting are separate.

6. RBD versus CephFS CSI?
RBD provides block-backed storage; CephFS provides file storage.

7. What should not be assumed across releases?
Driver names, secret conventions, defaults and supported features.

8. What logs help after a mount failure?
Pod events and the CSI node plugin on the scheduled node.

9. How do Rook and Ceph CSI work together?
Rook reconciles Ceph resources; CSI controller/provisioner and node components implement Kubernetes volume lifecycle operations against Ceph.

10. What happens after a PVC is created?
The configured provisioner can create storage and a PV is bound; a scheduled Pod uses node-side CSI operations, subject to binding mode and driver capabilities.

9. SOURCES

Research date: 2026-11-17
- https://github.com/ceph/ceph-csi
- https://kubernetes.io/docs/concepts/storage/dynamic-provisioning/
- https://rook.io/docs/rook/latest/Troubleshooting/ceph-csi-common-issues/
- https://rook.io/docs/rook/latest/Storage-Configuration/Ceph-CSI/ceph-csi-drivers/
