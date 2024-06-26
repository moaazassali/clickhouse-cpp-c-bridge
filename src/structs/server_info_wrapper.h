#pragma once

#include <cstdint>

#include <export.h>

struct ServerInfoWrapper {
    const char *name;
    const char *timezone;
    const char *display_name;
    uint64_t version_major;
    uint64_t version_minor;
    uint64_t version_patch;
    uint64_t revision;
};

extern "C" EXPORT inline void FreeServerInfoWrapper(ServerInfoWrapper *info) {
    delete[] info->name;
    delete[] info->timezone;
    delete[] info->display_name;

    info->name = nullptr;
    info->timezone = nullptr;
    info->display_name = nullptr;
}
