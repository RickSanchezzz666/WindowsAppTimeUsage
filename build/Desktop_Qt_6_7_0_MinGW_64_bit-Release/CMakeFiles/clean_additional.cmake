# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\TimeUsage_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TimeUsage_autogen.dir\\ParseCache.txt"
  "TimeUsage_autogen"
  )
endif()
