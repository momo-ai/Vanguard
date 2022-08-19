target_sources(Vanguard PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/UnitDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InterproceduralDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IntraproceduralDetector.cpp
    )

add_subdirectory(FunctionPrinter)
add_subdirectory(StatGen)
add_subdirectory(IRValidator)