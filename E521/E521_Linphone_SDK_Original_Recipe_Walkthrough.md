LINPHONE SDK: LINE-BY-LINE WALKTHROUGH OF THE ORIGINAL YOCTO RECIPE

01. HOW TO USE THIS WALKTHROUGH

This is a reading guide to the candidate-supplied source snapshot, not a replacement recipe or proof of a historical release configuration. The companion implementation guide explains the complete integration workflow. Here every physical line is indexed: R001–R273 for the recipe, C001–C171 for its local CMake class, and L001–L011 for layer.conf. Both languages use the same identifiers and source excerpts.

The local layer root is C:\Users\User\Downloads\meta-bc\meta-bc. Files were read without modification. Source excerpts preserve physical line numbering; indentation tabs are shown as spaces and trailing whitespace is omitted. Only R071 substitutes private-host/private-repository.git for the private Git endpoint. That line is a privacy-redacted quote, not a runnable download configuration.

Read source blocks first, then their per-line explanations. Continuation lines and braces are parts of larger statements, not commands to paste independently. Shell deletion and movement shown in the class are existing source being explained; they were not executed during this review. No full Yocto or target build was run.

02. THE MAIN MENTAL MODEL

Build dependencies supply headers, libraries and host tools. The toolchain selects the phone architecture. CMake builds the SDK, do_install stages files inside D, FILES distributes those files into packages, and an image chooses runtime packages. Source selection, version labels and package-manager versions are separate mechanisms. RPROVIDES does not create source recipes; SYSROOT_DIRS does not configure the device loader; a successful compile does not prove working calls.

Source paths used throughout: WORKDIR is temporary recipe workspace; S is unpacked source; B is build output; D is temporary installation root; RECIPE_SYSROOT contains dependencies. BUILD_INSTALL_PATH is this recipe’s intermediate SDK tree; INSTALL_PATH_OUT is its final /opt location on the device. None of the build-host paths should become runtime search paths.

03. ORIGINAL RECIPE

File: recipes-bc/linphone-sdk/linphone-sdk/linphone-sdk_latest.bb

R001–R012. IDENTITY AND DEFAULTS

```bitbake
VERSION_DEPENDENT_DEPENDS=""
VERSION_DEPENDENT_INHERIT="python3native"

# The default commit sha used if LINPHONE_SDK_REV is not set and LATEST_REVISIONS disabled
DEFAULT_COMMIT="${AUTOREV}"

DESCRIPTION = "WIP LINPHONE-SDK Audio/video SIP-based IP phone (console edition)"
HOMEPAGE = "http://www.linphone.org/technical-corner/linphone/overview"
SECTION = "network"
SECTION:linphonec =  "console/network"

INC_PR = "r0"
```

- R001: Defines an empty extension point for version-specific build dependencies. R019 inserts it into DEPENDS; here it contributes no package.

- R002: Selects python3native as a version-dependent inherited class. This prepares native Python support for build-time scripts, rather than installing Python on the phone.

- R003: Blank separator. It changes no variable and adds no task.

- R004: Documents a fallback commit, but the next line contradicts the implied fixed revision: it uses AUTOREV. Read executable metadata before trusting this comment.

- R005: Sets the fallback to the latest revision resolved by BitBake. Without an explicit pin, source can change between builds even when the recipe text does not.

- R006: Blank separator. It changes no variable and adds no task.

- R007: Sets human-readable package metadata. WIP and console edition are literal labels in this snapshot; they do not determine whether the built product has a GUI.

- R008: Provides a project information page, not the source download location; SRC_URI controls fetching. On the review date this old address returned HTTP 404. It is retained in the source quote as part of the original snapshot rather than treated as current documentation.

- R009: Classifies the package under network. SECTION is metadata, not a build dependency or a firewall configuration.

- R010: Defines an override of SECTION for linphonec. It has an effect only in the corresponding override/package context; it does not create a linphonec package.

- R011: Blank separator. It changes no variable and adds no task.

- R012: Defines a custom revision prefix consumed by R271. The name INC_PR is a convention of this recipe, not a task.

R013–R030. BUILD DEPENDENCIES AND RUNTIME ALIASES

```bitbake

DEPENDS = "\
    qtbase qttools-native qttools qtquickcontrols2 qtsvg qtmultimedia qtwayland qtwayland-native \
    doxygen-native git-native perl-native python3-native python3-pystache-native python3-six-native \
    alsa-lib virtual/gettext gsm jsoncpp libjpeg-turbo libsrtp libxml2 mariadb mbedtls pulseaudio speex \
    speexdsp xerces-c spandsp \
    ${VERSION_DEPENDENT_DEPENDS} \
    libopus libvpx \
    tiff \
    opencore-amr vo-amrwbenc \
    "

PROVIDES = "linphone-sdk"

RPROVIDES:${PN} = "\
    bcunit bcg729 bctoolbox belle-sip belr belcard bzrtp liblinphone linphonec lime ortp \
    mediastreamer2 mswebrtc \
    "
```

- R013: Blank separator. It changes no variable and adds no task.

- R014: Starts a multiline DEPENDS assignment. These names identify recipe providers needed before this recipe builds, not an image installation list.

- R015: Adds Qt base, tools, Quick Controls 2, SVG, multimedia and Wayland. Names ending in -native provide host tools; the other dependencies provide target-side development content. The matching Qt layer must be present.

- R016: Adds host documentation, Git, Perl and Python tools, including Python template/support modules. Native tools execute during the build and normally do not belong in the device image.

- R017: Adds audio, gettext, JSON, JPEG, SRTP, XML, MariaDB and TLS providers. A broad dependency list increases the build graph; it does not prove that every library is used in every phone feature.

- R018: Adds speech-processing, XML and telephony DSP providers. Their target headers/libraries become available through dependency sysroots.

- R019: Expands the version-specific dependency list from R001. It is empty in this snapshot but could be supplied by other metadata.

- R020: Adds Opus and VPX providers unconditionally. Disabling the corresponding PACKAGECONFIG option does not automatically remove these direct DEPENDS entries.

- R021: Adds TIFF unconditionally. The feature switch in R099 controls CMake arguments, while this dependency remains.

- R022: Adds AMR-related library providers unconditionally. Their feature and licensing choices need separate review.

- R023: Closes the multiline DEPENDS string. No command executes here.

- R024: Blank separator. It changes no variable and adds no task.

- R025: Declares a build-time provider alias identical to the recipe's normal name. It is largely redundant; it does not replace RPROVIDES.

- R026: Blank separator. It changes no variable and adds no task.

- R027: Starts runtime aliases for the main package PN. These aliases let runtime dependencies refer to the package under other names.

- R028: Lists component names provided by the runtime package. This does not create separate recipes or prove that all matching binaries are present.

- R029: Adds mediastreamer2 and mswebrtc runtime aliases. The mswebrtc name is not evidence that the complete browser WebRTC or mediasoup application stack is installed.

- R030: Closes the RPROVIDES list. Package contents still come from installation and FILES rules.

R031–R048. SOURCES, CLASSES AND LICENSING

```bitbake

S = "${WORKDIR}/git"

inherit cmakebuilder gettext pkgconfig chrpath perlnative ${VERSION_DEPENDENT_INHERIT} cmake_qt5

# License variables to use pre Linphone-SDK 5.2
# GPLv2 or later
# LICENSE = "GPL-2.0-or-later"
# LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=ff3103b5db8ba4e2c66c511b7a73e407"

# Licences variables to use for Linphone-SDK>=5.2
# AGPLv3 or later
LICENSE = "AGPL-3.0-or-later"
# LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=eb1e647870add0502f8f010b19de32af"

inherit gitpkgv

RDEPENDS:${PN} += "mbedtls speexdsp speex libopus libjpeg-turbo libturbojpeg jsoncpp libsrtp libsqlite3 libvpx libxerces-c spandsp"
```

- R031: Blank separator. It changes no variable and adds no task.

- R032: Sets S to the unpacked Git source directory. Check this path after do_unpack before locating patches or inspecting LICENSE.txt.

- R033: Blank separator. It changes no variable and adds no task.

- R034: Inherits build and helper classes. cmakebuilder is local, while cmake_qt5 also inherits standard cmake. Inspect expanded task definitions to establish the actual configure, compile and install implementations.

- R035: Blank separator. It changes no variable and adds no task.

- R036: Marks the following commented license settings as historical choices for older SDK versions. It does not select that older version.

- R037: Describes the historical GPL licensing choice; it is only a comment.

- R038: Shows a disabled LICENSE assignment. It has no effect while prefixed by a comment marker.

- R039: Shows a disabled checksum for an older license file. Never replace the active checksum with it without checking the actual fetched file.

- R040: Blank separator. It changes no variable and adds no task.

- R041: Introduces the newer licensing block; the active declaration follows in R043.

- R042: Summarizes the intended AGPLv3-or-later identifier. The actual selected source and its license files remain authoritative.

- R043: Declares AGPL-3.0-or-later for recipe license processing. It does not grant an alternative commercial license or settle every codec's separate conditions.

- R044: Keeps another disabled license checksum. The active checksum is R081, not this comment.

- R045: Blank separator. It changes no variable and adds no task.

- R046: Adds Git-derived package-version support through gitpkgv. The class must be supplied by an enabled layer; PKGV later consumes its output.

- R047: Blank separator. It changes no variable and adds no task.

- R048: Adds explicit runtime package dependencies. These are package names, which can differ from DEPENDS provider names; for example sqlite3 can produce libsqlite3. Verify providers through pkgdata.

R049–R071. REVISION SELECTION AND FETCHING

```bitbake

python () {
# 3 possible revisions:
# - if env[LATEST_REVISIONS] is set, use yocto autorev mecanism
# - if env[LINPHONE_SDK_REV] is defined, use the value as the revision (useful for continous integration)
# - Otherwise, use fixed stable revision

    if os.getenv('LATEST_REVISIONS', '') == "1":
        d.setVar('SRCREV', "${AUTOREV}")
    else:
        d.setVar('SRCREV', os.getenv('LINPHONE_SDK_REV', "${DEFAULT_COMMIT}"))

    d.setVar('LINPHONE_SDK_BRANCH', os.getenv('LINPHONE_SDK_BRANCH', 'master'))
}

# For visualisation
python () {
    print("")
    print("linphone-sdk")
    print(d.getVar('SRCREV', True))
}

SRC_URI = "gitsm://private-host/private-repository.git;protocol=http;branch=main"
```

- R049: Blank separator. It changes no variable and adds no task.

- R050: Starts anonymous Python evaluated while metadata is finalized, rather than a do_compile shell task. It changes the recipe datastore.

- R051: Introduces three intended source-selection modes. Their actual behavior is determined by R056–R061.

- R052: Documents the AUTOREV mode. The implementation requires the exact string 1, not just any nonempty value.

- R053: Documents an explicit commit passed through the environment. BitBake must allow that variable into its environment for this hook to read it.

- R054: Claims the fallback is fixed, but R005 makes it AUTOREV. This comment is inconsistent with this snapshot.

- R055: Blank separator. It changes no variable and adds no task.

- R056: Reads LATEST_REVISIONS from the process environment and tests for 1. This is os.getenv, not a direct query of a local.conf datastore variable.

- R057: Sets SRCREV to AUTOREV when that switch is enabled. This intentionally permits source movement.

- R058: Begins the fallback branch when the latest-revision switch is not enabled.

- R059: Uses LINPHONE_SDK_REV if available, otherwise DEFAULT_COMMIT. Because the latter is AUTOREV, merely unsetting LATEST_REVISIONS is insufficient for reproducibility.

- R060: Blank separator. It changes no variable and adds no task.

- R061: Stores a branch name from the environment with master as fallback. R071 does not reference this variable, so this assignment alone does not change the fetched main branch.

- R062: Ends the anonymous Python block. It defines metadata rather than starting a runtime service.

- R063: Blank separator. It changes no variable and adds no task.

- R064: Introduces parse-time diagnostic output. It is not a device-side logging configuration.

- R065: Starts another anonymous Python block. It may execute for parsing contexts and emit repeated console output.

- R066: Prints an empty line to separate diagnostic output. It changes no variable.

- R067: Prints the recipe label. Structured bb.note output would be easier to manage than unconditional print.

- R068: Prints expanded SRCREV. Resolving AUTOREV can require repository access; the output is diagnostic, not a durable release manifest.

- R069: Ends the diagnostic Python block.

- R070: Blank separator. It changes no variable and adds no task.

- R071: Fetches a private Git source with submodules, over HTTP, on literal branch main. The host/path shown here are privacy substitutions. gitsm follows recorded submodule references; it does not mean each submodule tracks its latest branch.

R072–R081. LICENSE CHECKSUM SELECTION

```bitbake

python () {
    if os.getenv("LINPHONE_SDK_LIC_FILES_CHKSUM", '') != '':
      bb.note("LINPHONE_SDK_LIC_FILES_CHKSUM=" + os.getenv("LINPHONE_SDK_LIC_FILES_CHKSUM", ''))
      d.setVar("LIC_FILES_CHKSUM_ENV", os.getenv("LINPHONE_SDK_LIC_FILES_CHKSUM"))
    else:
      d.setVar("LIC_FILES_CHKSUM_ENV", "eb1e647870add0502f8f010b19de32af")
}
#Bitbakes throws parse errors when we try to set license dynamically, so we only set LIC_FILES_CHKSUM (check .bb files to see which values to set)
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=5b4473596678d62d9d83096273422c8c"
```

- R072: Blank separator. It changes no variable and adds no task.

- R073: Starts Python intended to select a license-file checksum from the environment. Follow the destination variable through to the active assignment.

- R074: Tests whether the checksum environment variable is nonempty. It does not validate MD5 format or license content.

- R075: Logs that supplied checksum through bb.note. This is build-time information.

- R076: Stores it as LIC_FILES_CHKSUM_ENV, not LIC_FILES_CHKSUM. The distinction explains why the active license checksum does not change.

- R077: Begins the default-checksum branch.

- R078: Stores a default value in the same unused intermediate variable. R081 does not expand it.

- R079: Ends the checksum-selection Python block.

- R080: Explains the author's historical workaround. Treat the stated parser limitation as a comment, not a general rule that BitBake cannot expand license metadata.

- R081: Defines the active LICENSE.txt MD5 check. It detects changes to that file; without the fetched source we cannot verify that the literal checksum is correct for the selected revision.

R082–R099. FEATURE CONFIGURATION

```bitbake

PACKAGECONFIG ??= "bzrtp opus sqlite zlib video g2d imxvpuh264 amr tiff zxing"
PACKAGECONFIG[sqlite] = "-DENABLE_SQLITE_STORAGE=YES -DENABLE_SQLITE=YES, -DENABLE_SQLITE_STORAGE=NO -DENABLE_SQLITE=NO, sqlite3"
PACKAGECONFIG[zlib] = "-DENABLE_ZLIB=YES, -DENABLE_ZLIB=NO, zlib"
PACKAGECONFIG[bzrtp] = " -DENABLE_BZRTP=YES, -DENABLE_BZRTP=NO"
PACKAGECONFIG[mdns] = "-DENABLE_MDNS=YES, -DENABLE_MDNS=NO, avahi"
PACKAGECONFIG[imxvpuh264] = "-DENABLE_IMXVPUH264=YES, -DENABLE_IMXVPUH264=NO, imx-vpuwrap"
PACKAGECONFIG[h264] = "-DENABLE_NON_FREE_CODECS=YES -DENABLE_OPENH264=YES, -DENABLE_OPENH264=NO, openh264 nasm-native"
PACKAGECONFIG[g2d] = "-DENABLE_G2D=YES -DENABLE_VPU=YES, -DENABLE_G2D=NO, imx-vpuwrap"
PACKAGECONFIG[opus] = "-DENABLE_OPUS=YES, -DENABLE_OPUS=NO, libopus"
PACKAGECONFIG[video] = "-DENABLE_X11=YES -DENABLE_XV=YES -DENABLE_GLX=NO -DENABLE_GL=NO, -DENABLE_VIDEO=NO, libv4l libxv virtual/libgl glew libglu libyuv"
PACKAGECONFIG[vpx] = "-DENABLE_VPX=YES, -DENABLE_VPX=NO, libvpx yasm-native"

# Extra codecs/libs to match belledonne_original deployment
PACKAGECONFIG[amr] = "-DENABLE_AMR=YES -DENABLE_AMRWB=YES, -DENABLE_AMR=NO -DENABLE_AMRWB=NO, opencore-amr vo-amrwbenc"
# SILK may require non-redistributable SDK; enable if available in your layer
PACKAGECONFIG[silk] = "-DENABLE_SILK=YES, -DENABLE_SILK=NO, silk"
PACKAGECONFIG[tiff] = "-DENABLE_TIFF=YES, -DENABLE_TIFF=NO, tiff"
```

- R082: Blank separator. It changes no variable and adds no task.

- R083: Defines a weak default feature list. A stronger assignment can replace it. zxing is selected here without a matching definition in the supplied file.

- R084: Maps SQLite selection to enable/disable CMake arguments and the sqlite3 build dependency. The fields are separated by commas.

- R085: Maps the zlib feature to its CMake switch and zlib provider. This switch is separate from any transitive use of compression elsewhere.

- R086: Controls BZRTP through CMake. No extra dependency field is specified here; the SDK may build that component internally.

- R087: Defines optional mDNS support through Avahi. mdns is not in the default feature list.

- R088: Enables the i.MX VPU H.264 path and adds imx-vpuwrap. This ties the configuration to a compatible vendor BSP.

- R089: Defines a separate OpenH264 option with OpenH264 and NASM dependencies. It is not the same option as imxvpuh264, and it is not selected by the default list.

- R090: Enables G2D and VPU together, but its disabled side only explicitly disables G2D. Inspect the final ENABLE_VPU value rather than assuming perfect symmetry.

- R091: Controls Opus. The direct DEPENDS list also contains libopus, so disabling this feature alone still leaves the provider in the build graph.

- R092: Its enabled side requests X11/XVideo and disables GLX/GL; its disabled side sets ENABLE_VIDEO=NO. It does not explicitly set ENABLE_VIDEO=YES on the enabled side. Check the SDK defaults and final CMake cache, especially with a Wayland product.

- R093: Defines VPX enable/disable arguments and dependencies. vpx is absent from the default feature list even though libvpx is an unconditional dependency.

- R094: Blank separator. It changes no variable and adds no task.

- R095: Explains that the following options were added to match an earlier deployment. It is not proof that every copied plugin is currently produced.

- R096: Enables AMR and AMR-WB together and names their provider recipes. Check the actual resulting plugins and distribution obligations.

- R097: Warns that SILK may need a separately available SDK. This comment does not supply that SDK.

- R098: Defines an optional SILK feature with a silk dependency. It is inactive unless selected.

- R099: Defines the TIFF feature. Its direct provider also remains in DEPENDS independently of this selection.

R100–R111. SDK CMAKE OPTIONS

```bitbake

EXTRA_OECMAKE ??= " "
EXTRA_OECMAKE += " -DLINPHONESDK_PLATFORM=Yocto"
EXTRA_OECMAKE += " -DLINPHONESDK_VERSION=5.3.0-alpha-175-g28018be13"
EXTRA_OECMAKE += " -DENABLE_G729=ON -DENABLE_G729B_CNG=YES -DENABLE_G726=ON -DENABLE_ILBC=ON -DENABLE_RTP_MAP_ALWAYS_IN_SDP=ON"
EXTRA_OECMAKE += " -DENABLE_CONSOLE_UI=NO -DENABLE_GTK_UI=NO -DENABLE_CXX_WRAPPER=YES -DENABLE_VCARD=YES -DENABLE_XML2=YES -DENABLE_SOCI_MYSQL=YES -DENABLE_LDAP=NO"

EXTRA_OECMAKE += " -DENABLE_UNIT_TESTS=YES -DENABLE_TESTS=YES"

#Force cmake cross-compiling
EXTRA_OECMAKE += " -DCMAKE_CROSSCOMPILING=YES"
EXTRA_OECMAKE += " -DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/toolchain.cmake"
```

- R100: Blank separator. It changes no variable and adds no task.

- R101: Sets a weak default for extra CMake arguments to one space. This does not clear arguments supplied by stronger assignments or override-style additions.

- R102: Passes the SDK's platform selector as Yocto. This is a project-defined CMake option, not a generic switch that makes any source tree Yocto-compatible.

- R103: Passes a hard-coded SDK version label. The embedded abbreviated hash is text here; it does not pin SRCREV or prove correspondence to the fetched source.

- R104: Enables several audio codec/SDP options. Their actual implementation must exist in the selected source; accepted CMake cache values alone do not prove the code uses them.

- R105: Disables console/GTK UI, enables C++ wrapper, vCard, XML and SOCI/MySQL, and disables LDAP. This further shows why the earlier console-edition description is not authoritative.

- R106: Blank separator. It changes no variable and adds no task.

- R107: Requests unit and other tests during SDK configuration. This does not automatically execute tests on the target or guarantee that test binaries are packaged.

- R108: Blank separator. It changes no variable and adds no task.

- R109: States the author's cross-compilation intent. The toolchain file and CMAKE_SYSTEM_NAME are more important than this comment.

- R110: Attempts to set CMAKE_CROSSCOMPILING directly. CMake normally derives it from the target-system setup; this line is not a substitute for a correct toolchain file.

- R111: Points CMake to the generated toolchain file under WORKDIR. Verify which inherited task creates that file.

R112–R130. INTERMEDIATE AND FINAL INSTALL PATHS

```bitbake

BUILD_INSTALL_PREFIX = "${WORKDIR}/build/linphone-sdk/desktop"

INSTALL_PATH_OUT = "/opt/belledonne-communications"
INSTALL_PATH = ""

BUILD_INSTALL_PATH = "${BUILD_INSTALL_PREFIX}${INSTALL_PATH}"

#Used by cmake.bbclass to add the temporary target directory as root for find_package, required to find correct libraries directories
OECMAKE_EXTRA_ROOT_PATH = "${BUILD_INSTALL_PATH}"

EXTRA_OECMAKE += " -DCMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES=${STAGING_INCDIR}"
EXTRA_OECMAKE += " -DCMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES=${STAGING_INCDIR}"

#The actual target installation prefix when cross-compiling
EXTRA_OECMAKE += " -DCMAKE_STAGING_PREFIX=${BUILD_INSTALL_PATH}"
EXTRA_OECMAKE += " -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH}"

EXTRA_OECMAKE += " -DCMAKE_SKIP_RPATH=YES"
```

- R112: Blank separator. It changes no variable and adds no task.

- R113: Names the intermediate SDK installation tree inside the recipe work directory. It is a build-host path, not the final phone location.

- R114: Blank separator. It changes no variable and adds no task.

- R115: Names the final device prefix under /opt. Later installation code moves files there inside D.

- R116: Defines an empty suffix. An empty install prefix needs inspection against the SDK's generated install scripts; do not generalize it as a recommended CMake setup.

- R117: Blank separator. It changes no variable and adds no task.

- R118: Concatenates the intermediate prefix and empty suffix. In this snapshot it equals BUILD_INSTALL_PREFIX.

- R119: Blank separator. It changes no variable and adds no task.

- R120: Describes adding the intermediate SDK output to CMake searches. Whether this local class or another inherited class supplies the final toolchain must still be checked.

- R121: Adds the intermediate SDK tree to custom root-path configuration. It helps later SDK components find earlier built components.

- R122: Blank separator. It changes no variable and adds no task.

- R123: Overrides CMake's recorded implicit C include directories with STAGING_INCDIR. This is a workaround touching compiler-detection metadata, not an ordinary target_include_directories call.

- R124: Does the same for C++ includes. Check compiler detection and generated compile commands when changing the toolchain or SDK.

- R125: Blank separator. It changes no variable and adds no task.

- R126: Introduces installation-prefix configuration. Distinguish the host staging location from the device prefix.

- R127: Sets the host-side CMake staging prefix. Inspect do_install and generated install scripts to see how DESTDIR combines with it.

- R128: Passes the empty INSTALL_PATH as CMAKE_INSTALL_PREFIX. This is one reason the later relocation code requires careful checking.

- R129: Blank separator. It changes no variable and adds no task.

- R130: Disables CMake RPATH generation. The runtime loader must then find libraries through its normal policy or explicitly configured paths.

R131–R149. LINKING, LOGS AND BUILD TYPE

```bitbake

EXTRA_OECMAKE += " -DCMAKE_EXE_LINKER_FLAGS='-Wl,-rpath-link=${BUILD_INSTALL_PATH}/lib'"
EXTRA_OECMAKE += " -DCMAKE_SHARED_LINKER_FLAGS='-Wl,-rpath-link=${BUILD_INSTALL_PATH}/lib'"
EXTRA_OECMAKE += " -DCMAKE_MODULE_LINKER_FLAGS='-Wl,-rpath-link=${BUILD_INSTALL_PATH}/lib'"

EXTRA_OECMAKE += " \
    -DENABLE_DEBUG_LOGS=NO \
"

#ADD workaround for FIND packages
EXTRA_OECMAKE += " -Dbctoolbox_DIR=${BUILD_INSTALL_PATH}/share/bctoolbox/cmake"

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE:STRING=Release"
#Debug Release

#Apply default linker flags provided by Yocto.
#This avoids 'No GNU_HASH in the elf binary' error as documented
#in https://www.yoctoproject.org/docs/2.0.1/ref-manual/ref-manual.html#qa-issue-ldflags .
TARGET_CC_ARCH += "${LDFLAGS}"
```

- R131: Blank separator. It changes no variable and adds no task.

- R132: Adds link-time dependency lookup for executables under the intermediate SDK lib directory. rpath-link does not configure library lookup on the phone.

- R133: Applies that link-time lookup to shared-library linking. It does not install any dependency by itself.

- R134: Applies that lookup to CMake MODULE libraries, such as dynamically loaded modules. Runtime plugin loading remains a separate check.

- R135: Blank separator. It changes no variable and adds no task.

- R136: Starts a multiline addition to EXTRA_OECMAKE. The continuation is formatting, not a separate task.

- R137: Disables SDK debug logging through a project option. It does not necessarily remove all warnings, errors or application logs.

- R138: Closes that CMake-argument addition.

- R139: Blank separator. It changes no variable and adds no task.

- R140: Introduces a package-discovery workaround. Verify that the specified config directory really exists.

- R141: Points bctoolbox_DIR to a specific CMake package config location in the intermediate SDK. This favors that copy over other installations.

- R142: Blank separator. It changes no variable and adds no task.

- R143: Requests Release configuration. The += operator already inserts a separator, so the missing initial space inside the quoted text is not itself a concatenation bug.

- R144: Lists two possible build-type labels as a comment. It does not select Debug.

- R145: Blank separator. It changes no variable and adds no task.

- R146: Explains why the author wants Yocto linker flags retained. Check actual link commands to confirm that they reach each nested SDK component.

- R147: Mentions the GNU hash QA failure that motivated the workaround. It is not evidence that the current build has that failure.

- R148: Links an older QA reference. For Kirkstone behavior, use the matching current-for-this-build documentation and final task output.

- R149: Appends linker flags to TARGET_CC_ARCH. This mixes categories as a workaround and can duplicate flags when the class also includes LDFLAGS. Inspect final compiler/linker invocations before retaining it.

R150–R174. PACKAGING AND RUNTIME DEPENDENCIES

```bitbake

PACKAGES = "${PN} ${PN}-dev ${PN}-dbg"

FILES:${PN} += "${INSTALL_PATH_OUT}/bin/*"
FILES:${PN} += "${INSTALL_PATH_OUT}/lib/*"
FILES:${PN} += "${INSTALL_PATH_OUT}/share/*"
FILES:${PN} += "${INSTALL_PATH_OUT}/share/doc/${BPN}/CHANGELOG.md"
FILES:${PN} += "${INSTALL_PATH_OUT}/plugins/*"
FILES:${PN} += "${INSTALL_PATH_OUT}/cmake/*"
FILES:${PN} += "${INSTALL_PATH_OUT}/mkspecs/*"
FILES:${PN}-dev = "${INSTALL_PATH_OUT}/include/*"

RDEPENDS:${PN}:append:class-target = " \
    qtwayland-plugins \
    xwayland \
    qtgraphicaleffects \
    qtgraphicaleffects-qmlplugins \
    qtquickcontrols-qmlplugins \
    qtquickcontrols2-qmlplugins \
"

CFLAGS:append = " -Wno-error=unused-parameter -Wno-error=unused-variable"
CXXFLAGS:append = " -Wno-error=unused-parameter -Wno-error=unused-variable"

SYSROOT_DIRS += "/opt"
```

- R150: Blank separator. It changes no variable and adds no task.

- R151: Replaces the package list with runtime, development and debug packages, in that order. Broad runtime FILES rules can capture files before later packages; default package entries are also discarded.

- R152: Blank separator. It changes no variable and adds no task.

- R153: Includes executable files under the final /opt bin directory in the runtime package. It does not move files into that directory.

- R154: Includes the broad library tree in runtime. Inspect its handling of linker symlinks, archives, plugin subdirectories and debug content instead of assuming a clean development split.

- R155: Includes the broad share tree in runtime. Documentation and development metadata can be captured here.

- R156: Explicitly names a changelog path already within the broad share tree. It documents intent but may be redundant.

- R157: Includes a top-level plugins directory. The mediastreamer plugin directory used later is under lib and is a different path.

- R158: Includes a top-level cmake directory in runtime. Determine whether these files are useful on the device or belong in -dev.

- R159: Includes Qt mkspecs if installed there. They are commonly development metadata, so inspect the intended consumer.

- R160: Replaces the development FILES list with /opt headers only. Unlike +=, this can remove standard development patterns for symlinks and CMake/pkg-config metadata.

- R161: Blank separator. It changes no variable and adds no task.

- R162: Starts a target-class-only runtime dependency addition. The leading space prevents names joining when :append is applied.

- R163: Adds Qt Wayland plugins to the target runtime dependency list. Verify their package names in the selected Qt layer.

- R164: Requires Xwayland at runtime. This is an explicit product footprint/graphics choice, not something implied solely by using Qt.

- R165: Adds Qt Graphical Effects. It is a runtime package requirement, not a direct C++ compile flag.

- R166: Adds its QML plugins package. QML imports need the matching deployed plugin files.

- R167: Adds the first-generation Quick Controls QML plugins. Keeping both generations should match actual application imports.

- R168: Adds Quick Controls 2 QML plugins. Check image contents and QML module discovery on the actual phone.

- R169: Closes the target-only runtime dependency addition.

- R170: Blank separator. It changes no variable and adds no task.

- R171: Prevents unused-parameter and unused-variable warnings from becoming C compilation errors. It does not disable all warnings or all -Werror behavior.

- R172: Applies the same warning exceptions to C++. Keep exceptions narrow rather than masking unrelated diagnostics.

- R173: Blank separator. It changes no variable and adds no task.

- R174: Adds /opt to sysroot publication. Dependent recipes can then receive installed SDK content from that tree; it does not add /opt to the runtime loader search path.

R175–R196. CONFIGURE/INSTALL HOOKS AND DIAGNOSTICS

```bitbake

# Temporary work around for Qt5MultimediaConfig.cmake referencing non-existent videoimx6vivantevideonode directory
do_configure:prepend() {
    ln -sfn video/videonode "${RECIPE_SYSROOT}${OE_QMAKE_PATH_PLUGINS}/videoimx6vivantevideonode"
}


do_install:prepend () {
    install -m 0755 -d ${WORKDIR}/build/qtkeychain/lib "${D}${INSTALL_PATH_OUT}"
}

do_install:append () {
    echo "+++ D  = ${D}"
    echo "+++ prefix = ${prefix}"
    echo "+++ RECIPE_SYSROOT = ${RECIPE_SYSROOT}"
    echo "+++ WORKDIR = ${WORKDIR}"
    echo "+++ BUILD_INSTALL_PATH = ${BUILD_INSTALL_PATH}"
    echo "+++ INSTALL_PATH_OUT = ${INSTALL_PATH_OUT}"
    echo "+++ INSTALL_PATH_OUT/lib = ${D}${INSTALL_PATH_OUT}/lib"

    target_root_dir="${D}${INSTALL_PATH_OUT}"
    source_install_dir="${D}${BUILD_INSTALL_PATH}"
```

- R175: Blank separator. It changes no variable and adds no task.

- R176: Explains a Qt multimedia configuration workaround for a missing plugin directory reference. It identifies a compatibility issue, not a general Qt requirement.

- R177: Starts a shell hook that runs before the selected base do_configure implementation. It does not replace that base implementation.

- R178: Creates or updates a relative symlink in the recipe sysroot. The target video/videonode is relative to the plugin directory; it must exist, and the link is not the real video plugin implementation.

- R179: Ends the configure prepend hook.

- R180: Blank separator. It changes no variable and adds no task.

- R181: Blank separator. It changes no variable and adds no task.

- R182: Starts a hook before the inherited do_install. Establish that inherited implementation through the expanded metadata.

- R183: Creates both an intermediate QtKeychain lib directory and the final SDK destination under D with mode 0755. These are directories, not copied libraries. Unquoted paths assume no spaces.

- R184: Ends the install prepend hook.

- R185: Blank separator. It changes no variable and adds no task.

- R186: Starts a shell hook after the inherited installation task. The remaining relocation/copy commands execute here on the build host.

- R187: Prints the temporary installation root D. This path should not appear as a library search path on the device.

- R188: Prints the standard prefix variable for diagnosis. The recipe also passes its own install prefix, so compare the two in generated commands.

- R189: Prints the recipe's dependency sysroot. This is an input for building, not the final root filesystem.

- R190: Prints WORKDIR, the recipe's temporary working directory. It is not a release identifier.

- R191: Prints the intermediate SDK installation prefix. Use it to inspect where nested builds placed their outputs.

- R192: Prints the final device-relative SDK prefix. It does not itself create that directory.

- R193: Prints the SDK library destination inside D. This combines host staging and intended device layout.

- R194: Blank separator. It changes no variable and adds no task.

- R195: Defines a shell variable for the final SDK tree under D. Lowercase shell variables are expanded by the shell, not BitBake's datastore.

- R196: Defines the expected staged source tree under D plus the absolute BUILD_INSTALL_PATH. The generated install script must actually produce this nesting.

R197–R216. RELOCATING THE STAGED SDK

```bitbake

    install -d "${target_root_dir}/lib"

    # The SDK installs first into an absolute staging prefix under ${D};
    # move that content into the final /opt destination and remove the empty staging tree.
    if [ -d "${source_install_dir}" ]; then
        # Move all top-level entries
        find "${source_install_dir}" -mindepth 1 -maxdepth 1 -exec mv -t "${target_root_dir}" {} + 2>/dev/null || true
        rmdir -p --ignore-fail-on-non-empty "${source_install_dir}" 2>/dev/null || true
    fi

    target_lib_dir="${target_root_dir}/lib"
    target_plugin_dir="${target_root_dir}/lib/mediastreamer/plugins"
    target_pc_dir="${target_root_dir}/lib/pkgconfig"
    target_doc_dir="${target_root_dir}/share/doc/${BPN}"

    sysroot_lib_dir="${RECIPE_SYSROOT}/usr/lib"
    sysroot_cmake_dir="${RECIPE_SYSROOT}/usr/lib/cmake"
    sysroot_plugin_dir="${RECIPE_SYSROOT}/usr/lib/mediastreamer/plugins"
    sysroot_pc_dir="${RECIPE_SYSROOT}/usr/lib/pkgconfig"
```

- R197: Blank separator. It changes no variable and adds no task.

- R198: Creates the final lib directory. Its existence alone does not prove liblinphone was installed.

- R199: Blank separator. It changes no variable and adds no task.

- R200: Describes an assumption about CMake staging under D. Verify it against actual installation rather than treating the comment as evidence.

- R201: Explains the intended relocation and cleanup. Cleanup should remain restricted to the recipe staging tree.

- R202: Only performs relocation if the expected staged directory exists. A missing directory silently skips this block.

- R203: Says all top-level entries will be moved; find below also includes hidden entries because it does not use a shell star glob.

- R204: Moves top-level entries with GNU mv -t, batches arguments, suppresses stderr and ignores failure. Existing destination directories or copy/move errors can therefore be hidden.

- R205: Removes empty source directories and parents, ignoring failures and nonempty paths. It is not a backup or an update rollback mechanism.

- R206: Ends the conditional relocation block.

- R207: Blank separator. It changes no variable and adds no task.

- R208: Names the final SDK lib directory for later installation operations.

- R209: Names the mediastreamer plugin directory inside lib. This differs from the top-level plugins FILES entry in R157.

- R210: Names the pkg-config destination directory inside the SDK prefix.

- R211: Names the changelog destination using BPN, the base recipe name.

- R212: Blank separator. It changes no variable and adds no task.

- R213: Defines a sysroot lib directory but is not referenced by later commands in this function. It has no copying effect on its own.

- R214: Names dependency CMake metadata under hard-coded /usr/lib/cmake. On a different libdir layout this can miss files.

- R215: Names dependency mediastreamer plugins under hard-coded /usr/lib. Validate the actual provider's layout.

- R216: Names dependency pkg-config files under hard-coded /usr/lib/pkgconfig. Not all providers place every .pc file there.

R217–R239. PLUGIN, PKG-CONFIG AND CHANGELOG COPIES

```bitbake

    # Mediastreamer plugins
    install -d "${target_plugin_dir}"
    # Include additional plugins seen in previous deployments if present
    for f in msamr.so msamrwbdec.so msvpx.so mszxing.so; do
        if [ -f "${sysroot_plugin_dir}/${f}" ]; then
         install -m 0755 "${sysroot_plugin_dir}/${f}" "${target_plugin_dir}/"
        fi
    done

    # Pkgconfig
    install -d "${target_pc_dir}"
    for f in jsoncpp.pc libjpeg.pc libturbojpeg.pc opus.pc speexdsp.pc speex.pc vpx.pc x-c.pc zxing.pc; do
        if [ -f "${sysroot_pc_dir}/${f}" ]; then
            install -m 0644 "${sysroot_pc_dir}/${f}" "${target_pc_dir}/"
        fi
    done

    # Ship the source changelog with the installed SDK when present.
    if [ -f "${S}/CHANGELOG.md" ]; then
        install -d "${target_doc_dir}"
        install -m 0644 "${S}/CHANGELOG.md" "${target_doc_dir}/"
    fi
```

- R217: Blank separator. It changes no variable and adds no task.

- R218: Introduces selected media plugin copying. This is a build/install action, not runtime discovery.

- R219: Creates the plugin destination before copying. An empty directory can still satisfy a superficial directory-only check.

- R220: Describes copying plugins when present. Their optional treatment may be wrong if a product feature requires them.

- R221: Iterates over four explicit plugin filenames. It will not discover differently named or newly introduced plugins automatically.

- R222: Copies only if a regular file exists; a missing required plugin produces no error here.

- R223: Installs the plugin with mode 0755. Copying it from another recipe's sysroot can duplicate package ownership; verify its dependencies and intended package owner.

- R224: Ends the per-plugin file-existence check.

- R225: Ends the media plugin loop.

- R226: Blank separator. It changes no variable and adds no task.

- R227: Introduces pkg-config metadata copying. These files usually serve development tools rather than the running phone application.

- R228: Creates the pkg-config destination directory.

- R229: Iterates over selected dependency .pc files. This copies metadata, not the libraries those files describe.

- R230: Skips missing .pc files silently. The resulting metadata set can vary with enabled dependencies.

- R231: Copies a .pc file with mode 0644. Inspect prefix/libdir fields: copying a file does not rewrite its embedded paths for /opt.

- R232: Ends the per-file existence check.

- R233: Ends the pkg-config copying loop.

- R234: Blank separator. It changes no variable and adds no task.

- R235: Introduces optional source changelog packaging. This is documentation, not a source-revision pin.

- R236: Checks for CHANGELOG.md in S. No error is raised if that source version does not contain it.

- R237: Creates the SDK documentation destination.

- R238: Copies the changelog as a readable non-executable file. It can help support, but it is not a complete release manifest.

- R239: Ends the optional changelog block.

R240–R262. CMAKE METADATA AND DYNAMIC LOADER

```bitbake

    # CMake config files (shallow copy)
    install -d "${target_lib_dir}/cmake/MbedTLS" "${target_lib_dir}/cmake/Opus"
    find "${sysroot_cmake_dir}" -maxdepth 2 -type f -name '*MbedTLS*.cmake' \
        -exec install -m 0644 {} "${target_lib_dir}/cmake/MbedTLS/" \; 2>/dev/null || true
    find "${sysroot_cmake_dir}" -maxdepth 2 -type f -name '*Opus*.cmake' \
        -exec install -m 0644 {} "${target_lib_dir}/cmake/Opus/" \; 2>/dev/null || true

    # Additional CMake config files for Linphone stack components
    # Copy from /usr/lib/cmake/<Pkg> and /usr/share/<Pkg>/cmake if present
    for pkg in BelleSIP belr ortp Linphone LinphoneCxx Mediastreamer2 bctoolbox bzrtp Bcg729 bcmatroska2 decaf lime EQt5Keychain; do
        for base in "${RECIPE_SYSROOT}/usr/lib/cmake" "${RECIPE_SYSROOT}/usr/share/${pkg}/cmake"; do
            if [ -d "${base}/${pkg}" ]; then
                install -d "${target_lib_dir}/cmake/${pkg}"
                find "${base}/${pkg}" -maxdepth 1 -type f -name '*.cmake' \
                    -exec install -m 0644 {} "${target_lib_dir}/cmake/${pkg}/" \; 2>/dev/null || true
            fi
        done
    done
    # Make /opt libs discoverable by the dynamic linker
    install -d "${D}${sysconfdir}/ld.so.conf.d"
    printf '%s\n' "/opt/belledonne-communications/lib" > "${D}${sysconfdir}/ld.so.conf.d/belledonne.conf"
}
```

- R240: Blank separator. It changes no variable and adds no task.

- R241: Describes a shallow CMake-config copy. Referenced companion files may still be required.

- R242: Creates destinations for MbedTLS and Opus CMake configs. Directory presence does not prove a usable exported package.

- R243: Finds matching MbedTLS CMake files at depth up to two. The next line continues the same shell command.

- R244: Copies each match, hides stderr and tolerates failure. Flattening source directories can change the relative paths expected by configs.

- R245: Searches for matching Opus CMake files with the same depth limit.

- R246: Copies matching Opus configs and ignores errors. Test find_package against the exported result, not only the file count.

- R247: Blank separator. It changes no variable and adds no task.

- R248: Introduces another component-config copying loop. It is not a declaration of build-time dependencies.

- R249: Describes two expected source layouts. Compare that intention with the constructed paths in the next lines.

- R250: Loops over exact component names. Case matters on Linux; mismatched capitalization can silently skip a package directory.

- R251: Tries /usr/lib/cmake and /usr/share/pkg/cmake as base paths. The next line adds pkg again, so the second candidate becomes /usr/share/pkg/cmake/pkg. That does not match the usual /usr/share/pkg/cmake layout described in the comment.

- R252: Tests base/pkg, which reveals that duplicated package suffix in the second candidate. Missing directories are silently ignored.

- R253: Creates the component destination under the final SDK lib/cmake tree.

- R254: Finds only top-level .cmake files in the chosen source directory. Nested files and non-.cmake resources are excluded.

- R255: Copies those files with mode 0644 and ignores failure. Absolute paths inside imported targets remain unchanged.

- R256: Ends the candidate-directory existence check.

- R257: Ends the loop over candidate base paths.

- R258: Ends the loop over component names.

- R259: States the runtime-loader intention. Writing configuration alone does not prove that the target's loader cache is refreshed or that the image uses glibc.

- R260: Creates ld.so.conf.d inside D, not in the build host's real /etc.

- R261: Writes the final SDK lib path to belledonne.conf. The build shell interprets the printf newline; the device must support and consume this loader configuration.

- R262: Ends the installation append hook.

R263–R273. QA EXEMPTIONS AND PACKAGE VERSIONS

```bitbake

#Allow non-symlink .so files and static libraries in ${PN} package
INSANE_SKIP:${PN} += "dev-so staticdev already-stripped  installed-vs-shipped"

TARGET_LDFLAGS += " -lrt"
ILES:${PN} += "${sysconfdir}/ld.so.conf.d/belledonne.conf"
CMAKEOPTS += " -DBC_USE_GIT_VERSION=OFF -DBC_GIT_DESCRIBE_VERSION=5.3.0-alpha -DBC_GIT_DESCRIBE_VERSION=5.3.0-alpha"

PR = "${INC_PR}.0"
PV = "latest"
PKGV = "${GITPKGVTAG}"
```

- R263: Blank separator. It changes no variable and adds no task.

- R264: Explains only part of the following QA exemptions. already-stripped and installed-vs-shipped are additional checks beyond .so and static archives.

- R265: Skips four QA checks for PN. This permits packaging to proceed despite those classes of issue; it neither fixes missing files nor restores stripped debug symbols.

- R266: Blank separator. It changes no variable and adds no task.

- R267: Adds librt linkage to TARGET_LDFLAGS. Its necessity depends on the selected libc/toolchain and code; inspect the actual link command rather than assuming every platform needs it.

- R268: Contains ILES rather than FILES, so it does not add a packaging rule. Default FILES may already include /etc; verify whether the configuration is packaged before attributing a missing-file bug solely to this typo.

- R269: Appends version options to CMAKEOPTS and repeats BC_GIT_DESCRIBE_VERSION. The supplied custom configure command consumes EXTRA_OECMAKE, not CMAKEOPTS; inspect all final task implementations before assuming these options reach CMake.

- R270: Blank separator. It changes no variable and adds no task.

- R271: Builds PR as r0.0 from INC_PR. PR is a package revision, distinct from the upstream source commit and PV.

- R272: Sets the recipe version to latest, matching the filename. It is a selector label, not an immutable release identifier.

- R273: Uses gitpkgv's tag-derived value as the package version. Check the resulting PKGV and package-manager ordering across releases; do not infer it from PV=latest.

04. LOCAL CMAKE CLASS

File: classes/cmakebuilder.bbclass

C001–C026. GENERATOR AND HOST TOOLS

```bitbake
# Path to the CMake file to process.
OECMAKE_SOURCEPATH ??= "${S}"

DEPENDS:prepend = "cmake-native "
B = "${WORKDIR}/build"

# We need to unset CCACHE otherwise cmake gets too confused
CCACHE = ""

# What CMake generator to use.
# The supported options are "Unix Makefiles" or "Ninja".
OECMAKE_GENERATOR ?= "Ninja"

python() {
    generator = d.getVar("OECMAKE_GENERATOR")
    if generator == "Unix Makefiles":
        args = "-G 'Unix Makefiles' -DCMAKE_MAKE_PROGRAM=" + d.getVar("MAKE")
        d.setVar("OECMAKE_GENERATOR_ARGS", args)
        d.setVarFlag("do_compile", "progress", "percent")
    elif generator == "Ninja":
        d.appendVar("DEPENDS", " ninja-native")
        d.setVar("OECMAKE_GENERATOR_ARGS", "-G Ninja -DCMAKE_MAKE_PROGRAM=ninja")
        d.setVarFlag("do_compile", "progress", "outof:^\[(\d+)/(\d+)\]\s+")
    else:
        bb.fatal("Unknown CMake Generator %s" % generator)
}
```

- C001: Introduces the configurable source directory for CMake.

- C002: Uses S as a weak default for the CMake source path. A recipe can select a subdirectory instead.

- C003: Blank separator. It changes no variable and adds no task.

- C004: Prepends cmake-native to build dependencies, with a separating space. This supplies the host CMake executable.

- C005: Places generated build files in WORKDIR/build, separate from S by default.

- C006: Blank separator. It changes no variable and adds no task.

- C007: Documents the author's decision to disable compiler caching for this setup. It does not disable Yocto sstate.

- C008: Clears CCACHE for this class. Compiler caching and task-output caching are different mechanisms.

- C009: Blank separator. It changes no variable and adds no task.

- C010: Introduces the build-system generator setting.

- C011: Documents the two generators explicitly supported by the Python block below.

- C012: Defaults to Ninja when no earlier value is set. ?= is not the same weak-default operator as ??=.

- C013: Blank separator. It changes no variable and adds no task.

- C014: Starts parse-time Python to choose the generator and dependencies.

- C015: Reads the expanded generator setting from the datastore.

- C016: Selects the Unix Makefiles branch by exact string comparison.

- C017: Builds CMake generator arguments and chooses the configured Make executable.

- C018: Stores those arguments for the configure task.

- C019: Configures progress reporting for Make output. This affects BitBake's progress display, not generated code.

- C020: Selects the Ninja branch.

- C021: Adds ninja-native as a host build dependency.

- C022: Stores Ninja-specific CMake generator arguments.

- C023: Defines a regex that extracts completed/total counts from Ninja output. It is a Python string containing regex escapes; modernizing its spelling should preserve the regex semantics.

- C024: Handles every unsupported generator value.

- C025: Aborts parsing with bb.fatal rather than silently choosing another build system.

- C026: Closes generator-selection Python.

C027–C057. COMPILER FLAGS AND SEARCH SETTINGS

```bitbake
# C/C++ Compiler (without cpu arch/tune arguments)
OECMAKE_C_COMPILER ?= "`echo ${CC} | sed 's/^\([^ ]*\).*/\1/'`"
OECMAKE_CXX_COMPILER ?= "`echo ${CXX} | sed 's/^\([^ ]*\).*/\1/'`"
OECMAKE_AR ?= "${AR}"

# Compiler flags
OECMAKE_C_FLAGS ?= "${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS} ${CFLAGS}"
OECMAKE_CXX_FLAGS ?= "${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS} ${CXXFLAGS}"
OECMAKE_C_FLAGS_RELEASE ?= "-DNDEBUG"
OECMAKE_CXX_FLAGS_RELEASE ?= "-DNDEBUG"
OECMAKE_C_LINK_FLAGS ?= "${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS} ${CPPFLAGS} ${LDFLAGS}"
OECMAKE_CXX_LINK_FLAGS ?= "${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS} ${CXXFLAGS} ${LDFLAGS}"
CXXFLAGS += "${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS}"
CFLAGS += "${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS}"

OECMAKE_RPATH ?= ""
OECMAKE_PERLNATIVE_DIR ??= ""
OECMAKE_EXTRA_ROOT_PATH ?= ""

OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM = "ONLY"
OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM_class-native = "BOTH"

EXTRA_OECMAKE:append = " ${PACKAGECONFIG_CONFARGS}"

EXTRA_OECMAKE_BUILD:prepend:task-compile = "${PARALLEL_MAKE} "
EXTRA_OECMAKE_BUILD:prepend:task-install = "${PARALLEL_MAKEINST} "

OECMAKE_TARGET_COMPILE ?= "all"
OECMAKE_TARGET_INSTALL ?= "install"

FILES_${PN}-dev += "${libdir}/cmake ${datadir}/cmake"
```

- C027: Introduces extraction of compiler executable names from compiler commands.

- C028: Uses shell substitution and sed to take the first word of CC. Compiler wrappers or paths with spaces can invalidate that assumption.

- C029: Does the same for CXX. The remaining architecture/sysroot flags are supplied separately.

- C030: Defaults the archiver to AR. This must be the appropriate tool for the target objects.

- C031: Blank separator. It changes no variable and adds no task.

- C032: Introduces compiler and linker flag construction.

- C033: Combines target architecture, toolchain options and CFLAGS for C compilation.

- C034: Builds the corresponding C++ flag string.

- C035: Adds NDEBUG for Release C builds. This typically disables assert checks; it is not itself an optimization level.

- C036: Applies that Release define to C++.

- C037: Builds a C link-flags string containing architecture/toolchain, preprocessor and linker flags. Inspect the generated link rule to confirm effective use.

- C038: Builds the C++ link-flags string, including CXXFLAGS. Some flags may already be present elsewhere.

- C039: Also appends architecture/toolchain options to CXXFLAGS. Combined with C034 this can repeat them; inspect final expansion.

- C040: Does the same for CFLAGS, potentially duplicating terms included by C033.

- C041: Blank separator. It changes no variable and adds no task.

- C042: Defaults the desired install RPATH to empty. R130 separately asks CMake to skip RPATH.

- C043: Leaves an optional native Perl root empty unless another class supplies it.

- C044: Leaves extra CMake search roots empty by default. The recipe fills this with its intermediate SDK tree.

- C045: Blank separator. It changes no variable and adds no task.

- C046: Restricts find_program to configured roots. Unlike the common generic cross-compilation pattern using NEVER, this relies on native tool directories being among those roots.

- C047: Uses old override notation for class-native. On Kirkstone use OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM:class-native.

- C048: Blank separator. It changes no variable and adds no task.

- C049: Appends arguments generated from PACKAGECONFIG to the CMake option list. This connects R083–R099 to actual configure arguments if this path is used.

- C050: Blank separator. It changes no variable and adds no task.

- C051: Prepends the configured compile parallelism only in the task-compile override context.

- C052: Uses the install-parallelism setting in task-install. Effective use depends on which install task runs.

- C053: Blank separator. It changes no variable and adds no task.

- C054: Defaults the CMake build target to all.

- C055: Names install as the installation target. This class does not itself export a do_install implementation at C171.

- C056: Blank separator. It changes no variable and adds no task.

- C057: Adds development metadata paths using old FILES_${PN}-dev notation. Migrate to FILES:${PN}-dev and account for R160's replacing assignment.

C058–C090. TOOLCHAIN FILE GENERATION

```bitbake

# CMake expects target architectures in the format of uname(2),
# which do not always match TARGET_ARCH, so all the necessary
# conversions should happen here.
def map_target_arch_to_uname_arch(target_arch):
    if target_arch == "powerpc":
        return "ppc"
    if target_arch == "powerpc64":
        return "ppc64"
    return target_arch

cmakebuilder_do_generate_toolchain_file() {
    if [ "${BUILD_SYS}" = "${HOST_SYS}" ]; then
        cmake_crosscompiling="set( CMAKE_CROSSCOMPILING FALSE )"
    fi
    cat > ${WORKDIR}/toolchain.cmake <<EOF
# CMake system name must be something like "Linux".
# This is important for cross-compiling.
$cmake_crosscompiling
set( CMAKE_SYSTEM_NAME `echo ${TARGET_OS} | sed -e 's/^./\u&/' -e 's/^\(Linux\).*/\1/'` )
set( CMAKE_SYSTEM_PROCESSOR ${@map_target_arch_to_uname_arch(d.getVar('TARGET_ARCH'))} )
set( CMAKE_C_COMPILER ${OECMAKE_C_COMPILER} )
set( CMAKE_CXX_COMPILER ${OECMAKE_CXX_COMPILER} )
set( CMAKE_ASM_COMPILER ${OECMAKE_C_COMPILER} )
set( CMAKE_AR ${OECMAKE_AR} CACHE FILEPATH "Archiver" )
set( CMAKE_C_FLAGS "${OECMAKE_C_FLAGS}" CACHE STRING "CFLAGS" )
set( CMAKE_CXX_FLAGS "${OECMAKE_CXX_FLAGS}" CACHE STRING "CXXFLAGS" )
set( CMAKE_ASM_FLAGS "${OECMAKE_C_FLAGS}" CACHE STRING "ASM FLAGS" )
set( CMAKE_C_FLAGS_RELEASE "${OECMAKE_C_FLAGS_RELEASE}" CACHE STRING "Additional CFLAGS for release" )
set( CMAKE_CXX_FLAGS_RELEASE "${OECMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "Additional CXXFLAGS for release" )
set( CMAKE_ASM_FLAGS_RELEASE "${OECMAKE_C_FLAGS_RELEASE}" CACHE STRING "Additional ASM FLAGS for release" )
set( CMAKE_C_LINK_FLAGS "${OECMAKE_C_LINK_FLAGS}" CACHE STRING "LDFLAGS" )
set( CMAKE_CXX_LINK_FLAGS "${OECMAKE_CXX_LINK_FLAGS}" CACHE STRING "LDFLAGS" )
```

- C058: Blank separator. It changes no variable and adds no task.

- C059: Introduces target architecture normalization for CMake.

- C060: Explains that Yocto and uname-style architecture names may differ.

- C061: Ends that explanatory comment block.

- C062: Defines a Python helper callable from inline metadata expansion.

- C063: Detects powerpc.

- C064: Maps that spelling to ppc.

- C065: Detects powerpc64.

- C066: Maps it to ppc64.

- C067: Preserves every other architecture spelling, including the normal ARM names.

- C068: Blank separator. It changes no variable and adds no task.

- C069: Defines the shell implementation for generating a toolchain file. This is not yet the final exported task name.

- C070: Checks whether build and host system identifiers are the same. In this recipe, host means the system on which the built component will run.

- C071: For a native build, prepares an explicit FALSE setting for cross-compilation status.

- C072: Closes that build/host comparison.

- C073: Starts an unquoted here-document writing toolchain.cmake. Shell substitutions and variables are expanded while the file is generated.

- C074: Begins comments that will be written into the generated CMake file.

- C075: Explains why CMake needs a recognizable target-system name.

- C076: Inserts the optional shell variable from C071. It is empty for the normal cross case.

- C077: Transforms TARGET_OS into a CMake system name, normalizing Linux variants to Linux. This system setup is what normally activates cross-compilation.

- C078: Uses inline Python to normalize TARGET_ARCH for CMAKE_SYSTEM_PROCESSOR.

- C079: Writes the chosen target C compiler into the toolchain file.

- C080: Writes the chosen target C++ compiler.

- C081: Uses the C compiler driver for assembly source handling.

- C082: Stores the archiver as a cached FILEPATH value.

- C083: Stores initial C compiler flags in CMake's cache. Existing cache state can affect whether a non-FORCE cached value changes.

- C084: Stores C++ compiler flags in the cache.

- C085: Reuses the C flag string for assembly compilation.

- C086: Stores additional Release flags for C.

- C087: Stores additional Release flags for C++.

- C088: Reuses the C Release flags for assembly.

- C089: Writes the class's C link-flags variable. Verify its consumption in the generated build command, especially for nested projects.

- C090: Writes the corresponding C++ link-flags variable.

C091–C119. CMAKE ROOTS AND TASK ORDERING

```bitbake

# only search in the paths provided so cmake doesnt pick
# up libraries and tools from the native build machine
# BC modify: it makes more sense to put OECMAKE_EXTRA_ROOT_PATH first in the list order matters for cmake, and we should prefer custom paths for libraries/executables/includes search.
set( CMAKE_FIND_ROOT_PATH ${OECMAKE_EXTRA_ROOT_PATH} ${STAGING_DIR_HOST} ${STAGING_DIR_NATIVE} ${CROSS_DIR} ${OECMAKE_PERLNATIVE_DIR} ${EXTERNAL_TOOLCHAIN})
set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ${OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM} )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

# Use qt.conf settings
set( ENV{QT_CONF_PATH} ${WORKDIR}/qt.conf )

# We need to set the rpath to the correct directory as cmake does not provide any
# directory as rpath by default
set( CMAKE_INSTALL_RPATH ${OECMAKE_RPATH} )

# Use native cmake modules
list(APPEND CMAKE_MODULE_PATH "${STAGING_DATADIR}/cmake/Modules/")

# add for non /usr/lib libdir, e.g. /usr/lib64
set( CMAKE_LIBRARY_PATH ${libdir} ${base_libdir})

EOF
}

addtask generate_toolchain_file after do_patch before do_configure

CONFIGURE_FILES = "CMakeLists.txt"
```

- C091: Blank separator. It changes no variable and adds no task.

- C092: Introduces restricted search roots intended to avoid accidental host dependencies.

- C093: Continues that explanation; it is written as a CMake comment.

- C094: Explains why SDK-specific roots are placed first. Earlier search locations can select a different package copy.

- C095: Combines intermediate SDK, target sysroot, native sysroot, cross-tool and optional roots. Check these paths rather than assuming every root contains target libraries only.

- C096: Restricts find_package searches to configured roots.

- C097: Applies the selected find_program root policy. Native build tools must still resolve to host-runnable executables.

- C098: Restricts library searches to the roots.

- C099: Restricts header searches to the roots.

- C100: Blank separator. It changes no variable and adds no task.

- C101: Introduces Qt configuration for tool execution.

- C102: Sets QT_CONF_PATH in the CMake process environment to WORKDIR/qt.conf. It is not a deployment of that file to the phone.

- C103: Blank separator. It changes no variable and adds no task.

- C104: Introduces the install-RPATH setting.

- C105: Continues the author's explanation of the default behavior.

- C106: Sets CMAKE_INSTALL_RPATH from OECMAKE_RPATH, empty here unless overridden. R130's skip setting can disable RPATH processing altogether.

- C107: Blank separator. It changes no variable and adds no task.

- C108: Introduces additional CMake module search paths.

- C109: Appends a module directory from STAGING_DATADIR. Inspect its expanded origin; the comment alone does not establish which sysroot supplied it.

- C110: Blank separator. It changes no variable and adds no task.

- C111: Introduces support for nonstandard library directory names.

- C112: Adds libdir and base_libdir to CMAKE_LIBRARY_PATH. This does not copy files into those directories.

- C113: Blank separator. It changes no variable and adds no task.

- C114: Ends the shell here-document; the preceding text becomes toolchain.cmake.

- C115: Ends the toolchain-generator shell function.

- C116: Blank separator. It changes no variable and adds no task.

- C117: Adds generation after patching and before configuration in the task graph. Other inherited classes may define/export the same task, so inspect the final result.

- C118: Blank separator. It changes no variable and adds no task.

- C119: Records CMakeLists.txt as configuration input for consumers of CONFIGURE_FILES. This line does not invoke CMake on its own.

C120–C138. CONFIGURE CLEANUP AND CACHE INPUTS

```bitbake

cmakebuilder_do_configure() {
    if [ "${OECMAKE_BUILDPATH}" ]; then
        bbnote "cmakebuilder.bbclass no longer uses OECMAKE_BUILDPATH.  The default behaviour is now out-of-tree builds with B=WORKDIR/build."
    fi
    if [ "${S}" != "${B}" ]; then
        rm -rf ${B}
        mkdir -p ${B}
        cd ${B}
    else
        find ${B} -name CMakeFiles -or -name Makefile -or -name cmake_install.cmake -or -name CMakeCache.txt -delete
    fi

    # Just like autotools cmake can use a site file to cache result that need generated binaries to run
    if [ -e ${WORKDIR}/site-file.cmake ] ; then
        oecmake_sitefile="-C ${WORKDIR}/site-file.cmake"
    else
        oecmake_sitefile=
    fi
```

- C120: Blank separator. It changes no variable and adds no task.

- C121: Defines this class's configure implementation. It must survive final inheritance/export resolution to run as do_configure.

- C122: Checks an obsolete optional build-path variable.

- C123: Logs that the old variable is no longer used and describes the current B convention.

- C124: Ends the obsolete-variable check.

- C125: Chooses an out-of-source cleanup when S and B differ.

- C126: Recursively removes B before configuring. This is existing source under review, not a command to run manually; an incorrect B would make this dangerous.

- C127: Recreates the build directory.

- C128: Changes the task's working directory to B.

- C129: Handles an in-source build, where S equals B.

- C130: Runs find with OR branches and a final -delete. Because AND binds more tightly than OR, deletion is attached only to the last name test; this is not equivalent to deleting every listed name. Review grouping and directory handling before changing it.

- C131: Ends the source/build cleanup selection.

- C132: Blank separator. It changes no variable and adds no task.

- C133: Introduces an optional CMake initial-cache file useful for cross-build configuration checks.

- C134: Checks whether that cache file exists.

- C135: Prepares a -C argument to preload it. This does not run target binaries.

- C136: Handles the absence of a site file.

- C137: Clears the optional argument.

- C138: Ends the site-file selection.

C139–C160. THE ACTUAL CONFIGURE INVOCATION

```bitbake

    cmake \
      ${OECMAKE_GENERATOR_ARGS} \
      $oecmake_sitefile \
      ${OECMAKE_SOURCEPATH} \
      -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
      -DCMAKE_INSTALL_BINDIR:PATH=${@os.path.relpath(d.getVar('bindir'), d.getVar('prefix'))} \
      -DCMAKE_INSTALL_SBINDIR:PATH=${@os.path.relpath(d.getVar('sbindir'), d.getVar('prefix'))} \
      -DCMAKE_INSTALL_LIBEXECDIR:PATH=${@os.path.relpath(d.getVar('libexecdir'), d.getVar('prefix'))} \
      -DCMAKE_INSTALL_SYSCONFDIR:PATH=${sysconfdir} \
      -DCMAKE_INSTALL_SHAREDSTATEDIR:PATH=${@os.path.relpath(d.getVar('sharedstatedir'), d.  getVar('prefix'))} \
      -DCMAKE_INSTALL_LOCALSTATEDIR:PATH=${localstatedir} \
      -DCMAKE_INSTALL_LIBDIR:PATH=${@os.path.relpath(d.getVar('libdir'), d.getVar('prefix'))} \
      -DCMAKE_INSTALL_INCLUDEDIR:PATH=${@os.path.relpath(d.getVar('includedir'), d.getVar('prefix'))} \
      -DCMAKE_INSTALL_DATAROOTDIR:PATH=${@os.path.relpath(d.getVar('datadir'), d.getVar('prefix'))} \
      -DCMAKE_INSTALL_SO_NO_EXE=0 \
      -DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/toolchain.cmake \
      -DCMAKE_VERBOSE_MAKEFILE=1 \
      -DCMAKE_NO_SYSTEM_FROM_IMPORTED=1 \
      ${EXTRA_OECMAKE} \
      -Wno-dev
}
```

- C139: Blank separator. It changes no variable and adds no task.

- C140: Starts the multiline CMake configure invocation. The final effective command is the key evidence for debugging options.

- C141: Passes the selected generator arguments.

- C142: Passes the optional initial-cache argument when present.

- C143: Passes the source directory to CMake.

- C144: Sets a baseline installation prefix. Later EXTRA_OECMAKE can pass the same CMake variable again, so inspect the final cache.

- C145: Converts bindir into a path relative to prefix for the install layout.

- C146: Does the same for administrative executables in sbindir.

- C147: Does the same for helper executables in libexecdir.

- C148: Passes the configuration directory, normally /etc, as an absolute path.

- C149: Calculates the shared-state directory relative to prefix. Whitespace after d. in the Python expression is unusual style but does not by itself establish a syntax error.

- C150: Passes the local-state directory as configured by the distribution.

- C151: Passes libdir relative to prefix, allowing layouts such as lib or lib64.

- C152: Passes the relative header directory.

- C153: Passes the relative data-root directory.

- C154: Sets the shared-library installation permission policy used by CMake on applicable platforms. It does not replace packaging QA.

- C155: Points to the generated toolchain file. A later duplicate is present in the recipe; verify that values agree.

- C156: Requests verbose Makefile output. Ninja verbosity is controlled separately by the generated build invocation.

- C157: Tells CMake not to treat imported-target include directories as system includes merely because they are imported. This can change warning behavior.

- C158: Appends the recipe's additional arguments, including PACKAGECONFIG-derived flags. Repeated variables require checking final cache values.

- C159: Suppresses CMake developer warnings. It does not fix the underlying issue or suppress compilation errors.

- C160: Ends the custom configure function.

C161–C171. BUILD HELPER AND TASK EXPORT

```bitbake

cmake_runcmake_build() {
    bbnote ${DESTDIR:+DESTDIR=${DESTDIR} }VERBOSE=1 cmake --build '${B}' "$@" -- ${EXTRA_OECMAKE_BUILD}
    eval ${DESTDIR:+DESTDIR=${DESTDIR} }VERBOSE=1 cmake --build '${B}' "$@" -- ${EXTRA_OECMAKE_BUILD}
}

cmakebuilder_do_compile()  {
    cmake_runcmake_build --target ${OECMAKE_TARGET_COMPILE}
}

EXPORT_FUNCTIONS do_configure do_compile do_generate_toolchain_file
```

- C161: Blank separator. It changes no variable and adds no task.

- C162: Defines a helper to invoke the generated build system through cmake --build.

- C163: Logs the command, conditionally showing DESTDIR and enabling verbose output. This line logs rather than executes the build.

- C164: Executes the assembled command through eval, forwarding target arguments and native build-tool options. eval makes correct quoting especially important; inputs should remain controlled metadata.

- C165: Ends the build helper.

- C166: Blank separator. It changes no variable and adds no task.

- C167: Defines the class's compile task implementation.

- C168: Builds the configured target, normally all, through the helper.

- C169: Ends the compile function.

- C170: Blank separator. It changes no variable and adds no task.

- C171: Exports configure, compile and toolchain generation under the normal task names. No install function is exported here; the recipe relies on another inherited class for the base installation.

05. LAYER CONFIGURATION

File: conf/layer.conf

L001–L011. LAYER DISCOVERY AND VERSION PREFERENCE

```bitbake
BBPATH := "${BBPATH}:${LAYERDIR}"
BBFILES := "${BBFILES} ${LAYERDIR}/recipes-*/*/*.bb ${LAYERDIR}/recipes-*/*/*/*.bb ${LAYERDIR}/recipes-*/*/*/*.bbappend"
BBFILE_COLLECTIONS += "bc"
BBFILE_PATTERN_bc := "^${LAYERDIR}/"
BBFILE_PRIORITY_bc := "5"
LAYERSERIES_COMPAT_bc = "kirkstone"

LICENSE_FLAGS_ACCEPTED="commercial_libav"

PREFERED_LINPHONE_SDK_RECIPE_VERSION ?= "latest"
PREFERRED_VERSION_linphone-sdk="${PREFERED_LINPHONE_SDK_RECIPE_VERSION}"
```

- L001: Immediately extends BBPATH with this layer directory so BitBake can locate classes and related metadata. := expands the value at assignment time.

- L002: Defines recipe discovery patterns for two nesting depths, but append discovery only for the deeper pattern. A shallow .bbappend placed inside this layer would not be discovered by this line. Other layers use their own BBFILES rules.

- L003: Registers the collection name bc. This is the key used by the following layer-specific variables.

- L004: Associates matching paths with the bc collection. The underscore in BBFILE_PATTERN_bc is part of the variable convention, not an obsolete override to convert blindly.

- L005: Assigns layer priority 5. Priority can influence recipe selection when layers provide competing recipes; it is not a build execution order.

- L006: Declares Kirkstone compatibility. This is a metadata declaration, not proof that every line has been migrated correctly or every BSP dependency is available.

- L007: Blank separator. It changes no variable and adds no task.

- L008: Replaces LICENSE_FLAGS_ACCEPTED with commercial_libav. Reusable layers should leave license policy to the product configuration rather than silently replacing it.

- L009: Blank separator. It changes no variable and adds no task.

- L010: Defaults the custom selector to latest if not already set. PREFERED is the original spelling and must not be silently corrected when using this hook.

- L011: Maps that custom selector into BitBake's standard recipe-version preference. The underscore in PREFERRED_VERSION_linphone-sdk is valid naming, not an old override. This snapshot only supplies the latest recipe.

06. HOW THE INHERITED CLASSES FIT TOGETHER

The local cmakebuilder is not the entire build system. cmake_qt5 inherits cmake and qmake5_paths. Other inherited classes provide gettext, pkg-config, Perl/Python support, RPATH-related tooling and Git package versions. A task body named cmakebuilder_do_configure does not by itself prove that final do_configure uses it. Follow the expanded task bodies and their metadata history; also inspect generated run.do_* scripts after tasks have run.

The class source files from the original product build are needed to establish exact historical behavior. The official Kirkstone cmake_qt5 reference confirms its standard cmake inheritance, but does not prove that the product used that exact revision. Old override issues must be resolved before a failing snapshot can be inspected through bitbake -e.

07. COMMANDS FOR CHECKING THE EXPLANATION

Run these commands only from the existing phone build environment with its BSP and Qt layers. Keep the full expanded metadata local because it can contain private source URLs and build paths. These are read/inspection commands except the explicitly named build tasks.

```bash

bitbake-layers show-layers
bitbake-layers show-recipes linphone-sdk
bitbake-layers show-appends
bitbake -e linphone-sdk > linphone-sdk.environment.txt

grep -E '^(FILE|SRCREV|PV|PR|PKGV|S|B|D|T|RECIPE_SYSROOT|BUILD_INSTALL_PATH|INSTALL_PATH_OUT)=' \
    linphone-sdk.environment.txt
grep -E '^(PACKAGECONFIG|PACKAGECONFIG_CONFARGS|DEPENDS|PACKAGES|EXTRA_OECMAKE|CMAKEOPTS|LIC_FILES_CHKSUM)=' \
    linphone-sdk.environment.txt

sed -n '/^do_configure()/,/^}/p' linphone-sdk.environment.txt
sed -n '/^do_compile()/,/^}/p' linphone-sdk.environment.txt
sed -n '/^do_install()/,/^}/p' linphone-sdk.environment.txt
bitbake -c listtasks linphone-sdk
```

To inspect real installation and packaging, first use an approved pinned source revision and run the selected build stages. Read the log of any failure instead of assuming the next stage exists. A completed do_install does not yet create packages-split; that is produced during packaging.

```bash

bitbake -c install linphone-sdk
bitbake linphone-sdk

oe-pkgdata-util list-pkgs 'linphone-sdk*'
oe-pkgdata-util list-pkg-files linphone-sdk
oe-pkgdata-util list-pkg-files linphone-sdk-dev
oe-pkgdata-util find-path /etc/ld.so.conf.d/belledonne.conf

# Re-read the environment if any build configuration changed.
bitbake -e linphone-sdk > linphone-sdk.environment.txt
sdk_logs=$(sed -n 's/^T="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
sdk_work=$(sed -n 's/^WORKDIR="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
find "$sdk_logs" -maxdepth 1 -name 'log.do_*' -print
find "$sdk_logs" -maxdepth 1 -name 'run.do_*' -print
find "$sdk_work/packages-split" -name 'liblinphone.so*' -print
find "$sdk_work/packages-split" -name '*.pc' -print
```

08. FINDINGS AND A SENSIBLE FIX ORDER

- First make metadata compatible: fix the old overrides in C047/C057 in a maintained working copy. Do not blindly change underscores in L004/L011; those are valid variable conventions.
- Pin sources: address R005/R059 and record actual parent/submodule commits. R103 and R269 are not source pins.
- Correct the clear typo R268 and inspect actual package contents before claiming a user-visible failure.
- Resolve the undefined default zxing option and inspect final graphics/codec flags in R083–R099.
- Establish actual task implementations before changing installation or toolchain logic.
- Add mandatory-output checks around R202–R205 and required plugins instead of swallowing all errors.
- Review the second CMake-copy candidate in R251/R252 and shallow copying in R243–R255. Test exported configs against their actual consumers.
- Review package order and broad FILES rules before removing individual QA skips.
- Correct or replace the in-source cleanup expression C130 before relying on it.
- Move license policy out of reusable layer defaults, verify the active license checksum and verify package-version ordering.
- Rebuild and validate on the actual phone: loader resolution, Core startup, registration, calls, codecs and failover.

09. A SHORT INTERVIEW EXPLANATION

The recipe integrates a modified SDK into the phone image. It fetches source and submodules, prepares Qt/audio/codec dependencies, supplies a cross-compilation configuration and installs the SDK under /opt/belledonne-communications. The application gets headers and libraries through its recipe sysroot. Runtime dependencies and image contents then ensure the phone receives the required libraries and plugins. I would validate the actual fetched commit, generated CMake command, installation tree, packages and device behavior as separate steps.

The supplied snapshot includes implementation shortcuts and several clear inconsistencies. Understanding them is more useful than memorizing every flag: distinguish intention from effective metadata, build paths from device paths, and a recipe package name from a source component name. The snapshot does not establish personal authorship of each line or prove that proposed improvements were historically deployed.

10. SOURCES AND SNAPSHOT IDENTITY

Research date: 2026-11-15. The three local files are the primary source for this walkthrough. External documentation explains tool semantics; it does not confirm the private SDK source or a successful product build.

- R: recipes-bc/linphone-sdk/linphone-sdk/linphone-sdk_latest.bb; 273 lines; SHA-256 f49269e21074e27240bffca2450c98830a5d0d384f517472cc76c9635018161e

- C: classes/cmakebuilder.bbclass; 171 lines; SHA-256 33c0cf2cce41c33105639c2245874dbe47b45e60f0dc97e2172d37a1c65190bb

- L: conf/layer.conf; 11 lines; SHA-256 2a5e1f0d2de89bf4b9e5082afac697de406a36d317ce940fac1f1fde18a57ba7

- BitBake assignment, overrides, functions and export: https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-metadata.html

- Yocto recipe variables: https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html

- Yocto classes: https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html

- Yocto task semantics: https://docs.yoctoproject.org/4.0.30/ref-manual/tasks.html

- QA checks: https://docs.yoctoproject.org/4.0.30/ref-manual/qa-checks.html

- Override migration: https://docs.yoctoproject.org/4.0.30/migration-guides/migration-3.4.html#override-syntax-changes

- Official Qt CMake class reference: https://github.com/meta-qt5/meta-qt5/blob/kirkstone/classes/cmake_qt5.bbclass

- CMake toolchains: https://cmake.org/cmake/help/v3.22/manual/cmake-toolchains.7.html

- CMake staging prefix: https://cmake.org/cmake/help/v3.22/variable/CMAKE_STAGING_PREFIX.html

- GNU find expression precedence: https://www.gnu.org/software/findutils/manual/html_node/find_html/Combining-Primaries-With-Operators.html
