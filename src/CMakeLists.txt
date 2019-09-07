cmake_minimum_required (VERSION 3.5)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES *.cpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(subtitler ${SOURCES})
add_executable(sub-mover main.cpp)
target_link_libraries(sub-mover subtitler)
