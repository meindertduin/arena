#pragma once

#include <glm/glm.hpp>
#include <algorithm>

namespace math {
    inline constexpr glm::vec3 merge_min(const glm::vec3 &a, const glm::vec3 &b) {
        return { std::min<float>(a.x, b.x), std::min<float>(a.y, b.y), std::min<float>(a.z, b.z) };
    }

    inline constexpr glm::vec3 merge_max(const glm::vec3 &a, const glm::vec3 &b) {
        return { std::max<float>(a.x, b.x), std::max<float>(a.y, b.y), std::max<float>(a.z, b.z) };
    }
}
