cmake_minimum_required(VERSION 3.13)
project(Danzun VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(BUILD_SHARED_LIBS true)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/keinr/Danzun")

file(GLOB_RECURSE sources src/*.cpp src/*.c)
set(libs
    deps/stb/stb_image.c
)

file(COPY "data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(Danzun ${sources} ${libs})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_ROOT}/Modules" "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(glm 0.9 REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(Lua53 REQUIRED)
find_package(OpenAL 1.19 REQUIRED)

target_include_directories(Danzun
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include"
    PUBLIC "deps"
    PUBLIC "${GLFW_INCLUDE_DIRS}"
    PUBLIC "${GLM_INCLUDE_DIRS}"
    PUBLIC "${LUA53_INCLUDE_DIR}"
)

target_link_libraries(Danzun
    glfw
    ${LUA53_LIBRARIES}
    stdc++fs
)

set_target_properties(Danzun PROPERTIES OUTPUT_NAME "danzun")

set(DANZUN_DATA_DIR_PARENT "${CMAKE_INSTALL_PREFIX}")
set(DANZUN_VERSION "${CMAKE_PROJECT_VERSION}")
set(DANZUN_DATA_DIR "${DANZUN_DATA_DIR_PARENT}/danzun")
set(DANZUN_INIT_SCRIPT "${DANZUN_DATA_DIR}/data/lua/init.lua")

configure_file(src/cmake/config.h.in include/cmake/config.h)

install(
    TARGETS Danzun
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY "data"
    DESTINATION share/danzun
)

if (UNIX)

    # ty Stack https://stackoverflow.com/a/41592428/10821333
    find_program(LSB_RELEASE_EXEC lsb_release)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
        OUTPUT_VARIABLE DISTRO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (DISTRO MATCHES "Debian")

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
        set(CPACK_DEBIAN_FILE_NAME "Danzun-${DANZUN_VERSION}-Debian-${CMAKE_SYSTEM_PROCESSOR}.deb")

        set(CPACK_GENERATOR DEB)

    else()

        message(STATUS "Using generic tgz packages")

        set(CPACK_GENERATOR TGZ)

    endif()

else()

    set(CPACK_GENERATOR ZIP)

endif()

include(CPack)

