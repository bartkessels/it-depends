# It Depends

Getting grip on your dependencies.
<br>

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/mit)
<br>
<!-- Build status -->
[![Build & Test It Depends on all platforms](https://github.com/bartkessels/it-depends/actions/workflows/build_test.yml/badge.svg)](https://github.com/bartkessels/it-depends/actions/workflows/build_test.yml)
[![Package It Depends for all platforms](https://github.com/bartkessels/it-depends/actions/workflows/package.yml/badge.svg)](https://github.com/bartkessels/it-depends/actions/workflows/package.yml)
[![Vulnerability scan](https://github.com/bartkessels/it-depends/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/bartkessels/it-depends/actions/workflows/codeql-analysis.yml)
[![codecov](https://codecov.io/gh/bartkessels/it-depends/branch/main/graph/badge.svg?token=5BZQHUZNA6)](https://codecov.io/gh/bartkessels/it-depends)

---

Welcome to the Git repository of _It Depends_. _It Depends_ is a small application build to give you insights into your [Software Bill of Materials](https://english.ncsc.nl/research/research-results/using-the-software-bill-of-materials-for-enhancing-cybersecurity) or SBOM for short.
With this application you can visualize all the dependencies based on the generated SBOM, and give you insights in the versions that are used.

# Table of contents

- [1. Overview](#1-overview)
  - [1.1 Supported SBOM standards](#11-supported-sbom-standards)
  - [1.2 Roadmap](#12-roadmap)
- [2. External dependencies](#2-external-dependencies)
- [3. Build](#3-build)
  - [3.1 MacOS](#31-macos)
  - [3.2 Linux](#32-linux)
  - [3.3 Windows](#33-windows)
- [4. Package](#4-package)
  - [4.1 MacOS](#41-macos)
  - [4.2 Linux](#42-linux)
  - [4.3 Windows](#43-windows)
- [5. Automated testing](#5-automated-testing)
  - [5.1 Generate coverage report](#51-generate-coverage-report)
- [6. Contribute](#6-contribute)
  - [6.1 Branching strategy](#61-branching-strategy)
- [7. Create a new release](#7-create-a-new-release)

# 1. Overview

_It Depends_ main focus is allowing a developer to get a grip on the dependencies and transative dependencies of their system. _It Depends_ supports different kinds of SBOM standards. Based on these standards you can load the generated SBOM file into _It Depends_ and it will visualize all the dependencies for you.

## 1.1 Supported SBOM standards

_It Depends_ supports the following SBOM standards

- [Cyclone DX](https://cyclonedx.org)

If you're missing a specific standard, feel free to open an issue and request a new supported standard!

## 1.2 Roadmap

Because I'm developing _It Depends_ in my spare time, not everything I'd like to see can be implemented immediately. Therefore, the following features are going to be implemented in the upcoming future.

- Scanning dependency version against a database with known vulnerabilities. For example a custom hosted [Dependency Track](https://dependencytrack.org) server.
- Searching for updates for a package
  - If you have package _X_ with version _1.2_ but version _1.5_ is available, display a tag for that package that an update is available.

# 2. External dependencies

_It Depends_ uses CMake to download and compile most of it's dependencies. However, not all dependencies are available through this method. Or at most, are not suitable using this method. Therefore, the following dependencies are required to be installed on the system itself when trying to compile _It Depends_.

- [Qt](https://qt.io)
  - Cross-platform GUI framework
- [Ninja](https://ninja-build.org)
  - Cross-platform build system
- [CMake](https://cmake.org)
  - Cross-platform build tool generator

If you use the `use_installed_dependencies` flag when executing the `cmake` command, you're also going to need the following dependencies. __Note that these are NOT required by default!__.

- [Niels Lohmann Json](https://github.com/nlohmann/json)
  - JSON library, used to parse the JSON SBOM files

# 3. Build

When building _It Depends_ there are a couple of flags you can set when executing the `cmake` command.
These commands can be set through the `-D<variable_name>=<variable_value>` flag for the CMake command.

- `use_qt6`
  - __Values__: [`true`, `false`]
  - __Default value__: `true`
  - __Description__: Use Qt6 instead of Qt5.
- `use_installed_dependencies`
  - __Values__: [`true`, `false`]
  - __Default value__: `false`
  - __Description__: Use the installed versions of the dependencies for It Depends instead of fetching them using FetchContent.
- `package`
  - __Values__: [`true`, `false`]
  - __Default value__: `false`
  - __Description__: Package It Depends for all supported platforms. 
- `generate_coverage_report`
  - __Values__: [`true`, `false`]
  - __Default value__: `false`
  - __Description__: Generate a test coverage report when running `id_tests`.

## 3.1 MacOS

```bash
$ cmake . -G Ninja
$ ninja ItDepends
```

This will create the `bin/ItDepends.app` bundle. This can be executing by double-clicking it in Finder.

Please not that this App Bunlde does __NOT__ include the Qt-framework or the other dependencies. So when moving this bundle to another location, or computer, the application might not start up.

## 3.2 Linux

```bash
$ cmake . -G Ninja
$ ninja ItDepends
```

This will create the `bin/ItDepends` binary file. This can be executed by either running `./bin/itdepends` from the command line, or double-clicking the file through your file browser.

## 3.3 Windows

```powershell
C:\ItDepends> cmake -G Ninja
C:\ItDepends> ninja ItDepends
```

This will create the `bin/ItDepends.exe` executable. It can be executed by double-clicking the file in the File Explorer.

Please not that this executable does __NOT__ include the Qt-framework or the other dependencies. So when moving this executable to another location, or computer, the application might not start up.

# 4. Packaging

## 4.1 MacOS

Build the MacOS App Bundle with all dependencies and required frameworks.

```bash
# Create the project files
$ cmake . -G Ninja -Dpackaging=true

# Generate the MacOS bundle
$ ninja ItDepends
```

This will create the distributable App Bundle `bin/ItDepends.app`.

## 4.2 Linux

Build the Flatpak bundle with all dependencies and required frameworks.

```bash
# Prepare the Flatpak template
$ cmake . -G Ninja -Dpackaging=true

# Create the local Flatpak repository for our bundle
$ flatpak-builder --repo=itdepends_repo itdepends ./packaging/linux/itdepends.yml

# Create the Flatpak bundle
$ flatpak build-bundle itdepends_repo itdepends.flatpak net.bartkessels.itdepends 
```

## 4.3 Windows

Build the Windows executable with all dependencies and required frameworks.

```powershell
# Setup the project files
C:\ItDepends> cmake . -G Ninja -Dpackaging=true

# Generate the executable
C:\ItDepends> ninja ItDepends

# Add the Qt dependencies to the executable
C:\ItDepends> windeployqt bin/ItDepends.exe
```

# 5. Automated testing

To validate that _It Depends_ works properly, and keeps working throughout it's lifetime. _It Depends_ includes automated unit tests using [Catch2](https://github.com/catch/catch2). These tests are automatically executed when creating a PR or when directly pushing to the main branch (which you should __NEVER__ do).

You can also execute these tests manually by building and running the `id_tests` build target.

```bash
# Build the test executable
$ cmake . -G Ninja
$ ninja id_tests

# Run the tests
$ ./bin/id_tests
```

This will generate an application purely for testing _It Depends_. This application does not include the _It Depends_ GUI, so it doesn't do anything beyond executing the tests.

## 5.1 Generate coverage report

To generate a test coverage report for the test projects, set the `generate_coverage_report` when creating the `id_tests` project.
Thus the `cmake . -G Ninja` command above, would look like this `cmake . -G Ninja -Dgenerate_coverage_report=true`.

This will create the `default.profraw` file in the root of the repository. You can read this file using `llvm-cov export`.

The complete setup of viewing the coverage would look like this.

```bash
$ cmake . -G Ninja -Dgenerate_coverage_report=true
$ ninja id_tests
$ ./bin/id_tests
$ llvm-cov export default.profraw
```

# 6. Contribute

Is there a feature you'd like to see, or a bug you've encountered? Please let us know, and help us make _It Depends_ great for everyone! Or, if you're a developer, try to fix it yourself! If you'd like to contribute back to _It Depends_ but you're not quite sure yet what you can add, take a look at the [roadmap](#12-roadmap).

All contributions are welcome, so feel free to join the open source community and support _It Depends_ through your expertise!

To make sure everyone can contribute to _It Depends_ we value the quality and understandability of our code and repository.
So when you're building a feature, or patching a bug and you've made a decision, please document that decision in the [`docs/design.md`](docs/design.md) document. This will help future contributors to understand your rationale. If you've updated some logic in the code, please check the decision records and update the related onces. If you've done all this, update the test-suite and validate that your newly created code does exactly what you'd documented.

## 6.1 Branching strategy

So now that your idea is implemented, documented and tested it's time to merge it into _It Depends_! To help you out a bit on how to setup a branch, we've got you covered in this chapter!

_It Depends_ does not use a development branch but instead uses short lived feature branches which are directly merged into the `main`-branch. We've chosen this strategy 'cause we believe in _release often, release fast_. There's no need for your feature to gather dust in a stale `development` branch while waiting on some arbitrary date to be released. But, we do however, have some guidelines:

- If you're contributing a __feature__ use the `feature/<your-feature-name>` naming convention
- If you're contributing a __bug fix__ use the `bugfix/<the-name-of-the-bug>` naming convention.
- If you're contributing to __documentation__ use the `documentation/<name-of-change>` naming convention.
- If you're contributing a __hot fix__ use the `hotfix/<hotfix-type>-<name>` naming convention
  - These can be useful for updating dependency versions

# 7. Create a new release

To create a new release of _It Depends_, edit the `CmakeLists.txt` file and update the `VERSION` parameter of the `project` function. For versioning _It Depends_ uses
semantic versioning. Which, given the documentation on [semver.org](https://semver.org), means that the version number consists of MAJOR.MINOR.PATCH.

When creating a release of _It Depends_, check what kind of changes have been applied since the previous version and categorize these in one of the following segments:

1. Incompatible API change, or a user interface change
2. New functionality which doesn't break existing functionality
3. Bug fix

These can be mapped on the semantic versioning scheme in the following ways:

* Update the __MAJOR__ version when you've made a __breaking change__ either in the interfaces or in the UI.
* Update the __MINOR__ version when a __new feature__ is introduced
* Update the __PATCH__ version when a __bug is resolved__

When you've updated the version in `CMakeLists.txt` create a new tag in Git using the
following structure: `MAJOR.MINOR.PATCH`. For version 5 with a bugfix this would be `v5.0.1`.

This can be created using the following Git-command:

```bash
$ git tag -a v5.0.1
$ git push -u origin v5.0.1
```

This will create the tag locally and then push it to Github which in turn will kick off the required
pipelines to create the new release and add the build artifacts.
