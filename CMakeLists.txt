cmake_minimum_required(VERSION 3.28)

project(clickhouse-cpp-c-bridge)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/clickhouse-cpp-c-bridge.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
#add_executable(${PROJECT_NAME} src/clickhouse-cpp-c-bridge.cpp)

# ----------------------------------------
# ClickHouse C++ client (copied from https://github.com/ClickHouse/clickhouse-cpp)
# ----------------------------------------
add_subdirectory(dependencies/clickhouse-cpp)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/clickhouse-cpp/ dependencies/clickhouse-cpp/contrib/absl)
target_link_libraries(${PROJECT_NAME} PRIVATE clickhouse-cpp-lib)