#pragma once

#include <utility>

#include "../core/path.h"

namespace assets {
    class Resource {
    public:
        friend class Cache;
        Resource(const Resource &other) = delete;
        Resource& operator=(const Resource &other) = delete;

        virtual ~Resource() = default;

        [[nodiscard]] constexpr ALWAYS_INLINE const Path& path() const { return m_path; }

    protected:
        explicit Resource(Path path) :
            m_path{std::move(path)}
        {}

        virtual void load() = 0;
        virtual void unload() = 0;
    private:
         int m_size {};
         Path m_path;
    };
}