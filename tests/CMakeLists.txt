#include(GoogleTest)

macro(build_test TESTNAME FILES LIBRARIES)
    set(FILE_PATHS "")    
    foreach(FILE ${FILES})
        list(APPEND FILE_PATHS ${TESTNAME}/${FILE})
    endforeach()

    add_executable(
        ${TESTNAME}
        ${FILE_PATHS}
    )
    target_link_libraries(
        ${TESTNAME}
        GTest::gtest_main
        ${LIBRARIES} 
    )
    target_include_directories(${TESTNAME} PRIVATE ../include/ap)

    gtest_discover_tests(${TESTNAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TESTNAME})
endmacro()

add_executable(sq ap_externalExe_tests/bin/sq.cpp)

build_test(ap_basicMath_tests ap_basicMath_tests.cpp ap)

build_test(ap_bezierPoint_tests ap_bezierPoint_tests.cpp ap)
build_test(ap_bezier_tests ap_bezier_tests.cpp ap)
build_test(ap_bezierAirfoil_tests ap_bezierAirfoil_tests.cpp ap)
build_test(ap_bspline_tests ap_bspline_tests.cpp ap)
build_test(ap_convert_tests ap_convert_tests.cpp ap)
build_test(ap_distribution_tests ap_distribution_tests.cpp ap)
build_test(ap_filter_tests ap_filter_tests.cpp ap)
build_test(ap_airfoil_tests ap_airfoil_tests.cpp ap)
build_test(ap_substitute_tests ap_substitute_tests.cpp ap)
build_test(ap_xfoil_tests ap_xfoil_tests.cpp ap)
build_test(ap_externalExe_tests ap_externalExe_tests.cpp ap)


if(USE_FLTK)
    set(LIBS ap)
#   build_test(ap_flDialogs_tests ap_flDialogs_tests.cpp ${LIBS})
    build_test(ap_flFilesHandling_tests ap_flFilesHandling_tests.cpp ${LIBS})
endif()
