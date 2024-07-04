Clickhouse C++ C Bridge
========================
This is a C interface for the [clickhouse-cpp](https://github.com/ClickHouse/clickhouse-cpp) library providing all
the essential functionality to interact with ClickHouse from C using the Native protocol.

It is intended to be used for creating client libraries in other languages using this repository as a base for interop
as well as in C projects that need to interact with ClickHouse.

With this library, developers using any other language with C interop support can easily create highly performant client 
libraries for ClickHouse built on top of this library without having to worry about reverse-engineering the ClickHouse 
native protocol.


## Design choices
- Not all methods from clickhouse-cpp are exposed; only the essential ones are. This is because most of the 
non-exposed methods can most likely be implemented using the exposed ones from the client library side.
- If there is a method that is not exposed, but you think it should be, please open an issue or a pull request.