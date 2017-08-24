# The CMake setting of 'src/'

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} ${files})
  isvd_set_target(${target} ".a")
  install(TARGETS ${target} ARCHIVE DESTINATION ${LIB_FOLDER})
endmacro()

# Disable asserts
# list(APPEND DEFS "NDEBUG")

# Set include paths
include_directories(
  "${PROJECT_BINARY_DIR}/include/c"
  "${PROJECT_SOURCE_DIR}/include/c"
)

# libisvd
file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/libisvd/*"
                        "${CMAKE_CURRENT_BINARY_DIR}/libisvd/*")
set_target(isvd "${files}")
