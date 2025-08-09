file(REMOVE_RECURSE
  "libchtl_predefine.a"
  "libchtl_predefine.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/chtl_predefine.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
