cmake_minimum_required(VERSION 3.20)
project(Epoll)
include_directories(${INCLUDE_ROOT_PATH}/TcpSocket)
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
add_library(Epoll STATIC ${SRC})

