# Create configure files
function(ISVD_CONFIGURE_FN)
  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/*.in"
  )
  foreach(cfgfile ${cfgfiles})
    string(REGEX REPLACE "\\.in$" "" file ${cfgfile})
    configure_file(
      "${PROJECT_SOURCE_DIR}/${cfgfile}"
      "${PROJECT_BINARY_DIR}/${file}"
      @ONLY
    )
  endforeach()
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/*.in"
  )
  foreach(cfgfile ${cfgfiles})
    string(REGEX REPLACE "\\.in$" "" file ${cfgfile})
    configure_file(
      "${PROJECT_BINARY_DIR}/${cfgfile}"
      "${PROJECT_BINARY_DIR}/${file}"
      @ONLY
    )
  endforeach()
endfunction()

isvd_configure_fn()
unset(isvd_configure_fn)

# Set install rule
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_BINARY_DIR}/include/" DESTINATION include PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/share/"   DESTINATION share   PATTERN "*.in" EXCLUDE)
install(DIRECTORY "${PROJECT_BINARY_DIR}/share/"   DESTINATION share   PATTERN "*.in" EXCLUDE)
