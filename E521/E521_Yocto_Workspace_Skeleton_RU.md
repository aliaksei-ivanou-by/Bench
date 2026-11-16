СКЕЛЕТ ПРОЕКТА YOCTO: POKY, META-BC И СЛОИ ПРОДУКТА

Контекст: E521, Yocto Kirkstone. Дата проверки: 2026-11-16. Это пример организации рабочего каталога. Поддерево meta-bc соответствует предоставленному снимку; остальные каталоги продукта показывают распределение задач, а не восстанавливают исходное закрытое рабочее окружение.

01. ОСНОВНАЯ ИДЕЯ

Рабочий каталог содержит репозитории исходников, подключаемые слои метаданных, каталог сборки и кэши. sources/ — просто удобный родительский каталог, а не слой. У слоя обычно есть conf/layer.conf. BitBake читает список подключённых слоёв из build/conf/bblayers.conf. Папка meta-something не становится активной только из-за своего наличия.

Имена каталогов ниже — соглашение. Репозитории могут лежать иначе, в том числе рядом с Poky. Важны настроенные пути, совместимые ревизии метаданных и зависимости слоёв. Пути исходников и сборки должны быть без пробелов.

02. МИНИМАЛЬНАЯ РАБОЧАЯ ОСНОВА

```text
yocto-workspace/
|-- sources/
|   `-- poky/
|       |-- bitbake/
|       |-- meta/
|       |   |-- conf/
|       |   |-- classes/
|       |   `-- recipes-core/
|       |-- meta-poky/
|       |-- meta-yocto-bsp/
|       |-- scripts/
|       `-- oe-init-build-env
|-- build-qemu/
|   |-- conf/
|   |   |-- bblayers.conf
|   |   `-- local.conf
|   |-- cache/
|   `-- tmp/
|-- downloads/
`-- sstate-cache/
```

- poky/ — репозиторий эталонной интеграции. Это не один слой метаданных.
- poky/bitbake/ содержит движок сборки. Его не добавляют как слой.
- poky/meta/ — OpenEmbedded-Core: базовые рецепты, классы и настройки.
- poky/meta-poky/ добавляет правила эталонного дистрибутива Poky.
- poky/meta-yocto-bsp/ содержит BSP эталонного оборудования; он не заменяет BSP конкретного продукта NXP.
- oe-init-build-env подготавливает оболочку и создаёт или выбирает каталог сборки.
- build-qemu/ хранит локальную конфигурацию и результаты. Это не слой исходников.
- downloads/ хранит загруженные исходные данные; sstate-cache/ — повторно используемые результаты задач. Их расположение настраивается отдельно.

03. РАБОЧИЙ КАТАЛОГ ТЕЛЕФОНА С ВНЕШНИМИ СЛОЯМИ

```text
yocto-workspace/
|-- sources/
|   |-- poky/
|   |-- meta-openembedded/
|   |   |-- meta-oe/
|   |   |-- meta-networking/
|   |   |-- meta-python/
|   |   `-- meta-multimedia/
|   |-- meta-qt5/
|   |-- meta-freescale/
|   |-- meta-imx/
|   |   |-- meta-bsp/
|   |   `-- meta-sdk/
|   |-- meta-bc/
|   |   |-- conf/layer.conf
|   |   |-- classes/cmakebuilder.bbclass
|   |   `-- recipes-bc/
|   |       |-- linphone-sdk/
|   |       |   |-- linphone-sdk/
|   |       |   |   `-- linphone-sdk_latest.bb
|   |       |   `-- python3-pystache/
|   |       |       `-- python3-pystache_0.6.0.bb
|   |       |-- libyuv/
|   |       |-- gsm/
|   |       |-- spandsp/
|   |       `-- flexisip/
|   `-- meta-phone/
|       |-- conf/layer.conf
|       |-- recipes-apps/
|       |-- recipes-connectivity/
|       |-- recipes-core/
|       `-- recipes-kernel/
|-- build-phone/
|   |-- conf/bblayers.conf
|   |-- conf/local.conf
|   `-- tmp/
|-- downloads/
`-- sstate-cache/
```

Это типовая организация, а не универсальный список обязательных слоёв. meta-imx — репозиторий с несколькими слоями: в BBLAYERS указывается конкретный слой, например meta-imx/meta-bsp, а не автоматически корень репозитория. Нужные слои NXP/Freescale и их ревизии определяет manifest выбранного BSP. По этой схеме каталогов нельзя установить фактические MACHINE и выпуск BSP продукта.

meta-openembedded добавляет общие рецепты пакетов. meta-qt5 предоставляет рецепты и классы Qt. BSP производителя даёт поддержку оборудования. meta-bc содержит метаданные стека Linphone. meta-phone хранит приложения продукта, состав пакетов, сервисы и целевые дополнения. Имена каталогов и порядок слоёв не определяют авторство кода.

04. ЧТО НАХОДИТСЯ В ПРЕДОСТАВЛЕННОМ META-BC

В скачанной копии настоящий корень слоя — C:\Users\User\Downloads\meta-bc\meta-bc. Внешняя папка является только контейнером. При подключении копии в Linux нужно указать каталог с conf/layer.conf. В схеме этот внутренний слой сразу расположен как sources/meta-bc, чтобы избежать лишнего повторения имени.

Путь рецепта SDK имеет дополнительную вложенность: recipes-bc/linphone-sdk/linphone-sdk/linphone-sdk_latest.bb. Это допустимо, поскольку BBFILES предоставленного слоя явно включает такую глубину. Другой слой только со стандартным более коротким шаблоном сам этот путь не обнаружит.

Выдержка из оригинальных объявлений; это не полный новый конфигурационный файл:

```bitbake
BBFILE_COLLECTIONS += "bc"
BBFILES := "${BBFILES} ${LAYERDIR}/recipes-*/*/*.bb ${LAYERDIR}/recipes-*/*/*/*.bb ${LAYERDIR}/recipes-*/*/*/*.bbappend"
LAYERSERIES_COMPAT_bc = "kirkstone"
PREFERED_LINPHONE_SDK_RECIPE_VERSION ?= "latest"
PREFERRED_VERSION_linphone-sdk = "${PREFERED_LINPHONE_SDK_RECIPE_VERSION}"
```

conf/layer.conf объясняет BitBake, где искать метаданные слоя. classes/cmakebuilder.bbclass — общая логика сборки, а не исходники SDK. Рецепт .bb описывает получение и сборку SDK; загруженные C++-исходники попадают в рабочий каталог сборки, а не автоматически в слой. Замечания прежней проверки остаются в силе: в снимке есть старый синтаксис overrides и другие проблемы из построчного разбора.

05. НЕБОЛЬШОЙ СЛОЙ ПРОДУКТА

```text
meta-phone/
|-- conf/
|   `-- layer.conf
|-- recipes-apps/
|   `-- phone-ui/
|       |-- phone-ui_1.0.bb
|       `-- files/
|           `-- phone-ui.service
|-- recipes-connectivity/
|   `-- linphone-sdk/
|       |-- linphone-sdk_latest.bbappend
|       `-- files/
|-- recipes-core/
|   |-- images/
|   |   `-- phone-image.bb
|   `-- packagegroups/
|       `-- packagegroup-phone.bb
`-- recipes-kernel/
    `-- linux/
        `-- files/
```

Это примеры имён файлов продукта. Дополнение ядра создаётся только для поставщика, реально выбранного BSP; сам каталог ничего не меняет. Необязательные files/ хранят локальные входные файлы: unit сервиса, патчи и фрагменты конфигурации. Исходники приложения могут находиться в отдельном Git-репозитории, на который ссылается рецепт.

Пример conf/layer.conf для слоя телефона, напрямую зависящего от meta-bc и Qt 5:

```bitbake
BBPATH .= ":${LAYERDIR}"
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "phone"
BBFILE_PATTERN_phone = "^${LAYERDIR}/"
BBFILE_PRIORITY_phone = "6"
LAYERSERIES_COMPAT_phone = "kirkstone"
LAYERDEPENDS_phone = "core bc qt5-layer"
```

В зависимостях указываются идентификаторы коллекций других слоёв, а не имена папок. В предоставленном meta-bc коллекция называется bc; в просмотренном meta-qt5 для Kirkstone — qt5-layer. Слой Qt также объявляет собственные зависимости. Прямые зависимости от других слоёв продукта/BSP задаются их реальными именами коллекций. LAYERDEPENDS проверяет предпосылки, но не скачивает и не подключает слои.

Рецепт приложения собирает и упаковывает приложение. Packagegroup объединяет зависимости рабочих пакетов. Рецепт образа выбирает состав продукта. Дополнение SDK расширяет исходный рецепт без его копирования. Полный .bb уместен для собственного поставщика продукта, а .bbappend — для целевого расширения существующего поставщика. Приоритет 6 показан как настройка выбора рецептов, а не как указание собирать этот слой после слоя 5.

06. BBLAYERS.CONF И LOCAL.CONF

Ниже минимальный пример bblayers.conf для build-qemu, а не полная конфигурация телефона NXP. oe-init-build-env обычно создаёт начальный файл; нужно сохранять соответствующую версию конфигурации и по возможности менять пути через bitbake-layers.

```bitbake
POKY_BBLAYERS_CONF_VERSION = "2"
BBPATH = "${TOPDIR}"
BBFILES ?= ""

BBLAYERS ?= " \
    ${TOPDIR}/../sources/poky/meta \
    ${TOPDIR}/../sources/poky/meta-poky \
    ${TOPDIR}/../sources/poky/meta-yocto-bsp \
"
```

TOPDIR — активный каталог сборки. В этой схеме его родитель — yocto-workspace. Для телефона build-phone/conf/bblayers.conf дополнительно подключает нужные подслои meta-openembedded, Qt, слои BSP производителя, meta-bc и meta-phone. Указываются реальные каталоги слоёв с conf/layer.conf. Ни sources/, ни корень репозитория meta-openembedded не заменяют его отдельные подслои.

Минимальные настройки local.conf для упражнения QEMU:

```bitbake
MACHINE = "qemuarm64"
DL_DIR = "${TOPDIR}/../downloads"
SSTATE_DIR = "${TOPDIR}/../sstate-cache"
```

Сборка телефона сохраняет реальные MACHINE, дистрибутив и настройки производителя. Нельзя заменять их на qemuarm64. DISTRO определяет правила дистрибутива, MACHINE — оборудование и настройки архитектуры, а рецепт образа — пакеты. Важные настройки продукта в итоге хранятся в контролируемых метаданных выпуска, а не только в local.conf одного разработчика.

07. КОМАНДЫ ДЛЯ БАЗОВОГО КАТАЛОГА QEMU

На Linux-компьютере, подготовленном для Kirkstone, вне уже активного окружения сборки:

```bash
mkdir -p "$HOME/yocto-workspace/sources"
cd "$HOME/yocto-workspace"
git clone --branch kirkstone https://git.yoctoproject.org/poky sources/poky
source sources/poky/oe-init-build-env build-qemu

# The current directory is now build-qemu.
bitbake-layers show-layers
```

После настройки local.conf для QEMU из раздела 06 собирается готовый эталонный образ:

```bash
bitbake core-image-minimal
runqemu qemuarm64 core-image-minimal nographic slirp
```

Клонирование ветки создаёт начальное упражнение, а не неизменное описание выпуска. Для повторяемого продукта записываются или закрепляются согласованные commits слоёв. Новая оболочка возвращается в упражнение из yocto-workspace через source sources/poky/oe-init-build-env build-qemu. Копировать весь poky для каждого образа не требуется.

08. ПОДКЛЮЧЕНИЕ СЛОЁВ В СБОРКЕ ПРОДУКТА

После получения репозиториев продукта и совместимых ревизий используется его обычный вход в сборку. У BSP производителя это может быть специальный setup-скрипт, а не голая команда Poky. Сохраняется уже работающий набор слоёв BSP. Ниже показано добавление из build-phone в указанной структуре, а не полная подготовка телефона с нуля.

```bash
bitbake-layers add-layer ../sources/meta-openembedded/meta-oe
bitbake-layers add-layer ../sources/meta-openembedded/meta-networking
bitbake-layers add-layer ../sources/meta-openembedded/meta-python
bitbake-layers add-layer ../sources/meta-openembedded/meta-multimedia
bitbake-layers add-layer ../sources/meta-qt5
bitbake-layers add-layer ../sources/meta-bc

# Create the product layer only if it does not already exist.
bitbake-layers create-layer ../sources/meta-phone
bitbake-layers add-layer ../sources/meta-phone

bitbake-layers show-layers
bitbake-layers show-recipes linphone-sdk
bitbake-layers show-appends
```

create-layer создаёт базовый layer.conf; затем он настраивается под зависимости продукта, как в разделе 05. Уже подключённые слои повторно добавлять не нужно. Подключение даёт доступ к метаданным, но не включает все рецепты в образ и не исправляет отсутствующих поставщиков производителя. Предоставленному рецепту meta-bc нужны зависимости Qt/BSP телефона и ранее описанные исправления.

09. ГДЕ ПОЯВЛЯЮТСЯ РЕЗУЛЬТАТЫ СБОРКИ

```text
build-phone/
|-- conf/
|-- cache/
`-- tmp/
    |-- work/
    |   `-- ... recipe-specific work directories ...
    |-- sysroots-components/
    |-- pkgdata/
    `-- deploy/
        |-- images/
        |   `-- ... configured MACHINE ...
        |-- ipk/
        |-- rpm/
        |-- deb/
        `-- sdk/
```

Имена с многоточиями в work/deploy обозначают категории, а не каталоги, которые нужно создать буквально. Формат пакетов зависит от PACKAGE_CLASSES; ipk, rpm и deb не обязаны существовать одновременно. DEPLOY_DIR_IMAGE указывает реальные результаты для платы. Ядро, DTB, rootfs и файлы Wic зависят от образа/BSP; не каждая сборка создаёт все форматы.

Исходники рецепта S, каталог сборки B, временная установка D, логи T и sysroot зависимостей находятся в настроенной рабочей области сборки. Лучше запросить пути выбранного рецепта, чем зашивать имя архитектуры и версии. Изменения только в этих временных каталогах не являются сохранёнными изменениями слоя.

```bash
bitbake -e linphone-sdk | grep -E '^(S|B|D|T|WORKDIR|RECIPE_SYSROOT)='
bitbake -e phone-image | grep -E '^(MACHINE|DEPLOY_DIR_IMAGE|IMAGE_ROOTFS)='
```

phone-image — пример рецепта образа из раздела 05; при просмотре существующего продукта используется его фактический рецепт.

10. КУДА ОТНОСИТСЯ КОНКРЕТНОЕ ИЗМЕНЕНИЕ

- Поведение исходников и сборки SDK: поддерживаемый поставщик SDK или подходящее дополнение в слое продукта.
- Логика телефона C++: исходники приложения и его существующий рецепт, если меняются зависимости или установка.
- Запуск сервиса: unit в пакете соответствующего компонента и настройки интеграции systemd.
- Набор рабочих пакетов: рецепт образа или packagegroup продукта.
- Настройка ядра или device tree: выбранный поставщик ядра/BSP, часто с дополнением в слое продукта.
- Новый независимый модуль или сервис: при необходимости рецепт этого программного компонента.
- Отдельная линия GPIO: рецепта на физический вывод нет. Драйвер, настройка вывода и зависимости приложения/библиотеки — разные части задачи.
- Общий механизм сборки: класс с подходящей областью действия, а не копия задач в каждом рецепте.
- Подключение слоя: bblayers.conf. Поиск метаданных и зависимости слоя: его conf/layer.conf.
- Кэши загрузки и сборки: DL_DIR и SSTATE_DIR вне поддерживаемых исходных слоёв.

11. ИСТОЧНИКИ И СВЯЗАННЫЕ МАТЕРИАЛЫ E521

Предоставленные meta-bc/conf/layer.conf и список каталогов устанавливают реальную вложенность рецепта и коллекцию bc. Закрытый URI исходников не включён. Пример показывает возможную структуру, а не доказывает исторический полный набор слоёв продукта или успешную сборку.

- Слои: https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html

- Структура исходников и сборки: https://docs.yoctoproject.org/4.0.30/ref-manual/structure.html

- Переменные конфигурации: https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html

- Конфигурация слоя Qt 5: https://github.com/meta-qt5/meta-qt5/blob/kirkstone/conf/layer.conf

- Организация BSP: https://docs.yoctoproject.org/4.0.30/bsp-guide/bsp.html

Полный пример рецептов SDK и приложения: E521_Linphone_SDK_Yocto_Example_RU.md. Разбор каждой строки оригинального рецепта и класса: E521_Linphone_SDK_Original_Recipe_Walkthrough_RU.md.
