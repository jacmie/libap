include(GoogleTest)

macro(build_test TESTNAME FILES LIBRARIES)
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

    gtest_discover_tests(${TESTNAME})
endmacro()

build_test(hello_test hello_test.cc ap)
build_test(ap_discretization_tests ap_discretization_tests.cpp ap)


