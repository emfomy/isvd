# The CMake setting of 'src/'

# Break
if(NOT MCNLA_BUILD_LIB)
  return()
endif()

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} ${files})
  isvd_set_target(${target} ".a")
  install(TARGETS ${target} ARCHIVE DESTINATION ${LIB_FOLDER})
endmacro()

file(GLOB_RECURSE files ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
set_target(isvd "${files}")
