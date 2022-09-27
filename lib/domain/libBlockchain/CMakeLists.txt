target_sources(Vanguard PRIVATE

        )

#include_directories(rapidjson)
#include_directories(include)
add_subdirectory(solidity)
add_subdirectory(rust)
#add_subdirectory(test)

