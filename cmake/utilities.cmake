# Set target
macro(ISVD_SET_TARGET target ext)
  set_target_properties(${target} PROPERTIES SUFFIX "${BIN_SUFFIX}${ext}")
  target_include_directories(${target} SYSTEM PUBLIC ${INCS})
  target_link_libraries(${target} ${LIBS})
  target_compile_definitions(${target} PUBLIC ${DEFS})
  set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})
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

# Variables
string(ASCII 27 Esc)
