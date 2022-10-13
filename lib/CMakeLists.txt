#interface library 
add_library(libVanguard 
  detectors/DetectorRegistry.cpp
)

target_include_directories(libVanguard PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_executable(Vanguard
  Vanguard.cpp
)

target_link_libraries(Vanguard PUBLIC libVanguard)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_subdirectory(detectors)
add_subdirectory(analysis)
add_subdirectory(domain)
add_subdirectory(program)

target_include_directories(Vanguard PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:lib>  # <prefix>/include/mylib
)

set(LLVM_LINK_COMPONENTS
  LLVM
  #AllTargetsAsmParsers
  #AllTargetsCodeGens
  #AllTargetsDescs
  #AllTargetsInfos
  #AggressiveInstCombine
  LLVMAnalysis
  LLVMAsmParser
  LLVMBitWriter
  LLVMCodeGen
  LLVMCore
  LLVMCoroutines
  LLVMExtensions
  #IPO
  LLVMIRReader
  LLVMInstCombine
  LLVMInstrumentation
  LLVMMC
  LLVMObjCARCOpts
  LLVMRemarks
  LLVMScalarOpts
  LLVMSupport
  LLVMTarget
  LLVMTransformUtils
  LLVMVectorize
  LLVMPasses
)

target_link_libraries(Vanguard PUBLIC
  ${LLVM_LINK_COMPONENTS}
  ${SVF_LIB}
)
