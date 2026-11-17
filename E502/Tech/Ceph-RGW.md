Ceph-RGW

1. CATEGORY AND VERSION
Category: S3-compatible gateway
Versions: Project-specific versions are not established.

2. PURPOSE

RGW provides an object-storage interface on top of Ceph through S3-compatible APIs. Clients address buckets and objects, authenticate requests and receive HTTP responses. A signed URL delegates a particular request for a bounded time using the signer’s authority.

3. INTERNALS AND DESIGN

For an archive transfer, separate metadata validation, credential and signature generation, transport, RGW response and catalogue publication. A timeout may mean the client does not know whether a request completed, so the application needs explicit retry and reconciliation rules. Check pre-signed method, path, expiration and permissions without recording secrets. For a deployment that uses multipart upload, verify abort and cleanup behavior against the actual version and retention policy.

4. TYPICAL USAGE AND DIAGNOSIS

Separate endpoint, credentials, signature, authorization, object absence and transport failures when diagnosing access. Large objects can use multipart upload if supported by the deployed gateway and client; abandoned uploads need cleanup.

Inspect HTTP status and RGW logs; test permitted, expired and denied access.

An object-access failure can be separated into DNS or transport, S3 request signing, gateway authorization, object lookup and response transfer. Compare the actual HTTP method, request path and expiration when checking a signed URL, and avoid printing the complete URL. If a request times out during upload, determine whether the object exists before an application repeats the operation. Access testing should use a dedicated bucket and limited test credentials.

5. STRENGTHS AND LIMITATIONS

RGW gives applications an S3-compatible object interface backed by Ceph. Managed S3-compatible storage is an alternative when operating a Ceph cluster is unnecessary or unsuitable; compare compatibility, access and operational responsibilities.

6. RISKS AND FAILURE MODES

A URL is a bearer credential; avoid exposing it in logs. Compatibility varies by release and operation. An S3 object is not a Kubernetes block volume.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 1 and 16.

8. INTERVIEW QUESTIONS

1. What is its role?
S3-compatible gateway.

2. How does it work?
RGW provides an object-storage interface on top of Ceph through S3-compatible APIs. Clients address buckets and objects, authenticate requests and receive HTTP responses. A signed URL delegates a particular request for a bounded time using the signer’s authority.

3. How would you investigate a failure?
Separate endpoint, credentials, signature, authorization, object absence and transport failures when diagnosing access. Large objects can use multipart upload if supported by the deployed gateway and client; abandoned uploads need cleanup.

4. What are the important failure modes?
A URL is a bearer credential; avoid exposing it in logs. Compatibility varies by release and operation. An S3 object is not a Kubernetes block volume.

5. What practical workflow is relevant?
Inspect HTTP status and RGW logs; test permitted, expired and denied access.

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/radosgw/s3/
