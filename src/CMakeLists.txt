# The CMake setting of 'src/'

isvd_set_config_var()

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_FOLDER}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Macro
macro(SET_TARGET target files)
  # Set library
  add_library(${target} SHARED ${files})
  isvd_set_target(${target} ".so")
  set_target_properties(${target} PROPERTIES VERSION ${ISVD_VERSION})
  install(TARGETS ${target} LIBRARY DESTINATION ${LIB_FOLDER})
endmacro()

# Disable asserts
# list(APPEND DEFS "NDEBUG")

# Set include paths
include_directories("${PROJECT_CONFIG_DIR}/include/c"
                    "${CMAKE_CURRENT_CONFIG_DIR}")

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_D_TYPES}")
isvd_configure_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}")

# libisvd
set_target(isvd /dev/null)
set_target_properties(isvd PROPERTIES LINKER_LANGUAGE C)

# libisvd_la
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/la/*")
set_target(isvd_la "${files}")
target_link_libraries(isvd isvd_la)

# libisvd_core
file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/core/*")
set_target(isvd_core "${files}")
target_link_libraries(isvd_core isvd_la)
target_link_libraries(isvd isvd_core)

# libisvd_gpu
if(ISVD_USE_GPU)
  file(GLOB_RECURSE files "${CMAKE_CURRENT_CONFIG_DIR}/libisvd/gpu/*")
  set_target(isvd_gpu "${files}")
  target_link_libraries(isvd_gpu isvd_core)
  target_link_libraries(isvd isvd_gpu)
endif(ISVD_USE_GPU)
