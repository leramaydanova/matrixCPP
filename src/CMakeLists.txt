cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-14)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14)

project(S21Matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CODE_COVERAGE "Enable coverage reporting" ON)

include(FetchContent)
FetchContent_Declare(
  googletest
 URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(matrix
    s21_matrix_oop.cpp
    s21_matrix_oop_operators.cpp
    s21_matrix_oop_constructors.cpp
)
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(unit_tests
    tests/test.cpp
    tests/test_constructors.cpp
    tests/test_eq.cpp
    tests/test_math.cpp
	tests/test_operators.cpp
)

target_link_libraries(unit_tests
    matrix
    GTest::gtest_main
	GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Code coverage enabled")

    target_compile_options(matrix PRIVATE -fprofile-arcs -ftest-coverage -O0 -g)
    target_link_options(matrix PRIVATE -fprofile-arcs -ftest-coverage)

    target_compile_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage -O0 -g)
    target_link_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
endif()