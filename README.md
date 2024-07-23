Clickhouse C++ C Bridge <br/>[![Linux](https://github.com/moaazassali/clickhouse-cpp-c-bridge/actions/workflows/linux.yml/badge.svg)](https://github.com/moaazassali/clickhouse-cpp-c-bridge/actions/workflows/linux.yml) [![Windows](https://github.com/moaazassali/clickhouse-cpp-c-bridge/actions/workflows/windows.yml/badge.svg)](https://github.com/moaazassali/clickhouse-cpp-c-bridge/actions/workflows/windows.yml) [![macOS](https://github.com/moaazassali/clickhouse-cpp-c-bridge/actions/workflows/macos.yml/badge.svg)](https://github.com/moaazassali/clickhouse-cpp-c-bridge/actions/workflows/macos.yml) [![codecov](https://codecov.io/github/moaazassali/clickhouse-cpp-c-bridge/graph/badge.svg?token=LOW8YNGOU4)](https://codecov.io/github/moaazassali/clickhouse-cpp-c-bridge)
========================
This is a C interface for the [clickhouse-cpp](https://github.com/ClickHouse/clickhouse-cpp) library providing all
the essential functionality to interact with ClickHouse from C using the Native protocol.

It is intended to be used for creating client libraries in other languages with this library as a base for interop
as well as in C projects that need to interact with ClickHouse.

Developers using any other language with C interop support can easily create highly performant client
libraries for ClickHouse built on top of this library without having to worry about reverse-engineering the ClickHouse
native protocol.

## Some notes

- Not all methods from clickhouse-cpp are exposed; only the essential ones are. This is because the
  non-exposed methods can most likely be implemented using the exposed ones from the client library side.
- For example, Map, Point, Ring, Polygon and MultiPolygon are not exposed, but they can all be built using a combination
  of Array and Tuple columns.
- If there is a method that is not exposed, but you think it should be, please open an issue or a pull request.
- Just like the `Client` instance in clickhouse-cpp, the `Client` instance here is also NOT thread-safe.

## Common pitfalls

- With memory-managed languages, make sure to keep references to every object returned from the library until you are
  done with them:
    - If you create a block using `chc_block_create` and store the returned pointer in a private field in
      your library's `CHBlock` class and then create some columns using `chc_column_X_create` and simply pass those
      pointers to `chc_block_append`, you will often be appending freed memory to the block. Even though you have a
      reference to the block, the block does not have references to the columns, so they are freed by the garbage
      collector before you append them to the block (this is assuming you have properly implemented a way to dispose of
      the objects when they go out of scope or are freed by the GC). To avoid this, keep references to the columns as
      well by appending them to a list in the block class.


## Benchmarks
List of client libraries in other languages utilizing this library and achieving better performance compared to all other available open-source ones:
### C# [(clickhouse-csharp)](https://github.com/moaazassali/clickhouse-csharp):

For 1M rows inserted, `ClickHouse.Driver` is 5x faster than the second-fastest library (`ClickHouse.Client`)

| Library                    | Insertion Time Ratio  | Memory Usage  |
|:---------------------------|:----------------------|:--------------|
| ClickHouse.Driver (this)   | 1x                    | 1x            |
| ClickHouse.Client          | 5.09x                 | 3.33x         |
| Octonica.ClickHouseClient  | 6.21x                 | 0.71x         |
| ClickHouse.Ado             | 63.35x                | 4.56x         |
