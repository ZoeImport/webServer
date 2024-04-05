cmake_minimum_required(VERSION 3.20)
project(output)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(output main.cpp)
add_subdirectory(threadPool)


target_link_libraries(output thread_pool)