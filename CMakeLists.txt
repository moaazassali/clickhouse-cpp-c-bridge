cmake_minimum_required(VERSION 3.28)

project(clickhouse-cpp-c-bridge)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/clickhouse-cpp-c-bridge.cpp
)

add_library(clickhouse-cpp-c-bridge SHARED SOURCES)
