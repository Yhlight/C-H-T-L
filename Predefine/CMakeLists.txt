add_library(chtl_predefine STATIC
    Registry.h
    PredefinedCustomElements.h
    PredefinedCustomStyles.h
    PredefinedCustomVariables.h
    PredefinedTemplateElements.h
    PredefinedTemplateStyles.h
    PredefinedTemplateVariables.h
)

target_include_directories(chtl_predefine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chtl_predefine PUBLIC chtl_common)

if (MSVC)
    target_compile_options(chtl_predefine PRIVATE /W4 /permissive-)
else()
    target_compile_options(chtl_predefine PRIVATE -Wall -Wextra -Wpedantic)
endif()