Embedded-Linux

РАЗДЕЛ 1. ТЕХНОЛОГИЯ И ВЕРСИЯ

Категория: Встроенная ОС

Linux на i.MX; версия ядра зависит от продукта.

РАЗДЕЛ 2. НАЗНАЧЕНИЕ

Embedded Linux объединяет ядро Linux и выбранное пользовательское окружение для специализированного устройства. Он обеспечивает изоляцию процессов, сеть и аппаратные интерфейсы и позволяет адаптировать образ к ограничениям памяти и накопителя.

РАЗДЕЛ 3. ОСНОВНЫЕ ПОНЯТИЯ

Типичная загрузка передаёт управление от firmware к загрузчику, который загружает ядро и описание оборудования. Ядро инициализирует оборудование и монтирует корневую файловую систему; PID 1 запускает пользовательские сервисы.

Device tree описывает оборудование и конфигурацию; драйверы связываются с совместимыми устройствами. Этапы зависят от SoC и продукта.

Приложения используют файлы устройств и системные сервисы через интерфейсы ядра.

Сервис может перестать работать на разных границах: загрузчик может выбрать неверный артефакт, ядро — не обнаружить устройство, сервису может не хватать библиотеки или прав, а приложение может неправильно обработать runtime-событие. Начните с наблюдаемого симптома и найдите первый неисправный слой по логам загрузки, сообщениям ядра и журналам сервисов.

До предположения об ошибке C++ проверьте архитектуру и доступность библиотек. ABI ядра и user space, файлы устройств, права и firmware входят в поставляемую систему.

Реальные устройства также ограничивают время запуска, доступный для записи объём и способы восстановления. При проблемах USB, GPIO, аудио или времени работы дисплея проверка только на рабочей станции не подтверждает поведение устройства.

РАЗДЕЛ 4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Используйте dmesg для сообщений ядра, journalctl для логов сервисов при наличии, ps для процессов и ls -l /dev для устройств. Проверяйте состав образа, архитектуру программы, библиотеки, окружение сервиса, права и оборудование. При поддержке помогают удалённые gdb/gdbserver.

Если процесс работает вручную, но не при загрузке, сравните исполняемый файл, рабочий каталог, пользователя, окружение, доступные библиотеки и зависимые сервисы. При отсутствии оборудования изучите сообщения ядра и привязку драйвера до отладки приложения.

Для удалённой отладки используйте совместимые символы и фиксируйте версию установленного бинарного файла; несовпадение программы или символов может сделать стек вызовов ошибочным. Это общие приёмы диагностики, а не утверждение, что каждый случай происходил на телефоне.

ЗАГРУЗКА, КРОСС-РАЗРАБОТКА И ОБНОВЛЕНИЯ

Типичная ARM-последовательность: BootROM, необязательные SPL/early firmware, U-Boot, kernel с DTB и необязательным initramfs, затем PID 1 — systemd или sysvinit. Она зависит от SoC/boot chain. Initramfs может найти/разблокировать настоящий root и переключиться на него. Serial logs определяют первую отказавшую стадию.

Итоговая командная строка видна в /proc/cmdline. Источники могут включать U-Boot bootargs, boot configuration или chosen/bootargs в device tree; поведение CONFIG_CMDLINE зависит от архитектуры/конфигурации.

cmdline.txt у Raspberry Pi — платформенный механизм. console= выбирает консоль, root= определяет root device, rootwait ждёт его обнаружения, init= переопределяет обычный init executable, loglevel= задаёт подробность вывода в консоль.

Имена и идентификаторы зависят от платы.

Toolchain генерируется через bitbake core-image-minimal -c populate_sdk, устанавливается, затем в новом shell выполняется соответствующий environment-setup-* script. SDK с поддержкой CMake предоставляет toolchain file, обычно $OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake.

Новый CMake build directory исключает host cache settings; проверяются compiler, sysroot и target ABI. Разработка через внешний SDK не заменяет сопровождение рецепта.

Используются gdbserver на target и соответствующий cross-GDB с теми же executable, symbols и target sysroot. strace отслеживает syscalls, perf профилирует при доступных kernel events/permissions, Valgrind диагностирует поддерживаемые сценарии памяти с накладными расходами и ограничениями архитектур. Tools/symbols добавляются в development image явно; core-image-minimal не обязан их содержать.

Userspace использует интерфейсы ядра: /dev и ioctl, sysfs, GPIO character devices через libgpiod, i2c-dev, spidev и V4L2. mmap может отображать управляемые драйвером buffers, но не отменяет ownership, cache coherence и DMA synchronization.

Где подходит, предпочтительны существующие subsystem drivers. API libgpiod зависит от версии; старый sysfs GPIO deprecated.

Права и отказы проверяются на target.

SWUpdate предоставляет настраиваемые update handlers, RAUC управляет подписанными bundles и интеграцией slots/boot, Mender сочетает обновление устройств с управлением deployments. Выбираются совместимые с продуктом релизы: текущие версии не обязательно подходят Kirkstone.

Для A/B записывается/проверяется неактивный slot, переключается boot selection, good-status ставится после health checks, число попыток ограничивается с сохранением recovery. Миграции общих данных могут мешать откату.

Read-only rootfs требует writable-каталогов state/logs. Secure boot аутентифицирует цепочку загрузки; подписи обновлений и rollback policy — отдельные меры, не автоматический результат A/B.

КОМАНДЫ КРОСС-РАЗРАБОТКИ

Генерация SDK на Linux-host сборки:

```bash
bitbake core-image-minimal -c populate_sdk
```

После установки SDK и подключения соответствующего environment-setup script, из каталога CMake-проекта:

```bash
cmake -S . -B build-target \
  -DCMAKE_TOOLCHAIN_FILE="$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake"
cmake --build build-target
```

Базовая диагностика на целевом устройстве:

```bash
uname -a
cat /proc/cmdline
dmesg
ls -l /dev
```

РАЗДЕЛ 5. ПРЕИМУЩЕСТВА, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

Linux даёт зрелую экосистему и сеть, но размер и обычное планирование могут не подойти маленькому устройству или системе с жёстким real time. RTOS подходит для строгих сроков и малого объёма. PREEMPT_RT и оборудование нужно оценивать отдельно: гарантии жёсткого real time нельзя предполагать.

РАЗДЕЛ 6. ОШИБКИ И БЕЗОПАСНОСТЬ

Отсутствующий драйвер, неверный device tree, недостающий firmware и права могут выглядеть как ошибка приложения. Износ накопителя, потеря питания при обновлении, сети и памяти влияют на надёжность. Применяйте минимальные права, защищайте учётные данные и воспроизводите проблему на устройстве, если важны периферия или время.

РАЗДЕЛ 7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТАХ КАНДИДАТА

До прихода нашей команды существовала базовая заготовка платформы Yocto. Linphone SDK, WebRTC и mediasoup в ней отсутствовали. Наша команда добавила эти компоненты и интегрировала их сборочные зависимости, пакеты и runtime-требования в образ телефона. Мой личный вклад включал приложение/SDK, метаданные BitBake, упаковку, интеграцию образа и проверку на устройстве; интеграция всего стека была командной работой.

SIP-BASED PHONE SOFTWARE: CV указывает embedded Linux, Qt и i.MX. Легенда описывает приложение, сервисы и диагностику телефона. Запрос требует глубокого embedded Linux; Responsibilities отличает интеграцию от самостоятельного владения ядром.

РАЗДЕЛ 8. ВОПРОСЫ НА ИНТЕРВЬЮ

ВОПРОС EL-01. Что делает PID 1?

Ответ: PID 1 — первый user-space-процесс с особым lifecycle и reaping orphan-children. Init-система запускает/управляет сервисами и shutdown. Наличие PID 1 не доказывает readiness всех приложений/устройств.

ВОПРОС EL-02. Что такое корневая файловая система?

Ответ: Это filesystem, смонтированная как /, с runtime-программами, libs/config. Внутри могут монтироваться persistent/volatile-области. Состав и writable-политика соответствуют приложению, а не только boot ядра.

ВОПРОС EL-03. Что такое device tree?

Ответ: Device-tree описывает недетектируемое аппаратное устройство, buses, addresses, interrupts, GPIO и ресурсы. Он не реализует driver. Загруженный DTB, bindings и физическая плата согласуются.

ВОПРОС EL-04. Гарантируется ли жёсткое real time?

Ответ: Нет. Обычная конфигурация Linux не обещает hard-deadlines. Scheduling, preemption, interrupts, drivers и workload влияют на latency. Real-time требует измерения worst-case под нагрузкой, а не низкого среднего.

ВОПРОС EL-05. Почему нужен тест на устройстве?

Ответ: Цель содержит реальные boot, drivers, timing, ресурсы и filesystem. Desktop-тест изолирует логику, но не доказывает камеру, GPIO, audio-routing и startup. Нужны оба уровня с корректным указанием проверки.

ВОПРОС EL-06. Почему приложение работает в shell, но не как сервис?

Ответ: Сравниваются user/groups, environment, working-directory, limits, filesystem и startup-dependencies. Затем journal/effective-config. Shell может давать variables и уже готовые services, отсутствующие при boot.

ВОПРОС EL-07. Что важно для достоверного удалённого стека вызовов?

Ответ: Нужны точные executable/debug-symbols процесса/прошивки, архитектура и remote-debugger. Target-libraries сопоставляются с правильным sysroot. Правдоподобный stack неверного binary обманчив.

ВОПРОС EL-08. Какова типичная цепочка embedded Linux boot?

Ответ: Boot ROM и firmware/bootloader загружают kernel/hardware-description, ядро монтирует rootfs и запускает user-space. Этапы зависят от платы. До обвинения приложения определяется первая отсутствующая веха.

ВОПРОС EL-09. Почему существующий executable даёт Exec format error или No such file?

Ответ: Проверяются architecture, ABI, ELF-interpreter и сам файл. Отсутствующий dynamic-loader даёт missing-file при существующем executable. До правки логики исследуются ELF и loader на цели.

ВОПРОС EL-10. Как диагностировать missing shared-library?

Ответ: Проверяются required-libs, loader-search и deployed-files относительно sysroot/packages. Важны architecture/SONAME, а не одно имя. Временный LD_LIBRARY_PATH не заменяет исправление packaging.

ВОПРОС EL-11. Что разделяют процессы и потоки?

Ответ: Потоки процесса разделяют address-space и многие ресурсы, имея собственные execution-state/stacks. Sharing даёт и races. Mutex защищает инвариант; перенос в поток не устанавливает безопасное владение.

ВОПРОС EL-12. Как отличить deadlock от медленной работы?

Ответ: Исследуются stacks, waits, владение и прогресс. Цикл ожидания отличается от долгого I/O или CPU-работы. Сохраняется trigger-последовательность; sleeps лишь меняют timing.

ВОПРОС EL-13. Как предсказуемо остановить worker?

Ответ: Определяются stop-request, пробуждение blocking-операции и join-owner. Locks освобождаются до callbacks/waits с re-entry. Проверяются повтор startup/shutdown и initialization-failure; cleanup не зависит от живого UI.

ВОПРОС EL-14. Что важно при QThread и device-events?

Ответ: QThread-object обычно живёт в creator-thread, работа — в управляемом потоке. Нужны affinity worker и queued-delivery. GUI потребляет без блокировки, время жизни request/buffer покрывает доставку.

ВОПРОС EL-15. Как обрабатывать шумные GPIO edges?

Ответ: Проверяются line, polarity, электрические assumptions и timestamps/order относительно физического ввода. Bounce отделяется от software-дубля до debounce. Edge трубки становится контролируемым state-transition с явным shutdown/cleanup.

ВОПРОС EL-16. Доказывает ли рост RSS утечку?

Ответ: Нет. Allocator, caches, mappings и workload увеличивают RSS. Сравниваются одинаковые сценарии, lifetime/resources и diagnostics. Утечка означает, что выделения переживают нужного владельца или становятся недостижимыми без освобождения; одна большая выборка памяти этого не доказывает.

ВОПРОС EL-17. Как конфигурация переживает прерванную запись?

Ответ: Задаётся crash-consistency, обнаружение partial-file и замена. Частый подход — полный temporary-file и atomic-replace с нужной синхронизацией для durability. Recovery проверяется прерыванием; close не равен power-loss-safety.

ВОПРОС EL-18. Что меняется с read-only rootfs?

Ответ: Всем writers задаются writable/volatile-paths: state, logs, caches, update-metadata. Startup создаёт директории с правильным owner. Persistence после reboot отделяется от runtime-write; нужная конфигурация не должна тихо исчезать.

ВОПРОС EL-19. Как исследовать permissions без запуска всего root?

Ответ: Проверяются user, groups, file/device-permissions и security/sandbox-policy. Определяется минимальный доступ failing-operation. Root-test проверяет гипотезу, но постоянные лишние права увеличивают ущерб и скрывают контракт.

ВОПРОС EL-20. Что проверять unit, integration и target-тестами?

Ответ: Чистые state/conversion-rules проверяются unit, контракты компонентов — integration. Boot, GPIO, camera/audio и состав image требуют target/подходящего hardware. Успех уровня не доказывает остальные.

ВОПРОС EL-21. Исправляет ли rootwait отказ root filesystem?

Ответ: Он ожидает обнаружения устройства, но не исправляет отсутствие драйвера, неверный раздел или неподдерживаемую filesystem. Сначала определяются отказавшая стадия и root=.

ВОПРОС EL-22. Почему бинарник из SDK может не работать на target?

Ответ: Могут различаться architecture, loader, libc/C++ ABI или библиотеки. Нужны соответствующее SDK environment, новый CMake build directory и проверка реальных зависимостей.

ВОПРОС EL-23. Чем различаются strace, perf, Valgrind и GDB?

Ответ: strace отслеживает syscalls, perf профилирует через sampling, Valgrind проверяет поддерживаемые сценарии памяти, GDB исследует process state/control flow. Доступность и накладные расходы различаются.

ВОПРОС EL-24. Гарантирует ли A/B безопасные обновления с откатом?

Ответ: Нет. Нужны проверенные артефакты, boot selection, health confirmation, ограничение попыток и recovery. Миграции данных и anti-rollback policy могут ограничивать откат; secure boot требует собственной цепочки доверия.

РАЗДЕЛ 9. ИСТОЧНИКИ

Дата проверки: 2026-11-13

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
