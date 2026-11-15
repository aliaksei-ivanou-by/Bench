LINPHONE SDK IN YOCTO: PRACTICAL INTEGRATION EXAMPLE
LINPHONE SDK В YOCTO: ПРАКТИЧЕСКИЙ ПРИМЕР ИНТЕГРАЦИИ

01. PURPOSE / НАЗНАЧЕНИЕ

RU: Ниже один учебный пример целиком: подключаем официальный слой с рецептом SDK, добавляем свои настройки и собираем маленькую C++-программу, которая использует liblinphone. Затем включаем оба компонента в Linux-образ и проверяем запуск. Это пример реализации, а не копия исторического рецепта проекта.

EN: This complete learning example adds the official SDK recipe layer, applies project settings and builds a small C++ program using liblinphone. It then includes both components in a Linux image and checks execution. It illustrates an implementation rather than reproducing the project's historical recipe.

RU: Команды выполняются в Bash на Linux-хосте, подготовленном для Yocto Kirkstone. Windows PowerShell для сборки не подходит. Для самостоятельного упражнения выбран qemuarm64. В существующем проекте телефона сохраняются его MACHINE, BSP, DISTRO и рецепт образа. Подмена их конфигурацией QEMU не нужна. Полная сборка этого примера здесь не выполнялась; настройки сверены с официальными источниками, перечисленными в конце.

EN: Run the commands in Bash on a Linux host prepared for Yocto Kirkstone. Windows PowerShell is not a suitable build environment. The standalone exercise uses qemuarm64. An existing phone product keeps its own MACHINE, BSP, DISTRO and image recipe instead of adopting the QEMU configuration. This example has not been built here; its settings were checked against the official sources listed below.

02. THE INTEGRATION PATH / КАК СВЯЗАНЫ КОМПОНЕНТЫ

- meta-bc: upstream recipes for Linphone SDK / готовые рецепты SDK.
- meta-phone: our settings and application recipe / наши настройки и рецепт приложения.
- linphone-sdk: builds and packages the SDK / собирает и упаковывает SDK.
- linphone-probe: links a C++ executable to liblinphone / связывает C++-программу с liblinphone.
- core-image-minimal: includes the runtime packages / включает пакеты в образ.

RU: Рецепт SDK берём из официального meta-bc, а изменения храним в собственном слое через .bbappend. SDK состоит из нескольких компонентов; upstream-рецепт содержит особенности их сборки. Поэтому здесь нет упрощённого выдуманного рецепта всего SDK с несколькими универсальными CMake-флагами. Полный собственный .bb ниже относится к приложению, а .bbappend дополняет настоящий рецепт SDK.

EN: Use the SDK recipe from the official meta-bc layer and keep project changes in a separate layer through a .bbappend. The SDK contains several components, and the upstream recipe handles their build details. This example therefore does not invent a short universal SDK recipe with guessed CMake flags. The complete custom .bb below builds the application; the .bbappend extends the actual SDK recipe.

03. CHECK OUT THE LAYERS / ПОЛУЧИТЬ СЛОИ

RU: Начинаем в новом каталоге. На хосте уже должны быть установлены зависимости сборки из Yocto System Requirements. Команды ниже не устанавливают их автоматически.

EN: Start in a new directory on a host with the build dependencies from Yocto System Requirements already installed. These commands do not install the host dependencies.

```bash
mkdir -p "$HOME/yocto-linphone-lab"
cd "$HOME/yocto-linphone-lab"

git clone --branch kirkstone https://git.yoctoproject.org/poky
git clone --branch kirkstone https://git.openembedded.org/meta-openembedded
git clone --branch feature/yocto-kirkstone \
    https://gitlab.linphone.org/BC/public/meta-bc.git

cat > enter-build.sh <<'EOF'
export PREFERED_LINPHONE_SDK_RECIPE_VERSION="5.3.x"
export BB_ENV_PASSTHROUGH_ADDITIONS="${BB_ENV_PASSTHROUGH_ADDITIONS:-} PREFERED_LINPHONE_SDK_RECIPE_VERSION"
unset LATEST_REVISIONS
unset LINPHONE_SDK_REV LINPHONE_SDK_BRANCH
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

RU: Имя PREFERED_LINPHONE_SDK_RECIPE_VERSION действительно содержит одну R в PREFERED: так переменная называется у upstream. Значение 5.3.x выбирает семейство рецепта; точный исходный commit определяется выбранными метаданными. Это не утверждение о версии SDK в реальном проекте. Новая сессия начинается из корня yocto-linphone-lab командой source enter-build.sh; после неё текущий каталог — build.

EN: PREFERED_LINPHONE_SDK_RECIPE_VERSION intentionally has one R in PREFERED: this is the upstream variable name. The value 5.3.x selects a recipe family; the selected metadata determines the exact source commit. It does not establish the SDK version used in the real project. In a new session, run source enter-build.sh from yocto-linphone-lab; it changes the current directory to build.

04. EXTEND THE SDK RECIPE / ДОПОЛНИТЬ РЕЦЕПТ SDK

FILE: meta-phone/recipes-connectivity/linphone-sdk/linphone-sdk_%.bbappend

```bitbake
# Keep this learning example audio-only.
PACKAGECONFIG:remove = "video h264"

# The upstream SDK uses a non-standard installation prefix.
# Make headers and libraries available to dependent recipes.
SYSROOT_DIRS:append = " /opt/belledonne-communications"
```

RU: Создай файл по указанному пути. Все пути FILE отсчитываются от корня yocto-linphone-lab. Остальные команды выполняются из build. Символ % позволяет применить дополнение к выбранной версии рецепта linphone-sdk. Проверка show-appends ниже должна показать фактическое соответствие.

EN: Create the file at the path shown. All FILE paths are relative to yocto-linphone-lab; the remaining commands run from build. The % matches the selected linphone-sdk recipe version. The show-appends check below must confirm that the append applies.

RU: Видео отключено только для простого упражнения. Для видеотелефона его оставляют включённым и отдельно проверяют кодеки, устройства и лицензии. SYSROOT_DIRS нужен потому, что /opt не является обычным каталогом библиотек Yocto. Это доступность файлов при сборке другого рецепта, а не включение пакета в образ. SDK сохраняет собственные LICENSE и LIC_FILES_CHKSUM из upstream; не заменяем их на CLOSED или MIT.

EN: Video is disabled only to simplify the exercise. A video phone keeps it enabled and separately validates codecs, devices and licensing. SYSROOT_DIRS is needed because /opt is outside Yocto's usual library locations. It makes files available when another recipe builds; it does not install a package into the image. Keep the SDK's upstream LICENSE and LIC_FILES_CHKSUM rather than replacing them with CLOSED or MIT.

05. A SMALL C++ APPLICATION / МАЛЕНЬКОЕ C++-ПРИЛОЖЕНИЕ

FILE: meta-phone/recipes-apps/linphone-probe/files/main.cpp

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

RU: Программа проверяет наличие заголовков, линковку и загрузку библиотеки. Она не создаёт SIP-аккаунт и не подтверждает работу звонков. Такой короткий тест помогает сначала отделить проблемы интеграции SDK от проблем приложения.

EN: The program checks header availability, linking and library loading. It does not create a SIP account or prove that calls work. This small test separates SDK integration problems from application behavior.

FILE: meta-phone/recipes-apps/linphone-probe/files/CMakeLists.txt

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

RU: Путь к SDK поступает из рецепта. Ищем библиотеку только внутри целевого sysroot, чтобы случайно не взять библиотеку Linux-хоста. Флаг rpath-link помогает линкеру найти зависимости liblinphone во время сборки. Он не настраивает поиск библиотек на телефоне: это проверим отдельно при запуске.

EN: The recipe supplies the SDK path. Searching only inside the target sysroot prevents accidental use of host libraries. The rpath-link option helps the linker find liblinphone dependencies during the build. It does not configure library lookup on the phone; runtime lookup is checked separately.

06. THE APPLICATION RECIPE / РЕЦЕПТ ПРИЛОЖЕНИЯ

FILE: meta-phone/recipes-apps/linphone-probe/linphone-probe_1.0.bb

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

RU: MIT здесь относится к нашему учебному коду. Использование liblinphone сохраняет отдельные лицензионные обязательства SDK. Для промышленного продукта проверяются лицензии всей выбранной сборки, включая кодеки.

EN: MIT describes our example code. Using liblinphone retains the SDK's separate licensing obligations. A production product reviews the complete selected build, including codecs.

- DEPENDS: SDK headers and libraries are prepared before compilation / заголовки и библиотеки SDK доступны до компиляции.
- RDEPENDS: the runtime SDK package accompanies the executable / пакет SDK устанавливается вместе с приложением.
- inherit cmake: Yocto supplies the cross-toolchain and runs configuration, compilation and installation / Yocto передаёт кросс-компилятор и выполняет настройку, сборку и установку.
- do_install: CMake installs into the recipe's staging directory through DESTDIR / CMake устанавливает результат во временный каталог рецепта через DESTDIR.
- FILES: the standard package rules already cover /usr/bin/linphone-probe / стандартные правила упаковки уже покрывают /usr/bin/linphone-probe.

07. IMAGE CONFIGURATION / НАСТРОЙКА ОБРАЗА

RU: Добавь строки в существующий build/conf/local.conf один раз. Не заменяй весь файл. debug-tweaks нужен только для входа в локальный учебный QEMU-образ без пароля; в образ телефона эта настройка не переносится.

EN: Add these lines to the existing build/conf/local.conf once, without replacing the file. debug-tweaks permits passwordless access to the local learning image; do not carry it into the phone image.

```bitbake
MACHINE = "qemuarm64"
PACKAGE_CLASSES = "package_ipk"
EXTRA_IMAGE_FEATURES:append = " debug-tweaks"
IMAGE_INSTALL:append = " linphone-sdk linphone-probe"
```

RU: В продукте IMAGE_INSTALL лучше хранить в собственном рецепте образа или packagegroup. Здесь local.conf делает пример короче. DEPENDS не заменяет IMAGE_INSTALL: успешная сборка библиотеки ещё не означает, что она попала на устройство. Пакеты заголовков -dev и отладочные -dbg также не нужны в обычном рабочем образе.

EN: A product normally keeps image contents in its own image recipe or packagegroup. This example uses local.conf for brevity. DEPENDS does not replace IMAGE_INSTALL: a successfully built library is not necessarily installed on the device. Header packages ending in -dev and debug packages ending in -dbg are also unnecessary in a normal runtime image.

08. INSPECT AND BUILD / ПРОВЕРИТЬ И СОБРАТЬ

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

RU: До сборки смотрим, какой .bb реально выбран, какие исходники он скачивает и применился ли наш .bbappend. Для воспроизводимости сохраняем commit каждого слоя, свои изменения meta-phone и точные исходные ревизии SDK. Одной записи 5.3.x недостаточно. Если upstream использует плавающие ревизии или скачивает дополнительные исходники внутри сборки, их тоже нужно закрепить; layers.lock.txt сам по себе этого не делает. Полный вывод bitbake -e оставляем локально: он содержит пути и окружение сборки.

EN: Before building, inspect the selected .bb, its sources and the applied .bbappend. Reproducibility requires layer commits, our meta-phone changes and exact SDK source revisions. Recording only 5.3.x is insufficient. If upstream uses floating revisions or fetches additional sources during compilation, pin those too; layers.lock.txt alone does not do that. Keep the full bitbake -e output local because it contains build paths and environment data.

RU: В linphone-sdk должны быть рабочие библиотеки из /opt/belledonne-communications; в linphone-probe — /usr/bin/linphone-probe. Если upstream распределил библиотеки по отдельным пакетам, проверяем их имена через pkgdata и корректируем RDEPENDS по фактическому результату. Не добавляем все -dev пакеты в образ ради обхода ошибки упаковки.

EN: The SDK package should provide runtime libraries under /opt/belledonne-communications, and linphone-probe should provide /usr/bin/linphone-probe. If upstream splits libraries into additional packages, inspect their names using pkgdata and adjust RDEPENDS to match the actual output. Do not add every -dev package to the image to conceal packaging errors.

09. RUN THE IMAGE / ЗАПУСТИТЬ ОБРАЗ

BUILD HOST / ХОСТ СБОРКИ:

```bash
runqemu qemuarm64 core-image-minimal nographic slirp
```

GUEST CONSOLE, LOG IN AS root / КОНСОЛЬ ГОСТЯ, ВХОД root:

```bash
ls -l /opt/belledonne-communications/lib/liblinphone.so*
LD_LIBRARY_PATH=/opt/belledonne-communications/lib \
    /usr/bin/linphone-probe
```

RU: Ожидаем строку Linphone SDK version: и номер реально собранной версии. LD_LIBRARY_PATH задаётся только для этого процесса. В рабочем телефоне путь задаётся для сервиса приложения либо через конфигурацию загрузчика библиотек, если выбранная libc её поддерживает. Не записываем путь build/tmp/... в конфигурацию устройства. Выход из QEMU: Ctrl+A, затем X.

EN: Expect Linphone SDK version: followed by the actual built version. LD_LIBRARY_PATH applies only to this process. A phone configures the path for its application service or through the dynamic loader configuration when supported by its libc. Never put build/tmp/... paths into device configuration. Exit QEMU with Ctrl+A followed by X.

10. DEVELOPMENT COMMANDS / КОМАНДЫ ДЛЯ РАЗРАБОТКИ

```bash
# Run a specific stage and inspect the task output.
bitbake -c fetch linphone-sdk
bitbake -c unpack linphone-sdk
bitbake -c configure linphone-sdk

# Print paths to source, build directory and task logs.
bitbake -e linphone-sdk | grep -E '^(S|B|T|WORKDIR)='

# Open the recipe's development shell.
bitbake -c devshell linphone-sdk

# Rebuild after changing the application files or metadata.
bitbake linphone-probe
bitbake core-image-minimal

# Inspect the final application configuration and sysroot location.
bitbake -e linphone-probe | \
    grep -E '^(RECIPE_SYSROOT|DEPENDS|RDEPENDS:linphone-probe|EXTRA_OECMAKE)='

# Optional: generate an external cross-development SDK for this image.
bitbake -c populate_sdk core-image-minimal
```

RU: devshell открывает отдельную оболочку. Командой exit возвращаемся в исходную оболочку перед остальными командами. Логи находятся в каталоге T: log.do_configure, log.do_compile и log.do_install. Обычное изменение рецепта или локального исходника подхватывается повторным bitbake. Постоянно выполнять cleanall не нужно: он удаляет скачанные исходники и мешает использовать кэш.

EN: devshell opens a separate shell; use exit before continuing in the original shell. The T directory contains log.do_configure, log.do_compile and log.do_install. Running bitbake again normally detects recipe and local source changes. Routine cleanall calls are unnecessary: they delete downloaded sources and defeat caching.

RU: Для своего изменения SDK сначала смотрим SRC_URI и S выбранного рецепта. Если нужный файл находится в дереве, которое обрабатывает do_patch, патч храним в своём слое, добавляя FILESEXTRAPATHS:prepend := "${THISDIR}/files:" и SRC_URI:append = " file://имя-патча.patch". Если компонент скачивается позже внутренней сборкой SDK, обычный do_patch может его ещё не видеть. В таком случае применяем предусмотренный upstream способ либо используем закреплённый fork компонента. Сам факт существования .bbappend не гарантирует, что патч попадёт в нужный submodule.

EN: For an SDK change, inspect SRC_URI and S first. If the affected file is in the source tree handled by do_patch, keep the patch in the project layer and add FILESEXTRAPATHS:prepend := "${THISDIR}/files:" plus a file URI in SRC_URI:append. If the SDK's internal build downloads the component later, ordinary do_patch may run before that component exists. Use the upstream mechanism or a pinned component fork in that case. Having a .bbappend alone does not ensure that a patch reaches the correct submodule.

11. COMMON FAILURES / ТИПИЧНЫЕ ОШИБКИ

- No recipes available for .bbappend: check the selected recipe name and version with show-recipes / проверить имя и версию основного рецепта.
- Header not found: check DEPENDS, do_populate_sysroot and the /opt directory in the consumer's RECIPE_SYSROOT / проверить зависимость и наличие заголовков в sysroot приложения.
- Cannot find -llinphone: check that the target library and linker symlink exist in the searched lib directory / проверить целевую библиотеку и ссылку, используемую при линковке.
- Shared library not found at runtime: check installed packages and the device loader search path / проверить пакеты в образе и путь поиска библиотек на устройстве.
- Wrong architecture or file format: check MACHINE and the compiler command; do not copy host libraries into the image / проверить MACHINE и кросс-компилятор, исключить библиотеки хоста.
- Installed but not shipped: inspect the upstream package split and add the precise missing path to the correct package's FILES / проверить разбиение по пакетам и добавить конкретный путь в FILES нужного пакета.
- License or codec configuration failure: inspect the exact recipe requirement rather than accepting every commercial flag globally / разобраться с конкретной лицензией вместо общего разрешения всех commercial-флагов.

12. WHAT THIS PROVES / ЧТО ИМЕННО ПРОВЕРИЛИ

RU: После успешного запуска знаем, что Yocto собрал SDK для нужной архитектуры, приложение получило его заголовки и библиотеки, а образ содержит достаточно файлов для загрузки liblinphone. Дальше нужен отдельный тест телефонного приложения: регистрация SIP, входящий и исходящий звонки, звук в обе стороны, завершение вызова, потеря сети и переключение сервера. Для видеотелефона добавляются камера, кодеки и видеовызов. QEMU не заменяет проверку аудиотракта и оборудования реального телефона.

EN: A successful run establishes that Yocto built the SDK for the target architecture, the application received its headers and libraries, and the image contains enough files to load liblinphone. A separate phone application test must then cover SIP registration, incoming and outgoing calls, two-way audio, call termination, network loss and server failover. A video phone also needs camera, codec and video-call checks. QEMU cannot replace validation of the real phone's audio path and hardware.

13. SOURCES / ИСТОЧНИКИ

Research date / Дата проверки: 2026-11-15.

- Official Linphone Yocto integration guide: https://wiki.linphone.org/xwiki/wiki/public/view/Linphone/Building%20Linphone%20with%20Yocto/
- Official Kirkstone recipe layer: https://gitlab.linphone.org/BC/public/meta-bc/-/tree/feature/yocto-kirkstone
- Yocto host requirements: https://docs.yoctoproject.org/4.0.30/ref-manual/system-requirements.html
- Creating layers: https://docs.yoctoproject.org/4.0.30/dev-manual/layers.html
- Writing recipes: https://docs.yoctoproject.org/4.0.30/dev-manual/new-recipe.html
- SYSROOT_DIRS and recipe variables: https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html#term-SYSROOT_DIRS
- Debugging tasks: https://docs.yoctoproject.org/4.0.30/dev-manual/debugging.html
- Running QEMU: https://docs.yoctoproject.org/4.0.30/dev-manual/qemu.html
- Liblinphone version API declaration: https://github.com/BelledonneCommunications/liblinphone/blob/master/include/linphone/core.h
- Kirkstone common MIT license used by the example: https://git.yoctoproject.org/poky/tree/meta/files/common-licenses/MIT?h=kirkstone
