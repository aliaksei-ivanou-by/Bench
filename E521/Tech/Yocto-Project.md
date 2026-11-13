Yocto-Project

SECTION 1. TECHNOLOGY AND VERSION

Category: Build system

Yocto Project 4.0 Kirkstone; the exact project release must be checked in its metadata.

SECTION 2. PURPOSE

Yocto Project provides tools and metadata for building a tailored embedded Linux distribution and images. It is a project and ecosystem, not a Linux distribution installed on a device. OpenEmbedded metadata and BitBake turn source, configuration and package selection into reproducible target artifacts.

SECTION 3. CORE CONCEPTS

Recipes describe source, dependencies, build and install steps; classes share behavior. Layers organize related metadata, while machine and distribution configuration select hardware and policy.

A .bbappend extends a matching recipe from another layer. The build uses per-recipe sysroots for dependencies, packages installed files and assembles selected packages into an image.

The SDK supplies a cross-toolchain and target headers/libraries for external development. Shared state can reuse matching build outputs.

The build directory is separate from the source layers. Its configuration chooses the enabled layers, machine and distribution; layer priorities and provider selection determine which metadata is used.

A recipe produces one or more packages, but an image recipe or image configuration must select the packages needed at runtime. A generated SDK is built against a particular target configuration and should be kept compatible with it.

To diagnose a missing executable, inspect the recipe install step, package contents, image package selection and finally the deployed filesystem. Keep target-specific changes in the appropriate project layer so vendor updates remain manageable.

Do not confuse a successful desktop test with validation of a cross-built image on the physical product.

SECTION 4. TYPICAL USAGE

After sourcing the project build environment, bitbake <image> builds an image; bitbake-layers show-layers lists enabled layers and bitbake-layers show-appends shows matched appends. Inspect local.conf and bblayers.conf, build logs, package contents and the final root filesystem. Use the project’s release documentation and machine configuration; command output depends on the configured layers.

Practical investigation: first identify MACHINE, DISTRO and the enabled layer versions. If a file is missing on the device, check whether the recipe installed it, whether it appears in a built package, whether that package is selected by the image and whether the intended image was actually deployed.

oe-pkgdata-util can inspect built package data: find-path locates the package containing a path and list-pkg-files lists a package's files. Recheck permissions and service configuration on the target after confirming image contents.

LINPHONE SDK INTEGRATION FLOW

This is a general integration example. Here linphone-sdk names the SDK recipe, phone-ui names a consuming application recipe and phone-image names a product image recipe. Actual providers and output package names are determined by the chosen metadata. Linphone SDK is the VoIP software stack; a Yocto SDK is a generated cross-development toolchain, a different artifact.

FLOW-01. Establish the build baseline.

Start from a working image for the board.

Record MACHINE, DISTRO, Kirkstone-compatible layer revisions, compiler and C library.

Select a Linphone SDK release compatible with that baseline and the application's API.

Decide which audio, video, TLS and codec features are needed.

A current upstream master is not automatically compatible with an older product branch.

FLOW-02. Find an existing recipe before creating one.

In the initialized Linux build environment, inspect bitbake-layers show-layers, bitbake-layers show-recipes and bitbake-layers show-appends.

Search enabled metadata for liblinphone and related components; the provider may not be called linphone-sdk.

Reuse a compatible recipe with a product-layer .bbappend where possible.

Create a new recipe only when existing metadata cannot supply the required version or build model.

```bash
bitbake-layers show-layers
bitbake-layers show-recipes
bitbake-layers show-appends
```

FLOW-03. Put product changes in a layer.

Use an existing product layer or create one with bitbake-layers create-layer ../meta-phone, then enable it with bitbake-layers add-layer ../meta-phone.

Inspect conf/layer.conf for recipe discovery, layer dependencies and Kirkstone compatibility.

A possible layout is meta-phone/recipes-connectivity/linphone-sdk/ for the recipe and files/ for patches.

Do not edit vendor layers or temporary build outputs as the permanent solution.

```bash
bitbake-layers create-layer ../meta-phone
bitbake-layers add-layer ../meta-phone
```

FLOW-04. Define reproducible sources and licensing.

The recipe defines SUMMARY, LICENSE, LIC_FILES_CHKSUM, SRC_URI, SRCREV and S for the selected source layout.

Pin the exact commit and fetch all required source inputs through BitBake; use archive checksums for release archives.

Account for submodules where that release uses them.

Store local changes as versioned patches in SRC_URI or pin a maintained fork.

Review the licenses of enabled codecs and dependencies as well as the SDK itself.

FLOW-05. Choose how to build the dependency stack.

Linphone SDK has its own CMake orchestration for multiple components.

Inspect the selected release rather than treating it as a single ordinary library.

Prefer separate compatible recipes when the stack can use staged dependencies; otherwise adapt the SDK orchestration so source inputs, toolchains and installation remain controlled by Yocto.

Avoid hidden downloads during configure/compile and duplicate bundled/system copies of the same library.

Do not invent a universal switch that disables the superbuild: options vary by release.

FLOW-06. Describe cross-build inputs and features.

For a CMake-based component, inherit cmake and declare recipe-level DEPENDS for required target libraries.

Host-side generators require suitable native dependencies.

Use PACKAGECONFIG and EXTRA_OECMAKE to express supported feature choices.

The cmake class supplies cross-build integration; nested builds must preserve its compiler, sysroot and target settings.

Check log.do_configure and CMakeCache.txt for accidental host paths.

CPU tuning follows the machine configuration; hardware codecs also need the correct platform integration.

FLOW-07. Install into staging and create packages.

Run bitbake linphone-sdk and follow fetch, unpack, patch, configure, compile, install and packaging.

do_install writes into ${D}, not the build host's /usr.

Where upstream installation is incomplete, adapt installation explicitly.

Inspect the runtime libraries, plugins and resource files, plus development headers and CMake/pkg-config metadata.

Assign paths with FILES and split development/debug content appropriately.

Fix packaging QA failures instead of disabling them globally.

```bash
bitbake linphone-sdk
```

FLOW-08. Connect the application recipe.

For this example, phone-ui declares DEPENDS += "linphone-sdk".

The dependency's staged headers, libraries and discovery metadata become available in the application's recipe sysroot.

The application's CMake uses the package configuration or pkg-config interface actually exported by the chosen SDK release, rather than hard-coded host paths.

Shared-library runtime dependencies are normally discovered automatically; dynamically loaded plugins and data may need explicit RDEPENDS:${PN}.

Those entries name output packages, not arbitrary recipe names.

```bitbake
DEPENDS += "linphone-sdk"
```

FLOW-09. Select runtime packages in the image.

Add the application through the product image or packagegroup.

If phone-ui is its output package, an image fragment is IMAGE_INSTALL:append = " phone-ui".

Normal linked dependencies pull in their library packages; add separately needed plugins/resources explicitly.

Building linphone-sdk alone does not include it in the image.

A generated development SDK may additionally include development packages, while a production image usually does not need headers or static libraries.

```bitbake
IMAGE_INSTALL:append = " phone-ui"
```

FLOW-10. Integrate application startup.

If phone-ui is managed by systemd, its recipe can inherit systemd, install phone-ui.service under ${systemd_system_unitdir} and set SYSTEMD_SERVICE:${PN} = "phone-ui.service".

Ensure the distribution actually uses systemd and select the intended enablement policy.

The SDK libraries themselves normally need no service.

The application still needs writable state locations, audio/video device permissions and retry handling for network or SIP readiness; ordering after a network target alone does not guarantee server reachability.

```bitbake
inherit systemd
SYSTEMD_SERVICE:${PN} = "phone-ui.service"
```

FLOW-11. Inspect the image and validate on hardware.

Run bitbake phone-ui, then bitbake phone-image.

Inspect package contents with oe-pkgdata-util list-pkg-files using actual package names, and check the image manifest and root filesystem.

Deploy the intended image through the board's supported method.

Check architecture, dynamic loader, missing libraries, plugins, certificates and configuration.

Test registration, incoming/outgoing calls, audio/video, restart and network recovery.

Use systemctl status phone-ui.service and journalctl -u phone-ui.service when that service is installed.

On the Linux build host:

```bash
bitbake phone-ui
bitbake phone-image
```

On the device after image deployment:

```bash
systemctl status phone-ui.service
journalctl -u phone-ui.service
```

FLOW-12. Make the integration repeatable.

Keep layer changes, source revisions, patches and feature choices in version control.

Rebuild in CI without a developer's local workspace overrides, retain image manifests and test the same artifact on target.

Verify that changes to the SDK trigger the required application rebuild and that updated runtime libraries match the deployed executable.

Include upgrade/reboot regression checks; a successful recipe build is only one stage of delivery.

SPOKEN FLOW

First I identify the target configuration and an existing provider. Then I add or extend a recipe in the product layer, pin sources, declare dependencies and configure the cross-build.

BitBake builds the SDK, installs it into staging and produces packages. The application consumes its build interface through the recipe sysroot.

The image selects runtime packages, and the application service handles startup. Finally I inspect the image and validate calls, media and recovery on the physical device.

FOUNDATION AND PRACTICAL EXERCISES

Poky is a reference integration of BitBake, OpenEmbedded-Core metadata and reference distribution/BSP configuration. OpenEmbedded supplies the metadata/build ecosystem; BitBake executes the task graph.

A meta-* layer groups metadata. build/conf/bblayers.conf enables layers; local.conf holds local build choices.

MACHINE selects hardware/tuning, DISTRO selects distribution policy, and an image recipe selects packages and image features.

DL_DIR stores downloaded inputs; SSTATE_DIR stores reusable task outputs, commonly under sstate-cache. Sharing these directories can reduce fetching and rebuilding across compatible builds. A changed signature may prevent task-output reuse; neither cache replaces declared dependencies or pinned sources.

LAB-01. Boot a baseline.

Use a supported Linux host and a pinned Kirkstone revision of Poky.

The Kirkstone quick-build guide specifies at least 90 GB free disk and 8 GB RAM; allow additional space for SDKs and extra builds.

Initialize with source oe-init-build-env build-lab.

Set MACHINE = "qemuarm64" in conf/local.conf, run bitbake core-image-minimal and runqemu qemuarm64 nographic.

Success means reaching a guest shell and checking uname -a and /proc/cmdline.

QEMU does not reproduce every physical-board boot stage.

```bash
source oe-init-build-env build-lab
```

conf/local.conf:

```bitbake
MACHINE = "qemuarm64"
```

```bash
bitbake core-image-minimal
runqemu qemuarm64 nographic
```

LAB-02. Add a C++ application.

From the build directory run bitbake-layers create-layer ../meta-lab and bitbake-layers add-layer ../meta-lab.

Create ../hello with the following files and an actual source license; keep the source in version control.

main.cpp:

```cpp
#include <iostream>
int main() { std::cout << "hello from Yocto" << std::endl; }
```

CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.16)
project(hello LANGUAGES CXX)
add_executable(hello main.cpp)
install(TARGETS hello RUNTIME DESTINATION bin)
```

Run devtool add hello ../hello, inspect the generated source/license fields and inherit cmake, then run devtool build hello. Commit source changes as appropriate and run devtool finish hello ../meta-lab.

Inspect the exported recipe and sources, then run bitbake hello without the workspace override. For this exercise add IMAGE_INSTALL:append = " hello" in local.conf, rebuild core-image-minimal and run hello in QEMU.

In a product, maintain package selection in image/packagegroup metadata.

On the Linux build host:

```bash
bitbake-layers create-layer ../meta-lab
bitbake-layers add-layer ../meta-lab
```

After preparing and inspecting the sources:

```bash
devtool add hello ../hello
devtool build hello
```

After committing source changes:

```bash
devtool finish hello ../meta-lab
bitbake hello
```

conf/local.conf:

```bitbake
IMAGE_INSTALL:append = " hello"
```

```bash
bitbake core-image-minimal
runqemu qemuarm64 nographic
```

LAB-03. Export a kernel change.

Follow the BSP file's kernel workflow, using linux-yocto for this QEMU lab.

Deliver a product-layer .bbappend, one applicable patch and a .cfg fragment.

After leaving the devtool workspace, rebuild kernel and image and check the patch effect and final configuration.

LAB-04. Apply an overlay.

Use a supported board and matching layer, for example Raspberry Pi with meta-raspberrypi.

Compile the overlay, include it in boot artifacts and configure the real boot path to apply it.

Reboot and check the live device tree and driver binding.

A .dtbo in the deploy directory alone is insufficient; BSP explains the different U-Boot and Raspberry Pi firmware mechanisms.

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

QUESTION YCT-21. How do Poky, OpenEmbedded and BitBake differ?

Answer: Poky is a reference integration, OpenEmbedded supplies metadata and the build ecosystem, and BitBake executes tasks. Product layers/configuration produce the actual device image.

QUESTION YCT-22. What belongs in bblayers.conf and local.conf?

Answer: bblayers.conf enables layers; local.conf holds local settings such as MACHINE. MACHINE selects hardware/tuning, DISTRO selects policy, and the image selects packages.

QUESTION YCT-23. How do downloads and sstate-cache differ?

Answer: DL_DIR preserves fetched inputs; SSTATE_DIR preserves reusable task outputs. Reuse depends on signatures and compatible inputs. Neither cache repairs undeclared dependencies.

QUESTION YCT-24. What proves the recipe lab is complete?

Answer: The exported recipe builds without a workspace override, the package is in the image manifest and hello runs in the rebuilt guest. Workspace-only compilation proves less.

SECTION 9. SOURCES

Research date: 2026-11-13

- https://docs.yoctoproject.org/4.0.30/overview-manual/concepts.html

- https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html

- https://docs.yoctoproject.org/4.0.30/dev-manual/debugging.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html

- https://docs.yoctoproject.org/4.0.30/dev-manual/new-recipe.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html

- https://github.com/BelledonneCommunications/linphone-sdk

- https://github.com/BelledonneCommunications/linphone-sdk/blob/master/CMakeLists.txt

- https://docs.yoctoproject.org/4.0.30/brief-yoctoprojectqs/index.html

- https://docs.yoctoproject.org/4.0.30/sdk-manual/extensible.html
