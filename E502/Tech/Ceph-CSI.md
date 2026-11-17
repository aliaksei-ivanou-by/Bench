Ceph-CSI

1. CATEGORY AND VERSION
Category: Kubernetes storage driver
Versions: Project-specific versions are not established.

2. PURPOSE

Ceph CSI implements the Kubernetes Container Storage Interface for Ceph-backed storage. The RBD driver provisions and attaches block volumes; StorageClass parameters and secrets connect requests to a cluster and pool.

3. INTERNALS AND DESIGN

For a Pending claim, first read its events and inspect the StorageClass and driver name. If a PV exists but the Pod cannot use it, investigate scheduling, attachment and the CSI node plugin on the selected node. Verify access mode and volume mode before diagnosing a filesystem problem. Cluster connectivity, authorization and pool configuration belong to another boundary. Do not assume a fixed driver name or default settings across releases.

4. TYPICAL USAGE AND DIAGNOSIS

A PVC requests storage, a provisioner creates or selects a PV, and node-side components prepare and mount the volume for the workload. Inspect PVC events, driver controller and node logs, credentials and Ceph health.

kubectl get pvc,pv; kubectl describe pvc <name>

For dynamic provisioning, a StorageClass points to a driver and its required parameters; the PVC requests capacity and access characteristics. A controller-side provisioner and node-side plugin participate in different stages. PVC events and CSI logs can reveal whether creation, attachment or mounting failed. Exact driver names, secrets and capabilities are deployment-specific; use the installed release documentation instead of assuming current defaults apply to an older cluster.

5. STRENGTHS AND LIMITATIONS

CSI standardizes the Kubernetes integration boundary while a driver implements storage-specific behavior. A cloud-provider CSI driver or another storage backend may be appropriate; exact capabilities depend on the installed implementation.

6. RISKS AND FAILURE MODES

Provisioning, attachment, mount and application readiness are distinct stages. Access modes and volume modes have specific semantics; avoid treating an RGW bucket as an RBD PVC.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5 and 18.

8. INTERVIEW QUESTIONS

1. What is its role?
Kubernetes storage driver.

2. How does it work?
Ceph CSI implements the Kubernetes Container Storage Interface for Ceph-backed storage. The RBD driver provisions and attaches block volumes; StorageClass parameters and secrets connect requests to a cluster and pool.

3. How would you investigate a failure?
A PVC requests storage, a provisioner creates or selects a PV, and node-side components prepare and mount the volume for the workload. Inspect PVC events, driver controller and node logs, credentials and Ceph health.

4. What are the important failure modes?
Provisioning, attachment, mount and application readiness are distinct stages. Access modes and volume modes have specific semantics; avoid treating an RGW bucket as an RBD PVC.

5. What practical workflow is relevant?
kubectl get pvc,pv; kubectl describe pvc <name>

9. SOURCES

Research date: 2026-11-17
- https://github.com/ceph/ceph-csi
