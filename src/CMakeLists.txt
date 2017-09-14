# The CMake setting of 'src/'

isvd_set_config_var()

# Shared library
SET(BUILD_SHARED_LIBS ON)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_FOLDER}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_D_TYPES}")
isvd_configure_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}")

add_subdirectory(include)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_CONFIG_DIR}/include" "${PROJECT_BINARY_DIR}/include")

add_subdirectory(lib)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_CONFIG_DIR}/lib" "${PROJECT_BINARY_DIR}/lib")
