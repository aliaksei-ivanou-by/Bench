BitBake

РАЗДЕЛ 1. ТЕХНОЛОГИЯ И ВЕРСИЯ

Категория: Инструмент сборки

BitBake 2.0 с Yocto Kirkstone; точное поведение зависит от версии проекта.

РАЗДЕЛ 2. НАЗНАЧЕНИЕ

BitBake разбирает метаданные и выполняет граф зависимых задач для сборки целей. Это исполнитель задач системы OpenEmbedded; рецепты и конфигурации содержат обрабатываемые инструкции.

РАЗДЕЛ 3. ОСНОВНЫЕ ПОНЯТИЯ

При разборе конфигурации, классы, рецепты и подходящие appends объединяются в datastore. По метаданным выбираются providers и версии; затем планируются задачи do_fetch, do_unpack, do_patch, do_configure, do_compile, do_install и упаковки.

Зависимости связывают задачи разных рецептов. Сигнатуры и shared state позволяют повторно использовать результаты при совпадении входов, но не исправляют неописанную зависимость.

DEPENDS задаёт зависимости рецептов при сборке; RDEPENDS — runtime-зависимости пакета, обычно с указанием имени пакета.

Задачи рецепта образуют граф, а не один последовательный shell-скрипт. Например, получение и распаковка готовят исходники, а конфигурация и компиляция зависят от нужных входов сборки.

Задача установки размещает файлы в промежуточном каталоге; упаковка и сборка образа выполняются отдельно. Overrides и конфигурация слоёв могут изменить итоговое значение переменной, поэтому раскрытые метаданные часто полезнее одного отдельного присваивания.

Повторное использование shared state оценивают через сигнатуры и объявленные входы. Отсутствующую runtime-библиотеку ищут на границе пакета и образа, а ошибку конфигурации — по логу соответствующей задачи и sysroot.

Это разные пути диагностики.

РАЗДЕЛ 4. ТИПИЧНОЕ ИСПОЛЬЗОВАНИЕ

Команды выполняются в инициализированной среде сборки.

- bitbake <recipe> собирает цель.
- bitbake <recipe> -c listtasks перечисляет задачи.
- bitbake -e <recipe> показывает раскрытое окружение.
- bitbake -g <target> создаёт графы зависимостей.
- bitbake-layers show-appends помогает найти применённые appends.

При ошибке задачи изучают log.do_* в рабочем каталоге рецепта.

При ошибке сборки определите рецепт и задачу, прочитайте её лог, затем проверьте итоговые метаданные и объявленные зависимости. Если сборка успешна, а файла нет на устройстве, проследите путь от do_install до содержимого пакета и выбора в образ, не пересобирая всё случайным образом.

Имена рецептов в DEPENDS и имена пакетов в RDEPENDS имеют разные роли. oe-pkgdata-util проверяет метаданные уже собранных пакетов текущей конфигурации.

СОЗДАНИЕ И ДИАГНОСТИКА РЕЦЕПТА

.bb описывает компонент; подходящий .bbappend расширяет его из другого слоя. Honister 3.4 ввёл overrides с двоеточием: SRC_URI:append = " file://fix.patch" и FILES:${PN}:append = " ${datadir}/phone". Для :append сохраняются необходимые пробелы. Нельзя заменять все подчёркивания: PREFERRED_VERSION_recipe и суффиксы коллекций слоёв не являются override-синтаксисом.

Использовать inherit cmake, meson или autotools согласно системе сборки. inherit pkgconfig интегрирует pkg-config для кросс-сборки, но не устанавливает зависимости и не заменяет DEPENDS.

Библиотеки устанавливаются в ${D}${libdir}, headers — в ${D}${includedir}, executables — в ${D}${bindir}. Стандартное разбиение обычно относит headers и development metadata в ${PN}-dev, отделённую debug information — в ${PN}-dbg.

FILES:${PN} использует целевые пути без ${D}; проверяются PACKAGES и реальные файлы вместо помещения всего в runtime.

Например, bitbake -e hello | grep '^PACKAGECONFIG=' показывает итоговое значение; для других задач меняется имя переменной. bitbake -c devshell hello открывает shell окружения сборки, а не target shell. oe-pkgdata-util list-pkg-files hello и oe-pkgdata-util find-path /usr/bin/hello исследуют данные уже собранных пакетов. bitbake-layers show-appends подтверждает применение appends.

devtool add добавляет новый компонент; devtool modify предоставляет исходники существующего рецепта; devtool build поддерживает итерации; devtool finish экспортирует зафиксированные изменения в сопровождаемый слой и снимает workspace override. Проверяются сгенерированные sources, license fields, dependencies и install behavior.

LICENSE определяет лицензии, LIC_FILES_CHKSUM отслеживает их текст, SRC_URI — входные данные fetch, SRCREV — фиксированную ревизию VCS. Изменение license checksum требует анализа текста, а не только принятия нового hash.

Для installed-vs-shipped проверяются ${D}, PACKAGES и FILES; нужные файлы относятся в корректный пакет, ненужные перестают устанавливаться. Для dev-so проверяются development symlinks; plugin .so могут требовать отдельного решения.

Для file-rdeps добавляется настоящий runtime-provider. Для buildpaths/rpaths из конфигурации убираются host-пути.

Глобальный INSANE_SKIP скрывает дефекты вместо исправления.

ПРИМЕРЫ КОМАНД НА LINUX-HOST

Проверка метаданных и состава пакетов для рецепта hello:

```bash
bitbake -e hello | grep '^PACKAGECONFIG='
bitbake-layers show-appends
oe-pkgdata-util list-pkg-files hello
oe-pkgdata-util find-path /usr/bin/hello
```

Отдельная интерактивная сессия окружения сборки:

```bash
bitbake -c devshell hello
```

ФРАГМЕНТЫ РЕЦЕПТА

Пример расширения рецепта; пути относятся к целевой системе:

```bitbake
SRC_URI:append = " file://fix.patch"
FILES:${PN}:append = " ${datadir}/phone"
```

Для проекта на CMake с использованием pkg-config:

```bitbake
inherit cmake pkgconfig
```

РАЗДЕЛ 5. ПРЕИМУЩЕСТВА, ОГРАНИЧЕНИЯ И АЛЬТЕРНАТИВЫ

Граф задач явно задаёт зависимости, параллельное выполнение и повторное использование. Сложность создают взаимодействующие слои, overrides, сигнатуры и providers. Для одного host-приложения прямой CMake или Make часто проще, но он не заменяет составление образа и метаданные кросс-сборки, когда они нужны.

РАЗДЕЛ 6. ОШИБКИ И БЕЗОПАСНОСТЬ

Отсутствующий DEPENDS может дать сборку, работающую только благодаря случайному состоянию host или кеша. Пропущенная runtime-зависимость может оставить успешную сборку и неработающее устройство. Конфликты версий и providers, неприменённые .bbappend и незафиксированные загрузки нарушают воспроизводимость. До массовой очистки кеша изучайте сигнатуры и логи.

РАЗДЕЛ 7. ИСПОЛЬЗОВАНИЕ В ПРОЕКТАХ КАНДИДАТА

До прихода нашей команды существовала базовая заготовка платформы Yocto. Linphone SDK, WebRTC и mediasoup в ней отсутствовали. Наша команда добавила эти компоненты и интегрировала их сборочные зависимости, пакеты и runtime-требования в образ телефона. Мой личный вклад включал приложение/SDK, метаданные BitBake, упаковку, интеграцию образа и проверку на устройстве; интеграция всего стека была командной работой.

SIP-BASED PHONE SOFTWARE: CV указывает собственные рецепты и .bbappend для SDK. Легенда описывает кросс-сборку SDK и интеграцию образа; Responsibilities уточняет границы владения слоями и отдельными изменениями. Запрос прямо требует BitBake и рецепты.

РАЗДЕЛ 8. ВОПРОСЫ НА ИНТЕРВЬЮ

ВОПРОС BB-01. Что планирует BitBake?

Ответ: BitBake разбирает recipes/config/classes, выбирает providers и планирует граф tasks. Fetch/configure/compile/package зависят от prerequisites/signatures; это не просто shell-цикл рецептов.

ВОПРОС BB-02. Чем отличаются DEPENDS и RDEPENDS?

Ответ: DEPENDS задаёт build-зависимости recipes со staged-результатами. RDEPENDS — runtime-metadata пакетов, обычно RDEPENDS:${PN}. Нужный при compile рецепт не автоматически задаёт имя runtime-пакета.

ВОПРОС BB-03. Как посмотреть итоговые переменные?

Ответ: Используется bitbake -e recipe в настроенной среде. Проверяются итоговое значение и история присваиваний, overrides/appends, а не один файл слоя.

ВОПРОС BB-04. Где искать причину ошибки задачи?

Ответ: Начало — log.do_* упавшей задачи; run.do_* показывает generated-команду. Важны первая содержательная ошибка и контекст; последняя ошибка make часто следствие.

ВОПРОС BB-05. Почему сборка проходит, а устройство не работает?

Ответ: На цели могут отсутствовать package, loader, library, config, permissions или готовый сервис. Проверяются image/deployment и startup; пересборка compile не исправляет любую runtime-причину.

ВОПРОС BB-06. Чем отличается do_install от сборки образа?

Ответ: do_install копирует в ${D}. Packaging распределяет файлы по packages, do_rootfs собирает выбранные пакеты, image-tasks дают deployable-artifacts. Файлы ${D} не автоматически оказываются на устройстве.

ВОПРОС BB-07. Что проверить до сброса кеша?

Ответ: До очистки проверяются logs, metadata, revisions и signature-inputs. Неявная зависимость/неверный provider переживают clean-rebuild. Очистка должна проверять гипотезу, сохраняя evidence исходного отказа.

ВОПРОС BB-08. Какова обычная цепочка tasks рецепта?

Ответ: Обычный путь — fetch, unpack, patch, configure, compile, install, package. Реальное выполнение определяют graph/classes/dependencies. Образ потребляет packages позже; рецепт не обязан реализовать каждую task сам.

ВОПРОС BB-09. Чем различаются S, B, D и WORKDIR?

Ответ: S — исходники, B — build-каталог, D — install-staging, WORKDIR — рабочая область рецепта. Они могут различаться. Эти variables предотвращают запись outputs в слой и установку в host-filesystem.

ВОПРОС BB-10. Как рецепт выбирает исходники и patches?

Ответ: SRC_URI задаёт locations и дополнительные inputs: patches/local-files; checksums защищают archives. Для VCS при воспроизводимости фиксируется revision. Source-directory и branch/revision должны согласовываться.

ВОПРОС BB-11. Почему .bbappend не влияет на нужный рецепт?

Ответ: Имя может не совпасть с версией, слой выключен или выбран другой provider. Проверяются show-layers/show-appends, выбор recipe и итоговые values. Неприменённый append не меняет сборку.

ВОПРОС BB-12. Что решает FILESEXTRAPATHS?

Ответ: Расширяет поиск local-files metadata, часто из слоя append. SRC_URI file-entry недостаточно, если файл не найден в search-path. Изменение ограничивается нужным рецептом.

ВОПРОС BB-13. Зачем inherit класса build-system?

Ответ: cmake/autotools дают configure/build/install и cross-интеграцию. Рецепту всё равно нужны dependencies/options. Ручные host-команды обходят toolchain/sysroot и случайно используют host-libs.

ВОПРОС BB-14. Как связаны cross-compilation и sysroots?

Ответ: Toolchain создаёт target-код, recipe-sysroot даёт target headers/libs объявленных dependencies. Генераторы работают на host и требуют native-зависимости. Наличие executable в PATH не доказывает архитектуру.

ВОПРОС BB-15. Что контролирует PACKAGECONFIG?

Ответ: Выбирает optional-features и может связывать configure-arguments/dependencies. Проверяются итоговый выбор и upstream-build. Удаление flag не является доказанной size-оптимизацией без проверки зависимостей/runtime.

ВОПРОС BB-16. Как связаны PACKAGES и FILES?

Ответ: PACKAGES объявляет выходные пакеты, FILES распределяет installed-paths. Рецепт разделяет runtime/development/debug и другое. Missing-file проверяется через package-data: patterns и имена могут отправить его не туда.

ВОПРОС BB-17. Почему полезна QA-ошибка installed-vs-shipped?

Ответ: Она выявляет installed-files, не распределённые по packages. Исправляются путь установки или packaging под intended-layout. Глобальное отключение скрывает пропавший runtime-контент.

ВОПРОС BB-18. Что обеспечивают signatures и sstate?

Ответ: Signatures представляют task-inputs/metadata; sstate использует подходящие outputs. Необъявленный input может не вызвать rebuild. Изучаются signatures/dependencies вместо автоматического обвинения cache.

ВОПРОС BB-19. Чем различаются clean, cleansstate и cleanall?

Ответ: clean убирает work-outputs, оставляя shared-state. cleansstate удаляет и локальные sstate-результаты; remote-mirrors отдельно. cleanall удаляет ещё fetched-source. Выбор важен при общих downloads/caches.

ВОПРОС BB-20. Как исследовать неожиданный provider/dependency?

Ответ: Проверяются metadata/provider-preferences и graph, например bitbake -g. Build-edges recipes отделяются от runtime-edges packages. Исправляется зависимость, а не произвольный порядок и предположение заполненного sysroot.

ВОПРОС BB-21. Нужно ли заменять все подчёркивания двоеточиями в Honister?

Ответ: Нет. Изменились override operations и package overrides, но не обычные имена переменных и суффиксы без override-семантики. Нужен анализ смысла вместо сплошной замены.

ВОПРОС BB-22. Зачем отделять -dev и -dbg от runtime?

Ответ: Headers/build metadata нужны разработке, отделённые symbols — диагностике. Runtime обычно требует executables и runtime libraries. Реальное разбиение определяется patterns и порядком пакетов.

ВОПРОС BB-23. Как modify и finish сохраняют исправление?

Ответ: modify предоставляет исходники рецепта для итераций; после commit finish экспортирует изменения в слой и снимает workspace override. Результат проверяется сборкой через экспортированные метаданные.

ВОПРОС BB-24. Предоставляет ли inherit pkgconfig отсутствующую библиотеку?

Ответ: Нет. Он настраивает pkg-config для кросс-сборки. DEPENDS всё равно должен назвать provider, чьи headers, libraries и .pc нужны в recipe sysroot.

РАЗДЕЛ 9. ИСТОЧНИКИ

Дата проверки: 2026-11-13

- https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-execution.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/tasks.html

- https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-metadata.html

- https://docs.yoctoproject.org/migration-guides/migration-3.4.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/qa-checks.html

- https://docs.yoctoproject.org/4.0.30/sdk-manual/extensible.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html
