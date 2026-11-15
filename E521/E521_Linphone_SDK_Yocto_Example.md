LINPHONE SDK IN YOCTO: PRACTICAL INTEGRATION EXAMPLE

01. PURPOSE

This complete learning example adds the official SDK recipe layer, applies project settings and builds a small C++ program using liblinphone. It then includes both components in a Linux image and checks execution. It illustrates an implementation rather than reproducing the project's historical recipe.

Run the commands in Bash on a Linux host prepared for Yocto Kirkstone. Windows PowerShell is not a suitable build environment. The standalone exercise uses qemuarm64. An existing phone product keeps its own MACHINE, BSP, DISTRO and image recipe instead of adopting the QEMU configuration. This example has not been built here; its settings were checked against the official sources listed below.

02. THE INTEGRATION PATH

Reading order: sections 01–12 give the main path from layers to execution. Sections 13–18 explain files, tasks, the supplied original recipe, its audit, improvements and patches. Sections 19–23 add a product image, systemd, a Core check, an external SDK and diagnostics. Sections 24–26 cover reproducibility, updates, acceptance and an interview answer. This English file and its Russian companion have matching sections and identical code examples.

- meta-bc: upstream recipes for Linphone SDK
- meta-phone: our settings and application recipe
- linphone-sdk: builds and packages the SDK
- linphone-probe: links a C++ executable to liblinphone
- core-image-minimal: includes the runtime packages

Use the SDK recipe from the official meta-bc layer and keep project changes in a separate layer through a .bbappend. The SDK contains several components, and the upstream recipe handles their build details. This example therefore does not invent a short universal SDK recipe with guessed CMake flags. The complete custom .bb below builds the application; the .bbappend extends the actual SDK recipe.

03. CHECK OUT THE LAYERS

Start in a new directory on a host with the build dependencies from Yocto System Requirements already installed. These commands do not install the host dependencies.

```bash
mkdir -p "$HOME/yocto-linphone-lab"
cd "$HOME/yocto-linphone-lab"

git clone --branch kirkstone https://git.yoctoproject.org/poky
git clone --branch kirkstone https://git.openembedded.org/meta-openembedded
git clone --branch feature/yocto-kirkstone \
    https://gitlab.linphone.org/BC/public/meta-bc.git

cat > enter-build.sh <<'EOF'
export PREFERED_LINPHONE_SDK_RECIPE_VERSION="5.3.x"
unset LATEST_REVISIONS LINPHONE_SDK_REV LINPHONE_SDK_BRANCH
export BB_ENV_PASSTHROUGH_ADDITIONS="${BB_ENV_PASSTHROUGH_ADDITIONS:-} PREFERED_LINPHONE_SDK_RECIPE_VERSION"
source poky/oe-init-build-env build
EOF

source enter-build.sh

bitbake-layers add-layer ../meta-openembedded/meta-oe
bitbake-layers add-layer ../meta-openembedded/meta-networking
bitbake-layers add-layer ../meta-openembedded/meta-python
bitbake-layers add-layer ../meta-openembedded/meta-multimedia
bitbake-layers add-layer ../meta-bc

bitbake-layers create-layer ../meta-phone
bitbake-layers add-layer ../meta-phone

mkdir -p ../meta-phone/recipes-connectivity/linphone-sdk
mkdir -p ../meta-phone/recipes-apps/linphone-probe/files
```

PREFERED_LINPHONE_SDK_RECIPE_VERSION intentionally has one R in PREFERED: this is the upstream variable name. The value 5.3.x selects a recipe family; the selected metadata determines the exact source commit. It does not establish the SDK version used in the real project. In a new session, run source enter-build.sh from yocto-linphone-lab; it changes the current directory to build.

04. EXTEND THE SDK RECIPE

FILE: meta-phone/recipes-connectivity/linphone-sdk/linphone-sdk_%.bbappend

```bitbake
# Keep this learning example audio-only.
PACKAGECONFIG:remove = "video h264"

# The upstream SDK uses a non-standard installation prefix.
# Make headers and libraries available to dependent recipes.
SYSROOT_DIRS:append = " /opt/belledonne-communications"
```

Create the file at the path shown. All FILE paths are relative to yocto-linphone-lab; the remaining commands run from build. The % matches the selected linphone-sdk recipe version. The show-appends check below must confirm that the append applies.

Video is disabled only to simplify the exercise. A video phone keeps it enabled and separately validates codecs, devices and licensing. SYSROOT_DIRS is needed because /opt is outside Yocto's usual library locations. It makes files available when another recipe builds; it does not install a package into the image. Keep the SDK's upstream LICENSE and LIC_FILES_CHKSUM rather than replacing them with CLOSED or MIT.

05. A SMALL C++ APPLICATION

FILE: meta-phone/recipes-apps/linphone-probe/files/main.cpp

```cpp
#include <iostream>
#include <linphone/linphonecore.h>

int main()
{
    const char *version = linphone_core_get_version();
    if (version == nullptr) {
        std::cerr << "Linphone SDK returned no version\n";
        return 1;
    }

    std::cout << "Linphone SDK version: " << version << '\n';
    return 0;
}
```

The program checks header availability, linking and library loading. It does not create a SIP account or prove that calls work. This small test separates SDK integration problems from application behavior.

FILE: meta-phone/recipes-apps/linphone-probe/files/CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(linphone_probe LANGUAGES CXX)

include(GNUInstallDirs)

if(NOT LINPHONE_SDK_ROOT)
    message(FATAL_ERROR "LINPHONE_SDK_ROOT must point into the recipe sysroot")
endif()

find_path(LINPHONE_INCLUDE_DIR
    NAMES linphone/linphonecore.h
    PATHS "${LINPHONE_SDK_ROOT}/include"
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

find_library(LINPHONE_LIBRARY
    NAMES linphone
    PATHS "${LINPHONE_SDK_ROOT}/lib"
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

if(NOT LINPHONE_INCLUDE_DIR OR NOT LINPHONE_LIBRARY)
    message(FATAL_ERROR "Linphone headers or library are missing from the sysroot")
endif()

add_executable(linphone-probe main.cpp)
target_compile_features(linphone-probe PRIVATE cxx_std_17)
target_include_directories(linphone-probe PRIVATE "${LINPHONE_INCLUDE_DIR}")
target_link_libraries(linphone-probe PRIVATE "${LINPHONE_LIBRARY}")
target_link_options(linphone-probe PRIVATE
    "-Wl,-rpath-link,${LINPHONE_SDK_ROOT}/lib")

# Do not embed build-host paths in the installed executable.
set_target_properties(linphone-probe PROPERTIES
    SKIP_BUILD_RPATH TRUE
    INSTALL_RPATH "")

install(TARGETS linphone-probe RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
```

The recipe supplies the SDK path. Searching only inside the target sysroot prevents accidental use of host libraries. The rpath-link option helps the linker find liblinphone dependencies during the build. It does not configure library lookup on the phone; runtime lookup is checked separately.

06. THE APPLICATION RECIPE

FILE: meta-phone/recipes-apps/linphone-probe/linphone-probe_1.0.bb

```bitbake
SUMMARY = "Small C++ executable checking Linphone SDK integration"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
    file://main.cpp \
    file://CMakeLists.txt \
"
S = "${WORKDIR}"

DEPENDS = "linphone-sdk"
RDEPENDS:${PN} += "linphone-sdk"

inherit cmake

EXTRA_OECMAKE += " \
    -DLINPHONE_SDK_ROOT=${RECIPE_SYSROOT}/opt/belledonne-communications \
"
```

MIT describes our example code. Using liblinphone retains the SDK's separate licensing obligations. A production product reviews the complete selected build, including codecs.

- DEPENDS: SDK headers and libraries are prepared before compilation
- RDEPENDS: the runtime SDK package accompanies the executable
- inherit cmake: Yocto supplies the cross-toolchain and runs configuration, compilation and installation
- do_install: CMake installs into the recipe's staging directory through DESTDIR
- FILES: the standard package rules already cover /usr/bin/linphone-probe

07. IMAGE CONFIGURATION

Add these lines to the existing build/conf/local.conf once, without replacing the file. debug-tweaks permits passwordless access to the local learning image; do not carry it into the phone image.

```bitbake
MACHINE = "qemuarm64"
PACKAGE_CLASSES = "package_ipk"
EXTRA_IMAGE_FEATURES:append = " debug-tweaks"
IMAGE_INSTALL:append = " linphone-sdk linphone-probe"
```

A product normally keeps image contents in its own image recipe or packagegroup. This example uses local.conf for brevity. DEPENDS does not replace IMAGE_INSTALL: a successfully built library is not necessarily installed on the device. Header packages ending in -dev and debug packages ending in -dbg are also unnecessary in a normal runtime image.

08. INSPECT AND BUILD

```bash
bitbake-layers show-layers
bitbake-layers show-recipes linphone-sdk
bitbake-layers show-appends

bitbake -e linphone-sdk > linphone-sdk.environment.txt
grep -E '^(FILE|PV|SRC_URI|SRCREV|SRCREV_[A-Za-z0-9_]+|PACKAGECONFIG|SYSROOT_DIRS|LICENSE)=' \
    linphone-sdk.environment.txt

# Read the actual upstream SDK recipe selected by BitBake.
sdk_recipe=$(sed -n 's/^FILE="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
sed -n '1,220p' "$sdk_recipe"

for layer in poky meta-openembedded meta-bc; do
    printf '%s %s\n' "$layer" "$(git -C "../$layer" rev-parse HEAD)"
done > layers.lock.txt

bitbake linphone-sdk
bitbake linphone-probe
bitbake core-image-minimal

oe-pkgdata-util list-pkg-files linphone-sdk
oe-pkgdata-util list-pkg-files linphone-probe
grep -E 'linphone-sdk|linphone-probe' \
    tmp/deploy/images/qemuarm64/core-image-minimal-qemuarm64.manifest
```

Before building, inspect the selected .bb, its sources and the applied .bbappend. Reproducibility requires layer commits, our meta-phone changes and exact SDK source revisions. Recording only 5.3.x is insufficient. If upstream uses floating revisions or fetches additional sources during compilation, pin those too; layers.lock.txt alone does not do that. Keep the full bitbake -e output local because it contains build paths and environment data.

The SDK package should provide runtime libraries under /opt/belledonne-communications, and linphone-probe should provide /usr/bin/linphone-probe. If upstream splits libraries into additional packages, inspect their names using pkgdata and adjust RDEPENDS to match the actual output. Do not add every -dev package to the image to conceal packaging errors.

09. RUN THE IMAGE

BUILD HOST

```bash
runqemu qemuarm64 core-image-minimal nographic slirp
```

GUEST CONSOLE, LOG IN AS root

```bash
ls -l /opt/belledonne-communications/lib/liblinphone.so*
LD_LIBRARY_PATH=/opt/belledonne-communications/lib \
    /usr/bin/linphone-probe
```

Expect Linphone SDK version: followed by the actual built version. LD_LIBRARY_PATH applies only to this process. A phone configures the path for its application service or through the dynamic loader configuration when supported by its libc. Never put build/tmp/... paths into device configuration. Exit QEMU with Ctrl+A followed by X.

10. DEVELOPMENT COMMANDS

```bash
# Run a specific stage and inspect the task output.
bitbake -c fetch linphone-sdk
bitbake -c unpack linphone-sdk
bitbake -c configure linphone-sdk

# Print paths to source, build directory and task logs.
bitbake -e linphone-sdk | grep -E '^(S|B|T|WORKDIR)='

# Rebuild after changing the application files or metadata.
bitbake linphone-probe
bitbake core-image-minimal

# Inspect the final application configuration and sysroot location.
bitbake -e linphone-probe | \
    grep -E '^(RECIPE_SYSROOT|DEPENDS|RDEPENDS:linphone-probe|EXTRA_OECMAKE)='

# Optional: generate an external cross-development SDK for this image.
bitbake -c populate_sdk core-image-minimal
```

SEPARATE INTERACTIVE COMMAND

```bash
bitbake -c devshell linphone-sdk
# Inspect the development environment, then leave this shell:
exit
```

devshell opens a separate shell; use exit before continuing in the original shell. The T directory contains log.do_configure, log.do_compile and log.do_install. Running bitbake again normally detects recipe and local source changes. Routine cleanall calls are unnecessary: they delete downloaded sources and defeat caching.

For an SDK change, inspect SRC_URI and S first. If the affected file is in the source tree handled by do_patch, keep the patch in the project layer and add FILESEXTRAPATHS:prepend := "${THISDIR}/files:" plus a file URI in SRC_URI:append. If the SDK's internal build downloads the component later, ordinary do_patch may run before that component exists. Use the upstream mechanism or a pinned component fork in that case. Having a .bbappend alone does not ensure that a patch reaches the correct submodule.

11. COMMON FAILURES

- No recipes available for .bbappend: check the selected recipe name and version with show-recipes
- Header not found: check DEPENDS, do_populate_sysroot and the /opt directory in the consumer's RECIPE_SYSROOT
- Cannot find -llinphone: check that the target library and linker symlink exist in the searched lib directory
- Shared library not found at runtime: check installed packages and the device loader search path
- Wrong architecture or file format: check MACHINE and the compiler command; do not copy host libraries into the image
- Installed but not shipped: inspect the upstream package split and add the precise missing path to the correct package's FILES
- License or codec configuration failure: inspect the exact recipe requirement rather than accepting every commercial flag globally

12. WHAT THIS PROVES

A successful run establishes that Yocto built the SDK for the target architecture, the application received its headers and libraries, and the image contains enough files to load liblinphone. A separate phone application test must then cover SIP registration, incoming and outgoing calls, two-way audio, call termination, network loss and server failover. A video phone also needs camera, codec and video-call checks. QEMU cannot replace validation of the real phone's audio path and hardware.

13. FILES AND HOST CHECKS

The base exercise creates the following files. Create the application sources and recipes from sections 04–06 before running the build commands. The extra files in sections 18–20 are optional extensions; they are not prerequisites for printing the SDK version.

```text
yocto-linphone-lab/
  enter-build.sh
  poky/
  meta-openembedded/
  meta-bc/
  meta-phone/
    conf/layer.conf
    recipes-connectivity/linphone-sdk/linphone-sdk_%.bbappend
    recipes-apps/linphone-probe/linphone-probe_1.0.bb
    recipes-apps/linphone-probe/files/main.cpp
    recipes-apps/linphone-probe/files/CMakeLists.txt
  build/
    conf/bblayers.conf
    conf/local.conf
    layers.lock.txt
    linphone-sdk.environment.txt
    tmp/deploy/images/qemuarm64/
    tmp/deploy/ipk/
```

Use a supported Linux distribution and a normal user account. Check disk space, RAM and available CPUs before a long build. The actual requirement grows with Qt, video codecs, debug packages and cached build outputs; do not treat one quoted disk-size estimate as a guarantee. An existing product build should keep its current host setup and BSP configuration.

```bash
# Run on the Linux build host.
id -un
df -h .
free -h
nproc
git --version
python3 --version
locale

# From build/, confirm where BitBake will write its outputs.
bitbake -e linphone-sdk |     grep -E '^(MACHINE|DISTRO|TARGET_ARCH|TUNE_FEATURES|TMPDIR|DL_DIR|SSTATE_DIR)='
```

bitbake-layers create-layer generates conf/layer.conf. Its BBFILES patterns must include our two-level recipe directories, and LAYERSERIES_COMPAT must include kirkstone. In the supplied original layer the collection name is bc. Build-time dependencies such as Qt still need their own recipe providers; declaring a layer compatible does not supply them.

14. WHAT BITBAKE DOES STEP BY STEP

The important point is that source files, installation staging, the consumer sysroot, binary packages and the final device filesystem are different things. A file appearing in one of them does not automatically prove it reached the others.

- do_fetch obtains the SDK source and the submodules described by the fetcher.
- do_unpack prepares the source tree S.
- do_patch applies patches listed in SRC_URI.
- do_configure generates build files using a target toolchain.
- do_compile produces target binaries in B or the SDK's internal build directories.
- do_install installs files into D, a temporary filesystem tree.
- do_populate_sysroot exposes selected installed files to dependent recipes.
- do_package assigns installed files to runtime, development and debug packages.
- Package writing produces .ipk files in this exercise.
- The image's do_rootfs installs the selected packages into IMAGE_ROOTFS.
- Image creation turns that root filesystem into the configured image formats.

This is not one completely sequential chain: packaging and sysroot publication serve different consumers. DEPENDS connects the application build to the SDK's sysroot output. RDEPENDS and IMAGE_INSTALL connect runtime packages to the final root filesystem. Inherit cmake supplies standard build tasks for our small application; the SDK has its own more complex build behavior.

```bash
bitbake -c listtasks linphone-sdk
bitbake -g linphone-probe
# Inspect recipe-depends.dot and task-depends.dot in build/.
grep -n 'linphone-sdk' recipe-depends.dot | head -n 20
```

15. THE ORIGINAL RECIPE SUPPLIED FOR THIS REVIEW

Companion reading: E521_Linphone_SDK_Original_Recipe_Walkthrough.md explains every line of the supplied recipe, local CMake class and layer configuration using stable R/C/L identifiers.

The candidate supplied a local copy at C:\Users\User\Downloads\meta-bc. Its actual layer root is the nested meta-bc directory. The reviewed files are recipes-bc/linphone-sdk/linphone-sdk/linphone-sdk_latest.bb, classes/cmakebuilder.bbclass and conf/layer.conf. The source copy was inspected without modification. Private Git host and repository names are intentionally omitted from this guide.

This is a product-specific variant, not the unmodified public Kirkstone recipe. It contains only linphone-sdk_latest.bb. Therefore the 5.3.x selector in the standalone public exercise must not be carried into this local layer: use latest for the supplied recipe. The public QEMU exercise and this phone-specific case are separate configurations.

```bitbake
# Selector for the supplied product layer, not the public exercise.
PREFERED_LINPHONE_SDK_RECIPE_VERSION = "latest"
PREFERRED_VERSION_linphone-sdk = "latest"
```

The recipe fetches a Git repository with submodules through gitsm and a literal main branch. It declares AGPL-3.0-or-later and a checksum for LICENSE.txt. It inherits both a custom cmakebuilder class and cmake_qt5, plus helper classes. Because cmake_qt5 itself inherits cmake, inspect the final expanded do_configure, do_compile and do_install before attributing a task to one class. Inheritance order can affect which implementation actually runs.

- Direct dependencies include Qt base/tools/QML controls/multimedia/Wayland, native build tools, ALSA, PulseAudio, TLS, XML, database and codec libraries.
- PACKAGECONFIG defaults include bzrtp, opus, sqlite, zlib, video, g2d, imxvpuh264, amr, tiff and zxing.
- CMake options select the Yocto platform, C++ wrapper, vCard, XML and several audio codecs; tests are enabled.
- The version text passed to CMake is 5.3.0-alpha-175-g28018be13. This text alone does not identify the fetched commit.
- The intermediate SDK prefix is WORKDIR/build/linphone-sdk/desktop.
- The final device prefix is /opt/belledonne-communications.
- Installation moves staged content to that final prefix and copies selected plugins and metadata when present.
- The recipe writes an ld.so.conf.d file and declares runtime, development and debug packages.

The original requires the product's Qt layer and the matching i.MX BSP providers, in addition to the general OpenEmbedded layers. Features g2d and imxvpuh264 request imx-vpuwrap. Simply adding this layer to a generic QEMU build is not enough. Disabling PACKAGECONFIG video alone also leaves unconditional Qt and codec dependencies in DEPENDS; it does not turn this recipe into a minimal audio-only SDK build.

The following exact extracts show actual settings in the supplied recipe. They do not replace the complete file: the private SRC_URI, remaining dependencies and installation functions are omitted. Keep these observed settings separate from the proposed improvements in subsequent sections.

```bitbake
# Extracts from the supplied product recipe; not a standalone recipe.
S = "${WORKDIR}/git"
LICENSE = "AGPL-3.0-or-later"

inherit cmakebuilder gettext pkgconfig chrpath perlnative ${VERSION_DEPENDENT_INHERIT} cmake_qt5
inherit gitpkgv

PACKAGECONFIG ??= "bzrtp opus sqlite zlib video g2d imxvpuh264 amr tiff zxing"
PACKAGECONFIG[opus] = "-DENABLE_OPUS=YES, -DENABLE_OPUS=NO, libopus"
PACKAGECONFIG[imxvpuh264] = "-DENABLE_IMXVPUH264=YES, -DENABLE_IMXVPUH264=NO, imx-vpuwrap"
PACKAGECONFIG[g2d] = "-DENABLE_G2D=YES -DENABLE_VPU=YES, -DENABLE_G2D=NO, imx-vpuwrap"

EXTRA_OECMAKE += " -DLINPHONESDK_PLATFORM=Yocto"
EXTRA_OECMAKE += " -DLINPHONESDK_VERSION=5.3.0-alpha-175-g28018be13"
EXTRA_OECMAKE += " -DENABLE_UNIT_TESTS=YES -DENABLE_TESTS=YES"
EXTRA_OECMAKE += " -DCMAKE_SKIP_RPATH=YES"

BUILD_INSTALL_PREFIX = "${WORKDIR}/build/linphone-sdk/desktop"
INSTALL_PATH_OUT = "/opt/belledonne-communications"
INSTALL_PATH = ""
BUILD_INSTALL_PATH = "${BUILD_INSTALL_PREFIX}${INSTALL_PATH}"
OECMAKE_EXTRA_ROOT_PATH = "${BUILD_INSTALL_PATH}"

EXTRA_OECMAKE += " -DCMAKE_STAGING_PREFIX=${BUILD_INSTALL_PATH}"
EXTRA_OECMAKE += " -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH}"

PACKAGES = "${PN} ${PN}-dev ${PN}-dbg"
FILES:${PN} += "${INSTALL_PATH_OUT}/lib/*"
FILES:${PN}-dev = "${INSTALL_PATH_OUT}/include/*"
SYSROOT_DIRS += "/opt"
```

16. ORIGINAL RECIPE AUDIT: WHAT TO CHECK AND WHY

These are findings from the supplied text, not results of a completed target build. Preserve the original snapshot, fix a working copy and check each stage. Some findings are definite metadata mistakes; others require the expanded metadata or actual install output to determine their practical effect.

- AUDIT-01. The last file rule is ILES:${PN}, missing F. It does not extend FILES. The default FILES rules may still include /etc, so the typo alone does not prove that belledonne.conf is missing from the package. Check pkgdata.
- AUDIT-02. DEFAULT_COMMIT is AUTOREV. Without an explicit LINPHONE_SDK_REV, even with LATEST_REVISIONS unset, the fallback remains floating. The same recipe can fetch different source on different days.
- AUDIT-03. LINPHONE_SDK_BRANCH is assigned from the environment, but SRC_URI uses branch=main literally. Changing the environment variable does not change this fetcher's branch.
- AUDIT-04. cmakebuilder contains FILES_${PN}-dev and OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM_class-native. These use old override notation. Migrate them to FILES:${PN}-dev and OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM:class-native for Kirkstone.
- AUDIT-05. zxing is selected in PACKAGECONFIG without a matching PACKAGECONFIG[zxing] declaration in the supplied recipe. No fetched source inspection is needed to see that omission. Check whether another append supplies it before deciding how to fix it.
- AUDIT-06. LINPHONE_SDK_LIC_FILES_CHKSUM populates LIC_FILES_CHKSUM_ENV, while LIC_FILES_CHKSUM uses a separate literal checksum. The environment-derived value is not connected to that assignment.
- AUDIT-07. CMAKEOPTS contains version options, but the supplied custom class passes EXTRA_OECMAKE. Check final task scripts before assuming CMAKEOPTS changes the CMake command.
- AUDIT-08. PACKAGES puts the broad runtime package first, and its FILES includes the entire /opt library and share trees. Development symlinks, static archives, CMake files, pkg-config files or debug directories can be captured by the runtime package before more specific packages see them.
- AUDIT-09. INSANE_SKIP disables dev-so, staticdev, already-stripped and installed-vs-shipped. These skips can conceal packaging or symbol problems. Remove a skip after fixing its cause and rebuilding; do not remove all blindly.
- AUDIT-10. Optional copies and the staging move use conditional checks or ignore failures. A successful task can therefore omit an expected plugin or silently skip a move. Mandatory outputs need explicit existence checks.
- AUDIT-11. Build-host CMake and pkg-config metadata is copied into the runtime prefix. Such files may contain build paths or describe the wrong installation location. Inspect them and keep development metadata in -dev when appropriate.
- AUDIT-12. layer.conf assigns LICENSE_FLAGS_ACCEPTED rather than appending to product policy. It may replace other accepted flags. A reusable layer should not silently decide the product's license policy.
- AUDIT-13. The Qt multimedia workaround creates a symlink inside RECIPE_SYSROOT. It needs a comment explaining the affected Qt/BSP combination, checks for the intended target directory and a regression test when that combination changes.
- AUDIT-14. Both custom and standard CMake classes participate. Confirm which toolchain generator and install function survive expansion; do not diagnose installation from one class file alone.

```bash
# Run from the existing phone build, with its normal layers enabled.
bitbake -p
bitbake -e linphone-sdk > linphone-sdk.environment.txt
grep -E '^(FILE|SRC_URI|SRCREV|DEFAULT_COMMIT|PACKAGECONFIG|PACKAGECONFIG_CONFARGS|PACKAGES|INSANE_SKIP:linphone-sdk|LIC_FILES_CHKSUM|EXTRA_OECMAKE|CMAKEOPTS)=' \
+    linphone-sdk.environment.txt

# Display expanded task bodies and their metadata comments.
sed -n '/^do_configure()/,/^}/p' linphone-sdk.environment.txt
sed -n '/^do_compile()/,/^}/p' linphone-sdk.environment.txt
sed -n '/^do_install()/,/^}/p' linphone-sdk.environment.txt
```

17. A CONTROLLED IMPROVEMENT OF THE ORIGINAL

First fix the old override notation in a version-controlled working copy of cmakebuilder.bbclass; an append cannot reliably repair a class that fails parsing. Fix the ILES typo in the maintained recipe. Keep the product source URI and approved branch in private metadata. Do not copy the private URI into public documentation.

```bitbake
# Corrected declarations in the maintained source files.
FILES:${PN}-dev += "${libdir}/cmake ${datadir}/cmake"
OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM:class-native = "BOTH"
FILES:${PN}:append = " ${sysconfdir}/ld.so.conf.d/belledonne.conf"
```

For the supplied recipe, the existing environment hook can pin the source without changing the private source URL. The following is an alternative entry sequence for the existing phone build, not a continuation of enter-build.sh from section 03. Enter a reviewed full commit from the source repository; the command validates its format but cannot prove that the commit belongs to main. do_fetch provides that check against the configured repository.

```bash
read -r -p "Approved 40-character SDK commit: " phone_sdk_rev
if [[ ! "$phone_sdk_rev" =~ ^[0-9a-fA-F]{40}$ ]]; then
    printf '%s
' "A full Git commit is required" >&2
    return 1 2>/dev/null || exit 1
fi
export LINPHONE_SDK_REV="$phone_sdk_rev"
export PREFERED_LINPHONE_SDK_RECIPE_VERSION="latest"
unset LATEST_REVISIONS
export BB_ENV_PASSTHROUGH_ADDITIONS="${BB_ENV_PASSTHROUGH_ADDITIONS:-} LINPHONE_SDK_REV PREFERED_LINPHONE_SDK_RECIPE_VERSION"

# Now source the phone project's normal build-entry script.
# Do not source section 03's enter-build.sh: it deliberately clears this pin.
```

After entering the product build, check bitbake -e and fetch the source. Pin the parent Git commit and preserve its recorded submodule commits. A displayed version string and a successful clone are not substitutes for that record. Keep the branch literal main unless a reviewed product change deliberately replaces it.

FILE: meta-phone/recipes-connectivity/linphone-sdk/linphone-sdk_latest.bbappend

```bitbake
# Product variant only. Replace the generic %.bbappend with this file;
# do not keep both examples active unintentionally.
FILES:${PN}:append = " ${sysconfdir}/ld.so.conf.d/belledonne.conf"

do_install:append() {
    test -d "${D}/opt/belledonne-communications/include/linphone" || \
+        bbfatal "Linphone headers were not installed"
    test -d "${D}/opt/belledonne-communications/lib" || \
+        bbfatal "Linphone library directory was not installed"
    find "${D}/opt/belledonne-communications/lib" -maxdepth 1 \
+        -name 'liblinphone.so*' -print -quit | grep -q . || \
+        bbfatal "liblinphone shared library was not installed"
    test -s "${D}${sysconfdir}/ld.so.conf.d/belledonne.conf" || \
+        bbfatal "Dynamic-loader configuration was not installed"
}
```

This append adds early checks; it does not repair every audit finding. For example, the final package split should assign specific development files before the broad runtime package, and mandatory plugins need checks matched to the enabled configuration. First inspect packages-split, then change PACKAGES and FILES together. A blanket rewrite without the actual output could break an intentional plugin layout.

18. PATCHES AND DEVTOOL

For a normal application recipe, devtool provides a convenient edit/build/export cycle. The following optional demonstration changes only our local probe, so it does not require the private SDK source. It adds a configure-time message, so it remains compatible with the alternative main.cpp in section 21.

```bash
devtool modify linphone-probe
python3 - <<'PY'
from pathlib import Path
p = Path("workspace/sources/linphone-probe/CMakeLists.txt")
s = p.read_text()
message = 'message(STATUS "Building the phone SDK integration probe")'
assert message not in s
p.write_text(s + "\n" + message + "\n")
PY
git -C workspace/sources/linphone-probe add CMakeLists.txt
git -C workspace/sources/linphone-probe \
+    -c user.name="Example Author" -c user.email="example@example.org" \
+    commit -m "Describe the SDK probe during CMake configuration"
devtool build linphone-probe
devtool finish linphone-probe ../meta-phone
bitbake-layers show-appends
bitbake linphone-probe
```

For the SDK, inspect the source tree after unpacking before choosing a patch location. gitsm fetches tracked submodules, but the SDK superbuild may perform additional work of its own. A patch for liblinphone belongs to the component's real source location; a patch for the top-level SDK CMake belongs to the superbuild. Export the change with git format-patch from the repository where the change was committed and inspect the paths in the resulting patch.

The integration mechanism is FILESEXTRAPATHS plus a file entry in SRC_URI. The concrete patch name must match a real exported file. Validate the result with do_patch, inspect the affected source and then rebuild. Never regard a successful do_patch as proof that the rebuilt application is using that component rather than a different staged copy.

```bash
bitbake -c patch linphone-sdk
bitbake -e linphone-sdk | grep -E '^(S|T|SRC_URI)='
bitbake linphone-sdk linphone-probe
```

19. MOVE IMAGE CONTENTS INTO PRODUCT METADATA

The following optional files replace the exercise-only IMAGE_INSTALL addition in local.conf. Create both directories first. Keep MACHINE, DISTRO and package format in their appropriate build or product configuration. This example uses the public/QEMU path; it does not make the supplied i.MX recipe portable to QEMU.

```bash
mkdir -p ../meta-phone/recipes-core/packagegroups
mkdir -p ../meta-phone/recipes-core/images
```

FILE: meta-phone/recipes-core/packagegroups/packagegroup-phone-sdk.bb

```bitbake
SUMMARY = "Runtime packages for the SDK integration exercise"
LICENSE = "MIT"
inherit packagegroup
RDEPENDS:${PN} = "linphone-sdk linphone-probe"
```

FILE: meta-phone/recipes-core/images/phone-sdk-image.bb

```bitbake
require recipes-core/images/core-image-minimal.bb
SUMMARY = "Minimal image with the Linphone SDK integration probe"
IMAGE_INSTALL:append = " packagegroup-phone-sdk"
```

```bash
bitbake phone-sdk-image
runqemu qemuarm64 phone-sdk-image nographic slirp
```

The packagegroup gives one maintained place for related runtime packages. The image defines product contents. Neither file installs development headers by default. After switching images, use phone-sdk-image when inspecting its manifest, running QEMU or generating its external SDK.

20. AN OPTIONAL SYSTEMD CHECK SERVICE

Use this extension only in a build already configured for systemd. core-image-minimal may use another init system; adding a unit file does not switch it to systemd. Our probe exits after a short check, so its correct service type is oneshot. A continuously running phone application would have a different service lifecycle.

FILE: meta-phone/recipes-apps/linphone-probe/files/linphone-probe.service

```ini
[Unit]
Description=Linphone SDK integration check

[Service]
Type=oneshot
Environment=LD_LIBRARY_PATH=/opt/belledonne-communications/lib
ExecStart=/usr/bin/linphone-probe

[Install]
WantedBy=multi-user.target
```

FILE: meta-phone/recipes-apps/linphone-probe/linphone-probe_1.0.bbappend

```bitbake
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append = " file://linphone-probe.service"
inherit systemd
SYSTEMD_SERVICE:${PN} = "linphone-probe.service"
SYSTEMD_AUTO_ENABLE:${PN} = "disable"

do_install:append() {
    install -d "${D}${systemd_system_unitdir}"
    install -m 0644 "${WORKDIR}/linphone-probe.service"         "${D}${systemd_system_unitdir}/linphone-probe.service"
}
```

If devtool already created this append, merge the service settings into it and preserve its patch entries. The unit is packaged but not enabled automatically. After rebuilding and deploying the image, start it explicitly and inspect its result. Successful completion normally leaves a oneshot service inactive; that alone is not an error. For a real phone service, network availability, the writable configuration directory, device permissions and orderly Core shutdown need separate design.

```bash
# Run on a systemd-based target after image deployment.
systemctl start linphone-probe.service
systemctl status linphone-probe.service --no-pager
systemctl show linphone-probe.service -p Result -p ExecMainStatus
journalctl -u linphone-probe.service -b --no-pager
```

21. A STRONGER SMOKE TEST: CREATE AND START THE CORE

After the version-only probe works, replace main.cpp with this optional example. It exercises Core creation, startup, iteration, stop and release using the 5.3 API. It still does not register an account or establish an RTP media session. No SIP credentials are needed.

```cpp
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <linphone/core.h>
#include <linphone/api/c-factory.h>

int main()
{
    using CorePtr = std::unique_ptr<LinphoneCore, decltype(&linphone_core_unref)>;
    CorePtr core(linphone_factory_create_core_3(
        linphone_factory_get(), nullptr, nullptr, nullptr), &linphone_core_unref);

    if (!core) {
        std::cerr << "Core creation failed\n";
        return 1;
    }
    if (linphone_core_start(core.get()) != 0) {
        std::cerr << "Core startup failed\n";
        return 2;
    }

    for (int i = 0; i < 50; ++i) {
        linphone_core_iterate(core.get());
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    linphone_core_stop(core.get());
    std::cout << "Core startup and shutdown check completed\n";
    return 0;
}
```

Add the following two lines to CMakeLists.txt after add_executable. Keep the existing liblinphone linkage. Threads::Threads supplies the platform's thread flags instead of hard-coding a host compiler option.

```cmake
find_package(Threads REQUIRED)
target_link_libraries(linphone-probe PRIVATE Threads::Threads)
```

For a Qt application, the same owner thread should manage the Core and call iterate regularly, for example through a QTimer whose interval matches the SDK guidance. Marshal SDK callbacks into the correct UI thread. A timer is not proof of thread safety: application objects, callbacks and shutdown need clear ownership. Do not run a separate independent iterate loop from another thread against the same Core.

Warnings about unavailable sound or video devices in QEMU do not automatically mean the linker setup is wrong. Record the actual Core startup result and inspect the log. A real phone must also validate its installed codec plugins and audio devices; these checks cannot be inferred from this program returning zero.

22. AN EXTERNAL SDK FOR APPLICATION DEVELOPMENT

An image contains runtime files; an external SDK also needs development headers, linker symlinks and native build tools. First list the actual package names. For the supplied original recipe, linphone-sdk-dev is declared explicitly. Other recipe versions may split packages differently.

```bash
oe-pkgdata-util list-pkgs 'linphone-sdk*'
oe-pkgdata-util list-pkg-files linphone-sdk-dev
```

If that development package exists, add the following configuration before generating the standard SDK. This does not install headers into the phone image. With a custom /opt prefix, inspect the generated target sysroot: the presence of a package name alone is not sufficient.

```bitbake
TOOLCHAIN_TARGET_TASK:append = " linphone-sdk-dev"
TOOLCHAIN_HOST_TASK:append = " nativesdk-cmake nativesdk-ninja"
```

```bash
# In the Yocto build shell. Use phone-sdk-image if section 19 is active.
bitbake -c populate_sdk core-image-minimal
find tmp/deploy/sdk -maxdepth 1 -type f -name '*.sh' -print

# Select the installer just generated for this host, image and architecture.
read -r -p "Generated SDK installer path: " sdk_installer
test -f "$sdk_installer" &&     bash "$sdk_installer" -d "$HOME/phone-cross-sdk"
```

Open a fresh shell for the installed toolchain; do not mix it with the BitBake build environment. The command below expects exactly one environment-setup file and makes that assumption explicit. Keep the SDK and the deployed image from the same compatible release.

```bash
mapfile -t sdk_envs < <(find "$HOME/phone-cross-sdk" -maxdepth 1     -type f -name 'environment-setup-*' | sort)
if (( ${#sdk_envs[@]} != 1 )); then
    printf '%s\n' "Expected exactly one installed target environment" >&2
    return 1 2>/dev/null || exit 1
fi
source "${sdk_envs[0]}"

test -f "$SDKTARGETSYSROOT/opt/belledonne-communications/include/linphone/linphonecore.h"
find "$SDKTARGETSYSROOT/opt/belledonne-communications/lib"     -maxdepth 1 -name 'liblinphone.so*' -print

cmake -S "$HOME/yocto-linphone-lab/meta-phone/recipes-apps/linphone-probe/files" \
+    -B "$HOME/linphone-probe-cross-build" -G Ninja \
+    -DCMAKE_TOOLCHAIN_FILE="$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake" \
+    -DLINPHONE_SDK_ROOT="$SDKTARGETSYSROOT/opt/belledonne-communications"
cmake --build "$HOME/linphone-probe-cross-build" --verbose
```

Do not run the resulting ARM executable on the build host. A successful external build helps application iteration, but release packaging should still go through the recipe so dependencies, checksums and image contents remain controlled.

23. DIAGNOSE THE EXACT STAGE THAT FAILED

For a fetch failure, start with access to the repository, the selected revision, the branch and submodule access. For a configure failure, inspect the first missing dependency and the generated CMake command. A target library cannot replace a missing native tool. For a compile failure, find the first actual compiler error before reading the final task summary.

```bash
# Run from build/. Output paths are obtained from BitBake, not guessed.
bitbake -e linphone-sdk > linphone-sdk.environment.txt
sdk_logs=$(sed -n 's/^T="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
sdk_work=$(sed -n 's/^WORKDIR="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
find "$sdk_logs" -maxdepth 1 -name 'log.do_*' -print
find "$sdk_work/packages-split" -name 'liblinphone.so*' -print
find "$sdk_work/packages-split" -name 'belledonne.conf' -print

bitbake -e linphone-probe > linphone-probe.environment.txt
probe_sysroot=$(sed -n 's/^RECIPE_SYSROOT="\(.*\)"$/\1/p' linphone-probe.environment.txt)
find "$probe_sysroot/opt/belledonne-communications"     -name 'linphonecore.h' -o -name 'liblinphone.so*'
oe-pkgdata-util find-path /usr/bin/linphone-probe
oe-pkgdata-util find-path /etc/ld.so.conf.d/belledonne.conf
```

After linking, inspect the target ELF using the target readelf from a devshell or installed cross-SDK. Needed libraries, machine type and RPATH/RUNPATH are different checks. This example's executable should not contain build/tmp paths. A DT_NEEDED entry proves that a library is requested; it does not prove that the device loader can find it.

```bash
# In the installed cross-SDK shell after section 22.
probe_elf="$HOME/linphone-probe-cross-build/linphone-probe"
test -f "$probe_elf"
$READELF -h "$probe_elf"
$READELF -d "$probe_elf" | grep -E 'NEEDED|RPATH|RUNPATH'
```

On the phone, first check that the expected files exist and their symlinks resolve. For a glibc image, the installed ld.so.conf.d entry can be used when its loader cache is generated or refreshed. Merely writing that file does not prove the cache was updated. A service-specific LD_LIBRARY_PATH, as above, avoids relying on a global loader policy for this example. musl has different configuration rules.

For a missing codec plugin, check its package, location, SDK plugin-search policy and its own shared-library dependencies. A plugin .so being present is insufficient if one of its dependencies is absent. Avoid copying arbitrary .so files from a workstation or a different release: architecture, ABI and codec configuration must agree.

24. REPRODUCIBILITY AND CI

A release records more than a version label: layer commits, local patches, the SDK parent commit and submodule commits, MACHINE, DISTRO, compiler/toolchain configuration, enabled features, license checksums and image/package manifests. The original latest recipe especially needs an explicit source pin. Keep these records together with the release artifacts.

```bitbake
# Optional shared caches in the learning workspace.
DL_DIR = "${TOPDIR}/../shared-downloads"
SSTATE_DIR = "${TOPDIR}/../shared-sstate"
```

The download cache avoids fetching the same sources repeatedly. The shared-state cache reuses compatible task outputs based on their signatures. Neither is a release archive or a substitute for pinned inputs. For a custom superbuild, verify that its internal downloads and configuration changes participate in the declared source/build model; otherwise a nominally cached build can hide uncontrolled inputs.

A practical CI pipeline first parses metadata, then builds the SDK and application, checks packaging QA, builds the image, runs the version/Core tests in QEMU where supported, and runs hardware tests on the phone. Archive the exact manifests and the required task logs. Keep repository credentials outside recipes and do not publish full environment dumps.

25. RELEASE PACKAGES AND PHONE UPDATES

Yocto's .ipk output is a package-manager artifact. It is not automatically a safe phone update with rollback. If the product uses the .NET Autoprovisioning Manager to assemble per-phone partial updates, assemble them from approved release outputs after reading the phone's actual version. Do not rebuild the SDK separately for each phone.

A library update may require the application, SDK plugins and related configuration to change together. Compare release manifests and actual file hashes, not only timestamps. Keep the versioned shared library and its symlinks consistent. Mark additions, replacements and removals explicitly. Validate the expected source version and free space before stopping the phone service.

For file-based rollback, save the original affected files and metadata, persist a reverse-operation journal, then apply replacements safely. After restart, check the software version and meaningful phone health checks. If the update fails, restore replaced/deleted files, remove newly added files, restore metadata and verify the previous version. A power-loss recovery path must run before the ordinary phone application. This is an update-system responsibility, not something DEPENDS or BitBake implements automatically.

26. ACCEPTANCE CHECKLIST AND INTERVIEW ANSWER

- ACCEPT-01. The intended SDK recipe and append are selected; all required layers are present.
- ACCEPT-02. The SDK source revision and submodule revisions are recorded.
- ACCEPT-03. Final CMake task bodies use the target toolchain and the expected feature options.
- ACCEPT-04. Installed headers, runtime libraries and required plugins exist in D.
- ACCEPT-05. The application receives the SDK through its recipe sysroot rather than host paths.
- ACCEPT-06. Runtime and development packages contain the intended files; packaging skips have a justified, narrow scope.
- ACCEPT-07. The image manifest includes the runtime packages.
- ACCEPT-08. The target loader resolves liblinphone and its dependencies without build-host paths.
- ACCEPT-09. The version and Core checks finish successfully in the supported environment.
- ACCEPT-10. Hardware tests cover registration, both call directions, two-way audio, hold/resume, call termination, network loss and failover.
- ACCEPT-11. The video variant additionally checks camera access, enabled codecs and plugin loading.
- ACCEPT-12. An update and rollback test returns to the exact previous compatible software set.

INTERVIEW EXPLANATION OF THE INTEGRATION

The existing Yocto base provided the operating-system build, but the team had to add Linphone SDK integration. I would explain the work in three parts: building the SDK for the phone, making it available to the application, and installing a working software set on the device. The supplied recipe shows the practical build mechanisms: a source repository with submodules, Qt and codec dependencies, CMake cross-compilation, an intermediate staging area and a final installation under /opt/belledonne-communications.

The application depends on the SDK recipe at build time, so Yocto prepares its headers and libraries in the application sysroot. At runtime the image must contain the SDK libraries and required plugins, and the loader must know their location. I would first check a small program that prints the SDK version, then Core startup, and finally registration and calls on the actual phone. A successful compile is only the first part: audio, network transitions and plugins need device tests.

The audit findings in this guide describe the supplied snapshot. They do not prove when each line was written, which configuration produced a historical release, or who personally authored every recipe change. The technical explanation should keep team integration separate from personal ownership and should not claim that the proposed fixes were already deployed.

27. SOURCES AND LOCAL SNAPSHOT

Research date: 2026-11-15.

- Official Linphone Yocto integration guide: https://wiki.linphone.org/xwiki/wiki/public/view/Linphone/Building%20Linphone%20with%20Yocto/
- Official Kirkstone recipe layer: https://gitlab.linphone.org/BC/public/meta-bc/-/tree/feature/yocto-kirkstone
- Yocto host requirements: https://docs.yoctoproject.org/4.0.30/ref-manual/system-requirements.html
- Creating layers: https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html
- Writing recipes: https://docs.yoctoproject.org/4.0.30/dev-manual/new-recipe.html
- SYSROOT_DIRS and recipe variables: https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html#term-SYSROOT_DIRS
- Debugging tasks: https://docs.yoctoproject.org/4.0.30/dev-manual/debugging.html
- Running QEMU: https://docs.yoctoproject.org/4.0.30/dev-manual/qemu.html
- Liblinphone version API declaration: https://github.com/BelledonneCommunications/liblinphone/blob/master/include/linphone/core.h
- Kirkstone common MIT license used by the example: https://git.yoctoproject.org/poky/tree/meta/files/common-licenses/MIT?h=kirkstone

Additional official references:

- Recipe tasks: https://docs.yoctoproject.org/4.0.30/ref-manual/tasks.html

- QA checks: https://docs.yoctoproject.org/4.0.30/ref-manual/qa-checks.html

- Kirkstone-compatible override syntax: https://docs.yoctoproject.org/4.0.30/migration-guides/migration-3.4.html#override-syntax-changes

- Devtool workflows: https://docs.yoctoproject.org/4.0.30/sdk-manual/extensible.html

- External toolchain environment: https://docs.yoctoproject.org/4.0.30/sdk-manual/working-projects.html

- CMake toolchains: https://cmake.org/cmake/help/v3.22/manual/cmake-toolchains.7.html

- Qt CMake class: https://github.com/meta-qt5/meta-qt5/blob/kirkstone/classes/cmake_qt5.bbclass

- Core API, 5.3.0: https://github.com/BelledonneCommunications/liblinphone/blob/5.3.0/include/linphone/core.h

- Factory API, 5.3.0: https://github.com/BelledonneCommunications/liblinphone/blob/5.3.0/include/linphone/api/c-factory.h

- Service types; only established oneshot directives are used here: https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

Local snapshot fingerprints, SHA-256; checked 2026-11-15:

```text
linphone-sdk_latest.bb
f49269e21074e27240bffca2450c98830a5d0d384f517472cc76c9635018161e
cmakebuilder.bbclass
33c0cf2cce41c33105639c2245874dbe47b45e60f0dc97e2172d37a1c65190bb
conf/layer.conf
2a5e1f0d2de89bf4b9e5082afac697de406a36d317ce940fac1f1fde18a57ba7
```
