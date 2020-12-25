
if (NOT BUILD_PRIVATE_DOCS)
    message(STATUS "Configured to public docs")
    file(GLOB_RECURSE DANZUN_DOXYGEN_SRC "docs/*")
else()
    message(STATUS "Configured to code docs")
    file(GLOB_RECURSE DANZUN_DOXYGEN_SRC "src/*")
endif()

set(DOXYGEN_SKIP_DOT true)
find_package(Doxygen REQUIRED)

foreach(path IN LISTS DANZUN_DOXYGEN_SRC)
    set(DANZUN_DOXYGEN_INPUT "${DANZUN_DOXYGEN_INPUT} \\\n\"${CMAKE_SOURCE_DIR}/${path}\"")
endforeach()

configure_file(Doxyfile.in Doxyfile @ONLY)

add_custom_target(docs "${DOXYGEN_EXECUTABLE}")
