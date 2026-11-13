TECH INDEX

Commands and source/configuration examples use fenced blocks with language labels. Build-host commands, target diagnostics and recipe fragments are separated.

The Yocto Project usage section includes a twelve-step Linphone SDK integration flow, from source selection and recipes through application dependencies, image composition and target validation.

The collection contains 136 answered questions with stable identifiers: 24 each for YCT, BB, EL and BSP, and 20 each for SYS and IMX. Section and question labels are literal text, so they do not depend on automatic list numbering.

Scope: Only Yocto Project, BitBake, Embedded Linux, systemd, NXP i.MX and BSP, as explicitly requested. Other CV and request technologies are outside this collection.

RECOMMENDED READING ORDER

- Start with Yocto-Project.md: foundations, the twelve-step Linphone SDK flow and practical exercises LAB-01 through LAB-04.
- Continue with BitBake.md: recipe mechanics, dependencies, package splitting and QA diagnosis.
- Read BSP.md with Embedded-Linux.md: kernel/device tree, boot, cross-development and target diagnostics.
- Use systemd.md for startup and NXP-i.MX.md for the hardware/platform boundary.
- For quick review, open section 8 in each topic: every question has an answer and a stable identifier.

CHECKLIST ROUTE

- Yocto Project: Poky/configuration, caches and four practical exercises: QEMU, CMake application, kernel changes and board overlay.
- BitBake: build classes, package splitting, overrides, devtool, source/license metadata and QA.
- BSP: kernel patches/fragments, external modules, device-tree build and overlays.
- Embedded Linux: boot/cmdline, SDK, target tools, hardware interfaces and OTA/security.
- systemd: unit packaging and enablement through Yocto.

BUILD AND TOOLING

- Yocto Project: Yocto-Project.md — SIP-BASED PHONE SOFTWARE; request: Yocto, layers, recipes and images.
- BitBake: BitBake.md — SIP-BASED PHONE SOFTWARE; request: BitBake and recipes.

EMBEDDED AND OPERATING SYSTEM

- Embedded Linux: Embedded-Linux.md — SIP-BASED PHONE SOFTWARE; request: embedded Linux.
- systemd: systemd.md — SIP-BASED PHONE SOFTWARE; request: embedded Linux and image integration.
- NXP i.MX: NXP-i.MX.md — SIP-BASED PHONE SOFTWARE; request: adjacent embedded target experience.
- BSP: BSP.md — SIP-BASED PHONE SOFTWARE, target integration; request: BSP customization.
