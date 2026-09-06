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


set(AP_BASE ON CACHE BOOL "Build the base parts of the liballPurpose library")
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
    	COMPONENTS ${COMPONENTS_FLTK}
    	PATHS ${PACKAGE_CONFIG_DIR_FLTK}
    	NO_DEFAULT_PATH
    )
    if(${FLTK_FOUND})
       message(STATUS "Found FLTK: ${FLTK_DIR} (version ${FLTK_VERSION})")
    else()
       message(FATAL_ERROR 
            "\n=======================================================================\n"
            " FLTK NOT FOUND OR NOT BUILT YET!\n"
            "=======================================================================\n"
            " It looks like you haven't built the FLTK submodule dependency.\n"
            " Please run these commands (copy) in your terminal to build it first:\n\n"
            "   cd ${CMAKE_SOURCE_DIR}/extern/fltk\n"
            "   git submodule update --init\n"
            "   cmake -B build -DCMAKE_BUILD_TYPE=Release\n"
            "   cmake --build build -j8\n\n"
            " If you have FLTK compiled elsewhere, point CMake directly to it\n"
            " by passing this variable when configuring your project:\n\n"
            "   -DPACKAGE_CONFIG_DIR_FLTK=/path/to/your/built/fltk\n\n"
            " Once finished, return to your main build folder and run CMake again.\n"
            "=======================================================================\n"
       )
    endif()
endif()

if(USE_GL)
    find_package(OpenGL)

    if(OPENGL_FOUND)
        message(STATUS "Found OpenGL: ${OPENGL_LIBRARIES}")
    else()
        if(WIN32)
            message(FATAL_ERROR 
                "\n=======================================================================\n"
                " OPENGL NOT FOUND!\n"
                "=======================================================================\n"
                " Please ensure you have installed the Windows SDK via the \n"
                " Visual Studio Installer (Desktop development with C++ component).\n"
                "=======================================================================\n"
            )
        else()
            message(FATAL_ERROR 
                "\n=======================================================================\n"
                " OPENGL NOT FOUND!\n"
                "=======================================================================\n"
                " Please ensure you have the OpenGL development libraries installed.\n"
                " On Ubuntu/Debian: sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev\n"
                " On Fedora/CentOS: sudo dnf install mesa-libGL-devel mesa-libGLU-devel\n"
                "=======================================================================\n"
            )
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

if(AP_BASE)
    add_library(ap_base_obj OBJECT ${FULLPATH_INDEPENDENT_SRC} ${FULLPATH_INDEPENDENT_HEADERS})
    setup_ap_includes(ap_base_obj)

    add_library(ap_base STATIC $<TARGET_OBJECTS:ap_base_obj>)
    setup_ap_includes(ap_base)
    
    add_library(ap STATIC $<TARGET_OBJECTS:ap_base_obj>)
    setup_ap_includes(ap)
endif()

if(USE_FLTK)
    add_library(ap_fl_obj OBJECT ${FULLPATH_FL_SRC} ${FULLPATH_FL_HEADERS})
    setup_ap_includes(ap_fl_obj)
    target_include_directories(ap_fl_obj PRIVATE ${FLTK_INCLUDE_DIRS})

    add_library(ap_fl STATIC $<TARGET_OBJECTS:ap_fl_obj>)
    setup_ap_includes(ap_fl)
    
    target_link_libraries(ap_fl PUBLIC fltk fltk_images fltk_gl)
    if(LINUX)
        target_link_libraries(ap_fl PRIVATE dl X11 fontconfig Xft Xrender Xfixes Xinerama Xcursor jpeg png)
    endif()

    if(TARGET ap)
        target_sources(ap PRIVATE $<TARGET_OBJECTS:ap_fl_obj>)
        target_link_libraries(ap PUBLIC fltk fltk_images fltk_gl)
        if(LINUX)
            target_link_libraries(ap PRIVATE dl X11 fontconfig Xft Xrender Xfixes Xinerama Xcursor jpeg png)
        endif()
    endif()
endif()

if(USE_GL)
    add_library(ap_gl_obj OBJECT ${FULLPATH_GL_SRC} ${FULLPATH_GL_HEADERS})
    setup_ap_includes(ap_gl_obj)
    target_include_directories(ap_gl_obj PRIVATE ${OPENGL_INCLUDE_DIR})

    add_library(ap_gl STATIC $<TARGET_OBJECTS:ap_gl_obj>)
    setup_ap_includes(ap_gl)
    
    target_link_libraries(ap_gl PUBLIC ${OPENGL_LIBRARIES})

    if(TARGET ap)
        target_sources(ap PRIVATE $<TARGET_OBJECTS:ap_gl_obj>)
        target_link_libraries(ap PUBLIC ${OPENGL_LIBRARIES})
    endif()
endif()


### Testing ###


set(BUILD_GTESTS OFF CACHE BOOL "Build the tests.")
set(INSTALL_GTEST OFF)
set(INSTALL_GMOCK OFF)

set(PACKAGE_CONFIG_DIR_GTEST "${CMAKE_SOURCE_DIR}/extern/googletest/build/install" CACHE PATH "GoogleTest library CMake configuration directory.")

if(BUILD_GTESTS)
    enable_testing()
    include(GoogleTest)

    find_package(GTest 
        CONFIG 
        PATHS 
            "${PACKAGE_CONFIG_DIR_GTEST}"
            "${PACKAGE_CONFIG_DIR_GTEST}/lib/cmake/GTest"
            "${PACKAGE_CONFIG_DIR_GTEST}/lib64/cmake/GTest"
        NO_DEFAULT_PATH
    )

    if(GTest_FOUND)
        message(STATUS "Found GoogleTest: ${GTest_DIR}")
        add_subdirectory(tests)  
    else()
        message(FATAL_ERROR 
            "\n=======================================================================\n"
            " GOOGLETEST NOT FOUND OR NOT BUILT YET!\n"
            "=======================================================================\n"
            " It looks like you haven't built the GoogleTest submodule dependency.\n"
            " Please run these commands (copy) in your terminal to build it first:\n\n"
            "   cd ${CMAKE_SOURCE_DIR}/extern/googletest\n"
            "   git submodule update --init\n"
            "   cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=build/install\n"
            "   cmake --build build -j8\n"
            "   cmake --install build\n\n"
            " If you have GoogleTest compiled elsewhere, point CMake directly to it\n"
            " by passing this variable when configuring your project:\n\n"
            "   -DPACKAGE_CONFIG_DIR_GTEST=/path/to/your/built/googletest\n\n"
            " Once finished, return to your main build folder and run CMake again.\n"
            "=======================================================================\n"
        )
    endif()
endif()


### Install ###


include(GNUInstallDirs)

set(EXPORT_TARGETS "")

if(AP_BASE)
    list(APPEND EXPORT_TARGETS ap ap_base)
    install(FILES ${FULLPATH_INDEPENDENT_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ap)
endif()

if(USE_FLTK)
    list(APPEND EXPORT_TARGETS ap_fl)
    install(FILES ${FULLPATH_FL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ap)
endif()

if(USE_GL)
    list(APPEND EXPORT_TARGETS ap_gl)
    install(FILES ${FULLPATH_GL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ap)
endif()

if(EXPORT_TARGETS)
    install(TARGETS ${EXPORT_TARGETS}
        EXPORT apTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(EXPORT apTargets
        FILE apTargets.cmake
        NAMESPACE ap::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ap
    )
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/apConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/apConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ap"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/apConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ap
)
