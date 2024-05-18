#pragma once

#include <clickhouse/block.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline Block * CreateBlock()
{
	return new Block();
}

extern "C" __declspec(dllexport) inline void FreeBlock(const Block * block)
{
	delete block;
}

extern "C" __declspec(dllexport) inline void AppendColumn(Block * block, const char* name, Column * col)
{
	// fake shared_ptr to comply with the method signature
	const std::shared_ptr<Column> colSharedPtr(col, [](Column*) {});
	block->AppendColumn(name, colSharedPtr);
}

extern "C" __declspec(dllexport) inline size_t GetColumnCount(const Block * block)
{
	return block->GetColumnCount();
}

extern "C" __declspec(dllexport) inline BlockInfo Info(const Block *block) {
	return block->Info();
}

extern "C" __declspec(dllexport) inline void SetInfo(Block * block, BlockInfo info)
{
	block->SetInfo(info);
}

extern "C" __declspec(dllexport) inline size_t GetRowCount(const Block * block)
{
	return block->GetRowCount();
}

extern "C" __declspec(dllexport) inline size_t RefreshRowCount(Block * block)
{
	return block->RefreshRowCount();
}

extern "C" __declspec(dllexport) inline const char* GetColumnName(const Block * block, const size_t idx)
{
	return block->GetColumnName(idx).c_str();
}

extern "C" __declspec(dllexport) inline Column * GetColumnAt(const Block * block, const size_t idx)
{
	return (*block)[idx].get();
}
