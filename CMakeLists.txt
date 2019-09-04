cmake_minimum_required (VERSION 3.5)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES *.cpp)

# add_library(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
