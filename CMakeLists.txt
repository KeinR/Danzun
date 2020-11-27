cmake_minimum_required(VERSION 3.13)
project(danzun VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

file(GLOB_RECURSE sources src/*.cpp src/*.c)
set(libs
    extern/stb/stb_image.c
    extern/pugixml/pugixml.cpp
)

file(COPY "devel/scripts/mkheads" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_library(danzun ${sources} ${libs})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

add_subdirectory(extern/sub/glfw)
add_subdirectory(extern/sub/lua)

find_package(glm REQUIRED)

# add_dependencies(danzun glfw)

target_include_directories(danzun
    PRIVATE "extern"
    PRIVATE "${GLFW_INCLUDE_DIRS}"
    PUBLIC "${GLM_INCLUDE_DIRS}"
)

target_link_libraries(danzun
    glfw
    lua_static
    stdc++fs
)

add_subdirectory(frontend)

# include(GNUInstallDirs)

# install(
#     TARGETS danzun
#     EXPORT danzunConfig
#     ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
# )
# install(
#     FILES LICENSE
#     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/danzun"
# )
# install(
#     DIRECTORY "src/"
#     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/danzun"
#     FILES_MATCHING REGEX "^.*\\.(h|inl)$"
# )
# export(TARGETS danzun
#     FILE "${CMAKE_CURRENT_BINARY_DIR}/danzunConfig.cmake"
# )
# install(EXPORT danzunConfig
#     DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/danzun"
# )
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/danzunConfigVersion.cmake" COMPATIBILITY SameMajorVersion)
# install(FILES "${CMAKE_CURRENT_BINARY_DIR}/danzunConfigVersion.cmake"
#     DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/danzun"
# )

# if (WIN32 OR CYGWIN)
#   set(CPACK_GENERATOR ZIP)
# else()
#   set(CPACK_GENERATOR TGZ)
# endif()

# include(CPack)
