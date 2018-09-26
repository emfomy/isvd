# The CMake setting of 'cpplint/'

# Find CppLint
find_program(CMAKE_CPPLINT cpplint)
mark_as_advanced(CMAKE_CPPLINT)

# Break
if(NOT CMAKE_CPPLINT)

  # Add rule 'cpplint'
  add_custom_target(
    cpplint
    COMMAND eval "exit 1"
    COMMENT "${Esc}[1;33mWarning: 'cpplint' not found! Please set 'CMAKE_CPPLINT' using ccmake${Esc}[0m."
  )

  return()
endif()

# Macro
function(SET_CPPLINT_TARGET path linelength filter)
  string(REPLACE "/" "_" target ${path})
  add_custom_command(
    TARGET cpplint POST_BUILD
    COMMAND ${CMAKE_CPPLINT} --recursive --root="${PROJECT_BINARY_DIR}/${path}" --linelength=${linelength} --filter=${filter} ${path}
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    COMMENT "Run cpplint for ${path}"
  )
endfunction()

# CppLint
add_custom_target(
  cpplint
  DEPENDS ${CMAKE_CPPLINT_TARGETS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Run cpplint"
)

set_cpplint_target(tmp/src/include/c 128 "-build/include,-build/include_order,-readability/casting,-whitespace/blank_line,-whitespace/braces,-whitespace/parens")
set_cpplint_target(tmp/src/lib 128 "-build/include,-build/include_order,-build/include_what_you_use,-readability/casting,-whitespace/blank_line,-whitespace/braces,-whitespace/parens")
