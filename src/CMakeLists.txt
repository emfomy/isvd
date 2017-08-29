# The CMake setting of 'src/'

isvd_set_config_var()

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} STATIC ${files})
  isvd_set_target(${target} ".a")
  install(TARGETS ${target} ARCHIVE DESTINATION ${LIB_FOLDER})
endmacro()

# Disable asserts
# list(APPEND DEFS "NDEBUG")

# Set include paths
include_directories("${PROJECT_CONFIG_DIR}/include/c")
include_directories("${CMAKE_CURRENT_CONFIG_DIR}")

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_D_TYPES}")
isvd_configure_in_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}")

# libisvd
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/*")
set_target(isvd "${files}")
