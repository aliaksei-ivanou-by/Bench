BSP

SECTION 1. TECHNOLOGY AND VERSION

Category: Embedded platform

Board support package for the relevant NXP i.MX board and vendor release.

SECTION 2. PURPOSE

A board support package is the hardware-specific software and configuration needed to run an operating system on a particular board. Its scope varies by vendor and product; it is not merely one driver or one kernel patch.

SECTION 3. CORE CONCEPTS

A Linux BSP commonly includes bootloader and kernel sources or configuration, device trees, drivers, firmware and build metadata. Boot components initialize the hardware, the kernel uses the board description and drivers, and the root filesystem supplies user-space software.

In a Yocto environment vendor layers can package these elements; exact ownership and contents depend on the release. Board bring-up is the process of establishing basic operation on the actual hardware.

The BSP boundary is easiest to explain through a boot and peripheral path. Hardware-specific initialization begins in firmware and boot components; the kernel uses its configuration, drivers and hardware description; user space relies on the resulting devices and services.

A vendor release may provide recipes, patches and firmware that need to remain compatible with one another. When debugging, determine whether the device is absent in the kernel, unavailable because of permissions or firmware, or present but misused by an application.

Updating one component can affect the others, so boot, peripheral and recovery checks should be performed against the actual board revision. Integration of an application with an inherited BSP is valuable work, but it should not be presented as authorship of the entire BSP.

SECTION 4. TYPICAL USAGE

Start with board revision, vendor BSP release and machine configuration. Trace boot logs through bootloader and kernel, check the device tree and driver, then verify that required firmware and user-space packages are present. Test on physical hardware and record the configuration used.

For a proposed BSP change, compare the actual board revision and supported vendor release first. Trace the affected path from boot artifacts through device tree and driver to the user-space consumer.

Record the baseline configuration, build and deploy the matching artifacts in a suitable test environment, then verify boot, affected peripherals and the documented recovery method. A device that exists in Linux but cannot be opened may indicate permissions or user-space configuration rather than a missing BSP driver.

KERNEL, MODULE AND DEVICE-TREE WORKFLOW

A BSP may include vendor kernel/U-Boot branches, machine configuration, firmware and GPU/VPU/NPU components where required. Not every board needs proprietary blobs. Example ecosystems are meta-raspberrypi, meta-freescale with NXP meta-imx integration, and meta-ti; match their branches and dependencies to the selected release.

KERNEL-01. Patch the provider.

- Determine the provider of virtual/kernel.
- Run devtool modify virtual/kernel where supported, or use the resolved recipe name; the QEMU lab uses linux-yocto.
- Edit workspace sources, make a focused Git commit and build/test.
- Either export with devtool finish linux-yocto ../meta-lab, or manually use git format-patch -1 in the source repository.

In the manual path put the patch under files/ beside a product-layer linux-yocto_%.bbappend containing:

```bitbake
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://0001-lab-change.patch"
```

- The filename must match the exported patch.
- For manual export, remove the workspace override with devtool reset linux-yocto after preserving the patch; finish already removes it.
- Then test the layer-based build.
- Do not apply the same patch twice through both export methods.

Prepare workspace sources for the QEMU example:

```bash
devtool modify linux-yocto
```

After editing, committing and testing, export through devtool:

```bash
devtool finish linux-yocto ../meta-lab
```

Alternative: manual export from the source Git directory:

```bash
git format-patch -1
```

After preserving the patch and adding the append in the manual path:

```bash
devtool reset linux-yocto
```

KERNEL-02. Preserve configuration.

- Run bitbake -c menuconfig virtual/kernel, save, then bitbake -c diffconfig virtual/kernel if the provider supports these tasks.
- Copy the reported fragment into files/lab.cfg and add SRC_URI += "file://lab.cfg" to the append.
- For a linux-yocto exercise the fragment can contain CONFIG_PRINTK_TIME=y.
- Check the final .config and boot behavior.
- A vendor recipe that does not merge fragments needs its supported configuration mechanism; merely fetching .cfg is insufficient.

```bash
bitbake -c menuconfig virtual/kernel
bitbake -c diffconfig virtual/kernel
```

linux-yocto_%.bbappend:

```bitbake
SRC_URI += "file://lab.cfg"
```

files/lab.cfg:

```ini
CONFIG_PRINTK_TIME=y
```

KERNEL-03. Package an external module.

- Use inherit module and a Makefile compatible with the kernel build interface.
- The recipe builds against the selected kernel and packages installed .ko files.
- KERNEL_MODULE_AUTOLOAD += "lab_driver" requests boot-time loading; it does not select the module package into the image.
- Include the actual output package, check modinfo/modprobe and dmesg, and rebuild for kernel ABI/configuration changes.

External-module recipe fragment:

```bitbake
inherit module
KERNEL_MODULE_AUTOLOAD += "lab_driver"
```

DT-01. Build and select the description.

- .dts describes a board; .dtsi holds shared descriptions.
- Kernel build preprocessing and dtc produce .dtb.
- compatible participates in driver matching, but the driver and required clocks, regulators, pinctrl and firmware must also exist.
- KERNEL_DEVICETREE in machine configuration selects outputs for supporting recipes.
- Adding a new .dts through a kernel append usually also needs a patch to the appropriate build Makefile and selection of its output; fetch alone does not build/deploy it.

DT-02. Apply the overlay.

- An overlay uses /plugin/ and compiles to .dtbo.
- Symbol-based overlays need compatible symbol information, commonly generated with dtc -@ for base and overlay.
- U-Boot loads them, selects the FDT, reserves space with fdt resize and applies the overlay with fdt apply before booting Linux.
- Addresses/load commands depend on the board.
- Raspberry Pi firmware instead uses dtoverlay= in config.txt.
- Check the live tree and driver probe after boot; a deployed .dtbo is not proof of application.

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

A vendor BSP accelerates hardware enablement and supplies a validated baseline for supported configurations. It also creates dependencies on vendor releases, patches and compatible layers. Mainline support may simplify upstream maintenance when the hardware and features are adequately supported; the tradeoff must be evaluated per device.

SECTION 6. PITFALLS AND SECURITY

A correct application cannot compensate for a mismatched device tree, missing driver or wrong boot artifact. BSP updates can alter kernel interfaces or firmware expectations; validate peripherals, boot and updates together. Preserve recovery paths and verify authenticity of update artifacts when applicable.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

Before our team joined, there was a basic Yocto platform skeleton. It did not include Linphone SDK, WebRTC or mediasoup. Our team added those components and integrated their build dependencies, packages and runtime requirements into the phone image. My personal contribution covered application/SDK work, BitBake metadata, packaging, image integration and target validation; the stack integration was a team effort.

The request explicitly asks for BSP customization. SIP-BASED PHONE SOFTWARE in the CV describes i.MX integration; Legend describes work within the existing platform. Responsibilities supports application/image integration with that BSP, but not independent ownership of the complete BSP or board bring-up.

SECTION 8. INTERVIEW QUESTIONS

QUESTION BSP-01. What is a BSP?

Answer: A BSP is the hardware-specific software/configuration foundation for an OS on a board. It commonly includes boot and kernel integration, hardware description and drivers or firmware support. Its exact boundary depends on the vendor/product release; it is broader than one application recipe.

QUESTION BSP-02. Is BSP the same as the root filesystem?

Answer: No. The root filesystem contains user-space runtime files. BSP concerns hardware support and may be built alongside or integrated with that filesystem in a vendor image. A complete bootable product needs compatible components across both boundaries.

QUESTION BSP-03. Why is device tree important?

Answer: It tells the kernel how relevant hardware is connected and which resources it uses. Compatible bindings, driver support and the actual board must agree. Device-tree changes do not themselves implement missing driver functionality or correct physical wiring.

QUESTION BSP-04. What can a BSP update break?

Answer: Bootloader/kernel/DTB compatibility, driver behavior, firmware and user-space interfaces can all change. Validate the affected board and application paths, including recovery. A booting kernel is insufficient evidence that camera, GPIO, audio and persistent data still work.

QUESTION BSP-05. Does using a BSP prove ownership of it?

Answer: No. Consuming a BSP and adapting application/image integration differ from designing board support, porting drivers or performing bring-up. Personal claims should identify the actual components and validation performed rather than infer full ownership from platform presence.

QUESTION BSP-06. Is an existing device node proof that the application can use it?

Answer: No. A node may exist while permissions, driver state, firmware or application configuration prevent useful access. Check the operation that fails, kernel logs and the expected interface, then verify behavior with a minimal targeted scenario.

QUESTION BSP-07. How would you validate a BSP update?

Answer: Record a known-good component set and the proposed changes, then test boot, affected peripherals, application interfaces and recovery on each relevant board variant. Preserve a rollback route and compare repeatable scenarios; one successful startup is not a full regression check.

QUESTION BSP-08. Which artifacts must stay compatible across the boot chain?

Answer: Boot firmware/bootloader, kernel, DTB, rootfs and required firmware/modules must match the board and supported interfaces. Record the versions actually deployed, not only the source branch. Mixing artifacts from different releases can boot partially and fail later at a peripheral or application boundary.

QUESTION BSP-09. When is a device-tree change enough, and when is a driver change needed?

Answer: Device tree can express supported hardware connections and configuration through bindings. A missing behavior in the driver requires driver work; absent electrical support needs hardware attention. Start by identifying which boundary lacks the required capability rather than treating every board issue as a DTS edit.

QUESTION BSP-10. What is the role of a defconfig or kernel config fragment?

Answer: They provide requested kernel configuration inputs, while Kconfig dependencies determine the resolved configuration. Inspect the final .config and resulting artifacts. A requested option can be disabled by dependencies or built differently than expected, so the fragment alone is not proof of driver availability.

QUESTION BSP-11. How do built-in drivers, modules and firmware differ?

Answer: Built-in drivers are part of the kernel image; modules are loaded separately and must match the running kernel. Device firmware is another runtime input where required. A driver build can succeed while module packaging, firmware installation or loading fails on the target.

QUESTION BSP-12. Why keep a serial console during bring-up?

Answer: It provides early boot observations before networking, graphics and application logging are available. Use it to identify the last successful stage and preserve the error context. Console settings must match the board and boot configuration; absence of output is not automatically a dead processor.

QUESTION BSP-13. Why inspect device-tree bindings instead of copying nodes?

Answer: Bindings define property meanings, required resources and valid relationships for a compatible device. A copied node can reference the wrong GPIO, clock, interrupt or address and still look plausible. Check against the exact board and driver support, then validate actual probe and I/O.

QUESTION BSP-14. How do you confirm which DTB is actually loaded?

Answer: Compare bootloader configuration and boot logs with the running system's device-tree model and properties. The file generated in the build directory may not be the one deployed or selected at boot. Preserve artifact identity while testing a device-tree hypothesis.

QUESTION BSP-15. What is a reasonable bring-up order for a new board?

Answer: Start with the documented power/boot path and early console, then memory, storage/rootfs and essential interfaces before complex media/application scenarios. Coordinate with hardware specialists and validate one boundary at a time. This is a method description, not evidence of personal ownership of a completed bring-up.

QUESTION BSP-16. Which user-space assumptions must a BSP change preserve?

Answer: Applications depend on device interfaces, permissions, media formats, library/ABI support and startup behavior. Kernel-internal compatibility is not the whole product contract. Identify consumers and run their scenarios after a driver or hardware-description change, including their failure and restart paths.

QUESTION BSP-17. How do you separate an application defect from a BSP integration defect?

Answer: Use a minimal test of the expected kernel/device interface and compare the same image/configuration with the application path. If the interface fails independently, investigate driver/board integration. If it works, inspect application configuration, ownership and timing before changing the BSP.

QUESTION BSP-18. What makes a BSP handoff useful for application engineers?

Answer: Provide compatible image/SDK identifiers, interface expectations, known limitations, reproducible setup and a minimal validation scenario. Include the relevant logs and owners for unresolved boundaries. This lets application engineers test against a defined platform rather than reverse-engineer an undocumented artifact set.

QUESTION BSP-19. What should an update and recovery test include?

Answer: Check authenticated artifact selection where supported, compatible persistent-data layout, interruption handling and a known-good recovery path. Test cold boot and the relevant peripheral/application scenarios after both update and rollback. A backup image does not guarantee recovery if boot selection or data migration is incompatible.

QUESTION BSP-20. What evidence distinguishes BSP consumption from BSP customization?

Answer: Consuming a BSP uses its supported board/image interfaces. Customization is shown by specific changes to machine metadata, boot, kernel, DTB, drivers or firmware integration and their target checks. The exact contribution must be named; one small change does not imply authorship of the whole platform.

QUESTION BSP-21. Does any kernel recipe merge .cfg from SRC_URI?

Answer: No. Check provider support and final .config. Configuration dependencies can alter results, and vendor recipes may require a different mechanism.

QUESTION BSP-22. Does KERNEL_MODULE_AUTOLOAD install the module?

Answer: No. It requests boot loading. Include the actual module package and verify kernel compatibility and successful modprobe on target.

QUESTION BSP-23. Why can a compatible node fail to create a device?

Answer: It may be disabled, the driver absent, or probe may fail/defer due to clocks, regulators, pinctrl or firmware. Check the live tree and kernel logs.

QUESTION BSP-24. What proves an overlay was applied?

Answer: The boot path applies it, expected nodes/properties appear in the live tree, and driver binding succeeds. A compiled .dtbo alone is not proof.

SECTION 9. SOURCES

Research date: 2026-11-13

- https://docs.nxp.com/bundle/UG10163/page/topics/introduction_001.html
- https://docs.kernel.org/devicetree/usage-model.html
- https://docs.yoctoproject.org/4.0.30/bsp-guide/bsp.html
- https://docs.kernel.org/driver-api/driver-model/binding.html
- https://docs.yoctoproject.org/4.0.30/kernel-dev/common.html
- https://docs.u-boot.org/en/latest/usage/fdt_overlays.html
- https://www.raspberrypi.com/documentation/computers/config_txt.html
