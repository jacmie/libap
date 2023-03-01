cmake_minimum_required(VERSION 3.25)

project(ap LANGUAGES CXX)

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 17) 


### Process Source Files ### 


set(INDEPENDENT_HEADERS
    ap_airfoil.h    
    ap_basicMath.h
    ap_convert.h
    ap_discretization.h
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
#    ap_glGeometryObject.h
#    ap_glTechFont.h
#    ap_glTextLine.h
)

set(INDEPENDENT_SRC
    ap_airfoil.cpp  
    ap_basicMath.cpp
    ap_convert.cpp
    ap_discretization.cpp
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
#    ap_glGeometryObject.cpp
#    ap_glTechFont.cpp
#    ap_glTextLine.cpp
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
#set(INCLUDE_DIR_PANUKL_CONFIG   "/usr/local/include/PanuklConfig"   CACHE PATH "PanuklConfig library header files directory.")

set(LIBRARY_DIR_FLTK            "/usr/local/lib"                    CACHE PATH "FLTK library binaries directory.")
#set(LIBRARY_DIR_PANUKL_CONFIG   "/usr/local/lib"                    CACHE PATH "PanuklConfig library binaries directory.")

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

#if(USE_GL)
#    find_library(OPENGL_LIB GL)
#    if(NOT OPENGL_LIB)
#        message(FATAL_ERROR "OpenGL library not found!")
#    endif()
#endif()


### Compile ###


add_library(ap STATIC)
target_sources(ap PRIVATE ${FULLPATH_INDEPENDENT_HEADERS} ${FULLPATH_INDEPENDENT_SRC})
target_include_directories(ap PRIVATE include/ap)

if(USE_FLTK)
    target_sources(ap PRIVATE ${FULLPATH_FL_HEADERS} ${FULLPATH_FL_SRC})
    target_include_directories(ap PRIVATE ${INCLUDE_DIR_FLTK})
    target_link_libraries(ap PRIVATE -lfltk_jpeg -lfltk_images -lfltk_gl -lfltk)
    if(WIN32)
        target_link_libraries(ap PRIVATE -lfltk_png)
    elseif(UNIX)
        target_link_libraries(ap PRIVATE -lpng)    
    endif()
endif()

if(USE_GL)
    target_sources(ap PRIVATE ${FULLPATH_GL_HEADERS} ${FULLPATH_GL_SRC})
#    target_include_directories(ap PRIVATE ${INCLUDE_DIR_FLTK})
endif()

message(">> See available Cache Variables settings")


### Testing ###


set(BUILD_GTESTS ON CACHE BOOL "Build the tests")

if(BUILD_GTESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory("extern/googletest")
    add_subdirectory(tests)

#    mark_as_advanced(
#        BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
#        gmock_build_tests gtest_build_samples gtest_build_tests
#        gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
#    )

#    set_target_properties(gtest PROPERTIES FOLDER extern)
#    set_target_properties(gtest_main PROPERTIES FOLDER extern)
#    set_target_properties(gmock PROPERTIES FOLDER extern)
#    set_target_properties(gmock_main PROPERTIES FOLDER extern)    
endif()


### Installation ###

#install(DIRECTORY include/ap DESTINATION /usr/local/include)

#install(TARGETS CADfoil DESTINATION bin)
#install(TARGETS ap DESTINATION bin)