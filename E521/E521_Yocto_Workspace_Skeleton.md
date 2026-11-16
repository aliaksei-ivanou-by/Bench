YOCTO WORKSPACE SKELETON: POKY, META-BC AND PRODUCT LAYERS

Context: E521, Yocto Kirkstone. Research date: 2026-11-16. This is an example workspace organization. The meta-bc subtree follows the candidate-supplied snapshot; other product directories illustrate responsibilities rather than reconstructing the original private workspace.

01. THE BASIC IDEA

The workspace contains source repositories, enabled metadata layers, a build directory and caches. sources/ is just a convenient parent directory, not a layer. A layer normally has conf/layer.conf. BitBake reads enabled layers from build/conf/bblayers.conf. A directory called meta-something is not enabled merely because it exists.

The directory names below are a convention. Repositories can live elsewhere, including beside Poky. What matters is the configured path, compatible metadata revisions and actual layer dependencies. Keep source and build paths free of spaces.

02. MINIMAL WORKING BASE

```text
yocto-workspace/
|-- sources/
|   `-- poky/
|       |-- bitbake/
|       |-- meta/
|       |   |-- conf/
|       |   |-- classes/
|       |   `-- recipes-core/
|       |-- meta-poky/
|       |-- meta-yocto-bsp/
|       |-- scripts/
|       `-- oe-init-build-env
|-- build-qemu/
|   |-- conf/
|   |   |-- bblayers.conf
|   |   `-- local.conf
|   |-- cache/
|   `-- tmp/
|-- downloads/
`-- sstate-cache/
```

- poky/ is a reference integration repository. It is not one single metadata layer.
- poky/bitbake/ contains the build engine. Do not add it as a layer.
- poky/meta/ is OpenEmbedded-Core: base recipes, classes and configuration.
- poky/meta-poky/ adds the reference Poky distribution policy.
- poky/meta-yocto-bsp/ supplies reference hardware BSP metadata; it does not replace a product-specific NXP BSP.
- oe-init-build-env prepares the shell and creates/selects the build directory.
- build-qemu/ contains local configuration and generated output. It is not a source layer.
- downloads/ stores fetched inputs; sstate-cache/ stores reusable task outputs. Their locations are configured separately.

03. A PHONE WORKSPACE WITH EXTERNAL LAYERS

```text
yocto-workspace/
|-- sources/
|   |-- poky/
|   |-- meta-openembedded/
|   |   |-- meta-oe/
|   |   |-- meta-networking/
|   |   |-- meta-python/
|   |   `-- meta-multimedia/
|   |-- meta-qt5/
|   |-- meta-freescale/
|   |-- meta-imx/
|   |   |-- meta-bsp/
|   |   `-- meta-sdk/
|   |-- meta-bc/
|   |   |-- conf/layer.conf
|   |   |-- classes/cmakebuilder.bbclass
|   |   `-- recipes-bc/
|   |       |-- linphone-sdk/
|   |       |   |-- linphone-sdk/
|   |       |   |   `-- linphone-sdk_latest.bb
|   |       |   `-- python3-pystache/
|   |       |       `-- python3-pystache_0.6.0.bb
|   |       |-- libyuv/
|   |       |-- gsm/
|   |       |-- spandsp/
|   |       `-- flexisip/
|   `-- meta-phone/
|       |-- conf/layer.conf
|       |-- recipes-apps/
|       |-- recipes-connectivity/
|       |-- recipes-core/
|       `-- recipes-kernel/
|-- build-phone/
|   |-- conf/bblayers.conf
|   |-- conf/local.conf
|   `-- tmp/
|-- downloads/
`-- sstate-cache/
```

This is a typical organization, not a universal list of required layers. meta-imx is a repository containing several layers: the relevant BBLAYERS entry points to an actual layer such as meta-imx/meta-bsp, not automatically to the repository root. The selected vendor BSP manifest determines which NXP/Freescale layers and revisions are needed. The product’s exact MACHINE and BSP release are not identified by this directory sketch.

meta-openembedded adds reusable package recipes. meta-qt5 supplies Qt recipes and classes. The vendor BSP supplies hardware support. meta-bc supplies the Linphone stack metadata. meta-phone owns product applications, selected packages, services and deliberate overrides. Build-directory names and layer order do not establish which engineer authored the code.

04. WHAT META-BC CONTAINS IN THE SUPPLIED SNAPSHOT

The actual downloaded layer root is C:\Users\User\Downloads\meta-bc\meta-bc. The outer folder is only a container. When registering that copy in a Linux workspace, the layer path must resolve to the directory containing conf/layer.conf. The workspace sketch places that inner layer directly at sources/meta-bc to avoid an unnecessary repeated directory name.

The SDK recipe is three recipe-path components below the layer root: recipes-bc/linphone-sdk/linphone-sdk/linphone-sdk_latest.bb. That extra nesting is legal because the supplied layer’s BBFILES explicitly includes it. A different layer using only the standard shallower pattern would not discover the same layout automatically.

Selected original declarations; this is an excerpt, not a complete new layer configuration:

```bitbake
BBFILE_COLLECTIONS += "bc"
BBFILES := "${BBFILES} ${LAYERDIR}/recipes-*/*/*.bb ${LAYERDIR}/recipes-*/*/*/*.bb ${LAYERDIR}/recipes-*/*/*/*.bbappend"
LAYERSERIES_COMPAT_bc = "kirkstone"
PREFERED_LINPHONE_SDK_RECIPE_VERSION ?= "latest"
PREFERRED_VERSION_linphone-sdk = "${PREFERED_LINPHONE_SDK_RECIPE_VERSION}"
```

conf/layer.conf tells BitBake how to find this layer’s metadata. classes/cmakebuilder.bbclass is shared build logic, not the SDK source. The .bb recipe tells BitBake how to obtain and build the SDK; fetched C++ sources go under the build work directory, not automatically into the layer. Existing audit findings still apply: the supplied snapshot includes old override syntax and other issues described in the original-recipe walkthrough.

05. A SMALL PRODUCT LAYER

```text
meta-phone/
|-- conf/
|   `-- layer.conf
|-- recipes-apps/
|   `-- phone-ui/
|       |-- phone-ui_1.0.bb
|       `-- files/
|           `-- phone-ui.service
|-- recipes-connectivity/
|   `-- linphone-sdk/
|       |-- linphone-sdk_latest.bbappend
|       `-- files/
|-- recipes-core/
|   |-- images/
|   |   `-- phone-image.bb
|   `-- packagegroups/
|       `-- packagegroup-phone.bb
`-- recipes-kernel/
    `-- linux/
        `-- files/
```

These are example product filenames. Create a kernel append only for the kernel provider actually selected by the BSP; a directory alone has no build effect. The optional files/ directories hold local inputs such as service units, patches and config fragments. Application source may instead live in a separate Git repository referenced by its recipe.

Example conf/layer.conf for a phone layer that directly depends on both meta-bc and Qt 5:

```bitbake
BBPATH .= ":${LAYERDIR}"
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "phone"
BBFILE_PATTERN_phone = "^${LAYERDIR}/"
BBFILE_PRIORITY_phone = "6"
LAYERSERIES_COMPAT_phone = "kirkstone"
LAYERDEPENDS_phone = "core bc qt5-layer"
```

Dependency values are collection identifiers from the other layers, not directory names. The supplied meta-bc collection is bc; the referenced Kirkstone meta-qt5 collection is qt5-layer. Qt’s layer also declares its own dependencies. Include any further direct product/BSP layer dependencies using their actual collection names. LAYERDEPENDS checks prerequisites; it does not download or enable the layers for you.

The app recipe builds and packages the app. The packagegroup collects runtime package dependencies. The image recipe selects product contents. The SDK append extends the original recipe without duplicating it. A full .bb is appropriate when the product maintains its own provider; an append is appropriate when deliberately extending an existing provider. Priority 6 is an illustrative recipe-selection setting, not an instruction to build this layer after layer 5.

06. BBLAYERS.CONF AND LOCAL.CONF

The following is a minimal reference bblayers.conf for build-qemu, not the complete NXP phone configuration. oe-init-build-env normally creates a starting file; keep its matching configuration version and use bitbake-layers to adjust paths where possible.

```bitbake
POKY_BBLAYERS_CONF_VERSION = "2"
BBPATH = "${TOPDIR}"
BBFILES ?= ""

BBLAYERS ?= " \
    ${TOPDIR}/../sources/poky/meta \
    ${TOPDIR}/../sources/poky/meta-poky \
    ${TOPDIR}/../sources/poky/meta-yocto-bsp \
"
```

TOPDIR is the active build directory. In this layout its parent is yocto-workspace. For the phone, build-phone/conf/bblayers.conf additionally enables the selected meta-openembedded sublayers, Qt, vendor BSP layers, meta-bc and meta-phone. List actual layer directories with conf/layer.conf. Neither sources/ nor the meta-openembedded repository root is the correct substitute for its individual sublayers.

Minimal local.conf choices for the QEMU exercise:

```bitbake
MACHINE = "qemuarm64"
DL_DIR = "${TOPDIR}/../downloads"
SSTATE_DIR = "${TOPDIR}/../sstate-cache"
```

The phone build keeps its actual MACHINE, distribution and vendor setup. Do not replace them with qemuarm64. DISTRO controls distribution policy, MACHINE hardware/tuning, and an image recipe package selection. Important product settings should ultimately be maintained as release-controlled metadata rather than exist only in one developer’s local.conf.

07. COMMANDS FOR THE BASIC QEMU WORKSPACE

On a Linux host prepared for Kirkstone, starting outside an existing build environment:

```bash
mkdir -p "$HOME/yocto-workspace/sources"
cd "$HOME/yocto-workspace"
git clone --branch kirkstone https://git.yoctoproject.org/poky sources/poky
source sources/poky/oe-init-build-env build-qemu

# The current directory is now build-qemu.
bitbake-layers show-layers
```

Set the QEMU local.conf values from section 06, then build the existing reference image:

```bash
bitbake core-image-minimal
runqemu qemuarm64 core-image-minimal nographic slirp
```

Cloning a branch creates a starting exercise, not an immutable release definition. Record or pin the approved layer commits for a reproducible product. A new shell re-enters this exercise from yocto-workspace with source sources/poky/oe-init-build-env build-qemu. There is no reason to copy the entire poky repository for each image.

08. ENABLING LAYERS IN THE PRODUCT BUILD

After the product’s repositories and compatible revisions are present, use its normal build-entry procedure. For a vendor BSP this may be a vendor setup script rather than the bare Poky command. Keep the already-working BSP layer set. The commands below illustrate additions from build-phone in the directory layout above; they are not a complete phone bootstrap.

```bash
bitbake-layers add-layer ../sources/meta-openembedded/meta-oe
bitbake-layers add-layer ../sources/meta-openembedded/meta-networking
bitbake-layers add-layer ../sources/meta-openembedded/meta-python
bitbake-layers add-layer ../sources/meta-openembedded/meta-multimedia
bitbake-layers add-layer ../sources/meta-qt5
bitbake-layers add-layer ../sources/meta-bc

# Create the product layer only if it does not already exist.
bitbake-layers create-layer ../sources/meta-phone
bitbake-layers add-layer ../sources/meta-phone

bitbake-layers show-layers
bitbake-layers show-recipes linphone-sdk
bitbake-layers show-appends
```

create-layer produces a basic layer.conf; adapt it to the product dependencies as in section 05. Existing enabled layers should not be added again. Adding layers only makes metadata available: it does not automatically add every recipe to the image or repair missing vendor providers. The supplied meta-bc recipe needs the phone’s Qt/BSP dependencies and its previously documented fixes.

09. WHERE BUILD OUTPUT APPEARS

```text
build-phone/
|-- conf/
|-- cache/
`-- tmp/
    |-- work/
    |   `-- ... recipe-specific work directories ...
    |-- sysroots-components/
    |-- pkgdata/
    `-- deploy/
        |-- images/
        |   `-- ... configured MACHINE ...
        |-- ipk/
        |-- rpm/
        |-- deb/
        `-- sdk/
```

The work/deploy names shown with ellipses are descriptive categories, not literal directories to create. Package output formats depend on PACKAGE_CLASSES; do not expect ipk, rpm and deb all to exist. DEPLOY_DIR_IMAGE identifies actual board-image output. Kernel images, DTBs, rootfs and Wic files depend on the selected image/BSP; not every build creates every format.

Recipe source S, build directory B, temporary installation D, logs T and recipe dependency sysroots live in the configured build work area. Query the selected recipe instead of hard-coding the architecture/version directory name. Temporary edits in these paths are not durable layer changes.

```bash
bitbake -e linphone-sdk | grep -E '^(S|B|D|T|WORKDIR|RECIPE_SYSROOT)='
bitbake -e phone-image | grep -E '^(MACHINE|DEPLOY_DIR_IMAGE|IMAGE_ROOTFS)='
```

phone-image is the illustrative image recipe from section 05; substitute the actual product recipe when inspecting an existing build.

10. WHERE A CHANGE BELONGS

- SDK source/build behavior: maintain the SDK provider or a deliberate matching append in the product layer.
- Phone C++ behavior: change application source and its existing recipe when build dependencies or installation change.
- Service startup: package the unit with the owning component and configure systemd integration.
- Runtime package set: product image or packagegroup.
- Kernel option or device-tree change: the selected kernel/BSP provider, commonly extended from the product layer.
- A new independent module or service: a recipe for that software component when needed.
- A single GPIO line: no recipe per physical pin. Existing driver, pin configuration and application/library dependencies are separate concerns.
- A shared build mechanism: an appropriately scoped class, not duplicated task code in every recipe.
- Layer registration: bblayers.conf. Layer metadata discovery/dependencies: that layer’s conf/layer.conf.
- Fetch/build caches: DL_DIR and SSTATE_DIR, outside maintained source layers.

11. SOURCES AND RELATED E521 MATERIAL

The supplied meta-bc/conf/layer.conf and its directory listing establish the original recipe nesting and bc collection. No private repository URI is included. The standalone example shows a possible layout; it is not proof of the historical full product layer set or a completed build.

- Layers: https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html

- Source and build directory structure: https://docs.yoctoproject.org/4.0.30/ref-manual/structure.html

- Configuration variables: https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html

- Qt 5 layer configuration: https://github.com/meta-qt5/meta-qt5/blob/kirkstone/conf/layer.conf

- BSP organization: https://docs.yoctoproject.org/4.0.30/bsp-guide/bsp.html

For the complete SDK recipe/application example: E521_Linphone_SDK_Yocto_Example.md. For each original recipe/class line: E521_Linphone_SDK_Original_Recipe_Walkthrough.md.
