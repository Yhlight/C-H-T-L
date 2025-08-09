# CHTLConfig.cmake - CHTL CMake configuration file


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was CHTLConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(CHTL_VERSION 1.0.0)
set(CHTL_VERSION_MAJOR 1)
set(CHTL_VERSION_MINOR 0)
set(CHTL_VERSION_PATCH 0)

include("${CMAKE_CURRENT_LIST_DIR}/CHTLTargets.cmake")

# 提供CHTL::chtl_core和CHTL::chtl_shared目标
set(CHTL_LIBRARIES CHTL::chtl_core)
set(CHTL_INCLUDE_DIRS "/usr/local/include/chtl")

# 检查组件
set(CHTL_FOUND TRUE)
foreach(component ${CHTL_FIND_COMPONENTS})
    if(component STREQUAL "shared")
        if(TARGET CHTL::chtl_shared)
            set(CHTL_shared_FOUND TRUE)
        else()
            set(CHTL_shared_FOUND FALSE)
            if(CHTL_FIND_REQUIRED_shared)
                set(CHTL_FOUND FALSE)
            endif()
        endif()
    endif()
endforeach()

check_required_components(CHTL)
