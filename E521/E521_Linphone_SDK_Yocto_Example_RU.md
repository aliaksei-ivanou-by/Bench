LINPHONE SDK В YOCTO: ПРАКТИЧЕСКИЙ ПРИМЕР ИНТЕГРАЦИИ

01. НАЗНАЧЕНИЕ

Ниже один учебный пример целиком: подключаем официальный слой с рецептом SDK, добавляем свои настройки и собираем маленькую C++-программу, которая использует liblinphone. Затем включаем оба компонента в Linux-образ и проверяем запуск. Это пример реализации, а не копия исторического рецепта проекта.

Команды выполняются в Bash на Linux-хосте, подготовленном для Yocto Kirkstone. Windows PowerShell для сборки не подходит. Для самостоятельного упражнения выбран qemuarm64. В существующем проекте телефона сохраняются его MACHINE, BSP, DISTRO и рецепт образа. Подмена их конфигурацией QEMU не нужна. Полная сборка этого примера здесь не выполнялась; настройки сверены с официальными источниками, перечисленными в конце.

02. КАК СВЯЗАНЫ КОМПОНЕНТЫ

Как читать: разделы 01–12 дают основной путь от слоёв до запуска. Разделы 13–18 объясняют файлы, задачи, предоставленный оригинальный рецепт, его аудит, улучшения и патчи. Разделы 19–23 добавляют образ продукта, systemd, проверку Core, внешний SDK и диагностику. Разделы 24–26 посвящены повторяемой сборке, обновлению, приёмке и ответу на собеседовании. В русском файле и его английской паре одинаковые разделы и примеры кода.

- meta-bc: готовые рецепты SDK.
- meta-phone: наши настройки и рецепт приложения.
- linphone-sdk: собирает и упаковывает SDK.
- linphone-probe: связывает C++-программу с liblinphone.
- core-image-minimal: включает пакеты в образ.

Рецепт SDK берём из официального meta-bc, а изменения храним в собственном слое через .bbappend. SDK состоит из нескольких компонентов; upstream-рецепт содержит особенности их сборки. Поэтому здесь нет упрощённого выдуманного рецепта всего SDK с несколькими универсальными CMake-флагами. Полный собственный .bb ниже относится к приложению, а .bbappend дополняет настоящий рецепт SDK.

03. ПОЛУЧИТЬ СЛОИ

Начинаем в новом каталоге. На хосте уже должны быть установлены зависимости сборки из Yocto System Requirements. Команды ниже не устанавливают их автоматически.

```bash
mkdir -p "$HOME/yocto-linphone-lab"
cd "$HOME/yocto-linphone-lab"

git clone --branch kirkstone https://git.yoctoproject.org/poky
git clone --branch kirkstone https://git.openembedded.org/meta-openembedded
git clone --branch feature/yocto-kirkstone \
    https://gitlab.linphone.org/BC/public/meta-bc.git

cat > enter-build.sh <<'EOF'
export PREFERED_LINPHONE_SDK_RECIPE_VERSION="5.3.x"
unset LATEST_REVISIONS LINPHONE_SDK_REV LINPHONE_SDK_BRANCH
export BB_ENV_PASSTHROUGH_ADDITIONS="${BB_ENV_PASSTHROUGH_ADDITIONS:-} PREFERED_LINPHONE_SDK_RECIPE_VERSION"
source poky/oe-init-build-env build
EOF

source enter-build.sh

bitbake-layers add-layer ../meta-openembedded/meta-oe
bitbake-layers add-layer ../meta-openembedded/meta-networking
bitbake-layers add-layer ../meta-openembedded/meta-python
bitbake-layers add-layer ../meta-openembedded/meta-multimedia
bitbake-layers add-layer ../meta-bc

bitbake-layers create-layer ../meta-phone
bitbake-layers add-layer ../meta-phone

mkdir -p ../meta-phone/recipes-connectivity/linphone-sdk
mkdir -p ../meta-phone/recipes-apps/linphone-probe/files
```

Имя PREFERED_LINPHONE_SDK_RECIPE_VERSION действительно содержит одну R в PREFERED: так переменная называется у upstream. Значение 5.3.x выбирает семейство рецепта; точный исходный commit определяется выбранными метаданными. Это не утверждение о версии SDK в реальном проекте. Новая сессия начинается из корня yocto-linphone-lab командой source enter-build.sh; после неё текущий каталог — build.

04. ДОПОЛНИТЬ РЕЦЕПТ SDK

ФАЙЛ: meta-phone/recipes-connectivity/linphone-sdk/linphone-sdk_%.bbappend

```bitbake
# Keep this learning example audio-only.
PACKAGECONFIG:remove = "video h264"

# The upstream SDK uses a non-standard installation prefix.
# Make headers and libraries available to dependent recipes.
SYSROOT_DIRS:append = " /opt/belledonne-communications"
```

Создай файл по указанному пути. Все пути FILE отсчитываются от корня yocto-linphone-lab. Остальные команды выполняются из build. Символ % позволяет применить дополнение к выбранной версии рецепта linphone-sdk. Проверка show-appends ниже должна показать фактическое соответствие.

Видео отключено только для простого упражнения. Для видеотелефона его оставляют включённым и отдельно проверяют кодеки, устройства и лицензии. SYSROOT_DIRS нужен потому, что /opt не является обычным каталогом библиотек Yocto. Это доступность файлов при сборке другого рецепта, а не включение пакета в образ. SDK сохраняет собственные LICENSE и LIC_FILES_CHKSUM из upstream; не заменяем их на CLOSED или MIT.

05. МАЛЕНЬКОЕ C++-ПРИЛОЖЕНИЕ

ФАЙЛ: meta-phone/recipes-apps/linphone-probe/files/main.cpp

```cpp
#include <iostream>
#include <linphone/linphonecore.h>

int main()
{
    const char *version = linphone_core_get_version();
    if (version == nullptr) {
        std::cerr << "Linphone SDK returned no version\n";
        return 1;
    }

    std::cout << "Linphone SDK version: " << version << '\n';
    return 0;
}
```

Программа проверяет наличие заголовков, линковку и загрузку библиотеки. Она не создаёт SIP-аккаунт и не подтверждает работу звонков. Такой короткий тест помогает сначала отделить проблемы интеграции SDK от проблем приложения.

ФАЙЛ: meta-phone/recipes-apps/linphone-probe/files/CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(linphone_probe LANGUAGES CXX)

include(GNUInstallDirs)

if(NOT LINPHONE_SDK_ROOT)
    message(FATAL_ERROR "LINPHONE_SDK_ROOT must point into the recipe sysroot")
endif()

find_path(LINPHONE_INCLUDE_DIR
    NAMES linphone/linphonecore.h
    PATHS "${LINPHONE_SDK_ROOT}/include"
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

find_library(LINPHONE_LIBRARY
    NAMES linphone
    PATHS "${LINPHONE_SDK_ROOT}/lib"
    NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

if(NOT LINPHONE_INCLUDE_DIR OR NOT LINPHONE_LIBRARY)
    message(FATAL_ERROR "Linphone headers or library are missing from the sysroot")
endif()

add_executable(linphone-probe main.cpp)
target_compile_features(linphone-probe PRIVATE cxx_std_17)
target_include_directories(linphone-probe PRIVATE "${LINPHONE_INCLUDE_DIR}")
target_link_libraries(linphone-probe PRIVATE "${LINPHONE_LIBRARY}")
target_link_options(linphone-probe PRIVATE
    "-Wl,-rpath-link,${LINPHONE_SDK_ROOT}/lib")

# Do not embed build-host paths in the installed executable.
set_target_properties(linphone-probe PROPERTIES
    SKIP_BUILD_RPATH TRUE
    INSTALL_RPATH "")

install(TARGETS linphone-probe RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
```

Путь к SDK поступает из рецепта. Ищем библиотеку только внутри целевого sysroot, чтобы случайно не взять библиотеку Linux-хоста. Флаг rpath-link помогает линкеру найти зависимости liblinphone во время сборки. Он не настраивает поиск библиотек на телефоне: это проверим отдельно при запуске.

06. РЕЦЕПТ ПРИЛОЖЕНИЯ

ФАЙЛ: meta-phone/recipes-apps/linphone-probe/linphone-probe_1.0.bb

```bitbake
SUMMARY = "Small C++ executable checking Linphone SDK integration"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
    file://main.cpp \
    file://CMakeLists.txt \
"
S = "${WORKDIR}"

DEPENDS = "linphone-sdk"
RDEPENDS:${PN} += "linphone-sdk"

inherit cmake

EXTRA_OECMAKE += " \
    -DLINPHONE_SDK_ROOT=${RECIPE_SYSROOT}/opt/belledonne-communications \
"
```

MIT здесь относится к нашему учебному коду. Использование liblinphone сохраняет отдельные лицензионные обязательства SDK. Для промышленного продукта проверяются лицензии всей выбранной сборки, включая кодеки.

- DEPENDS: заголовки и библиотеки SDK доступны до компиляции.
- RDEPENDS: пакет SDK устанавливается вместе с приложением.
- inherit cmake: Yocto передаёт кросс-компилятор и выполняет настройку, сборку и установку.
- do_install: CMake устанавливает результат во временный каталог рецепта через DESTDIR.
- FILES: стандартные правила упаковки уже покрывают /usr/bin/linphone-probe.

07. НАСТРОЙКА ОБРАЗА

Добавь строки в существующий build/conf/local.conf один раз. Не заменяй весь файл. debug-tweaks нужен только для входа в локальный учебный QEMU-образ без пароля; в образ телефона эта настройка не переносится.

```bitbake
MACHINE = "qemuarm64"
PACKAGE_CLASSES = "package_ipk"
EXTRA_IMAGE_FEATURES:append = " debug-tweaks"
IMAGE_INSTALL:append = " linphone-sdk linphone-probe"
```

В продукте IMAGE_INSTALL лучше хранить в собственном рецепте образа или packagegroup. Здесь local.conf делает пример короче. DEPENDS не заменяет IMAGE_INSTALL: успешная сборка библиотеки ещё не означает, что она попала на устройство. Пакеты заголовков -dev и отладочные -dbg также не нужны в обычном рабочем образе.

08. ПРОВЕРИТЬ И СОБРАТЬ

```bash
bitbake-layers show-layers
bitbake-layers show-recipes linphone-sdk
bitbake-layers show-appends

bitbake -e linphone-sdk > linphone-sdk.environment.txt
grep -E '^(FILE|PV|SRC_URI|SRCREV|SRCREV_[A-Za-z0-9_]+|PACKAGECONFIG|SYSROOT_DIRS|LICENSE)=' \
    linphone-sdk.environment.txt

# Read the actual upstream SDK recipe selected by BitBake.
sdk_recipe=$(sed -n 's/^FILE="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
sed -n '1,220p' "$sdk_recipe"

for layer in poky meta-openembedded meta-bc; do
    printf '%s %s\n' "$layer" "$(git -C "../$layer" rev-parse HEAD)"
done > layers.lock.txt

bitbake linphone-sdk
bitbake linphone-probe
bitbake core-image-minimal

oe-pkgdata-util list-pkg-files linphone-sdk
oe-pkgdata-util list-pkg-files linphone-probe
grep -E 'linphone-sdk|linphone-probe' \
    tmp/deploy/images/qemuarm64/core-image-minimal-qemuarm64.manifest
```

До сборки смотрим, какой .bb реально выбран, какие исходники он скачивает и применился ли наш .bbappend. Для воспроизводимости сохраняем commit каждого слоя, свои изменения meta-phone и точные исходные ревизии SDK. Одной записи 5.3.x недостаточно. Если upstream использует плавающие ревизии или скачивает дополнительные исходники внутри сборки, их тоже нужно закрепить; layers.lock.txt сам по себе этого не делает. Полный вывод bitbake -e оставляем локально: он содержит пути и окружение сборки.

В linphone-sdk должны быть рабочие библиотеки из /opt/belledonne-communications; в linphone-probe — /usr/bin/linphone-probe. Если upstream распределил библиотеки по отдельным пакетам, проверяем их имена через pkgdata и корректируем RDEPENDS по фактическому результату. Не добавляем все -dev пакеты в образ ради обхода ошибки упаковки.

09. ЗАПУСТИТЬ ОБРАЗ

ХОСТ СБОРКИ:

```bash
runqemu qemuarm64 core-image-minimal nographic slirp
```

КОНСОЛЬ ГОСТЯ, ВХОД root:

```bash
ls -l /opt/belledonne-communications/lib/liblinphone.so*
LD_LIBRARY_PATH=/opt/belledonne-communications/lib \
    /usr/bin/linphone-probe
```

Ожидаем строку Linphone SDK version: и номер реально собранной версии. LD_LIBRARY_PATH задаётся только для этого процесса. В рабочем телефоне путь задаётся для сервиса приложения либо через конфигурацию загрузчика библиотек, если выбранная libc её поддерживает. Не записываем путь build/tmp/... в конфигурацию устройства. Выход из QEMU: Ctrl+A, затем X.

10. КОМАНДЫ ДЛЯ РАЗРАБОТКИ

```bash
# Run a specific stage and inspect the task output.
bitbake -c fetch linphone-sdk
bitbake -c unpack linphone-sdk
bitbake -c configure linphone-sdk

# Print paths to source, build directory and task logs.
bitbake -e linphone-sdk | grep -E '^(S|B|T|WORKDIR)='

# Rebuild after changing the application files or metadata.
bitbake linphone-probe
bitbake core-image-minimal

# Inspect the final application configuration and sysroot location.
bitbake -e linphone-probe | \
    grep -E '^(RECIPE_SYSROOT|DEPENDS|RDEPENDS:linphone-probe|EXTRA_OECMAKE)='

# Optional: generate an external cross-development SDK for this image.
bitbake -c populate_sdk core-image-minimal
```

ОТДЕЛЬНАЯ ИНТЕРАКТИВНАЯ КОМАНДА:

```bash
bitbake -c devshell linphone-sdk
# Inspect the development environment, then leave this shell:
exit
```

devshell открывает отдельную оболочку. Командой exit возвращаемся в исходную оболочку перед остальными командами. Логи находятся в каталоге T: log.do_configure, log.do_compile и log.do_install. Обычное изменение рецепта или локального исходника подхватывается повторным bitbake. Постоянно выполнять cleanall не нужно: он удаляет скачанные исходники и мешает использовать кэш.

Для своего изменения SDK сначала смотрим SRC_URI и S выбранного рецепта. Если нужный файл находится в дереве, которое обрабатывает do_patch, патч храним в своём слое, добавляя FILESEXTRAPATHS:prepend := "${THISDIR}/files:" и SRC_URI:append = " file://имя-патча.patch". Если компонент скачивается позже внутренней сборкой SDK, обычный do_patch может его ещё не видеть. В таком случае применяем предусмотренный upstream способ либо используем закреплённый fork компонента. Сам факт существования .bbappend не гарантирует, что патч попадёт в нужный submodule.

11. ТИПИЧНЫЕ ОШИБКИ

- No recipes available for .bbappend: проверить имя и версию основного рецепта.
- Header not found: проверить зависимость и наличие заголовков в sysroot приложения.
- Cannot find -llinphone: проверить целевую библиотеку и ссылку, используемую при линковке.
- Shared library not found at runtime: проверить пакеты в образе и путь поиска библиотек на устройстве.
- Wrong architecture or file format: проверить MACHINE и кросс-компилятор, исключить библиотеки хоста.
- Installed but not shipped: проверить разбиение по пакетам и добавить конкретный путь в FILES нужного пакета.
- License or codec configuration failure: разобраться с конкретной лицензией вместо общего разрешения всех commercial-флагов.

12. ЧТО ИМЕННО ПРОВЕРИЛИ

После успешного запуска знаем, что Yocto собрал SDK для нужной архитектуры, приложение получило его заголовки и библиотеки, а образ содержит достаточно файлов для загрузки liblinphone. Дальше нужен отдельный тест телефонного приложения: регистрация SIP, входящий и исходящий звонки, звук в обе стороны, завершение вызова, потеря сети и переключение сервера. Для видеотелефона добавляются камера, кодеки и видеовызов. QEMU не заменяет проверку аудиотракта и оборудования реального телефона.

13. СТРУКТУРА ФАЙЛОВ И ПРОВЕРКА ХОСТА

В основном упражнении получаются следующие файлы. Перед сборкой нужно создать исходники приложения и рецепты из разделов 04–06. Дополнительные файлы из разделов 18–20 относятся к отдельным расширениям; для вывода версии SDK они не нужны.

```text
yocto-linphone-lab/
  enter-build.sh
  poky/
  meta-openembedded/
  meta-bc/
  meta-phone/
    conf/layer.conf
    recipes-connectivity/linphone-sdk/linphone-sdk_%.bbappend
    recipes-apps/linphone-probe/linphone-probe_1.0.bb
    recipes-apps/linphone-probe/files/main.cpp
    recipes-apps/linphone-probe/files/CMakeLists.txt
  build/
    conf/bblayers.conf
    conf/local.conf
    layers.lock.txt
    linphone-sdk.environment.txt
    tmp/deploy/images/qemuarm64/
    tmp/deploy/ipk/
```

Используем поддерживаемый Linux и обычную учётную запись пользователя. Перед долгой сборкой проверяем диск, память и число процессоров. Требования растут при добавлении Qt, видеокодеков, отладочных пакетов и кэша результатов; одна оценка свободного места не гарантирует успешную сборку. В существующем продукте сохраняем рабочую подготовку хоста и настройки BSP.

```bash
# Run on the Linux build host.
id -un
df -h .
free -h
nproc
git --version
python3 --version
locale

# From build/, confirm where BitBake will write its outputs.
bitbake -e linphone-sdk |     grep -E '^(MACHINE|DISTRO|TARGET_ARCH|TUNE_FEATURES|TMPDIR|DL_DIR|SSTATE_DIR)='
```

Команда bitbake-layers create-layer создаёт conf/layer.conf. Шаблоны BBFILES должны находить наши рецепты, а LAYERSERIES_COMPAT должен включать kirkstone. В предоставленном исходном слое имя коллекции — bc. Для сборочных зависимостей вроде Qt всё равно нужны отдельные поставщики рецептов: совместимость слоя сама их не добавляет.

14. ЧТО BITBAKE ДЕЛАЕТ ПО ШАГАМ

Важно различать исходники, временную установку, sysroot приложения, бинарные пакеты и файловую систему устройства. Если файл появился в одном месте, это ещё не означает, что он попал во все остальные.

- do_fetch получает исходники SDK и подмодули, описанные fetcher.
- do_unpack подготавливает дерево исходников S.
- do_patch применяет патчи, перечисленные в SRC_URI.
- do_configure создаёт файлы сборки с использованием целевого toolchain.
- do_compile собирает целевые бинарники в B или во внутренних каталогах SDK.
- do_install устанавливает файлы в D, временное дерево файловой системы.
- do_populate_sysroot передаёт выбранные установленные файлы зависимым рецептам.
- do_package распределяет файлы по рабочим, разработческим и отладочным пакетам.
- Запись пакетов в этом упражнении создаёт файлы .ipk.
- Задача do_rootfs у образа устанавливает выбранные пакеты в IMAGE_ROOTFS.
- Создание образов преобразует эту файловую систему в настроенные форматы.

Это не одна строго последовательная цепочка: упаковка и подготовка sysroot обслуживают разные задачи. DEPENDS связывает сборку приложения с результатом подготовки sysroot SDK. RDEPENDS и IMAGE_INSTALL определяют рабочие пакеты в итоговой файловой системе. inherit cmake предоставляет стандартные задачи нашему маленькому приложению; у SDK сборка устроена сложнее.

```bash
bitbake -c listtasks linphone-sdk
bitbake -g linphone-probe
# Inspect recipe-depends.dot and task-depends.dot in build/.
grep -n 'linphone-sdk' recipe-depends.dot | head -n 20
```

15. ОРИГИНАЛЬНЫЙ РЕЦЕПТ, ПРЕДОСТАВЛЕННЫЙ ДЛЯ ПРОВЕРКИ

Отдельный построчный разбор: E521_Linphone_SDK_Original_Recipe_Walkthrough_RU.md объясняет каждую строку предоставленного рецепта, локального класса CMake и конфигурации слоя через постоянные номера R/C/L.

Для проверки предоставлена локальная копия C:\Users\User\Downloads\meta-bc. Корень слоя находится во вложенном каталоге meta-bc. Проверены recipes-bc/linphone-sdk/linphone-sdk/linphone-sdk_latest.bb, classes/cmakebuilder.bbclass и conf/layer.conf. Исходная копия просмотрена без изменений. Внутренний Git-сервер и имена закрытых репозиториев в руководство не перенесены.

Это вариант для конкретного продукта, а не неизменённый публичный рецепт Kirkstone. В нём есть только linphone-sdk_latest.bb. Поэтому значение 5.3.x из самостоятельного публичного упражнения нельзя переносить в этот локальный слой: для предоставленного рецепта выбирается latest. Публичное упражнение QEMU и этот вариант для телефона используют разные конфигурации.

```bitbake
# Selector for the supplied product layer, not the public exercise.
PREFERED_LINPHONE_SDK_RECIPE_VERSION = "latest"
PREFERRED_VERSION_linphone-sdk = "latest"
```

Рецепт получает Git-репозиторий с подмодулями через gitsm; в SRC_URI жёстко задана ветка main. Указаны AGPL-3.0-or-later и контрольная сумма LICENSE.txt. Рецепт наследует собственный класс cmakebuilder, cmake_qt5 и вспомогательные классы. Поскольку cmake_qt5 сам наследует cmake, перед объяснением фактической сборки нужно посмотреть итоговые do_configure, do_compile и do_install. Порядок наследования может влиять на выбранную реализацию задачи.

- Прямые зависимости включают Qt base/tools/QML controls/multimedia/Wayland, инструменты сборки для хоста, ALSA, PulseAudio, библиотеки TLS, XML, баз данных и кодеков.
- Значения PACKAGECONFIG по умолчанию: bzrtp, opus, sqlite, zlib, video, g2d, imxvpuh264, amr, tiff и zxing.
- Параметры CMake выбирают платформу Yocto, C++ wrapper, vCard, XML и несколько аудиокодеков; тесты включены.
- В CMake передаётся строка версии 5.3.0-alpha-175-g28018be13. Сама эта строка не определяет скачанный commit.
- Промежуточный префикс SDK — WORKDIR/build/linphone-sdk/desktop.
- Итоговый префикс на устройстве — /opt/belledonne-communications.
- При установке содержимое staging переносится в итоговый каталог; отдельные плагины и метаданные копируются при наличии.
- Рецепт создаёт файл ld.so.conf.d и объявляет рабочий, разработческий и отладочный пакеты.

Для оригинала нужны слой Qt и подходящие поставщики из BSP i.MX, помимо общих слоёв OpenEmbedded. Функции g2d и imxvpuh264 требуют imx-vpuwrap. Просто добавить этот слой в обычную сборку QEMU недостаточно. Отключение только PACKAGECONFIG video также не убирает безусловные зависимости Qt и кодеков из DEPENDS: минимальной аудиосборкой такой рецепт не становится.

Ниже точные выдержки из предоставленного рецепта. Они показывают реальные параметры, но не заменяют полный файл: намеренно опущены закрытый SRC_URI, остальные зависимости и функции установки. Сохраняем отдельно факт наличия этих настроек и предлагаемые улучшения из следующих разделов.

```bitbake
# Extracts from the supplied product recipe; not a standalone recipe.
S = "${WORKDIR}/git"
LICENSE = "AGPL-3.0-or-later"

inherit cmakebuilder gettext pkgconfig chrpath perlnative ${VERSION_DEPENDENT_INHERIT} cmake_qt5
inherit gitpkgv

PACKAGECONFIG ??= "bzrtp opus sqlite zlib video g2d imxvpuh264 amr tiff zxing"
PACKAGECONFIG[opus] = "-DENABLE_OPUS=YES, -DENABLE_OPUS=NO, libopus"
PACKAGECONFIG[imxvpuh264] = "-DENABLE_IMXVPUH264=YES, -DENABLE_IMXVPUH264=NO, imx-vpuwrap"
PACKAGECONFIG[g2d] = "-DENABLE_G2D=YES -DENABLE_VPU=YES, -DENABLE_G2D=NO, imx-vpuwrap"

EXTRA_OECMAKE += " -DLINPHONESDK_PLATFORM=Yocto"
EXTRA_OECMAKE += " -DLINPHONESDK_VERSION=5.3.0-alpha-175-g28018be13"
EXTRA_OECMAKE += " -DENABLE_UNIT_TESTS=YES -DENABLE_TESTS=YES"
EXTRA_OECMAKE += " -DCMAKE_SKIP_RPATH=YES"

BUILD_INSTALL_PREFIX = "${WORKDIR}/build/linphone-sdk/desktop"
INSTALL_PATH_OUT = "/opt/belledonne-communications"
INSTALL_PATH = ""
BUILD_INSTALL_PATH = "${BUILD_INSTALL_PREFIX}${INSTALL_PATH}"
OECMAKE_EXTRA_ROOT_PATH = "${BUILD_INSTALL_PATH}"

EXTRA_OECMAKE += " -DCMAKE_STAGING_PREFIX=${BUILD_INSTALL_PATH}"
EXTRA_OECMAKE += " -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH}"

PACKAGES = "${PN} ${PN}-dev ${PN}-dbg"
FILES:${PN} += "${INSTALL_PATH_OUT}/lib/*"
FILES:${PN}-dev = "${INSTALL_PATH_OUT}/include/*"
SYSROOT_DIRS += "/opt"
```

16. АУДИТ ОРИГИНАЛА: ЧТО ПРОВЕРИТЬ И ПОЧЕМУ

Ниже результаты чтения предоставленных файлов, а не завершённой сборки для устройства. Оригинал нужно сохранить, исправления делать в рабочей копии и проверять по этапам. Часть пунктов — конкретные ошибки метаданных; для остальных нужно посмотреть итоговые переменные или результат установки.

- AUDIT-01. Последнее правило называется ILES:${PN}: пропущена F. Оно не дополняет FILES. При этом стандартные правила FILES могут уже включать /etc, поэтому одна опечатка ещё не доказывает отсутствие belledonne.conf в пакете. Проверяем pkgdata.
- AUDIT-02. DEFAULT_COMMIT равен AUTOREV. Без явно заданного LINPHONE_SDK_REV даже при отключённом LATEST_REVISIONS остаётся плавающая ревизия. Один рецепт в разные дни может получить разные исходники.
- AUDIT-03. LINPHONE_SDK_BRANCH берётся из окружения, но SRC_URI содержит буквальное branch=main. Изменение переменной окружения не меняет ветку этого fetcher.
- AUDIT-04. В cmakebuilder есть FILES_${PN}-dev и OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM_class-native. Это старый синтаксис overrides. Для Kirkstone нужны FILES:${PN}-dev и OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM:class-native.
- AUDIT-05. zxing включён в PACKAGECONFIG, но PACKAGECONFIG[zxing] в предоставленном рецепте не объявлен. Это видно без доступа к исходникам SDK. Перед исправлением проверяем, не добавляется ли объявление другим .bbappend.
- AUDIT-06. LINPHONE_SDK_LIC_FILES_CHKSUM записывается в LIC_FILES_CHKSUM_ENV, а LIC_FILES_CHKSUM содержит отдельную фиксированную сумму. Значение из окружения с этим присваиванием не связано.
- AUDIT-07. В CMAKEOPTS записаны параметры версии, но предоставленный собственный класс передаёт EXTRA_OECMAKE. Перед выводом о влиянии CMAKEOPTS нужно проверить итоговые скрипты задач.
- AUDIT-08. В PACKAGES широкий рабочий пакет стоит первым, а его FILES включает целиком деревья lib и share внутри /opt. Ссылки для разработки, статические архивы, файлы CMake, pkg-config и отладочные каталоги могут попасть в рабочий пакет раньше, чем до них дойдут более точные пакеты.
- AUDIT-09. INSANE_SKIP отключает dev-so, staticdev, already-stripped и installed-vs-shipped. Это может скрывать ошибки упаковки и символов. Каждое исключение убираем после исправления причины и повторной сборки, а не все сразу вслепую.
- AUDIT-10. Копирование необязательных файлов и перенос staging используют проверки наличия или игнорирование ошибок. Поэтому успешная задача может не включить ожидаемый плагин или пропустить перенос. Для обязательных результатов нужны явные проверки наличия.
- AUDIT-11. Метаданные CMake и pkg-config из окружения сборки копируются в рабочий префикс. Они могут содержать пути хоста или описывать неправильное расположение файлов. Их нужно проверить; разработческие метаданные по возможности хранить в -dev.
- AUDIT-12. layer.conf присваивает LICENSE_FLAGS_ACCEPTED вместо дополнения политики продукта. Так можно затереть ранее разрешённые флаги. Переиспользуемый слой не должен молча определять лицензионную политику продукта.
- AUDIT-13. Обход ошибки Qt multimedia создаёт ссылку внутри RECIPE_SYSROOT. Нужны пояснение о затронутой комбинации Qt/BSP, проверка целевого каталога и регрессионный тест при смене этой комбинации.
- AUDIT-14. В сборке участвуют собственный и стандартный классы CMake. Нужно проверить, какая генерация toolchain и какая установка остаются после раскрытия метаданных; по одному файлу класса это не определить.

```bash
# Run from the existing phone build, with its normal layers enabled.
bitbake -p
bitbake -e linphone-sdk > linphone-sdk.environment.txt
grep -E '^(FILE|SRC_URI|SRCREV|DEFAULT_COMMIT|PACKAGECONFIG|PACKAGECONFIG_CONFARGS|PACKAGES|INSANE_SKIP:linphone-sdk|LIC_FILES_CHKSUM|EXTRA_OECMAKE|CMAKEOPTS)=' \
+    linphone-sdk.environment.txt

# Display expanded task bodies and their metadata comments.
sed -n '/^do_configure()/,/^}/p' linphone-sdk.environment.txt
sed -n '/^do_compile()/,/^}/p' linphone-sdk.environment.txt
sed -n '/^do_install()/,/^}/p' linphone-sdk.environment.txt
```

17. УПРАВЛЯЕМОЕ УЛУЧШЕНИЕ ОРИГИНАЛА

Сначала исправляем старый синтаксис overrides в рабочей копии cmakebuilder.bbclass под контролем версий: дополнение не сможет надёжно исправить класс, который не проходит разбор. В поддерживаемом рецепте исправляем ILES. Адрес исходников и согласованную ветку храним в закрытых метаданных продукта. Закрытый URI в публичную документацию не копируем.

```bitbake
# Corrected declarations in the maintained source files.
FILES:${PN}-dev += "${libdir}/cmake ${datadir}/cmake"
OECMAKE_FIND_ROOT_PATH_MODE_PROGRAM:class-native = "BOTH"
FILES:${PN}:append = " ${sysconfdir}/ld.so.conf.d/belledonne.conf"
```

В предоставленном рецепте существующий механизм переменных окружения позволяет закрепить исходники, не меняя закрытый URL. Ниже отдельный вход в существующую сборку телефона, а не продолжение enter-build.sh из раздела 03. Вводится проверенный полный commit из репозитория исходников. Команда проверяет формат, но не принадлежность ветке main: это проверит do_fetch при обращении к настроенному репозиторию.

```bash
read -r -p "Approved 40-character SDK commit: " phone_sdk_rev
if [[ ! "$phone_sdk_rev" =~ ^[0-9a-fA-F]{40}$ ]]; then
    printf '%s
' "A full Git commit is required" >&2
    return 1 2>/dev/null || exit 1
fi
export LINPHONE_SDK_REV="$phone_sdk_rev"
export PREFERED_LINPHONE_SDK_RECIPE_VERSION="latest"
unset LATEST_REVISIONS
export BB_ENV_PASSTHROUGH_ADDITIONS="${BB_ENV_PASSTHROUGH_ADDITIONS:-} LINPHONE_SDK_REV PREFERED_LINPHONE_SDK_RECIPE_VERSION"

# Now source the phone project's normal build-entry script.
# Do not source section 03's enter-build.sh: it deliberately clears this pin.
```

После входа в сборку продукта проверяем bitbake -e и загрузку исходников. Закрепляем родительский Git commit и сохраняем записанные в нём commits подмодулей. Строка версии и успешное клонирование эту запись не заменяют. Ветку main сохраняем, если согласованное изменение продукта не предусматривает другую.

ФАЙЛ: meta-phone/recipes-connectivity/linphone-sdk/linphone-sdk_latest.bbappend

```bitbake
# Product variant only. Replace the generic %.bbappend with this file;
# do not keep both examples active unintentionally.
FILES:${PN}:append = " ${sysconfdir}/ld.so.conf.d/belledonne.conf"

do_install:append() {
    test -d "${D}/opt/belledonne-communications/include/linphone" || \
+        bbfatal "Linphone headers were not installed"
    test -d "${D}/opt/belledonne-communications/lib" || \
+        bbfatal "Linphone library directory was not installed"
    find "${D}/opt/belledonne-communications/lib" -maxdepth 1 \
+        -name 'liblinphone.so*' -print -quit | grep -q . || \
+        bbfatal "liblinphone shared library was not installed"
    test -s "${D}${sysconfdir}/ld.so.conf.d/belledonne.conf" || \
+        bbfatal "Dynamic-loader configuration was not installed"
}
```

Это дополнение добавляет ранние проверки, но не исправляет весь аудит. Например, при упаковке точные разработческие файлы должны распределяться до широкого рабочего пакета, а обязательные плагины нужно проверять с учётом включённых функций. Сначала смотрим packages-split, затем вместе меняем PACKAGES и FILES. Переписывание вслепую может сломать нужное размещение плагинов.

18. ПАТЧИ И DEVTOOL

Для обычного рецепта приложения devtool упрощает цикл изменения, сборки и сохранения патча. Следующий необязательный пример меняет только наш локальный probe и не требует закрытых исходников SDK. Он добавляет сообщение на этапе configure, поэтому совместим с заменой main.cpp примером Core из раздела 21.

```bash
devtool modify linphone-probe
python3 - <<'PY'
from pathlib import Path
p = Path("workspace/sources/linphone-probe/CMakeLists.txt")
s = p.read_text()
message = 'message(STATUS "Building the phone SDK integration probe")'
assert message not in s
p.write_text(s + "\n" + message + "\n")
PY
git -C workspace/sources/linphone-probe add CMakeLists.txt
git -C workspace/sources/linphone-probe \
+    -c user.name="Example Author" -c user.email="example@example.org" \
+    commit -m "Describe the SDK probe during CMake configuration"
devtool build linphone-probe
devtool finish linphone-probe ../meta-phone
bitbake-layers show-appends
bitbake linphone-probe
```

Для SDK сначала смотрим дерево после распаковки и только затем выбираем место патча. gitsm получает записанные подмодули, но superbuild SDK может выполнять и собственные действия. Патч liblinphone относится к реальному каталогу этого компонента, а патч верхнего CMake SDK — к superbuild. Изменение сохраняем через git format-patch из того репозитория, где оно закоммичено, и проверяем пути внутри патча.

Механизм подключения — FILESEXTRAPATHS и запись файла в SRC_URI. Имя патча должно соответствовать реальному экспортированному файлу. Результат проверяем через do_patch, просмотр изменённого исходника и пересборку. Успех do_patch ещё не доказывает, что приложение использует именно этот компонент, а не другую копию из staging.

```bash
bitbake -c patch linphone-sdk
bitbake -e linphone-sdk | grep -E '^(S|T|SRC_URI)='
bitbake linphone-sdk linphone-probe
```

19. ПЕРЕНЕСТИ СОСТАВ ОБРАЗА В МЕТАДАННЫЕ ПРОДУКТА

Следующие необязательные файлы заменяют учебное добавление IMAGE_INSTALL в local.conf. Сначала создаём оба каталога. MACHINE, DISTRO и формат пакетов остаются в соответствующих настройках сборки или продукта. Здесь используется публичный вариант для QEMU; он не делает предоставленный рецепт i.MX переносимым на QEMU.

```bash
mkdir -p ../meta-phone/recipes-core/packagegroups
mkdir -p ../meta-phone/recipes-core/images
```

ФАЙЛ: meta-phone/recipes-core/packagegroups/packagegroup-phone-sdk.bb

```bitbake
SUMMARY = "Runtime packages for the SDK integration exercise"
LICENSE = "MIT"
inherit packagegroup
RDEPENDS:${PN} = "linphone-sdk linphone-probe"
```

ФАЙЛ: meta-phone/recipes-core/images/phone-sdk-image.bb

```bitbake
require recipes-core/images/core-image-minimal.bb
SUMMARY = "Minimal image with the Linphone SDK integration probe"
IMAGE_INSTALL:append = " packagegroup-phone-sdk"
```

```bash
bitbake phone-sdk-image
runqemu qemuarm64 phone-sdk-image nographic slirp
```

Packagegroup даёт одно поддерживаемое место для связанных рабочих пакетов. Рецепт образа определяет состав продукта. Заголовки для разработки по умолчанию не устанавливаются. После переключения образа используем phone-sdk-image при проверке manifest, запуске QEMU и генерации внешнего SDK.

20. НЕОБЯЗАТЕЛЬНЫЙ ПРОВЕРОЧНЫЙ СЕРВИС SYSTEMD

Расширение используется только в сборке, уже настроенной на systemd. core-image-minimal может использовать другую init-систему; добавление unit-файла не переключает её на systemd. Наш probe завершается после короткой проверки, поэтому ему подходит oneshot. Постоянно работающее приложение телефона имеет другой жизненный цикл сервиса.

ФАЙЛ: meta-phone/recipes-apps/linphone-probe/files/linphone-probe.service

```ini
[Unit]
Description=Linphone SDK integration check

[Service]
Type=oneshot
Environment=LD_LIBRARY_PATH=/opt/belledonne-communications/lib
ExecStart=/usr/bin/linphone-probe

[Install]
WantedBy=multi-user.target
```

ФАЙЛ: meta-phone/recipes-apps/linphone-probe/linphone-probe_1.0.bbappend

```bitbake
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append = " file://linphone-probe.service"
inherit systemd
SYSTEMD_SERVICE:${PN} = "linphone-probe.service"
SYSTEMD_AUTO_ENABLE:${PN} = "disable"

do_install:append() {
    install -d "${D}${systemd_system_unitdir}"
    install -m 0644 "${WORKDIR}/linphone-probe.service"         "${D}${systemd_system_unitdir}/linphone-probe.service"
}
```

Если devtool уже создал это дополнение, добавляем настройки сервиса в него и сохраняем записи патчей. Unit попадёт в пакет, но не включится автоматически. После пересборки и установки образа запускаем его вручную и проверяем результат. Успешно завершившийся oneshot обычно становится inactive; само по себе это не ошибка. Для рабочего сервиса телефона отдельно проектируются доступность сети, доступный для записи каталог настроек, права на устройства и корректная остановка Core.

```bash
# Run on a systemd-based target after image deployment.
systemctl start linphone-probe.service
systemctl status linphone-probe.service --no-pager
systemctl show linphone-probe.service -p Result -p ExecMainStatus
journalctl -u linphone-probe.service -b --no-pager
```

21. БОЛЕЕ ПОЛНАЯ БЫСТРАЯ ПРОВЕРКА: СОЗДАТЬ И ЗАПУСТИТЬ CORE

После успешного простого вывода версии можно заменить main.cpp этим необязательным примером. Он проверяет создание Core, запуск, обработку событий, остановку и освобождение через API 5.3. Регистрации аккаунта и медиасеанса RTP здесь ещё нет. Учётные данные SIP не нужны.

```cpp
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <linphone/core.h>
#include <linphone/api/c-factory.h>

int main()
{
    using CorePtr = std::unique_ptr<LinphoneCore, decltype(&linphone_core_unref)>;
    CorePtr core(linphone_factory_create_core_3(
        linphone_factory_get(), nullptr, nullptr, nullptr), &linphone_core_unref);

    if (!core) {
        std::cerr << "Core creation failed\n";
        return 1;
    }
    if (linphone_core_start(core.get()) != 0) {
        std::cerr << "Core startup failed\n";
        return 2;
    }

    for (int i = 0; i < 50; ++i) {
        linphone_core_iterate(core.get());
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    linphone_core_stop(core.get());
    std::cout << "Core startup and shutdown check completed\n";
    return 0;
}
```

Следующие две строки добавляются в CMakeLists.txt после add_executable. Существующую линковку с liblinphone сохраняем. Threads::Threads передаёт нужные для платформы параметры потоков вместо жёстко заданного флага компилятора хоста.

```cmake
find_package(Threads REQUIRED)
target_link_libraries(linphone-probe PRIVATE Threads::Threads)
```

В приложении Qt один владеющий поток должен управлять Core и регулярно вызывать iterate, например через QTimer с интервалом по рекомендациям SDK. Обновление интерфейса из callback передаётся в правильный поток UI. Наличие таймера само по себе не обеспечивает потокобезопасность: нужны понятное владение объектами, обработка callback и порядок остановки. Нельзя параллельно крутить независимый iterate для того же Core в другом потоке.

Предупреждения об отсутствии звукового устройства или камеры в QEMU не означают автоматически ошибку линковки. Проверяем реальный результат запуска Core и читаем лог. На телефоне дополнительно проверяются плагины кодеков и аудиоустройства; из нулевого кода завершения этой программы их работоспособность не следует.

22. ВНЕШНИЙ SDK ДЛЯ РАЗРАБОТКИ ПРИЛОЖЕНИЯ

Образ содержит рабочие файлы, а внешнему SDK нужны ещё заголовки, ссылки для линковки и инструменты сборки для хоста. Сначала смотрим реальные имена пакетов. В предоставленном оригинале linphone-sdk-dev объявлен явно. Другие версии рецепта могут распределять файлы иначе.

```bash
oe-pkgdata-util list-pkgs 'linphone-sdk*'
oe-pkgdata-util list-pkg-files linphone-sdk-dev
```

Если такой разработческий пакет существует, добавляем следующие настройки перед генерацией стандартного SDK. Заголовки от этого не устанавливаются в образ телефона. При собственном префиксе /opt обязательно проверяем целевой sysroot получившегося SDK: одного имени пакета недостаточно.

```bitbake
TOOLCHAIN_TARGET_TASK:append = " linphone-sdk-dev"
TOOLCHAIN_HOST_TASK:append = " nativesdk-cmake nativesdk-ninja"
```

```bash
# In the Yocto build shell. Use phone-sdk-image if section 19 is active.
bitbake -c populate_sdk core-image-minimal
find tmp/deploy/sdk -maxdepth 1 -type f -name '*.sh' -print

# Select the installer just generated for this host, image and architecture.
read -r -p "Generated SDK installer path: " sdk_installer
test -f "$sdk_installer" &&     bash "$sdk_installer" -d "$HOME/phone-cross-sdk"
```

Для установленного toolchain открываем новую оболочку и не смешиваем её с окружением BitBake. Команда ниже ожидает ровно один файл environment-setup и явно проверяет это условие. SDK и установленный образ должны относиться к одной совместимой версии продукта.

```bash
mapfile -t sdk_envs < <(find "$HOME/phone-cross-sdk" -maxdepth 1     -type f -name 'environment-setup-*' | sort)
if (( ${#sdk_envs[@]} != 1 )); then
    printf '%s\n' "Expected exactly one installed target environment" >&2
    return 1 2>/dev/null || exit 1
fi
source "${sdk_envs[0]}"

test -f "$SDKTARGETSYSROOT/opt/belledonne-communications/include/linphone/linphonecore.h"
find "$SDKTARGETSYSROOT/opt/belledonne-communications/lib"     -maxdepth 1 -name 'liblinphone.so*' -print

cmake -S "$HOME/yocto-linphone-lab/meta-phone/recipes-apps/linphone-probe/files" \
+    -B "$HOME/linphone-probe-cross-build" -G Ninja \
+    -DCMAKE_TOOLCHAIN_FILE="$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake" \
+    -DLINPHONE_SDK_ROOT="$SDKTARGETSYSROOT/opt/belledonne-communications"
cmake --build "$HOME/linphone-probe-cross-build" --verbose
```

Полученный ARM-бинарник не запускаем на хосте сборки. Внешняя сборка ускоряет разработку приложения, но выпуск пакета всё равно должен идти через рецепт: так сохраняется контроль зависимостей, контрольных сумм и состава образа.

23. ДИАГНОСТИРОВАТЬ КОНКРЕТНЫЙ ЭТАП ОШИБКИ

При ошибке загрузки начинаем с доступа к репозиторию, выбранной ревизии, ветки и подмодулей. При ошибке configure смотрим первую недостающую зависимость и сформированную команду CMake. Целевая библиотека не заменяет отсутствующий инструмент для хоста. При ошибке компиляции ищем первое реальное сообщение компилятора, а не только итоговую сводку задачи.

```bash
# Run from build/. Output paths are obtained from BitBake, not guessed.
bitbake -e linphone-sdk > linphone-sdk.environment.txt
sdk_logs=$(sed -n 's/^T="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
sdk_work=$(sed -n 's/^WORKDIR="\(.*\)"$/\1/p' linphone-sdk.environment.txt)
find "$sdk_logs" -maxdepth 1 -name 'log.do_*' -print
find "$sdk_work/packages-split" -name 'liblinphone.so*' -print
find "$sdk_work/packages-split" -name 'belledonne.conf' -print

bitbake -e linphone-probe > linphone-probe.environment.txt
probe_sysroot=$(sed -n 's/^RECIPE_SYSROOT="\(.*\)"$/\1/p' linphone-probe.environment.txt)
find "$probe_sysroot/opt/belledonne-communications"     -name 'linphonecore.h' -o -name 'liblinphone.so*'
oe-pkgdata-util find-path /usr/bin/linphone-probe
oe-pkgdata-util find-path /etc/ld.so.conf.d/belledonne.conf
```

После линковки проверяем целевой ELF через readelf из devshell или установленного cross-SDK. Список требуемых библиотек, архитектура и RPATH/RUNPATH — разные проверки. В исполняемом файле этого примера не должно быть путей build/tmp. Запись DT_NEEDED говорит, что библиотека требуется, но не доказывает, что загрузчик устройства её найдёт.

```bash
# In the installed cross-SDK shell after section 22.
probe_elf="$HOME/linphone-probe-cross-build/linphone-probe"
test -f "$probe_elf"
$READELF -h "$probe_elf"
$READELF -d "$probe_elf" | grep -E 'NEEDED|RPATH|RUNPATH'
```

На телефоне сначала проверяем наличие файлов и корректность ссылок. В образе с glibc запись ld.so.conf.d может использоваться при создании или обновлении кэша загрузчика. Сам факт записи файла ещё не означает, что кэш обновился. В этом примере LD_LIBRARY_PATH для конкретного сервиса позволяет не зависеть от глобальной настройки загрузчика. У musl правила конфигурации другие.

Если не находится плагин кодека, проверяем его пакет, каталог, правила поиска плагинов SDK и собственные зависимости этого .so. Наличия файла недостаточно, если отсутствует одна из его библиотек. Нельзя переносить случайные .so с рабочего компьютера или другой версии: должны совпадать архитектура, ABI и настройки кодеков.

24. ПОВТОРЯЕМОСТЬ СБОРКИ И CI

Для выпуска сохраняем не только строку версии: нужны commits слоёв, локальные патчи, родительский commit SDK и commits подмодулей, MACHINE, DISTRO, конфигурация toolchain, включённые функции, лицензионные суммы и manifests образа и пакетов. Оригинальному рецепту latest особенно важно явно задать ревизию. Эти записи храним вместе с артефактами выпуска.

```bitbake
# Optional shared caches in the learning workspace.
DL_DIR = "${TOPDIR}/../shared-downloads"
SSTATE_DIR = "${TOPDIR}/../shared-sstate"
```

Кэш загрузки избавляет от повторного получения одинаковых исходников. Shared-state повторно использует совместимые результаты задач по их сигнатурам. Ни один кэш не заменяет архив выпуска и закреплённые входные данные. Для собственного superbuild проверяем, что внутренние загрузки и изменения настроек учитываются в модели сборки; иначе внешне удобный кэш может скрывать неконтролируемые исходники.

Практический CI сначала разбирает метаданные, затем собирает SDK и приложение, выполняет проверки упаковки, собирает образ, запускает проверку версии и Core в QEMU там, где это поддерживается, и тестирует телефон на железе. Сохраняем точные manifests и нужные логи задач. Учётные данные репозиториев не помещаем в рецепты, полные дампы окружения не публикуем.

25. ПАКЕТЫ ВЫПУСКА И ОБНОВЛЕНИЯ ТЕЛЕФОНА

Файл .ipk, созданный Yocto, — артефакт пакетного менеджера. Он сам по себе ещё не является безопасным обновлением телефона с откатом. Если в продукте .NET Autoprovisioning Manager собирает частичные пакеты для конкретных телефонов, пакет формируется из проверенных артефактов выпуска после получения фактической версии телефона. SDK не пересобирается отдельно для каждого аппарата.

Изменение библиотеки может требовать совместного обновления приложения, плагинов SDK и связанных настроек. Сравниваем manifests выпусков и реальные хеши файлов, а не только время изменения. Версионная библиотека и ссылки на неё должны оставаться согласованными. Явно отмечаем добавления, замены и удаления. До остановки сервиса проверяем ожидаемую исходную версию и свободное место.

Для отката по файлам сохраняем исходные затрагиваемые файлы и метаданные, надёжно записываем журнал обратных операций, затем безопасно выполняем замену. После перезапуска проверяем версию и содержательные признаки работоспособности телефона. При неудаче восстанавливаем заменённые и удалённые файлы, убираем новые, возвращаем метаданные и проверяем предыдущую версию. Восстановление после пропадания питания должно выполняться до обычного приложения телефона. Это задача системы обновления; DEPENDS и BitBake её автоматически не решают.

26. КРИТЕРИИ ПРИЁМКИ И ОТВЕТ НА СОБЕСЕДОВАНИИ

- ACCEPT-01. Выбраны нужный рецепт SDK и дополнение; все требуемые слои подключены.
- ACCEPT-02. Ревизия SDK и ревизии подмодулей записаны.
- ACCEPT-03. Итоговые задачи CMake используют целевой toolchain и ожидаемые функции.
- ACCEPT-04. В D есть установленные заголовки, рабочие библиотеки и обязательные плагины.
- ACCEPT-05. Приложение получает SDK через sysroot своего рецепта, а не через пути хоста.
- ACCEPT-06. Состав рабочих и разработческих пакетов соответствует назначению; исключения QA узкие и обоснованные.
- ACCEPT-07. Manifest образа содержит рабочие пакеты.
- ACCEPT-08. Загрузчик устройства находит liblinphone и зависимости без путей хоста сборки.
- ACCEPT-09. Проверки версии и Core успешно завершаются в поддерживаемой среде.
- ACCEPT-10. На железе проверены регистрация, оба направления звонка, двусторонний звук, hold/resume, завершение вызова, потеря сети и переключение сервера.
- ACCEPT-11. Видеовариант дополнительно проходит проверку камеры, включённых кодеков и загрузки плагинов.
- ACCEPT-12. Тест обновления и отката возвращает точный предыдущий совместимый комплект ПО.

ОБЪЯСНЕНИЕ ИНТЕГРАЦИИ НА СОБЕСЕДОВАНИИ

Готовая основа Yocto давала сборку операционной системы, а интеграцию Linphone SDK добавляла команда. Я бы объяснил работу тремя частями: собрать SDK для телефона, дать приложению возможность с ним собраться и установить на устройство рабочий комплект ПО. В предоставленном рецепте видны практические механизмы: исходники с подмодулями, зависимости Qt и кодеков, кросс-сборка CMake, промежуточный staging и итоговая установка в /opt/belledonne-communications.

На этапе сборки приложение зависит от рецепта SDK, поэтому Yocto подготавливает его заголовки и библиотеки в sysroot приложения. Для запуска образ должен содержать библиотеки SDK и нужные плагины, а загрузчик — знать их расположение. Сначала я бы проверил маленькую программу с выводом версии, затем запуск Core и только потом регистрацию и звонки на реальном телефоне. Успешная компиляция — лишь начало: звук, изменения сети и плагины проверяются на устройстве.

Замечания этого руководства относятся к предоставленному снимку. Они не доказывают, когда появилась каждая строка, с какой конфигурацией собирался исторический выпуск и кто лично написал каждое изменение рецепта. В техническом рассказе нужно различать интеграцию команды и собственную работу, а предложенные исправления не представлять как уже внедрённые.

27. ИСТОЧНИКИ И ЛОКАЛЬНЫЙ СНИМОК

Дата проверки: 2026-11-15.

- Официальное руководство по интеграции Linphone в Yocto: https://wiki.linphone.org/xwiki/wiki/public/view/Linphone/Building%20Linphone%20with%20Yocto/
- Официальный слой рецептов для Kirkstone: https://gitlab.linphone.org/BC/public/meta-bc/-/tree/feature/yocto-kirkstone
- Требования Yocto к хосту сборки: https://docs.yoctoproject.org/4.0.30/ref-manual/system-requirements.html
- Создание слоёв: https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html
- Написание рецептов: https://docs.yoctoproject.org/4.0.30/dev-manual/new-recipe.html
- SYSROOT_DIRS и переменные рецептов: https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html#term-SYSROOT_DIRS
- Диагностика задач: https://docs.yoctoproject.org/4.0.30/dev-manual/debugging.html
- Запуск QEMU: https://docs.yoctoproject.org/4.0.30/dev-manual/qemu.html
- Объявление API версии liblinphone: https://github.com/BelledonneCommunications/liblinphone/blob/master/include/linphone/core.h
- Общая лицензия MIT из Kirkstone для учебного кода: https://git.yoctoproject.org/poky/tree/meta/files/common-licenses/MIT?h=kirkstone

Дополнительные официальные источники:

- Задачи рецептов: https://docs.yoctoproject.org/4.0.30/ref-manual/tasks.html

- Проверки QA: https://docs.yoctoproject.org/4.0.30/ref-manual/qa-checks.html

- Синтаксис overrides для Kirkstone: https://docs.yoctoproject.org/4.0.30/migration-guides/migration-3.4.html#override-syntax-changes

- Работа с devtool: https://docs.yoctoproject.org/4.0.30/sdk-manual/extensible.html

- Окружение внешнего toolchain: https://docs.yoctoproject.org/4.0.30/sdk-manual/working-projects.html

- Toolchain в CMake: https://cmake.org/cmake/help/v3.22/manual/cmake-toolchains.7.html

- Класс CMake для Qt: https://github.com/meta-qt5/meta-qt5/blob/kirkstone/classes/cmake_qt5.bbclass

- API Core, 5.3.0: https://github.com/BelledonneCommunications/liblinphone/blob/5.3.0/include/linphone/core.h

- API Factory, 5.3.0: https://github.com/BelledonneCommunications/liblinphone/blob/5.3.0/include/linphone/api/c-factory.h

- Типы сервисов; в примере используются давно поддерживаемые параметры oneshot: https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html

Контрольные суммы локального снимка, SHA-256; проверено 2026-11-15:

```text
linphone-sdk_latest.bb
f49269e21074e27240bffca2450c98830a5d0d384f517472cc76c9635018161e
cmakebuilder.bbclass
33c0cf2cce41c33105639c2245874dbe47b45e60f0dc97e2172d37a1c65190bb
conf/layer.conf
2a5e1f0d2de89bf4b9e5082afac697de406a36d317ce940fac1f1fde18a57ba7
```
