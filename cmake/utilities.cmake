# Set target
macro(ISVD_SET_TARGET target ext)
  set_target_properties(${target} PROPERTIES SUFFIX "${BIN_SUFFIX}${ext}")
  target_include_directories(${target} SYSTEM PUBLIC ${INCS})
  target_link_libraries(${target} ${LIBS})
  target_compile_definitions(${target} PUBLIC ${DEFS})
  set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  set_target_properties(${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})
endmacro()

# Variables
string(ASCII 27 Esc)
