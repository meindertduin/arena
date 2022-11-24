#pragma once

#include <glm/glm.hpp>
#include "texture.h"
#include "shader.h"

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

        glm::vec3 ambient{};
        glm::vec3 diffuse{};
        glm::vec3 specular{};

        bool reflects { false };
        float shininess{};

        [[nodiscard]] constexpr ALWAYS_INLINE
        const std::vector<std::shared_ptr<graphics::Texture>>& textures() const { return m_textures; }

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<ShaderProgram>& shader() const { return m_shader; }

        void add_texture(const std::shared_ptr<graphics::Texture> &texture) {
            m_textures.push_back(texture);
        }

        void set_shader(const std::shared_ptr<ShaderProgram> &shader) {
            m_shader = shader;
        }
    private:
        std::vector<std::shared_ptr<graphics::Texture>> m_textures;
        std::shared_ptr<ShaderProgram> m_shader { nullptr };
    };
}
