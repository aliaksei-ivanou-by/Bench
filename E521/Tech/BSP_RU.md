BSP

РАЗДЕЛ 1. ТЕХНОЛОГИЯ И ВЕРСИЯ

Категория: Встроенная платформа

Board support package для конкретной платы NXP i.MX и релиза производителя.

РАЗДЕЛ 2. НАЗНАЧЕНИЕ

Board support package — аппаратно-зависимое ПО и конфигурация, необходимые для работы ОС на конкретной плате. Состав зависит от производителя и продукта; это не только один драйвер или патч ядра.

РАЗДЕЛ 3. ОСНОВНЫЕ ПОНЯТИЯ

Linux BSP обычно включает исходники или конфигурацию загрузчика и ядра, device trees, драйверы, firmware и метаданные сборки. Компоненты загрузки инициализируют оборудование, ядро использует описание платы и драйверы, а root filesystem содержит user-space ПО.

В Yocto слои производителя могут упаковывать эти элементы; состав и владение зависят от релиза. Board bring-up — запуск базовых функций на конкретном оборудовании.

Границу BSP удобно объяснять через загрузку и путь периферии. Аппаратная инициализация начинается в firmware и компонентах загрузки; ядро использует свою конфигурацию, драйверы и описание оборудования; user space зависит от полученных устройств и сервисов.

Релиз производителя может содержать рецепты, патчи и firmware, которые должны оставаться совместимыми. При диагностике определите, отсутствует ли устройство в ядре, недоступно из-за прав или firmware, либо присутствует, но неверно используется приложением.

Обновление одного компонента влияет на другие, поэтому загрузку, периферию и восстановление проверяют на конкретной ревизии платы. Интеграция приложения с существующим BSP — важная работа, но её не следует представлять как создание всего BSP.

РАЗДЕЛ 4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Начните с ревизии платы, релиза BSP и конфигурации machine. Проследите логи загрузчика и ядра, проверьте device tree и драйвер, затем наличие firmware и user-space пакетов. Проверяйте на физическом оборудовании и фиксируйте использованную конфигурацию.

Для предполагаемого изменения BSP сначала сопоставьте реальную ревизию платы и поддерживаемый релиз производителя. Проследите затронутый путь от загрузочных артефактов через device tree и драйвер до приложения user space.

Зафиксируйте исходную конфигурацию, соберите и разверните соответствующие артефакты в подходящем тестовом окружении, затем проверьте загрузку, периферию и документированный способ восстановления. Если устройство есть в Linux, но не открывается, причиной могут быть права или конфигурация user space, а не отсутствие драйвера BSP.

WORKFLOW ЯДРА, МОДУЛЕЙ И DEVICE TREE

BSP может включать vendor-ветки ядра/U-Boot, machine configuration, firmware и компоненты GPU/VPU/NPU при необходимости. Проприетарные blobs нужны не каждой плате. Примеры экосистем: meta-raspberrypi, meta-freescale с интеграцией NXP meta-imx и meta-ti; ветки и зависимости согласуются с выбранным релизом.

KERNEL-01. Изменить provider.

- Определить provider virtual/kernel.
- Выполнить devtool modify virtual/kernel, где поддерживается, либо использовать разрешённое имя рецепта; в упражнении QEMU это linux-yocto.
- Изменить workspace sources, сделать отдельный Git commit, собрать и проверить.
- Либо экспортировать через devtool finish linux-yocto ../meta-lab, либо вручную использовать git format-patch -1 в репозитории исходников.

В ручном варианте положить патч в files/ рядом с linux-yocto_%.bbappend собственного слоя, содержащим:

```bitbake
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://0001-lab-change.patch"
```

- Имя файла совпадает с экспортированным патчем.
- При ручном экспорте после сохранения патча снять workspace override через devtool reset linux-yocto; finish уже снимает его.
- Затем проверить сборку из слоя.
- Нельзя применять один патч дважды через оба способа экспорта.

Подготовка исходников в workspace для примера QEMU:

```bash
devtool modify linux-yocto
```

После редактирования, commit и проверки — экспорт через devtool:

```bash
devtool finish linux-yocto ../meta-lab
```

Альтернатива — ручной экспорт из Git-каталога исходников:

```bash
git format-patch -1
```

После сохранения патча и добавления append при ручном экспорте:

```bash
devtool reset linux-yocto
```

KERNEL-02. Сохранить конфигурацию.

- Выполнить bitbake -c menuconfig virtual/kernel, сохранить, затем bitbake -c diffconfig virtual/kernel, если provider поддерживает задачи.
- Скопировать фрагмент из указанного командой места в files/lab.cfg и добавить SRC_URI += "file://lab.cfg" в append.
- Для упражнения linux-yocto фрагмент может содержать CONFIG_PRINTK_TIME=y.
- Проверить итоговую .config и поведение после загрузки.
- Если vendor-рецепт не объединяет fragments, нужен поддерживаемый им механизм конфигурации; одной загрузки .cfg недостаточно.

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

KERNEL-03. Упаковать внешний модуль.

- Использовать inherit module и Makefile, совместимый с интерфейсом сборки ядра.
- Рецепт собирается против выбранного ядра и упаковывает установленные .ko.
- KERNEL_MODULE_AUTOLOAD += "lab_driver" запрашивает загрузку при старте, но не выбирает пакет модуля в образ.
- Включить реальный выходной пакет, проверить modinfo/modprobe и dmesg, пересобирать при изменениях ABI/configuration ядра.

Фрагмент рецепта внешнего модуля:

```bitbake
inherit module
KERNEL_MODULE_AUTOLOAD += "lab_driver"
```

DT-01. Собрать и выбрать описание.

- .dts описывает плату; .dtsi хранит общие описания.
- Preprocessing в kernel build и dtc создают .dtb.
- compatible участвует в сопоставлении с драйвером, но также нужны сам драйвер, clocks, regulators, pinctrl и firmware.
- KERNEL_DEVICETREE в machine configuration выбирает outputs у поддерживающих её рецептов.
- Добавление нового .dts через append к ядру обычно требует патча соответствующего build Makefile и выбора output; один fetch не обеспечивает сборку/поставку.

DT-02. Применить overlay.

- Overlay использует /plugin/ и компилируется в .dtbo.
- Для overlays по symbols нужна совместимая symbol information, обычно создаваемая dtc -@ для base и overlay.
- U-Boot загружает их, выбирает FDT, выделяет место через fdt resize и применяет overlay через fdt apply перед запуском Linux.
- Адреса/команды загрузки зависят от платы.
- Firmware Raspberry Pi вместо этого использует dtoverlay= в config.txt.
- После загрузки проверяются живое дерево и probe драйвера; поставленный .dtbo не доказывает применение.

РАЗДЕЛ 5. ПРЕИМУЩЕСТВА, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

BSP производителя ускоряет поддержку оборудования и даёт проверенную основу для поддерживаемых конфигураций. Одновременно возникают зависимости от релизов, патчей и совместимых слоёв производителя. Mainline может упростить сопровождение при достаточной поддержке оборудования и функций; компромисс оценивается для конкретного устройства.

РАЗДЕЛ 6. ОШИБКИ И БЕЗОПАСНОСТЬ

Корректное приложение не исправит несовпадающий device tree, отсутствующий драйвер или неверный загрузочный артефакт. Обновление BSP может изменить интерфейсы ядра или требования к firmware; проверяйте периферию, загрузку и обновление вместе. Сохраняйте способы восстановления и проверяйте подлинность артефактов обновления, когда это применимо.

РАЗДЕЛ 7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТАХ КАНДИДАТА

До прихода нашей команды существовала базовая заготовка платформы Yocto. Linphone SDK, WebRTC и mediasoup в ней отсутствовали. Наша команда добавила эти компоненты и интегрировала их сборочные зависимости, пакеты и runtime-требования в образ телефона. Мой личный вклад включал приложение/SDK, метаданные BitBake, упаковку, интеграцию образа и проверку на устройстве; интеграция всего стека была командной работой.

Запрос прямо требует настройки BSP. SIP-BASED PHONE SOFTWARE в CV описывает интеграцию i.MX; легенда — работу внутри существующей платформы. Responsibilities подтверждает интеграцию приложения и образа с BSP, но не самостоятельное владение всем BSP или board bring-up.

РАЗДЕЛ 8. ВОПРОСЫ НА ИНТЕРВЬЮ

ВОПРОС BSP-01. Что такое BSP?

Ответ: BSP — hardware-specific software/configuration-основа ОС на плате. Обычно включает boot/kernel, hardware-description, drivers/firmware. Граница зависит от vendor/product-релиза; это шире одного application-recipe.

ВОПРОС BSP-02. BSP — это root filesystem?

Ответ: Нет. Rootfs содержит user-space-файлы. BSP обеспечивает hardware-support и может собираться рядом/вместе в vendor-image. Продукту нужны совместимые компоненты обоих уровней.

ВОПРОС BSP-03. Зачем нужен device tree?

Ответ: Он сообщает ядру соединения/ресурсы hardware. Bindings, drivers и плата согласуются. Device-tree не реализует отсутствующий driver и не исправляет физическую разводку.

ВОПРОС BSP-04. Что может сломать обновление BSP?

Ответ: Меняются совместимость boot/kernel/DTB, drivers, firmware и user-space interfaces. Проверяются плата/приложение и recovery. Boot ядра недостаточен для камеры, GPIO, audio и persistent-data.

ВОПРОС BSP-05. Означает ли использование BSP владение им?

Ответ: Нет. Использование BSP и app/image-интеграция отличаются от board-support, porting-drivers и bring-up. Называются личные компоненты/проверки, а не полное владение по наличию платформы.

ВОПРОС BSP-06. Доказывает ли файл устройства, что приложение может его использовать?

Ответ: Нет. Node существует при неверных permissions, driver-state, firmware или config. Проверяются failing-operation, kernel-логи/interface и минимальный целевой сценарий.

ВОПРОС BSP-07. Как проверить обновление BSP?

Ответ: Фиксируются known-good-набор и изменения; проверяются boot, peripherals, app-interfaces/recovery на вариантах платы. Сохраняется rollback, сравниваются повторяемые сценарии; один startup не полная регрессия.

ВОПРОС BSP-08. Какие boot-artifacts должны быть совместимы?

Ответ: Firmware/bootloader, kernel, DTB, rootfs и modules/firmware соответствуют плате/interfaces. Записываются deployed-версии, а не только source-branch. Смешение релизов даёт частичный boot с поздним отказом peripheral/app.

ВОПРОС BSP-09. Когда достаточно device-tree, а когда нужен driver?

Ответ: DT выражает поддержанные соединения/config через bindings. Отсутствующее поведение требует driver-work, электрическая проблема — hardware. Сначала находится недостающая capability, а не любая проблема считается DTS-правкой.

ВОПРОС BSP-10. Для чего defconfig/config-fragment?

Ответ: Они задают вход конфигурации ядра, Kconfig-dependencies — итог. Проверяются .config и artifacts. Option может отключиться dependency или собраться иначе; fragment не доказывает наличие driver.

ВОПРОС BSP-11. Чем различаются built-in, modules и firmware?

Ответ: Built-in входят в kernel, modules загружаются отдельно и соответствуют running-kernel. Firmware устройства — ещё один input. Сборка driver проходит при ошибке packaging, firmware или loading на цели.

ВОПРОС BSP-12. Зачем serial-console при bring-up?

Ответ: Даёт ранние наблюдения до network/graphics/app-logs. Определяется последняя успешная стадия и сохраняется ошибка. Console-настройки соответствуют плате/boot; отсутствие вывода не автоматически мёртвый процессор.

ВОПРОС BSP-13. Зачем bindings, а не копирование nodes?

Ответ: Bindings задают смысл properties, ресурсы и связи compatible-device. Скопированный node может иметь неверные GPIO/clock/IRQ/address при правдоподобном виде. Проверяются плата/driver и реальный probe/I/O.

ВОПРОС BSP-14. Как подтвердить фактически загруженный DTB?

Ответ: Сравниваются bootloader-config/логи с model/properties running-device-tree. Build-file может быть не deployed/selected. При проверке DT-гипотезы сохраняется identity artifact.

ВОПРОС BSP-15. Каков разумный порядок bring-up новой платы?

Ответ: Сначала documented power/boot и early-console, затем memory, storage/rootfs, essential-interfaces и сложные media/app-сценарии. Работа согласуется с hardware с поэтапной проверкой. Это метод, не доказательство личного полного bring-up.

ВОПРОС BSP-16. Какие user-space assumptions сохраняет BSP-изменение?

Ответ: Приложению нужны device-interfaces, permissions, media-formats, libs/ABI и startup. Совместимость внутри kernel — не весь контракт. После driver/DT меняются и проверяются consumer-сценарии, включая отказ/restart.

ВОПРОС BSP-17. Как отделить app-дефект от BSP-интеграции?

Ответ: Минимально проверяется kernel/device-interface на том же image/config и сравнивается с app. Независимый отказ ведёт к driver/board. Рабочий interface — к app-config, ownership/timing до изменения BSP.

ВОПРОС BSP-18. Что делает BSP-handoff полезным app-инженерам?

Ответ: Нужны image/SDK-identifiers, interfaces, ограничения, reproducible-setup и минимальный сценарий с логами/владельцами границ. Тогда приложение проверяется относительно определённой платформы вместо неизвестного набора artifacts.

ВОПРОС BSP-19. Что включить в update/recovery-test?

Ответ: Проверяются auth выбора artifact где поддержано, persistent-data layout, прерывание и known-good recovery. После update/rollback — cold-boot и peripheral/app-сценарии. Backup-image недостаточен при несовместимом boot-selection/data-migration.

ВОПРОС BSP-20. Что отличает использование BSP от customization?

Ответ: Использование опирается на поддержанные board/image interfaces. Customization показывают конкретные machine/boot/kernel/DTB/driver/firmware-изменения и target-проверки. Вклад называется точно; малая правка не означает авторство всей платформы.

ВОПРОС BSP-21. Любой ли рецепт ядра объединяет .cfg из SRC_URI?

Ответ: Нет. Проверяются поддержка provider и итоговая .config. Зависимости конфигурации могут менять результат; vendor-рецепту может требоваться другой механизм.

ВОПРОС BSP-22. Устанавливает ли KERNEL_MODULE_AUTOLOAD модуль?

Ответ: Нет. Он запрашивает загрузку при старте. Нужно включить реальный пакет модуля и проверить совместимость ядра и успешный modprobe на target.

ВОПРОС BSP-23. Почему compatible-узел может не дать работающего устройства?

Ответ: Он может быть disabled, драйвер отсутствовать, probe завершаться ошибкой/откладываться из-за clocks, regulators, pinctrl или firmware. Проверяются живое дерево и kernel logs.

ВОПРОС BSP-24. Что подтверждает применение overlay?

Ответ: Путь загрузки применяет его, nodes/properties появляются в живом дереве, binding драйвера успешен. Одного собранного .dtbo недостаточно.

РАЗДЕЛ 9. ИСТОЧНИКИ

Дата проверки: 2026-11-13

- https://docs.nxp.com/bundle/UG10163/page/topics/introduction_001.html
- https://docs.kernel.org/devicetree/usage-model.html
- https://docs.yoctoproject.org/4.0.30/bsp-guide/bsp.html
- https://docs.kernel.org/driver-api/driver-model/binding.html
- https://docs.yoctoproject.org/4.0.30/kernel-dev/common.html
- https://docs.u-boot.org/en/latest/usage/fdt_overlays.html
- https://www.raspberrypi.com/documentation/computers/config_txt.html
