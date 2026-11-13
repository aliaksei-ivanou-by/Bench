systemd

SECTION 1. TECHNOLOGY AND VERSION

Category: Service management

systemd on embedded Linux; directives depend on the installed version.

SECTION 2. PURPOSE

systemd is an init and service manager. It represents services and other resources as units and supervises their lifecycle.

SECTION 3. CORE CONCEPTS

Units include service, socket, mount, device and target types. Requires= and Wants= express dependencies; After= and Before= express ordering and do not alone start another unit. Service type influences when startup is considered complete. An active target does not necessarily mean that an endpoint or compositor socket is ready.

Unit configuration separates relationships in the Unit section from process settings in Service and installation information in Install. Wants= is generally a weaker dependency than Requires=, whereas ordering is specified independently.

A service may start correctly but fail later; inspect the main process, exit status, restart policy and journal rather than treating a restart as a fix. Service environment and execution identity can differ from an interactive shell, which explains why a command works manually but not during boot.

Examine drop-ins and the final resolved properties when configuration appears inconsistent. For a graphical application, distinguish the service being started from the compositor actually accepting connections.

Use the deployed systemd manual because options and defaults vary by version.

SECTION 4. TYPICAL USAGE

systemctl status <service> shows state; journalctl -u <service> shows its journal; systemctl cat <service> displays unit definitions and drop-ins. systemctl show exposes resolved properties. After editing a unit, systemctl daemon-reload reloads definitions. systemd-analyze critical-chain helps inspect startup ordering.

Type=simple does not notify systemd when the application has completed its own initialization; Type=notify can report readiness when the application implements the notification protocol. network.target is an ordering point, not proof of connectivity.

network-online.target can wait for a configured network when the appropriate network manager and wait service are set up, but it does not guarantee that a specific remote server is reachable or remains reachable. Prefer explicit application retry and diagnostics where network conditions can change.

YOCTO UNIT PACKAGING

An application recipe can inherit systemd, install phone-ui.service under ${D}${systemd_system_unitdir} and set SYSTEMD_SERVICE:${PN} = "phone-ui.service". SYSTEMD_AUTO_ENABLE:${PN} = "enable" explicitly selects enablement.

Assign the unit to the intended package and ensure systemd is selected as init; image inclusion remains separate. ExecStart must match the installed executable.

Choose suitable Type, User, restart policy and writable state. After image deployment and reboot inspect systemctl cat, systemctl status and journalctl -u.

Let the class handle enablement rather than calling the build host's systemctl in do_install.

PACKAGING AND VALIDATION EXAMPLES

Application recipe fragment; unit installation is defined separately:

```bitbake
inherit systemd
SYSTEMD_SERVICE:${PN} = "phone-ui.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"
```

Check on the target device after package installation:

```bash
systemctl cat phone-ui.service
systemctl status phone-ui.service
journalctl -u phone-ui.service
```

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Declarative units, dependencies, logging and supervision make startup manageable. Incorrect dependencies may hide failures or delay boot; a minimal device may choose a smaller init system.

SECTION 6. PITFALLS AND SECURITY

After= is not a readiness check. A restart loop can hide a persistent configuration error; inspect exit status and logs. Restrict service privileges and protect sensitive data. Network and Wayland/Weston readiness depend on actual service behavior.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

Before our team joined, there was a basic Yocto platform skeleton. It did not include Linphone SDK, WebRTC or mediasoup. Our team added those components and integrated their build dependencies, packages and runtime requirements into the phone image. My personal contribution covered application/SDK work, BitBake metadata, packaging, image integration and target validation; the stack integration was a team effort.

SIP-BASED PHONE SOFTWARE: CV names systemd and device-side service configuration. Legend describes startup ordering and phone validation. The request requires embedded Linux and image integration.

SECTION 8. INTERVIEW QUESTIONS

QUESTION SYS-01. Does After= start the other unit?

Answer: No. After= establishes ordering if both units participate in the transaction; it does not pull the other unit in. Requirement dependencies such as Wants= or Requires= decide inclusion. Ordering is still different from application-specific readiness.

QUESTION SYS-02. Requires= versus Wants=?

Answer: Both can pull another unit into activation, but Requires= creates a stronger requirement relationship. Startup failure handling also depends on ordering such as After=. Wants= allows the requesting unit to continue when the wanted unit fails; neither directive alone expresses a remote endpoint health check.

QUESTION SYS-03. What does daemon-reload do?

Answer: It rereads unit definitions and rebuilds dependency information. It does not restart a running service or make the process reread its application configuration. Restart or a supported service reload is a separate action.

QUESTION SYS-04. Where do you inspect errors?

Answer: Use systemctl status and journalctl -u for the failing unit, then inspect the effective unit, exit status, dependencies and environment. Compare the service user, paths and startup conditions with a successful manual launch.

QUESTION SYS-05. Does an active network target prove server access?

Answer: No. network.target is a synchronization point, not a statement that a particular host is reachable. A service must handle DNS, route and endpoint failures at runtime even when startup ordering is correct.

QUESTION SYS-06. Does Type=simple prove that application initialization has finished?

Answer: No. Type=simple regards the service as started before application initialization is complete. Type=notify can provide explicit readiness when the program sends READY=1. Declaring the type without implementing the protocol does not make the application ready.

QUESTION SYS-07. Does network-online.target guarantee the SIP server is reachable?

Answer: No. It waits for the network implementation's configured online condition, not for a specific SIP server, DNS result or authentication exchange. Endpoint recovery still needs application retries/backoff and observable error handling.

QUESTION SYS-08. How do start and enable differ?

Answer: start activates a unit now; enable creates the configured installation links so it can be pulled in later, commonly during boot. An enabled service can be stopped or failed, and an active service need not be enabled. Check both states.

QUESTION SYS-09. How do you model a service dependency safely?

Answer: Identify whether the dependency is required or optional and whether startup must wait for it. Combine inclusion and ordering deliberately, then test dependency absence and failure. A dependency cycle is a design error, not something to fix by adding more After= lines.

QUESTION SYS-10. When is Type=oneshot useful?

Answer: It runs a finite setup action and considers startup finished after the command exits successfully. RemainAfterExit can keep its unit active without a long-running process. This is different from supervising a daemon, and the command must be safe for its expected invocation pattern.

QUESTION SYS-11. How do you investigate a restart loop?

Answer: Inspect the first failure and exit status before later restart noise. Check executable, configuration, dependencies and permissions, then review Restart=, RestartSec= and start limits. Automatic restart is recovery policy, not a substitute for diagnosing the initial fault.

QUESTION SYS-12. How can you find a boot delay?

Answer: Use boot journals and systemd-analyze timing or critical-chain information, then correlate the slow unit with its dependencies. A unit's active timestamp is not necessarily useful application readiness. Repeat on the actual image and device rather than extrapolating from a desktop.

QUESTION SYS-13. Why can ordering after Weston still leave a Qt application unable to start?

Answer: Weston's process may exist before the needed display socket and runtime environment are usable. Check the actual socket, XDG_RUNTIME_DIR, WAYLAND_DISPLAY, service user and permissions. Use an explicit readiness contract or bounded recovery, rather than an arbitrary sleep.

QUESTION SYS-14. Why might a service lack hardware access?

Answer: Its user/groups, device permissions, sandbox settings or available device nodes can differ from an interactive shell. Check the effective unit and driver/device state. Running everything as root may hide the symptom but does not explain or minimize the required privileges.

QUESTION SYS-15. How should a service stop cleanly?

Answer: Handle termination by stopping new work, unblocking event loops, joining worker threads and releasing resources within a bounded time. Check the configured stop timeout and actual exit behavior. Abrupt termination can leave data or external device state inconsistent even when memory is reclaimed.

QUESTION SYS-16. Does a systemd watchdog prove application health?

Answer: Only if the application sends watchdog notifications based on meaningful progress. A timer that sends notifications while the actual work is deadlocked can mask failure. Process liveness, watchdog heartbeat and successful SIP/media operations are different observations.

QUESTION SYS-17. How do you limit journal storage on an embedded device?

Answer: Choose volatile or persistent storage deliberately and configure the corresponding capacity/retention limits, such as RuntimeMaxUse or SystemMaxUse. Reduce noisy logging and inspect disk usage. Capacity limits help protect space but do not by themselves guarantee low flash wear or preserve every diagnostic event.

QUESTION SYS-18. What belongs in a safe diagnostic bundle?

Answer: Collect relevant journal/application/SIP logs and version/context information with a bounded time/size range. Sanitize credentials, tokens, account identities and private endpoints where required. Check the produced bundle itself and restrict download access; log availability does not make disclosure safe.

QUESTION SYS-19. Why use a drop-in instead of editing a vendor unit?

Answer: A drop-in records a local override separately from the packaged unit and is easier to inspect during updates. Check the merged configuration with systemctl cat or show. Run daemon-reload after unit changes and apply the appropriate restart; do not assume all directives combine like simple scalar values.

QUESTION SYS-20. How is a service connected to a Yocto image?

Answer: The recipe installs the unit and application into the staged filesystem, packaging includes them, and systemd integration metadata defines the relevant service behavior. The image must select the package. Verify unit presence, enablement policy and boot behavior on the deployed target.

SECTION 9. SOURCES

Research date: 2026-11-13

- https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html

- https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

- https://wiki.freedesktop.org/www/Software/systemd/NetworkTarget/

- https://www.freedesktop.org/software/systemd/man/latest/journald.conf.html

- https://www.freedesktop.org/software/systemd/man/latest/sd_notify.html

- https://www.freedesktop.org/software/systemd/man/latest/systemd.exec.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html
