cmake_minimum_required(VERSION 3.20)
project(output)

enable_testing()
add_test(NAME EXE_test COMMAND output)


set(CXX_STANDARD 20)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(INCLUDE_ROOT_PATH ${PROJECT_SOURCE_DIR}/include)
# set(BOOST_ROOT "/usr/lib/cmake/Boost-1.83.0")


find_package(Boost 1.83 REQUIRED COMPONENTS unit_test_framework REQUIRED)
find_package(spdlog REQUIRED)
 

include_directories(${Boost_INCLUDE_DIRS})
 

add_executable(output TEST.cpp)
# add_subdirectory(include/threadPool)
# add_subdirectory(include/TcpSocket)
# add_subdirectory(include/epoll)
add_subdirectory(include/tools)
add_subdirectory(include/httpParse)
add_subdirectory(include/webserver)
add_subdirectory(include/database)

# boost module
find_package(boost)
target_link_libraries(output ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# mariadbcpp module
# include_directories(/usr/include/mariadb)
# link_directories(/usr/lib/mariadb)
target_link_libraries(output mariadbcpp)


# target_link_libraries(output spdlog::spdlog)
# target_link_libraries(output ThreadPool)
# target_link_libraries(output TcpSocket)
# target_link_libraries(output Epoll)
target_link_libraries(output Tool)
target_link_libraries(output Httpparse)
target_link_libraries(output webserver)
target_link_libraries(output database)


# target_compile_options(output PUBLIC -g)

