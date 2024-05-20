#include "client_wrapper.h"
#include "query_wrapper.h"
#include "block_wrapper.h"

// columns
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

// structs
#include "structs/client_options_wrapper.h"
#include "structs/clickhouse_result_status.h"
#include "structs/server_info_wrapper.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!dsvdsv" << std::endl;
    const auto client = CreateClient("192.168.70.176");

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
