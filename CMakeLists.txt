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

function(prepend_paths OUT_VAR PREFIX)
    set(TEMPORARY_LIST "")
    foreach(FILE ${ARGN})
        list(APPEND TEMPORARY_LIST "${PREFIX}/${FILE}")
    endforeach()
    set(${OUT_VAR} ${TEMPORARY_LIST} PARENT_SCOPE)
endfunction()

prepend_paths(FULLPATH_INDEPENDENT_HEADERS "include/ap" ${INDEPENDENT_HEADERS})
prepend_paths(FULLPATH_FL_HEADERS          "include/ap" ${FL_HEADERS})
prepend_paths(FULLPATH_GL_HEADERS          "include/ap" ${GL_HEADERS})

prepend_paths(FULLPATH_INDEPENDENT_SRC     "src"        ${INDEPENDENT_SRC})
prepend_paths(FULLPATH_FL_SRC              "src"        ${FL_SRC})
prepend_paths(FULLPATH_GL_SRC              "src"        ${GL_SRC})


### Include & Lib Dependencies ###


set(USE_FLTK OFF CACHE BOOL "Build parts of the liballPurpose dependent on the FLTK library")
set(USE_GL OFF CACHE BOOL "Build parts of the liballPurpose dependent on the OpenGL library")

set(PACKAGE_CONFIG_DIR_FLTK	"${CMAKE_SOURCE_DIR}/extern/fltk/build" CACHE PATH "FLTK library CMake configuration directory.")

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
       message(STATUS "Found FLTK: ${FLTK_DIR} (version ${FLTK_VERSION})")
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
        if(LIB_OPENGL)
            message(STATUS "Found OpenGL: ${LIB_OPENGL}")
        else()
            message(FATAL_ERROR "OpenGL library not found!")
        endif()
    endif()
endif()


### Compile ###


macro(setup_ap_includes TARGET_NAME)
    target_include_directories(${TARGET_NAME} 
        PUBLIC 
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ap>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
endmacro()

add_library(ap_base_obj OBJECT ${FULLPATH_INDEPENDENT_SRC} ${FULLPATH_INDEPENDENT_HEADERS})
setup_ap_includes(ap_base_obj)

if(USE_FLTK)
    add_library(ap_fl_obj OBJECT ${FULLPATH_FL_SRC} ${FULLPATH_FL_HEADERS})
    setup_ap_includes(ap_fl_obj)
    target_include_directories(ap_fl_obj PRIVATE ${FLTK_INCLUDE_DIRS})
endif()

if(USE_GL)
    add_library(ap_gl_obj OBJECT ${FULLPATH_GL_SRC} ${FULLPATH_GL_HEADERS})
    setup_ap_includes(ap_gl_obj)
    target_include_directories(ap_gl_obj PRIVATE ${OPENGL_INCLUDE_DIR})
endif()


add_library(ap_base STATIC $<TARGET_OBJECTS:ap_base_obj>)
setup_ap_includes(ap_base)

if(USE_FLTK)
    add_library(ap_fl STATIC $<TARGET_OBJECTS:ap_fl_obj>)
    setup_ap_includes(ap_fl)
    target_link_libraries(ap_fl PUBLIC ap_base fltk fltk_images fltk_gl)
    if(LINUX)
        target_link_libraries(ap_fl PRIVATE dl X11 fontconfig Xft Xrender Xfixes Xinerama Xcursor jpeg png)
    endif()
endif()

if(USE_GL)
    add_library(ap_gl STATIC $<TARGET_OBJECTS:ap_gl_obj>)
    setup_ap_includes(ap_gl)
    target_link_libraries(ap_gl PUBLIC ap_base ${OPENGL_LIBRARIES})
endif()


add_library(ap STATIC $<TARGET_OBJECTS:ap_base_obj>)
setup_ap_includes(ap)

if(USE_FLTK)
    target_sources(ap PRIVATE $<TARGET_OBJECTS:ap_fl_obj>)
    target_link_libraries(ap PUBLIC fltk fltk_images fltk_gl)
    if(LINUX)
        target_link_libraries(ap PRIVATE dl X11 fontconfig Xft Xrender Xfixes Xinerama Xcursor jpeg png)
    endif()
endif()

if(USE_GL)
    target_sources(ap PRIVATE $<TARGET_OBJECTS:ap_gl_obj>)
    target_link_libraries(ap PUBLIC ${OPENGL_LIBRARIES})
endif()


### Testing ###


set(BUILD_GTESTS OFF CACHE BOOL "Build the tests.")
set(INSTALL_GTEST OFF)
set(INSTALL_GMOCK OFF)

if(BUILD_GTESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory("extern/googletest")
    add_subdirectory(tests)  
endif()


### Install ###
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default local dependencies installation target layout path prefix." FORCE)

if(NOT CMAKE_INSTALL_BINDIR)
    set(CMAKE_INSTALL_BINDIR bin)
endif()
if(NOT CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include)
endif()
if(NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
endif()

set(EXPORT_TARGETS ap ap_base)
if(USE_FLTK)
    list(APPEND EXPORT_TARGETS ap_fl)
endif()
if(USE_GL)
    list(APPEND EXPORT_TARGETS ap_gl)
endif()

install(TARGETS ${EXPORT_TARGETS}
    EXPORT apTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ap DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT apTargets
    FILE apTargets.cmake
    NAMESPACE ap::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ap
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/apConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/apConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ap"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/apConfig.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ap"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/apConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ap
)
