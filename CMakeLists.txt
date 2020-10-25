cmake_minimum_required(VERSION 3.17)
project(danzun VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE libs extern/*.c)

add_library(danzun ${sources} ${libs})

find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
target_include_directories(danzun PUBLIC "extern")
target_include_directories(danzun PUBLIC ${GLM_INCLUDE_DIRS})
target_include_directories(danzun PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(danzun PUBLIC glfw)

add_subdirectory(tests)
