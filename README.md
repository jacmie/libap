# libap

![License](https://img.shields.io/badge/license-MIT-blue)
[![C++](https://img.shields.io/badge/C++-lib-blue.svg?style=flat&logo=c%2B%2B)](#)
[![CMake](https://img.shields.io/badge/CMake-lib-blue)](https://cmake.org)
[![FLTK](https://img.shields.io/badge/FLTK-lib-blue)](https://www.fltk.org/)

The is All Purpose Library - `libap` is a collection of useful procedures tailored for engineering applications.  
It is written in modern C++, uses CMake as its build system, and is continuously tested across multiple environments (Linux, macOS, and Windows) via GitHub Actions.

## Library Architecture and Modules

The library is split into three main logical parts which can be selectively enabled or disabled during compilation.

### Combined Library (`ap`)
* **Unified Library**: When compiling, parent `ap` library target is created which bundles all object files from the selected modules into a single target. 
* **Dependencies**: The `ap` target explicitly requires the core components (`AP_BASE`) to be enabled. If additional modules like `USE_FLTK` or `USE_GL` are toggled on, their respective source objects and interface link flags are automatically appended into this unified library.

### Base Component (`ap_base`)
Core engineering, mathematics, and curve generation utilities. **These have no external dependencies.**

* **Airfoils**
  * `ap_naca`: Generates geometric coordinates for 4-digit and 5-digit NACA airfoils.
  * `ap_airfoil`: Reads and writes airfoil coordinates data files; interfaces with the `ap_naca` module.
* **Basic Math Procedures**
  * `ap_basicMath`: Collection of fundamental mathematical procedures, primarily geometric.
  * `ap_vector`: 3D vector algebra (Header-only implementation).
  * `ap_matrix`: 3x3 matrix algebra (Header-only implementation).
* **Bezier and B-Spline Curves**
  * `ap_bezier`: Generates Bezier curves and provides associated geometric operations.
  * `ap_bspline`: Generates B-Spline curves and provides associated geometric operations.
  * `ap_bezierAirfoil`: Generates parametric airfoil geometries using Bezier curves.
* **Convert & Utilities**
  * `ap_convert`: Standardized, type-safe casting wrappers maintaining high precision when converting floating-point values to strings.
  * `ap_distribution`: Non-linear point distribution profiles over specified distances, optimized for computational meshing procedures.
* **Interprocess & Execution**
  * `ap_externalExe`: Cross-platform, standardized execution of external applications and scripts (supports call abstractions, piping, and native Windows CreateProcess or POSIX forks).
  * `ap_gnuplotPipe`: A streaming pipe interface directly to Gnuplot plotting software.
  * `ap_xfoil`: Standard callbacks and automated execution pipelines for the XFOIL aerodynamic panel code via pipes.
* **Processing & Filtering**
  * `ap_filter`: A basic digital low-pass filter framework for vector data series.
  * `ap_substitute`: Template-driven text file parser designed to search/replace values using markers and scrape structural results from output logs.

### FLTK Component (`ap_fl`)
Optional visual wrappers and native widgets leveraging the Fast Light Toolkit GUI.

* `ap_flDialogs`: Enhanced FLTK modal dialogs with customizable formatting to seamlessly match a parent application's styling.
* `ap_flFilesHandling`: Standardized user file-system workflows including browse dialogs, existential verification, and access permission validation.
* `ap_glFLTKcolor`: Utility mapping internal FLTK color identifiers to standard RGB profiles, useful for uniform OpenGL viewport rendering.

### OpenGL Component (`ap_gl`)
Vector font engines and overlays optimized for real-time graphics rendering pipeline viewports.

* `ap_glTechFont`: A custom technical vector font drawn via low-level primitives (`GL_LINES`). Supports custom lineweights, colorization, scene-bound rotation vectors, and screen-space camera alignment.
* `ap_glTextLine`: A multi-character layout manager utilizing `ap_glTechFont` to build structural lines of text inside an active OpenGL viewport context.

## Repository Structure

* **`dox`**: Project documentation assets and manuals. (See the internal `README.md` inside `dox` for build rules).
* **`extern`**: Submodules and third-party dependencies managed by the repository.
  * `fltk`: GUI layout library pulled optionally for UI components.
  * `googletest`: Test assertion and mocking architecture.
* **`include`**: Centralized structure containing the exposed public header API files.
* **`src`**: C++ implementation source code files.
* **`tests`**: Automated suite of isolated unit tests.

## Get and set the project

Clone the library to the desired directory.
```bash
git clone git@github.com:jacmie/libap.git
```

Update git submodules (gtest, FLTK):
```bash
git submodule update --init --recursive
```

## Build

The library offers modular control over what gets compiled. You can selectively disable the core layer or explicitly pull optional graphics wrappers depending on your project constraints.

| CMake Option | Default | Description |
| :--- | :--- | :--- |
| `AP_BASE` | `ON` | Compiles the core computational libraries (`ap_base` and unified `ap`). |
| `USE_FLTK` | `OFF` | Compiles FLTK interface modules (`ap_fl`). Requires FLTK dependencies. |
| `USE_GL` | `OFF` | Compiles OpenGL technical typography engines (`ap_gl`). Requires OpenGL drivers. |
| `BUILD_GTESTS` | `OFF` | Configures and builds the automated unit test suites using GoogleTest. |

### Compilation Scenarios

Before running scenarios that enable `USE_FLTK` or `BUILD_GTESTS`, you must handle their external dependencies. This requires either building the packaged submodules locally (refer to the documentation inside the `extern` directory for step-by-step instructions) or pointing CMake to valid, pre-installed versions of FLTK and GoogleTest already available on your operating system.

#### Scenario 1: Default Base Build
Compiles only the core math and computational components without any external dependencies.
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j8
```

#### Scenario 2: FLTK UI Addons Enabled
Compiles the base components alongside the FLTK interface extensions.
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_FLTK=ON
cmake --build . -j8
```

#### Scenario 3: OpenGL Typography Interface Enabled
Compiles the base components alongside the viewport font renderer modules.
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_GL=ON
cmake --build . -j8
```

#### Scenario 4: Full Suite Build with Verification Tests
Compiles all base assets, GUI layers, OpenGL typography modules, and prepares the GoogleTest execution suite.
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_FLTK=ON -DUSE_GL=ON -DBUILD_GTESTS=ON
cmake --build . -j8
ctest --output-on-failure
```

#### Scenario 5: Isolated OpenGL Module (Without Core Base)
Builds only the OpenGL typography component library, omitting the unified `ap` target and core base math libraries.
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_GL=ON -DAP_BASE=OFF
cmake --build . -j8
```

#### Scenario 6: Isolated FLTK Module (Without Core Base)
Builds only the FLTK addon interface libraries, skipping compilation of the core computational targets.
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_FLTK=ON -DAP_BASE=OFF
cmake --build . -j8
```

## Tests

To run the tests on the project (testing the libap takes few seconds):
```bash
# from the build directory,
# additional option to make verbose output in case of failure
ctest --output-on-failure
```

## Installation

Only the libraries and corresponding headers that were selected during the configuration are installed.  
When installing, targets and headers are sorted into system-standard structural conventions:
* **Libraries (`.a` / `.lib`)**: Installed to `${CMAKE_INSTALL_LIBDIR}` (e.g., `lib/`).
* **Headers (`.h`)**: Copied component-by-component into `${CMAKE_INSTALL_INCLUDEDIR}/ap/` (e.g., `include/ap/`).
* **CMake Interface Files**: Module exports (`apTargets.cmake`, `apConfig.cmake`) are deployed to `${CMAKE_INSTALL_LIBDIR}/cmake/ap/`.

You can control the installation path in three ways depending on your workflow preferences:

#### Option A: Standard System Installation
Installs the library directly into your operating system's standard directories (e.g., `/usr/local` on Linux/macOS). This usually requires root privileges.
```bash
cmake --install .
```

#### Option B: Configuration-Time Prefix (Recommended)
Defines the installation destination during the initial configuration step. This is ideal when setting up repeatable build configurations or using package managers.
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/custom_directory
cmake --build . -j8
cmake --install .
```

#### Option C: Dynamic Installation-Time Prefix
Overrides the installation destination on the fly during the actual installation step without requiring a project re-configuration.
```bash
cmake --install . --prefix /path/to/custom_directory
```

## Usage

When `libap` is installed, it exports native CMake configuration targets. This allows downstream consumer software to look up the library components via standard `find_package` infrastructure.

### Integrating via CMake

Add the following pattern to your application's `CMakeLists.txt`:

```cmake
# Locate the installed library and request desired modules
find_package(ap REQUIRED COMPONENTS fltk)

# Link your application against the specific exported namespace targets
add_executable(my_engineering_app main.cpp)
target_link_libraries(my_engineering_app PRIVATE ap::ap_fl)
```

Depending on your installation architecture, the exported namespaces available for linking are:
* `ap::ap` (Unified base target combining objects)
* `ap::ap_base` (Isolated base computational library)
* `ap::ap_fl` (Isolated FLTK component library)
* `ap::ap_gl` (Isolated OpenGL component library)
