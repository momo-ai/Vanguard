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

### Setting Up SVF ###
set(SVF_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SVF")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE (STATUS "building SVF in debug mode")
    if (EXISTS "${SVF_DIR}/Debug-build")
        set(SVF_LIB "${SVF_DIR}/Debug-build/lib/libSvf.a")
    else()
        set(SVF_LIB "${SVF_DIR}/Release-build/lib/libSvf.a")
    endif()
else()
    MESSAGE (STATUS "building SVF in release mode")
    set(SVF_LIB "${SVF_DIR}/Release-build/lib/libSvf.a")
endif()
set(SVF_HEADER "${SVF_DIR}/include")
include_directories("${SVF_HEADER}")
MESSAGE("${SVF_HEADER}")

## We don't need this now, leaving it here as we might need it in the future.
##set z3 env
#if (DEFINED Z3_DIR)
#    set(ENV{Z3_DIR} "${Z3_DIR}")
#endif()
#if(CMAKE_BUILD_TYPE MATCHES "Debug")
#    if(EXISTS "${Z3_DIR}/src")
#        find_package(Z3 REQUIRED CONFIG)
#        include_directories(${Z3_CXX_INCLUDE_DIRS})
#    else()
#        find_library(Z3_LIBRARIES NAMES libz3.a libz3.so
#                HINTS $ENV{Z3_DIR}
#                PATH_SUFFIXES bin)
#        find_path(Z3_INCLUDES NAMES z3++.h
#                HINTS $ENV{Z3_DIR}
#                PATH_SUFFIXES include z3)
#        if(NOT Z3_LIBRARIES OR NOT Z3_INCLUDES)
#            message(FATAL_ERROR "Z3 not found!")
#        endif()
#        include_directories(${Z3_INCLUDES})
#        LINK_DIRECTORIES(${Z3_DIR}/bin)
#    endif()
#else()
#    find_library(Z3_LIBRARIES NAMES libz3.a libz3.so
#            HINTS $ENV{Z3_DIR}
#            PATH_SUFFIXES bin)
#    find_path(Z3_INCLUDES NAMES z3++.h
#            HINTS $ENV{Z3_DIR}
#            PATH_SUFFIXES include z3)
#    if(NOT Z3_LIBRARIES OR NOT Z3_INCLUDES)
#        message(FATAL_ERROR "Z3 not found!")
#    endif()
#    include_directories(${Z3_INCLUDES})
#    LINK_DIRECTORIES(${Z3_DIR}/bin)
#endif()

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
