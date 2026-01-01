cmake_minimum_required (VERSION 3.11)
project (leapc)
enable_language (C)
add_library (leapc src/leap.c src/quo_mod.c)
target_include_directories (leapc PUBLIC inc)

include (CTest)
enable_testing ()

file (GLOB TestsToRun tests/*.c)
set (TestNames)
foreach (test_to_run ${TestsToRun})
    get_filename_component (TestName ${test_to_run} NAME_WE)
    if (NOT TestName MATCHES ".+_test$")
        continue ()
    endif ()
    list (APPEND TestNames ${TestName})
    add_test (NAME ${TestName} COMMAND TestDriverForLeapC ${TestName})
endforeach ()
create_test_sourcelist (Tests test_driver.c ${TestNames})

add_executable (TestDriverForLeapC)
target_sources (TestDriverForLeapC PRIVATE test_driver.c ${TestsToRun})
target_link_libraries (TestDriverForLeapC PRIVATE leapc)

# Link the math library on GNU or Clang compilers. This is needed for math
# functions like `floor`. The GNU and Clang compilers do not auto-link the math
# library. The GNU C compiler defines CMAKE_C_COMPILER_ID as "GNU" and the Clang
# compiler defines it as "Clang".
#
# On other compilers (like MSVC), the math functions are in the standard C
# library, so no separate linking is needed. Do not link the math library on
# Windows (WIN32) because it is not needed there.
message (STATUS "CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND NOT WIN32)
    target_link_libraries (TestDriverForLeapC PRIVATE m)
endif ()

# Find the Doxygen output at html/index.html in the build folder.
# Optimise for C language: data structures not classes!
find_package (Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if (DOXYGEN_FOUND)
    set (DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set (DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set (DOXYGEN_EXTRACT_STATIC YES)
    set (DOXYGEN_SOURCE_BROWSER YES)
    set (DOXYGEN_EXCLUDE ${PROJECT_BINARY_DIR}/test_driver.c)
    doxygen_add_docs (Doxygen ${PROJECT_SOURCE_DIR})
endif ()
