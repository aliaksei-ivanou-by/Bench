BSP

SECTION 1. TECHNOLOGY AND VERSION

Category: Embedded platform

Board support package for the relevant NXP i.MX board and vendor release.

SECTION 2. PURPOSE

A board support package, or BSP, supplies the software and settings needed to run a system on a particular board. It connects the operating system to the board hardware.

SECTION 3. CORE CONCEPTS

- A BSP usually includes bootloader and kernel support, board configuration, device descriptions, drivers and required firmware. The exact contents depend on the vendor and product.
- The root filesystem contains user-space programs and data. It works with the BSP but is not the same thing.
- The device tree describes hardware connections and resources. Drivers still need to support those devices.
- Kernel options, modules and firmware determine which devices can initialize. The device files and permissions then affect application access.
- Vendor and product layers can split these responsibilities. Check the actual source of a change before calling it a BSP change.
- New-board bring-up, platform maintenance and application integration are different levels of work. Describe personal changes at the right level.
- Kernel, bootloader, device tree and root filesystem need compatible versions and a tested recovery path.

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

COMPONENT RECOVERY VERSUS BOARD RECOVERY

- An updater running in Linux can recover a compatible application release while the base system remains bootable. It cannot be assumed to repair a broken bootloader, unreadable rootfs or incompatible device tree. Define the separate board reflashing/recovery procedure.
- A serial UART console helps observe boot and issue supported bootloader commands; it is not proof that firmware payloads themselves travel over UART. Confirm the board’s real flashing transport before describing it.
- Application-slot switching is not equivalent to A/B kernel/rootfs. Bootloader selection, retry accounting and boot confirmation require separate platform integration.

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

A vendor BSP accelerates hardware enablement and supplies a validated baseline for supported configurations. It also creates dependencies on vendor releases, patches and compatible layers. Mainline support may simplify upstream maintenance when the hardware and features are adequately supported; the tradeoff must be evaluated per device.

SECTION 6. PITFALLS AND SECURITY

A correct application cannot compensate for a mismatched device tree, missing driver or wrong boot artifact. BSP updates can alter kernel interfaces or firmware expectations; validate peripherals, boot and updates together. Preserve recovery paths and verify authenticity of update artifacts when applicable.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

Before our team joined, there was a basic Yocto platform skeleton. It did not include Linphone SDK, WebRTC or mediasoup. Our team added those components to the phone image, including their build dependencies, packages and the settings needed to run them. My personal contribution covered application/SDK work, BitBake metadata, packaging, image integration and testing on the device; the stack integration was a team effort.

The request explicitly asks for BSP customization. SIP-BASED PHONE SOFTWARE in the CV describes i.MX integration; Legend describes work within the existing platform. Responsibilities supports application/image integration with that BSP, but not independent ownership of the complete BSP or board bring-up.

SECTION 8. INTERVIEW QUESTIONS

QUESTION BSP-01. What is a BSP?

Answer: A BSP is the hardware-specific software/configuration foundation for an OS on a board. It commonly includes boot and kernel integration, hardware description and drivers or firmware support. Its exact boundary depends on the vendor/product release; it is broader than one application recipe.

Example and checks: For a phone product, the application needs both working hardware support and its user-space libraries/settings. These may be delivered together but are different responsibilities. Identify what the vendor provides and what product layers add. This makes failures and update compatibility easier to assign correctly.

QUESTION BSP-02. Is BSP the same as the root filesystem?

Answer: No. The root filesystem contains user-space runtime files. BSP concerns hardware support and may be built alongside or integrated with that filesystem in a vendor image. A complete bootable product needs compatible components across both boundaries.

Example and checks: For a phone product, the application needs both working hardware support and its user-space libraries/settings. These may be delivered together but are different responsibilities. Identify what the vendor provides and what product layers add. This makes failures and update compatibility easier to assign correctly.

QUESTION BSP-03. Why is device tree important?

Answer: It tells the kernel how relevant hardware is connected and which resources it uses. Compatible bindings, driver support and the actual board must agree. Device-tree changes do not themselves implement missing driver functionality or correct physical wiring.

Example and checks: For example, enabling a camera node does not create missing driver code. Check its binding, resources and supported compatible value first. Match addresses, clocks and GPIO to the actual board. Then inspect the driver’s startup messages before testing the complete application.

QUESTION BSP-04. What can a BSP update break?

Answer: Bootloader/kernel/DTB compatibility, driver behavior, firmware and user-space interfaces can all change. Validate the affected board and application paths, including recovery. A booting kernel is insufficient evidence that camera, GPIO, audio and persistent data still work.

Example and checks: After changing the platform, repeat the application’s important hardware scenarios even if compilation still passes. Device paths, permissions, timing and media support may have changed. Record the exact image and board. A useful test result says which functions worked on that combination.

QUESTION BSP-05. Does using a BSP prove ownership of it?

Answer: No. Consuming a BSP and adapting application/image integration differ from designing board support, porting drivers or performing bring-up. Personal claims should identify the actual components and validation performed rather than infer full ownership from platform presence.

Example and checks: For example, adapting a package or service to use an existing BSP is not independent board bring-up. Explain the exact file or interface you changed. Then describe the target evidence that checked it. This gives a stronger answer than either claiming the whole BSP or dismissing integration as trivial.

QUESTION BSP-06. Is an existing device node proof that the application can use it?

Answer: No. A node may exist while permissions, driver state, firmware or application configuration prevent useful access. Check the operation that fails, kernel logs and the expected interface, then verify behavior with a minimal targeted scenario.

Example and checks: Start with a minimal device check before the full phone UI. If the driver cannot initialize, changing Qt call logic is unlikely to help. If the device works but the service lacks access, investigate permissions and environment. Follow the first failing layer instead of the layer that displays the error.

QUESTION BSP-07. How would you validate a BSP update?

Answer: Record a known-good component set and the proposed changes, then test boot, affected peripherals, application interfaces and recovery on each relevant board variant. Preserve a rollback route and compare repeatable scenarios; one successful startup is not a full regression check.

Example and checks: After changing the platform, repeat the application’s important hardware scenarios even if compilation still passes. Device paths, permissions, timing and media support may have changed. Record the exact image and board. A useful test result says which functions worked on that combination.

QUESTION BSP-08. Which artifacts must stay compatible across the boot chain?

Answer: Boot firmware/bootloader, kernel, DTB, rootfs and required firmware/modules must match the board and supported interfaces. Record the versions actually deployed, not only the source branch. Mixing artifacts from different releases can boot partially and fail later at a peripheral or application boundary.

Example and checks: A new kernel with an old incompatible device tree can fail even when both files exist. Check the bootloader’s actual selection and storage layout. Include the root filesystem and early userspace in compatibility checks. Keep a known working combination available while validating the replacement.

QUESTION BSP-09. When is a device-tree change enough, and when is a driver change needed?

Answer: Device tree can express supported hardware connections and configuration through bindings. A missing behavior in the driver requires driver work; absent electrical support needs hardware attention. Start by identifying which boundary lacks the required capability rather than treating every board issue as a DTS edit.

Example and checks: For example, enabling a camera node does not create missing driver code. Check its binding, resources and supported compatible value first. Match addresses, clocks and GPIO to the actual board. Then inspect the driver’s startup messages before testing the complete application.

QUESTION BSP-10. What is the role of a defconfig or kernel config fragment?

Answer: They provide requested kernel configuration inputs, while Kconfig dependencies determine the resolved configuration. Inspect the final .config and resulting artifacts. A requested option can be disabled by dependencies or built differently than expected, so the fragment alone is not proof of driver availability.

Example and checks: For a kernel option, inspect the final .config after all fragments and dependencies have been processed. The requested setting may be overridden or depend on another option. Confirm whether this vendor recipe supports the fragment workflow. Test the needed behavior on the running kernel afterward.

QUESTION BSP-11. How do built-in drivers, modules and firmware differ?

Answer: Built-in drivers are part of the kernel image; modules are loaded separately and must match the running kernel. Device firmware is another runtime input where required. A driver build can succeed while module packaging, firmware installation or loading fails on the target.

Example and checks: A module must be built for the selected kernel and actually included in the image. Any required firmware must be installed too. Autoload configuration only requests loading; it does not supply those files. Check module load results and kernel messages on the phone.

QUESTION BSP-12. Why keep a serial console during bring-up?

Answer: It provides early boot observations before networking, graphics and application logging are available. Use it to identify the last successful stage and preserve the error context. Console settings must match the board and boot configuration; absence of output is not automatically a dead processor.

Example and checks: The serial console can show a bootloader prompt while the firmware data is transferred through a different interface. Record both the control steps and the actual data path. Do not label the process UART flashing based only on seeing serial output. Use the documented procedure for that board.

QUESTION BSP-13. Why inspect device-tree bindings instead of copying nodes?

Answer: Bindings define property meanings, required resources and valid relationships for a compatible device. A copied node can reference the wrong GPIO, clock, interrupt or address and still look plausible. Check against the exact board and driver support, then validate actual probe and I/O.

Example and checks: For example, enabling a camera node does not create missing driver code. Check its binding, resources and supported compatible value first. Match addresses, clocks and GPIO to the actual board. Then inspect the driver’s startup messages before testing the complete application.

QUESTION BSP-14. How do you confirm which DTB is actually loaded?

Answer: Compare bootloader configuration and boot logs with the running system's device-tree model and properties. The file generated in the build directory may not be the one deployed or selected at boot. Preserve artifact identity while testing a device-tree hypothesis.

Example and checks: Compare the tree used by the running system with the expected board changes. For overlays, confirm that the boot path applies the file, not merely copies it into deployment output. Then check driver binding and behavior. A source edit without a changed running tree cannot fix the device.

QUESTION BSP-15. What is a reasonable bring-up order for a new board?

Answer: Start with the documented power/boot path and early console, then memory, storage/rootfs and essential interfaces before complex media/application scenarios. Coordinate with hardware specialists and validate one boundary at a time. This is a method description, not evidence of personal ownership of a completed bring-up.

Example and checks: Bring up one stage at a time and keep its result repeatable before adding the next. Start with observation and recovery access, then verify storage and the basic system. Add peripheral and application tests afterward. This reduces the number of possible causes when the next change fails.

QUESTION BSP-16. Which user-space assumptions must a BSP change preserve?

Answer: Applications depend on device interfaces, permissions, media formats, library/ABI support and startup behavior. Kernel-internal compatibility is not the whole product contract. Identify consumers and run their scenarios after a driver or hardware-description change, including their failure and restart paths.

Example and checks: After changing the platform, repeat the application’s important hardware scenarios even if compilation still passes. Device paths, permissions, timing and media support may have changed. Record the exact image and board. A useful test result says which functions worked on that combination.

QUESTION BSP-17. How do you separate an application defect from a BSP integration defect?

Answer: Use a minimal test of the expected kernel/device interface and compare the same image/configuration with the application path. If the interface fails independently, investigate driver/board integration. If it works, inspect application configuration, ownership and timing before changing the BSP.

Example and checks: Start with a minimal device check before the full phone UI. If the driver cannot initialize, changing Qt call logic is unlikely to help. If the device works but the service lacks access, investigate permissions and environment. Follow the first failing layer instead of the layer that displays the error.

QUESTION BSP-18. What makes a BSP handoff useful for application engineers?

Answer: Provide compatible image/SDK identifiers, interface expectations, known limitations, reproducible setup and a minimal validation scenario. Include the relevant logs and owners for unresolved boundaries. This lets application engineers test against a defined platform rather than reverse-engineer an undocumented artifact set.

Example and checks: A useful handoff lets another engineer reproduce the supported image and check a basic device function. Include required versions, enabled features and known limits. Describe how to collect startup evidence and recover the board. A directory of binaries alone does not provide that working contract.

QUESTION BSP-19. What should an update and recovery test include?

Answer: Check authenticated artifact selection where supported, compatible persistent-data layout, interruption handling and a known-good recovery path. Test cold boot and the relevant peripheral/application scenarios after both update and rollback. A backup image does not guarantee recovery if boot selection or data migration is incompatible.

Example and checks: Application recovery assumes Linux and the updater can still run. If the bootloader or root filesystem is unusable, an older application directory is not enough. Test that separate failure path through the board’s recovery process. Keep its claims separate from successful rollback of phone application files.

QUESTION BSP-20. What evidence distinguishes BSP consumption from BSP customization?

Answer: Consuming a BSP uses its supported board/image interfaces. Customization is shown by specific changes to machine metadata, boot, kernel, DTB, drivers or firmware integration and their target checks. The exact contribution must be named; one small change does not imply authorship of the whole platform.

Example and checks: For example, adapting a package or service to use an existing BSP is not independent board bring-up. Explain the exact file or interface you changed. Then describe the target evidence that checked it. This gives a stronger answer than either claiming the whole BSP or dismissing integration as trivial.

QUESTION BSP-21. Does any kernel recipe merge .cfg from SRC_URI?

Answer: No. Check provider support and final .config. Configuration dependencies can alter results, and vendor recipes may require a different mechanism.

Example and checks: For a kernel option, inspect the final .config after all fragments and dependencies have been processed. The requested setting may be overridden or depend on another option. Confirm whether this vendor recipe supports the fragment workflow. Test the needed behavior on the running kernel afterward.

QUESTION BSP-22. Does KERNEL_MODULE_AUTOLOAD install the module?

Answer: No. It requests boot loading. Include the actual module package and verify kernel compatibility and successful modprobe on target.

Example and checks: A module must be built for the selected kernel and actually included in the image. Any required firmware must be installed too. Autoload configuration only requests loading; it does not supply those files. Check module load results and kernel messages on the phone.

QUESTION BSP-23. Why can a compatible node fail to create a device?

Answer: It may be disabled, the driver absent, or probe may fail/defer due to clocks, regulators, pinctrl or firmware. Check the live tree and kernel logs.

Example and checks: Compare the tree used by the running system with the expected board changes. For overlays, confirm that the boot path applies the file, not merely copies it into deployment output. Then check driver binding and behavior. A source edit without a changed running tree cannot fix the device.

QUESTION BSP-24. What proves an overlay was applied?

Answer: The boot path applies it, expected nodes/properties appear in the live tree, and driver binding succeeds. A compiled .dtbo alone is not proof.

Example and checks: Compare the tree used by the running system with the expected board changes. For overlays, confirm that the boot path applies the file, not merely copies it into deployment output. Then check driver binding and behavior. A source edit without a changed running tree cannot fix the device.

QUESTION BSP-25. Does application rollback recover a non-booting board?

Answer: Not by itself. The application updater requires a working base system. Boot/rootfs recovery needs the board’s supported flashing or independent recovery path; do not infer it from retaining an older Qt executable.

Example and checks: Application recovery assumes Linux and the updater can still run. If the bootloader or root filesystem is unusable, an older application directory is not enough. Test that separate failure path through the board’s recovery process. Keep its claims separate from successful rollback of phone application files.

QUESTION BSP-26. Does a UART boot console prove UART firmware flashing?

Answer: No. The console may control a bootloader that loads payloads over another interface. Distinguish observation/control from image transport and identify the exact board procedure.

Example and checks: The serial console can show a bootloader prompt while the firmware data is transferred through a different interface. Record both the control steps and the actual data path. Do not label the process UART flashing based only on seeing serial output. Use the documented procedure for that board.

QUESTION BSP-27. What is a DTB, and does building one need a separate recipe?

Answer: DTB means Device Tree Blob: the compiled binary representation of a board's hardware description. The source normally consists of a .dts file and included .dtsi files. It describes such things as memory, buses, GPIO controllers, pin configuration and connected devices. On a typical device-tree-based ARM system the bootloader supplies this description to the kernel. The DTB contains data, not driver code, and is not the kernel or root filesystem.

Example and checks: The usual path is .dts plus included descriptions, kernel build preprocessing and dtc, then a .dtb deployed with the boot artifacts. A separate recipe for each DTB is normally unnecessary: the existing kernel/BSP recipe builds selected trees, commonly controlled through KERNEL_DEVICETREE. Board changes usually belong in a product-layer append or patch to that provider. Standalone device-tree recipes are also possible, depending on the BSP. Finally check which tree the bootloader actually loads; a rebuilt DTB left in the build directory cannot change the running phone.

SECTION 9. SOURCES

Research date: 2026-11-16

- https://docs.nxp.com/bundle/UG10163/page/topics/introduction_001.html
- https://docs.kernel.org/devicetree/usage-model.html
- https://docs.yoctoproject.org/4.0.30/bsp-guide/bsp.html
- https://docs.kernel.org/driver-api/driver-model/binding.html
- https://docs.yoctoproject.org/4.0.30/kernel-dev/common.html
- https://docs.u-boot.org/en/latest/usage/fdt_overlays.html
- https://www.raspberrypi.com/documentation/computers/config_txt.html
- https://docs.u-boot.org/en/latest/usage/cmd/bootm.html
