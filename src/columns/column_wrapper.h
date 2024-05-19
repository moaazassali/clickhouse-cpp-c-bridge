#pragma once

using namespace clickhouse;

extern "C" EXPORT inline void FreeColumn(const Column * col) {
	delete col;
}