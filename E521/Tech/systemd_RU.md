systemd

РАЗДЕЛ 1. ТЕХНОЛОГИЯ И ВЕРСИЯ

Категория: Управление сервисами

systemd в embedded Linux; директивы зависят от установленной версии.

РАЗДЕЛ 2. НАЗНАЧЕНИЕ

systemd — менеджер инициализации и сервисов. Он представляет сервисы и другие ресурсы как units и управляет их жизненным циклом.

РАЗДЕЛ 3. ОСНОВНЫЕ ПОНЯТИЯ

Units включают service, socket, mount, device и target. Requires= и Wants= задают зависимости; After= и Before= задают порядок и сами по себе не запускают другой unit. Тип сервиса влияет на момент завершения запуска. Активный target не обязательно означает готовность endpoint или сокета композитора.

Конфигурация unit отделяет зависимости в разделе Unit от параметров процесса в Service и установки в Install. Wants= обычно слабее Requires=, а порядок задаётся независимо.

Сервис может успешно стартовать, но завершиться позднее; проверяйте основной процесс, код выхода, политику перезапуска и журнал, не считая перезапуск исправлением. Окружение и пользователь сервиса могут отличаться от интерактивной оболочки, поэтому команда может работать вручную и не работать при загрузке.

Если конфигурация выглядит противоречивой, проверяйте drop-ins и итоговые свойства. Для графического приложения различайте запуск сервиса и фактическую готовность композитора принимать подключения.

Используйте руководство установленной версии: параметры и значения по умолчанию могут различаться.

РАЗДЕЛ 4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

systemctl status <service> показывает состояние; journalctl -u <service> — журнал; systemctl cat <service> — определения unit и drop-ins. systemctl show показывает итоговые свойства. После изменения unit команда systemctl daemon-reload перечитывает определения. systemd-analyze critical-chain помогает исследовать порядок запуска.

Type=simple не сообщает systemd о завершении внутренней инициализации приложения; Type=notify может сообщать о готовности, если приложение реализует протокол уведомлений. network.target — точка упорядочивания, а не доказательство подключения.

network-online.target может ожидать настройки сети при соответствующих менеджере сети и wait-сервисе, но не гарантирует доступность конкретного удалённого сервера или её сохранение. При изменении сети приложению нужны явные повторы и диагностика.

УПАКОВКА UNIT В YOCTO

Рецепт приложения может использовать inherit systemd, устанавливать phone-ui.service в ${D}${systemd_system_unitdir} и задавать SYSTEMD_SERVICE:${PN} = "phone-ui.service". SYSTEMD_AUTO_ENABLE:${PN} = "enable" явно выбирает включение.

Unit относится к нужному пакету, systemd выбирается как init; включение в образ остаётся отдельным шагом. ExecStart соответствует установленному executable.

Выбираются подходящие Type, User, restart policy и writable state. После поставки образа и reboot проверяются systemctl cat, systemctl status и journalctl -u.

Enablement обеспечивает class вместо вызова systemctl сборочного host в do_install.

ПРИМЕРЫ УПАКОВКИ И ПРОВЕРКИ

Фрагмент рецепта приложения; установка unit описывается отдельно:

```bitbake
inherit systemd
SYSTEMD_SERVICE:${PN} = "phone-ui.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"
```

Проверка на целевом устройстве после установки пакета:

```bash
systemctl cat phone-ui.service
systemctl status phone-ui.service
journalctl -u phone-ui.service
```

РАЗДЕЛ 5. ПРЕИМУЩЕСТВА, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

Декларативные units, зависимости, журналирование и контроль упрощают запуск. Неверные зависимости могут скрыть сбой или задержать загрузку; минимальное устройство может использовать более простую init-систему.

РАЗДЕЛ 6. ОШИБКИ И БЕЗОПАСНОСТЬ

After= не проверяет готовность. Циклический перезапуск может скрывать постоянную ошибку; проверяйте код выхода и логи. Ограничивайте права сервисов и защищайте конфиденциальные данные. Готовность сети и Wayland/Weston зависит от реального поведения сервисов.

РАЗДЕЛ 7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТАХ КАНДИДАТА

До прихода нашей команды существовала базовая заготовка платформы Yocto. Linphone SDK, WebRTC и mediasoup в ней отсутствовали. Наша команда добавила эти компоненты и интегрировала их сборочные зависимости, пакеты и runtime-требования в образ телефона. Мой личный вклад включал приложение/SDK, метаданные BitBake, упаковку, интеграцию образа и проверку на устройстве; интеграция всего стека была командной работой.

SIP-BASED PHONE SOFTWARE: CV указывает systemd и конфигурацию сервисов. Легенда описывает порядок запуска и проверку телефона. Запрос требует embedded Linux и интеграцию образа.

РАЗДЕЛ 8. ВОПРОСЫ НА ИНТЕРВЬЮ

ВОПРОС SYS-01. Запускает ли After= другой unit?

Ответ: Нет. After= задаёт порядок, если оба units участвуют; он не подтягивает другой unit. Wants=/Requires= задают включение. Порядок отличается от прикладной readiness.

ВОПРОС SYS-02. Чем отличаются Requires= и Wants=?

Ответ: Оба подтягивают unit, но Requires= создаёт более сильную связь. Обработка startup-failure зависит и от After=. Wants= позволяет продолжить при отказе зависимости; ни одна директива не проверяет remote-endpoint.

ВОПРОС SYS-03. Что делает daemon-reload?

Ответ: Перечитывает unit-definitions и dependencies. Не перезапускает сервис и не заставляет процесс перечитать app-config. Restart или поддерживаемый service-reload выполняются отдельно.

ВОПРОС SYS-04. Где искать ошибки?

Ответ: Используются systemctl status/journalctl -u, затем effective-unit, exit-status, dependencies/environment. User, paths и startup сравниваются с успешным ручным запуском.

ВОПРОС SYS-05. Доказывает ли network target доступность сервера?

Ответ: Нет. network.target — synchronization-point, а не доступность host. Сервис обрабатывает DNS, route и endpoint-failures даже при правильном startup-order.

ВОПРОС SYS-06. Доказывает ли Type=simple завершение инициализации приложения?

Ответ: Нет. Type=simple считает сервис запущенным до завершения app-initialization. Type=notify даёт readiness при READY=1 программы. Одно объявление type без протокола не делает приложение готовым.

ВОПРОС SYS-07. Гарантирует ли network-online.target доступность SIP-сервера?

Ответ: Нет. Ожидается online-условие network-implementation, а не конкретный SIP-server, DNS или auth. Recovery endpoint требует retries/backoff приложения и наблюдаемой ошибки.

ВОПРОС SYS-08. Чем различаются start и enable?

Ответ: start активирует сейчас, enable создаёт installation-links для последующего включения, обычно boot. Enabled-сервис может быть stopped/failed, active — не enabled. Проверяются оба состояния.

ВОПРОС SYS-09. Как безопасно моделировать dependency сервиса?

Ответ: Определяется required/optional и необходимость ожидания. Inclusion/ordering объединяются осознанно с тестом отсутствия/отказа. Cycle — ошибка дизайна, не повод добавлять After=.

ВОПРОС SYS-10. Когда полезен Type=oneshot?

Ответ: Выполняет конечную setup-команду, завершая startup после успеха. RemainAfterExit сохраняет active без долгоживущего процесса. Это отличается от daemon-supervision; команда должна выдерживать ожидаемый режим вызова.

ВОПРОС SYS-11. Как исследовать restart-loop?

Ответ: Проверяются первый отказ/exit-status до последующего шума. Затем executable, config, dependencies, permissions, Restart=, RestartSec= и start-limits. Restart-policy не заменяет причину.

ВОПРОС SYS-12. Как найти задержку boot?

Ответ: Используются boot-журнал и systemd-analyze timing/critical-chain с dependencies. Active-timestamp не обязательно app-readiness. Проверка повторяется на реальном image/устройстве, а не переносится с desktop.

ВОПРОС SYS-13. Почему After=Weston не гарантирует запуск Qt?

Ответ: Процесс Weston может существовать до готовности socket/runtime-environment. Проверяются socket, XDG_RUNTIME_DIR, WAYLAND_DISPLAY, user и permissions. Нужны readiness-контракт/ограниченный recovery вместо sleep.

ВОПРОС SYS-14. Почему сервису недоступно оборудование?

Ответ: User/groups, device-permissions, sandbox и nodes отличаются от shell. Проверяются effective-unit и driver/device. Запуск всего root скрывает симптом, не объясняя минимальные привилегии.

ВОПРОС SYS-15. Как корректно останавливать сервис?

Ответ: При termination прекращается новая работа, разблокируются loops, join-ятся workers, освобождаются ресурсы в ограниченное время. Проверяются stop-timeout и выход. Резкая остановка портит данные/устройство даже при освобождённой памяти.

ВОПРОС SYS-16. Доказывает ли watchdog здоровье приложения?

Ответ: Только если notifications связаны с реальным прогрессом. Таймер heartbeat при deadlock основной работы скрывает отказ. Liveness, heartbeat и успешные SIP/media — разные наблюдения.

ВОПРОС SYS-17. Как ограничить journal на embedded-устройстве?

Ответ: Осознанно выбираются volatile/persistent и соответствующие limits, например RuntimeMaxUse/SystemMaxUse. Уменьшается шум, проверяется disk-usage. Limits защищают место, но не гарантируют низкий износ flash и сохранность каждого события.

ВОПРОС SYS-18. Что включать в безопасный diagnostics-bundle?

Ответ: Нужны journal/app/SIP-логи и version/context с ограничениями времени/размера. Санитизируются credentials, tokens, identities/private-endpoints. Проверяется сам bundle и download-access; наличие логов не делает раскрытие безопасным.

ВОПРОС SYS-19. Зачем drop-in вместо правки vendor-unit?

Ответ: Drop-in отделяет override от packaged-unit и упрощает обновления. Merged-config проверяется systemctl cat/show. После изменения units нужен daemon-reload и соответствующий restart; не все директивы объединяются как scalar.

ВОПРОС SYS-20. Как сервис связан с образом Yocto?

Ответ: Recipe устанавливает unit/application в staging, packaging включает их, systemd-metadata задаёт поведение сервиса. Image выбирает package. На цели проверяются unit, enablement-policy и boot.

РАЗДЕЛ 9. ИСТОЧНИКИ

Дата проверки: 2026-11-13

- https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html

- https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

- https://wiki.freedesktop.org/www/Software/systemd/NetworkTarget/

- https://www.freedesktop.org/software/systemd/man/latest/journald.conf.html

- https://www.freedesktop.org/software/systemd/man/latest/sd_notify.html

- https://www.freedesktop.org/software/systemd/man/latest/systemd.exec.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html
