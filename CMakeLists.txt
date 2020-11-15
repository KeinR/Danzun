cmake_minimum_required(VERSION 3.10)
project(danzun VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

file(GLOB_RECURSE sources src/*.cpp src/*.c)
file(GLOB_RECURSE libs extern/*.cpp extern/*.c)

file(COPY "devel/scripts/mkheads" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_library(danzun ${sources} ${libs})

target_link_libraries(danzun INTERFACE "stdc++fs")

find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
target_include_directories(danzun PRIVATE "extern")
target_include_directories(danzun PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(danzun PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(danzun PUBLIC glfw)

add_subdirectory(tests)

include(GNUInstallDirs)

install(
    TARGETS danzun
    EXPORT danzunConfig
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
install(
    FILES LICENSE
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/danzun"
)
install(
    DIRECTORY "src/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/danzun"
    FILES_MATCHING PATTERN "*.h"
)
export(TARGETS danzun
    FILE "${CMAKE_CURRENT_BINARY_DIR}/danzunConfig.cmake"
)
install(EXPORT danzunConfig
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/danzun"
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/danzunConfigVersion.cmake" COMPATIBILITY SameMajorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/danzunConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/danzun"
)

if (WIN32 OR CYGWIN)
  set(CPACK_GENERATOR ZIP)
else()
  set(CPACK_GENERATOR TGZ)
endif()

include(CPack)
