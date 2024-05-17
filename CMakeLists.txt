cmake_minimum_required(VERSION 3.28)

project(clickhouse-cpp-c-bridge)

set(CMAKE_CXX_STANDARD 17)

add_library(testclion SHARED clickhouse-cpp-c-bridge.cpp)