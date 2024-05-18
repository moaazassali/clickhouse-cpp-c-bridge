#include "client_wrapper.h"
#include "clickhouse_result_status.h"
#include "query_wrapper.h"
#include "block_wrapper.h"

#include "columns/column_wrapper.h"
#include "columns/column_int8.h"
#include "columns/column_int16.h"
#include "columns/column_int32.h"
#include "columns/column_int64.h"
#include "columns/column_uint8.h"
#include "columns/column_uint16.h"
#include "columns/column_uint32.h"
#include "columns/column_uint64.h"
#include "columns/column_float32.h"
#include "columns/column_float64.h"
#include "columns/column_string.h"
#include "columns/column_datetime.h"
#include "columns/column_datetime64.h"

#include <iostream>

int main() {
    try {
        std::cout << "Hello, World!dsvdsv" << std::endl;
        const auto client = CreateClient("192.168.70.176");

        std::cout << "Created client" << std::endl;

        /// Create a table.
        const auto query = CreateQuery("DROP TABLE test.gg");
        auto error = Execute(client, query);

        std::cout << error.code << std::endl;
        std::cout << error.message << std::endl;

        delete[] error.message;
        error.message = nullptr;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    /*
    Execute(client, "CREATE TABLE IF NOT EXISTS default.numbers (id UInt64, name String) ENGINE = Memory");

    auto block = CreateBlock();

    auto idCol = CreateColumnUInt64();
    ColumnUInt64Append(*idCol, 1);
    ColumnUInt64Append(*idCol, 7);


    auto nameCol = CreateColumnString();
    ColumnStringAppend(*nameCol, "one");
    ColumnStringAppend(*nameCol, "seven");

    AppendColumn(block, "id", idCol);
    AppendColumn(block, "name", nameCol);

    Insert(client, "default.numbers", block);

    FreeColumn(idCol);
    FreeColumn(nameCol);
    FreeBlock(block);
    */

    // keep the console window open
    std::cin.get();

    return 0;
}