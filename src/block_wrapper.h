#pragma once

#include <clickhouse/block.h>
#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline Block * CreateBlock()
{
	return new Block();
}

extern "C" EXPORT inline void FreeBlock(const Block * block)
{
	delete block;
}

extern "C" EXPORT inline void AppendColumn(Block * block, const char* name, Column * col)
{
	// fake shared_ptr to comply with the method signature
	const std::shared_ptr<Column> colSharedPtr(col, [](Column*) {});
	block->AppendColumn(name, colSharedPtr);
}

extern "C" EXPORT inline size_t GetColumnCount(const Block * block)
{
	return block->GetColumnCount();
}

extern "C" EXPORT inline BlockInfo Info(const Block *block) {
	return block->Info();
}

extern "C" EXPORT inline void SetInfo(Block * block, BlockInfo info)
{
	block->SetInfo(info);
}

extern "C" EXPORT inline size_t GetRowCount(const Block * block)
{
	return block->GetRowCount();
}

extern "C" EXPORT inline size_t RefreshRowCount(Block * block)
{
	return block->RefreshRowCount();
}

extern "C" EXPORT inline const char* GetColumnName(const Block * block, const size_t idx)
{
	return block->GetColumnName(idx).c_str();
}

extern "C" EXPORT inline Column * GetColumnAt(const Block * block, const size_t idx)
{
	return (*block)[idx].get();
}
