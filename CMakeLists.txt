cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
include_directories("${CMAKE_SOURCE_DIR}/linear_algebra")

add_subdirectory(src)
