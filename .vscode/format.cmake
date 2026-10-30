cmake_minimum_required (VERSION 3.11)

find_package (Git REQUIRED)
find_program (CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if (NOT CLANG_FORMAT_EXECUTABLE)
    message (FATAL_ERROR "clang-format was not found on PATH")
endif ()

# Assume that the CMake script is located in the .vscode directory and
# the project root is its parent.
get_filename_component (PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
execute_process (
    COMMAND "${GIT_EXECUTABLE}" ls-files -- "*.c" "*.h"
    WORKING_DIRECTORY "${PROJECT_ROOT}"
    OUTPUT_VARIABLE SOURCES
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE RESULT
)
if (NOT RESULT STREQUAL "0")
    message (FATAL_ERROR "git ls-files failed: ${RESULT}")
endif ()
if (SOURCES STREQUAL "")
    message (FATAL_ERROR "No tracked C source or header files found")
endif ()

# Normalise line endings and convert the list of sources into a CMake
# list. Then launch clang-format on the listed source files using the
# style defined in the .clang-format file with -i to modify the files in
# place.
string (REPLACE "\r\n" "\n" SOURCES "${SOURCES}")
string (REPLACE "\n" ";" SOURCES "${SOURCES}")
execute_process (
    COMMAND "${CLANG_FORMAT_EXECUTABLE}" --style=file -i ${SOURCES}
    WORKING_DIRECTORY "${PROJECT_ROOT}"
    RESULT_VARIABLE RESULT
)
if (NOT RESULT STREQUAL "0")
    message (FATAL_ERROR "clang-format failed: ${RESULT}")
endif ()
