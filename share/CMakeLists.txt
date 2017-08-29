# The CMake setting of 'share/'

isvd_set_config_var()

# Configure files
isvd_configure_in_fn("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_CONFIG_DIR}")

# Set install rule
install(DIRECTORY "${CMAKE_CURRENT_CONFIG_DIR}/isvd" DESTINATION share/isvd)
