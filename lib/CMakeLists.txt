set(LLVM_LINK_COMPONENTS
  LLVMAnalysis
  LLVMAsmParser
  LLVMBitWriter
  LLVMCodeGen
  LLVMCore
  LLVMSupport
  LLVMPasses
)

add_library(libVanguard)
target_link_libraries(libVanguard
  PUBLIC
  SVF::Svf
  ${LLVM_LINK_COMPONENTS}
)
target_include_directories(libVanguard PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>" #TODO: Change install interface?
)

add_subdirectory(detectors)
add_subdirectory(analysis)
add_subdirectory(domain)
add_subdirectory(program)


add_executable(Vanguard
  Vanguard.cpp
)
target_link_libraries(Vanguard PRIVATE libVanguard)

# TODO - set the build folder as where the executable is created