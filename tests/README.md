# libap - Tests

This is All Purpose Library - libap test directory.\
The tests are written in C++ and run by ctest (part of cmake) and gtest.

Parts of the library have tests in separate subcatalogues.\
Each subcatalogue contains:\
**test_name.cpp** - single C++ file with the tests\
and the catalogue may contain:\
**data** - subdirectory with input data for the tests\
**out** - subdirectory with output data from the tests\
**ref** - subdirectory with reference data to compare with the output data\

Local **CMakeList.txt** drives the tests build.\
**compare_files.h** contains general helper procedure used in tests to compare reference and output data.\





