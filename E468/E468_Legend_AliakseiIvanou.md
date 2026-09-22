PROJECT LEGEND

DOCUMENT INFORMATION

Request ID: E468
Candidate: Aliaksei Ivanou
Target role: Senior C++ Developer
CV source: E468 Aliaksei Ivanou (13, C++).pdf
Source request: E468_Request_AliakseiIvanou.md
Source profile: E468_Profile_AliakseiIvanou.md
Source analysis: E468_Request_Analysis_AliakseiIvanou.md
Preparation language: English
Document status: Interview-ready

PURPOSE

This document contains the detailed project narratives behind the E468 CV. It is reference material for follow-up questions, not one continuous speech.

HOW TO USE THE LEGEND

Start with the short project summary, then expand the technical contribution, result, and scope boundary that match the interviewer’s question. The request profile is the source of truth for dates, roles, and restricted claims.

PRIVATE CONSISTENCY NOTES

• Use past tense for the completed embedded SIP assignment.
• The library assignment ended in April 2024, not April 2025.
• Home accounting was an independent project, not employment.
• Fourteen-plus years refers to overall software engineering and R&D experience.

PROJECT 1. SIP DESK PHONE PLATFORM FOR AUDIO AND VIDEO COMMUNICATION

CV period: May 2025 – present
Verified period: May 2025 – August 2026
CV role: Senior Software Engineer
Verified role: C++ Software Engineer; senior individual contributor with a separate internal technical-lead component
Project status: FACTUAL CORRECTION

Short project summary
My most recent assignment was an embedded platform for SIP desk phones. The product family included devices with and without a camera, so the software supported both audio-only and video communication.
The platform covers the complete phone workflow: SIP registration, incoming and outgoing calls, call hold and transfer, conferences, phonebook access, direct IP dialing, device configuration, and automatic provisioning.
The product consists of several parts:
A native application running on the phone.
An embedded Linux system built with Yocto.
SIP and multimedia components based on Linphone SDK, Qt Multimedia, libwebrtc, libmediasoupclient, and related libraries.
WebRTC conferencing functionality.
A web management interface.
A Windows-based provisioning utility.
Device-side services and configuration.
The target devices are based on the NXP i.MX platform. The native application is mainly written in C++17 and uses Qt 5.15 and Qt Widgets.
My role and ownership
I worked mainly on the native C++ and Qt application and its call-handling logic. My responsibility was to make the call flow easier to maintain and to ensure that the UI correctly reflected the actual state of calls and media sessions.
I also worked with Linphone SDK integration, video and conference scenarios, phone-side WebRTC functionality, provisioning tools, and embedded Linux integration.
Call-flow refactoring
One of the main technical problems was that the legacy call-flow code mixed several responsibilities:
UI rendering.
Call state management.
User actions.
SIP events.
Media negotiation.
Direct calls to Linphone SDK.
Qt signals and slots.
Because these responsibilities were tightly coupled, even a small change could affect several call scenarios. For example, changing the behavior of a held call could also influence the active video window or the controls displayed for a second call.
I worked on an incremental refactoring of this logic. The goal was not to rewrite the entire application because the product already had many working features and existing UI behavior had to be preserved.
I separated the logic into clearer areas:
Domain and call-state logic.
Presentation logic.
Processing of user actions.
Media-related logic.
Integration with Linphone SDK.
I had to preserve compatibility with the existing QObject signals and the existing Qt Widgets UI. This allowed us to improve the internal structure without introducing a large risky migration.
Video-call edge cases
Another important part of my work was improving the behavior of video calls and conferences.
The difficult cases were not basic one-to-one calls but combinations of several events, such as:
The active call being placed on hold.
A second call arriving while another call is active.
The remote side ending the call.
Switching the active video stream.
Updating the video layout during a conference.
Removing outdated overlays and controls.
Synchronizing the UI with the actual media state.
The main challenge was that the UI state, call state, and media state could change independently. A SIP call could already be terminated while an old video widget was still displayed, for example. I worked on making these transitions more predictable and ensuring that the UI was updated when the underlying call or media state changed.
SIP and Linphone SDK
The application uses Linphone SDK and liblinphone for SIP functionality.
I worked on extending and customizing the backend integration to support SIP failover and backup-server connectivity. The purpose was to improve device reliability when the primary SIP server was unavailable.
The application had to correctly manage server connectivity and keep the rest of the call logic consistent with the current registration state. My work was focused on integrating this behavior into the existing application rather than replacing the complete SIP stack.
If this subject comes up during an interview, I explain that the main goal was to make the device more resilient while keeping the failover logic isolated from the presentation layer.
WebRTC conferences
I also participated in the WebRTC conferencing part of the product. The project used mediasoup and libmediasoupclient.
My work covered the client-side UI and signaling flows, including:
Creating and joining a conference.
Processing incoming conference invitations.
Displaying the participant list.
Adding participants by SIP address, IP address, or phonebook entry.
Displaying conference status.
Implementing the conference control panel.
Managing video-tile layouts.
Controlling audio and video devices.
The main challenge was coordinating signaling events, participant state, media streams, and the Qt UI. The interface needed to react correctly when participants joined or left, when media became available, or when the active stream changed.
Provisioning utility
The product ecosystem also includes a WinForms configuration utility.
I participated in migrating this tool from .NET Framework 4.8 to .NET 8. The migration included modernizing the project structure and unifying project-file formats used by different device-related tools.
The provisioning workflows involved:
SNMP for device management.
DHCP for network configuration and discovery.
TFTP for transferring configuration data.
SQLite for local data storage.
This task was different from my main C++ work, but it gave me a broader understanding of how the complete device ecosystem was configured and maintained.
Embedded Linux integration
I collaborated with engineers working on Yocto, BitBake, systemd, and the NXP i.MX target platform.
My involvement included application integration, dependencies, build configuration, and device-side service configuration. I was not responsible for the entire Linux distribution, but I worked with the embedded environment when application changes required changes in the image, services, hardware access, or runtime configuration.
Outcome and main lesson
This project combines several areas: modern C++, legacy Qt code, SIP, WebRTC, multimedia, embedded Linux, and hardware integration.
My main contribution is making complex call scenarios more reliable and making the existing code easier to understand and extend without breaking the behavior of deployed devices.

PROJECT 2. INTEGRATED LIBRARY SYSTEM

CV period: March 2022 – April 2025
Verified period: March 2022 – April 2024
CV role: Senior Software Engineer
Verified role: Junior at entry; promoted to middle grade in May 2022; one of three C developers
Project status: FACTUAL CORRECTION

Short project summary
This was a large library management system with more than forty years of development history. It was used by different clients around the world and had to support large amounts of library and catalog data.
Because of its long history, the system was not based on a single technology. It combined:
C for important core functionality.
Java 11 for some application components.
Scala for API-related functionality.
MySQL and PostgreSQL databases.
Socket-based communication.
Existing Jenkins builds and AWS-hosted Linux deployment environments.
A major project requirement was to continue developing the product while maintaining compatibility with existing components and workflows.
My role and ownership
I joined the project at junior grade, was promoted to middle grade in May 2022, and shared responsibility for the C89 backend as one of three C developers.
My responsibilities included:
Investigating and fixing complex defects.
Developing new functionality.
Improving performance.
Working across established inter-service request and response paths.
Implementing a targeted Scala API request and Swagger integration backed by C processing.
Implementing and debugging PostgreSQL- and MySQL-backed application behavior.
Using existing Jenkins and AWS-hosted Linux build and deployment environments.
Estimating tasks.
Conducting code reviews.
Cooperating with the client’s engineering team.
Working with the legacy C codebase
A large part of my work involved understanding code that had been developed and modified over many years.
The main difficulty in this type of system is that business behavior is often distributed across several functions, modules, database operations, and communication layers. A change that looks local can affect older workflows or clients.
When investigating an issue, I first tried to reproduce it and determine whether it came from business logic, data handling, socket communication, or an integration boundary. I used debugging and logging information to trace the execution path and understand the existing behavior before making a change.
The objective was usually to make a focused and compatible modification instead of redesigning a large part of the product.
Cross-service functionality
I implemented and debugged features across established request and response paths spanning Scala APIs, C services, Java data services, and database-backed behavior.
The strongest documented contribution was cross-component application work rather than design of the low-level socket transport. I correlated logs, added focused diagnostics, and corrected the component that owned the root cause.
Performance and defect investigation
I worked on performance improvements and complex production-related defects.
For performance tasks, I investigated where time or resources were being spent before changing the implementation. Depending on the problem, the cause could be inefficient processing, repeated operations, unnecessary data access, or interaction between several legacy components.
Because the system was mature, every optimization had to preserve the established business behavior. A technically faster solution was not acceptable if it changed the expected result or broke compatibility.
Scala API contribution
I implemented a targeted Scala API request, exposed it through Swagger, mapped its data, and connected it to established C-side processing.
This was a specific cross-language feature rather than broad ownership or refactoring of the Scala architecture. My primary responsibility remained the C89 backend.
Database-backed behavior
I worked with PostgreSQL and MySQL through application features and cross-service data paths. I changed the application-side mapping or feature logic required by assigned tasks and validated the complete workflow.
Database administration and broad migration ownership were outside my role. Any table change must be described through a concrete task I personally handled.
AWS-hosted build and deployment
I compiled, deployed, validated, and diagnosed changes in existing AWS-hosted Linux environments using Jenkins builds, nightly and on-demand deployments, SSH, logs, gdb, and core dumps.
I did not administer AWS, own Jenkins, or automate the CI/CD platform.
Collaboration and code review
I estimated development tasks and participated in planning. For legacy tasks, estimation required time not only for implementation but also for investigation, compatibility checks, and review.
I conducted code reviews for both my immediate team and the client’s team. I checked correctness, readability, compatibility with existing code, and possible side effects. Code review was also an important method of sharing knowledge about older areas of the system.
Outcome and main lesson
The main value of this project was learning how to safely develop a large, mature product. My strongest contribution was the ability to investigate unfamiliar legacy code, find the real source of a problem, and introduce compatible changes across C, Scala, databases, and communication components.

PROJECT 3. CORPORATE SYSTEM FOR THE OIL AND GAS INDUSTRY

CV period: October 2021 – December 2021
Verified period: October 2021 – December 2021
CV role: Software Engineer
Verified role: Junior C++ Software Engineer
Project status: CONFIRMED — NARROWER SCOPE

Short project summary
This was a corporate system for internal use in the oil and gas industry. It had a C++17 backend and a web-based frontend built with JavaScript, HTML, and jQuery.
The application ran in a Windows environment. It used MySQL and Microsoft SQL Server for data storage, Nginx as part of the server environment, CMake for builds, and Git and Bitbucket for version control.
My role and ownership
I joined an existing project for a relatively short assignment. My primary responsibility was backend development in C++17.
My tasks included:
Implementing backend functionality.
Supporting project milestones.
Investigating and fixing defects.
Optimizing existing code.
Reducing technical debt.
Removing outdated legacy components.
Estimating assigned tasks.
Since this was a short engagement, I focused on understanding the relevant parts of the existing system quickly and delivering targeted changes.
Working with the existing application
The system already had established workflows and integrations, so changes had to remain compatible with the frontend and database layer.
When implementing a backend change, I considered:
The input received from the frontend.
The C++ business logic.
Database operations.
Error handling.
The format of the result returned to the caller.
I also removed obsolete components where they were no longer needed. The purpose was to simplify maintenance and reduce the risk associated with unsupported code.
Outcome and main lesson
This project strengthened my ability to join an existing product, learn its structure quickly, and contribute within a limited period. It also gave me additional experience with C++17 backend development in a Windows-based corporate environment.

PROJECT 4. HOME ACCOUNTING SOFTWARE

CV period: July 2020 – July 2021
Verified period: May 2020 – September 2021; application started in July 2020
CV role: Software Engineer
Verified role: Sole designer and developer; independent project, not employment
Project status: FACTUAL CORRECTION

Short project summary
This was a desktop application for personal financial accounting. It allowed users to record and manage financial transactions such as bills, receipts, and credit-card operations.
The main technologies were:
C++.
FLTK for the graphical interface.
SQLite for local storage.
CMake for the build system.
Google Test for testing.
plog for logging.
Visual Studio as the main development environment.
My role and ownership
I developed functionality for entering, storing, and reviewing financial transactions.
The application followed a traditional desktop structure:
The FLTK UI collected user input.
Application logic validated and processed the data.
SQLite stored transaction records.
The UI displayed the stored information and financial results.
My work included connecting the UI with the application and persistence logic, handling transaction data, and making the application convenient for regular use.
SQLite integration
SQLite was a good fit because the application needed reliable local storage without a separate database server.
I worked on storing and retrieving transaction data and ensuring that the application could access the required records efficiently. It was important to keep the database interaction separated from the UI so that presentation changes did not directly affect storage logic.
Testing and diagnostics
Google Test was used to verify application behavior. The most suitable areas for automated testing were business logic and data-processing operations that did not depend directly on graphical widgets.
plog was used for error and diagnostic logging. This helped identify failures in data processing and database operations.
CMake provided a repeatable build process and simplified the management of the application, tests, and external dependencies.
Outcome and main lesson
This project gave me complete experience with a standalone C++ desktop application: UI development, business logic, local database integration, build configuration, automated testing, and diagnostics.

PROJECT 5. 3D RECONSTRUCTION SOFTWARE FOR INDUSTRIAL APPLICATIONS

CV period: March 2020 – May 2020
Verified period: March 2020 – May 2020
CV role: Software Engineer
Verified role: C++ Software Engineer in a product-company R&D group
Project status: CONFIRMED

Short project summary
The purpose of this project was to generate 3D models using data received from multiple 2D laser sensors.
Such software can be used in industrial inspection, manufacturing, robotics, and quality-control systems where accurate spatial information is required.
The main technologies were:
C++.
Point Cloud Library, or PCL.
Open3D.
Visual Studio.
Git.
My role and ownership
I worked on software components responsible for processing laser-sensor data and representing it as a 3D model.
PCL was used for operations on point-cloud data. Open3D was used for visualization and analysis of the generated result.
The general data flow was:
Receive data generated by the 2D laser sensors.
Convert or prepare it for point-cloud processing.
Process and combine the available spatial data.
Generate a representation of the 3D object or scene.
Visualize the result for inspection and analysis.
My work focused on implementing and integrating processing and visualization functionality. I also used Visual Studio for debugging and performance investigation.
Technical challenge
The project had to process data from several sensors and produce a consistent 3D representation. The important concerns were the correctness of the input data, efficient point-cloud handling, and a clear visualization of the result.
Since this was a short specialized project, I describe my role as contributing to the processing pipeline rather than claiming ownership of the entire reconstruction algorithm or sensor-calibration system.
Outcome and main lesson
This project gave me practical experience with 3D data structures, point-cloud processing, specialized C++ libraries, and industrial sensor data.

PROJECT 6. SOFTWARE MODULES FOR UAV SYSTEMS

CV period: August 2018 – December 2019
Verified period: Workstream within continuous August 2012 – January 2020 employment
CV role: Software Engineer
Verified role: Research and design engineer working primarily in MATLAB
Project status: FACTUAL CORRECTION

Short project summary
This project involved software and algorithms for processing photo and video data received from optical sensors used in unmanned aerial vehicles.
The objective was to improve image quality, compatibility, stability, and the usefulness of data received from the sensors.
My main development environment was MATLAB, with PostgreSQL used in the wider project environment.
My role and ownership
I developed several image-processing modules:
A debayer algorithm.
Image-format conversion tools.
An image-stabilization algorithm.
An image-fusion algorithm.
Debayer processing
Some cameras produce raw data using a Bayer color-filter pattern. Such input does not directly contain a complete RGB value for every pixel.
I implemented a debayer-processing module that converted raw sensor data into a full-color image. The main objective was to reconstruct the missing color components while preserving image detail and avoiding unnecessary visual artifacts.
Format conversion
Different modules and external systems could require different image formats.
I developed conversion tools that allowed image data to be transformed into the required representation. This improved compatibility between data sources, processing algorithms, and downstream systems.
The important aspects were preserving the image dimensions, channel information, and required data precision during conversion.
Image stabilization
UAV images can contain motion caused by the movement and vibration of the platform.
I worked on an image-stabilization algorithm intended to reduce visible motion and improve the clarity of video data. At a high level, the process involved analyzing changes between frames and applying correction to reduce unwanted movement.
I would only provide exact details about the transformation model or feature-detection method if they match the real implementation.
Image fusion
I also worked on combining information received from multiple sensors.
The purpose of image fusion was to produce a more informative result with improved detail or contrast. The algorithm needed to align the available inputs and combine useful information without introducing unnecessary artifacts.
Outcome and main lesson
This project developed my experience in practical image-processing algorithms and working with real sensor data, where noise, motion, image formats, and data quality must all be considered.

PROJECT 7. REMOTE-SENSING SATELLITE DATABASE

CV period: March 2016 – March 2017
Verified period: Workstream within continuous August 2012 – January 2020 employment
CV role: Software Engineer
Verified role: Research and design engineer with secondary web and database responsibility
Project status: FACTUAL CORRECTION

Short project summary
This project was a database and web application for storing detailed information about Earth-observation satellites.
The system allowed users to access, search, and manage satellite specifications. The main technologies were:
Ruby.
Ruby on Rails.
PostgreSQL.
Microsoft Access for legacy data.
My role and ownership
I worked on three main areas:
The Ruby on Rails web interface.
PostgreSQL database design and optimization.
Integration and migration of legacy data from Microsoft Access.
Web interface
The web interface allowed users with different levels of technical knowledge to view and manage satellite information.
I implemented application functionality that connected user actions in the web interface with the underlying data stored in PostgreSQL.
PostgreSQL
The satellite records contained detailed technical characteristics, so the database needed a structure that supported both data management and efficient retrieval.
I worked on the PostgreSQL schema and queries used to store and search this information. The objective was to keep the data organized and make commonly used operations efficient.
Legacy-data support
Some existing information was stored in Microsoft Access.
I worked on compatibility and data migration between the legacy source and PostgreSQL. This required understanding differences in schemas and data formats and ensuring that important information was preserved during the transition.
Outcome and main lesson
This project expanded my experience beyond C++ and algorithms. It gave me practical exposure to web development, relational database design, legacy-data migration, and user-facing information systems.

PROJECT 8. SATELLITE EARTH-OBSERVATION IMAGE PROCESSING SOFTWARE

CV period: August 2012 – March 2016
Verified period: Selected workstream within continuous August 2012 – January 2020 employment
CV role: Software Engineer
Verified role: Research and design engineer; primary algorithm environment was MATLAB
Project status: FACTUAL CORRECTION

Short project summary
This was my first major software and algorithm R&D period and the foundation of my image-processing experience.
The software contained a set of modules for processing and analyzing images received from Earth-observation satellites. The functionality included:
Brightness normalization.
Optical-defect correction.
Linear-resolution measurement.
Sharpness analysis.
Quantization-range prediction.
Image compression based on ADPCM.
The primary algorithm environment was MATLAB. Supporting tools and technologies included PostgreSQL, Microsoft Access, Systems Tool Kit, Jira, and project-specific implementation and documentation tooling.
My role and ownership
I worked on the development, investigation, and verification of image-processing algorithms.
I designed, implemented, and verified the algorithms in MATLAB and supported handover to the engineers responsible for onboard or operational implementation. I did not own the complete flight-software platform.
Brightness normalization and optical correction
Images or frames received from a satellite can have different brightness levels or optical distortions.
I developed algorithms that normalized brightness across multiple frames and reduced visible inconsistencies. The objective was to produce a more uniform image and improve the quality of further analysis.
I also worked on eliminating optical defects between frames. This was important when multiple frames had to be compared or combined.
Linear-resolution measurement
I developed software for evaluating the linear resolution of satellite images using the sharp-edge method.
The general idea was to analyze how the imaging system represented a transition between dark and bright areas. A perfectly sharp edge in the observed scene becomes less sharp in the captured image. By analyzing this transition, the software could estimate the effective imaging resolution.
I also developed functionality for evaluating image sharpness and edge clarity. These measurements helped assess the quality and performance of the imaging system.
Image-type prediction and adaptive quantization
Another task was classifying remote-sensing scene content and adapting the quantization strategy to improve image quality at a fixed compression ratio and computation budget.
Different scene types, such as water, agriculture, forest, urban texture, and cloud, have different contrast and spatial-frequency characteristics. A fixed quantizer wastes bits in some scenes and damages useful detail in others. I implemented image-type prediction and adaptive quantization and compared the result with the previous approach on reference imagery.
The strongest documented automation result was automated linear-resolution assessment, which replaced a manual expert workflow with repeatable software-generated measurements.
ADPCM compression
I designed and implemented an image-compression algorithm based on Adaptive Differential Pulse-Code Modulation.
Instead of encoding every pixel value independently, the algorithm worked with differences between values and adapted the quantization process to the data.
The implementation supported multiple quantizers, allowing the compression behavior to be adjusted for different input characteristics and data-size requirements.
The main balance was between:
Compression ratio.
Reconstructed image quality.
Data range.
Computational complexity.
Supporting tools and data
PostgreSQL and Microsoft Access were used for related data storage. Systems Tool Kit was used for satellite and Earth-observation planning tasks, and Jira supported task tracking.
Outcome and main lesson
This project gave me a strong foundation in algorithm development. I learned how to move from an instrument-level requirement to implementation and experimentation in MATLAB, verification using real imagery, formal documentation, and handover to the engineers responsible for operational or onboard implementation.

FINAL INTERVIEW POSITIONING

How the projects connect

The career progression runs from measurement and image-processing R&D through industrial C++ and enterprise legacy systems to embedded C++ and Qt product development. The common themes are diagnosis across layers, safe change in inherited systems, and engineering under performance, compatibility, or hardware constraints.

The satellite and UAV period established algorithm design and hardware-facing validation. The 3D project moved that experience into a native C++ and Qt application. The independent project added layered design, testing, logging, and reproducible builds. The enterprise projects developed safe legacy maintenance and cross-component debugging. The SIP project combined these skills in an embedded product involving application state, a third-party SDK, networking, media, provisioning, firmware, and hardware.

SAFE BOUNDARY STATEMENTS

Scala

My primary responsibility was the C89 backend. In Scala I implemented a targeted API request backed by C processing and updated Swagger. I did not broadly refactor or own the Scala architecture.

AWS and CI/CD

I built, deployed, and diagnosed the application in existing AWS-hosted Linux environments using Jenkins, SSH, logs, gdb, and core dumps. I did not administer AWS or own CI/CD automation.

WebRTC

My main responsibility was phone-side integration using libwebrtc and libmediasoupclient. I made a limited contribution to the initial Node.js server but did not own the later rewrite.

GStreamer

The media path I implemented used libwebrtc, libmediasoupclient, Qt Multimedia, and Linphone callbacks rather than a GStreamer pipeline.

V4L2

I worked with camera discovery, selection, frame formats, and rendering through the application and media stack on NXP i.MX, but I did not implement a direct V4L2 ioctl capture loop.

Conan

I did not use Conan on these projects. Embedded dependencies were handled through Yocto and BitBake, while the independent application used pinned submodules and CMake FetchContent.

CLOSING POSITIONING

My strongest value for a C++ role is the ability to understand a complex existing system, locate the real owner of behavior, and make a focused improvement without breaking established workflows. I combine hands-on C and C++ development with embedded Linux, Qt, debugging, legacy modernization, multimedia and networking integration, and a long algorithm-development foundation.
