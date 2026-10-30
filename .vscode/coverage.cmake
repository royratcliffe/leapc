cmake_minimum_required (VERSION 3.11)

foreach (TOOL clang clang++ llvm-profdata llvm-cov ninja)
    find_program (${TOOL}_EXECUTABLE NAMES "${TOOL}")
    if (NOT ${TOOL}_EXECUTABLE)
        message (FATAL_ERROR "${TOOL} was not found on PATH")
    endif ()
endforeach ()

function (run)
    execute_process (COMMAND ${ARGV} RESULT_VARIABLE RESULT)
    if (NOT RESULT STREQUAL "0")
        message (FATAL_ERROR "Command failed (${RESULT}): ${ARGV}")
    endif ()
endfunction ()

get_filename_component (PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set (BUILD_DIR "${PROJECT_ROOT}/build/coverage")
set (PROFILE_DIR "${BUILD_DIR}/profiles")

# Create build and profile directories if they don't yet exist.
run ("${CMAKE_COMMAND}" -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" -G Ninja
    "-DCMAKE_C_COMPILER=${clang_EXECUTABLE}"
    "-DCMAKE_CXX_COMPILER=${clang++_EXECUTABLE}"
    "-DCMAKE_MAKE_PROGRAM=${ninja_EXECUTABLE}"
    -DCMAKE_BUILD_TYPE=Debug
    "-DCMAKE_C_FLAGS=-fprofile-instr-generate -fcoverage-mapping"
    -DCMAKE_EXE_LINKER_FLAGS=-fprofile-instr-generate
    -DCMAKE_DISABLE_FIND_PACKAGE_Doxygen=TRUE
)
run ("${CMAKE_COMMAND}" --build "${BUILD_DIR}" --target TestDriverForLeapC)

# Only merge profiles from this test run.
file (MAKE_DIRECTORY "${PROFILE_DIR}")
file (GLOB OLD_PROFILES "${PROFILE_DIR}/*.profraw")
if (OLD_PROFILES)
    file (REMOVE ${OLD_PROFILES})
endif ()
run ("${CMAKE_COMMAND}" -E env "LLVM_PROFILE_FILE=${PROFILE_DIR}/test-%p.profraw"
    "${CMAKE_CTEST_COMMAND}" --test-dir "${BUILD_DIR}" --output-on-failure
)
file (GLOB PROFILES "${PROFILE_DIR}/*.profraw")
if (NOT PROFILES)
    message (FATAL_ERROR "Tests generated no coverage profiles")
endif ()
set (PROFILE "${BUILD_DIR}/coverage.profdata")
run ("${llvm-profdata_EXECUTABLE}" merge -sparse ${PROFILES} -o "${PROFILE}")

# Generate coverage report using llvm-cov.
set (TEST_DRIVER "${BUILD_DIR}/TestDriverForLeapC")
if (CMAKE_HOST_WIN32)
    string (APPEND TEST_DRIVER ".exe")
endif ()
file (GLOB SOURCES "${PROJECT_ROOT}/src/*.c" "${PROJECT_ROOT}/inc/*.h")
run ("${llvm-cov_EXECUTABLE}" report "${TEST_DRIVER}"
    "-instr-profile=${PROFILE}" ${SOURCES}
)
run ("${llvm-cov_EXECUTABLE}" show "${TEST_DRIVER}"
    "-instr-profile=${PROFILE}" -format=html
    "-output-dir=${BUILD_DIR}/html" -show-branches=count ${SOURCES}
)
message (STATUS "Coverage report: ${BUILD_DIR}/html/index.html")
