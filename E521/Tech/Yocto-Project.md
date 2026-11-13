Yocto-Project

SECTION 1. TECHNOLOGY AND VERSION
Category: Build system
Yocto Project 4.0 Kirkstone; the exact project release must be checked in its metadata.

SECTION 2. PURPOSE

Yocto Project provides tools and metadata for building a tailored embedded Linux distribution and images. It is a project and ecosystem, not a Linux distribution installed on a device. OpenEmbedded metadata and BitBake turn source, configuration and package selection into reproducible target artifacts.

SECTION 3. CORE CONCEPTS

Recipes describe source, dependencies, build and install steps; classes share behavior. Layers organize related metadata, while machine and distribution configuration select hardware and policy. A .bbappend extends a matching recipe from another layer. The build uses per-recipe sysroots for dependencies, packages installed files and assembles selected packages into an image. The SDK supplies a cross-toolchain and target headers/libraries for external development. Shared state can reuse matching build outputs.

The build directory is separate from the source layers. Its configuration chooses the enabled layers, machine and distribution; layer priorities and provider selection determine which metadata is used. A recipe produces one or more packages, but an image recipe or image configuration must select the packages needed at runtime. A generated SDK is built against a particular target configuration and should be kept compatible with it. To diagnose a missing executable, inspect the recipe install step, package contents, image package selection and finally the deployed filesystem. Keep target-specific changes in the appropriate project layer so vendor updates remain manageable. Do not confuse a successful desktop test with validation of a cross-built image on the physical product.

SECTION 4. TYPICAL USAGE

After sourcing the project build environment, bitbake <image> builds an image; bitbake-layers show-layers lists enabled layers and bitbake-layers show-appends shows matched appends. Inspect local.conf and bblayers.conf, build logs, package contents and the final root filesystem. Use the project’s release documentation and machine configuration; command output depends on the configured layers.

Practical investigation: first identify MACHINE, DISTRO and the enabled layer versions. If a file is missing on the device, check whether the recipe installed it, whether it appears in a built package, whether that package is selected by the image and whether the intended image was actually deployed. oe-pkgdata-util can inspect built package data: find-path locates the package containing a path and list-pkg-files lists a package's files. Recheck permissions and service configuration on the target after confirming image contents.

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Yocto supports hardware-specific composition, controlled versions and long-term image maintenance. The cost is metadata complexity, build time and responsibility for layer compatibility and security updates. Buildroot may be simpler for a smaller fixed image; a binary distribution may speed up development where its packages and update policy fit the device.

SECTION 6. PITFALLS AND SECURITY

A recipe compiling successfully does not prove its package is in the image. Distinguish build-time DEPENDS from runtime package dependencies, and host tools from target libraries. Pin compatible layers and sources, review licenses, protect signing credentials and test update and rollback behavior. Cache reuse does not replace target verification.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: the CV lists Yocto/BitBake and i.MX. The Legend describes recipe and package work, SDK cross-compilation, image integration and service startup. The request asks for extensive Yocto, custom layers, recipes and image builds; Responsibilities distinguishes confirmed inherited-platform integration from unsupported full-platform ownership.

SECTION 8. INTERVIEW QUESTIONS

QUESTION YCT-01. What is a layer?

Answer: A layer groups recipes, appends, classes and configuration for one concern. conf/layer.conf declares how its metadata is discovered; bblayers.conf enables it in a build. A layer directory alone does not affect an image.

QUESTION YCT-02. What does .bbappend do?

Answer: A .bbappend extends a recipe whose name/version pattern matches. It can add patches, files, configuration or task fragments without copying the upstream recipe. bitbake-layers show-appends checks whether the intended match actually happens.

QUESTION YCT-03. Why is a compiled binary absent from the image?

Answer: Compilation is only one step. The file must reach the recipe's install area, belong to an output package, be selected into the image and survive deployment. Inspect those stages before rebuilding everything.

QUESTION YCT-04. What is the SDK for?

Answer: The SDK provides a cross-toolchain and target sysroot for application development outside the full image build. Its environment selects compiler, headers and libraries; the SDK must match the target configuration and ABI.

QUESTION YCT-05. Is cache reuse a target test?

Answer: No. Shared-state reuse restores outputs whose task signatures match the cache. It does not execute a device scenario or establish boot, peripheral or media correctness; those need runtime validation.

QUESTION YCT-06. What is the difference between MACHINE and DISTRO?

Answer: MACHINE selects hardware-specific configuration such as the board support and tuning. DISTRO selects distribution policy and features. An image selects a runtime package set; none of these concepts is interchangeable.

QUESTION YCT-07. How can you find which package contains a file?

Answer: Use oe-pkgdata-util find-path with built package metadata, then list-pkg-files for the matching package. Check the image manifest and deployed file as well: finding a provider does not prove the package was installed.

QUESTION YCT-08. How do a recipe, package, packagegroup and image differ?

Answer: A recipe describes how to build and package a component; it can produce several packages. A packagegroup collects runtime package dependencies. The image assembles a chosen package set and filesystem artifacts for deployment.

QUESTION YCT-09. How would you organize vendor and product customizations?

Answer: Keep hardware support in BSP-oriented layers and product-specific applications, appends and policy in project layers. Declare compatible releases and dependencies, enable the layers explicitly and inspect the selected providers. This reduces the need to edit vendor metadata directly.

QUESTION YCT-10. Does layer priority override every configuration choice?

Answer: No. BBFILE_PRIORITY influences recipe selection, but version preferences, providers, overrides and parsing rules also matter. Inspect the chosen recipe and resolved variables rather than assuming the highest-priority layer wins every setting.

QUESTION YCT-11. How do you add an application and its service to an image?

Answer: The recipe builds the application and installs executable, configuration and unit file into the staging area. Package metadata assigns the files and service integration. The image or packagegroup selects the runtime package; startup is verified on the device.

QUESTION YCT-12. What is the difference between a native tool and target software?

Answer: A native tool runs on the build host, for example a code generator. Target libraries and executables use the target ABI and sysroot. Confusing them can link host libraries into a target build or try to run target code during compilation.

QUESTION YCT-13. What are downloads and shared state used for?

Answer: The download directory stores fetched source artifacts; shared state stores reusable task outputs. They solve different caching problems. Pin source revisions and record configuration even when both caches are available; a cache is not a source-version policy.

QUESTION YCT-14. How do you make a build reproducible?

Answer: Record layer revisions, source revisions, configuration, toolchain inputs and the intended target. Eliminate undeclared host dependencies and uncontrolled network fetches, then compare artifacts under controlled conditions. Pinning alone helps but is not proof of bit-for-bit reproducibility.

QUESTION YCT-15. How do you inspect image contents before flashing?

Answer: Inspect package metadata, the image manifest and the generated root filesystem or image contents. Check binaries, libraries, units, permissions and model-specific configuration, then confirm that the same artifact is deployed. A recipe log alone cannot establish image composition.

QUESTION YCT-16. How do you reduce image size safely?

Answer: Measure package and file contributions first. Remove unnecessary packages/features or development artifacts, preserving runtime dependencies, licenses and diagnostics required for support. Compare startup and product scenarios afterwards; stripping symbols alone is not a complete size strategy.

QUESTION YCT-17. What must be checked for a read-only root filesystem?

Answer: Identify every writer: logs, caches, application state, credentials and update mechanisms. Provide deliberate writable or volatile locations and verify service behavior after reboot. A read-only image flag cannot repair applications that assume arbitrary writable paths.

QUESTION YCT-18. How would you plan an image update and rollback?

Answer: Identify compatible boot, kernel, device-tree, rootfs and persistent-data versions. Verify artifact authenticity, interrupted-update behavior and a known-good recovery path on a test device. Data migrations can prevent rollback even when an old executable still boots.

QUESTION YCT-19. How do licenses and security updates enter the workflow?

Answer: Review recipe license metadata and license manifests, track source provenance and assess relevant vulnerability reports. Apply compatible fixes, rebuild and validate the resulting image. A successful CVE scan is one input, not proof that the product is secure.

QUESTION YCT-20. How do you separate theoretical Yocto knowledge from personal ownership?

Answer: Explain the technical mechanism, then identify the concrete recipes, packages and image integration actually handled. Keep creating a distribution or BSP from scratch separate from working in inherited layers. This prevents a conceptual answer from becoming an unsupported experience claim.

SECTION 9. SOURCES

Research date: 2026-11-13
- https://docs.yoctoproject.org/4.0.30/overview-manual/concepts.html
- https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html
- https://docs.yoctoproject.org/4.0.30/dev-manual/debugging.html
- https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html
