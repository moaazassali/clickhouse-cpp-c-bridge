#pragma once

#include <clickhouse/exceptions.h>

struct ClickHouseError{
	int code;
	char* message;
};

extern "C" __declspec(dllexport) inline void FreeClickHouseError(const ClickHouseError * error) {
	delete[] error->message;
	delete error;
}

inline void SetMessage(ClickHouseError & error, const char* message) {
	delete[] error.message;

	// Allocate new memory for the message and copy it
	size_t length = std::strlen(message);
	error.message = new char[length + 1];
	std::strcpy(error.message, message);
}

template <typename Func>
ClickHouseError TryCatchClickHouseError(Func&& func) {
	ClickHouseError error = { 0, nullptr };

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
		SetMessage(error, e.what());
	}
	catch (const clickhouse::ProtocolError& e) {
		error.code = -2; // Protocol error
		SetMessage(error, e.what());
	}
	catch (const clickhouse::UnimplementedError& e) {
		error.code = -3; // Unimplemented error
		SetMessage(error, e.what());
	}
	catch (const clickhouse::AssertionError& e) {
		error.code = -4; // Assertion error
		SetMessage(error, e.what());
	}
	catch (const clickhouse::OpenSSLError& e) {
		error.code = -5; // OpenSSL error
		SetMessage(error, e.what());
	}
	catch (const clickhouse::LZ4Error& e) {
		error.code = -6; // LZ4 error
		SetMessage(error, e.what());
	}
	catch (const clickhouse::Error& e) {
		error.code = -7; // Runtime error
		SetMessage(error, e.what());
	}
	catch (const std::exception& e) {
		error.code = -8; // Standard exception
		SetMessage(error, e.what());
	}
	catch (...) {
		error.code = -9; // Unknown exception
		SetMessage(error, "Unknown exception");
	}

	return error;
}