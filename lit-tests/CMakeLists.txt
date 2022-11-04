find_program(LLVM_EXTERNAL_LIT NAMES lit llvm-lit ${LLVM_EXTERNAL_LIT})
if (LLVM_EXTERNAL_LIT STREQUAL "LLVM_EXTERNAL_LIT-NOTFOUND")
  message(WARNING "lit not found, C++-only lit tests will not be run")  # curr issue is we don't setup lit-check
else()
  message(STATUS "Using lit: ${LLVM_EXTERNAL_LIT}")
  configure_lit_site_cfg(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
    MAIN_CONFIG
      ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
  )

  add_lit_testsuite(check-lit "Running the lit-based regression tests"
    ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS libVanguard
  )

endif()