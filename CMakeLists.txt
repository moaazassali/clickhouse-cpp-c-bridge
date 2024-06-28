cmake_minimum_required(VERSION 3.12)

project(clickhouse-cpp-c-bridge)

set(CMAKE_CXX_STANDARD 17)

# ----------------------------------------
# ClickHouse C++ client (copied from https://github.com/ClickHouse/clickhouse-cpp)
# ----------------------------------------
add_subdirectory(dependencies/clickhouse-cpp)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/clickhouse-cpp/ dependencies/clickhouse-cpp/contrib/absl)
target_link_libraries(${PROJECT_NAME} PRIVATE clickhouse-cpp-lib)

# ----------------------------------------
# Doctest (https://github.com/doctest/doctest/blob/master/doc/markdown/build-systems.md)
# ----------------------------------------
add_subdirectory(dependencies/doctest)

# ----------------------------------------
# This project
# ----------------------------------------
set(SOURCES
        src/main.cpp
)

#add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})