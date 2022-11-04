# define header file that points to unit test source files
set(UNITTESTS_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/unittests_config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/unittests_config.h")

# link ctest to unit tests
include(GoogleTest)

macro(vanguard_gtest_suite target)
  gtest_discover_tests(${target})
  list(APPEND VANGUARD_UNIT_TESTS ${target})
endmacro()

add_executable(VanguardUnitTests
    vanguard-unittests.cpp
)

target_include_directories(VanguardUnitTests PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}"
  )

target_link_libraries(VanguardUnitTests PUBLIC
  GTest::gtest_main
)
vanguard_gtest_suite(VanguardUnitTests)

add_custom_target(check-unit
  DEPENDS ${VANGUARD_UNIT_TESTS}
  COMMAND "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target test
)
