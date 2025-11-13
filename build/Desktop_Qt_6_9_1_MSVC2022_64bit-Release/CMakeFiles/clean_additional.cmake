# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\zzz_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\zzz_autogen.dir\\ParseCache.txt"
  "zzz_autogen"
  )
endif()
