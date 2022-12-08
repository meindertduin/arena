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

        [[nodiscard]] constexpr ALWAYS_INLINE
        const std::vector<std::shared_ptr<graphics::Texture>>& textures() const {
            return m_textures;
        }

        [[nodiscard]] constexpr ALWAYS_INLINE
        const std::vector<Material::Uniform>& uniforms() const {
            return m_uniforms;
        }

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<Shader>& shader() const { return m_shader; }

        void add_texture(const std::shared_ptr<graphics::Texture> &texture) {
            m_textures.push_back(texture);
        }

        void add_uniform(const Material::Uniform &uniform) {
            m_uniforms.push_back(uniform);
        }

        void set_shader(const std::shared_ptr<Shader> &shader) {
            m_shader = shader;
        }

        void update();
    protected:
        friend class assets::Cache;

        void load(std::size_t size, char *data) override;
    private:
        std::vector<std::shared_ptr<graphics::Texture>> m_textures;
        std::shared_ptr<Shader> m_shader { nullptr };
        std::vector<Material::Uniform> m_uniforms;
    };
}
