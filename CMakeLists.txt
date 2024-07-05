cmake_minimum_required(VERSION 3.12)

project(clickhouse-cpp-c-bridge)

set(CMAKE_CXX_STANDARD 17)

# Required to build on linux (needs fpic)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ========================================
# Library
# ========================================
set(LIB_SOURCES
        src/main.cpp
)
add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})

# We include src/ to have absolute include paths from src/ directory instead of relative paths
# Also since our public header files use #include of external dependencies, we need to make this PUBLIC
# Otherwise, dependent projects will not be able to find the headers to build and will give errors
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

# ClickHouse C++ client (copied from https://github.com/ClickHouse/clickhouse-cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/clickhouse-cpp)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/clickhouse-cpp/
        PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/clickhouse-cpp/contrib/absl
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC clickhouse-cpp-lib
)


# ========================================
# Tests (run `ctest` in build directory)
# ========================================
enable_testing()

# Find all test files under tests/
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(${PROJECT_NAME}-tests ${TEST_SOURCES})

# Link the project library
target_link_libraries(${PROJECT_NAME}-tests PRIVATE ${PROJECT_NAME})

# Doctest (https://github.com/doctest/doctest/blob/master/doc/markdown/build-systems.md)
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/doctest)

# Include the directories for the test target
target_include_directories(${PROJECT_NAME}-tests
        PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/doctest
)

# These two lines are needed to find doctest_discover_tests()
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/dependencies/doctest/scripts/cmake")
include(doctest)

doctest_discover_tests(${PROJECT_NAME}-tests)