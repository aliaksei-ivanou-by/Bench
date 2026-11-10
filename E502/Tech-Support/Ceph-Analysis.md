CEPH: ANALYSIS AND INTERVIEW PREPARATION

1. SOURCE AND PURPOSE

Source: Ceph-Notes.md, transcribed from the nine-page Ceph.pdf supplied for E502. Original page numbers are preserved.
Research date: 10 November 2026.

The note is a broad overview of RADOS, OSDs, monitors, managers, MDS, RGW, erasure coding, CRUSH, Ceph CSI, Rook and OpenStack integration. It is useful for preparing technical questions; it is not evidence of project work, ownership or current proficiency.

2. CORE ARCHITECTURE

- RADOS is the distributed object-storage foundation. RGW exposes S3- and Swift-compatible HTTP APIs on top of RADOS; RBD provides block images and CephFS provides a file system. RGW is a gateway, not a synonym for RADOS.
- A pool is a logical partition with properties such as placement policy. Objects are mapped into placement groups (PGs), and CRUSH uses cluster topology and rules to select the OSDs for each PG. A PG is a logical grouping, not a physical disk or a fixed amount of capacity.
- OSDs store data and participate in replication, recovery and rebalancing. Monitors maintain maps and use quorum for cluster coordination. The manager exposes cluster-management functions and metrics. MDS manages CephFS metadata; clients also communicate directly with OSDs for file data.
- RGW data, bucket indexes and user or bucket metadata have different functions and may use different pools. Their actual layout depends on the deployed zone and configuration.

3. CORRECTIONS AND QUALIFICATIONS TO THE SOURCE NOTES

1. Pages 1–2: a single monitor can form a cluster, but is not a fault-tolerant production configuration. Three monitors across independent failure domains are a common baseline; five are recommended for production clusters with at least five suitable hosts. An odd count is useful for quorum, not a guarantee of independence or resilience.

2. Page 2: loss of monitor quorum prevents normal cluster coordination and map updates. The source claim that Ceph can operate only while a majority of monitors is available is too absolute for every existing I/O path: behavior depends on client state, authentication, maps and failures. Distinguish control-plane availability from client data I/O.

3. Page 3: CephFS capabilities govern client caching and access to inode data and metadata. Do not memorize one MDS request per file as a protocol guarantee: caching, invalidation and workload affect the number of requests.

4. Pages 4–5: a PG is a logical set of objects mapped to an OSD acting set; it is not the physical place itself. A CRUSH rule may be used by multiple pools, so there is no universal one-to-one pool-to-rule relationship. Placement must also satisfy the chosen failure domain, not merely the number of OSDs.

5. Page 4: erasure coding divides an object into K data and M coding chunks, generally placed on K+M OSDs. It can reconstruct data after up to M chunk losses under suitable conditions, but degraded I/O availability also depends on pool settings such as min_size, PG state and topology. Replication versus EC is a workload and durability tradeoff, not an absolute hot-versus-cold rule.

6. Page 4: the assertion that manual bucket resharding is only offline is outdated. Ceph documentation describes online bucket-index resharding since Luminous, including manual administration; writes may be blocked briefly. Thresholds, growth and limits depend on release and configuration; do not assume the 100,000-object threshold or 1-to-16 sequence as universal.

7. Pages 5–6: ceph-csi clusterID is a stable unique identifier matched to driver configuration, often the cluster FSID but not universally required to equal it. Check the deployed driver, Ceph and Kubernetes compatibility matrix rather than expecting their version numbers to match. Node-plugin privileges and networking requirements depend on the actual deployment manifests.

8. Page 6: RBD raw block RWX support does not make an ordinary filesystem safe for concurrent writes by multiple nodes. An application must provide appropriate coordination or a clustered filesystem. CephFS is the usual shared-filesystem path, subject to deployment and access-mode configuration.

9. Pages 7–8: Ceph is a possible OpenStack storage backend, not the default or mandatory backend for every service. The statement that Cinder RBD does not support multi-attach is outdated: Cinder release notes document RBD multi-attach support with restrictions. The Cinder CSI plugin also documents multi-attach, snapshots, resizing and cloning subject to its prerequisites and the underlying OpenStack deployment; it is not universally limited to RWO or devoid of snapshot support.

10. Pages 7–8: show_image_direct_url and clone behavior have configuration, compatibility and security implications. The listed pool names and volume identifiers are examples, not universal names. A latency advantage for direct ceph-csi is workload-dependent: Cinder is involved in provisioning and attachment, so the additional control-plane call should not automatically be assumed to add an I/O hop to every read or write.

11. Pages 6–7: Rook manages Ceph and can connect an external cluster, but upgrade ordering and operational steps depend on Rook/Ceph versions and cluster configuration. Use the relevant release documentation and actual health state before planning changes.

4. INTERVIEW QUESTIONS

- What is the difference between RADOS, RGW, RBD and CephFS? RADOS stores objects; RGW exposes object APIs, RBD exposes block images and CephFS provides a file system.
- How is an object placed? The object maps to a PG in a pool; CRUSH maps that PG to an acting set of OSDs using the configured topology and rule.
- Why separate MON quorum and OSD data paths? MONs coordinate cluster maps; clients and OSDs exchange data using those maps. Control-plane failures and data-path failures have different effects.
- When would you use replicated or erasure-coded pools? Compare usable capacity, latency, workload, recovery costs, fault domains and the features supported by the deployed release.
- What does Rook do versus ceph-csi? Rook manages Ceph resources; ceph-csi provisions and attaches RBD or CephFS volumes for Kubernetes workloads.
- What is the difference between direct ceph-csi and Cinder CSI? Direct ceph-csi provisions in Ceph; Cinder CSI uses OpenStack Cinder. Evaluate operations, quotas, network access, security, available features and measured performance.
- What evidence would you inspect for a slow Ceph operation? Health and PG state, client and network latency, OSD utilization, disk latency, recovery activity and workload characteristics before choosing a change.
- What does this note establish about experience? It is technical preparation material. The project-experience assessment remains the CV-versus-Summary reconciliation.

5. OFFICIAL SOURCES

- Ceph architecture and placement: https://docs.ceph.com/en/latest/architecture/dynamic-cluster-management/
- Monitor troubleshooting and quorum: https://docs.ceph.com/en/latest/rados/troubleshooting/troubleshooting-mon/
- Ceph erasure coding: https://docs.ceph.com/en/latest/architecture/erasure-coding/
- RGW dynamic resharding: https://docs.ceph.com/en/latest/radosgw/dynamicresharding/
- ceph-csi support matrix: https://github.com/ceph/ceph-csi
- CephFS CSI clusterID: https://github.com/ceph/ceph-csi/blob/devel/docs/cephfs/deploy.md
- Cinder RBD multi-attach release notes: https://docs.openstack.org/releasenotes/cinder/en_GB/stein.html
- Cinder CSI capabilities: https://github.com/kubernetes/cloud-provider-openstack/blob/master/docs/cinder-csi-plugin/features.md
- RBD backend and pool sharing: https://docs.openstack.org/cinder/yoga/configuration/block-storage/drivers/ceph-rbd-volume-driver.html
