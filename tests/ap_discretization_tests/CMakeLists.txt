#cmake_minimum_required(VERSION 3.14)
#project(my_project)

# GoogleTest requires at least C++14
#set(CMAKE_CXX_STANDARD 17)

add_executable(
  ap_discretization_tests
  ap_discretization_tests/ap_discretization_tests.cpp
)
target_link_libraries(
  ap_discretization_tests
  GTest::gtest_main
  ap
)
target_include_directories(ap_discretization_tests PRIVATE ../../include/ap)
#target_link_libraries(ap_discretization_tests PRIVATE -ap)

#include(GoogleTest)
#gtest_discover_tests(hello_test)
include(GoogleTest)
gtest_discover_tests(ap_discretization_tests)
