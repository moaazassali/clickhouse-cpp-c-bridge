#include <doctest/doctest.h>

#include "query_wrapper.h"

TEST_CASE("Correctly create and free query") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK(q->GetText() == query);
    CHECK_NOTHROW(chc_query_free(q));
}

TEST_CASE("Correctly get query text") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK(std::string(chc_query_get_text(q)) == query);
}

TEST_CASE("Correctly get query id") {
    const auto query = "SELECT 1";
    const auto query_id = "123";
    Query *q = chc_query_create(query, query_id);
    CHECK(q != nullptr);
    CHECK(std::string(chc_query_get_query_id(q)) == query_id);
}

static bool CALLED = false;

static void FakeCallback(const Block *block) {
    CALLED = true;
}

TEST_CASE("Correctly convert and execute SelectCallbackWrapper") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);

    const auto cb = GetSelectCallback(FakeCallback);
    cb(Block()); // call the fake callback
    CHECK(CALLED);
}

TEST_CASE("Correctly set query on data callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_data(q, FakeCallback));
}


static bool FakeCancelableCallback(const Block *block) {
    return true;
}

TEST_CASE("Correctly convert and execute SelectCancelableCallbackWrapper") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);

    const auto cb = GetSelectCancelableCallback(FakeCancelableCallback);
    CHECK(cb(Block()) == true); // call the fake callback
}

TEST_CASE("Correctly set query on data cancelable callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_data_cancelable(q, FakeCancelableCallback));
}

static void FakeProgressCallback(const Progress *progress) {
    CALLED = true;
}

TEST_CASE("Correctly convert and execute ProgressCallbackWrapper") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CALLED = false;
    const auto cb = GetProgressCallback(FakeProgressCallback);
    cb(Progress()); // call the fake callback
    CHECK(CALLED);
}

TEST_CASE("Correctly set query on progress callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_progress(q, FakeProgressCallback));
}

static bool FakeSelectServerLogCallback(const Block *block) {
    return true;
}

TEST_CASE("Correctly convert and execute SelectServerLogCallbackWrapper") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);

    const auto cb = GetSelectServerLogCallback(FakeSelectServerLogCallback);
    CHECK(cb(Block()) == true); // call the fake callback
}

TEST_CASE("Correctly set query on select server log callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_server_log(q, FakeSelectServerLogCallback));
}

static bool FakeProfileEventsCallback(const Block *block) {
    return true;
}

TEST_CASE("Correctly convert and execute ProfileEventsCallbackWrapper") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);

    const auto cb = GetProfileEventsCallback(FakeProfileEventsCallback);
    CHECK(cb(Block()) == true); // call the fake callback
}

TEST_CASE("Correctly set query on profile events callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_profile_events(q, FakeProfileEventsCallback));
}

static void FakeProfileCallback(const Profile *profile) {
    CALLED = true;
}

TEST_CASE("Correctly convert and execute ProfileCallbackWrapper") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CALLED = false;
    const auto cb = GetProfileCallback(FakeProfileCallback);
    cb(Profile()); // call the fake callback
    CHECK(CALLED);
}

TEST_CASE("Correctly set query on profile callback") {
    const auto query = "SELECT 1";
    Query *q = chc_query_create(query);
    CHECK(q != nullptr);
    CHECK_NOTHROW(chc_query_on_profile(q, FakeProfileCallback));
}
