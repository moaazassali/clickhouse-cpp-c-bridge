#include <doctest/doctest.h>

#include "structs/clickhouse_result_status.h"

TEST_CASE("Created chc_result_status correctly reflects error type") {
    SUBCASE("ServerException") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::ServerException(std::make_unique<clickhouse::Exception>(
                clickhouse::Exception{1, "ServerException", "ServerException", "ServerException", nullptr}
            ));
        });

        CHECK(result.code == 1);
        CHECK(std::string(result.message) == "ServerException");
        chc_result_status_free(&result);
    }

    SUBCASE("ValidationError") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::ValidationError("ValidationError");
        });

        CHECK(result.code == -1);
        CHECK(std::string(result.message) == "ValidationError");
        chc_result_status_free(&result);
    }

    SUBCASE("ProtocolError") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::ProtocolError("ProtocolError");
        });

        CHECK(result.code == -2);
        CHECK(std::string(result.message) == "ProtocolError");
        chc_result_status_free(&result);
    }

    SUBCASE("UnimplementedError") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::UnimplementedError("UnimplementedError");
        });

        CHECK(result.code == -3);
        CHECK(std::string(result.message) == "UnimplementedError");
        chc_result_status_free(&result);
    }

    SUBCASE("AssertionError") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::AssertionError("AssertionError");
        });

        CHECK(result.code == -4);
        CHECK(std::string(result.message) == "AssertionError");
        chc_result_status_free(&result);
    }

    SUBCASE("OpenSSLError") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::OpenSSLError("OpenSSLError");
        });

        CHECK(result.code == -5);
        CHECK(std::string(result.message) == "OpenSSLError");
        chc_result_status_free(&result);
    }

    SUBCASE("CompressionError") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::CompressionError("CompressionError");
        });

        CHECK(result.code == -6);
        CHECK(std::string(result.message) == "CompressionError");
        chc_result_status_free(&result);
    }

    SUBCASE("Error") {
        auto result = TryCatchClickHouseError([]() {
            throw clickhouse::Error("Error");
        });

        CHECK(result.code == -7);
        CHECK(std::string(result.message) == "Error");
        chc_result_status_free(&result);
    }

    SUBCASE("std::exception") {
        auto result = TryCatchClickHouseError([]() {
            throw std::exception("std::exception");
        });

        CHECK(result.code == -8);
        CHECK(std::string(result.message) == "std::exception");
        chc_result_status_free(&result);
    }

    SUBCASE("Unknown exception") {
        auto result = TryCatchClickHouseError([]() {
            throw "Unknown exception";
        });

        CHECK(result.code == -9);
        CHECK(std::string(result.message) == "Unknown exception");
        chc_result_status_free(&result);
    }

    SUBCASE("NoError") {
        auto result = TryCatchClickHouseError([]() {
            // No error
        });

        CHECK(result.code == 0);
        CHECK(result.message == nullptr);
        chc_result_status_free(&result);
    }
}
