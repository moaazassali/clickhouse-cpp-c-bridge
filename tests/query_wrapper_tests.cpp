#include <doctest/doctest.h>

#include "query_wrapper.h"

TEST_CASE("Correctly create and free query") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK(q->GetText() == query);
    CHECK_NOTHROW(chc_query_free(q));
}

void FakeCallback(const Block *block) {
}

TEST_CASE("Correctly set query on data callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_data(q, FakeCallback));
}

bool FakeCancelableCallback(const Block *block) {
    return true;
}

TEST_CASE("Correctly set query on data cancelable callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_data_cancelable(q, FakeCancelableCallback));
}
