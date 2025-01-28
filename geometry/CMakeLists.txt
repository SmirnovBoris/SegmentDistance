cmake_minimum_required (VERSION 3.14)
project ("segment_distance")

add_library(geometry INTERFACE)

target_include_directories(geometry INTERFACE ${PROJECT_SOURCE_DIR}/include)
