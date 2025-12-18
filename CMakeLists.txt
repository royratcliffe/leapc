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
    add_test (NAME ${TestName} COMMAND RunTests ${TestName})
endforeach ()
create_test_sourcelist (Tests test_driver.c ${TestNames})

add_executable (RunTests)
target_sources (RunTests PRIVATE test_driver.c ${TestsToRun})
target_link_libraries (RunTests leapc m)

# Find the Doxygen output at html/index.html in the build folder.
# Optimise for C: data structures not classes!
find_package (Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if (DOXYGEN_FOUND)
set (DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
set (DOXYGEN_EXCLUDE ${PROJECT_BINARY_DIR}/test_driver.c)
doxygen_add_docs (doxygen ${PROJECT_SOURCE_DIR})
endif ()
