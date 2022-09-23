cmake_minimum_required(VERSION 3.14)
project(vanguard)

# we need LLVM_HOME in order to automatically set LLVM_DIR
if(NOT DEFINED ENV{LLVM_HOME})
  message(FATAL_ERROR "$LLVM_HOME is not defined")
else ()
  set(ENV{LLVM_HOME} $ENV{LLVM_HOME})
  set(ENV{LLVM_DIR} $ENV{LLVM_HOME}/lib/cmake/llvm)
endif()

find_package(LLVM 13 REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
message(${LLVM_LIBRARY_DIRS})
if (${LLVM_VERSION_MAJOR} VERSION_GREATER_EQUAL 10)
  set(CMAKE_CXX_STANDARD 14)
endif ()

add_subdirectory(lib)  # Use your pass name here.
# TODO Here: define a bunch of variables in CMAKE that can be used as string substitutes into configure file
# Pass them in as options in CMake, try to set up variables
configure_file(run.py.in ${PROJECT_SOURCE_DIR}/run.py)

### TESTING ###
option(DOWNLOAD_GTEST ON)

include(CTest)
enable_testing() 
# fetch google test directly unless installed via nix 
if (DOWNLOAD_GTEST)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
else() 
    find_package(GTest REQUIRED)
endif() 

add_subdirectory(unit-tests) 

# add catch-all target for tests 
add_custom_target(check 
  DEPENDS
  # unit test target must exist 
  $<$<BOOL:BUILD_TESTING>:check-unit>
)

## Install target

include (GNUInstallDirs)

install(TARGETS Vanguard
  EXPORT ${PROJECT_NAME}Targets
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}Targets DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
