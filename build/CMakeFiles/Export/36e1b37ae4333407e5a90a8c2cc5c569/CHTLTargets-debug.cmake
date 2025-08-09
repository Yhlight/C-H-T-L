#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CHTL::chtl_core" for configuration "Debug"
set_property(TARGET CHTL::chtl_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(CHTL::chtl_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libchtl_core.a"
  )

list(APPEND _cmake_import_check_targets CHTL::chtl_core )
list(APPEND _cmake_import_check_files_for_CHTL::chtl_core "${_IMPORT_PREFIX}/lib/libchtl_core.a" )

# Import target "CHTL::chtl_shared" for configuration "Debug"
set_property(TARGET CHTL::chtl_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(CHTL::chtl_shared PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libchtl.so"
  IMPORTED_SONAME_DEBUG "libchtl.so"
  )

list(APPEND _cmake_import_check_targets CHTL::chtl_shared )
list(APPEND _cmake_import_check_files_for_CHTL::chtl_shared "${_IMPORT_PREFIX}/lib/libchtl.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
