#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics {
    enum class ShaderType {
        Vertex,
        Fragment,
    };

    struct Shader {
        uint32_t id;
        ShaderType type;

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

        void setProperty(std::string properyName, int) const;
        void setProperty(std::string properyName, float) const;
        void setProperty(std::string properyName, glm::vec3&&) const;
        void setProperty(std::string properyName, glm::mat4&&) const;
        void setProperty(std::string properyName, glm::vec3&) const;
        void setProperty(std::string properyName, glm::mat4&) const;
    };
}
