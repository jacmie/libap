cmake_minimum_required(VERSION 3.25)

project(ap LANGUAGES CXX)

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 17) 


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

set(INCLUDE_DIR_FLTK            "/usr/local/include"                CACHE PATH "FLTK library header files directory.")

set(LIBRARY_DIR_FLTK            "/usr/local/lib"                    CACHE PATH "FLTK library binaries directory.")

if(USE_FLTK)
    find_library(FLTK_LIB fltk)
    if(NOT FLTK_LIB)
        message(FATAL_ERROR "FLTK library not found!")
    endif()
endif()

if(USE_GL)
    find_library(OPENGL_LIB GL)
    if(NOT OPENGL_LIB)
        message(FATAL_ERROR "OpenGL library not found!")
    endif()
endif()


### Compile ###

#link_libraries(-lpng -lGL -lXft -lXrender -lXfixes -lfontconfig -lX11 -ldl)

if (WIN32) #MINGW
    link_libraries(-lws2_32 -lwindowscodecs -lole32 -loleaut32 -lpsapi -lopengl32 -lglu32)
    link_libraries(-mwindows -lole32 -luuid -lcomctl32 -lwsock32 -lsupc++ -lwinmm -lgdi32 -lm -lz)
#    link_libraries(-lfltk_jpeg -lfltk_png)
elseif (LINUX)
    link_libraries(-lpng -lGL -lXft -lXrender -lXfixes -lfontconfig -lX11 -ldl)
elseif (IOS)
    # iOS libs
endif()

add_library(ap STATIC)
target_sources(ap PRIVATE ${FULLPATH_INDEPENDENT_HEADERS} ${FULLPATH_INDEPENDENT_SRC})
target_include_directories(ap PRIVATE include/ap)

#link_libraries(-ldl -lX11 -lfontconfig -lpng -lGL -lXft -lXrender -lXfixes)

if(USE_FLTK)
    target_sources(ap PRIVATE ${FULLPATH_FL_HEADERS} ${FULLPATH_FL_SRC})
    target_include_directories(ap PRIVATE ${INCLUDE_DIR_FLTK})
    link_libraries(-lfltk_images -lfltk_gl -lfltk)
    if(WIN32)
        link_libraries(-lfltk_jpeg -lfltk_png)
    elseif(UNIX)
        link_libraries(-ljpeg -lpng)    
    endif()
endif()

if(USE_GL)
    target_sources(ap PRIVATE ${FULLPATH_GL_HEADERS} ${FULLPATH_GL_SRC})
#    target_include_directories(ap PRIVATE ${INCLUDE_DIR_GL})
endif()

message(">> See available Cache Variables settings")


### Testing ###


set(BUILD_GTESTS ON CACHE BOOL "Build the tests")

if(BUILD_GTESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory("extern/googletest")
    add_subdirectory(tests)  
endif()


### Installation ###

#install(DIRECTORY include/ap DESTINATION /usr/local/include)

#install(TARGETS CADfoil DESTINATION bin)
#install(TARGETS ap DESTINATION bin)
