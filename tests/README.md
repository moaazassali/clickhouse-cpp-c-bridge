Clickhouse C++ C Bridge Tests
=============================
This directory contains tests for the Clickhouse C++ C Bridge.

The tests are written in C++ and use the [doctest](https://github.com/doctest/doctest]) testing framework.

To build and run the tests:

1. Use CMake to build the `clickhouse-cpp-c-bridge-tests` target.
2. Run `cd out/<your_build_dir>`
3. Run `ctest`

### Some notes

These tests assume that the original [clickhouse-cpp](https://github.com/ClickHouse/clickhouse-cpp) library is free of
bugs, so the tests chosen are not exhaustive. The tests are meant to test the C++ C Bridge and not the original library.
Nevertheless, a lot of tests do test the original library as well, but that is not the main goal.

If you find a bug, verify that it is not in the original library before reporting it here.

