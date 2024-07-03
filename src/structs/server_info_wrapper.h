#pragma once

#include <cstdint>

#include <export.h>

struct chc_server_info {
    const char *name;
    const char *timezone;
    const char *display_name;
    uint64_t version_major;
    uint64_t version_minor;
    uint64_t version_patch;
    uint64_t revision;
};

extern "C" EXPORT inline void chc_server_info_free(chc_server_info *info) {
    delete[] info->name;
    delete[] info->timezone;
    delete[] info->display_name;

    info->name = nullptr;
    info->timezone = nullptr;
    info->display_name = nullptr;
}
