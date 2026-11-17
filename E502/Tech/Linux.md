Linux

1. CATEGORY AND VERSION
Category: Operating system and systems programming
Version: The CV and request name Linux; exact kernel versions for the projects are not established.

2. PURPOSE

Linux provides processes, virtual memory, scheduling, filesystems, networking and device interfaces. A storage developer needs to connect application behavior with the kernel, filesystem and devices without assuming every latency or memory problem is a kernel defect.

3. INTERNALS AND DESIGN

A process has a virtual address space; page tables map virtual pages to physical memory as needed. Virtual address space, resident memory and total machine memory are different quantities. Page faults can occur for normal demand paging as well as other reasons. Anonymous memory and file-backed pages have different roles; memory pressure and reclaim can influence latency. Numbers must be interpreted with the kernel and container limits in context.

Threads in a process share address-space resources but have their own execution state and stacks. Locks protect shared invariants but contention can reduce throughput or create deadlocks. A high-CPU thread, a thread waiting on a lock and a thread blocked on I/O require different investigation. Match debug symbols to the binary and understand whether observation pauses the process.

Buffered file I/O generally uses the page cache; dirty data may be written back later. A successful write call is not automatically a guarantee of persistence after power loss. Synchronization operations such as fsync have specific semantics and errors; actual guarantees depend on the filesystem and storage stack. Direct I/O, asynchronous operations and networking need their own interface and alignment rules rather than a blanket assumption about bypassing every cache.

4. TYPICAL USAGE AND DIAGNOSIS

For high CPU and slow storage, define the affected process, workload and time window. Inspect process and per-thread CPU, memory trend, thread states, kernel and application logs, device latency and utilization, network and cluster recovery. Compare an affected host or OSD with peers. Sampling profiling may reveal hot paths with bounded overhead, while tracing, verbose logs, Valgrind and debugger attachment can affect timing or stop execution. Use operationally approved procedures and a test environment for intrusive work.

For a C++ failure, use matching executable and symbols, logs and available core dumps. A debugger can show thread stacks and lock wait locations; that is one observation, not proof of a race or deadlock. Verify an identified hypothesis against representative tests and observe errors, tail latency and throughput before and after under comparable load.

5. STRENGTHS AND LIMITATIONS

Linux offers mature process isolation, networking, instrumentation and device support. Performance and durability depend on hardware, configuration and workload; no single diagnostic tool or metric provides the full cause. Sampling and trace tools have different overhead and visibility.

6. RISKS AND FAILURE MODES

Avoid unbounded allocation, descriptor leaks, unsynchronized shared state and assumptions about write completion. Profiling and logging can change the observed behavior and expose sensitive data. Use least privilege and avoid drawing production conclusions from an unmatched test environment.

7. USE IN THE CANDIDATE’S PROJECTS

The E502 CV names Linux, POSIX streaming I/O and C/C++ work. The Legend describes archive ingestion and phone integration; Responsibilities reconciles those claims with Summary. The request asks for Linux I/O, memory and threading. This file is theory and does not establish kernel, Ceph OSD or storage-tuning experience.

Request relationship: item 17; low-level debugging in item 3.

8. INTERVIEW QUESTIONS

1. Virtual memory versus resident memory?
Virtual memory is an address-space view; resident memory is the portion currently resident in physical RAM.

2. Is every page fault an error?
No. Some faults are expected during normal memory mapping and demand paging.

3. What do threads in a process share?
They share the process address space and resources while retaining individual execution state and stacks.

4. Is a high CPU usage proof of a memory leak?
No. CPU usage and memory growth require separate evidence and hypotheses.

5. What does the page cache do?
It caches file-backed pages and participates in buffered reads and writes.

6. Does a successful write guarantee durability?
Not by itself; synchronization and the complete storage stack determine persistence guarantees.

7. Why inspect individual threads?
One busy or blocked thread can explain behavior hidden in an aggregate process metric.

8. Is profiling always more intrusive than logging?
No. Sampling settings and logging volume determine their overhead; measure the impact.

9. SOURCES

Research date: 2026-11-17
- https://docs.kernel.org/admin-guide/mm/concepts.html
- https://man7.org/linux/man-pages/man7/pthreads.7.html
- https://man7.org/linux/man-pages/man2/fsync.2.html
