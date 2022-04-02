add_library(Vanguard SHARED
        # List your source files here.
        # Skeleton.cpp
        TaintAnalysis.cpp
        TaintAnalysis.h
        Analysis.h
        Taint.cpp
        Taint.h
        IntraproceduralVanguard.cpp
        IntraproceduralVanguard.h
        LocalVanguard.cpp
        LocalVanguard.h SCCVanguard.cpp SCCVanguard.h Vanguard.h Vanguard.cpp ReadWriteRetriever.cpp ReadWriteRetriever.h Val.h RegisterVal.cpp RegisterVal.h TaintLabel.cpp TaintLabel.h TaintSink.h TaintSource.h TaintNode.h TaintSink.cpp TaintNode.cpp TaintSummary.cpp TaintSummary.h TaintLabelStore.cpp TaintLabelStore.h FunctionTaintSource.cpp FunctionTaintSource.h FunctionTaintSink.cpp FunctionTaintSink.h Val.cpp TaintSummaryStore.cpp TaintSummaryStore.h detectors/TaintTest/TaintExample.cpp detectors/TaintTest/TaintExample.h detectors/TaintTest/AnalysisExample.cpp detectors/TaintTest/AnalysisExample.h detectors/TaintTest/ExampleSource.cpp detectors/TaintTest/ExampleSource.h detectors/TaintTest/ExampleSink.cpp detectors/TaintTest/ExampleSink.h TaintSinkProvider.h MemoryTaint.cpp MemoryTaint.h RegisterTaint.cpp RegisterTaint.h StorageTaint.cpp StorageTaint.h MemoryVal.cpp MemoryVal.h StorageVal.cpp StorageVal.h AAWrapper.cpp AAWrapper.h)

if(DEFINED ENV{Z3_HOME})
  set(ENV{Z3_DIR} $ENV{Z3_HOME})
endif()

if(DEFINED ENV{LIBBLOCKCHAIN_HOME})
  message(STATUS "LIBBLOCKCHAIN_HOME: ${LIBBLOCKCHAIN_HOME}")
  set(ENV{LIBBLOCKCHAIN_DIR} $ENV{LIBBLOCKCHAIN_HOME})
endif()

find_package(libBlockchain
        REQUIRED
        CONFIG)

find_package(Z3
  REQUIRED
  CONFIG
  # `NO_DEFAULT_PATH` is set so that -DZ3_DIR has to be passed to find Z3.
  # This should prevent us from accidentally picking up an installed
  # copy of Z3. This is here to benefit Z3's build system when building
  # this project. When making your own project you probably shouldn't
  # use this option.
  #NO_DEFAULT_PATH
)

add_subdirectory(detectors)

message(STATUS "Z3_FOUND: ${Z3_FOUND}")
message(STATUS "Found Z3 ${Z3_VERSION_STRING}")
message(STATUS "Z3_DIR: ${Z3_DIR}")

message(STATUS "Found libBlockchain ${LIBBLOCKCHAIN_VERSION_STRING}")
message(STATUS "LIBBLOCKCHAIN_DIR: $ENV{LIBBLOCKCHAIN_DIR}")

target_include_directories(Vanguard PRIVATE ${Z3_CXX_INCLUDE_DIRS})
target_include_directories(Vanguard PRIVATE ${LIBBLOCKCHAIN_INCLUDE_DIRS})
target_link_libraries(Vanguard PRIVATE ${Z3_LIBRARIES})
target_link_libraries(Vanguard PRIVATE BlockchainStatic)

target_compile_options(Vanguard PRIVATE ${Z3_COMPONENT_CXX_FLAGS})

if (CMAKE_SYSTEM_NAME MATCHES "[Ww]indows")
  # On Windows we need to copy the Z3 libraries
  # into the same directory as the executable
  # so that they can be found.
  foreach (z3_lib ${Z3_LIBRARIES})
    message(STATUS "Adding copy rule for ${z3_lib}")
    add_custom_command(TARGET Vanguard
      POST_BUILD
      COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${z3_lib}>
        $<TARGET_FILE_DIR:cpp_example>
    )
  endforeach()
endif()

# Use C++11 to compile your pass (i.e., supply -std=c++11).
target_compile_features(Vanguard PRIVATE cxx_range_for cxx_auto_type)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(Vanguard PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(Vanguard PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

