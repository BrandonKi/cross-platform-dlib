cmake_minimum_required(VERSION 3.0.0)
project(example VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_library(widget1 SHARED ${CMAKE_CURRENT_SOURCE_DIR}/test-widget1.cpp)

add_library(widget2 SHARED ${CMAKE_CURRENT_SOURCE_DIR}/test-widget2.cpp)

set_target_properties(widget1
    PROPERTIES
    POSITION_INDEPENDENT_CODE 1
)

set_target_properties(widget2
    PROPERTIES
    POSITION_INDEPENDENT_CODE 1
)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)