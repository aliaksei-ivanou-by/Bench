Embedded-Linux

SECTION 1. TECHNOLOGY AND VERSION

Category: Embedded operating system

Linux on i.MX; kernel version is product-specific.

SECTION 2. PURPOSE

Embedded Linux combines the Linux kernel and a selected user space for a dedicated device. It supplies process isolation, networking and hardware interfaces while allowing an image tailored to memory and storage constraints.

SECTION 3. CORE CONCEPTS

A typical boot chain passes control from firmware to a bootloader, which loads the kernel and a hardware description. The kernel initializes hardware and mounts a root filesystem; PID 1 starts user-space services.

Device tree describes hardware and configuration; drivers bind to compatible devices. Actual boot stages differ by SoC and product.

User-space applications access device files and system services through kernel interfaces.

A service can fail at several different boundaries: the bootloader may load the wrong artifact, the kernel may fail to probe a device, the service may lack a library or permission, or the application may mishandle a runtime event. Start with the observed symptom and identify the earliest failing layer using the boot log, kernel messages and service logs.

Confirm architecture and shared-library availability before assuming a C++ defect. The kernel and user-space ABI, device nodes, permissions and firmware are part of the delivered system.

Real devices also impose startup timing, limited writable storage and recovery requirements. When an issue depends on USB, GPIO, audio or display timing, a desktop-only reproduction cannot establish full target behavior.

SECTION 4. TYPICAL USAGE

Use dmesg for kernel messages, journalctl for service logs where available, ps for processes and ls -l /dev for device nodes. Check image contents, executable architecture, libraries, service environment, permissions and hardware. Remote gdb/gdbserver can help when supported.

For a process that runs interactively but fails at boot, compare the executable, working directory, user, environment, available libraries and dependent services. For missing hardware, inspect kernel messages and driver binding before debugging the application.

For cross-debugging, use target-compatible symbols and record the deployed binary version; a mismatched executable or debug symbols can make a backtrace misleading. These are general diagnostic techniques, not a claim that each occurred on the phone.

BOOT, CROSS-DEVELOPMENT AND UPDATES

A common ARM sequence is BootROM, optional SPL/early firmware, U-Boot, kernel plus DTB and optional initramfs, then PID 1 such as systemd or sysvinit. It varies by SoC/boot chain. Initramfs may locate/unlock the real root and switch to it. Serial logs identify the first failing stage.

The final command line is visible in /proc/cmdline. Inputs can include U-Boot bootargs, boot configuration or chosen/bootargs in device tree; CONFIG_CMDLINE behavior depends on architecture/configuration.

Raspberry Pi cmdline.txt is platform-specific. console= chooses a console, root= identifies the root device, rootwait waits for discovery, init= overrides the normal init executable and loglevel= controls console verbosity.

Names and identifiers depend on the board.

Generate a toolchain with bitbake core-image-minimal -c populate_sdk, install it and source its matching environment-setup-* script in a fresh shell. An SDK with CMake support supplies a toolchain file, commonly $OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake.

Use a fresh CMake build directory to avoid host cache settings; check compiler, sysroot and target ABI. External SDK development does not replace maintaining the recipe.

Use target gdbserver and matching cross-GDB with the same executable, symbols and target sysroot. strace follows syscalls, perf profiles where kernel events/permissions allow, and Valgrind diagnoses supported memory behavior with overhead and architecture limitations. Add tools/symbols to a development image deliberately; core-image-minimal need not contain them.

Userspace uses kernel interfaces: /dev and ioctl, sysfs, GPIO character devices through libgpiod, i2c-dev, spidev and V4L2. mmap can map driver-managed buffers but does not remove ownership, cache-coherence or DMA-synchronization requirements.

Prefer existing subsystem drivers where appropriate. libgpiod APIs vary by version; old sysfs GPIO is deprecated.

Check permissions and failures on target.

SWUpdate provides configurable update handlers, RAUC manages signed bundles and slot/boot integration, and Mender combines device updating with deployment management. Select product-compatible releases rather than assuming current versions fit Kirkstone.

For A/B, write/verify the inactive slot, switch boot selection, mark good after health checks and bound retries with recovery. Shared data migrations can obstruct rollback.

Read-only rootfs needs writable state/log locations. Secure boot authenticates the boot chain; update signatures and rollback policy are separate controls, not automatic results of A/B.

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Linux offers a mature ecosystem and networking but its size and ordinary scheduling may not suit a very small or hard-real-time device. An RTOS can suit strict timing and smaller footprints. PREEMPT_RT and hardware need separate evaluation; hard-real-time guarantees cannot be assumed.

SECTION 6. PITFALLS AND SECURITY

A missing driver, wrong device tree, absent firmware or incorrect permissions can look like an application failure. Storage wear, power loss during updates, network loss and insufficient memory affect reliability. Apply least privilege, protect credentials and reproduce on hardware when peripherals or timing matter.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: CV names embedded Linux, Qt and i.MX. Legend describes application, services and phone diagnostics. The request asks for deep embedded Linux; Responsibilities distinguishes integration from independent kernel ownership.

SECTION 8. INTERVIEW QUESTIONS

QUESTION EL-01. What does PID 1 do?

Answer: PID 1 is the first user-space process and has special lifecycle and orphan-child reaping responsibilities. The chosen init system starts/manages services and shutdown. A running PID 1 does not establish readiness of every application or hardware-dependent service.

QUESTION EL-02. What is the root filesystem?

Answer: It is the filesystem mounted as /, containing the runtime programs, libraries and configuration. Additional persistent or volatile filesystems may be mounted beneath it. Its contents and writability must match application expectations, not only allow the kernel to boot.

QUESTION EL-03. What is device tree?

Answer: Device tree describes non-discoverable hardware and its relationships to the kernel: buses, addresses, interrupts, GPIO and related resources. It does not implement a driver. The loaded DTB, driver bindings and physical board must agree.

QUESTION EL-04. Is hard real time guaranteed?

Answer: No. Ordinary Linux configuration does not promise hard deadlines. Scheduling policy, preemption, interrupt behavior, drivers and workload affect latency. Real-time requirements need measured worst-case behavior under representative stress, not only a low average latency.

QUESTION EL-05. Why test on target?

Answer: The target has the actual boot chain, drivers, peripheral timing, resources and filesystem. Desktop tests isolate logic but cannot prove camera, GPIO, audio routing or full startup. Use both levels and attribute each result to the level actually checked.

QUESTION EL-06. Why can an application work in a shell but fail as a service?

Answer: Compare user/groups, environment, working directory, resource limits, filesystem access and startup dependencies. Then inspect the service journal and effective configuration. A shell may supply variables or already-ready services that do not exist during boot.

QUESTION EL-07. What is important for a reliable remote backtrace?

Answer: Use the exact executable and debug symbols matching the running firmware/process, the correct architecture and an appropriate remote debugger. Resolve target shared libraries against the right sysroot. A plausible stack from mismatched binaries can be misleading.

QUESTION EL-08. What is the typical embedded Linux boot chain?

Answer: Boot ROM and board firmware/bootloader load the kernel and hardware description, then the kernel mounts a root filesystem and starts user space. Exact stages depend on the board. Identify the first missing milestone before blaming the application.

QUESTION EL-09. Why can an existing executable report Exec format error or No such file?

Answer: Check architecture, ABI and the ELF interpreter as well as the file itself. A missing dynamic loader can produce a missing-file symptom even when the executable exists. Inspect the ELF metadata and deployed loader before changing application logic.

QUESTION EL-10. How do you diagnose a missing shared library?

Answer: Inspect the executable's required libraries and loader search configuration, then compare the deployed files with the intended sysroot/packages. Architecture and SONAME compatibility matter, not only a matching filename. Avoid treating a temporary LD_LIBRARY_PATH workaround as a complete packaging fix.

QUESTION EL-11. What do processes and threads share?

Answer: Threads in a process share address space and many process resources, but have separate execution state and stacks. This enables cheap sharing and also races. A mutex protects a defined invariant; merely moving work to another thread does not establish safe ownership.

QUESTION EL-12. How do you distinguish a deadlock from slow work?

Answer: Inspect thread stacks, wait states, resource ownership and progress over time. A fixed wait cycle differs from a long I/O operation or CPU-bound computation. Preserve the triggering sequence and avoid adding sleeps that merely change the timing.

QUESTION EL-13. How do you make a worker thread stop predictably?

Answer: Define who requests stop, how blocking operations wake and who joins the thread. Release locks before callbacks or waits that may re-enter the owner. Validate repeated startup/shutdown and failure during initialization; cleanup must not depend on the UI remaining alive.

QUESTION EL-14. What is important when combining QThread and device events?

Answer: A QThread object normally lives in its creator thread, while work runs in the managed thread. Use explicit worker affinity and queued delivery for cross-thread state. The GUI should consume events without blocking, and request/buffer lifetime must extend through delivery.

QUESTION EL-15. How would you handle noisy GPIO edge events?

Answer: Check line identity, active polarity, electrical assumptions and whether event timestamps/order match the physical input. Distinguish bounce from software duplication before adding debounce. A handset edge should become a controlled state transition, with shutdown and event-source cleanup explicitly handled.

QUESTION EL-16. Does rising RSS prove a memory leak?

Answer: No. Allocator retention, caches, mappings and workload growth can increase RSS. Compare repeated equivalent scenarios, object/resource lifetime and memory diagnostics. A leak means allocations outlive their intended owners or become unreachable without release; one larger memory sample does not establish that.

QUESTION EL-17. How should persistent configuration survive interrupted writes?

Answer: Define the required crash-consistency contract, including how partial files are detected and replaced. A common file strategy writes a complete temporary representation and atomically replaces the visible file, with appropriate synchronization when durability is required. Validate recovery after interruption rather than assuming close means power-loss safety.

QUESTION EL-18. What changes with a read-only root filesystem?

Answer: Every writer needs a deliberate writable or volatile path: application state, logs, caches and update metadata. Service startup must create required directories with correct ownership. Validate reboot persistence separately from runtime writability and avoid silently losing required configuration.

QUESTION EL-19. How do you investigate permission failures without running everything as root?

Answer: Inspect the service user, groups, filesystem/device permissions and applicable security/sandbox policy. Identify the minimum missing access at the failing operation. A root test can localize a permission hypothesis, but permanent excess privilege increases impact and hides the intended contract.

QUESTION EL-20. Which checks belong in unit, integration and target tests?

Answer: Pure state/conversion rules can be checked in unit tests; component contracts need integration scenarios. Boot, physical GPIO, camera/audio and image contents require the target or an appropriate hardware setup. Passing one level cannot be used to claim coverage of the others.

QUESTION EL-21. Does rootwait repair a root filesystem failure?

Answer: It waits for device discovery; it cannot fix a missing driver, wrong partition or unsupported filesystem. Identify the failing boot stage and root= value first.

QUESTION EL-22. Why can an SDK-built binary fail on target?

Answer: Architecture, loader, libc/C++ ABI or libraries may differ. Use the matching SDK environment and a fresh CMake build directory, and inspect actual dependencies.

QUESTION EL-23. How do strace, perf, Valgrind and GDB differ?

Answer: strace traces syscalls, perf samples performance, Valgrind checks supported memory behavior, and GDB inspects process state/control flow. Availability and overhead differ.

QUESTION EL-24. Does A/B guarantee secure, reversible upgrades?

Answer: No. Require verified artifacts, boot selection, health confirmation, bounded retries and recovery. Data migrations and anti-rollback policy can restrict rollback; secure boot needs its own trust chain.

SECTION 9. SOURCES

Research date: 2026-11-13

- https://docs.kernel.org/admin-guide/init.html

- https://docs.kernel.org/devicetree/usage-model.html

- https://doc.qt.io/archives/qt-5.15/qthread.html

- https://docs.kernel.org/userspace-api/gpio/chardev.html

- https://sourceware.org/gdb/current/onlinedocs/gdb.html/Remote-Debugging.html

- https://docs.kernel.org/admin-guide/kernel-parameters.html

- https://docs.yoctoproject.org/4.0.30/sdk-manual/using.html

- https://docs.kernel.org/driver-api/gpio/using-gpio.html

- https://rauc.readthedocs.io/en/latest/basic.html

- https://sbabic.github.io/swupdate/swupdate.html

- https://docs.mender.io/overview/introduction
