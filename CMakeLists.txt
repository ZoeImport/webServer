cmake_minimum_required(VERSION 3.20)
project(output)

set(CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(INCLUDE_ROOT_PATH ${PROJECT_SOURCE_DIR}/include)

add_executable(output main.cpp)
add_subdirectory(include/threadPool)
add_subdirectory(include/TcpSocket)
add_subdirectory(include/epoll)
add_subdirectory(include/tools)

target_link_libraries(output ThreadPool)
target_link_libraries(output TcpSocket)
target_link_libraries(output Epoll)
target_link_libraries(output Tool)
