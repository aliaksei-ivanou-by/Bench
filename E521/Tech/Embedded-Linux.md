Embedded-Linux

1. TECHNOLOGY AND VERSION
Category: Embedded operating system
Linux on i.MX; kernel version is product-specific.

2. PURPOSE

Embedded Linux combines the Linux kernel and a selected user space for a dedicated device. It supplies process isolation, networking and hardware interfaces while allowing an image tailored to memory and storage constraints.

3. CORE CONCEPTS

A typical boot chain passes control from firmware to a bootloader, which loads the kernel and a hardware description. The kernel initializes hardware and mounts a root filesystem; PID 1 starts user-space services. Device tree describes hardware and configuration; drivers bind to compatible devices. Actual boot stages differ by SoC and product. User-space applications access device files and system services through kernel interfaces.

A service can fail at several different boundaries: the bootloader may load the wrong artifact, the kernel may fail to probe a device, the service may lack a library or permission, or the application may mishandle a runtime event. Start with the observed symptom and identify the earliest failing layer using the boot log, kernel messages and service logs. Confirm architecture and shared-library availability before assuming a C++ defect. The kernel and user-space ABI, device nodes, permissions and firmware are part of the delivered system. Real devices also impose startup timing, limited writable storage and recovery requirements. When an issue depends on USB, GPIO, audio or display timing, a desktop-only reproduction cannot establish full target behavior.

4. TYPICAL USAGE

Use dmesg for kernel messages, journalctl for service logs where available, ps for processes and ls -l /dev for device nodes. Check image contents, executable architecture, libraries, service environment, permissions and hardware. Remote gdb/gdbserver can help when supported.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Linux offers a mature ecosystem and networking but its size and ordinary scheduling may not suit a very small or hard-real-time device. An RTOS can suit strict timing and smaller footprints. PREEMPT_RT and hardware need separate evaluation; hard-real-time guarantees cannot be assumed.

6. PITFALLS AND SECURITY

A missing driver, wrong device tree, absent firmware or incorrect permissions can look like an application failure. Storage wear, power loss during updates, network loss and insufficient memory affect reliability. Apply least privilege, protect credentials and reproduce on hardware when peripherals or timing matter.

7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: CV names embedded Linux, Qt and i.MX. Legend describes application, services and phone diagnostics. The request asks for deep embedded Linux; Responsibilities distinguishes integration from independent kernel ownership.

8. INTERVIEW QUESTIONS

1. What does PID 1 do?
It starts and manages user-space services according to the init system.

2. What is the root filesystem?
The filesystem containing user-space files available as the root of the running system.

3. What is device tree?
A hardware description passed to the kernel, typically for hardware not automatically discoverable.

4. Is hard real time guaranteed?
No. Timing depends on configuration, workload, drivers and hardware.

5. Why test on target?
Hardware, boot order, drivers and resources differ from a desktop.

9. SOURCES

Research date: 2026-11-11
- https://docs.kernel.org/admin-guide/init.html
- https://docs.kernel.org/devicetree/usage-model.html
