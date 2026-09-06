# External Project Dependencies (extern/)

This directory houses the third-party submodules used by **ap**. To maintain absolute control over the build environment and avoid polluting system directories or repository files, each dependency must be built and isolated locally within its own `build/` directory using an internal installation layout.

### Update Git Submodules

If you did not clone this repository recursively, download the submodule files first:

```bash
git submodule update --init --recursive
```

### Build & Locally Install FLTK

```bash
cd fltk
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./build/install
cmake --build build -j8
cmake --install build
cd ..
```

### Build & Locally Install GoogleTest (For Unit Tests)

```bash
cd googletest
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./build/install
cmake --build build -j8
cmake --install build
cd ..
```

