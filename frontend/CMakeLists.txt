cmake_minimum_required(VERSION 3.13)
project(danzun-run VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

file(GLOB sources src/*.cpp)

add_executable(danzun-run ${sources})

target_link_libraries(danzun-run danzun)
