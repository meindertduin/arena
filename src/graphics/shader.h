#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../platform/platform.h"
#include "../core/path.h"

namespace graphics {
    constexpr int MATRICES_BLOCK_BINDING = 0;
    constexpr int LIGHTS_BLOCK_BINDING = 1;

    enum class ShaderType {
        Vertex,
        Fragment,
    };

    class Shader {
    public:
        Shader(ShaderType type, std::string path);
        ~Shader();

        Shader(const Shader &other) = delete;
        Shader(Shader &&other) = delete;

        Shader& operator=(const Shader &other) = delete;
        Shader& operator=(Shader &&other) = delete;

        [[nodiscard]] constexpr ALWAYS_INLINE uint32_t id() const { return m_id; }
        // TODO remove once shader inherits from resource
        [[nodiscard]] constexpr ALWAYS_INLINE std::string path() const { return m_path; }
    private:
        uint32_t m_id;
        ShaderType m_type;
        std::string m_path;
    };

    class ShaderProgram {
    public:
        std::unique_ptr<Shader> vertexShader;
        std::unique_ptr<Shader> fragmentShader;

        ShaderProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        ~ShaderProgram();

        void use() const;
        void link() const;

        void set_property(const std::string& property_name, int) const;
        void set_property(const std::string& property_name, float) const;
        void set_property(const std::string& property_name, glm::vec3&&) const;
        void set_property(const std::string& property_name, glm::vec4&&) const;
        void set_property(const std::string& property_name, glm::mat4&&) const;
        void set_property(const std::string& property_name, const glm::vec3&) const;
        void set_property(const std::string& property_name, const glm::vec4&) const;
        void set_property(const std::string& property_name, const glm::mat4&) const;

        void set_uniform_loc(const std::string& name, int index) const;
    private:
        uint32_t id{};
        uint32_t program;
    };
}
