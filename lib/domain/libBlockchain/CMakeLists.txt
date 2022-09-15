target_sources(Vanguard PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/BlockchainFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SummaryReader.cpp
        )

#include_directories(rapidjson)
#include_directories(include)
add_subdirectory(solidity)
#add_subdirectory(test)

