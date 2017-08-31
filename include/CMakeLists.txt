# The CMake setting of 'include/'

isvd_set_config_var()

# Configure files
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}" "${ISVD_D_TYPES}")
isvd_configure_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}")

# Set install rule
install(DIRECTORY "${CMAKE_CURRENT_CONFIG_DIR}/c/" DESTINATION include/c)
