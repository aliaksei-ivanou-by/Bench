SELF INTRO

DOCUMENT INFORMATION

Request ID: fake1
Candidate: Alex I.
Target role: C++ Software Engineer, generic positioning because no request was provided
CV source: !MODIFIED Aliaksei Ivanou (13, C++).pdf
Source request: Not provided
Preparation language: English
Delivery format: Domain-based full spoken version with a detailed current-project section
Estimated duration: 5–6 minutes
Document status: Interview-ready

PURPOSE

This is a domain-based opening self-introduction for a C++ Software Engineer interview. It first presents the candidate’s experience by domain with representative projects and then expands the current Cloud Native Encoding Platform project.

TARGET POSITIONING

Alex is a software engineer with more than thirteen years of commercial experience and a background in both hardware and software development. His main technical areas are C and C++ systems, cloud-native media processing, enterprise and legacy platforms, industrial software, and MATLAB-based image-processing applications.

His domains include telecommunications and video delivery, library systems, oil and gas, personal-finance software, industrial 3D reconstruction, UAV systems, and aerospace and Earth-observation systems.

INTERVIEW SCRIPT

Hello, my name is Alex.

I am a software engineer with more than thirteen years of commercial experience and a background in both hardware and software development. My main specialization is C and C++ software development, and I also have extensive MATLAB experience in algorithms and image-analysis applications.

The easiest way to describe my background is by the domains in which I have worked.

The first domain is cloud-native video processing and delivery, which is also my current area. Since April 2025, I have worked as a Streaming Engineer and Architect on a distributed microservices platform for real-time video encoding and delivery. The platform supports live and video-on-demand content, is designed for more than one hundred thousand concurrent users across three availability zones, and combines C++ for performance-critical services with Java and Kotlin for development speed. Its services are cloud-agnostic and support multi-cloud, hybrid-cloud and on-premise configurations.

The second domain is library systems. From March 2022 to April 2025, I worked on a large library-management platform with more than forty years of operational history. The system combined C, Java and Scala and had to support high data volumes and complex workflows while remaining compatible with legacy components. I worked on complex defects, performance improvements, socket-based features, C development, Scala API refactoring, AWS delivery pipelines, database changes, task estimation, code review and legacy modernization.

The third domain is oil and gas. In 2021, I worked on a corporate system built with C++17, JavaScript, HTML and jQuery, with Microsoft SQL Server, MySQL and Nginx. My responsibilities included backend implementation, feature development, task estimation, defect correction, performance work, technical-debt reduction and removal of obsolete legacy components.

The fourth domain is desktop and financial software. From July 2020 to July 2021, I developed a home-accounting application in C++. I used FLTK for the graphical interface, SQLite for transaction storage, Google Test for testing, plog for diagnostics and CMake for build automation.

The fifth domain is industrial 3D reconstruction. In 2020, I developed software that generated 3D models from data captured by multiple 2D laser sensors. I used C++, Point Cloud Library and Open3D for point-cloud processing, visualization and analysis, with Visual Studio as the main development and debugging environment.

The sixth domain is UAV and aerospace systems. For the UAV project, I developed MATLAB modules for digital image processing, including debayering, image-format conversion, image stabilization and image fusion. For Earth-observation systems, I worked on a Ruby on Rails and PostgreSQL database of remote-sensing satellites and on C++ and MATLAB software for satellite-image analysis, linear-resolution measurement, image-quality processing, quantization-range prediction and ADPCM-based compression.

I would now like to explain my current cloud-native encoding project in more detail.

The product is a distributed platform for real-time video encoding and delivery. It handles both live streams and video-on-demand content, with low latency and high reliability as key product requirements. The codebase follows a hybrid language model: C++ is used for performance-critical services, while Java and Kotlin are used where development speed is more important. The services are designed to remain cloud-agnostic, so the same platform can work with multiple public clouds and on-premise infrastructure.

One of my main architecture tasks was replacing legacy JSON-RPC inter-process communication with gRPC and Protobuf. This reduced serialization overhead by approximately forty percent and reduced request size by approximately sixty percent. The change improved the efficiency of communication between services and established a typed contract for service interaction.

Another major area was delivery to cloud storage. I analyzed the relationship between connector cost and upload speed so that the platform could select the best fit for customer preferences. I also improved predictable segment-upload service levels from ninety percent to 99.9 percent for cloud storage. The supported output ecosystem included Amazon S3, Google Cloud Storage, Azure Blob Storage and Akamai MSL4 and MSL5.

For observability, I architected an instrumentation and monitoring framework for the C++ encoder. It supported Google Cloud, Prometheus and OpenTelemetry. I also instrumented FFmpeg libavfilter pipelines, and this work reduced end-to-end latency by four seconds. The wider environment included Grafana and cloud monitoring services, so performance and delivery behavior could be observed across the processing path.

I also worked on media-format and streaming workflows. I implemented end-to-end conversion from CEA-608 and CEA-708 captions to TTML in the IMSC profile and WebVTT. I diagnosed HLS and DASH manifest misalignment in Live-to-VOD workflows and prevented orphan segments when an input was removed. I implemented encoder recovery for output outages across S3, Google Cloud Storage, Azure Blob Storage and Akamai.

Another part of my work focused on developer productivity. I developed AI skills for the team to support faster feature delivery and incident resolution. I integrated mcp-on-demand, graphify and rag-code-mcp into AI workflows to improve response quality and reduce token consumption. I also owned and maintained an internal Go fork of rag-code-mcp and added support for C, C++, Java and Kotlin codebases.

The current project brings together the themes that have appeared throughout my career: performance-sensitive C++, distributed-system integration, reliability, observability, data formats, cloud services and practical modernization of existing systems. I am most interested in work where performance, architecture and operational reliability have to be solved together rather than in isolation.

EXPECTED FOLLOW-UP TOPICS

• Why JSON-RPC was replaced with gRPC and Protobuf and how the forty-percent and sixty-percent improvements were measured.

• How cloud connector cost and upload speed were compared.

• What predictable segment-upload SLA means and how the change from ninety percent to 99.9 percent was validated.

• The architecture of the C++ encoder instrumentation and monitoring framework.

• Which FFmpeg libavfilter stages contributed to the four-second latency reduction.

• How CEA-608 and CEA-708 captions were converted to TTML and WebVTT.

• Failure detection, retry, state recovery and consistency during cloud-output outages.

• HLS and DASH manifest alignment in Live-to-VOD workflows.

• The purpose of the internal rag-code-mcp fork and how language support was implemented in Go.

• How C++, Java and Kotlin responsibilities were divided across the platform.
