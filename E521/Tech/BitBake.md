BitBake

1. TECHNOLOGY AND VERSION
Category: Build tool
BitBake 2.0 with Yocto Kirkstone; exact behavior follows the project version.

2. PURPOSE

BitBake parses metadata and schedules a dependency graph of tasks to build targets. It is the task executor used by the OpenEmbedded build system; recipes and configuration provide the instructions it evaluates.

3. CORE CONCEPTS

Parsing combines configuration, classes, recipes and matching appends into a datastore. Providers and versions are selected from metadata; BitBake then schedules tasks such as do_fetch, do_unpack, do_patch, do_configure, do_compile, do_install and packaging. Dependencies connect tasks across recipes. Signatures and shared state permit reuse when inputs match; they do not make an undeclared dependency safe. DEPENDS names build-time recipe dependencies; RDEPENDS is a runtime package dependency, commonly qualified by package name.

A recipe’s tasks form a graph rather than a single linear shell script. For example, fetching and unpacking prepare sources, while configuration and compilation depend on the appropriate build inputs. The install task places files in a staging directory; subsequent packaging and image assembly are separate steps. Overrides and layer configuration can change the final value of a variable, so inspecting the expanded metadata is often more useful than reading one assignment in isolation. Shared-state hits should be understood through signatures and declared inputs. A missing runtime library is investigated at the package and image boundary, while a failed configure step calls for its own task log and sysroot checks. These are distinct diagnostic paths.

4. TYPICAL USAGE

bitbake <recipe> builds a target; bitbake <recipe> -c listtasks lists tasks; bitbake -e <recipe> shows the expanded environment; bitbake -g <target> generates dependency graphs. bitbake-layers show-appends helps identify matching appends. For a failed task inspect the log.do_* file in the recipe work directory. Commands run in an initialized build environment.

5. STRENGTHS, LIMITATIONS AND ALTERNATIVES

A task graph makes dependencies, parallel execution and reuse explicit. Complexity comes from interacting layers, overrides, signatures and providers. A direct CMake or Make build is often simpler for a single host application; it does not replace image composition and cross-build metadata when those are required.

6. PITFALLS AND SECURITY

A missing DEPENDS can produce a build that only works because of accidental host or cache state. A runtime dependency omitted from packaging can yield a successful build and a failing target. Version/provider conflicts, unmatched .bbappend files and unpinned downloads can break reproducibility. Avoid indiscriminate cache cleaning before examining signatures and logs.

7. USE IN THE CANDIDATE’S PROJECTS

SIP-BASED PHONE SOFTWARE: the CV lists custom recipes and .bbappend for the SDK. The Legend describes SDK cross-build and image integration; Responsibilities qualifies ownership of dedicated layers and individual changes. The request explicitly asks for BitBake and recipes.

8. INTERVIEW QUESTIONS

1. What does BitBake schedule?
A graph of tasks derived from metadata and dependencies.

2. DEPENDS versus RDEPENDS?
DEPENDS affects build-time recipe dependencies; RDEPENDS describes runtime package dependencies.

3. How can you inspect resolved variables?
Use bitbake -e <recipe> in the configured build environment.

4. Where is a task failure explained?
Inspect the corresponding log.do_* in the recipe work directory.

5. Why can a build pass but a target fail?
The runtime package, library, configuration or service may be absent or incompatible.

9. SOURCES

Research date: 2026-11-11
- https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-execution.html
- https://docs.yoctoproject.org/4.0.30/ref-manual/variables.html
