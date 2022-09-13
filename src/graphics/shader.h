#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics {
    constexpr int MATRICES_BLOCK_BINDING = 0;
    constexpr int LIGHTS_BLOCK_BINDING = 1;

    enum class ShaderType {
        Vertex,
        Fragment,
    };

    struct Shader {
        uint32_t id;
        ShaderType type;
        std::string path;

        Shader(ShaderType type, const std::string& path);
        ~Shader();

        Shader(const Shader &other) = delete;
        Shader(Shader &&other) = delete;

        Shader& operator=(const Shader &other) = delete;
        Shader& operator=(Shader &&other) = delete;
    };

    struct ShaderProgram {
        uint32_t id{};
        uint32_t program;

        std::unique_ptr<Shader> vertexShader;
        std::unique_ptr<Shader> fragmentShader;

        ShaderProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        ~ShaderProgram();

        void use() const;
        void link() const;

        void set_property(const std::string& property_name, int) const;
        void set_property(const std::string& property_name, float) const;
        void set_property(const std::string& property_name, glm::vec3&&) const;
        void set_property(const std::string& property_name, glm::mat4&&) const;
        void set_property(const std::string& property_name, glm::vec3&) const;
        void set_property(const std::string& property_name, glm::mat4&) const;

        void set_uniform_loc(const std::string& name, int index) const;
    };
}
