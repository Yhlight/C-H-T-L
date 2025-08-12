# CMake generated Testfile for 
# Source directory: /workspace
# Build directory: /workspace/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(hello_world "/workspace/build/chtl" "/workspace/examples/hello-world.chtl" "-o" "/workspace/build/test-output")
set_tests_properties(hello_world PROPERTIES  _BACKTRACE_TRIPLES "/workspace/CMakeLists.txt;56;add_test;/workspace/CMakeLists.txt;0;")
