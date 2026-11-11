Yocto-Project

1. TECHNOLOGY AND VERSION
Category: Build system
Yocto Project 4.0 Kirkstone; the exact project release must be checked in its metadata.

2. PURPOSE

Yocto Project provides tools and metadata for building a tailored embedded Linux distribution and images. It is a project and ecosystem, not a Linux distribution installed on a device. OpenEmbedded metadata and BitBake turn source, configuration and package selection into reproducible target artifacts.

3. CORE CONCEPTS

Recipes describe source, dependencies, build and install steps; classes share behavior. Layers organize related metadata, while machine and distribution configuration select hardware and policy. A .bbappend extends a matching recipe from another layer. The build uses per-recipe sysroots for dependencies, packages installed files and assembles selected packages into an image. The SDK supplies a cross-toolchain and target headers/libraries for external development. Shared state can reuse matching build outputs.

The build directory is separate from the source layers. Its configuration chooses the enabled layers, machine and distribution; layer priorities and provider selection determine which metadata is used. A recipe produces one or more packages, but an image recipe or image configuration must select the packages needed at runtime. A generated SDK is built against a particular target configuration and should be kept compatible with it. To diagnose a missing executable, inspect the recipe install step, package contents, image package selection and finally the deployed filesystem. Keep target-specific changes in the appropriate project layer so vendor updates remain manageable. Do not confuse a successful desktop test with validation of a cross-built image on the physical product.

4. TYPICAL USAGE

After sourcing the project build environment, bitbake <image> builds an image; bitbake-layers show-layers lists enabled layers and bitbake-layers show-appends shows matched appends. Inspect local.conf and bblayers.conf, build logs, package contents and the final root filesystem. Use the project’s release documentation and machine configuration; command output depends on the configured layers.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Yocto supports hardware-specific composition, controlled versions and long-term image maintenance. The cost is metadata complexity, build time and responsibility for layer compatibility and security updates. Buildroot may be simpler for a smaller fixed image; a binary distribution may speed up development where its packages and update policy fit the device.

6. PITFALLS AND SECURITY

A recipe compiling successfully does not prove its package is in the image. Distinguish build-time DEPENDS from runtime package dependencies, and host tools from target libraries. Pin compatible layers and sources, review licenses, protect signing credentials and test update and rollback behavior. Cache reuse does not replace target verification.

7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: the CV lists Yocto/BitBake and i.MX. The Legend describes recipe and package work, SDK cross-compilation, image integration and service startup. The request asks for extensive Yocto, custom layers, recipes and image builds; Responsibilities distinguishes confirmed inherited-platform integration from unsupported full-platform ownership.

8. INTERVIEW QUESTIONS

1. What is a layer?
A collection of related recipes, configuration and classes that can be combined with other layers.

2. What does .bbappend do?
It modifies or extends a matching recipe without copying the entire original recipe.

3. Why is a compiled binary absent from the image?
It may not have been installed into a package, or the package may not have been selected for the image.

4. What is the SDK for?
It provides a cross-development toolchain and sysroot for building applications against a target environment.

5. Is cache reuse a target test?
No. It only reuses matching build outputs; runtime behavior still needs verification on the target.

9. SOURCES

Research date: 2026-11-11
- https://docs.yoctoproject.org/4.0.30/overview-manual/concepts.html
- https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html
