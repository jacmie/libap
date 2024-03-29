cmake_minimum_required(VERSION 3.25)

project(ap LANGUAGES CXX)

if(UNIX)
    add_compile_options(-Wall -Wno-array-bounds)
endif()
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)


### Process Source Files ### 


set(INDEPENDENT_HEADERS
    ap_airfoil.h    
    ap_basicMath.h
    ap_bezier.h
    ap_bezierAirfoil.h
    ap_bezierPoint.h
    ap_bspline.h
    ap_convert.h
    ap_distribution.h
    ap_externalExe.h
    ap_filter.h
    ap_gnuplotPipe.h
    ap_naca.h
    ap_substitute.h
    ap_xfoil.h
    ap_utils.h
)

set(FL_HEADERS
    ap_flDialogs.h
    ap_flFilesHandling.h
    ap_glFLTKcolor.h
)

set(GL_HEADERS
    ap_glTechFont.h
    ap_glTextLine.h
)

set(INDEPENDENT_SRC
    ap_airfoil.cpp  
    ap_basicMath.cpp
    ap_bezier.cpp
    ap_bezierAirfoil.cpp
    ap_bspline.cpp
    ap_convert.cpp
    ap_distribution.cpp
    ap_externalExe.cpp
    ap_filter.cpp
    ap_gnuplotPipe.cpp
    ap_naca.cpp
    ap_substitute.cpp
    ap_xfoil.cpp
    ap_utils.cpp
)

set(FL_SRC
    ap_flDialogs.cpp
    ap_flFilesHandling.cpp
    ap_glFLTKcolor.cpp
)

set(GL_SRC
    ap_glTechFont.cpp
    ap_glTextLine.cpp
)

foreach(H_FILE ${INDEPENDENT_HEADERS})
    list(APPEND FULLPATH_INDEPENDENT_HEADERS include/ap/${H_FILE})
endforeach()

foreach(H_FILE ${FL_HEADERS})
    list(APPEND FULLPATH_FL_HEADERS include/ap/${H_FILE})
endforeach()

foreach(H_FILE ${GL_HEADERS})
    list(APPEND FULLPATH_GL_HEADERS include/ap/${H_FILE})
endforeach()

foreach(CPP_FILE ${INDEPENDENT_SRC})
    list(APPEND FULLPATH_INDEPENDENT_SRC src/${CPP_FILE})
endforeach()

foreach(CPP_FILE ${FL_SRC})
    list(APPEND FULLPATH_FL_SRC src/${CPP_FILE})
endforeach()

foreach(CPP_FILE ${GL_SRC})
    list(APPEND FULLPATH_GL_SRC src/${CPP_FILE})
endforeach()


### Include & Lib Dependencies ###


set(USE_FLTK ON CACHE BOOL "Build parts of the liballPurpose dependent on the FLTK library")
set(USE_GL ON CACHE BOOL "Build parts of the liballPurpose dependent on the OpenGL library")

set(INCLUDE_DIR_GL   "/usr/local/include"   CACHE PATH "GL library header files directory.")
set(LIBRARY_DIR_GL   "/usr/local/lib"       CACHE PATH "GL library binaries directory.")

if(LINUX)
    set(INCLUDE_DIR_FLTK        "${CMAKE_SOURCE_DIR}/extern/fltk/build/install/include"    CACHE PATH "FLTK library header files directory.")
    set(PACKAGE_CONFIG_DIR_FLTK	"${CMAKE_SOURCE_DIR}/extern/fltk/build/install/share/fltk" CACHE PATH "FLTK library binaries directory.")
elseif(APPLE)
    set(INCLUDE_DIR_FLTK        "${CMAKE_SOURCE_DIR}/extern/fltk/build/install/include"    CACHE PATH "FLTK library header files directory.")
	set(PACKAGE_CONFIG_DIR_FLTK	"${CMAKE_SOURCE_DIR}/extern/fltk/build/install/FLTK.framework/Resources/CMake" CACHE PATH "FLTK library binaries directory.")
elseif(WIN32)
    set(INCLUDE_DIR_FLTK        "${CMAKE_SOURCE_DIR}/extern/fltk/build/install/include"    CACHE PATH "FLTK library header files directory.")
    set(PACKAGE_CONFIG_DIR_FLTK	"${CMAKE_SOURCE_DIR}/extern/fltk/build/install/CMake"      CACHE PATH "FLTK library CMake configuration directory.")
endif()

message(">> INCLUDE_DIR_GL:          ${INCLUDE_DIR_GL}")
message(">> LIBRARY_DIR_GL:          ${LIBRARY_DIR_GL}")
message(">> INCLUDE_DIR_FLTK:        ${INCLUDE_DIR_FLTK}")
message(">> PACKAGE_CONFIG_DIR_FLTK: ${PACKAGE_CONFIG_DIR_FLTK}")

if(USE_FLTK)
    if(UNIX)
    	set(COMPONENTS_FLTK fltk_images fltk_gl fltk) # jpeg, png - system native
    else()
    	set(COMPONENTS_FLTK fltk_images fltk_gl fltk_z fltk fltk_jpeg fltk_png)
    endif()

    find_package(FLTK 
    	REQUIRED 
    	COMPONENTS ${COMPONENTS_FLTK}
    	PATHS ${PACKAGE_CONFIG_DIR_FLTK}
    	NO_DEFAULT_PATH
    )
    if(${FLTK_FOUND})
       message(STATUS "Found FLTK")
    else()
       message(FATAL_ERROR "Could not find FLTK")
    endif()
endif()

if(USE_GL)
    if(LINUX)
        find_library(LIB_OPENGL
            NAMES GL
            HINTS "${LIBRARY_DIR_GL}"
            REQUIRED
        )
        if(NOT LIB_OPENGL)
            message(FATAL_ERROR "OpenGL library not found!")
        endif()
    endif()
endif()


### Compile ###


if(LINUX)
    link_libraries(dl X11 fontconfig Xft Xrender Xfixes Xinerama Xcursor jpeg png)
endif()

add_library(ap STATIC)
target_sources(ap PRIVATE ${FULLPATH_INDEPENDENT_HEADERS} ${FULLPATH_INDEPENDENT_SRC})
target_include_directories(ap PRIVATE include/ap)

if(USE_FLTK)
    target_sources(ap PRIVATE ${FULLPATH_FL_HEADERS} ${FULLPATH_FL_SRC})
    target_include_directories(ap PRIVATE ${INCLUDE_DIR_FLTK})
    target_link_libraries(ap PRIVATE ${COMPONENTS_FLTK})
endif()

if(USE_GL)
    target_sources(ap PRIVATE ${FULLPATH_GL_HEADERS} ${FULLPATH_GL_SRC})
    target_include_directories(ap PRIVATE ${INCLUDE_DIR_GL})
endif()


### Testing ###


set(BUILD_GTESTS ON CACHE BOOL "Build the tests.")
set(INSTALL_GTEST OFF)

if(BUILD_GTESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory("extern/googletest")
    add_subdirectory(tests)  
endif()


### Install ###


install(DIRECTORY include/ap DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS ap DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

