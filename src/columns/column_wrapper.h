#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline void FreeColumn(const Column * col) {
	delete col;
}