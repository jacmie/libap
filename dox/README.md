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

## Building documentation
To build documentation *Doxygen* and *GraphViz* must be installed. Configuration of the documentation is in the *dox/doxyfile*.\
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

## Contributing to the project

Github account may be needed. If you want to contribute to the project follow few guidelines:\
Clone the libap project, set it up, build and run tests. Make sure everting runs smoothly, if not ask for help.\
Create new branch for the development.\
For the bug fixes start name of the branch with *fix_<branch_name>* and for the new feature *ft_<branch_name>*.\
Add and commit changes:
```
# add all recent changes to the repository including new, or deleted files
git add -A
git commit -m "Meaningful comment"
git push origin ft_<branch_name>
```
 
Fix bugs, or make new features. If your development is mature enough make pull request.\
Go to the libap github (https://github.com/jacmie/libap/pulls) pull request tab.
* *New pull request*
* Select *base* branch as *develop* and your branch as *compare* 
* If you get message *Able to merge*, then *Create pull request*
* Otherwise, update your branch with *pull*, solve conflicts and repeat the procedure from the beginning

### Good practice

Few loose advises on the development:\
Follow the rule: *KISS* - Keep It Stupid Simple, always choose simpler solution (if possible). Simple things, simply work and are more easily understood for other developers.\
Use meaningful names of the variables and functions.\
Don't link new libraries, rather use standard ones if possible.\
Avoid complicated, one line code structures, they tend to look nice and efficient, but are hard to debug.\
Use common sense to balance using new programming features that help in the development, but don't over complicate things with added complexity of code and dependencies.\
Write tests for all new public methods and functions (see examples in the tests directory).\
Write documentation for all new public methods and functions. Describe general purpose of the function, input parameters and what it returns (see example comments in the header files).\
Follow general recommendations for code formatting by Google (https://google.github.io/styleguide/cppguide.html).
