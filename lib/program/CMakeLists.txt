target_sources(Vanguard PRIVATE
    #put source files here
    ${CMAKE_CURRENT_SOURCE_DIR}/Instruction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Function.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LLVMFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CompilationUnit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Type.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Value.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Universe.cpp
)
