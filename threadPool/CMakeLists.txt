cmake_minimum_required(VERSION 3.20)
project(thread_pool)
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
add_library(thread_pool STATIC ${SRC})

