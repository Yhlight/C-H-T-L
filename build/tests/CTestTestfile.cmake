# CMake generated Testfile for 
# Source directory: /workspace/tests
# Build directory: /workspace/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ScannerTest "/workspace/build/tests/test_scanner")
set_tests_properties(ScannerTest PROPERTIES  WORKING_DIRECTORY "/workspace/tests" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;50;add_test;/workspace/tests/CMakeLists.txt;0;")
add_test(CHTLCompilerTest "/workspace/build/tests/test_chtl_compiler")
set_tests_properties(CHTLCompilerTest PROPERTIES  WORKING_DIRECTORY "/workspace/tests" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;51;add_test;/workspace/tests/CMakeLists.txt;0;")
