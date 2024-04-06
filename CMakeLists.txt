cmake_minimum_required(VERSION 3.20)
project(output)

set(CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(output main.cpp)
add_subdirectory(threadPool)
add_subdirectory(TcpSocket)
add_subdirectory(TcpSocket/epoll)


target_link_libraries(output ThreadPool)
target_link_libraries(output TcpSocket)
target_link_libraries(output Epoll)
