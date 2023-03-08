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
    #gtest_add_tests(${TESTNAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TESTNAME})
endmacro()

build_test(ap_basicMath_tests ap_basicMath_tests.cpp ap)
build_test(ap_discretization_tests ap_discretization_tests.cpp ap)
build_test(ap_airfoil_tests ap_airfoil_tests.cpp ap)


