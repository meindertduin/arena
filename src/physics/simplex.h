#pragma once

#include <glm/vec3.hpp>
#include <initializer_list>
#include <iterator>
#include <array>
#include "../platform/platform.h"

namespace physics {
    class Simplex {
    public:
        Simplex() :
                m_points({ glm::vec3{0}, glm::vec3{0}, glm::vec3{0}, glm::vec3{0} }),
                m_size{0}
        {}

        Simplex& operator=(std::initializer_list<glm::vec3> list) {
            for (auto v = list.begin(); v != list.end(); v++) {
                m_points[std::distance(list.begin(), v)] = *v;
            }
            m_size = list.size();

            return *this;
        }

        void push_front(const glm::vec3 &point) {
            m_points = { point, m_points[0], m_points[1], m_points[2] };
            m_size = std::min(m_size + 1, 4u);
        }

        constexpr ALWAYS_INLINE glm::vec3& operator[](uint32_t i) { return m_points[i]; }
        [[nodiscard]] constexpr ALWAYS_INLINE uint32_t size() const { return m_size; }

        [[nodiscard]] constexpr auto begin() const { return m_points.begin(); }
        [[nodiscard]] constexpr auto end() const { return m_points.end() - (4 - m_size); }
    private:
        std::array<glm::vec3, 4> m_points;
        uint32_t m_size;
    };
}