#include(GoogleTest)

macro(build_test TESTNAME)
    add_executable(
        ${TESTNAME}
        "${TESTNAME}/${TESTNAME}.cpp"
    )
    target_link_libraries(
        ${TESTNAME}
        GTest::gtest_main
        ap 
    )
    target_include_directories(${TESTNAME} PRIVATE ../include/ap)

    gtest_discover_tests(${TESTNAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TESTNAME})
endmacro()

add_executable(sq ap_externalExe_tests/bin/sq.cpp)

build_test(ap_basicMath_tests)
build_test(ap_bezierPoint_tests)
build_test(ap_bezier_tests)
build_test(ap_bezierAirfoil_tests)
build_test(ap_bspline_tests)
build_test(ap_convert_tests)
build_test(ap_distribution_tests)
build_test(ap_filter_tests)
build_test(ap_airfoil_tests)
build_test(ap_substitute_tests)
build_test(ap_xfoil_tests)
build_test(ap_externalExe_tests)

if(USE_FLTK)
#   build_test(ap_flDialogs_tests)
    build_test(ap_flFilesHandling_tests)
endif()
