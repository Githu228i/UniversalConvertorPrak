# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/PrakFiles_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PrakFiles_autogen.dir/ParseCache.txt"
  "PrakFiles_autogen"
  )
endif()
