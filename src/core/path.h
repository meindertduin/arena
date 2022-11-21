#pragma once

#include <string>
#include "hash.h"

class Path {
public:
    Path() = default;
    explicit Path(std::string path);

    [[nodiscard]] constexpr const std::string& path() const { return m_path; }

    inline auto operator==(const Path &rhs) const { return this->m_hash == rhs.m_hash; }
    inline auto operator!=(const Path &rhs) const { return this->m_hash == rhs.m_hash; }

private:
    std::string m_path{};
    Hash64 m_hash{};
};