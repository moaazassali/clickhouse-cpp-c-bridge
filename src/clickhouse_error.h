#pragma once

#include <clickhouse/exceptions.h>

// Possible memory leak here or dangling pointers? Idk...

struct ClickHouseError{
	int code;
	const char* message;
};

inline void SetMessage(ClickHouseError & error, const char* message) {
	// why dangling pointer?
	error.message = std::string(message).c_str();
}

template <typename Func>
ClickHouseError TryCatchClickHouseError(Func&& func) {
	ClickHouseError error = { 0, "" };

	try {
		// Call the provided function
		func();
	}
	catch (const clickhouse::ServerException& e) {
		error.code = e.GetCode();
		SetMessage(error, e.what());
	}
	catch (const clickhouse::ValidationError& e) {
		error.code = -1; // Validation error
		error.message = e.what();
	}
	catch (const clickhouse::ProtocolError& e) {
		error.code = -2; // Protocol error
		error.message = e.what();
	}
	catch (const clickhouse::UnimplementedError& e) {
		error.code = -3; // Unimplemented error
		error.message = e.what();
	}
	catch (const clickhouse::AssertionError& e) {
		error.code = -4; // Assertion error
		error.message = e.what();
	}
	catch (const clickhouse::OpenSSLError& e) {
		error.code = -5; // OpenSSL error
		error.message = e.what();
	}
	catch (const clickhouse::LZ4Error& e) {
		error.code = -6; // LZ4 error
		error.message = e.what();
	}
	catch (const clickhouse::Error& e) {
		error.code = -7; // Runtime error
		error.message = e.what();
	}
	catch (const std::exception& e) {
		error.code = -8; // Standard exception
		error.message = e.what();
	}
	catch (...) {
		error.code = -9; // Unknown exception
		error.message = "Unknown exception";
	}

	return error;
}