cmake_minimum_required(VERSION 3.12)

project(clickhouse-cpp-c-bridge)

set(CMAKE_CXX_STANDARD 17)

# ========================================
# Library
# ========================================
set(LIB_SOURCES
        src/main.cpp
)
add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})

# ClickHouse C++ client (copied from https://github.com/ClickHouse/clickhouse-cpp)
add_subdirectory(dependencies/clickhouse-cpp)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/clickhouse-cpp/ dependencies/clickhouse-cpp/contrib/absl)
target_link_libraries(${PROJECT_NAME} PRIVATE clickhouse-cpp-lib)


# ========================================
# Tests (run ctest in build directory)
# ========================================
enable_testing()

# Find all test files under tests/
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(${PROJECT_NAME}-tests ${TEST_SOURCES})

# Link the project library
target_link_libraries(${PROJECT_NAME}-tests PRIVATE ${PROJECT_NAME})

# Doctest (https://github.com/doctest/doctest/blob/master/doc/markdown/build-systems.md)
add_subdirectory(dependencies/doctest)
target_include_directories(${PROJECT_NAME}-tests PRIVATE dependencies/doctest)

# These two lines are needed to find doctest_discover_tests
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/doctest/scripts/cmake")
include(doctest)

doctest_discover_tests(${PROJECT_NAME}-tests)