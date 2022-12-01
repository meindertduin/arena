#pragma once

#include <glm/glm.hpp>
#include "texture.h"
#include "shader.h"
#include "gpu_buffer.h"

namespace graphics {
    class Material : public assets::Resource {
    public:
        struct Uniform {
            std::string name;

            union {
                int int_value;
                float float_value;
                glm::vec2 v2;
                glm::vec3 v3;
                glm::vec4 v4;
                glm::mat4 matrix;
            };
        };

        explicit Material(const Path &path) : assets::Resource(path) {}

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

        void add_uniform(const Material::Uniform &uniform) {
            m_uniforms.push_back(uniform);
        }

        void set_shader(const std::shared_ptr<ShaderProgram> &shader) {
            m_shader = shader;
        }

        void load(std::size_t size, char *data) override;
        void unload() override {}
    private:
        std::vector<std::shared_ptr<graphics::Texture>> m_textures;
        std::shared_ptr<ShaderProgram> m_shader { nullptr };
        std::shared_ptr<UniformBuffer> m_buffer{};

        std::vector<Material::Uniform> m_uniforms;
    };
}
