# Configure functions
function(ISVD_CONFIGURE_IN_FN srcdir outdir)
  message(STATUS "Configure files in ${srcdir}")
  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${srcdir}" "${srcdir}/*"
  )
  foreach(cfgfile ${cfgfiles})
    if(NOT cfgfile MATCHES "\@")
      configure_file(
        "${srcdir}/${cfgfile}"
        "${outdir}/${cfgfile}"
        @ONLY
      )
    endif()
  endforeach()
endfunction()

function(ISVD_CONFIGURE_X_FN srcdir outdir xtypes)
  isvd_set_types(${xtypes})

  message(STATUS "Configure files in ${srcdir} for ${xname} precision")

  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${srcdir}" "${srcdir}/*\@x\@*"
  )
  foreach(cfgfile ${cfgfiles})
    string(REGEX REPLACE "\@x\@" "${x}" outfile ${cfgfile})
    configure_file(
      "${srcdir}/${cfgfile}"
      "${outdir}/${outfile}"
      @ONLY
    )
  endforeach()
endfunction()

# Set configure variables
set(CONFIG_DIR_NAME "tmp")
set(PROJECT_CONFIG_DIR "${PROJECT_BINARY_DIR}/${CONFIG_DIR_NAME}")
macro(ISVD_SET_CONFIG_VAR)
  file(RELATIVE_PATH CMAKE_CURRENT_CONFIG_DIR ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
  set(CMAKE_CURRENT_CONFIG_DIR "${PROJECT_CONFIG_DIR}/${CMAKE_CURRENT_CONFIG_DIR}")
endmacro()

# Clean configure folder
add_custom_target(
  ${CONFIG_DIR_NAME}clean
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${PROJECT_CONFIG_DIR}"
  COMMENT "Clean configure folder"
)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_CONFIG_DIR}")
