# Types definitions
macro(ISVD_SET_TYPES x_ xtype_ XName_ XStr_)
  string(TOLOWER "${x_}" x)
  string(TOUPPER "${x_}" X)

  set(xtype_____ ${xtype_})

  string(TOUPPER "${xtype_}" XTYPE)

  string(TOLOWER "${XName_}" xname)
  set(XName "${XName_}")

  set(XStr "${XStr_}")
endmacro()

unset(ISVD_S_TYPES)
unset(ISVD_D_TYPES)
unset(ISVD_C_TYPES)
unset(ISVD_Z_TYPES)
list(APPEND ISVD_S_TYPES "s" "isvd_s_val_t" "Real Single"    "RealSingle")
list(APPEND ISVD_D_TYPES "d" "isvd_d_val_t" "Real Double"    "RealDouble")
list(APPEND ISVD_C_TYPES "c" "isvd_c_val_t" "Complex Single" "ComplexSingle")
list(APPEND ISVD_Z_TYPES "z" "isvd_z_val_t" "Complex Double" "ComplexDouble")

# BLAS definitions
set(
  ISVD_TYPE_MACRO_DEFINE
  "#define CHAR1 char"
  "#define INT   isvd_int_t"
  "#define REAL4 isvd_s_val_t"
  "#define REAL8 isvd_d_val_t"
  "#define COMP4 isvd_c_val_t"
  "#define COMP8 isvd_z_val_t"
)
string(REPLACE ";" "\n" ISVD_TYPE_MACRO_DEFINE "${ISVD_TYPE_MACRO_DEFINE}")

set(
  ISVD_TYPE_MACRO_UNDEF
  "#undef CHAR1"
  "#undef INT"
  "#undef REAL4"
  "#undef REAL8"
  "#undef COMP4"
  "#undef COMP8"
)
string(REPLACE ";" "\n" ISVD_TYPE_MACRO_UNDEF "${ISVD_TYPE_MACRO_UNDEF}")
