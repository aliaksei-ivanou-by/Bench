SELF INTRO

DOCUMENT INFORMATION

Request ID: E496
Candidate: Aliaksei Ivanou
Target role: GNC Engineer
CV source: E496 Aliaksei Ivanou (7, MATLAB, C++).pdf
Source request: E496_Request_AliakseiIvanou.md
Source profile: E496_Profile_AliakseiIvanou.md
Source analysis: E496_Request_Analysis_AliakseiIvanou.md
Preparation language: English
Delivery format: Full spoken version
Estimated duration: 4–5 minutes
Document status: Interview-ready; checked against Responsibilities and the completed Request Analysis

PURPOSE

This is the opening self-introduction for the GNC Engineer interview. It leads with the candidate's strongest verified aerospace, MATLAB, modelling, calibration, validation, and embedded-software evidence while stating clearly that professional spacecraft GNC and feedback-controller ownership are not established.

TARGET POSITIONING

Aliaksei is an aerospace algorithm and software engineer whose strongest relevant experience is more than seven years of MATLAB-based R&D for satellite and UAV optical systems, followed by production C/C++ and embedded Linux work. His evidence is strongest in physical modelling, constrained algorithm design, sensor geometry, flight validation, and model-to-implementation collaboration; he must position these as foundations for learning the role, not as prior ownership of spacecraft attitude control.

INTERVIEW SCRIPT

Hello, my name is Aliaksei Ivanou.

I am an aerospace algorithm and software engineer with more than eight years across research and development and commercial software engineering. The part of my background most relevant to this role is seven and a half years in the research department of a company that develops optical payloads for Earth-observation satellites and UAVs. My main working environment there was MATLAB, and my responsibility was to design, implement, and verify algorithms against real instrument constraints.

For satellite systems, I worked on detector-segment stitching, radiometric correction, onboard image compression, adaptive quantization, and automated resolution assessment. One representative decision was choosing an ADPCM-family compression approach because it could achieve the required data reduction within a very limited onboard computation budget. A theoretically stronger but more expensive algorithm would not have been useful if the flight hardware could not run it. I owned the MATLAB reference algorithm and its verification, while a separate flight-software group owned the implementation running onboard. That boundary taught me to make assumptions, interfaces, reference inputs and outputs, precision, and expected behavior explicit.

For a UAV optical system, I developed debayering, image-stabilization, image-fusion, and format-conversion modules. I also worked with the interface between the camera and the navigation system. In one case, the camera and the IMU each behaved correctly, but the calculated frame-centre coordinates were wrong because their actual alignment differed from the nominal geometry. I calibrated that relationship, incorporated the correction into the coordinate computation, and validated the result against known ground positions. I also participated in more than thirty UAV test flights as an optical-payload operator, so I am used to comparing a model with the behavior of a real physical system and learning from measured data.

My academic foundation is a five-year Radiophysics degree with a specialization in Satellite Information Systems and Technologies. It included ballistics and small-spacecraft control, as well as statistical and physical modelling. In university work I used Monte Carlo simulation for a statistical bioequivalence method, implemented and tested Gaussian-mixture clustering in MATLAB, and used forward modelling for an atmospheric inverse problem. This is not the same as spacecraft Monte Carlo verification, but it gave me a strong habit of making assumptions explicit and validating models with constructed or measured evidence.

During the last five years, I moved into production C and C++ development. Most recently, I worked in C++17 and Qt on an ARM64 embedded Linux product, crossing application, SDK, Yocto image, service, network, peripheral, and physical-device boundaries. That experience strengthened my software architecture, asynchronous-state, diagnostics, testing, and hardware-integration skills.

I want to be precise about the boundary of my fit. I have not yet built spacecraft attitude-control laws, designed feedback control for flexible or resonant plants, implemented Kalman filtering, used MuJoCo, performed system identification, or designed active noise cancellation. My MATLAB experience is substantial but historical and would need a refresh. What I bring is an aerospace and physics foundation, years of algorithm work on real instruments, evidence-based research habits, experience moving from a reference algorithm toward constrained onboard behavior, and recent embedded C++ engineering discipline.

That is why the Hummingbird role is interesting to me. It combines physical modelling, simulation, experimental data, onboard constraints, and close collaboration between algorithm and embedded engineers. I would approach the direct GNC areas as a serious learning curve, while contributing immediately in algorithm structuring, verification, model-to-software interfaces, diagnostics, and disciplined work with real-system data.

INTERVIEW BOUNDARIES

• Do not claim three years of control-system development or professional spacecraft GNC experience.
• Do not convert UAV image stabilization into vehicle attitude stabilization.
• Do not convert image fusion or IMU-to-camera calibration into Kalman filtering or navigation-state estimation.
• Do not describe the academic Monte Carlo work as spacecraft pointing or stability verification.
• Do not claim MuJoCo, reaction-wheel, control-moment-gyro, momentum-management, system-identification, or multi-joint robotic-control experience.
• Do not convert phone-side media integration into active-noise-cancellation or audio-control-loop ownership.
• Describe MATLAB as extensive historical experience that requires a refresh; do not claim established scientific-Python depth.
• State that the flight-software group owned onboard implementation of the MATLAB algorithms.
• Use May 2025 to August 2026 for the completed SIP desk-phone assignment.
• Treat the shared name of Samara State Aerospace University and Samara Aerospace as a coincidence; no affiliation is established.

EXPECTED FOLLOW-UP TOPICS

• IMU-to-camera calibration and why interface errors can remain hidden when both subsystems pass individual tests.
• Selection of an ADPCM-family algorithm under a fixed onboard computation and downlink budget.
• MATLAB reference behavior, handover to the flight-software group, and verification of target results.
• UAV image stabilization and fusion, with the explicit boundary from vehicle control and state estimation.
• Monte Carlo coursework, synthetic ground truth, and the difference from GNC dispersion analysis.
• Ballistics and small-spacecraft-control coursework versus professional control-system experience.
• Embedded C++17, asynchronous state, physical-device diagnosis, and Yocto-based target integration.
• Why the candidate is interested despite the direct GNC gap and how he would structure the learning plan.
• Current MATLAB currency and the absence of verified MuJoCo and scientific-Python experience.
• Work location, US work authorization, and whether Samara Aerospace accepts adjacent profiles.
