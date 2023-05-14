# libap - Tests

This is All Purpose Library - libap test directory.\n
The tests are written in C++ and run by ctest (part of cmake) and gtest.

Parts of the library have tests in separate subcatalogues.\n
Each subcatalogue contains:\n
**test_name.cpp** - single C++ file with the tests\n
and the catalogue may contain:\n
**data** - subdirectory with input data for the tests\n
**out** - subdirectory with output data from the tests\n
**ref** - subdirectory with reference data to compare with the output data\n

Local **CMakeList.txt** drives the tests build.\n
**compare_files.h** contains general helper procedure used in tests to compare reference and output data.\n





