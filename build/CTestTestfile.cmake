# CMake generated Testfile for 
# Source directory: /workspace
# Build directory: /workspace/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(module_packing_test "/usr/bin/cmake" "-P" "/workspace/cmake/PackModules.cmake")
set_tests_properties(module_packing_test PROPERTIES  WORKING_DIRECTORY "/workspace/build" _BACKTRACE_TRIPLES "/workspace/CMakeLists.txt;93;add_test;/workspace/CMakeLists.txt;0;")
subdirs("src")
