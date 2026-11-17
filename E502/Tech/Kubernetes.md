Kubernetes

1. CATEGORY AND VERSION
Category: Container orchestration
Versions: Project-specific versions are not established.

2. PURPOSE

Kubernetes schedules containers as Pods and maintains desired state via controllers. Services provide discovery and access; ConfigMaps and Secrets supply configuration; persistent storage uses PVs, PVCs, StorageClasses and CSI drivers.

3. INTERNALS AND DESIGN

A StorageClass defines provisioning settings, a PVC expresses a claim and a PV represents storage bound to that claim. The CSI controller and node components perform distinct stages. Follow scheduling, binding, attachment and mount in order, inspecting events at each step. A running Pod can still have failing application requests; readiness and storage integrity require additional checks.

Pods group containers scheduled to nodes; controllers reconcile workload replicas, while Services provide a stable access abstraction. ConfigMaps and Secrets carry configuration with different intended uses. Probes and container state influence workload availability, but a Running Pod does not prove its external dependencies or stored data are correct. Namespaces, RBAC and resource limits affect where and how workloads operate.

PersistentVolume represents storage, PersistentVolumeClaim requests it, and StorageClass selects provisioning behavior. Dynamic provisioning depends on a suitable driver. Immediate binding can happen before scheduling; WaitForFirstConsumer delays binding or provisioning until a consuming Pod is scheduled, which helps honor topology constraints. Reclaim policy and volume/access modes must be checked for the actual class and driver.

4. TYPICAL USAGE AND DIAGNOSIS

Trace Pod scheduling, container events and service connectivity separately from PVC binding, volume attachment and mounting. Operators extend the API using custom resources and reconciliation.

kubectl get pods; kubectl describe pod <name>; kubectl get pvc,pv

A troubleshooting sequence can start with the Pod event stream and its PVC. If the claim is Pending, check StorageClass and provisioner; if bound but the container cannot start, inspect node scheduling, attachment and mount events. Once the workload starts, test the application path separately. These checks are not proof that a specific operator, storage policy or incident existed on the CV project.

Scenario: an application Pod remains Pending with a PVC. Check Pod and PVC events, class name, provisioner and binding mode. Under WaitForFirstConsumer, inspect Pod scheduling constraints before treating the claim as a storage outage. Once bound, failures may instead occur at attach, mount, readiness or application access. Collect events and component logs at each boundary before changing resources.

5. STRENGTHS AND LIMITATIONS

Kubernetes coordinates scheduling and declarative workloads but adds operational complexity. A simpler deployment or managed platform may be preferable for a small system; compare storage, operations and availability requirements.

6. RISKS AND FAILURE MODES

Pod running is not equivalent to application readiness or storage health. Configure resource limits, access control and secret handling for the deployment.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5, 13 and 18.

8. INTERVIEW QUESTIONS

1. What is a Pod?
The smallest schedulable Kubernetes unit containing one or more containers.

2. What is a controller?
A component that reconciles actual resources toward desired state.

3. PVC versus PV?
PVC requests storage; PV represents a storage volume.

4. What does StorageClass select?
Provisioner and storage parameters, including applicable binding and reclaim settings.

5. Why can Pending be normal?
WaitForFirstConsumer may wait for workload scheduling.

6. Does Running prove readiness?
No; probes and dependency behavior need separate checks.

7. What does a Service provide?
A stable abstraction for reaching selected endpoints.

8. What should be checked before deleting a PVC?
Reclaim policy, data retention requirements and the actual storage workflow.

9. SOURCES

Research date: 2026-11-17
- https://kubernetes.io/docs/concepts/storage/persistent-volumes/
- https://kubernetes.io/docs/concepts/storage/storage-classes/
