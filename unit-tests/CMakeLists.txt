include(GoogleTest)

macro(vanguard_gtest_suite target)
  gtest_discover_tests(${target})
  list(APPEND VANGUARD_UNIT_TESTS ${target})
endmacro() 

add_executable(ExampleTest
    Example.cpp
)
target_link_libraries(ExampleTest PUBLIC 
  GTest::gtest_main
)
vanguard_gtest_suite(ExampleTest)

add_custom_target(check-unit
  DEPENDS ${VANGUARD_UNIT_TESTS}
  COMMAND "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target test
)
