#pragma once

#include <stdint.h>
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

        Shader(ShaderType type, std::string path);
        ~Shader();

        Shader(const Shader &other) = delete;
        Shader(Shader &&other) = delete;

        Shader& operator=(const Shader &other) = delete;
        Shader& operator=(Shader &&other) = delete;
    };

    struct ShaderProgram {
        uint32_t id;
        uint32_t program;

        std::unique_ptr<Shader> vertexShader;
        std::unique_ptr<Shader> fragmentShader;

        ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
        ~ShaderProgram();

        void use() const;
        void link() const;

        void set_property(std::string properyName, int) const;
        void set_property(std::string properyName, float) const;
        void set_property(std::string properyName, glm::vec3&&) const;
        void set_property(std::string properyName, glm::mat4&&) const;
        void set_property(std::string properyName, glm::vec3&) const;
        void set_property(std::string properyName, glm::mat4&) const;
    };
}
