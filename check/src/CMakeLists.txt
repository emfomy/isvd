# The CMake setting of 'check/src'

isvd_set_config_var()

# Configure files
file(COPY "${PROJECT_CONFIG_DIR}/src/" DESTINATION "${CMAKE_CURRENT_CONFIG_DIR}")
file(GLOB_RECURSE cfiles "${CMAKE_CURRENT_CONFIG_DIR}/*.c")
foreach(cfile ${cfiles})
  string(REGEX REPLACE "\\.c$" ".cxx" cxxfile ${cfile})
  file(RENAME ${cfile} ${cxxfile})
endforeach()

file(RENAME "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/param.cxx"
            "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/param.c")

# checkisvd
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/*")
add_library(checkisvd EXCLUDE_FROM_ALL ${files})
isvd_set_target(checkisvd ".a")
