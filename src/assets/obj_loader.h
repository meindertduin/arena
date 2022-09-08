#pragma once

#include <string>

namespace assets {
    struct Cache;
    void load_obj(const std::string& filename, Cache *cache);
}
