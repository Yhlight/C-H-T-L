# Install script for directory: /workspace

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/chtl-compiler" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/chtl-compiler")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/chtl-compiler"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/workspace/build/chtl-compiler")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/chtl-compiler" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/chtl-compiler")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/chtl-compiler")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/chtl-compiler" TYPE FILE FILES
    "/workspace/src/scanner/CodeScanner.h"
    "/workspace/src/compiler/Compiler.h"
    "/workspace/src/compiler/MainCompiler.h"
    "/workspace/src/chtl/CHTLCompiler.h"
    "/workspace/src/css/CSSCompiler.h"
    "/workspace/src/js/JavaScriptCompiler.h"
    "/workspace/src/chtljs/CHTLJSCompiler.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/chtl-compiler/antlr" TYPE FILE FILES
    "/workspace/generated/chtl/grammars/chtl/grammars/chtl/CHTLLexer.h"
    "/workspace/generated/chtl/grammars/chtl/grammars/chtl/CHTLParser.h"
    "/workspace/generated/chtl/grammars/chtl/grammars/chtl/CHTLListener.h"
    "/workspace/generated/chtl/grammars/chtl/grammars/chtl/CHTLBaseListener.h"
    "/workspace/generated/css/grammars/css/grammars/css/CSSLexer.h"
    "/workspace/generated/css/grammars/css/grammars/css/CSSParser.h"
    "/workspace/generated/css/grammars/css/grammars/css/CSSListener.h"
    "/workspace/generated/css/grammars/css/grammars/css/CSSBaseListener.h"
    "/workspace/generated/js/grammars/js/grammars/js/JavaScriptLexer.h"
    "/workspace/generated/js/grammars/js/grammars/js/JavaScriptParser.h"
    "/workspace/generated/js/grammars/js/grammars/js/JavaScriptListener.h"
    "/workspace/generated/js/grammars/js/grammars/js/JavaScriptBaseListener.h"
    "/workspace/generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSLexer.h"
    "/workspace/generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSParser.h"
    "/workspace/generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSListener.h"
    "/workspace/generated/chtljs/grammars/chtljs/grammars/chtljs/CHTLJSBaseListener.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chtl-compiler/grammars" TYPE DIRECTORY FILES "/workspace/grammars/" FILES_MATCHING REGEX "/[^/]*\\.g4$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/tests/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/docs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/examples/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
