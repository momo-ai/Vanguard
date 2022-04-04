target_sources(Vanguard PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendAnalysis.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendAnalysis.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendDetector.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendSink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendSink.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendSource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaintedSendSource.h
        )