Yocto-Project

SECTION 1. TECHNOLOGY AND VERSION

Category: Build system

Yocto Project 4.0 Kirkstone; the exact project release must be checked in its metadata.

SECTION 2. PURPOSE

Yocto Project helps build a Linux system for a particular device. You choose the programs, libraries and settings that go into its image. OpenEmbedded provides recipes and build settings; BitBake reads them and runs the build tasks.

SECTION 3. CORE CONCEPTS

- A recipe describes where to get a component and how to build, install and package it.
- A class contains steps shared by several recipes. A layer groups related recipes and settings. A .bbappend adds changes to a matching recipe.
- MACHINE selects the board settings. DISTRO selects system-wide rules. The image selects packages to install.
- A recipe sysroot is a directory with the device headers and libraries needed to build that recipe. The SDK provides a compiler and libraries for development outside the full image build.
- One recipe may produce several packages. A successful build does not mean that those packages are included in the image.
- Sstate stores reusable task results. Reuse saves build time but does not test the phone.
- Keep build output separate from source layers. Check selected recipes and final settings when several layers affect the same component.
- A generated SDK must match the device configuration. Test the final image on hardware as well as testing local application logic.

SECTION 4. TYPICAL USAGE

After sourcing the project build environment, bitbake <image> builds an image; bitbake-layers show-layers lists enabled layers and bitbake-layers show-appends shows matched appends. Inspect local.conf and bblayers.conf, build logs, package contents and the final root filesystem. Use the project’s release documentation and machine configuration; command output depends on the configured layers.

Practical investigation: first identify MACHINE, DISTRO and the enabled layer versions. If a file is missing on the device, check whether the recipe installed it, whether it appears in a built package, whether that package is selected by the image and whether the intended image was actually deployed.

oe-pkgdata-util can inspect built package data: find-path locates the package containing a path and list-pkg-files lists a package's files. Recheck permissions and service configuration on the target after confirming image contents.

LINPHONE SDK INTEGRATION FLOW

This is a general integration example. Here linphone-sdk names the SDK recipe, phone-ui names a consuming application recipe and phone-image names a product image recipe. Actual providers and output package names are determined by the chosen metadata. Linphone SDK is the VoIP software stack; a Yocto SDK is a generated cross-development toolchain, a different artifact.

FLOW-01. Choose the starting build.

- Start with a working image for the board.
- Record MACHINE, DISTRO, layer revisions, compiler and C library. The layers must support Kirkstone.
- Choose an SDK release that works with this build and the application API.
- List the audio, video, TLS and codecs you need. The newest upstream code may not fit an older product branch.

FLOW-02. Look for an existing recipe.

- In the Linux build environment, list the enabled layers, recipes and appends.
- Look for liblinphone and related components. The recipe may have a different name.
- Use a compatible recipe with a product-layer .bbappend if possible. Create a recipe when the existing ones cannot build the version you need.

```bash
bitbake-layers show-layers
bitbake-layers show-recipes
bitbake-layers show-appends
```

FLOW-03. Keep changes in a product layer.

- Use an existing product layer or create and enable meta-phone.
- Check conf/layer.conf: which recipes it finds, which layers it needs and whether it supports Kirkstone.
- One possible directory is meta-phone/recipes-connectivity/linphone-sdk/ with patches under files/.
- Do not keep the permanent fix only in a vendor layer or temporary build directory.

```bash
bitbake-layers create-layer ../meta-phone
bitbake-layers add-layer ../meta-phone
```

FLOW-04. Fix source versions and check licenses.

- Set SUMMARY, LICENSE, LIC_FILES_CHKSUM, SRC_URI, SRCREV and S for the chosen sources.
- Pin a Git commit and let BitBake fetch all inputs. Check release-archive checksums and any required submodules.
- Keep changes as patches listed in SRC_URI or as a fixed commit in a maintained fork.
- Check licenses for the SDK, enabled codecs and other dependencies.

FLOW-05. Decide how dependencies are built.

- Linphone SDK can build several components through its own CMake process. Read the chosen release setup.
- Where supported, build dependencies through separate Yocto recipes. Otherwise adapt the SDK build so Yocto still controls the inputs, compiler and installation.
- Avoid downloads during configure/compile and conflicting bundled and system copies of a library.
- Do not assume every SDK version has the same switch for disabling its combined build, often called a superbuild.

FLOW-06. Set up the device build.

- For a CMake component, use inherit cmake and list required library recipes in DEPENDS.
- Tools that run on the build computer need suitable native dependencies.
- PACKAGECONFIG and EXTRA_OECMAKE select the features supported by that recipe and source version.
- Nested builds must use the same device compiler and sysroot. Check log.do_configure and CMakeCache.txt for accidental computer paths.
- CPU settings come from the machine configuration. Hardware codecs also need the right platform support.

FLOW-07. Build and package the SDK.

- Build the SDK and follow fetch, unpack, patch, configure, compile, install and package tasks.
- do_install writes under ${D}, not into the build computer’s /usr. Add missing installation steps if needed.
- Check libraries, plugins, resources, headers and CMake/pkg-config files.
- Use FILES to assign them to packages. Keep development and debug files separate where appropriate and fix packaging QA errors.

```bash
bitbake linphone-sdk
```

FLOW-08. Connect the application.

- The phone-ui recipe lists the SDK recipe in DEPENDS. This makes its headers, libraries and build-discovery files available in the application’s sysroot.
- The application uses the CMake package or pkg-config files actually supplied by that SDK version. Do not hard-code paths from the build computer.
- Yocto normally detects shared-library dependencies. Loaded plugins and data may need explicit RDEPENDS:${PN}, using output package names.

```bitbake
DEPENDS += "linphone-sdk"
```

FLOW-09. Select packages for the image.

- Add the application package through the product image or packagegroup. The example package name is phone-ui.
- Linked dependencies usually bring their library packages; include extra plugins and resources when required.
- Building the SDK alone does not put it in the image.
- A development SDK may need headers and other development files that the production image does not need.

```bitbake
IMAGE_INSTALL:append = " phone-ui"
```

FLOW-10. Set up application startup.

- If the system uses systemd, let the application recipe install its unit and describe it through the systemd class.
- Choose whether the service should start at boot. SDK libraries normally need no separate service.
- Check writable state directories and audio/video permissions.
- The application still needs network/SIP retry handling. Startup order alone cannot guarantee that a remote server is reachable.

```bitbake
inherit systemd
SYSTEMD_SERVICE:${PN} = "phone-ui.service"
```

FLOW-11. Check the image and the phone.

- Build the application and then the product image. Inspect package contents, the image manifest and root filesystem.
- Install that image using the board’s supported method. Check architecture, loader, libraries, plugins, certificates and settings.
- Test registration, incoming/outgoing calls, audio/video, restart and network recovery on the phone.
- Use application and service logs to locate failures.

On the build computer:

```bash
bitbake phone-ui
bitbake phone-image
```

On the device:

```bash
systemctl status phone-ui.service
journalctl -u phone-ui.service
```

FLOW-12. Make the result repeatable.

- Keep layer changes, source commits, patches and feature settings in version control.
- Build in CI without the developer’s workspace overrides. Keep manifests and test the same built image on hardware.
- Check that an SDK change rebuilds the application when needed and that the deployed executable matches its libraries.
- Include update and reboot checks. A successful SDK build is only one part of delivery.

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

- Use a supported Linux host and a pinned Kirkstone revision of Poky.
- The Kirkstone quick-build guide specifies at least 90 GB free disk and 8 GB RAM; allow additional space for SDKs and extra builds.
- Initialize with source oe-init-build-env build-lab.
- Set MACHINE = "qemuarm64" in conf/local.conf, run bitbake core-image-minimal and runqemu qemuarm64 nographic.
- Success means reaching a guest shell and checking uname -a and /proc/cmdline.
- QEMU does not reproduce every physical-board boot stage.

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

- From the build directory run bitbake-layers create-layer ../meta-lab and bitbake-layers add-layer ../meta-lab.
- Create ../hello with the following files and an actual source license; keep the source in version control.

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

- Run devtool add hello ../hello, inspect the generated source/license fields and inherit cmake, then run devtool build hello. Commit source changes as appropriate and run devtool finish hello ../meta-lab.
- Inspect the exported recipe and sources, then run bitbake hello without the workspace override. For this exercise add IMAGE_INSTALL:append = " hello" in local.conf, rebuild core-image-minimal and run hello in QEMU.
- In a product, maintain package selection in image/packagegroup metadata.

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

- Follow the BSP file's kernel workflow, using linux-yocto for this QEMU lab.
- Deliver a product-layer .bbappend, one applicable patch and a .cfg fragment.
- After leaving the devtool workspace, rebuild kernel and image and check the patch effect and final configuration.

LAB-04. Apply an overlay.

- Use a supported board and matching layer, for example Raspberry Pi with meta-raspberrypi.
- Compile the overlay, include it in boot artifacts and configure the real boot path to apply it.
- Reboot and check the live device tree and driver binding.
- A .dtbo in the deploy directory alone is insufficient; BSP explains the different U-Boot and Raspberry Pi firmware mechanisms.

RELEASE ARTIFACTS FOR VERSION-AWARE UPDATES

- Retain the exact released application, SDK and script artifacts after packaging transformations, not a later rebuild of the same source tag. Keep file inventories and checksums tied to image/platform and model compatibility.
- Build the phone-specific update from its detected source release and the target release; dynamic package assembly is not recompilation per phone. The project story transfers complete changed files; binary deltas can be considered separately as a transfer optimization.
- Check source-version compatibility and checksums, prepare a consistent target set and retain the affected previous files for recovery. If binary deltas are introduced separately, they require exact source files. A manual update.sh package can already be partial; the newer mechanism improves package selection and automation. This does not imply rootfs A/B or recovery from an unbootable BSP.

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Yocto supports hardware-specific composition, controlled versions and long-term image maintenance. The cost is metadata complexity, build time and responsibility for layer compatibility and security updates. Buildroot may be simpler for a smaller fixed image; a binary distribution may speed up development where its packages and update policy fit the device.

SECTION 6. PITFALLS AND SECURITY

A recipe compiling successfully does not prove its package is in the image. Distinguish build-time DEPENDS from runtime package dependencies, and host tools from target libraries. Pin compatible layers and sources, review licenses, protect signing credentials and test update and rollback behavior. Cache reuse does not replace target verification.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

Before our team joined, there was a basic Yocto platform skeleton. It did not include Linphone SDK, WebRTC or mediasoup. Our team added those components to the phone image, including their build dependencies, packages and the settings needed to run them. My personal contribution covered application/SDK work, BitBake metadata, packaging, image integration and testing on the device; the stack integration was a team effort.

SIP-BASED PHONE SOFTWARE: the CV lists Yocto/BitBake and i.MX. The Legend describes recipe and package work, SDK cross-compilation, image integration and service startup. The request asks for extensive Yocto, custom layers, recipes and image builds; Responsibilities distinguishes confirmed inherited-platform integration from unsupported full-platform ownership.

SECTION 8. INTERVIEW QUESTIONS

QUESTION YCT-01. What is a layer?

Answer: A layer groups recipes, appends, classes and configuration for one concern. conf/layer.conf declares how its metadata is discovered; bblayers.conf enables it in a build. A layer directory alone does not affect an image.

Example and checks: For the phone, keep board support separate from application and SDK changes. Enable the product layer explicitly and declare its dependencies. This makes it easier to update vendor layers without losing the phone integration. Check the final recipe selection when two layers provide the same component.

QUESTION YCT-02. What does .bbappend do?

Answer: A .bbappend extends a recipe whose name/version pattern matches. It can add patches, files, configuration or task fragments without copying the upstream recipe. bitbake-layers show-appends checks whether the intended match actually happens.

Example and checks: For example, a product append can add an SDK patch without copying the vendor recipe. Its filename still has to match the selected recipe. Check show-appends and the actual patch task. A patch file sitting in the layer is not enough.

QUESTION YCT-03. Why is a compiled binary absent from the image?

Answer: Compilation is only one step. The file must reach the recipe's install area, belong to an output package, be selected into the image and survive deployment. Inspect those stages before rebuilding everything.

Example and checks: Follow one concrete file, such as an SDK library, through installation, package contents and the image manifest. Then compare it with the phone filesystem. This shows where delivery diverged from the build. Rebuilding the library alone cannot add a package that the image never selected.

QUESTION YCT-04. What is the SDK for?

Answer: The SDK provides a cross-toolchain and target sysroot for application development outside the full image build. Its environment selects compiler, headers and libraries; the SDK must match the target configuration and ABI.

Example and checks: For an external application build, source the SDK environment and check its compiler and sysroot. A code generator running on the computer needs a host-compatible executable instead. Do not reuse an old desktop CMake cache. Validate the produced binary against the libraries actually installed on the phone.

QUESTION YCT-05. Is cache reuse a target test?

Answer: No. Shared-state reuse restores outputs whose task signatures match the cache. It does not execute a device scenario or establish boot, peripheral or media correctness; those need runtime validation.

Example and checks: An unchanged SDK may be restored quickly while another component is rebuilt. That is a build-time optimization, not a functional test. Check which inputs caused reuse or rebuilding. Always test important registration and media scenarios on the resulting image regardless of cache hits.

QUESTION YCT-06. What is the difference between MACHINE and DISTRO?

Answer: MACHINE selects hardware-specific configuration such as the board support and tuning. DISTRO selects distribution policy and features. An image selects a runtime package set; none of these concepts is interchangeable.

Example and checks: Imagine two phone models using one application codebase. Their board settings and available peripherals may differ, while product policy remains shared. The image still chooses the packages each model needs. Separate these choices before changing local.conf to fix a model-specific failure.

QUESTION YCT-07. How can you find which package contains a file?

Answer: Use oe-pkgdata-util find-path with built package metadata, then list-pkg-files for the matching package. Check the image manifest and deployed file as well: finding a provider does not prove the package was installed.

Example and checks: Follow one concrete file, such as an SDK library, through installation, package contents and the image manifest. Then compare it with the phone filesystem. This shows where delivery diverged from the build. Rebuilding the library alone cannot add a package that the image never selected.

QUESTION YCT-08. How do a recipe, package, packagegroup and image differ?

Answer: A recipe describes how to build and package a component; it can produce several packages. A packagegroup collects runtime package dependencies. The image assembles a chosen package set and filesystem artifacts for deployment.

Example and checks: Imagine two phone models using one application codebase. Their board settings and available peripherals may differ, while product policy remains shared. The image still chooses the packages each model needs. Separate these choices before changing local.conf to fix a model-specific failure.

QUESTION YCT-09. How would you organize vendor and product customizations?

Answer: Keep hardware support in BSP-oriented layers and product-specific applications, appends and policy in project layers. Declare compatible releases and dependencies, enable the layers explicitly and inspect the selected providers. This reduces the need to edit vendor metadata directly.

Example and checks: For the phone, keep board support separate from application and SDK changes. Enable the product layer explicitly and declare its dependencies. This makes it easier to update vendor layers without losing the phone integration. Check the final recipe selection when two layers provide the same component.

QUESTION YCT-10. Does layer priority override every configuration choice?

Answer: No. BBFILE_PRIORITY influences recipe selection, but version preferences, providers, overrides and parsing rules also matter. Inspect the chosen recipe and resolved variables rather than assuming the highest-priority layer wins every setting.

Example and checks: If the expected SDK recipe was not selected, inspect the available versions, provider preferences and final overrides. The layer priority is only part of that decision. Make a small change and confirm which recipe now runs. Do not infer selection from directory names alone.

QUESTION YCT-11. How do you add an application and its service to an image?

Answer: The recipe builds the application and installs executable, configuration and unit file into the staging area. Package metadata assigns the files and service integration. The image or packagegroup selects the runtime package; startup is verified on the device.

Example and checks: For a phone application, check both the executable package and its service unit. The unit must point to the installed path and have the intended enablement policy. Then boot the image without manually preparing the environment. This verifies the whole installation path, not only compilation.

QUESTION YCT-12. What is the difference between a native tool and target software?

Answer: A native tool runs on the build host, for example a code generator. Target libraries and executables use the target ABI and sysroot. Confusing them can link host libraries into a target build or try to run target code during compilation.

Example and checks: For an external application build, source the SDK environment and check its compiler and sysroot. A code generator running on the computer needs a host-compatible executable instead. Do not reuse an old desktop CMake cache. Validate the produced binary against the libraries actually installed on the phone.

QUESTION YCT-13. What are downloads and shared state used for?

Answer: The download directory stores fetched source artifacts; shared state stores reusable task outputs. They solve different caching problems. Pin source revisions and record configuration even when both caches are available; a cache is not a source-version policy.

Example and checks: An unchanged SDK may be restored quickly while another component is rebuilt. That is a build-time optimization, not a functional test. Check which inputs caused reuse or rebuilding. Always test important registration and media scenarios on the resulting image regardless of cache hits.

QUESTION YCT-14. How do you make a build reproducible?

Answer: Record layer revisions, source revisions, configuration, toolchain inputs and the intended target. Eliminate undeclared host dependencies and uncontrolled network fetches, then compare artifacts under controlled conditions. Pinning alone helps but is not proof of bit-for-bit reproducibility.

Example and checks: The old release used for a delta must be the exact file that was distributed. A fresh build from the same tag may differ because of tools or packaging. Keep the released files and their checksums. Use those records to reject a delta when the phone’s starting files do not match.

QUESTION YCT-15. How do you inspect image contents before flashing?

Answer: Inspect package metadata, the image manifest and the generated root filesystem or image contents. Check binaries, libraries, units, permissions and model-specific configuration, then confirm that the same artifact is deployed. A recipe log alone cannot establish image contents.

Example and checks: Follow one concrete file, such as an SDK library, through installation, package contents and the image manifest. Then compare it with the phone filesystem. This shows where delivery diverged from the build. Rebuilding the library alone cannot add a package that the image never selected.

QUESTION YCT-16. How do you reduce image size safely?

Answer: Measure package and file contributions first. Remove unnecessary packages/features or development artifacts, preserving runtime dependencies, licenses and diagnostics required for support. Compare startup and product scenarios afterwards; stripping symbols alone is not a complete size strategy.

Example and checks: Measure which packages and files occupy space before removing them. An unused development package is different from a library required by a codec. After a change, repeat startup, calling and diagnostics checks. Also keep license information and matching symbols where they are required.

QUESTION YCT-17. What must be checked for a read-only root filesystem?

Answer: Identify every writer: logs, caches, application state, credentials and update mechanisms. Provide deliberate writable or volatile locations and verify service behavior after reboot. A read-only image flag cannot repair applications that assume arbitrary writable paths.

Example and checks: For example, SIP settings must survive reboot while temporary caches may not need to. Put each type of data in the appropriate writable location. Check permissions from the actual service user. Test a clean boot so missing directories are not accidentally supplied by a developer’s previous session.

QUESTION YCT-18. How would you plan an image update and rollback?

Answer: Identify compatible boot, kernel, device-tree, rootfs and persistent-data versions. Verify artifact authenticity, interrupted-update behavior and a known-good recovery path on a test device. Data migrations can prevent rollback even when an old executable still boots.

Example and checks: Before activation, record the exact previous release and preserve its complete matching files. Keep a way to select them again after failure. Check shared settings as well as binaries. Recovery is incomplete if the old executable returns but can no longer read the data it needs.

QUESTION YCT-19. How do licenses and security updates enter the workflow?

Answer: Review recipe license metadata and license manifests, track source revisions and build history and assess relevant vulnerability reports. Apply compatible fixes, rebuild and validate the resulting image. A successful CVE scan is one input, not proof that the product is secure.

Example and checks: For an SDK dependency update, check the changed source and license text as well as vulnerability reports. Decide whether the issue applies to the enabled features. Rebuild the affected components and test the resulting phone image. A scan result is evidence to assess, not an automatic statement that the product is safe.

QUESTION YCT-20. How do you separate theoretical Yocto knowledge from personal ownership?

Answer: Explain the technical mechanism, then identify the concrete recipes, packages and image integration actually handled. Keep creating a distribution or BSP from scratch separate from working in inherited layers. This prevents a conceptual answer from becoming an unsupported experience claim.

Example and checks: A useful interview example names the component, the changed recipe and the device check. Adding Linphone to an existing platform is substantial work, but different from writing every BSP component. State what was done by the team and what you personally changed. Keep hypothetical design advice separate from delivered work.

QUESTION YCT-21. How do Poky, OpenEmbedded and BitBake differ?

Answer: Poky is a reference integration, OpenEmbedded supplies metadata and the build ecosystem, and BitBake executes tasks. Product layers/configuration produce the actual device image.

Example and checks: On the project, the board baseline was the starting point rather than the complete phone product. Product layers added the telephony and conferencing components. BitBake executed their recipes along with the platform tasks. This example shows how the reference tools and the product-specific content fit together.

QUESTION YCT-22. What belongs in bblayers.conf and local.conf?

Answer: bblayers.conf enables layers; local.conf holds local settings such as MACHINE. MACHINE selects hardware/tuning, DISTRO selects policy, and the image selects packages.

Example and checks: Imagine two phone models using one application codebase. Their board settings and available peripherals may differ, while product policy remains shared. The image still chooses the packages each model needs. Separate these choices before changing local.conf to fix a model-specific failure.

QUESTION YCT-23. How do downloads and sstate-cache differ?

Answer: DL_DIR preserves fetched inputs; SSTATE_DIR preserves reusable task outputs. Reuse depends on signatures and compatible inputs. Neither cache repairs undeclared dependencies.

Example and checks: An unchanged SDK may be restored quickly while another component is rebuilt. That is a build-time optimization, not a functional test. Check which inputs caused reuse or rebuilding. Always test important registration and media scenarios on the resulting image regardless of cache hits.

QUESTION YCT-24. What proves the recipe lab is complete?

Answer: The exported recipe builds without a workspace override, the package is in the image manifest and hello runs in the rebuilt guest. Workspace-only compilation proves less.

Example and checks: First export the recipe and any changes from the workspace into the maintained layer. Build again through that layer and inspect the image manifest. Finally run the application in the rebuilt guest. This detects work that succeeded locally only because temporary developer files were still active.

QUESTION YCT-25. Why keep exact released artifacts instead of rebuilding the old Git tag?

Answer: Toolchain, metadata or packaging differences can change bytes. A binary delta requires the exact original file checksum. Retain distributed artifacts and compatibility metadata; a matching version label alone is insufficient.

Example and checks: The old release used for a delta must be the exact file that was distributed. A fresh build from the same tag may differ because of tools or packaging. Keep the released files and their checksums. Use those records to reject a delta when the phone’s starting files do not match.

QUESTION YCT-26. What must be retained to recover the exact pre-update release?

Answer: A complete consistent executable/library/script/resource set, metadata and the previous activation state. Persistent data must remain compatible or have a restoration path. A reverse delta or a version number alone is not a recovery plan.

Example and checks: Before activation, record the exact previous release and preserve its complete matching files. Keep a way to select them again after failure. Check shared settings as well as binaries. Recovery is incomplete if the old executable returns but can no longer read the data it needs.

SECTION 9. SOURCES

Research date: 2026-11-15

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
- https://www.daemonology.net/bsdiff/
