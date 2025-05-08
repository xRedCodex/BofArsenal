cmake_minimum_required(VERSION 3.5)
project(BOFArsenal)

# Creates the main "build_all" target
add_custom_target(build_all ALL)

# Finds all Makefiles, but excludes the build directory
file(GLOB_RECURSE MAKEFILES RELATIVE ${CMAKE_SOURCE_DIR} "*/Makefile")
list(FILTER MAKEFILES EXCLUDE REGEX "^build/")

# For each Makefile found
foreach(MAKEFILE ${MAKEFILES})
    # Gets the directory of the Makefile
    get_filename_component(DIR ${MAKEFILE} DIRECTORY)

    # Replaces slashes with underscores in target names
    string(REPLACE "/" "_" TARGET_NAME ${DIR})

    # Creates a custom target for each Makefile
    add_custom_target(
        ${TARGET_NAME}_build
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/${DIR} ${CMAKE_MAKE_PROGRAM}
        COMMENT "Building Makefile in ${DIR}"
    )

    # Adds the target to "build_all"
    add_dependencies(build_all ${TARGET_NAME}_build)
endforeach()
