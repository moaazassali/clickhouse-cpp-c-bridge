#include <doctest/doctest.h>

#include "block_wrapper.h"
#include "columns/column_int8.h"
#include "columns/column_wrapper.h"

TEST_CASE("Correctly create and free block") {
    Block *b = chc_block_create();
    CHECK(b != nullptr);
    CHECK_NOTHROW(chc_block_free(b));
}

TEST_CASE("Appending column to block correctly") {
    Block *b = chc_block_create();
    Column *c = chc_column_int8_create();
    chc_block_append_column(b, "test", c);
    CHECK(chc_block_column_count(b) == 1);
    CHECK(strcmp(chc_block_column_name(b, 0), "test") == 0);
    CHECK(chc_block_column_at(b, 0) == c);
    SUBCASE("Freeing block should not free column") {
        chc_block_free(b);
        CHECK_NOTHROW(chc_column_free(c));
    }
}

TEST_CASE("Getting block info correctly") {
    const Block *b = chc_block_create();
    BlockInfo info = chc_block_get_info(b);
    CHECK(info.bucket_num == -1);
    CHECK(info.is_overflows == 0);
}

TEST_CASE("Setting block info correctly") {
    Block *b = chc_block_create();
    constexpr BlockInfo info = {1, 1};
    chc_block_set_info(b, info);
    CHECK(chc_block_get_info(b).bucket_num == 1);
    CHECK(chc_block_get_info(b).is_overflows == 1);
}

TEST_CASE("Getting row count and refreshing correctly") {
    Block *b = chc_block_create();
    CHECK(chc_block_row_count(b) == 0);
    CHECK(chc_block_refresh_row_count(b) == 0);
    ColumnInt8 *c = chc_column_int8_create();
    chc_block_append_column(b, "test", c);
    CHECK(chc_block_row_count(b) == 0);
    CHECK(chc_block_refresh_row_count(b) == 0);
    chc_column_int8_append(c, 1);
    CHECK(chc_block_row_count(b) == 0); // old value
    CHECK(chc_block_refresh_row_count(b) == 1); // new value
    chc_block_free(b);
}
