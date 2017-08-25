# Create configure files
function(ISVD_CONFIGURE_X_FN cfgdir outdir)
  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${cfgdir}" "${cfgdir}/*\@x\@*.xin"
  )
  set(X D)
  set(x d)
  set(xtype double)
  foreach(cfgfile ${cfgfiles})
    string(REGEX REPLACE "\@x\@" "d" outfile ${cfgfile})
    string(REGEX REPLACE "\\.xin$" "" outfile ${outfile})
    configure_file(
      "${cfgdir}/${cfgfile}"
      "${outdir}/${outfile}"
      @ONLY
    )
  endforeach()
  unset(X)
  unset(x)
  unset(xtype)
endfunction()

function(ISVD_CONFIGURE_IN_FN cfgdir outdir)
  string(REPLACE ";" " " DEFS_STR "${DEFS}")
  file(
    GLOB_RECURSE cfgfiles
    RELATIVE "${cfgdir}" "${cfgdir}/*.in"
  )
  foreach(cfgfile ${cfgfiles})
    string(REGEX REPLACE "\\.in$" "" outfile ${cfgfile})
    configure_file(
      "${cfgdir}/${cfgfile}"
      "${outdir}/${outfile}"
      @ONLY
    )
  endforeach()
endfunction()

isvd_configure_x_fn("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
isvd_configure_x_fn("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}")
isvd_configure_in_fn("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
isvd_configure_in_fn("${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}")
unset(isvd_configure_x_fn)
unset(isvd_configure_in_fn)
