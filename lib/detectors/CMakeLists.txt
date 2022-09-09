target_sources(Vanguard PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/UnitDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ProgramDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DetectorRegistry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AAWrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AARequirement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DAWrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DARequirement.cpp
    )

add_subdirectory(FunctionPrinter)
add_subdirectory(StatGen)
add_subdirectory(Reentrancy)
add_subdirectory(IRValidator)
add_subdirectory(near-detectors)
