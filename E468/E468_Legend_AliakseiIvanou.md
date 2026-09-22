Legend

1 SIP Desk Phone Platform for Audio and Video Communication

Period: May 2025 – present
Role: Senior Software Engineer
Project overview
My current project is an embedded platform for SIP desk phones. The product family includes devices with and without a camera, so the software must support both audio-only and video communication.
The platform covers the complete phone workflow: SIP registration, incoming and outgoing calls, call hold and transfer, conferences, phonebook access, direct IP dialing, device configuration, and automatic provisioning.
The product consists of several parts:
A native application running on the phone.
An embedded Linux system built with Yocto.
SIP and multimedia components based on Linphone SDK, GStreamer, and related libraries.
WebRTC conferencing functionality.
A web management interface.
A Windows-based provisioning utility.
Device-side services and configuration.
The target devices are based on the NXP i.MX platform. The native application is mainly written in C++17 and uses Qt 5.15 and Qt Widgets.
My role
I work as a Senior Software Engineer, mainly on the native application and its call-handling logic. My responsibility is to make the call flow easier to maintain and to ensure that the UI correctly reflects the actual state of calls and media sessions.
I also work with the Linphone SDK integration, video and conference scenarios, WebRTC functionality, provisioning tools, and embedded Linux integration.
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
Main project takeaway
This project combines several areas: modern C++, legacy Qt code, SIP, WebRTC, multimedia, embedded Linux, and hardware integration.
My main contribution is making complex call scenarios more reliable and making the existing code easier to understand and extend without breaking the behavior of deployed devices.

2 Library Management System
Period: March 2022 – April 2025
Role: Senior Software Engineer
Project overview
This was a large library management system with more than forty years of development history. It was used by different clients around the world and had to support large amounts of library and catalog data.
Because of its long history, the system was not based on a single technology. It combined:
C for important core functionality.
Java 11 for some application components.
Scala for API-related functionality.
MySQL and PostgreSQL databases.
Socket-based communication.
AWS-based CI/CD pipelines.
A major project requirement was to continue developing the product while maintaining compatibility with existing components and workflows.
My role
I worked as a Senior Software Engineer and was one of the main contributors working with the C codebase.
My responsibilities included:
Investigating and fixing complex defects.
Developing new functionality.
Improving performance.
Working with socket-based communication.
Refactoring Scala API code.
Updating database tables.
Working with existing AWS pipelines.
Estimating tasks.
Conducting code reviews.
Cooperating with the client’s engineering team.
Working with the legacy C codebase
A large part of my work involved understanding code that had been developed and modified over many years.
The main difficulty in this type of system is that business behavior is often distributed across several functions, modules, database operations, and communication layers. A change that looks local can affect older workflows or clients.
When investigating an issue, I first tried to reproduce it and determine whether it came from business logic, data handling, socket communication, or an integration boundary. I used debugging and logging information to trace the execution path and understand the existing behavior before making a change.
The objective was usually to make a focused and compatible modification instead of redesigning a large part of the product.
Socket-based functionality
I implemented and maintained backend and frontend functionality related to socket communication.
This required careful handling of:
Connection state.
Requests and responses.
Data exchanged between components.
Errors and unexpected input.
Compatibility with existing communication behavior.
The important part was not only sending or receiving data, but also ensuring that the new functionality worked correctly with older parts of the system.
Performance and defect investigation
I worked on performance improvements and complex production-related defects.
For performance tasks, I investigated where time or resources were being spent before changing the implementation. Depending on the problem, the cause could be inefficient processing, repeated operations, unnecessary data access, or interaction between several legacy components.
Because the system was mature, every optimization had to preserve the established business behavior. A technically faster solution was not acceptable if it changed the expected result or broke compatibility.
Scala API refactoring
Some API functionality was implemented in Scala. I refactored existing Scala code to improve its structure, readability, and maintainability.
The purpose was to make future modifications safer and reduce unnecessary complexity. I did not position myself as a dedicated Scala specialist; my work was focused on the parts of the API that were connected to the features and changes assigned to me.
Database changes
New features sometimes required changes to existing database tables.
I worked with MySQL and PostgreSQL and modified the schema to support updated workflows. Because this was an established system, database changes had to be compatible with existing data and application behavior.
Before making a change, it was necessary to understand how the affected tables were used by different components and whether existing queries or workflows depended on their current structure.
AWS pipelines
The project used AWS-related pipelines to automate build and deployment processes.
I worked with the existing pipelines as part of the development and delivery process. My role was related to using and adjusting the established CI/CD workflow when required by application changes. I did not design the complete cloud infrastructure from scratch.
Collaboration and code review
I estimated development tasks and participated in planning. For legacy tasks, estimation required time not only for implementation but also for investigation, compatibility checks, and review.
I conducted code reviews for both my immediate team and the client’s team. I checked correctness, readability, compatibility with existing code, and possible side effects. Code review was also an important method of sharing knowledge about older areas of the system.
Main project takeaway
The main value of this project was learning how to safely develop a large, mature product. My strongest contribution was the ability to investigate unfamiliar legacy code, find the real source of a problem, and introduce compatible changes across C, Scala, databases, and communication components.

3 Corporate System for the Oil and Gas Industry
Period: October 2021 – December 2021
Role: Software Engineer
Project overview
This was a corporate system for internal use in the oil and gas industry. It had a C++17 backend and a web-based frontend built with JavaScript, HTML, and jQuery.
The application ran in a Windows environment. It used MySQL and Microsoft SQL Server for data storage, Nginx as part of the server environment, CMake for builds, and Git and Bitbucket for version control.
My role
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
Main project takeaway
This project strengthened my ability to join an existing product, learn its structure quickly, and contribute within a limited period. It also gave me additional experience with C++17 backend development in a Windows-based corporate environment.

4 Home Accounting Software
Period: July 2020 – July 2021
Role: Software Engineer
Project overview
This was a desktop application for personal financial accounting. It allowed users to record and manage financial transactions such as bills, receipts, and credit-card operations.
The main technologies were:
C++.
FLTK for the graphical interface.
SQLite for local storage.
CMake for the build system.
Google Test for testing.
plog for logging.
Visual Studio as the main development environment.
My role
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
Main project takeaway
This project gave me complete experience with a standalone C++ desktop application: UI development, business logic, local database integration, build configuration, automated testing, and diagnostics.

5 3D Reconstruction Software for Industrial Applications
Period: March 2020 – May 2020
Role: Software Engineer
Project overview
The purpose of this project was to generate 3D models using data received from multiple 2D laser sensors.
Such software can be used in industrial inspection, manufacturing, robotics, and quality-control systems where accurate spatial information is required.
The main technologies were:
C++.
Point Cloud Library, or PCL.
Open3D.
Visual Studio.
Git.
My role
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
Main project takeaway
This project gave me practical experience with 3D data structures, point-cloud processing, specialized C++ libraries, and industrial sensor data.

6 Software Modules for UAV Systems
Period: August 2018 – December 2019
Role: Software Engineer
Project overview
This project involved software and algorithms for processing photo and video data received from optical sensors used in unmanned aerial vehicles.
The objective was to improve image quality, compatibility, stability, and the usefulness of data received from the sensors.
My main development environment was MATLAB, with PostgreSQL used in the wider project environment.
My role
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
Main project takeaway
This project developed my experience in practical image-processing algorithms and working with real sensor data, where noise, motion, image formats, and data quality must all be considered.

7 Remote Sensing Satellites Database
Period: March 2016 – March 2017
Role: Software Engineer
Project overview
This project was a database and web application for storing detailed information about Earth-observation satellites.
The system allowed users to access, search, and manage satellite specifications. The main technologies were:
Ruby.
Ruby on Rails.
PostgreSQL.
Microsoft Access for legacy data.
My role
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
Main project takeaway
This project expanded my experience beyond C++ and algorithms. It gave me practical exposure to web development, relational database design, legacy-data migration, and user-facing information systems.

8 Satellite Earth-Observation Image Processing Software
Period: August 2012 – March 2016
Role: Software Engineer
Project overview
This was my first major commercial project and the foundation of my image-processing experience.
The software contained a set of modules for processing and analyzing images received from Earth-observation satellites. The functionality included:
Brightness normalization.
Optical-defect correction.
Linear-resolution measurement.
Sharpness analysis.
Quantization-range prediction.
Image compression based on ADPCM.
The main technologies were C++, MATLAB, CMake, Visual Studio, PostgreSQL, Microsoft Access, System Tool Kit, and Jira.
My role
I worked on the development, investigation, and verification of image-processing algorithms.
MATLAB was useful for algorithm research, experiments, data analysis, and verification. C++ was used for software implementation where integration and performance were important.
Brightness normalization and optical correction
Images or frames received from a satellite can have different brightness levels or optical distortions.
I developed algorithms that normalized brightness across multiple frames and reduced visible inconsistencies. The objective was to produce a more uniform image and improve the quality of further analysis.
I also worked on eliminating optical defects between frames. This was important when multiple frames had to be compared or combined.
Linear-resolution measurement
I developed software for evaluating the linear resolution of satellite images using the sharp-edge method.
The general idea was to analyze how the imaging system represented a transition between dark and bright areas. A perfectly sharp edge in the observed scene becomes less sharp in the captured image. By analyzing this transition, the software could estimate the effective imaging resolution.
I also developed functionality for evaluating image sharpness and edge clarity. These measurements helped assess the quality and performance of the imaging system.
Quantization-range prediction
Another task was predicting the required quantization range for satellite images.
The purpose was to estimate the expected range of brightness values based on Earth-observation data and albedo information. This helped select an appropriate range for the sensor data and reduce the risk of losing information because of incorrect quantization.
I also automated this analysis so that it could be applied more efficiently to the available data.
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
PostgreSQL and Microsoft Access were used for related data storage. System Tool Kit was used in the project environment for work associated with satellite systems and Earth-observation scenarios.
CMake and Visual Studio were used for building and developing the C++ components, while Jira supported task tracking.
Main project takeaway
This project gave me a strong foundation in algorithm development. I learned how to move from a mathematical idea to experimentation in MATLAB, implementation in C++, and verification using real or representative image data.
