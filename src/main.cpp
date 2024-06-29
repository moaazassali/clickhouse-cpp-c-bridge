#include "utils.h"
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
#include "columns/column_fixed_string.h"
#include "columns/column_datetime.h"
#include "columns/column_datetime64.h"
#include "columns/column_date.h"
#include "columns/column_date32.h"
#include "columns/column_uuid.h"
#include "columns/column_ipv4.h"
#include "columns/column_ipv6.h"
#include "columns/column_int128.h"
#include "columns/column_decimal.h"
#include "columns/column_tuple.h"
#include "columns/column_nullable.h"
#include "columns/column_enum8.h"
#include "columns/column_enum16.h"
#include "columns/column_array.h"

// structs
#include "structs/client_options_wrapper.h"
#include "structs/clickhouse_result_status.h"
#include "structs/server_info_wrapper.h"
#include "structs/endpoint_wrapper.h"
#include "structs/uuid_wrapper.h"
#include "structs/int128_wrapper.h"
#include "structs/optional_wrapper.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!dsvdsv" << std::endl;
    auto options = ClientOptionsWrapper();
    auto query = Query();
    options.host = "192.168.70.176";
    std::cout << "Host set:" << options.host << std::endl;
    Client *client;
    CreateClient(&options, &client);
    //const auto client = new Client(ClientOptions().SetHost("192.168.70.176"));
    std::cout << "Client created" << std::endl;

    // keep the console window open
    std::cin.get();

    return 0;
}
