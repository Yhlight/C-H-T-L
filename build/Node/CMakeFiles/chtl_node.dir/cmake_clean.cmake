file(REMOVE_RECURSE
  "libchtl_node.a"
  "libchtl_node.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/chtl_node.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
