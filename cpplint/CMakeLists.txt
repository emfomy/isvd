# The CMake setting of 'cpplint/'

# Find CppLint
find_program(CMAKE_CPPLINT cpplint)
mark_as_advanced(CMAKE_CPPLINT)

# Macro
function(SET_CPPLINT_TARGET path)
  string(REPLACE "/" "_" target ${path})
  add_custom_target(
    cpplint_${target}
    COMMAND ${CMAKE_CPPLINT} --recursive --root=${PROJECT_CONFIG_DIR}/${path} ${ARGN} ${path}
    WORKING_DIRECTORY ${PROJECT_CONFIG_DIR}
    COMMENT "Run cpplint for ${path}"
  )
  add_dependencies(cpplint cpplint_${target})
endfunction()

# CppLint
add_custom_target(
  cpplint
  DEPENDS ${CMAKE_CPPLINT_TARGETS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Run cpplint"
)

set_cpplint_target(include/c --linelength=128 --filter=-build/include,-build/include_order,-readability/casting,-whitespace/blank_line,-whitespace/braces,-whitespace/parens)
set_cpplint_target(src --linelength=128 --filter=-build/include,-build/include_order,-build/include_what_you_use,-readability/casting,-whitespace/blank_line,-whitespace/braces,-whitespace/parens)
