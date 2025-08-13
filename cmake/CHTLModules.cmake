# CHTLModules.cmake - CHTL模块打包和部署功能
#
# 功能：
# - 扫描module目录中的CMOD/CJMOD
# - 自动打包符合标准的模块
# - 将打包好的模块复制到输出目录

include(CMakeParseArguments)

# 检查模块是否为有效的CMOD
function(is_valid_cmod module_path result_var)
    set(${result_var} FALSE PARENT_SCOPE)
    
    # 检查必需的目录结构
    if(NOT IS_DIRECTORY "${module_path}/src")
        return()
    endif()
    
    if(NOT IS_DIRECTORY "${module_path}/info")
        return()
    endif()
    
    # 获取模块名
    get_filename_component(module_name "${module_path}" NAME)
    
    # 检查info文件是否存在
    if(NOT EXISTS "${module_path}/info/${module_name}.chtl")
        return()
    endif()
    
    # 检查src目录是否有.chtl文件
    file(GLOB chtl_files "${module_path}/src/*.chtl")
    if(chtl_files)
        set(${result_var} TRUE PARENT_SCOPE)
    endif()
endfunction()

# 检查模块是否为有效的CJMOD
function(is_valid_cjmod module_path result_var)
    set(${result_var} FALSE PARENT_SCOPE)
    
    # 检查必需的目录结构
    if(NOT IS_DIRECTORY "${module_path}/src")
        return()
    endif()
    
    if(NOT IS_DIRECTORY "${module_path}/info")
        return()
    endif()
    
    # 获取模块名
    get_filename_component(module_name "${module_path}" NAME)
    
    # 检查info文件是否存在
    if(NOT EXISTS "${module_path}/info/${module_name}.chtl")
        return()
    endif()
    
    # 检查src目录是否有C++源文件
    file(GLOB cpp_files "${module_path}/src/*.cpp" "${module_path}/src/*.cc" "${module_path}/src/*.cxx")
    file(GLOB h_files "${module_path}/src/*.h" "${module_path}/src/*.hpp" "${module_path}/src/*.hxx")
    
    if(cpp_files OR h_files)
        set(${result_var} TRUE PARENT_SCOPE)
    endif()
endfunction()

# 打包CMOD模块
function(pack_cmod module_path output_dir)
    # 从module.info读取实际的模块名
    set(module_info_file "${module_path}/info/module.info")
    if(EXISTS "${module_info_file}")
        file(STRINGS "${module_info_file}" module_info_lines)
        foreach(line ${module_info_lines})
            if(line MATCHES "^name[ ]*=[ ]*(.+)")
                string(STRIP "${CMAKE_MATCH_1}" module_name)
                break()
            endif()
        endforeach()
    endif()
    
    # 如果无法从module.info读取，使用目录名
    if(NOT module_name)
        get_filename_component(module_name "${module_path}" NAME)
    endif()
    
    set(output_file "${output_dir}/${module_name}.cmod")
    
    message(STATUS "Packing CMOD: ${module_name} from ${module_path}")
    
    # 创建临时目录
    set(temp_dir "${CMAKE_CURRENT_BINARY_DIR}/temp_cmod_${module_name}")
    file(MAKE_DIRECTORY "${temp_dir}")
    
    # 收集需要打包的文件
    set(files_to_pack "")
    
    # 添加src目录下的所有文件
    file(GLOB_RECURSE src_files RELATIVE "${module_path}" "${module_path}/src/*")
    foreach(file ${src_files})
        list(APPEND files_to_pack "${file}")
    endforeach()
    
    # 添加info目录下的所有文件
    file(GLOB_RECURSE info_files RELATIVE "${module_path}" "${module_path}/info/*")
    foreach(file ${info_files})
        list(APPEND files_to_pack "${file}")
    endforeach()
    
    # 创建文件列表
    set(file_list_path "${temp_dir}/files.txt")
    file(WRITE "${file_list_path}" "")
    foreach(file ${files_to_pack})
        file(APPEND "${file_list_path}" "${file}\n")
    endforeach()
    
    # 使用tar创建归档（如果可用）
    find_program(TAR_EXECUTABLE tar)
    if(TAR_EXECUTABLE)
        execute_process(
            COMMAND ${TAR_EXECUTABLE} -czf "${output_file}" -C "${module_path}" ${files_to_pack}
            WORKING_DIRECTORY "${module_path}"
            RESULT_VARIABLE tar_result
        )
        if(NOT tar_result EQUAL 0)
            message(WARNING "Failed to pack CMOD ${module_name} using tar")
        else()
            message(STATUS "Successfully packed CMOD: ${output_file}")
        endif()
    else()
        # 回退到简单的文本打包格式
        message(STATUS "tar not found, using simple text format for CMOD")
        
        # 创建简单的文本归档格式
        file(WRITE "${output_file}" "CHTL_CMOD_ARCHIVE_V1\n")
        file(APPEND "${output_file}" "MODULE:${module_name}\n")
        file(APPEND "${output_file}" "FILES:${list_length}\n")
        
        foreach(file ${files_to_pack})
            file(READ "${module_path}/${file}" file_content)
            string(LENGTH "${file_content}" file_size)
            file(APPEND "${output_file}" "FILE:${file}:${file_size}\n")
            file(APPEND "${output_file}" "${file_content}\n")
        endforeach()
        
        file(APPEND "${output_file}" "END_ARCHIVE\n")
        message(STATUS "Successfully packed CMOD (text format): ${output_file}")
    endif()
    
    # 清理临时目录
    file(REMOVE_RECURSE "${temp_dir}")
endfunction()

# 编译并打包CJMOD模块
function(pack_cjmod module_path output_dir)
    get_filename_component(module_name "${module_path}" NAME)
    
    message(STATUS "Building and packing CJMOD: ${module_name}")
    
    # 收集源文件
    file(GLOB cpp_sources "${module_path}/src/*.cpp" "${module_path}/src/*.cc" "${module_path}/src/*.cxx")
    file(GLOB h_sources "${module_path}/src/*.h" "${module_path}/src/*.hpp" "${module_path}/src/*.hxx")
    
    if(NOT cpp_sources)
        message(WARNING "No C++ source files found for CJMOD ${module_name}")
        return()
    endif()
    
    # 创建共享库
    set(lib_name "cjmod_${module_name}")
    add_library(${lib_name} SHARED ${cpp_sources})
    
    # 设置属性
    set_target_properties(${lib_name} PROPERTIES
        PREFIX ""
        OUTPUT_NAME "${module_name}"
        SUFFIX ".cjmod"
        RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY "${output_dir}"
    )
    
    # 添加包含目录
    target_include_directories(${lib_name} PRIVATE
        "${module_path}/src"
        "${CMAKE_SOURCE_DIR}/src/chtl"  # CHTL头文件
        "${CMAKE_SOURCE_DIR}/src/chtljs" # CHTL JS头文件
    )
    
    # 设置C++标准
    target_compile_features(${lib_name} PRIVATE cxx_std_17)
    
    # 添加必要的编译选项
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${lib_name} PRIVATE
            -fPIC
            -Wall
            -Wextra
            -O2
        )
    endif()
    
    # 复制info文件到输出目录
    add_custom_command(
        TARGET ${lib_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${output_dir}/${module_name}_info"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
            "${module_path}/info" 
            "${output_dir}/${module_name}_info"
        COMMENT "Copying CJMOD info files for ${module_name}"
    )
    
    message(STATUS "CJMOD ${module_name} will be built as shared library")
endfunction()

# 扫描并处理所有模块
function(process_chtl_modules)
    cmake_parse_arguments(
        ARG
        ""
        "SOURCE_DIR;OUTPUT_DIR"
        ""
        ${ARGN}
    )
    
    if(NOT ARG_SOURCE_DIR)
        set(ARG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/module")
    endif()
    
    if(NOT ARG_OUTPUT_DIR)
        set(ARG_OUTPUT_DIR "${CMAKE_BINARY_DIR}/module")
    endif()
    
    # 创建输出目录
    file(MAKE_DIRECTORY "${ARG_OUTPUT_DIR}")
    
    message(STATUS "Scanning for CHTL modules in: ${ARG_SOURCE_DIR}")
    
    # 扫描module目录
    if(NOT EXISTS "${ARG_SOURCE_DIR}")
        message(STATUS "Module directory not found: ${ARG_SOURCE_DIR}")
        return()
    endif()
    
    # 递归扫描模块目录，支持嵌套结构
    file(GLOB_RECURSE module_info_files "${ARG_SOURCE_DIR}/*/info/module.info")
    
    set(cmod_count 0)
    set(cjmod_count 0)
    
    foreach(info_file ${module_info_files})
        # 获取模块目录（info文件的父目录的父目录）
        get_filename_component(info_dir "${info_file}" DIRECTORY)
        get_filename_component(candidate "${info_dir}" DIRECTORY)
        
        # 检查是否为CMOD
        is_valid_cmod("${candidate}" is_cmod)
        if(is_cmod)
            pack_cmod("${candidate}" "${ARG_OUTPUT_DIR}")
            math(EXPR cmod_count "${cmod_count} + 1")
            continue()
        endif()
        
        # 检查是否为CJMOD
        is_valid_cjmod("${candidate}" is_cjmod)
        if(is_cjmod)
            pack_cjmod("${candidate}" "${ARG_OUTPUT_DIR}")
            math(EXPR cjmod_count "${cjmod_count} + 1")
            continue()
        endif()
            
    endforeach()
    
    message(STATUS "Found ${cmod_count} CMOD(s) and ${cjmod_count} CJMOD(s)")
    
    # 创建模块索引文件
    set(index_file "${ARG_OUTPUT_DIR}/modules.index")
    file(WRITE "${index_file}" "# CHTL Module Index\n")
    file(APPEND "${index_file}" "# Generated by CMake\n\n")
    file(APPEND "${index_file}" "CMOD_COUNT=${cmod_count}\n")
    file(APPEND "${index_file}" "CJMOD_COUNT=${cjmod_count}\n\n")
    
    # 列出所有模块
    file(GLOB cmod_files "${ARG_OUTPUT_DIR}/*.cmod")
    file(GLOB cjmod_files "${ARG_OUTPUT_DIR}/*.cjmod")
    
    file(APPEND "${index_file}" "[CMOD]\n")
    foreach(cmod ${cmod_files})
        get_filename_component(cmod_name "${cmod}" NAME_WE)
        file(APPEND "${index_file}" "${cmod_name}\n")
    endforeach()
    
    file(APPEND "${index_file}" "\n[CJMOD]\n")
    foreach(cjmod ${cjmod_files})
        get_filename_component(cjmod_name "${cjmod}" NAME_WE)
        file(APPEND "${index_file}" "${cjmod_name}\n")
    endforeach()
    
    message(STATUS "Module index written to: ${index_file}")
endfunction()

# 添加自定义目标来手动触发模块打包
function(add_module_packing_target)
    add_custom_target(pack-modules
        COMMAND ${CMAKE_COMMAND} 
            -DCMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}
            -DCMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}
            -P ${CMAKE_SOURCE_DIR}/cmake/PackModules.cmake
        COMMENT "Packing CHTL modules..."
    )
endfunction()