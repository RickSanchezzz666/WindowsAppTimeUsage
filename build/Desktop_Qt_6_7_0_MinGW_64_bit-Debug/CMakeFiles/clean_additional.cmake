# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WindowsAppTimeUsage_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WindowsAppTimeUsage_autogen.dir\\ParseCache.txt"
  "WindowsAppTimeUsage_autogen"
  )
endif()
