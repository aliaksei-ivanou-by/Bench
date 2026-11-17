Kubernetes

1. CATEGORY AND VERSION
Category: Container orchestration
Versions: Project-specific versions are not established.

2. PURPOSE

Kubernetes schedules containers as Pods and maintains desired state via controllers. Services provide discovery and access; ConfigMaps and Secrets supply configuration; persistent storage uses PVs, PVCs, StorageClasses and CSI drivers.

3. INTERNALS AND DESIGN

A StorageClass defines provisioning settings, a PVC expresses a claim and a PV represents storage bound to that claim. The CSI controller and node components perform distinct stages. Follow scheduling, binding, attachment and mount in order, inspecting events at each step. A running Pod can still have failing application requests; readiness and storage integrity require additional checks.

4. TYPICAL USAGE AND DIAGNOSIS

Trace Pod scheduling, container events and service connectivity separately from PVC binding, volume attachment and mounting. Operators extend the API using custom resources and reconciliation.

kubectl get pods; kubectl describe pod <name>; kubectl get pvc,pv

A troubleshooting sequence can start with the Pod event stream and its PVC. If the claim is Pending, check StorageClass and provisioner; if bound but the container cannot start, inspect node scheduling, attachment and mount events. Once the workload starts, test the application path separately. These checks are not proof that a specific operator, storage policy or incident existed on the CV project.

5. STRENGTHS AND LIMITATIONS

Kubernetes coordinates scheduling and declarative workloads but adds operational complexity. A simpler deployment or managed platform may be preferable for a small system; compare storage, operations and availability requirements.

6. RISKS AND FAILURE MODES

Pod running is not equivalent to application readiness or storage health. Configure resource limits, access control and secret handling for the deployment.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 5, 13 and 18.

8. INTERVIEW QUESTIONS

1. What is its role?
Container orchestration.

2. How does it work?
Kubernetes schedules containers as Pods and maintains desired state via controllers. Services provide discovery and access; ConfigMaps and Secrets supply configuration; persistent storage uses PVs, PVCs, StorageClasses and CSI drivers.

3. How would you investigate a failure?
Trace Pod scheduling, container events and service connectivity separately from PVC binding, volume attachment and mounting. Operators extend the API using custom resources and reconciliation.

4. What are the important failure modes?
Pod running is not equivalent to application readiness or storage health. Configure resource limits, access control and secret handling for the deployment.

5. What practical workflow is relevant?
kubectl get pods; kubectl describe pod <name>; kubectl get pvc,pv

9. SOURCES

Research date: 2026-11-17
- https://kubernetes.io/docs/concepts/storage/persistent-volumes/
