#pragma once

#include <clickhouse/block.h>

#include "export.h"
#include "utils.h"

using namespace clickhouse;

extern "C" EXPORT inline Block *chc_block_create() {
    return new Block();
}

extern "C" EXPORT inline void chc_block_free(const Block *block) {
    delete block;
}

extern "C" EXPORT inline void chc_block_append_column(Block *block, const char *name, Column *col) {
    // fake shared_ptr to comply with the method signature
    // freeing the columns should be handled by the external library since columns are directly used by the end user.
    // we don't want them to be owned by the block and freed automatically when the user might still have references to them.
    block->AppendColumn(name, make_fake_shared(col));
}

extern "C" EXPORT inline size_t chc_block_column_count(const Block *block) {
    return block->GetColumnCount();
}

extern "C" EXPORT inline BlockInfo chc_block_get_info(const Block *block) {
    return block->Info();
}

extern "C" EXPORT inline void chc_block_set_info(Block *block, const BlockInfo info) {
    block->SetInfo(info);
}

extern "C" EXPORT inline size_t chc_block_row_count(const Block *block) {
    return block->GetRowCount();
}

extern "C" EXPORT inline size_t chc_block_refresh_row_count(Block *block) {
    return block->RefreshRowCount();
}

extern "C" EXPORT inline const char *chc_block_column_name(const Block *block, const size_t idx) {
    return block->GetColumnName(idx).c_str();
}

extern "C" EXPORT inline Column *chc_block_column_at(const Block *block, const size_t idx) {
    return (*block)[idx].get();
}
