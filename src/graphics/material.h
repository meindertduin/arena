#pragma once

#include <glm/glm.hpp>
#include "texture.h"

namespace graphics {
    class Material {
    public:
        Material() = default;
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) :
            ambient{ambient},
            diffuse{diffuse},
            specular{specular},
            shininess{shininess}
        {}

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        bool reflects { false };
        float shininess;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<graphics::Texture>& texture() const { return m_texture; }

        void set_texture(const std::shared_ptr<graphics::Texture> &texture) {
            m_texture = texture;
        }

    private:
        std::shared_ptr<graphics::Texture> m_texture { nullptr };
    };
}
