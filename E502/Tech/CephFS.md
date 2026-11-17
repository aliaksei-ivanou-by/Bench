CephFS

1. CATEGORY AND VERSION
Category: Distributed file system
Versions: The vacancy names CephFS; the CV project does not establish a deployed version.

2. PURPOSE

CephFS provides a shared, POSIX-oriented file-system interface backed by the Ceph RADOS cluster. It is appropriate to discuss when clients need filesystem paths and shared file access. It is distinct from RGW’s HTTP object API and RBD’s block images.

3. INTERNALS AND DESIGN

CephFS uses Metadata Servers (MDS) for filesystem metadata and RADOS pools for metadata and file data. Clients interact with MDS for metadata coordination and access RADOS for file data. The cluster and client configuration determine availability, behavior and supported capabilities; do not infer the project’s topology or versions.

A file path, directory operation and file permissions are filesystem concepts. By comparison, an RGW client works with buckets, object keys and HTTP requests; an RBD client receives block storage that may contain a filesystem. The choice depends on the required interface, access patterns, failure behavior and operations. Shared mount access does not automatically make an application safe for concurrent writes; the application and storage interfaces must agree on coordination.

Kubernetes may provision CephFS-backed storage through an appropriate CSI driver and StorageClass. A PVC, binding, node mount and application access are separate steps. ReadWriteMany expresses a shared-access mode when supported by the selected driver and deployment; it is not evidence that every application handles multiple writers safely.

4. TYPICAL USAGE AND DIAGNOSIS

Scenario: a Pod using shared file storage cannot access its files. Inspect Pod and PVC events, StorageClass and PV, CSI controller and node-side logs, network and credentials. Then check CephFS and MDS health and file permissions. If the volume mounts but a path is missing, verify the application’s expected path and data rather than assuming a CSI provisioning failure.

Read-only examples in an authorized environment: kubectl get pvc,pv; kubectl describe pvc <claim>; ceph fs status; ceph health detail. Exact commands and resource names depend on the deployed release and access permissions.

5. STRENGTHS AND LIMITATIONS

CephFS provides shared filesystem semantics for workloads that need them. It adds metadata-service and operational dependencies; RGW or RBD can be a better fit for object or block interfaces. Compare client compatibility, access patterns, availability and operational responsibility rather than selecting by name alone.

6. RISKS AND FAILURE MODES

A mounted filesystem can still encounter permission errors, unavailable metadata services, network interruption or backend pressure. Multiple writers require application-level correctness. Snapshots and replicated storage should not be assumed to replace tested independent backups. Diagnose the specific boundary before changing cluster configuration.

7. CONNECTION TO PROJECT AND REQUEST

The original E502 request names CephFS as a possible Ceph component. The Remote Sensing Satellites Database CV project specifies RGW, RBD and CSI but does not claim CephFS work. This file is interview theory and does not establish project use or personal CephFS experience.

Request relationship: request items 1 and 16.

8. INTERVIEW QUESTIONS

1. What interface does CephFS provide?
A distributed filesystem interface backed by RADOS.

2. What does MDS do?
It serves and coordinates CephFS filesystem metadata.

3. How does CephFS differ from RGW?
CephFS exposes filesystem semantics; RGW provides supported HTTP object APIs.

4. How does CephFS differ from RBD?
CephFS is a shared filesystem; RBD provides block images.

5. Is a mounted volume proof of correct application data?
No; permissions, expected paths and actual content still require checks.

6. Does RWX guarantee safe concurrent application writes?
No; the application must also handle coordination and correctness.

7. Where do you investigate a failed Kubernetes mount?
Check PVC/Pod events, CSI node logs, credentials, network and CephFS health.

8. Is this topic evidence of personal project experience?
No; it is request-related theory and the CV project does not claim CephFS work.

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/cephfs/
- https://kubernetes.io/docs/concepts/storage/persistent-volumes/
