OpenStack

1. CATEGORY AND VERSION
Category: Cloud infrastructure and storage services
Versions: The E502 request mentions OpenStack. The customer’s actual OpenStack, Ceph and driver versions are not specified.

2. PURPOSE

OpenStack is a collection of services for managing cloud infrastructure. In the interview, the specific question was about Cinder and Manila: Cinder is the OpenStack Block Storage service, while Manila provides shared file systems as a service. Each can use a suitable storage backend through a driver; Ceph is one possible backend rather than an automatic requirement.

3. CORE CONCEPTS

Cinder manages the lifecycle of block volumes: a user requests a volume, a scheduler and volume service select and use a configured backend, and the volume can be attached to an appropriate consumer such as a Nova virtual machine. The backend can be Ceph RBD when the deployed Cinder driver and configuration support it. A Cinder volume is a block-storage abstraction; applications still need an appropriate filesystem or other block consumer above it.

Manila provides shared file systems through shares. A share type, backend driver, access rules and export or mount details govern how clients obtain access. Depending on the configured Manila driver and deployment, CephFS can be used as a backend or access protocol. Do not assume every Manila share uses CephFS or the same access protocol.

Ceph RGW provides an S3-compatible object interface and is a separate access path from both Cinder’s block volumes and Manila’s shared file systems. Ceph CSI is the driver interface for Kubernetes storage lifecycle operations; Cinder and Manila are OpenStack services. A real deployment can combine these technologies, but the actual customer architecture must be established from its configuration.

4. TYPICAL USAGE AND DIAGNOSIS

For a Cinder volume, distinguish creation, backend provisioning, attachment to the compute consumer and filesystem or application access. Inspect the volume state and errors, the relevant OpenStack service and driver logs, then backend connectivity and health. A volume existing in Cinder does not by itself prove that it is attached or usable by an application.

For a Manila share, inspect the share state, configured backend and protocol, access rules and export or mount details. Then separate client network, authentication and permissions from CephFS/MDS or other backend health. Both investigations require the deployed release’s documentation and the actual configured driver; these are general approaches, not project incidents.

5. STRENGTHS AND LIMITATIONS

Cinder provides a managed block-volume interface for appropriate cloud consumers; Manila provides a managed shared-filesystem interface. They solve different access problems. An S3 object service or a Kubernetes CSI driver may be more appropriate for other consumers and requirements. Using any of these does not remove the operational responsibility for the selected backend.

6. PITFALLS AND SECURITY

Do not equate a Cinder block device, a Manila share and an RGW bucket. Check credentials, access policy, network reachability and the intended consumer. Provisioning success, attachment or mounting, and correct application data are separate checks. Snapshot and recovery capabilities depend on the backend and release; verify a restore procedure rather than assuming that a snapshot is an independent backup.

7. CONNECTION TO THE REQUEST AND EXPERIENCE

The E502 request names OpenStack as a cloud-platform skill and describes an OpenStack-based environment. In the interview recording, the candidate said he did not have experience with Cinder or Manila. The Remote Sensing Satellites Database CV project does not claim work with either service. This section is interview theory, not evidence of project or personal experience.

Request relationship: OpenStack, request item 25.

8. INTERVIEW QUESTIONS

1. What is Cinder?
The OpenStack Block Storage service, which manages block volumes for supported consumers.

2. What is Manila?
The OpenStack Shared File Systems service, which manages shared file systems through configured backends.

3. What is the difference between a Cinder volume and a Manila share?
Cinder provides block storage; Manila provides a shared filesystem interface through a supported protocol and backend.

4. Can Cinder use Ceph RBD?
Yes, with a compatible configured Cinder RBD backend; it is not the only possible backend.

5. Can Manila use CephFS?
Yes, through a supported and configured Manila driver; other backends also exist.

6. Is RGW the same as Cinder or Manila?
No. RGW exposes supported object APIs such as S3; Cinder and Manila provide different OpenStack storage services.

7. Is Cinder the same as Ceph CSI?
No. Cinder is an OpenStack block-storage service; CSI defines the storage driver boundary used by Kubernetes.

8. What should you check if a volume exists but a VM cannot use it?
Check attachment and consumer state, permissions, network and backend logs, then the filesystem or application path.

9. What is the conceptual path from a Cinder request to a Ceph RBD backend?
Cinder receives the volume request, selects a configured backend and the RBD driver manages the backing volume; attachment to the compute consumer is a separate stage.

10. How would you investigate a Manila share that exists but cannot be mounted?
Check share status, export location, access rules, client network and permissions, then the configured backend and service logs.

9. SOURCES

Research date: 2026-11-17
- https://docs.openstack.org/cinder/latest/
- https://docs.openstack.org/manila/latest/
- https://docs.openstack.org/manila/latest/configuration/shared-file-systems/drivers/cephfs_driver.html
