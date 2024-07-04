Clickhouse C++ C Bridge
========================
This is a C interface for the [clickhouse-cpp](https://github.com/ClickHouse/clickhouse-cpp) library providing all
the essential functionality to interact with ClickHouse from C using the Native protocol.

It is intended to be used for creating client libraries in other languages with this library as a base for interop
as well as in C projects that need to interact with ClickHouse.

Developers using any other language with C interop support can easily create highly performant client 
libraries for ClickHouse built on top of this library without having to worry about reverse-engineering the ClickHouse 
native protocol.

## Some notes
- Not all methods from clickhouse-cpp are exposed; only the essential ones are. This is because most of the 
non-exposed methods can most likely be implemented using the exposed ones from the client library side.
- If there is a method that is not exposed, but you think it should be, please open an issue or a pull request.
- Just like the `Client` instance in clickhouse-cpp, the `Client` instance here is also NOT thread-safe.

## Common pitfalls
- With memory-managed languages, make sure to keep references to every object returned from the library until you are done with them:
  - If you create a block using `chc_block_create` and store the returned pointer in a private field in 
  your library's `CHBlock` class and then create some columns using `chc_column_X_create` and simply pass those pointers to 
  `chc_block_append`, you will often be appending freed memory to the block. Even though you have a reference to the block,
  the block does not have references to the columns, so they are freed by the garbage collector before you append them 
  to the block (this is assuming you have properly implemented a way to dispose of the objects when they go out of scope 
  or are freed by the GC). To avoid this, keep references to the columns as well by appending them to a list in the block class.
