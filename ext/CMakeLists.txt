# The CMake setting of 'ext/'

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} ${files})
  target_compile_definitions(${target} PUBLIC "NDEBUG")
  set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-w")
endmacro()

# Disable asserts
list(APPEND DEFS "NDEBUG")

# mmio
set_target(extmmio  ${CMAKE_CURRENT_SOURCE_DIR}/mmio/mmio.c)
set_target(extmmiox ${CMAKE_CURRENT_SOURCE_DIR}/mmio/mmio.cxx)
