#include "hash.h"

#include <xxh3/xxhash64.h>

Hash64::Hash64(const std::string &value) {
    m_hash = XXHash64::hash(value.c_str(), value.length(), 347183);
}
