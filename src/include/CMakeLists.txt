# The CMake setting of 'src/include/'

isvd_set_config_var()

# Set install rule
install(DIRECTORY "${CMAKE_CURRENT_CONFIG_DIR}/c/" DESTINATION include/c)
