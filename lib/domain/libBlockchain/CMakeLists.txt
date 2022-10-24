target_sources(libVanguard PRIVATE
        SummaryReader.cpp
)

#include_directories(rapidjson)
#include_directories(include)
add_subdirectory(langs)
#add_subdirectory(test)

