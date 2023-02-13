cmake_minimum_required(VERSION 3.25)

project(CADero LANGUAGES CXX)


### Process Source Files ### 


file(STRINGS src/base/FILES BASE_FILES)
foreach(SRC_FILE ${BASE_FILES})
    list(APPEND SRC_LIST_BASE src/base/${SRC_FILE})
endforeach()

file(STRINGS src/airfoil/FILES AIRFOIL_FILES)
foreach(SRC_FILE ${AIRFOIL_FILES})
    list(APPEND SRC_LIST_AIRFOIL src/airfoil/${SRC_FILE})
endforeach()

set(SRC_LIST_AIRFOIL_NO_MAIN ${SRC_LIST_AIRFOIL})
list(REMOVE_ITEM SRC_LIST_AIRFOIL_NO_MAIN "src/airfoil/airfoil_main.cpp")
list(REMOVE_ITEM SRC_LIST_AIRFOIL_NO_MAIN "src/airfoil/airfoil_icon_res.h")
list(REMOVE_ITEM SRC_LIST_AIRFOIL_NO_MAIN "src/airfoil/airfoil_icon_res.rc")

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/src/airfoil/airfoil_gui.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/airfoil/airfoil_gui.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/airfoil/airfoil_gui.fl
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/src/airfoil && fluid -c airfoil_gui.fl
    COMMENT STATUS "Processing FL file ${CMAKE_CURRENT_SOURCE_DIR}/src/designer/airfoil_gui.fl"
)

file(STRINGS src/designer/FILES DESIGNER_FILES)
foreach(SRC_FILE ${DESIGNER_FILES})
    list(APPEND SRC_LIST_DESIGNER src/designer/${SRC_FILE})
endforeach()

set(DESIGNER_FL_FILES ${DESIGNER_FILES})
list(FILTER DESIGNER_FL_FILES INCLUDE REGEX .*\.fl)

foreach(FL_FILE ${DESIGNER_FL_FILES})
    string(REGEX REPLACE "\.fl" "" FL_FILE_NO_EXT ${FL_FILE})
    add_custom_command(
        OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/src/designer/${FL_FILE_NO_EXT}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/designer/${FL_FILE_NO_EXT}.h
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/designer/${FL_FILE}
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/src/designer && fluid -c ${FL_FILE}
        COMMENT STATUS "Processing FL file ${CMAKE_CURRENT_SOURCE_DIR}/src/designer/${FL_FILE}"
    )
endforeach()


### Compile Flags ###


add_compile_options(-Wall -Wextra)
add_compile_options(-Wno-write-strings -Wno-unused-parameter -Wno-cast-function-type) # Temporary options to limit number of Warnings
set(CMAKE_CXX_STANDARD 11) 


### Include & Lib Dependencies ###


set(INCLUDE_DIR_FLTK            "/usr/local/include"                CACHE PATH "FLTK library header files directory.")
set(INCLUDE_DIR_GL_EXT          "/usr/local/include/glExt"          CACHE PATH "glExt library header files directory.")
set(INCLUDE_DIR_JM_COMMON       "/usr/local/include/JMcommon"       CACHE PATH "JMcommon library header files directory.")
set(INCLUDE_DIR_PANUKL_CONFIG   "/usr/local/include/PanuklConfig"   CACHE PATH "PanuklConfig library header files directory.")
set(INCLUDE_DIR_OCCT            "/usr/local/include/opencascade"    CACHE PATH "OCCT library header files directory.")

set(LIBRARY_DIR_FLTK            "/usr/local/lib"                    CACHE PATH "FLTK library binaries directory.")
set(LIBRARY_DIR_GL_EXT          "/usr/local/lib"                    CACHE PATH "glExt library binaries directory.")
set(LIBRARY_DIR_JM_COMMON       "/usr/local/lib"                    CACHE PATH "JMcommon library binaries directory.")
set(LIBRARY_DIR_PANUKL_CONFIG   "/usr/local/lib"                    CACHE PATH "PanuklConfig library binaries directory.")
set(LIBRARY_DIR_OCCT            "/usr/local/lib/opencascade"        CACHE PATH "OCCT library binaries directory.")

#include_directories(src/base src/airfoil src/designer)
#include_directories(${INCLUDE_DIR_FLTK} ${INCLUDE_DIR_GL_EXT} ${INCLUDE_DIR_JM_COMMON} ${INCLUDE_DIR_PANUKL_CONFIG} ${INCLUDE_DIR_OCCT})
#link_libraries(-L${LIBRARY_DIR_FLTK} -L${LIBRARY_DIR_GL_EXT} -L${LIBRARY_DIR_JM_COMMON} -L${LIBRARY_DIR_PANUKL_CONFIG} -L${LIBRARY_DIR_OCCT})

# In future check details and shift to: target_...
link_libraries(-lglExt -lPanuklConfig -lJMcommon)
link_libraries(-lfltk_jpeg -lfltk_images -lfltk_gl -lfltk)
link_libraries(-lTKernel -lTKBRep -lTKG2d -lTKG3d -lTKMath -lTKGeomBase -lTKIGES -lTKXDEIGES -lTKSTEP -lTKXDESTEP -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209
               -lTKXSBase -lTKShHealing -lTKTopAlgo -lTKGeomAlgo -lTKPrim -lTKBool -lTKBO -lTKSTL -lTKVRML -lTKXCAF -lTKV3d -lTKService -lTKLCAF -lTKHLR -lTKMesh -lTKCAF -lTKVCAF -lTKCDF)

if (WIN32) #MINGW
    link_libraries(-lws2_32 -lwindowscodecs -lole32 -loleaut32 -lpsapi -lopengl32 -lglu32)
    link_libraries(-mwindows -lole32 -luuid -lcomctl32 -lwsock32 -lsupc++ -lwinmm -lgdi32 -lm -lz)
    link_libraries(-lfltk_png)
elseif (LINUX)
    link_libraries(-ldl -lX11 -lfontconfig -lpng -lGL -lGLU -lXft -lXrender -lXfixes)
elseif (IOS)
    # iOS libs
endif()


### Compile ###

add_library(Base OBJECT ${SRC_LIST_BASE})
target_include_directories(Base PRIVATE ${INCLUDE_DIR_JM_COMMON} ${INCLUDE_DIR_OCCT})
add_library(AirfoilNoMain OBJECT ${SRC_LIST_AIRFOIL_NO_MAIN})
target_include_directories(AirfoilNoMain PRIVATE ${INCLUDE_DIR_FLTK} ${INCLUDE_DIR_GL_EXT} ${INCLUDE_DIR_JM_COMMON} ${INCLUDE_DIR_PANUKL_CONFIG} ${INCLUDE_DIR_OCCT} src/base src/designer)

add_executable(CADfoil)
target_sources(CADfoil PRIVATE $<TARGET_OBJECTS:Base> $<TARGET_OBJECTS:AirfoilNoMain> "src/airfoil/airfoil_main.cpp" "src/airfoil/airfoil_icon_res.rc")
target_include_directories(CADfoil PRIVATE ${INCLUDE_DIR_FLTK} ${INCLUDE_DIR_GL_EXT} ${INCLUDE_DIR_JM_COMMON} ${INCLUDE_DIR_PANUKL_CONFIG} ${INCLUDE_DIR_OCCT} src/base src/designer)
target_link_libraries(CADfoil PRIVATE -L${LIBRARY_DIR_FLTK} -L${LIBRARY_DIR_GL_EXT} -L${LIBRARY_DIR_JM_COMMON} -L${LIBRARY_DIR_PANUKL_CONFIG} -L${LIBRARY_DIR_OCCT})
#target_link_libraries(CADfoil PRIVATE -lglExt -lPanuklConfig -lJMcommon)

add_executable(CADero)
target_sources(CADero PRIVATE $<TARGET_OBJECTS:Base> $<TARGET_OBJECTS:AirfoilNoMain> ${SRC_LIST_DESIGNER})
target_include_directories(CADero PRIVATE ${INCLUDE_DIR_FLTK} ${INCLUDE_DIR_GL_EXT} ${INCLUDE_DIR_JM_COMMON} ${INCLUDE_DIR_PANUKL_CONFIG} ${INCLUDE_DIR_OCCT} src/base src/airfoil src/designer)
target_link_libraries(CADero PRIVATE -L${LIBRARY_DIR_FLTK} -L${LIBRARY_DIR_GL_EXT} -L${LIBRARY_DIR_JM_COMMON} -L${LIBRARY_DIR_PANUKL_CONFIG} -L${LIBRARY_DIR_OCCT})
#target_link_libraries(CADero PRIVATE -lglExt -lPanuklConfig -lJMcommon)

message(">> See available Cache Variables settings")


### Testing ###

add_subdirectory(extern/googletest)

enable_testing()

include(GoogleTest)

#add_library(libCADero STATIC)
#target_sources(libCADero PRIVATE ${SRC_LIST_BASE} PRIVATE ${SRC_LIST_AIRFOIL_NO_MAIN} PRIVATE ${SRC_LIST_DESIGNER})

add_subdirectory(tests)







### Installation ###


# Very basic, to imrove: launcher, icon, etc.
install(TARGETS CADfoil DESTINATION bin)
install(TARGETS CADero DESTINATION bin)
# MinGW bin needs also libstdc++-6.dll (can't avoid if OCCT has dynamic libs)
