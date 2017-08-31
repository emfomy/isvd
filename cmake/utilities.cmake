# Set target
macro(ISVD_SET_TARGET target ext)
  set_target_properties(${target} PROPERTIES SUFFIX "${BIN_SUFFIX}${ext}")

  if(INCS)
    target_include_directories(${target} SYSTEM PUBLIC ${INCS})
  endif()

  if(LIBS)
    target_link_libraries(${target} ${LIBS})
  endif()

  if(DEFS)
    target_compile_definitions(${target} PUBLIC ${DEFS})
  endif()

  if(COMFLGS)
    set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${COMFLGS})
  endif()

  if(LNKFLGS)
    set_target_properties(${target} PROPERTIES LINK_FLAGS    ${LNKFLGS})
  endif()
endmacro()

# Variables
string(ASCII 27 Esc)
