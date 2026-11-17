S3-API

1. CATEGORY AND VERSION
Category: Object-storage protocol
Versions: Project-specific versions are not established.

2. PURPOSE

S3-style APIs operate on buckets and object keys using HTTP operations. Authentication, request signatures and authorization determine access. A pre-signed URL grants a time-limited request using signer credentials.

3. INTERNALS AND DESIGN

A pre-signed URL is tied to an operation and signature parameters; an expired URL, permission error and absent object are different cases. The effective lifetime can also be limited by the credentials used to sign it. Multipart support and S3 compatibility vary by gateway release. A client timeout can leave an unknown completion outcome; define retries and reconciliation rather than assuming failure means no object exists.

An S3-style API addresses objects by bucket and key using HTTP operations. Object metadata and access policy are distinct from the application’s relational catalogue. Request signing authenticates a particular request; a pre-signed URL delegates a method and signed parameters for a limited time using the signer’s credentials. The effective lifetime may be shorter when temporary credentials expire earlier.

Multipart upload divides an object into independently transmitted parts followed by an explicit completion operation. Retries must respect the client and gateway semantics; an interrupted operation may require checking and cleanup. ETag is an opaque entity tag and must not be universally treated as a cryptographic content checksum. Compatibility with a gateway such as RGW is release-specific.

4. TYPICAL USAGE AND DIAGNOSIS

Distinguish PUT/GET, access errors, missing objects, expiration and transfer interruption. Multipart upload divides large uploads into parts and completes them explicitly when supported. Object identifiers and relational catalogue records require application-level coordination.

Inspect HTTP response codes; compare a trusted checksum independently of ETag.

A request can fail at the HTTP transport, authentication, authorization, bucket or object boundary. For a pre-signed operation, verify the actual method, path and expiration and keep the full URL out of diagnostics. A database transaction and an object PUT are separate actions; an application needs a way to identify and reconcile partially completed work. The concrete behavior of a Ceph gateway must be checked against that gateway release rather than assumed from all AWS features.

Scenario: a download link works for one client and fails for another. Compare method, full request path handling, expiry and authorization while keeping the secret-bearing URL out of logs. Separate an HTTP access error from a missing object and from a network failure. On upload timeout, check the resulting object or multipart state before deciding whether to retry; database metadata needs its own reconciliation path.

5. STRENGTHS AND LIMITATIONS

Object APIs suit addressable binary objects and HTTP clients; they do not supply POSIX filesystem behavior. A filesystem or block volume is more appropriate when the workload requires those semantics.

6. RISKS AND FAILURE MODES

A signed URL is a bearer credential; prevent leakage and use appropriate expiration. ETag is not universally a content checksum. S3-compatible behavior depends on the implementation and version.

7. CONNECTION TO PROJECT AND REQUEST

The E502 CV lists this technology for Remote Sensing Satellites Database. The project Legend describes an architecture using it; Responsibilities distinguishes the CV claims from factual evidence. Theory and examples here do not establish personal experience.

Request relationship: request item 27.

8. INTERVIEW QUESTIONS

1. What identifies an object?
The bucket and object key in the relevant service and account context.

2. What is a pre-signed URL?
A time-limited signed request using the signer’s permissions.

3. Is the URL sensitive?
Yes; possession can allow the signed operation while valid.

4. What limits its effective lifetime?
The specified expiration and, where applicable, the lifetime of signing credentials.

5. What is multipart completion?
The explicit operation finalizing uploaded parts into an object.

6. Is ETag always an integrity hash?
No; its meaning depends on the operation and implementation.

7. Is a DB commit atomic with S3 PUT?
Not automatically; the application must address partial completion.

8. Does S3 compatibility imply all AWS features?
No; verify the particular implementation and release.

9. SOURCES

Research date: 2026-11-17
- https://docs.aws.amazon.com/AmazonS3/latest/userguide/using-presigned-url.html
- https://docs.ceph.com/en/quincy/radosgw/s3/
