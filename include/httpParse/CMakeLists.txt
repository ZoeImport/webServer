cmake_minimum_required(VERSION 3.20)
project(Httpparse)
# set(TCP_SOCKET_ROOT_PATH ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
add_library(Httpparse SHARED ${SRC})
target_link_libraries(Httpparse PUBLIC Tool)

