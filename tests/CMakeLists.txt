cmake_minimum_required(VERSION 3.10)
project(test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

file(COPY "data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(GLOB_RECURSE sources src/*.cpp)

add_executable(test ${sources})

target_link_libraries(test PUBLIC danzun)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(test PUBLIC glfw)
target_link_libraries(test PUBLIC stdc++fs)

