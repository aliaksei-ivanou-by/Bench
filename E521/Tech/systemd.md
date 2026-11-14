systemd

SECTION 1. TECHNOLOGY AND VERSION

Category: Service management

systemd on embedded Linux; directives depend on the installed version.

SECTION 2. PURPOSE

Systemd starts and supervises services. It describes services and other system resources as units and manages their start, stop and dependencies.

SECTION 3. CORE CONCEPTS

- Units describe services, sockets, mounts, devices and targets. A target groups related units.
- Wants= and Requires= add dependencies. After= and Before= set order; they do not start another unit on their own.
- The service Type determines when systemd considers startup complete. A started process may still be initializing.
- A service can have a different user, working directory and environment from a terminal session. This can explain why manual startup works but boot startup fails.
- Inspect the exit status and journal before changing the restart policy. Repeating a failed launch does not fix its cause.
- Drop-in files can change unit settings. Check the combined result with systemctl cat or systemctl show.
- A running network target or compositor service does not prove that a particular server or display socket is ready.

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

PHONE DIAGNOSTICS AND HEALTH CONFIRMATION

- QLoggingCategory filters application categories; it does not by itself guarantee journal delivery or secret removal. Configure the logging sink/service stdout/stderr and include category/session context in the emitted message.
- SystemMaxUse/SystemKeepFree govern persistent journal storage; RuntimeMaxUse governs volatile storage. RateLimitIntervalSec/RateLimitBurst and category verbosity address message volume. Storage bounds do not prove low cumulative flash writes.
- Bound support bundles by time and size. Remove SIP credentials, authorization material, private keys and sensitive configuration, including copies in SDK traces. Missing logs must remain visible as partial collection.
- For update confirmation, check local service stability and SDK initialization; a remote PBX outage is not alone a reason to roll back.

Target inspection examples:

```bash
journalctl --disk-usage
journalctl -u phone-ui.service --since "10 minutes ago" --no-pager
systemctl show phone-ui.service -p MainPID -p NRestarts -p Result
```

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Declarative units, dependencies, logging and supervision make startup manageable. Incorrect dependencies may hide failures or delay boot; a minimal device may choose a smaller init system.

SECTION 6. PITFALLS AND SECURITY

After= is not a readiness check. A restart loop can hide a persistent configuration error; inspect exit status and logs. Restrict service privileges and protect sensitive data. Network and Wayland/Weston readiness depend on actual service behavior.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

Before our team joined, there was a basic Yocto platform skeleton. It did not include Linphone SDK, WebRTC or mediasoup. Our team added those components to the phone image, including their build dependencies, packages and the settings needed to run them. My personal contribution covered application/SDK work, BitBake metadata, packaging, image integration and testing on the device; the stack integration was a team effort.

SIP-BASED PHONE SOFTWARE: CV names systemd and device-side service configuration. Legend describes startup ordering and phone validation. The request requires embedded Linux and image integration.

SECTION 8. INTERVIEW QUESTIONS

QUESTION SYS-01. Does After= start the other unit?

Answer: No. After= establishes ordering if both units participate in the transaction; it does not pull the other unit in. Requirement dependencies such as Wants= or Requires= decide inclusion. Ordering is still different from application-specific readiness.

Example and checks: For the phone, decide whether the application merely starts after another service or must require it too. Those are separate settings. Then inspect what happens when the dependency fails. A dependency declaration is useful only if its failure behavior matches the product requirement.

QUESTION SYS-02. Requires= versus Wants=?

Answer: Both can pull another unit into activation, but Requires= creates a stronger requirement relationship. Startup failure handling also depends on ordering such as After=. Wants= allows the requesting unit to continue when the wanted unit fails; neither directive alone expresses a remote endpoint health check.

Example and checks: For the phone, decide whether the application merely starts after another service or must require it too. Those are separate settings. Then inspect what happens when the dependency fails. A dependency declaration is useful only if its failure behavior matches the product requirement.

QUESTION SYS-03. What does daemon-reload do?

Answer: It rereads unit definitions and rebuilds dependency information. It does not restart a running service or make the process reread its application configuration. Restart or a supported service reload is a separate action.

Example and checks: For example, changing a unit file does not alter the process that is already running. Reload systemd’s definitions and apply the required restart or supported reload separately. Inspect the combined unit and drop-ins afterward. This avoids debugging an old process against a newly edited file.

QUESTION SYS-04. Where do you inspect errors?

Answer: Use systemctl status and journalctl -u for the failing unit, then inspect the effective unit, exit status, dependencies and environment. Compare the service user, paths and startup conditions with a successful manual launch.

Example and checks: If the Qt application repeatedly exits, inspect its first failure before the restart messages dominate the journal. Compare the executable, settings and service environment. Limit repeated starts while investigating. A successful automatic restart does not prove the original defect is gone.

QUESTION SYS-05. Does an active network target prove server access?

Answer: No. network.target is a synchronization point, not a statement that a particular host is reachable. A service must handle DNS, route and endpoint failures at runtime even when startup ordering is correct.

Example and checks: A phone can have an address while its configured PBX is unreachable. Treat initial network setup and later server availability separately. Let the application report registration state and retry as designed. Otherwise an unrelated server outage may be mistaken for a boot failure.

QUESTION SYS-06. Does Type=simple prove that application initialization has finished?

Answer: No. Type=simple regards the service as started before application initialization is complete. Type=notify can provide explicit readiness when the program sends READY=1. Declaring the type without implementing the protocol does not make the application ready.

Example and checks: Define what local readiness means: settings loaded, required components initialized and the application processing work. A live process alone is weaker evidence. Keep external PBX reachability as a separate status. Then test whether a hung component can still produce an apparently healthy heartbeat.

QUESTION SYS-07. Does network-online.target guarantee the SIP server is reachable?

Answer: No. It waits for the network implementation's configured online condition, not for a specific SIP server, DNS result or authentication exchange. Endpoint recovery still needs application retries/backoff and observable error handling.

Example and checks: A phone can have an address while its configured PBX is unreachable. Treat initial network setup and later server availability separately. Let the application report registration state and retry as designed. Otherwise an unrelated server outage may be mistaken for a boot failure.

QUESTION SYS-08. How do start and enable differ?

Answer: start activates a unit now; enable creates the configured installation links so it can be pulled in later, commonly during boot. An enabled service can be stopped or failed, and an active service need not be enabled. Check both states.

Example and checks: After building the image, inspect that the unit and executable are both in the selected package. Confirm the intended enablement policy and boot the phone. Test a fresh boot rather than relying on a manually started service. That checks packaging and startup together.

QUESTION SYS-09. How do you model a service dependency safely?

Answer: Identify whether the dependency is required or optional and whether startup must wait for it. Combine inclusion and ordering deliberately, then test dependency absence and failure. A dependency cycle is a design error, not something to fix by adding more After= lines.

Example and checks: For the phone, decide whether the application merely starts after another service or must require it too. Those are separate settings. Then inspect what happens when the dependency fails. A dependency declaration is useful only if its failure behavior matches the product requirement.

QUESTION SYS-10. When is Type=oneshot useful?

Answer: It runs a finite setup action and considers startup finished after the command exits successfully. RemainAfterExit can keep its unit active without a long-running process. This is different from supervising a daemon, and the command must be safe for its expected invocation pattern.

Example and checks: A one-time preparation task might create required directories or validate a local file before the application starts. It should return failure when preparation fails. Decide whether its completed state must remain active for dependency purposes. Do not hide a long-running background process inside a oneshot command.

QUESTION SYS-11. How do you investigate a restart loop?

Answer: Inspect the first failure and exit status before later restart noise. Check executable, configuration, dependencies and permissions, then review Restart=, RestartSec= and start limits. Automatic restart is recovery policy, not a substitute for diagnosing the initial fault.

Example and checks: If the Qt application repeatedly exits, inspect its first failure before the restart messages dominate the journal. Compare the executable, settings and service environment. Limit repeated starts while investigating. A successful automatic restart does not prove the original defect is gone.

QUESTION SYS-12. How can you find a boot delay?

Answer: Use boot journals and systemd-analyze timing or critical-chain information, then correlate the slow unit with its dependencies. A unit's active timestamp is not necessarily useful application readiness. Repeat on the actual image and device rather than extrapolating from a desktop.

Example and checks: Follow the chain leading to the service the user is waiting for. A long-running service outside that chain may not delay the phone UI. Match timing with journal messages and readiness checks. Change the actual wait condition rather than removing dependencies blindly.

QUESTION SYS-13. Why can ordering after Weston still leave a Qt application unable to start?

Answer: Weston's process may exist before the needed display socket and runtime environment are usable. Check the actual socket, XDG_RUNTIME_DIR, WAYLAND_DISPLAY, service user and permissions. Use an explicit readiness contract or bounded recovery, rather than an arbitrary sleep.

Example and checks: For example, Weston may have started but the application may lack its socket path or permissions. Compare the service user and display-related environment with a working launch. Check device access separately. Avoid granting broad privileges just to make one startup symptom disappear.

QUESTION SYS-14. Why might a service lack hardware access?

Answer: Its user/groups, device permissions, sandbox settings or available device nodes can differ from an interactive shell. Check the effective unit and driver/device state. Running everything as root may hide the symptom but does not explain or minimize the required privileges.

Example and checks: For example, Weston may have started but the application may lack its socket path or permissions. Compare the service user and display-related environment with a working launch. Check device access separately. Avoid granting broad privileges just to make one startup symptom disappear.

QUESTION SYS-15. How should a service stop cleanly?

Answer: Handle termination by stopping new work, unblocking event loops, joining worker threads and releasing resources within a bounded time. Check the configured stop timeout and actual exit behavior. Abrupt termination can leave data or external device state inconsistent even when memory is reclaimed.

Example and checks: The phone application should stop accepting new work, finish or cancel outstanding work and release hardware safely. Worker waits must be able to finish. Test stopping during a call transition and while idle. Check the result before relying on systemd’s final timeout or forced termination.

QUESTION SYS-16. Does a systemd watchdog prove application health?

Answer: Only if the application sends watchdog notifications based on meaningful progress. A timer that sends notifications while the actual work is deadlocked can mask failure. Process liveness, watchdog heartbeat and successful SIP/media operations are different observations.

Example and checks: Define what local readiness means: settings loaded, required components initialized and the application processing work. A live process alone is weaker evidence. Keep external PBX reachability as a separate status. Then test whether a hung component can still produce an apparently healthy heartbeat.

QUESTION SYS-17. How do you limit journal storage on an embedded device?

Answer: Choose volatile or persistent storage deliberately and configure the corresponding capacity/retention limits, such as RuntimeMaxUse or SystemMaxUse. Reduce noisy logging and inspect disk usage. Capacity limits help protect space but do not by themselves guarantee low flash wear or preserve every diagnostic event.

Example and checks: For a phone, choose which faults need logs after reboot and how much storage they may occupy. Then control category verbosity and message rate. Check actual disk use and behavior under repeated errors. A small retained journal can still generate many flash writes over time.

QUESTION SYS-18. What belongs in a safe diagnostic bundle?

Answer: Collect relevant journal/application/SIP logs and version/context information with a bounded time/size range. Sanitize credentials, tokens, account identities and private endpoints where required. Check the produced bundle itself and restrict download access; log availability does not make disclosure safe.

Example and checks: Build a bundle for a known incident and inspect the resulting archive, not only the collector code. Check application logs, SDK traces and copied configuration for secrets. Missing files should be reported as partial collection. The support user needs enough context to correlate events without receiving credentials.

QUESTION SYS-19. Why use a drop-in instead of editing a vendor unit?

Answer: A drop-in records a local override separately from the packaged unit and is easier to inspect during updates. Check the merged configuration with systemctl cat or show. Run daemon-reload after unit changes and apply the appropriate restart; do not assume all directives combine like simple scalar values.

Example and checks: For example, changing a unit file does not alter the process that is already running. Reload systemd’s definitions and apply the required restart or supported reload separately. Inspect the combined unit and drop-ins afterward. This avoids debugging an old process against a newly edited file.

QUESTION SYS-20. How is a service connected to a Yocto image?

Answer: The recipe installs the unit and application into the staged filesystem, packaging includes them, and systemd integration metadata defines the relevant service behavior. The image must select the package. Verify unit presence, enablement policy and boot behavior on the deployed target.

Example and checks: After building the image, inspect that the unit and executable are both in the selected package. Confirm the intended enablement policy and boot the phone. Test a fresh boot rather than relying on a manually started service. That checks packaging and startup together.

QUESTION SYS-21. Do journal size limits alone protect flash endurance?

Answer: They bound retained storage, not cumulative writes. Control verbose categories and message rates, choose persistent/volatile policy deliberately and measure relevant behavior. Rotation does not mean that only one journal-sized amount was ever written.

Example and checks: For a phone, choose which faults need logs after reboot and how much storage they may occupy. Then control category verbosity and message rate. Check actual disk use and behavior under repeated errors. A small retained journal can still generate many flash writes over time.

QUESTION SYS-22. What should confirm a phone update when the PBX is offline?

Answer: Local application/service stability, readable configuration and SDK initialization can establish local health. Report external registration availability separately. Define a bounded confirmation policy so an unrelated network outage does not cause an endless rollback loop.

Example and checks: Define what local readiness means: settings loaded, required components initialized and the application processing work. A live process alone is weaker evidence. Keep external PBX reachability as a separate status. Then test whether a hung component can still produce an apparently healthy heartbeat.

SECTION 9. SOURCES

Research date: 2026-11-14

- https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html

- https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

- https://wiki.freedesktop.org/www/Software/systemd/NetworkTarget/

- https://www.freedesktop.org/software/systemd/man/latest/journald.conf.html

- https://www.freedesktop.org/software/systemd/man/latest/sd_notify.html

- https://www.freedesktop.org/software/systemd/man/latest/systemd.exec.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html
- https://www.freedesktop.org/software/systemd/man/249/journald.conf.html
- https://doc.qt.io/archives/qt-5.15/qloggingcategory.html
