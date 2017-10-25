# The CMake setting of 'src/include/'

isvd_set_config_var()

# Set 'include' folder
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_CONFIG_DIR}" "${PROJECT_BINARY_DIR}/include")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_BINARY_DIR}/include")

# Set install rule
install(DIRECTORY "${CMAKE_CURRENT_CONFIG_DIR}/c/" DESTINATION include/c)
