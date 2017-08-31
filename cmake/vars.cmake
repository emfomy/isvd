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

# BLAS definitions
set(
  ISVD_LA_BLAS_TYPE_DEFINE
  "#define CHAR1 char"
  "#define INT   isvd_int_t"
  "#define REAL4 float"
  "#define REAL8 double"
  "#define COMP4 complex float"
  "#define COMP8 complex double"
)
string(REPLACE ";" "\n" ISVD_LA_BLAS_TYPE_DEFINE "${ISVD_LA_BLAS_TYPE_DEFINE}")

set(
  ISVD_LA_BLAS_TYPE_UNDEF
  "#undef CHAR1"
  "#undef INT"
  "#undef REAL4"
  "#undef REAL8"
  "#undef COMP4"
  "#undef COMP8"
)
string(REPLACE ";" "\n" ISVD_LA_BLAS_TYPE_UNDEF "${ISVD_LA_BLAS_TYPE_UNDEF}")
