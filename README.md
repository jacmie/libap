# libap

This is All Purpose Library - libap, which contains various, useful procedures for engineering.\
It is written in C++ and the project is run with cmake. It is tested in different environments via github actions.

# Parts of the library

## Airfoils
- ap_naca - generates airfoil coordinates for 4 and 5 digit NACA airfoils
- ap_airfoil - reads and writes airfoil coordinates data files, uses also *ap_naca* module to generate data

## Basic Math Procedures
- ap_basicMath - contains various, basic mathematical procedures, many associated with geometry
- ap_vector - vector of size 3 algebra, only header files based part of the library
- ap_matrix - matrix of size 3x3 algebra, only header files based part of the library

## Bezier and B-Spline Curves
- ap_bezier - generates Bezier curves and makes operations on them
- ap_bspline - generates B-Spline curves and makes operations on them
- ap_bezierAirfoil - generates parametric geometry of airfoil based on Bezier curves

## Convert   
- ap_convert - standardized form of often used types casting, maintains high precision when casting from real numbers to strings

## Distribution
- ap_distribution - performs nonlinear points distribution on specified distance, useful for meshing procedures

## Programs and Scripts Execution
- ap_externalExe - standardized execution of external programs and scripts from code, possible different execution forms: call, pipe, CreateProcess, for Linux, Macos, Windows systems

## Filter
- ap_filter - simple low pass filter for vector data

## FLTK GUI Library Addons
- ap_flDialogs - enhanced FLTK dialogs, with custom format that can fit main application gui format
- ap_flFilesHandling - standardized files handling procedures like: browse, check file existence, check file permissions, etc.
- ap_glFLTKcolor - converts FLTK color id to rgb values, used for example for OpenGL applications

## OpenGL Technical Font
- ap_glTechFont - technical font that can be used in OpenGL view, font characters based on drawing GL_LINES, thickness and color can be formatted, character can rotate with the scene, or stay perpendicular to the screen
- ap_glTextLine - uses ap_glTechFont to create line of text in the OpenGL view

## Gnuplot Pipe
- ap_gnuplotPipe - pipe to Gnuplot plotting software

## Substitute
- ap_substitute.cpp - text file parser, basing on template file it can insert values in places specified by markers and read data from output files from places specified by markers
          
## Xfoil Callbacks
- ap_xfoil - most common procedures to execute in Xfoil via pipe airfoil manipulation and analysis

# Repository Structure

**dox**             - contains the libap project documentation. See README.md in the directory for more details.\
**extern**          - contains external submodules used in the project:\
    * googletest - to perform testing\
    * fltk - gui library used to optionally build FLTK addons\
**include**         - directory with header files of the libap library.\
**src**             - directory with source files of the libap library.\
**tests**           - directory with unit tests.\
**.git**            - git repository configuration files\
**.github**         - github actions configuration files\
**CMakeLists.txt**  - main cmake file\
**README.md**       - the readme file you are reading ;)\
**.gitignore**      - files and directories git does not include in the repository\
**.gitmodules**     - configuration of git submodules, see also extern directory\
