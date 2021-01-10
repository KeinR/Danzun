cmake_minimum_required(VERSION 3.13)
project(Danzun VERSION 0.3 LANGUAGES CXX C)

option(BUILD_DOCS "Whether the documentation target should be generated" OFF)
option(BUILD_PRIVATE_DOCS "If MAKE_DOCS is turned on, will build docs for the codebase as opposed to the Lua API" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/keinr/Danzun")

# Thanks stack https://stackoverflow.com/a/61381440/10821333
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall)
endif()

file(GLOB_RECURSE sources src/*.cpp src/*.c)
set(libs
    deps/GLAD/glad.c
    deps/stb/stb_image.c
    deps/stb/stb_vorbis.c
    deps/dr/dr_wav.c
)

add_executable(Danzun ${sources} ${libs})

set_target_properties(Danzun PROPERTIES OUTPUT_NAME "danzun")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_ROOT}/Modules" "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(glm REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(Lua53 REQUIRED)
find_package(OpenAL 1.19 REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


target_include_directories(Danzun
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include"
    PUBLIC "deps"
    PUBLIC "${GLFW_INCLUDE_DIRS}"
    PUBLIC "${GLM_INCLUDE_DIRS}"
    PUBLIC "${LUA53_INCLUDE_DIR}"
    PUBLIC "${OPENAL_INCLUDE_DIR}"
)

target_link_libraries(Danzun
    glfw
    ${OPENAL_LIBRARY}
    ${LUA53_LIBRARIES}
    stdc++fs
    Threads::Threads
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

endif()

# Subdirectories

if (BUILD_DOCS)
    set(DOXYGEN_SKIP_DOT ON)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        add_subdirectory(docs)
    endif()
endif()

# Configuration

set(DANZUN_VERSION "${CMAKE_PROJECT_VERSION}")

configure_file(src/cmake/config.h.in include/cmake/config.h)

# Packaging

install(
    TARGETS Danzun
    RUNTIME DESTINATION bin
)

if (UNIX)

    # ty Stack https://stackoverflow.com/a/41592428/10821333
    find_program(LSB_RELEASE_EXEC lsb_release)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
        OUTPUT_VARIABLE DISTRO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (DISTRO MATCHES "Debian" OR DISTRO MATCHES "Ubuntu")

        message(STATUS "Using debain packages")

        set(CPACK_DEBIAN_PACKAGE_VERSION ${VERSION})
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Orion Musselman <orionmusselman@gmail.com>")
        set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A basic 'Shoot em' up' bullet hell game engine (runtime)")
        set(CPACK_DEBIAN_PACKAGE_SECTION "games")
        set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
        set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
        set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "${CMAKE_PROJECT_HOMEPAGE_URL}")
        set(CPACK_DEBIAN_FILE_NAME "Danzun-${DANZUN_VERSION}-${DISTRO}-${CMAKE_SYSTEM_PROCESSOR}.deb")

        set(CPACK_GENERATOR ${CPACK_GENERATOR} DEB)

    endif()

    set(CPACK_GENERATOR ${CPACK_GENERATOR} TGZ)

else()

    set(CPACK_GENERATOR ${CPACK_GENERATOR} ZIP)

endif()

include(CPack)

