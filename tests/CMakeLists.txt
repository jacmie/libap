cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

#add_subdirectory("../extern/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

#enable_testing()

add_executable(
  hello_test
  hello_test.cc
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

#add_subdirectory(ap_discretization_tests)

#add_executable(
#  ap_discretization_tests
#  ap_discretization_tests/ap_discretization_tests.cpp
#)
#target_link_libraries(
#  ap_discretization_tests
#  GTest::gtest_main
#  ap
#)

#target_include_directories(ap_discretization_tests PRIVATE ../include/ap)
#target_link_libraries(ap_discretization_tests PRIVATE -ap)

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
endmacro()

build_test(ap_discretization_tests ap_discretization_tests.cpp ap)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(ap_discretization_tests)

#gtest_discover_tests(ap_discretization_tests/ap_discretization_tests)
#    add_subdirectory(./tests/ap_discretization_tests)

macro(package_add_test_with_libraries TESTNAME FILES LIBRARIES TEST_WORKING_DIRECTORY)
    add_executable(${TESTNAME} ${FILES})
    target_include_directories(${TESTNAME} PRIVATE ../include/ap)
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${TEST_WORKING_DIRECTORY}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

#package_add_test_with_libraries(test1 test1.cpp lib_to_test "${PROJECT_DIR}/european-test-data/")
#package_add_test_with_libraries(ap_discretization_tests ap_discretization_tests/ap_discretization_tests.cpp ap "${PROJECT_DIR}/tests/ap_discretization_tests/")
