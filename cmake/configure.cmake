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
set(PROJECT_CONFIG_DIR "${PROJECT_BINARY_DIR}/tmp")
macro(ISVD_SET_CONFIG_VAR)
  file(RELATIVE_PATH CMAKE_CURRENT_CONFIG_DIR ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
  set(CMAKE_CURRENT_CONFIG_DIR "${PROJECT_CONFIG_DIR}/${CMAKE_CURRENT_CONFIG_DIR}")
endmacro()

# Set types
macro(ISVD_SET_TYPES x_ xtype_ x_type_ XName_ XStr_)
  string(TOLOWER "${x_}" x)
  string(TOUPPER "${x_}" X)

  set(xtype ${xtype_})

  string(TOUPPER "${x_type_}" X_TYPE)

  string(TOLOWER "${XName_}" xname)
  set(XName "${XName_}")

  set(XStr "${XStr_}")
endmacro()

unset(ISVD_S_TYPES)
unset(ISVD_D_TYPES)
unset(ISVD_C_TYPES)
unset(ISVD_Z_TYPES)
list(APPEND ISVD_S_TYPES "s" "float"          "float"          "Real Single"    "RealSingle")
list(APPEND ISVD_D_TYPES "d" "double"         "double"         "Real Double"    "RealDouble")
list(APPEND ISVD_C_TYPES "c" "complex float"  "complex_float"  "Complex Single" "ComplexSingle")
list(APPEND ISVD_Z_TYPES "z" "complex double" "complex_double" "Complex Double" "ComplexDouble")

# Add to clean rule
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_CONFIG_DIR}")
