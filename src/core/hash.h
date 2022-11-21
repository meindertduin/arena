#pragma once

#include <cstdint>
#include <compare>
#include <string>

class Hash64 {
public:
    Hash64() = default;
    explicit Hash64(const std::string &value);

    auto operator==(const Hash64 &rhs) const { return m_hash == rhs.m_hash; }
    auto operator!=(const Hash64 rhs) const { return m_hash != rhs.m_hash; }
    auto operator<=>(const Hash64 rhs) const { return m_hash <=> rhs.m_hash; }
private:
    uint64_t m_hash { 0 };
};