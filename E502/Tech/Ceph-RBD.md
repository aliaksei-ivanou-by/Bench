Ceph-RBD

1. CATEGORY AND VERSION
Category: Distributed block storage
Versions: Project-specific versions are not established.

2. PURPOSE

RADOS Block Device exposes images as block devices backed by Ceph objects. Clients or CSI can map an RBD image and place a filesystem or use raw block mode above it. Pools and storage policies belong to the underlying cluster.

3. INTERNALS AND DESIGN

RBD and RGW are different entry points. RBD provides a block image for a client or Kubernetes volume; RGW provides an HTTP object API. A filesystem placed on a block image owns its own file semantics. Snapshot, restore and deletion behavior depend on the tool, storage class and policy; validate the complete application recovery path rather than assuming that an image snapshot alone is a backup.

4. TYPICAL USAGE AND DIAGNOSIS

Track the RBD image, pool, client credentials, mapping and Kubernetes volume state. An attached volume, filesystem mount and application data correctness are separate checks.

Inspect PVC/PV status and CSI logs; use the RBD tools provided by the installed release.

In Kubernetes, a block image may back a PV created through the CSI driver; the workload may consume it as a mounted filesystem or raw block device. Verify the StorageClass, PVC events, PV and node-side mapping before troubleshooting application files. Recoverability depends on a tested procedure, retained snapshots or backups and correct application consistency. A successful mount alone does not prove that the workload sees the expected data.

5. STRENGTHS AND LIMITATIONS

RBD supplies block images backed by Ceph and can support Kubernetes workloads through CSI. RGW object storage has different APIs and semantics; a managed block-storage driver is an alternative when its operating model fits.

6. RISKS AND FAILURE MODES

Access modes do not replace application-level locking; multi-writer support depends on configuration and filesystem. Snapshots are not a complete independent backup strategy.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5 and 16.

8. INTERVIEW QUESTIONS

1. What is its role?
Distributed block storage.

2. How does it work?
RADOS Block Device exposes images as block devices backed by Ceph objects. Clients or CSI can map an RBD image and place a filesystem or use raw block mode above it. Pools and storage policies belong to the underlying cluster.

3. How would you investigate a failure?
Track the RBD image, pool, client credentials, mapping and Kubernetes volume state. An attached volume, filesystem mount and application data correctness are separate checks.

4. What are the important failure modes?
Access modes do not replace application-level locking; multi-writer support depends on configuration and filesystem. Snapshots are not a complete independent backup strategy.

5. What practical workflow is relevant?
Inspect PVC/PV status and CSI logs; use the RBD tools provided by the installed release.

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/rbd/
