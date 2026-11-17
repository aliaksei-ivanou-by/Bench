Ceph-RGW

1. CATEGORY AND VERSION
Category: S3-compatible gateway
Versions: Project-specific versions are not established.

2. PURPOSE

RGW provides an object-storage interface on top of Ceph through S3-compatible APIs. Clients address buckets and objects, authenticate requests and receive HTTP responses. A signed URL delegates a particular request for a bounded time using the signer’s authority.

3. INTERNALS AND DESIGN

For an archive transfer, separate metadata validation, credential and signature generation, transport, RGW response and catalogue publication. A timeout may mean the client does not know whether a request completed, so the application needs explicit retry and reconciliation rules. Check pre-signed method, path, expiration and permissions without recording secrets. For a deployment that uses multipart upload, verify abort and cleanup behavior against the actual version and retention policy.

RGW provides an HTTP object interface compatible with supported S3 operations on top of RADOS. A bucket, key, operation and authentication context identify a request; the gateway translates object-facing work into underlying storage operations. RGW is distinct from RBD, which exposes block images. Compatibility and features depend on the deployed Ceph release and configuration; do not infer full parity with every AWS S3 feature.

A pre-signed URL delegates an operation using the signer’s credentials and permissions. The HTTP method, path, signed parameters and expiration matter. The URL is effectively a bearer credential: a holder may use it while valid and authorized. Multipart upload has explicit initiation, parts and completion; interrupted uploads can leave unfinished work, so cleanup policy and retry behavior matter.

4. TYPICAL USAGE AND DIAGNOSIS

Separate endpoint, credentials, signature, authorization, object absence and transport failures when diagnosing access. Large objects can use multipart upload if supported by the deployed gateway and client; abandoned uploads need cleanup.

Inspect HTTP status and RGW logs; test permitted, expired and denied access.

An object-access failure can be separated into DNS or transport, S3 request signing, gateway authorization, object lookup and response transfer. Compare the actual HTTP method, request path and expiration when checking a signed URL, and avoid printing the complete URL. If a request times out during upload, determine whether the object exists before an application repeats the operation. Access testing should use a dedicated bucket and limited test credentials.

Scenario: an archive record exists but download returns an error. First separate HTTP transport, status code, expiration, request method, signature and authorization; then verify the object key and gateway/cluster health. Do not print the full URL or credentials. A timeout during upload can leave an unknown outcome, so verify object or multipart state before retrying according to the application’s idempotency contract.

5. STRENGTHS AND LIMITATIONS

RGW gives applications an S3-compatible object interface backed by Ceph. Managed S3-compatible storage is an alternative when operating a Ceph cluster is unnecessary or unsuitable; compare compatibility, access and operational responsibilities.

6. RISKS AND FAILURE MODES

A URL is a bearer credential; avoid exposing it in logs. Compatibility varies by release and operation. An S3 object is not a Kubernetes block volume.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request items 1 and 16.

8. INTERVIEW QUESTIONS

1. What is RGW?
The Ceph gateway exposing supported object APIs such as S3.

2. RGW versus RBD?
RGW exposes object APIs over HTTP; RBD provides block images.

3. What does a pre-signed URL grant?
A time-limited signed request bounded by the signer’s permissions and request conditions.

4. Can it be freely logged?
No; it can grant access and should be treated as sensitive.

5. What is multipart completion?
An explicit step assembling uploaded parts into the resulting object.

6. Does timeout prove upload failed?
No; the result can be unknown and requires verification and safe retry.

7. Is ETag always a checksum?
No; its meaning depends on the operation and implementation.

8. Is RGW fully identical to AWS S3?
No; supported operations and behavior depend on the Ceph release.

9. SOURCES

Research date: 2026-11-17
- https://docs.ceph.com/en/quincy/radosgw/s3/
- https://docs.aws.amazon.com/AmazonS3/latest/userguide/using-presigned-url.html
