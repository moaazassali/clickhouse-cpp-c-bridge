#pragma once

#include <clickhouse/exceptions.h>

#include <export.h>

struct chc_result_status {
    int code;
    char *message;
};

extern "C" EXPORT inline void chc_result_status_free(chc_result_status *result) {
    delete[] result->message;
    result->message = nullptr;
}

inline void SetMessage(chc_result_status &result, const char *message) {
    delete[] result.message;

    // Allocate new memory for the message and copy it
    const size_t length = std::strlen(message);
    result.message = new char[length + 1];
    std::strcpy(result.message, message);
}

template<typename Func>
chc_result_status TryCatchClickHouseError(Func &&func) {
    chc_result_status result = {0, nullptr};

    try {
        // Call the provided function
        func();
    } catch (const clickhouse::ServerException &e) {
        result.code = e.GetCode();
        SetMessage(result, e.what());
    }
    catch (const clickhouse::ValidationError &e) {
        result.code = -1;
        SetMessage(result, e.what());
    }
    catch (const clickhouse::ProtocolError &e) {
        result.code = -2;
        SetMessage(result, e.what());
    }
    catch (const clickhouse::UnimplementedError &e) {
        result.code = -3;
        SetMessage(result, e.what());
    }
    catch (const clickhouse::AssertionError &e) {
        result.code = -4;
        SetMessage(result, e.what());
    }
    catch (const clickhouse::OpenSSLError &e) {
        result.code = -5;
        SetMessage(result, e.what());
    }
    catch (const clickhouse::CompressionError &e) {
        result.code = -6;
        SetMessage(result, e.what());
    }
    catch (const clickhouse::Error &e) {
        result.code = -7; // Runtime error
        SetMessage(result, e.what());
    }
    catch (const std::exception &e) {
        result.code = -8;
        SetMessage(result, e.what());
    }
    catch (...) {
        result.code = -9; // Unknown exception
        SetMessage(result, "Unknown exception");
    }

    return result;
}
