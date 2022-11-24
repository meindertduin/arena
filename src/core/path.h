#pragma once

#include <string>
#include "hash.h"

class Path {
public:
    Path() = default;
    explicit Path(const std::string &path) :
        m_path{path},
        m_hash{path}
    {}

    explicit Path(const std::string &&path) :
            m_path{path}
    {
        m_hash = Hash64{m_path};
    }

    [[nodiscard]] constexpr ALWAYS_INLINE const std::string& path() const { return m_path; }
    [[nodiscard]] constexpr ALWAYS_INLINE Hash64 hash() const { return m_hash; }

    inline auto operator==(const Path &rhs) const { return m_hash == rhs.m_hash; }
    inline auto operator!=(const Path &rhs) const { return m_hash != rhs.m_hash; }
private:
    std::string m_path{};
    Hash64 m_hash{};
};