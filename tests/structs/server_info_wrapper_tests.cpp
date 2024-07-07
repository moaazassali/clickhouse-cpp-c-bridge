#include <doctest/doctest.h>

#include "structs/server_info_wrapper.h"

TEST_CASE("Correctly free server info") {
    chc_server_info info{};
    info.name = new char[5];
    info.timezone = new char[5];
    info.display_name = new char[5];
    chc_server_info_free(&info);
    CHECK(info.name == nullptr);
    CHECK(info.timezone == nullptr);
    CHECK(info.display_name == nullptr);
}
