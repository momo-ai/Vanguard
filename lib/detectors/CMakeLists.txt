target_sources(Vanguard PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/UnitDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ProgramDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DetectorRegistry.cpp
    )

add_subdirectory(FunctionPrinter)
add_subdirectory(StatGen)
add_subdirectory(IRValidator)