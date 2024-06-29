#include <random>
#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_uuid.h"

TEST_CASE("Constructed ColumnUUID is valid") {
    const auto col = CreateColumnUUID();

    SUBCASE("Type is UUID") {
        CHECK(col->Type()->GetCode() == Type::UUID);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnUUID correctly") {
    const auto col = CreateColumnUUID();

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    uint64_t first = dis(gen);
    uint64_t second = dis(gen);

    ColumnUUIDAppend(col, {first, second});
    CHECK(col->At(0).first == first);
    CHECK(col->At(0).second == second);
    CHECK(col->Size() == 1);

    uint64_t max_uint64 = std::numeric_limits<uint64_t>::max();
    ColumnUUIDAppend(col, {max_uint64, max_uint64});
    SUBCASE("Returns same value when appending uuid max value") {
        CHECK(col->At(1).first == max_uint64);
        CHECK(col->At(1).second == max_uint64);
        CHECK(col->Size() == 2);
    }

    ColumnUUIDAppend(col, {0, 0});
    SUBCASE("Returns same value when appending uuid min value") {
        CHECK(col->At(2).first == 0);
        CHECK(col->At(2).second == 0);
        CHECK(col->Size() == 3);
    }
}
