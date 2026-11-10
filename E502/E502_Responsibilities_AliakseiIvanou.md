RESPONSIBILITIES: CV AND FACTUAL EXPERIENCE

CV source: E502 Aliaksei Ivanou (13, C++).pdf

1. PROJECT IDENTITY AND FACTUAL CORRECTIONS

1. SIP Desk Phone Platform for Audio and Video Communication

Classification: FULL MATCH

PROJECT FACTUAL CORRECTION
CV: May 2024–present, Software Engineer. Summary: May 2025–August 2026 on the SIP project; middle C++ engineer, with a separate internal People Lead role from October 2025.
Evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md; Summary/Interview/Career Overview.md

2. Remote Sensing Satellites Database

Classification: NOT FULL MATCH

PROJECT FACTUAL CORRECTION
CV: April 2022–April 2024, Software Engineer. Summary: a Rails/PostgreSQL satellite reference database in 2015–2016; the described Ceph-based archive system is not the same full project.
Evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md; Summary/Interview/Career Overview.md

3. Software Modules for UAV

Classification: FULL MATCH

PROJECT FACTUAL CORRECTION
CV: March 2020–March 2022, Software Engineer. Summary: optical-system algorithm work within August 2012–January 2020, as a design and research engineer.
Evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md; Summary/Interview/Career Overview.md

4. Software for Processing and Analysis of Satellite Earth Observation Images

Classification: FULL MATCH

PROJECT FACTUAL CORRECTION
CV: January 2018–February 2020, Software Engineer. Summary: satellite imaging work within August 2012–January 2020, as a design and research engineer.
Evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md; Summary/Interview/Career Overview.md

5. Library System

Classification: FULL MATCH

PROJECT FACTUAL CORRECTION
CV: January 2015–December 2017, Software Engineer. Summary: March 2022–April 2024 on the library project, primarily C89 backend development.
Evidence: Summary/Interview/2022-2024. Integrated Library System.md; Summary/Interview/Career Overview.md

6. Corporate System for the Oil and Gas Industry

Classification: FULL MATCH

PROJECT FACTUAL CORRECTION
CV: August 2012–December 2014, Software Engineer, C++11. Summary: October 2021–January 2022, Junior C++ Software Engineer, C++17.
Evidence: Summary/Interview/2021. Oil and Gas Corporate System.md; Summary/Interview/Career Overview.md

2. CV RESPONSIBILITY RECONCILIATION

1. SIP Desk Phone Platform for Audio and Video Communication

1.1. Refactored SIP call handling toward a cleaner MVC/MVVM-style architecture by separating UI rendering from call state, user actions, media negotiation, and Linphone-SDK integration logic.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I refactored Qt call handling into sessions, services, adapters and presentation boundaries. The larger refactor was completed as internal architecture work.

Actual implementation, reasoning and validation: Inherited Qt call handling mixed presentation, SDK callbacks and lifecycle state. I incrementally extracted sessions, services and adapters with explicit QObject/thread ownership. Late callbacks and teardown required focused tests and repeated call transitions. The broader refactor was completed as internal architecture work, not released functionality.

Gap: The CV does not distinguish internal architecture work from released functionality.

Follow-up topics: Qt, asynchronous state, SDK integration

1.2. Incrementally decomposed legacy Qt Widgets call-flow code into clearer domain, presentation, and SDK-integration boundaries while preserving existing UI behavior and QObject signal compatibility.

Status: CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I decomposed inherited Qt call handling into clearer boundaries while maintaining existing interaction patterns and signal connections.

Actual implementation, reasoning and validation: I moved behavior across domain, presentation and SDK-integration boundaries while preserving signal contracts. Signal signatures, queued delivery and object lifetime constrain extraction; changing one consumer at a time reduces migration risk. Focused tests and original call scenarios checked preserved behavior, without asserting that every internal change shipped.

Gap: No material gap in the stated incremental refactoring.

Follow-up topics: QObject signals, controllers, regression

1.3. Hardened video-call and conference UI behavior for edge cases such as held calls, second-line calls, remote hangups, stale overlays, and active video stream switching.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I worked on call and conference UI, hold, second calls, remote hangups and video state; these were validated as adjacent device scenarios.

Actual implementation, reasoning and validation: I worked on phone-side C++/Qt video and conference integration. A visible defect could originate in signaling, SDK parameters, rendering or device readiness. Physical-phone scenarios and logs separated these layers. The record supports this broader work, not an individually retained incident proving every edge case named in the CV.

Gap: The complete list of individual UI fixes and outcomes is broader than the specifically evidenced cases.

Follow-up topics: Hold, teardown, video state

1.4. Extended and customized Linphone-SDK (liblinphone) backend logic to implement SIP failover and backup-server connectivity for improved device reliability.

Status: CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I implemented a registration watchdog and primary/backup failover/failback in the customized liblinphone SDK and integrated its APIs into the phone application.

Actual implementation, reasoning and validation: I reverted an initial Qt rotation attempt, implemented watchdog/failover/failback in customized liblinphone and integrated active/backup APIs. Authentication realm, persisted configuration and UI had to follow SDK-owned state. I added a backup-domain AuthInfo change and validated primary loss/recovery through SIP logs, runtime state and real phones.

Gap: The work was in the project-specific SDK, not upstream Linphone.

Follow-up topics: Registration, failover, authentication

1.5. Developed WebRTC video-conferencing UI and signaling flows: conference creation/join, incoming invite screens, participant roster, SIP/IP/phonebook add dialogs, status strip, control panel, video tile layout, and audio/video device controls.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I integrated and debugged the phone-side WebRTC/mediasoup conference path, with a limited contribution to the initial Node.js server.

Actual implementation, reasoning and validation: My main ownership was phone-side Qt/Linphone and WebRTC/mediasoup integration and debugging. I contributed only to the initial Node.js server, not its later rewrite. Session establishment, device selection and rendered media were checked separately. This supports conferencing work without claiming independently evidenced ownership of every listed dialog.

Gap: The CV lists a broad set of UI and signaling flows; Summary does not establish sole ownership of every listed flow or the later server rewrite.

Follow-up topics: Conference lifecycle, media, ownership

1.6. Autoprovisioning tooling: migrated a WinForms-based configuration utility from .NET Framework 4.8 to .NET 8, unified project file formats across the device ecosystem, and implemented provisioning workflows using SNMP, DHCP, TFTP, and SQLite.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I migrated the inherited WinForms tool to .NET 8 and developed configuration and discovery workflows using SNMP, DHCP, TFTP and SQLite.

Actual implementation, reasoning and validation: I migrated WinForms from .NET Framework 4.8 to .NET 8 and built explicit project-state persistence, discovery and provisioning with SQLite, SNMP, DHCP and TFTP. Supported Project/JSON round trips were checked against generated files and devices. Earlier Framework binary payloads were incompatible; this was not universal backward compatibility or a secret vault.

Gap: The old encrypted BinaryFormatter format is incompatible with the later JSON reader; supported project formats must not be described as universally backward compatible.

Follow-up topics: Format migration, device discovery, provisioning

1.7. Collaborated on Yocto/BitBake customization, i.MX embedded Linux target integration, and device-side service configuration for hardware-software integration.

Status: CONFIRMED

Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md

Interview answer: I adapted inherited Yocto/BitBake recipes, packages and startup services and debugged integration on i.MX devices.

Actual implementation, reasoning and validation: I adapted inherited Yocto Kirkstone/BitBake recipes, installed package contents and systemd startup on ARM64. Weston/Wayland, services and media readiness could cause application symptoms. Image builds, boot scenarios, logs and remote debugging validated integration; I did not introduce Yocto or own all firmware.

Gap: I worked within an inherited platform; I did not create the Yocto platform.

Follow-up topics: BitBake, systemd, target debugging

2. Remote Sensing Satellites Database

2.1. Developed Ruby on Rails web interfaces and workflows for satellite catalogues, metadata, dataset search, and archive access.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I built a Rails and PostgreSQL reference database for remote-sensing satellites and their parameters during 2015–2016.

Actual implementation, reasoning and validation: The real project was a satellite reference database and web interface in Rails/PostgreSQL. I modeled queryable satellite and mission parameters for the department. Shared reference data is supported; the later archive platform, distributed storage and exact dataset-access workflows in the CV are not established by that work.

Gap: The CV presents a different 2022–2024 system and archive platform; Summary supports the earlier reference database, not that complete platform.

Follow-up topics: Rails, PostgreSQL, reference data

2.2. Developed C++ ingestion components with POSIX streaming I/O and optimized memory buffers for large imagery and telemetry archives.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I can discuss the Rails/PostgreSQL reference database and MATLAB image-processing work.

Actual implementation, reasoning and validation: The actual database used Rails/PostgreSQL and imaging used MATLAB. Neither establishes C++ ingestion, POSIX streaming or optimized archive buffers. No benchmark or memory bound can be attributed here. Streaming can be explained as theory; the personal answer stays with the reference database and algorithms.

Gap: Summary has no evidence of C++ ingestion, POSIX streaming or archive buffer optimization on this project.

Follow-up topics: C++ I/O theory, reference database

2.3. Implemented multithreaded data validation, checksum calculation, and file preparation for bulk ingestion.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I designed and verified imaging algorithms in MATLAB; I do not claim a multithreaded archive-ingestion pipeline.

Actual implementation, reasoning and validation: No project evidence supports a multithreaded archive validator, checksum pipeline or bulk-ingestion preparation. MATLAB image verification and relational reference data have different execution and data models. Queue bounds and checksum failures are theory topics, not delivered implementations or validation outcomes from this project.

Gap: No evidence of parallel archive validation, checksums or bulk ingestion.

Follow-up topics: Validation and checksum theory

2.4. Integrated Ceph RGW via S3 API for satellite data storage and retrieval, including pre-signed URLs for secure file access.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I worked on a Rails/PostgreSQL satellite reference database; I have not integrated Ceph RGW or S3 in that work.

Actual implementation, reasoning and validation: The supported database was relational reference software, not an RGW/S3 archive integration. Pre-signed URLs, Ceph credentials and object lifecycle ownership are unsupported. AWS coursework is separate learning evidence. No upload, retrieval or security-validation result for Ceph can be attributed to this database.

Gap: No evidence for Ceph, S3 object storage or pre-signed URLs.

Follow-up topics: Object storage and S3 theory

2.5. Deployed and maintained Ceph services in Kubernetes using Rook Operator.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: My supported system work includes Linux device integration and application debugging, not Kubernetes or Ceph operations.

Actual implementation, reasoning and validation: There is no supported Ceph cluster or Kubernetes/Rook operation by the candidate. The Rails database cannot prove upgrades, recovery or distributed-storage maintenance. Operator reconciliation and failure domains remain preparation topics; no production cluster, availability result or operational duty is inferred.

Gap: No evidence of Kubernetes, Rook or Ceph deployment.

Follow-up topics: Kubernetes and Rook theory

2.6. Configured Ceph CSI for RBD, enabling dynamic persistent volume provisioning.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I have not configured Ceph CSI or RBD; I can discuss deployment integration on the embedded Linux project.

Actual implementation, reasoning and validation: Ceph CSI, RBD and dynamic volumes have no project evidence. SIP-device provisioning is adjacent systems work but a different mechanism from Kubernetes volume provisioning. No PVC, mount or recovery scenario is invented for the reference database; the answer identifies the practical gap directly.

Gap: No supporting evidence for CSI, RBD or dynamic volume provisioning.

Follow-up topics: CSI, RBD and volume theory

2.7. Investigated Ceph performance issues, analyzing I/O latency, throughput, OSD behavior, and BlueStore utilization.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: My diagnosis experience is in application and target behavior, including logs, gdb and Valgrind.

Actual implementation, reasoning and validation: No supported assignment involved Ceph OSD/BlueStore, storage latency or throughput benchmarks. Real native debugging belongs to library and SIP systems and does not establish storage-engine tuning. gdb/Valgrind use cannot justify a Ceph benchmark or numerical performance result.

Gap: No evidence of Ceph performance, OSD or BlueStore investigation.

Follow-up topics: Performance diagnosis versus storage tuning

2.8. Developed Python scripts for storage health checks, deployment validation, data integrity, and performance testing.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: My supported automation includes MATLAB algorithm evaluation; storage-health and benchmark scripting is not evidenced.

Actual implementation, reasoning and validation: Occasional Python use is recorded, but no production storage-health, integrity or deployment suite is established. Rails and MATLAB cannot prove pytest automation. Python/pytest exercises can demonstrate learning separately; no project test suite, run history or operational outcome is inferred from preparation material.

Gap: No supporting evidence for production Python storage-health or performance scripts.

Follow-up topics: Python and storage test theory

2.9. Monitored storage infrastructure with Prometheus and Grafana, identifying bottlenecks and resource issues.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I used application and system logs to diagnose the library and phone products.

Actual implementation, reasoning and validation: The factual diagnostic record uses logs in other projects. No Prometheus metrics, Grafana dashboards, exporters or storage alerts are recorded for this database. Log-based isolation is transferable adjacent experience, not metrics-platform ownership; no monitoring discovery or dashboard outcome is claimed.

Gap: No evidence of Prometheus or Grafana monitoring.

Follow-up topics: Logs, metrics and observability

3. Software Modules for UAV

3.1. Developed digital image processing modules for UAV optical sensor systems, combining MATLAB algorithm development with C++ implementation of performance-critical components.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I developed UAV imaging algorithms in MATLAB, including debayering, stabilization and fusion.

Actual implementation, reasoning and validation: I designed MATLAB modules for debayering, conversion, stabilization and fusion, verified reference/real imagery and coordinated target integration. Input sensor models and intermediate representations matter as much as final appearance. The supported result is a MATLAB processing chain, not personally implemented C++ flight components.

Gap: C++ implementation of performance-critical UAV modules is not supported.

Follow-up topics: MATLAB, image pipeline

3.2. Prototyped and evaluated debayering algorithms in MATLAB and implemented C++ processing modules to convert raw Bayer sensor data into full-color images.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I designed and evaluated debayering algorithms in MATLAB on optical sensor data.

Actual implementation, reasoning and validation: Debayering reconstructs missing colours from a Bayer pattern. I evaluated this behavior in MATLAB with inspectable intermediate images. Edges expose false colours and interpolation errors, so raw reference targets and representative frames matter. This supports algorithm development, not an evidenced personal C++ port.

Gap: C++ Bayer conversion implementation is not supported.

Follow-up topics: Bayer pattern, image validation

3.3. Developed C++ image format conversion and preprocessing components to support different sensor output formats and ensure compatibility across processing pipelines.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I worked on image format conversion as part of the MATLAB UAV processing work.

Actual implementation, reasoning and validation: I implemented MATLAB conversions so sensor output could feed downstream processing coherently. Dimensions, channel interpretation and value ranges were checked through intermediate arrays and representative images. The work supports conversion algorithms and interface reasoning, not a retained production C++ conversion implementation.

Gap: The record does not support C++ conversion-component ownership.

Follow-up topics: Formats, pipeline interfaces

3.4. Optimized image frame processing in C++, focusing on efficient memory buffer management and reducing unnecessary data copying during image operations.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I evaluated imaging algorithms in MATLAB; C++ buffer optimization on this project is not evidenced.

Actual implementation, reasoning and validation: Algorithm design under instrument constraints is supported; C++ copy elimination and buffer-lifetime optimization are not. MATLAB verification must remain separate from a hypothetical native optimization. No allocation profile, benchmark or quantified C++ speedup is recorded; the defensible answer concerns resource-aware algorithms.

Gap: No evidence of C++ frame-buffer ownership or copy optimization.

Follow-up topics: Buffers and memory theory

3.5. Developed and evaluated image stabilization algorithms using MATLAB, implementing selected processing operations in C++ for integration into image processing workflows.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I developed and evaluated UAV stabilization algorithms in MATLAB.

Actual implementation, reasoning and validation: I developed MATLAB stabilization for imagery affected by UAV motion. Real/reference sequences and intermediate visualization help distinguish compensation artifacts from acquisition or platform behavior. This supports the algorithmic work and its validation, while the CV's selected C++ operations are not established personal implementation scope.

Gap: A C++ implementation of selected operations is not supported.

Follow-up topics: Stabilization, representative data

3.6. Designed and validated multi-sensor image fusion algorithms in MATLAB and integrated the resulting processing modules into the software pipeline.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I designed and verified image-fusion algorithms in MATLAB for the UAV optical system.

Actual implementation, reasoning and validation: I designed MATLAB fusion modules to combine useful image information, collaborating with instrument/software colleagues on integration. Alignment and scene motion determine whether fusion adds detail or artifacts. Reference and real-image comparisons support validation, without implying ownership of the complete target software pipeline.

Gap: Summary supports algorithm design, but not the asserted software-pipeline integration scope.

Follow-up topics: Fusion, reference imagery

3.7. Tested image processing modules using representative sensor datasets, analyzing output quality, processing accuracy, and performance.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I verified imaging algorithms using reference imagery and participated in real UAV flight testing as payload operator.

Actual implementation, reasoning and validation: I checked algorithms on reference/real imagery and participated in optical-payload flight testing. Synthetic cases isolate transformations and known targets provide physical references; flights include actual motion and acquisition. This supports image-quality validation and instrument feedback, not an invented C++ performance campaign.

Gap: The CV implies testing C++ modules and performance; Summary supports algorithm and flight validation instead.

Follow-up topics: Reference imagery, flight testing

4. Software for Processing and Analysis of Satellite Earth Observation Images

4.1. Developed algorithms for standardizing brightness levels across multiple frames and eliminating optical defects, improving the overall quality and consistency of satellite imagery.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I designed MATLAB frame-stitching and radiometric matching algorithms to remove visible brightness differences between detector segments.

Actual implementation, reasoning and validation: I designed MATLAB stitching with feature-based overlap alignment and radiometric matching. Geometry alone leaves brightness steps because detectors respond differently. Synthetic offsets, uniform scenes and seam inspection separate geometric and radiometric problems; the delivered result was continuous imagery with corrected joins.

Gap: Summary describes radiometric matching and stitching; it does not establish every possible optical-defect correction.

Follow-up topics: Radiometry, stitching, seams

4.2. Designed and implemented software to analyze the linear resolution of satellite images using the sharp edge method, enhancing the accuracy of imaging performance evaluation.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I developed automated linear-resolution assessment in MATLAB using flight-test imagery.

Actual implementation, reasoning and validation: I automated MATLAB linear-resolution assessment from flight-test imagery. Defining a repeatable criterion and suitable target interpretation came before computation. Known targets and repeated runs made measurements comparable across operators. The precise sharp-edge estimator in the CV is not independently established by the factual record.

Gap: The sharp-edge method is named in the CV but not established by the cited Summary record.

Follow-up topics: Sharp-edge method, ground truth

4.3. Created algorithms to assess image sharpness and edge clarity, ensuring precise resolution measurements for remote sensing applications and contributing to reliable data interpretation.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I automated image-resolution assessment and validated results against reference targets and repeatability.

Actual implementation, reasoning and validation: I turned expert-driven resolution analysis into a defined MATLAB measurement workflow. Noise, target choice and image conditions affect interpretation, so repeatability against references matters more than one attractive number. This supports automated quality assessment, not an additional separately documented edge-clarity algorithm.

Gap: Summary establishes automated resolution assessment, but does not document separate edge-clarity algorithms.

Follow-up topics: Edge clarity, repeatability

4.4. Developed software to predict quantization ranges for remote sensing satellites by analyzing Earth observation data and estimating the albedo range, improving sensor calibration and minimizing data loss.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I predicted image type and adapted quantization to improve image quality at a given compression ratio.

Actual implementation, reasoning and validation: I implemented image-type prediction and adaptive quantization to improve reconstruction quality at matched compression ratios. Smooth and textured scenes place different demands on quantization. The supported mechanism is scene-dependent adaptation; a separate albedo-range estimator and sensor-calibration ownership are not established.

Gap: The evidence describes image-type prediction, not a documented albedo-range estimation workflow.

Follow-up topics: Image type, quantization, compression

4.5. Automated the prediction of quantization ranges, streamlining workflows, and improving operational efficiency.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I implemented image-type prediction and adaptive quantization in MATLAB and compared quality at matched compression ratios.

Actual implementation, reasoning and validation: Prediction/adaptation software made compression behavior repeatable across scene types in MATLAB. Reference scenes and matched-ratio reconstruction comparisons validate that work. No separate time-saving metric or exact albedo-based planning pipeline supports the CV's broader automation wording.

Gap: Automation of an albedo-based range-prediction workflow is not documented.

Follow-up topics: Adaptive quantization, comparison

4.6. Designed and implemented a custom image compression algorithm using ADPCM with multiple quantizers, achieving optimized compression ratios and enhanced flexibility for different data sizes.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2012-2020. Satellite and UAV Optical Imaging Software.md

Interview answer: I designed an ADPCM-family lossy compression algorithm in MATLAB and verified it against hardware and image-quality constraints.

Actual implementation, reasoning and validation: I designed an ADPCM-family MATLAB reference with prediction and adaptive quantization, achieving 3–4x compression within a hard compute budget. A stronger transform codec did not fit. Reference/difficult scenes, error inspection and expert review checked reconstruction before handover to onboard implementers; extra multiple-quantizer details are not invented.

Gap: Multiple distinct quantizers and C++ implementation are not established; flight-software implementation was another team’s responsibility.

Follow-up topics: ADPCM, compute budget, validation

5. Library System

5.1. Developed and maintained backend modules in C for library catalogue management and digital collection workflows, focusing on data processing, validation, and core business logic.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I shared C89 backend responsibility with two other C developers, implementing features, fixes and refactoring for library workflows.

Actual implementation, reasoning and validation: I shared the C89 backend with two other C engineers, implementing features, fixes and refactoring across modules. Scala invoked C behavior and C used Java data services. Logs, integrated builds, review and QA checked user-visible behavior; added S3/digital-object workflows are outside this supported scope.

Gap: Digital-object collection processing as stated in the CV is not specifically supported.

Follow-up topics: C89, library workflows, diagnostics

5.2. Designed and optimized socket-based communication components in C and Java to support concurrent client sessions and data exchange between distributed backend services.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I debugged and changed C, Java and Scala components across inherited custom service interfaces.

Actual implementation, reasoning and validation: I used inherited custom protocols across Scala, C and Java and traced faults through them. A consumer symptom could originate in a C payload or data-service path. Correlated logs and native inspection found the owning layer; design of sockets and concurrent-session architecture is not supported.

Gap: Design and optimization ownership of socket-based components and concurrent sessions is not supported.

Follow-up topics: Cross-service logs, protocol boundaries

5.3. Extended service APIs and Scala endpoints to support evolving catalogue workflows and integration with existing application modules.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I made occasional Scala API and Swagger changes, including requests that invoked C-side behavior.

Actual implementation, reasoning and validation: I added a Scala API request backed by existing C processing and updated Swagger documentation. Reuse avoided duplicated domain logic but required coherent request mapping, return values and errors. Integrated validation and review protected this interface; Scala work remained secondary and task-specific.

Gap: This was secondary, task-specific work, not primary ownership of all API endpoints.

Follow-up topics: Scala, Swagger, C integration

5.4. Integrated AWS S3 object storage through the S3 API to persist digital collection assets, including scanned manuscripts and other large media files, while maintaining bibliographic metadata and object references in relational databases.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I worked with C backend behavior and Java data services using PostgreSQL and MySQL.

Actual implementation, reasoning and validation: Persistence used Java services reaching PostgreSQL and residual MySQL. AWS EC2 provided Linux build/runtime hosts. Neither establishes S3 objects, digital collections or object/reference coordination. No upload, pre-signed access or object-lifecycle result can be attributed; the answer describes actual service/database interaction.

Gap: No evidence of AWS S3 object-storage integration or digital-object reference ownership.

Follow-up topics: Relational services, object-storage theory

5.5. Implemented streaming upload and byte-range download mechanisms for large digital objects, reducing memory consumption and avoiding unnecessary loading of complete files into application memory.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I developed and debugged the C89 backend and followed service requests through logs.

Actual implementation, reasoning and validation: Native buffer corrections and diagnostics are supported, but large-object streaming uploads and byte-range downloads are different unrecorded tasks. gdb/Valgrind explain actual memory work without establishing S3 transfer protocols, retry semantics or measured reduction of transfer memory.

Gap: No evidence of streaming S3 upload or byte-range download implementation.

Follow-up topics: Native diagnostics, streaming theory

5.6. Updated MySQL and PostgreSQL schemas and optimized database queries to improve data retrieval performance when handling large library catalogues.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I integrated application behavior with Java services accessing PostgreSQL and residual MySQL models.

Actual implementation, reasoning and validation: Database migration predated my assignment and administration belonged elsewhere. I connected C behavior with Java data services for PostgreSQL/MySQL and traced persistence symptoms through those interfaces. Personal schema changes, indexes and query-performance improvements are not supported and no speed metric is added.

Gap: Schema updates and query optimization ownership are not evidenced; the migration predated the assignment.

Follow-up topics: Service/database boundary, migrations

5.7. Improved backend data-processing workflows and maintained compatibility with existing legacy application components.

Status: CONFIRMED

Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I implemented focused C backend changes and refactoring while preserving compatibility with Java, Scala and existing workflows.

Actual implementation, reasoning and validation: I changed C89 code while preserving custom inter-service expectations and library workflows. Focused refactoring improved maintainability without assuming a platform rewrite. Original reproduction, adjacent integration/QA scenarios and approval from all added reviewers checked compatibility and the corrected user-visible result.

Gap: The underlying compatibility work is directly supported.

Follow-up topics: C89, compatibility, regression

5.8. Participated in release preparation, deployment workflow improvements, and code reviews to maintain application stability and code quality.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md

Interview answer: I participated in mandatory code review and used Jenkins builds and existing nightly or on-demand deployments for validation.

Actual implementation, reasoning and validation: I used Bitbucket review, Jenkins builds on AWS Linux and nightly/on-demand deployment to developer/QA hosts. All added reviewers approved changes and QA provided regression feedback. This supports release participation and workflow use, not Jenkins administration, infrastructure ownership or evidenced deployment-process redesign.

Gap: Ownership of deployment workflow improvements is not established; infrastructure administration was outside my role.

Follow-up topics: Reviews, Jenkins, QA

6. Corporate System for the Oil and Gas Industry

6.1. Developed and maintained backend components in C++11 for internal corporate workflows and operational data processing in the oil and gas domain.

Status: FACTUAL CORRECTION

Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I implemented and maintained C++17 application features for an oil-and-gas data system during October 2021–January 2022.

Actual implementation, reasoning and validation: I delivered C++17 application changes with occasional JavaScript and MySQL-backed work. Representative input was followed through processing and displayed output, then external QA checked regression. C++11 and the CV's dates/employment framing are factual corrections, not the supported language standard and assignment history.

Gap: The CV says C++11 and 2012–2014; the supported period, standard and junior role differ.

Follow-up topics: C++17, legacy application

6.2. Integrated LevelDB as an embedded, disk-backed key-value storage engine into C++ backend services to persist and index high-frequency telemetry and sensor events locally on disk, complementing relational storage in Microsoft SQL Server.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I worked on C++17 application logic and MySQL-backed sensor-data workflows.

Actual implementation, reasoning and validation: The supported persistence path was relational, especially MySQL. LevelDB integration, local telemetry indexes and embedded key-value ownership are not established. No durability, index or cross-engine coordination test can be claimed; the defensible explanation follows C++ processing and actual relational application behavior.

Gap: No evidence of LevelDB integration, disk-backed indexing or key-value ownership.

Follow-up topics: MySQL, data flow, LevelDB theory

6.3. Optimized LevelDB storage performance by tuning block cache configuration and compaction settings to improve write throughput and maintain efficient data access under sustained ingestion workloads.

Status: NOT SUPPORTED

Summary evidence: No supporting evidence in Summary; adjacent evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I implemented application features and focused legacy-code changes in C++17.

Actual implementation, reasoning and validation: No supported record describes LevelDB cache, compaction or ingestion-throughput tuning. Safe legacy changes and defect fixes are different work. No benchmark, setting or measured gain is invented; storage-engine concepts remain theory rather than evidence of this assignment.

Gap: No evidence of LevelDB block-cache or compaction tuning.

Follow-up topics: Performance measurement theory

6.4. Developed and maintained database access layers, supporting interaction between embedded key-value storage and relational database systems.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I worked with C++ application behavior backed by MySQL and traced values across application layers.

Actual implementation, reasoning and validation: I maintained C++ processing and MySQL-backed behavior, following values through storage and retrieval. Dedicated LevelDB/SQL abstraction or atomic coordination between engines is unsupported. Complete workflow reproduction and external QA validated relational behavior without claiming a cross-engine architecture.

Gap: A dedicated key-value/relational access-layer implementation and LevelDB ownership are not supported.

Follow-up topics: C++, MySQL, data flow

6.5. Maintained MySQL persistence components for auxiliary operational data and application metadata, while Microsoft SQL Server remained the primary relational database for corporate business records.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I worked with MySQL-backed processing workflows; Microsoft SQL Server was also part of the system environment.

Actual implementation, reasoning and validation: MySQL supported the processing workflows I worked on; SQL Server belonged to the wider relational landscape. I checked processed/stored/displayed values, but the exact primary-versus-auxiliary split and independent database-component ownership in the CV are not established by that application work.

Gap: Personal ownership of the MySQL persistence components and the CV’s division of database roles are broader than the record.

Follow-up topics: MySQL, SQL Server, role boundaries

6.6. Supported integration between backend services and the web interface implemented using JavaScript, HTML, and jQuery.

Status: CONFIRMED

Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I occasionally changed JavaScript when a task crossed C++ processing and the user-facing workflow.

Actual implementation, reasoning and validation: I changed JavaScript when a task crossed native processing and presentation. C++ values, MySQL state and displayed behavior formed one workflow, so fixing only one layer was insufficient. Representative input and final output were checked together, followed by external QA regression.

Gap: This was secondary to C++ work.

Follow-up topics: JavaScript, C++ integration

6.7. Refactored existing C++ components, resolved defects, and removed outdated code to improve application reliability and maintainability.

Status: CONFIRMED

Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I implemented C++17 features, corrected defects, refactored inherited code and removed obsolete components.

Actual implementation, reasoning and validation: I simplified C++17 paths and removed obsolete code after reconstructing dependencies. Small changes kept customer workflows reviewable within a sprint. Regression followed original/adjacent C++, MySQL and JavaScript behavior; the outcome was corrected behavior and reduced maintenance surface without an invented reliability percentage.

Gap: The supported work uses C++17, not the CV’s C++11.

Follow-up topics: Legacy refactoring, QA

6.8. Participated in technical task estimation, code reviews, and development planning to support predictable delivery of project functionality.

Status: PARTIALLY CONFIRMED

Summary evidence: Summary/Interview/2021. Oil and Gas Corporate System.md

Interview answer: I worked on assigned C++ changes in an established review and QA process.

Actual implementation, reasoning and validation: I participated in sprint delivery, sized assigned changes and supported reproducible handoff to external QA and bi-weekly customer demos. This supports participation rather than team-level planning ownership or every review activity in the CV. No project-management or predictive-delivery metric is claimed.

Gap: Specific ownership of estimation and development planning on this short assignment is not directly documented.

Follow-up topics: Task scope, review, delivery

3. REQUEST RESPONSIBILITY AND REQUIREMENT COVERAGE

Request item 1. Design and implement new features in Ceph, including RGW, RADOS, RBD and CephFS

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Ceph RGW integration through S3 API
Summary evidence: No supporting evidence in Summary
Assessment: The candidate has never worked in the Ceph codebase or with a Ceph cluster. The closest real evidence is feature development inside large inherited codebases: the Sierra C89 backend and a customized Linphone SDK, where he implemented new SDK-side behavior.
Interview response: I have not developed Ceph features. My relevant experience is implementing features inside large existing C and C++ codebases, including SDK-level changes in a customized open-source SIP stack, and I would approach Ceph the same way: understand the data path and invariants first, then change the narrowest component.

Request item 2. Optimize the performance, scalability and reliability of the storage system

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Ceph performance investigation; Oil and gas, LevelDB tuning
Summary evidence: No supporting evidence in Summary for storage performance work
Assessment: No storage-system tuning, OSD or BlueStore analysis, LevelDB or RocksDB tuning or benchmark campaigns are recorded. Reliability work on the SIP platform, primary/backup failover and failback, is real but is not storage.
Interview response: I have not tuned a storage system. My reliability example is SIP primary/backup failover that I implemented in the SDK, and my performance habit is to measure the actual path before changing it.

Request item 3. Troubleshoot distributed storage issues and debug low-level system behavior

Type: RESPONSIBILITY
Coverage: PARTIALLY COVERED
Related CV item: Library System, backend modules and service communication; SIP platform, target integration
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 01, 03 and 04; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, sections 03 and 04
Assessment: Low-level debugging is directly supported: log-first diagnosis across services and language runtimes, gdb and core dumps on AWS EC2 Linux, Valgrind for invalid-memory and initialization defects in C, and gdbserver on ARM64 targets. The distributed-storage part is not supported.
Interview response: Low-level diagnosis is my strongest area. On a production C platform on AWS Linux, a symptom in Java or Scala often led back to a C root cause, and I worked from correlated logs to gdb, core dumps and Valgrind. I have not diagnosed Ceph or other distributed-storage failures.

Request item 4. Participate in upstream Ceph development and community discussions

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary
Assessment: No upstream open-source contribution is recorded. Public GitHub repositories contain the candidate's own C++20 application and Stroustrup exercises. The customized Linphone SDK work was internal to the customer project.
Interview response: I have not contributed upstream to Ceph. I have maintained customer-specific changes in a customized open-source SDK, so I understand the cost of carrying a fork, but I have not gone through an upstream review process.

Request item 5. Integrate Ceph with Kubernetes through Rook and CSI drivers

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Rook Operator and Ceph CSI for RBD
Summary evidence: No supporting evidence in Summary
Assessment: Kubernetes, Rook and Ceph CSI project experience is not supported by Summary. Interview-theory question banks provide preparation material, not evidence that the candidate has mastered these technologies.
Interview response: I have not deployed Ceph with Rook or configured Ceph CSI. This would be new hands-on work for me.

Request item 6. Monitor and improve system observability using telemetry and metrics

Type: RESPONSIBILITY
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database, Prometheus and Grafana monitoring
Summary evidence: No supporting evidence in Summary for metrics systems
Assessment: Observability in the real record is log-based: service logs on Sierra, application, SIP and system logs and active-proxy diagnostics on the SIP platform. No Prometheus, Grafana, exporters, alerting or dashboards are recorded.
Interview response: My diagnostic work has been log-centred, including adding diagnostics where a state was invisible. I have not built Prometheus metrics or Grafana dashboards.

Request item 7. Plan and execute development tasks using Agile methodologies

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Oil and gas, task estimation and planning; Library System, release preparation
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04
Assessment: Two-week sprints, daily stand-ups, weekly grooming, demos and retrospectives with Jira on Sierra; Asana-based planning on the SIP platform; estimation of own tasks.
Interview response: I have worked in Scrum with two-week sprints, grooming, demos and retrospectives, and I estimate and plan my own work within that process.

Request item 8. Contribute to technical documentation, design reviews and internal knowledge sharing

Type: RESPONSIBILITY
Coverage: COVERED
Related CV item: Library System, code reviews; SIP platform, architecture refactoring
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/Career Overview.md, section 02; Summary/Interview/Recruiter Brief.md, section 06
Assessment: All EPAM and customer reviewers had to approve a change on Sierra; Swagger documentation updates; call/account architecture decisions on the SIP platform; onboarding, 1:1s, development planning and interview preparation as People Lead from October 2025.
Interview response: Review and knowledge sharing are part of my routine: multi-reviewer approval on a production platform, architecture discussions on the embedded project and, since October 2025, mentoring and onboarding as People Lead while remaining hands-on.

Request item 9. Very strong developer with experience across various technical areas

Type: MUST-HAVE, REVISED
Coverage: PARTIALLY COVERED
Related CV item: All CV projects
Summary evidence: Summary/Interview/Career Overview.md, sections 02 to 04
Assessment: Breadth is real and unusual: C89 backend, C++17 backend, C++17 and Qt on embedded Linux with Yocto, SIP and WebRTC, C# and .NET 8 tooling, occasional Java, Scala and JavaScript, and seven years of MATLAB algorithm R&D. The formal grade is middle, not senior, and none of the areas is storage or cloud infrastructure.
Interview response: My profile is broad by design: I have worked across C backend services, C++ on embedded Linux, protocol stacks and Windows tooling, and earlier on aerospace algorithms. The common thread is diagnosing systems where behavior depends on several layers at once.

Request item 10. Development experience in C++

Type: MUST-HAVE, REVISED
Coverage: COVERED
Related CV item: SIP platform; Oil and gas; Library System
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 01; Summary/Interview/2021. Oil and Gas Corporate System.md, section 01; Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/2020-2021. Independent C++ Engineering Projects.md, section 01
Assessment: More than six years of C and C++ practice, five of them commercial: C++17 on the SIP platform and the oil-and-gas system, C89 on Sierra and a published C++20 application.
Interview response: C and C++ are my main languages: C++17 and Qt on embedded Linux most recently, C89 on a large production backend before that, and C++17 in an enterprise data system.

Request item 11. Infrastructure experience

Type: MUST-HAVE, REVISED
Coverage: PARTIALLY COVERED
Related CV item: SIP platform, Yocto and device-side service configuration; Library System, deployment workflow
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04; Summary/Interview/2022-2024. Integrated Library System.md, sections 01 and 03
Assessment: Supported infrastructure-adjacent work: Yocto Kirkstone recipes, packaging and systemd service startup; DHCP, TFTP and SNMP provisioning tooling; daily use of AWS EC2 Linux hosts over SSH; Jenkins and GitLab CI as a user. Data-centre, cloud-platform, storage or Kubernetes operations are not supported.
Interview response: My infrastructure experience is at the Linux system level: building device images with Yocto, defining systemd services, provisioning devices over DHCP and TFTP and debugging services on AWS Linux hosts. I have not operated cloud infrastructure or storage clusters.

Request item 12. Ceph or NetApp storage experience, including some Ceph experience

Type: MUST-HAVE, REVISED
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Neither Ceph nor NetApp is recorded. This is the decisive gap for both versions of the request.
Interview response: I do not have hands-on Ceph or NetApp experience. I would need to learn the storage stack on the project, starting from the client's own deployment.

Request item 13. Kubernetes experience

Type: MUST-HAVE, REVISED
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary; Summary/Interview/Certificates and Continuing Education.md records Docker as coursework only
Assessment: No project use of Kubernetes is recorded. Preparation material does not establish the candidate's current theoretical proficiency.
Interview response: I have not run workloads or storage on Kubernetes in a project. I would need to build practical experience with the team's deployment and operating model.

Request item 14. Senior engineering level

Type: MUST-HAVE, SHARED VACANCY CONDITION
Coverage: PARTIALLY COVERED
Related CV item: Professional summary
Summary evidence: Summary/Interview/Recruiter Brief.md, sections 06 and 07; Summary/Interview/Career Overview.md, section 02
Assessment: The formal grade is middle; senior was never awarded. Scope beyond the title includes design decisions and review on the embedded product and People Lead responsibilities for a sub-group that grew from four to six engineers, with roughly 80% hands-on delivery.
Interview response: My grade is middle. My scope has included architecture decisions on an embedded product and, since October 2025, People Lead responsibilities for an internal group of four to six engineers while staying primarily hands-on.

Request item 15. Strong proficiency in C++ and Python, five or more years

Type: MUST-HAVE, ORIGINAL
Coverage: PARTIALLY COVERED
Related CV item: Skills matrix: C++ 11 years, Python 2 years
Summary evidence: Summary/Interview/Recruiter Brief.md, section 07; occasional Python use in Summary/Interview/Vacancy Preparation/Vacancy Preparation. FinDev Senior C++ Engineer, Electronic Bond Trading/Vacancy Preparation. FinDev Senior C++ Engineer, Electronic Bond Trading.md, section 03
Assessment: C++17 work on the embedded and oil-and-gas projects and an independent C++20 application are directly supported. The C89 backend assignment is relevant systems-programming experience, but combining C and C++ duration does not by itself demonstrate five years of proficiency specifically in C++. Five years of Python proficiency and production Python are not established, so the combined requirement is not fully met.
Interview response: C and C++ are my primary languages with more than six years of practice. Python I have used occasionally for scripts, not as a production language.

Request item 16. Hands-on experience with Ceph: RGW, RADOS, RBD or CephFS

Type: MUST-HAVE, ORIGINAL
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Same gap as item 12, stated at component level.
Interview response: I have not worked hands-on with RGW, RADOS, RBD or CephFS.

Request item 17. Solid understanding of Linux internals: I/O, memory management and threading

Type: MUST-HAVE, ORIGINAL
Coverage: PARTIALLY COVERED
Related CV item: Library System; SIP platform
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 03 and 04; Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04
Assessment: User-space Linux depth is supported: native memory defects in C with fixed-size buffers, Valgrind, core-dump analysis, processes and logs on Linux hosts, QThread and queued connections across thread boundaries, systemd and an embedded Linux image. Kernel I/O paths, page cache, block layer, direct I/O and NUMA or memory-management tuning are not supported.
Interview response: I work comfortably in Linux user space: native memory defects, core dumps, Valgrind, threads and cross-thread event delivery, services and images. Kernel-level storage I/O tuning I would treat as an area to deepen.

Request item 18. Familiarity with Kubernetes, Rook and Ceph CSI drivers

Type: MUST-HAVE, ORIGINAL
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Same gap as items 5 and 13.
Interview response: I have not used Kubernetes, Rook or Ceph CSI on a project; these would be new practical areas for me.

Request item 19. Experience with Git, GitHub and CI/CD pipelines

Type: MUST-HAVE, ORIGINAL
Coverage: COVERED
Related CV item: Source control systems: Git, GitLab, Bitbucket
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04; Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/Recruiter Brief.md, section 09
Assessment: Git across all commercial projects; GitLab with merge requests and GitLab CI; Bitbucket with Jenkins builds on AWS Linux and nightly or on-demand deployment; public GitHub repositories. Ownership of CI infrastructure is not established.
Interview response: I use Git daily with merge-request review and have worked with GitLab CI and Jenkins pipelines; I have used them rather than owned their infrastructure.

Request item 20. Exposure to large-scale infrastructure or cloud-native environments

Type: MUST-HAVE, ORIGINAL
Coverage: PARTIALLY COVERED
Related CV item: Library System; Oil and gas
Summary evidence: Summary/Interview/2022-2024. Integrated Library System.md, sections 01 and 02; Summary/Interview/2021. Oil and Gas Corporate System.md, section 01; Summary/Interview/Recruiter Brief.md, section 08
Assessment: Development on production systems hosted on AWS EC2 for a library-software vendor whose installed customer base served more than 9,000 libraries, and on Microsoft Azure for an oil-and-gas corporate system. The library count describes the vendor's customer base, not the deployment scale of the specific Sierra platform or the candidate's services. These are cloud-hosted, not cloud-native Kubernetes environments.
Interview response: I have developed and debugged services running on AWS and Azure for large production systems, but not in a Kubernetes-based cloud-native platform.

Request item 21. Proficiency with observability tools such as Prometheus and Grafana

Type: MUST-HAVE, ORIGINAL
Coverage: NOT COVERED
Related CV item: Remote Sensing Satellites Database
Summary evidence: No supporting evidence in Summary
Assessment: Same gap as item 6.
Interview response: I have not used Prometheus or Grafana in a project.

Request item 22. English at B2+ level

Type: MUST-HAVE, SHARED VACANCY CONDITION
Coverage: PARTIALLY COVERED
Related CV item: Language proficiency: English B2+
Summary evidence: Summary/Interview/Recruiter Brief.md, section 03
Assessment: English has been the professional working language since 2021 with distributed teams in the US, India and Europe. Summary records B2 as the defensible level, with course certificates through B1 and a B2 course exam result of 60.5/100.
Interview response: English has been my daily working language since 2021, including direct technical communication with customer teams. I would describe my level as B2.

Request item 23. EU location, CET working hours and at least 30 hours per week

Type: MUST-HAVE, SHARED VACANCY CONDITION
Coverage: PARTIALLY COVERED
Related CV item: No direct match
Summary evidence: Summary/Interview/Recruiter Brief.md, sections 02 and 07; Summary/Interview/Career Overview.md, section 02
Assessment: The candidate is available full time, works in a CET-compatible time zone and has been between assignments since September 2026. Summary records him as a Belarusian citizen in Minsk, relocating to Warsaw with a Polish national D visa valid from 26 September 2026 to 25 September 2027. The EU-location requirement is satisfied only once he works from Poland.
Interview response: I am available full time in CET hours. I hold a Polish national D visa and worked in Warsaw for two years before; my working location for the project would be Poland.

Request item 24. Contributions to open-source projects, especially Ceph

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: No direct match
Summary evidence: No supporting evidence in Summary for open-source contribution; Summary/Interview/Recruiter Brief.md, section 09, records own public repositories only
Assessment: Own public repositories are not open-source project contributions.
Interview response: My public code is my own C++ projects; I have not contributed to an external open-source project.

Request item 25. Experience with cloud platforms: AWS, Azure or OpenStack

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: Library System, AWS; Cloud skills
Summary evidence: Summary/Interview/Certificates and Continuing Education.md, section 06; Summary/Interview/2022-2024. Integrated Library System.md, section 01; Summary/Interview/2021. Oil and Gas Corporate System.md, section 01
Assessment: Developer use of AWS EC2 Linux hosts and of an Azure-hosted system; two AWS digital training badges from May 2024, not certifications. No OpenStack.
Interview response: I have worked on systems hosted on AWS and Azure as a developer and hold two AWS training badges. I have not worked with OpenStack.

Request item 26. Familiarity with performance profiling tools and storage benchmarks

Type: NICE-TO-HAVE
Coverage: PARTIALLY COVERED
Related CV item: SIP platform, Valgrind and gdb
Summary evidence: Summary/Interview/2025-2026. Embedded SIP Desk Phone Platform.md, section 04; Summary/Interview/2022-2024. Integrated Library System.md, section 04
Assessment: Valgrind and debugger-based diagnosis are supported; dedicated profilers such as perf and storage benchmarks such as fio, rados bench or COSBench are not.
Interview response: I use Valgrind and gdb regularly for diagnosis. Storage benchmarking tools would be new for me.

Request item 27. Knowledge of S3 and Swift protocols and object-storage semantics

Type: NICE-TO-HAVE
Coverage: NOT COVERED
Related CV item: Library System, AWS S3 integration; Remote Sensing Satellites Database, Ceph RGW through S3 API
Summary evidence: No supporting evidence in Summary
Assessment: The S3 integration and pre-signed URL claims are CV-only. AWS coursework covers S3 conceptually.
Interview response: I know the S3 model from AWS training, but I have not integrated S3 or Swift in a project.
