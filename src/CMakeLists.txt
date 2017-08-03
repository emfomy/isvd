# The CMake setting of 'src/'

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} ${files})
  isvd_set_target(${target})
  install(TARGETS ${target} RUNTIME DESTINATION ${LIB_FOLDER})
endmacro()

# file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
# set_target(isvd.a ${files})
