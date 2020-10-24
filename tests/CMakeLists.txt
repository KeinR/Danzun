cmake_minimum_required(VERSION 3.17)
project(game VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

file(GLOB_RECURSE sources src/*.cpp)
# set(libs extern/pugixml/pugixml.cpp)
file(COPY "data" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(game ${sources} ${libs})

target_include_directories(game PUBLIC "extern/")
target_include_directories(game PUBLIC "${CMAKE_BINARY_DIR}/include/eng/")
target_link_libraries(game PUBLIC glfw)
