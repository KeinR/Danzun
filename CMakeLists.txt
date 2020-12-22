cmake_minimum_required(VERSION 3.13)
project(danzun VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(BUILD_SHARED_LIBS true)

file(GLOB_RECURSE sources src/*.cpp src/*.c)
set(libs
    extern/stb/stb_image.c
    extern/pugixml/pugixml.cpp
)

file(COPY "data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_library(danzun STATIC ${sources} ${libs})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_ROOT}/Modules" "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(glm 0.9 REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(Lua53 REQUIRED)
find_package(OpenAL 1.19 REQUIRED)

target_include_directories(danzun
    PUBLIC "extern"
    PUBLIC "${GLFW_INCLUDE_DIRS}"
    PUBLIC "${GLM_INCLUDE_DIRS}"
    PUBLIC "${LUA53_INCLUDE_DIR}"
)

target_link_libraries(danzun
    glfw
    ${LUA53_LIBRARIES}
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
