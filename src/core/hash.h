#pragma once

#include <cstdint>
#include <compare>
#include <string>
#include "../platform/platform.h"

class Hash64 {
public:
    Hash64() = default;
    explicit Hash64(const std::string &value);

    auto operator==(const Hash64 &rhs) const { return m_hash == rhs.m_hash; }
    auto operator!=(const Hash64 rhs) const { return m_hash != rhs.m_hash; }
    auto operator<=>(const Hash64 rhs) const { return m_hash <=> rhs.m_hash; }

    [[nodiscard]] constexpr ALWAYS_INLINE uint64_t value() const { return m_hash; }
private:
    uint64_t m_hash { 0 };
};

template<>
struct std::hash<Hash64> {
    auto operator()(const Hash64 hash64) const -> size_t {
        return hash<uint64_t>()(hash64.value());
    }
};