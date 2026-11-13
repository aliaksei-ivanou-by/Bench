BitBake

SECTION 1. TECHNOLOGY AND VERSION

Category: Build tool

BitBake 2.0 with Yocto Kirkstone; exact behavior follows the project version.

SECTION 2. PURPOSE

BitBake parses metadata and schedules a dependency graph of tasks to build targets. It is the task executor used by the OpenEmbedded build system; recipes and configuration provide the instructions it evaluates.

SECTION 3. CORE CONCEPTS

Parsing combines configuration, classes, recipes and matching appends into a datastore. Providers and versions are selected from metadata; BitBake then schedules tasks such as do_fetch, do_unpack, do_patch, do_configure, do_compile, do_install and packaging.

Dependencies connect tasks across recipes. Signatures and shared state permit reuse when inputs match; they do not make an undeclared dependency safe.

DEPENDS names build-time recipe dependencies; RDEPENDS is a runtime package dependency, commonly qualified by package name.

A recipe’s tasks form a graph rather than a single linear shell script. For example, fetching and unpacking prepare sources, while configuration and compilation depend on the appropriate build inputs.

The install task places files in a staging directory; subsequent packaging and image assembly are separate steps. Overrides and layer configuration can change the final value of a variable, so inspecting the expanded metadata is often more useful than reading one assignment in isolation.

Shared-state hits should be understood through signatures and declared inputs. A missing runtime library is investigated at the package and image boundary, while a failed configure step calls for its own task log and sysroot checks.

These are distinct diagnostic paths.

SECTION 4. TYPICAL USAGE

bitbake <recipe> builds a target; bitbake <recipe> -c listtasks lists tasks; bitbake -e <recipe> shows the expanded environment; bitbake -g <target> generates dependency graphs. bitbake-layers show-appends helps identify matching appends. For a failed task inspect the log.do_* file in the recipe work directory. Commands run in an initialized build environment.

For a failed build, identify the recipe and failed task, read its log, then inspect the final metadata and declared dependencies. For a successful build with a missing target file, follow do_install into package contents and image selection rather than rebuilding randomly.

Recipe names in DEPENDS and package names in RDEPENDS have different roles. For package inspection use oe-pkgdata-util only after the relevant packages have been built; the available metadata belongs to the current build configuration.

RECIPE AUTHORING AND DIAGNOSTICS

A .bb defines a component; a matching .bbappend extends it from another layer. Honister 3.4 introduced colon overrides: SRC_URI:append = " file://fix.patch" and FILES:${PN}:append = " ${datadir}/phone". Preserve spaces for :append. Do not replace all underscores: PREFERRED_VERSION_recipe and layer collection suffixes are not override syntax.

Use inherit cmake, meson or autotools according to the build system. inherit pkgconfig integrates cross-build pkg-config; it does not install dependencies or replace DEPENDS.

Install libraries under ${D}${libdir}, headers under ${D}${includedir}, executables under ${D}${bindir}. Default splitting normally places headers and development metadata in ${PN}-dev and detached debug information in ${PN}-dbg.

FILES:${PN} uses target paths without ${D}; inspect PACKAGES and actual files instead of assigning everything to runtime.

For example, bitbake -e hello | grep '^PACKAGECONFIG=' inspects a resolved value; change the variable name for other investigations. bitbake -c devshell hello opens a build-environment shell, not a target shell. oe-pkgdata-util list-pkg-files hello and oe-pkgdata-util find-path /usr/bin/hello inspect already-built package data. bitbake-layers show-appends confirms matching appends.

devtool add introduces a new component; devtool modify exposes an existing recipe's sources; devtool build supports iteration; devtool finish exports committed changes to a maintained layer and removes the workspace override. Review generated sources, license fields, dependencies and install behavior.

LICENSE identifies licenses, LIC_FILES_CHKSUM tracks relevant license text, SRC_URI identifies fetch inputs and SRCREV pins a VCS revision. A changed license checksum requires reviewing the text, not merely accepting the new hash.

For installed-vs-shipped, inspect ${D}, PACKAGES and FILES; assign intended files to the correct package or stop installing unwanted files. For dev-so, check development symlinks; plugin .so files may require deliberate treatment.

For file-rdeps, supply the genuine runtime provider. For buildpaths/rpaths, remove leaked host paths from configuration.

A global INSANE_SKIP hides defects rather than repairing them.

LINUX BUILD-HOST COMMAND EXAMPLES

Inspect metadata and package contents for the hello recipe:

```bash
bitbake -e hello | grep '^PACKAGECONFIG='
bitbake-layers show-appends
oe-pkgdata-util list-pkg-files hello
oe-pkgdata-util find-path /usr/bin/hello
```

A separate interactive build-environment session:

```bash
bitbake -c devshell hello
```

RECIPE FRAGMENTS

Example recipe extension; paths refer to the target filesystem:

```bitbake
SRC_URI:append = " file://fix.patch"
FILES:${PN}:append = " ${datadir}/phone"
```

For a CMake project using pkg-config:

```bitbake
inherit cmake pkgconfig
```

SECTION 5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

A task graph makes dependencies, parallel execution and reuse explicit. Complexity comes from interacting layers, overrides, signatures and providers. A direct CMake or Make build is often simpler for a single host application; it does not replace image composition and cross-build metadata when those are required.

SECTION 6. PITFALLS AND SECURITY

A missing DEPENDS can produce a build that only works because of accidental host or cache state. A runtime dependency omitted from packaging can yield a successful build and a failing target. Version/provider conflicts, unmatched .bbappend files and unpinned downloads can break reproducibility. Avoid indiscriminate cache cleaning before examining signatures and logs.

SECTION 7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: the CV lists custom recipes and .bbappend for the SDK. The Legend describes SDK cross-build and image integration; Responsibilities qualifies ownership of dedicated layers and individual changes. The request explicitly asks for BitBake and recipes.

SECTION 8. INTERVIEW QUESTIONS

QUESTION BB-01. What does BitBake schedule?

Answer: BitBake parses recipes, configuration and classes, resolves providers and schedules a dependency graph of tasks. Tasks such as fetch, configure, compile and package run only when their prerequisites and signature decisions allow it; it is not just a shell loop over recipes.

QUESTION BB-02. DEPENDS versus RDEPENDS?

Answer: DEPENDS names recipe-level build dependencies whose staged outputs are needed for the build. RDEPENDS is package-level runtime dependency metadata, usually qualified as RDEPENDS:${PN}. A dependency needed while compiling is not automatically the right runtime package name.

QUESTION BB-03. How can you inspect resolved variables?

Answer: Use bitbake -e recipe in the configured environment. Inspect the final value and its assignment history, including overrides and appends, rather than reading one layer file and assuming it is the selected value.

QUESTION BB-04. Where is a task failure explained?

Answer: Start with the failed task's log.do_* under its task log directory, and inspect run.do_* when the generated command matters. Keep the first meaningful error and task context; the final make error is often only a consequence.

QUESTION BB-05. Why can a build pass but a target fail?

Answer: A target can lack a runtime package, loader, shared library, configuration, permission or ready service despite successful compilation. Check image selection and deployed files, then actual startup diagnostics; rebuilding the compiler stage does not fix every runtime cause.

QUESTION BB-06. What is the difference between do_install and image construction?

Answer: do_install copies files into the recipe's ${D} staging area. Packaging assigns those files to output packages; do_rootfs assembles selected packages and image tasks create deployable artifacts. Files in ${D} are not automatically present on the device.

QUESTION BB-07. What should you inspect before invalidating the cache?

Answer: Inspect task logs, resolved metadata, source revisions and task-signature inputs before deleting cache state. An undeclared dependency or wrong provider can survive a clean rebuild. Cache invalidation should answer a specific hypothesis and preserve evidence of the original failure.

QUESTION BB-08. What is the normal recipe task chain?

Answer: A typical path fetches, unpacks, patches, configures, compiles, installs and packages source outputs. The task graph, inherited classes and dependencies determine actual execution. Image assembly consumes packages later; recipes need not implement every task themselves.

QUESTION BB-09. What is the difference between S, B, D and WORKDIR?

Answer: S locates unpacked source, B the build directory, D the install staging area and WORKDIR the recipe work area. They can differ. Using these variables avoids writing build outputs into source layers or installing directly into the host filesystem.

QUESTION BB-10. How does a recipe select source and patches?

Answer: SRC_URI lists source locations and additional inputs such as patches or local files; checksums protect fetched archives. For version-controlled sources, pin the intended revision where reproducibility requires it. The recipe's source directory and branch/revision must agree.

QUESTION BB-11. How can a .bbappend fail to affect the intended recipe?

Answer: Its filename may not match the selected recipe version, its layer may be disabled, or another provider may be selected. Check show-layers, show-appends, recipe selection and resolved values. Editing an unmatched append changes no build behavior.

QUESTION BB-12. What does FILESEXTRAPATHS solve?

Answer: It extends the search locations for local files referenced by recipe metadata, commonly from an append's layer. A correct SRC_URI file entry is insufficient if the file cannot be found through the selected search path. Keep changes local to the intended recipe.

QUESTION BB-13. Why inherit a build-system class?

Answer: Classes such as cmake or autotools supply standard configure/build/install behavior and cross-build integration. A recipe still needs correct dependencies and project options. Hand-written host commands can bypass toolchain/sysroot handling and accidentally use host libraries.

QUESTION BB-14. How are cross-compilation and sysroots connected?

Answer: The configured toolchain emits target code and the recipe sysroot supplies target headers/libraries from declared dependencies. Build-time generators run on the host and need the appropriate native dependency. An executable's presence in PATH is not proof of the correct architecture.

QUESTION BB-15. What does PACKAGECONFIG control?

Answer: It selects optional recipe features and can associate configure arguments and dependencies with each choice. Check the resolved selection and upstream build-system behavior. Removing a feature flag is not a reliable size optimization unless dependencies and runtime behavior are also validated.

QUESTION BB-16. How do PACKAGES and FILES relate?

Answer: PACKAGES declares output packages and FILES assigns installed paths to them. A recipe can split runtime, development, debug and other content. Inspect package data when a built file is missing; broad patterns or wrong package names can place it somewhere unexpected.

QUESTION BB-17. Why is installed-vs-shipped a useful QA failure?

Answer: It identifies installed files that were not assigned to the recipe's packages. Fix the install location or packaging metadata according to the intended layout. Disabling the check globally can hide genuinely missing runtime content.

QUESTION BB-18. What do task signatures and sstate protect?

Answer: Signatures represent task inputs and relevant metadata; sstate can reuse matching outputs. An input missing from the declared dependency model may not trigger the needed rebuild. Inspect signature differences and dependencies rather than assuming cache corruption whenever output is surprising.

QUESTION BB-19. How do clean, cleansstate and cleanall differ?

Answer: clean removes recipe work outputs while leaving reusable shared state. cleansstate also removes local shared-state results; remote mirrors are separate. cleanall additionally removes fetched source artifacts. Choose deliberately, especially when downloads or caches are shared with other builds.

QUESTION BB-20. How do you investigate an unexpected provider or dependency?

Answer: Use resolved metadata and provider preferences, then inspect recipe/task dependencies, for example with bitbake -g. Distinguish build-time recipe edges from runtime package edges. Correct the declared relationship instead of adding arbitrary task order or relying on a previously populated sysroot.

QUESTION BB-21. Should every underscore become a colon in Honister?

Answer: No. Override operations and package overrides changed, but ordinary variable names and non-override suffixes did not. Review semantics rather than performing blanket replacement.

QUESTION BB-22. Why separate -dev and -dbg from runtime?

Answer: Headers/build metadata support development; detached symbols support diagnosis. The runtime normally needs executables and runtime libraries. Default package patterns/order determine the actual split.

QUESTION BB-23. How do modify and finish preserve a fix?

Answer: modify exposes recipe sources for iteration; after committing, finish exports changes to a layer and removes the workspace override. Rebuild through the exported metadata.

QUESTION BB-24. Does inherit pkgconfig provide a missing library?

Answer: No. It configures cross-build pkg-config. DEPENDS must still name the provider whose headers, libraries and .pc files are needed in the recipe sysroot.

SECTION 9. SOURCES

Research date: 2026-11-13

- https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-execution.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/tasks.html

- https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-metadata.html

- https://docs.yoctoproject.org/migration-guides/migration-3.4.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/qa-checks.html

- https://docs.yoctoproject.org/4.0.30/sdk-manual/extensible.html

- https://docs.yoctoproject.org/4.0.30/ref-manual/classes.html
