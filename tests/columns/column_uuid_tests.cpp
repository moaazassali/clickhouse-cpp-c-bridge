#include <random>
#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_uuid.h"

TEST_CASE("Constructed ColumnUUID is valid") {
    const auto col = chc_column_uuid_create();

    SUBCASE("Type is UUID") {
        CHECK(col->Type()->GetCode() == Type::UUID);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnUUID correctly") {
    const auto col = chc_column_uuid_create();

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    uint64_t first = dis(gen);
    uint64_t second = dis(gen);

    chc_column_uuid_append(col, {first, second});
    CHECK(chc_column_uuid_at(col, 0).first == first);
    CHECK(col->At(0).second == second);
    CHECK(col->Size() == 1);

    uint64_t max_uint64 = std::numeric_limits<uint64_t>::max();
    chc_column_uuid_append(col, {max_uint64, max_uint64});
    SUBCASE("Returns same value when appending uuid max value") {
        CHECK(chc_column_uuid_at(col, 1).first == max_uint64);
        CHECK(chc_column_uuid_at(col, 1).second == max_uint64);
        CHECK(col->Size() == 2);
    }

    chc_column_uuid_append(col, {0, 0});
    SUBCASE("Returns same value when appending uuid min value") {
        CHECK(chc_column_uuid_at(col, 2).first == 0);
        CHECK(chc_column_uuid_at(col, 2).second == 0);
        CHECK(col->Size() == 3);
    }
}
