systemd

1. TECHNOLOGY AND VERSION
Category: Service management
systemd on embedded Linux; directives depend on the installed version.

2. PURPOSE

systemd is an init and service manager. It represents services and other resources as units and supervises their lifecycle.

3. CORE CONCEPTS

Units include service, socket, mount, device and target types. Requires= and Wants= express dependencies; After= and Before= express ordering and do not alone start another unit. Service type influences when startup is considered complete. An active target does not necessarily mean that an endpoint or compositor socket is ready.

Unit configuration separates relationships in the Unit section from process settings in Service and installation information in Install. Wants= is generally a weaker dependency than Requires=, whereas ordering is specified independently. A service may start correctly but fail later; inspect the main process, exit status, restart policy and journal rather than treating a restart as a fix. Service environment and execution identity can differ from an interactive shell, which explains why a command works manually but not during boot. Examine drop-ins and the final resolved properties when configuration appears inconsistent. For a graphical application, distinguish the service being started from the compositor actually accepting connections. Use the deployed systemd manual because options and defaults vary by version.

4. TYPICAL USAGE

systemctl status <service> shows state; journalctl -u <service> shows its journal; systemctl cat <service> displays unit definitions and drop-ins. systemctl show exposes resolved properties. After editing a unit, systemctl daemon-reload reloads definitions. systemd-analyze critical-chain helps inspect startup ordering.

Type=simple does not notify systemd when the application has completed its own initialization; Type=notify can report readiness when the application implements the notification protocol. network.target is an ordering point, not proof of connectivity. network-online.target can wait for a configured network when the appropriate network manager and wait service are set up, but it does not guarantee that a specific remote server is reachable or remains reachable. Prefer explicit application retry and diagnostics where network conditions can change.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

Declarative units, dependencies, logging and supervision make startup manageable. Incorrect dependencies may hide failures or delay boot; a minimal device may choose a smaller init system.

6. PITFALLS AND SECURITY

After= is not a readiness check. A restart loop can hide a persistent configuration error; inspect exit status and logs. Restrict service privileges and protect sensitive data. Network and Wayland/Weston readiness depend on actual service behavior.

7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: CV names systemd and device-side service configuration. Legend describes startup ordering and phone validation. The request requires embedded Linux and image integration.

8. INTERVIEW QUESTIONS

1. Does After= start the other unit?
No. It orders units when both are scheduled.

2. Requires= versus Wants=?
Both can pull in another unit; Requires= has stronger failure and stopping semantics.

3. What does daemon-reload do?
It reloads unit definitions and rebuilds dependency information.

4. Where do you inspect errors?
Start with unit status and journal logs, then inspect dependencies and environment.

5. Does an active network target prove server access?
No. Connectivity and endpoint readiness require separate checks.

6. Does Type=simple prove that application initialization has finished?
No. For explicit readiness the application can support the notification protocol and a suitable service type.

7. Does network-online.target guarantee the SIP server is reachable?
No. It reflects the network manager's readiness definition, not the availability of a particular remote server.

9. SOURCES

Research date: 2026-11-11
- https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html
- https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html
- https://wiki.freedesktop.org/www/Software/systemd/NetworkTarget/
