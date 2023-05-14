# libap - Developers documentation

This is the developers documentation for the All Purpose Library - libap.

# Dependencies

 * git          - to clone and develop the library (https://git-scm.com/)
 * cmake        - to generate build system for the desired C++ compiler and operating system (https://cmake.org/)
 * C++ compiler - desired C++ compiler for the chosen operating system
 * gtest        - to build and execute tests (https://github.com/google/googletest) included as git submodule in the extern directory
 * FLTK library - gui library (https://www.fltk.org/) for building custom gui widgets, included as git submodule in the extern directory (it can be turned off in the cmake cache file - optional) 
 * GL library   - 3D graphics library (https://www.opengl.org/) for building 3D graphics entities (it can be turned off in the cmake cache file - optional)
 * Doxygen      - to build the documentation (https://www.doxygen.nl/ - optional)
 * GraphViz     - to build graphs in the documentation (https://graphviz.org/ - optional)

# Building the library

## Get and set the project
Clone the library to the desired directory.
```
git clone git@github.com:jacmie/libap.git
```
Update git submodules (gtest, FLTK):
```
git submodule update --init --recursive
git submodule update --recursive --remote
```
Create directory for the build output files, for example in the libap directory.\
Navigate to the directory and make initial configuration of the project.

```
cd libap
mkdir build
cd build

# from the build directory the ".." are pointing to upper directory,
# the project directory with the main CMakeLists.txt file
cmake ..
```
## Configure the project
The project has been configured by cmake with the default settings. To adjust the settings use ccmake in unix systems, or cmake gui.

```
# still from the build directory
ccmake ..

# in the ccmake (or cmake gui):
    - change desired options
    - [t] Toggle for advanced options
    - [c] Configure again after the changes
    - [g] Generate project files
    - [q] Leave the configurator
```

Basic options to set:
| Variable            | Default value                           | Comment                                                                                   |
|---------------------|-----------------------------------------|-------------------------------------------------------------------------------------------|
|BUILD_GMOCK          | ON                                      | Gtest test option to build mocks, not used in the project                                 |
|BUILD_GTESTS         | ON                                      | Gtest test option to build tests                                                          |
|CMAKE_BUILD_TYPE     | Release                                 | Type of build, which sets flags for compilation, most common values are Release, or Debug |
|CMAKE_INSTALL_PREFIX | /usr/local                              | Directory where the project will be installed (see installation part)                     |
|GTEST_HAS_ABSL       | OFF                                     | Default gtest option                                                                      |
|INCLUDE_DIR_FLTK     | /usr/local/include                      | Where cmake should look for the FLTK header files                                         |
|INCLUDE_DIR_GL       | /usr/local/include                      | Where cmake should look for the GL header files                                           |
|LIBRARY_DIR_FLTK     | /usr/local/lib                          | Where cmake should look for the FLTK librarie                                             |
|LIBRARY_DIR_GL       | /usr/local/lib                          | Where cmake should look for the GL librarie                                               |
|LIB_FLTK             | /usr/local/lib/libfltk.a                | FLTK librarie to find                                                                     |
|LIB_OPENGL           | /usr/lib/x86_64-linux-gnu/libGL.so      | GL librarie to find                                                                       |
|USE_FLTK             | ON                                      | Build libap with FLTK                                                                     |
|USE_GL               | ON                                      | Build libap with GL                                                                       |
|CMAKE_INSTALL_LIBDIR | lib                                     | (*advanced options) Subdirectory in the CMAKE_INSTALL_PREFIX directory for the library    |
|CMAKE_INSTALL_INCLUDEDIR | include                             | (*advanced options) Subdirectory in the CMAKE_INSTALL_PREFIX directory for the header files |

## Build

To build the project:

```
# from the build directory,
# the "." points to current directory
cmake --build .
```
For specyfying particular build system and other options look in to the cmake documentation (https://cmake.org/cmake/help/latest/manual/cmake.1.html).

After Configuration and Generation of the project also the native build system may be used, for example:
```
# from the build directory
make
```

## Tests

To run the tests on the project (testing the libap takes few seconds):
```
# from the build directory,
# additional option to make verbose output in case of failure
ctest --output-on-failure
```

After Configuration and Generation of the project also the native build system may be used, for example:
```
# from the build directory
make test
```

The project is automaticly build and tested by github actions in four different environments:
- Ubuntu
- Macos
- Windows - VS 17
- Windows - MSYS 2

## Building documentation
To build documentaion *Doxygen* and *GraphViz* must be installed. Configuration of the documentation is in the *dox/doxyfile*.\
Do not include build documentation in the repository (the catalogue is listed in the .gitignore except the *doxyfile* and *README*).\
To make changes in the documentation go to the *dox* catalogue:
```
cd dox
```
### Main configuration
It is not recommended to change it without a reason.\
Still, to make changes of the main settings of the documentation in the gui: 
```
doxywizard ./doxyfile
```
Optionally *doxyfile* can be edited directly.

### Documentation update
Make update of the comments in the header files with appropriate format for *Doxygen*.\
Build the documentation in the *Doxywizard* and display it, or build it from command line:
```
doxygen ./doxyfile
```
After building from command line open *html/index.html* with browser. The *html* catalogue will appear after building the documentation.\
When rebuilding the documentation and it is opened in the browser, just refresh the documentation to see changes. 

## Installation

To install the library and header files:
```
# from the build directory,
# the "." points to current directory
cmake --install .
```
On Unix systems administrator privilages may be needed. Then run the command, or similar appropriate for the operating system to enable the administrator privilages:
```
# from the build directory,
# the "." points to current directory
sudo cmake --install .
```

After *Configuration* and *Generation* of the project also the native build system may be used, for example:
```
# from the build directory
sudo make install
```

# Contributing to the project

Github account may be needed. If you want to contribute to the project follow few guidelines:\
Clone the libap project, set it up, build and run tests. Make sure everting runs smoothly, if not ask for help.\
Create new branch for the development.\
For the bug fixes start name of the branch with *fix_<branch_name>* and for the new feature *ft_<branch_name>*.\
Add and commit changes:
```
# add all recent changes to the repository including new, or delated files
git add -A
git commit -m "Meaningful comment"
git push origin ft_<branch_name>
```
 
Fix bugs, or make new features. If your development is mature enough make pull request.\
Go to the libap github (https://github.com/jacmie/libap/pulls) pull request tab.\
* *New pull request*
* Select *base* branch as *develop* and your branch as *compare* 
* If you get message *Able to merge*, then *Create pull request*
* Otherwise, update your branch with *pull*, solve conflicts and repet the procedure from the beginning

## Good practice

Few loose advices on the development:\
Follow the rule: *KISS* - Keep It Stupid Simple, always choose simpler solution (if possible). Simple things, simply work and are more easyly understood for other developers.\
Use meaningfull names of the variables and functions.\
Don't link new libraris, rather use standard ones if possible.\
Avoid complicated, one line code structures, they tend to look nice and efficient, but are hard to debug.\
Use common sense to balance using new programing features that help in the development, but don't overcomplicate things with added complexity of code and dependencies.\
Write tests for all new public methods and functions (see examples in the tests directory).\
Write documentation for all new public methods and functions. Describe general purpose of the function, input parameters and what it returns (see example comments in the header files).\
Follow general recomendations for code formating by Google (https://google.github.io/styleguide/cppguide.html).




