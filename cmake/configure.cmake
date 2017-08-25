# Create configure files
function(ISVD_CONFIGURE_X_FN cfgdir outdir xtypes)
  isvd_set_types(${xtypes})

  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${cfgdir}" "${cfgdir}/*\@x\@*.in"
  )
  foreach(cfgfile ${cfgfiles})
    string(REGEX REPLACE "\@x\@" "${x}" outfile ${cfgfile})
    string(REGEX REPLACE "\\.in$" "" outfile ${outfile})
    configure_file(
      "${cfgdir}/${cfgfile}"
      "${outdir}/${outfile}"
      @ONLY
    )
  endforeach()
endfunction()

function(ISVD_CONFIGURE_IN_FN cfgdir outdir)
  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${cfgdir}" "${cfgdir}/*.in"
  )
  foreach(cfgfile ${cfgfiles})
    if(NOT cfgfile MATCHES "\@")
      string(REGEX REPLACE "\\.in$" "" outfile ${cfgfile})
      configure_file(
        "${cfgdir}/${cfgfile}"
        "${outdir}/${outfile}"
        @ONLY
      )
    endif()
  endforeach()
endfunction()

isvd_configure_x_fn("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}" "${ISVD_S_TYPES}")
isvd_configure_x_fn("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" "${ISVD_D_TYPES}")
isvd_configure_x_fn("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}" "${ISVD_D_TYPES}")
isvd_configure_in_fn("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
isvd_configure_in_fn("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}")
unset(isvd_configure_x_fn)
unset(isvd_configure_in_fn)
