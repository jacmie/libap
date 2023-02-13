cmake_minimum_required(VERSION 3.25)

project(ap LANGUAGES CXX)


### Process Source Files ### 


set(INDEPENDENT_HEADERS
    ap_basicMath.h
    ap_convert.h
    ap_discretization.h
    ap_externalExe.h
    ap_filter.h
    ap_gnuplotPipe.h
    ap_substitute.h
    ap_xfoil.h
)

set(FL_HEADERS
    ap_flDialogs.h
    ap_flFilesHandling.h
    ap_glFLTKcolor.h
)

set(GL_HEADERS
    ap_glGeometryObject.h
    ap_glTechFont.h
    ap_glTextLine.h
)

set(INDEPENDENT_SRC
    ap_basicMath.cpp
    ap_convert.cpp
    ap_discretization.cpp
    ap_externalExe.cpp
    ap_filter.cpp
    ap_gnuplotPipe.cpp
    ap_substitute.cpp
    ap_xfoil.cpp
)

set(FL_SRC
    ap_flDialogs.cpp
    ap_flFilesHandling.cpp
    ap_glFLTKcolor.cpp
)

set(GL_SRC
    ap_glGeometryObject.cpp
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


### Compile Flags ###


add_compile_options(-Wall -Wextra)
add_compile_options(-Wno-write-strings -Wno-unused-parameter -Wno-cast-function-type) # Temporary options to limit number of Warnings
set(CMAKE_CXX_STANDARD 17) 


### Include & Lib Dependencies ###

set(USE_FLTK ON CACHE BOOL "Build parts of the liballPurpose dependent on the FLTK library")
set(USE_OPENGL ON CACHE BOOL "Build parts of the liballPurpose dependent on the OpenGL library")

set(INCLUDE_DIR_FLTK            "/usr/local/include"                CACHE PATH "FLTK library header files directory.")
#set(INCLUDE_DIR_GL_EXT          "/usr/local/include/glExt"          CACHE PATH "glExt library header files directory.")
#set(INCLUDE_DIR_PANUKL_CONFIG   "/usr/local/include/PanuklConfig"   CACHE PATH "PanuklConfig library header files directory.")

set(LIBRARY_DIR_FLTK            "/usr/local/lib"                    CACHE PATH "FLTK library binaries directory.")
#set(LIBRARY_DIR_GL_EXT          "/usr/local/lib"                    CACHE PATH "glExt library binaries directory.")
#set(LIBRARY_DIR_PANUKL_CONFIG   "/usr/local/lib"                    CACHE PATH "PanuklConfig library binaries directory.")

#include_directories(src/base src/airfoil src/designer)
#include_directories(${INCLUDE_DIR_FLTK} ${INCLUDE_DIR_GL_EXT} ${INCLUDE_DIR_JM_COMMON} ${INCLUDE_DIR_PANUKL_CONFIG} ${INCLUDE_DIR_OCCT})
#link_libraries(-L${LIBRARY_DIR_FLTK} -L${LIBRARY_DIR_GL_EXT} -L${LIBRARY_DIR_JM_COMMON} -L${LIBRARY_DIR_PANUKL_CONFIG} -L${LIBRARY_DIR_OCCT})

# In future check details and shift to: target_...
link_libraries(-lfltk_jpeg -lfltk_images -lfltk_gl -lfltk)

if (WIN32) #MINGW
    link_libraries(-lws2_32 -lwindowscodecs -lole32 -loleaut32 -lpsapi -lopengl32 -lglu32)
    link_libraries(-mwindows -lole32 -luuid -lcomctl32 -lwsock32 -lsupc++ -lwinmm -lgdi32 -lm -lz)
    link_libraries(-lfltk_png)
elseif (LINUX)
    link_libraries(-ldl -lX11 -lfontconfig -lpng -lGL -lGLU -lXft -lXrender -lXfixes)
elseif (IOS)
    # iOS libs
endif()

if(USE_FLTK)
    find_library(FLTK_LIB fltk)
    if(NOT FLTK_LIB)
        message(FATAL_ERROR "FLTK library not found!")
    endif()
endif()

#if(USE_OPENGL)
#    find_library(OPENGL_LIB GL)
#    if(NOT OPENGL_LIB)
#        message(FATAL_ERROR "OpenGL library not found!")
#    endif()
#endif()


### Compile ###


add_library(ap STATIC)
target_sources(ap PRIVATE ${FULLPATH_INDEPENDENT_HEADERS} ${FULLPATH_INDEPENDENT_SRC})
target_include_directories(ap PRIVATE include/ap)
#target_link_libraries(CADfoil PRIVATE -L${LIBRARY_DIR_FLTK} -L${LIBRARY_DIR_GL_EXT} -L${LIBRARY_DIR_JM_COMMON} -L${LIBRARY_DIR_PANUKL_CONFIG} -L${LIBRARY_DIR_OCCT})

message(">> See available Cache Variables settings")


### Testing ###

#add_subdirectory(extern/googletest)

#enable_testing()

#include(GoogleTest)

#add_library(libCADero STATIC)
#target_sources(libCADero PRIVATE ${SRC_LIST_BASE} PRIVATE ${SRC_LIST_AIRFOIL_NO_MAIN} PRIVATE ${SRC_LIST_DESIGNER})

#add_subdirectory(tests)




### Installation ###


# Very basic, to imrove: launcher, icon, etc.
#install(TARGETS CADfoil DESTINATION bin)
#install(TARGETS CADero DESTINATION bin)
# MinGW bin needs also libstdc++-6.dll (can't avoid if OCCT has dynamic libs)
