
message(STATUS "Generating documentation target...")
file(GLOB_RECURSE DANZUN_DOXYGEN_SRC "*.dox")
file(GLOB_RECURSE DANZUN_CUSTOM_STYLES_SRC "*.css")

if (BUILD_PRIVATE_DOCS)
    message(STATUS "Including code docs")
    file(GLOB_RECURSE DANZUN_DOXYGEN_SRC_HEADS "src/*.h")
    set(DANZUN_DOXYGEN_SRC ${DANZUN_DOXYGEN_SRC} ${DANZUN_DOXYGEN_SRC_HEADS})
endif()

foreach(path IN LISTS DANZUN_DOXYGEN_SRC)
    set(DANZUN_DOXYGEN_INPUT "${DANZUN_DOXYGEN_INPUT} \\\n\"${path}\"")
endforeach()

foreach(path IN LISTS DANZUN_CUSTOM_STYLES_SRC)
    set(DANZUN_CUSTOM_STYLES "${DANZUN_CUSTOM_STYLES} \\\n\"${path}\"")
endforeach()

configure_file(Doxyfile.in Doxyfile @ONLY)

add_custom_target(docs "${DOXYGEN_EXECUTABLE}"
    WORKING_DIRECTORY "."
    COMMENT "Generating HTML documentation" VERBATIM)
