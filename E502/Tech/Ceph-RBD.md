Ceph-RBD

1. CATEGORY AND VERSION
Category: Distributed block storage
Versions: Project-specific versions are not established.

2. PURPOSE

RADOS Block Device exposes images as block devices backed by Ceph objects. Clients or CSI can map an RBD image and place a filesystem or use raw block mode above it. Pools and storage policies belong to the underlying cluster.

3. INTERNALS AND DESIGN

RBD and RGW are different entry points. RBD provides a block image for a client or Kubernetes volume; RGW provides an HTTP object API. A filesystem placed on a block image owns its own file semantics. Snapshot, restore and deletion behavior depend on the tool, storage class and policy; validate the complete application recovery path rather than assuming that an image snapshot alone is a backup.

RBD represents a block image backed by Ceph storage. A client can map it as a block device, put a filesystem on it or consume it as raw block where supported. Images, pools and snapshots exist at the storage layer; a filesystem, database and Kubernetes claim add other layers with their own semantics. A block volume is not an S3 bucket and a snapshot is not automatically an independent backup.

In Kubernetes, Ceph CSI can provision an RBD-backed volume for a PVC. Binding, node attachment, device mapping, filesystem mount and application startup are separate stages. ReadWriteOnce normally constrains read/write mounting to a single node, not necessarily a single Pod; actual concurrency and driver behavior still matter. Application-consistent recovery requires coordination with the application and a tested restore procedure.

4. TYPICAL USAGE AND DIAGNOSIS

Track the RBD image, pool, client credentials, mapping and Kubernetes volume state. An attached volume, filesystem mount and application data correctness are separate checks.

Inspect PVC/PV status and CSI logs; use the RBD tools provided by the installed release.

In Kubernetes, a block image may back a PV created through the CSI driver; the workload may consume it as a mounted filesystem or raw block device. Verify the StorageClass, PVC events, PV and node-side mapping before troubleshooting application files. Recoverability depends on a tested procedure, retained snapshots or backups and correct application consistency. A successful mount alone does not prove that the workload sees the expected data.

Scenario: PVC is Bound but a Pod cannot read its volume. Check scheduling and events, then CSI attachment and node-plugin logs, device mapping and mount. Verify access mode, the intended filesystem and credentials before changing the storage class. If the volume mounts but data differs, investigate the application’s expected path and restore history rather than equating mount success with data integrity.

5. STRENGTHS AND LIMITATIONS

RBD supplies block images backed by Ceph and can support Kubernetes workloads through CSI. RGW object storage has different APIs and semantics; a managed block-storage driver is an alternative when its operating model fits.

6. RISKS AND FAILURE MODES

Access modes do not replace application-level locking; multi-writer support depends on configuration and filesystem. Snapshots are not a complete independent backup strategy.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5 and 16.

8. INTERVIEW QUESTIONS

1. What does RBD expose?
A distributed Ceph-backed block image.

2. Is RBD an S3 bucket?
No; RGW provides object access, while RBD provides block storage.

3. What can run on an RBD image?
A filesystem or a raw-block consumer, subject to the deployment and driver.

4. Does RWO mean one Pod?
It limits read/write mounting to one node; multiple Pods on that node can be possible.

5. Is a snapshot an independent backup?
Not by itself; retention, failure domain and restore must be addressed.

6. What does Bound prove?
The claim is bound to a PV; it does not prove attachment, mount or application correctness.

7. Where do you inspect a mount failure?
Check Pod events, CSI node logs, mapping, filesystem and permissions.

8. Why validate restore?
A snapshot or backup is useful only if the application can recover the intended data.

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/rbd/
- https://kubernetes.io/docs/concepts/storage/persistent-volumes/
