#pragma once

#include <utility>

#include "../core/path.h"

namespace assets {
    class Resource {
    public:
        explicit Resource(const Path &path) :
                m_path{path}
        {}

        Resource(const Resource &other) = delete;
        Resource& operator=(const Resource &other) = delete;

        virtual ~Resource() = default;

        [[nodiscard]] constexpr ALWAYS_INLINE const Path& path() const { return m_path; }

    protected:
        friend class Cache;

        virtual void load(std::size_t size, char *data) = 0;
        virtual void unload() = 0;
    private:
         int m_size {};
         Path m_path;
    };
}