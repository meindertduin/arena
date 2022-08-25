#include "shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include <iostream>

namespace graphics {
    // TODO move this to a different namespace and tidy up
    std::string read_file_contents(std::string path) {
        std::ifstream ifs { path };

        if (ifs.fail()) {
            throw std::runtime_error("IO ERROR: Shader file: " + path + " does not exist.");
        }

        std::stringstream sstream;

        sstream << ifs.rdbuf();
        ifs.close();

        return sstream.str();
    }

    Shader::Shader(ShaderType type, std::string path) : type(type) {
        if (type == ShaderType::Fragment)
            id = glCreateShader(GL_FRAGMENT_SHADER);
        else
            id = glCreateShader(GL_VERTEX_SHADER);

        auto data = read_file_contents(path);
        const char* charData = data.c_str();

        glShaderSource(id, 1, &charData, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            std::cout << infoLog;
            throw std::runtime_error("GL ERROR: Failed to compile shader.");
        }
    }

    Shader::~Shader() {
        glDeleteShader(id);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(program);
    }

    ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
        program = glCreateProgram();

        vertexShader = std::unique_ptr<Shader>(new Shader { ShaderType::Vertex, vertexShaderPath});
        fragmentShader = std::unique_ptr<Shader>(new Shader { ShaderType::Fragment, fragmentShaderPath });

        glAttachShader(program, vertexShader->id);
        glAttachShader(program, fragmentShader->id);
    }

    void ShaderProgram::use() const {
        glUseProgram(program);
    }

    void ShaderProgram::link() const {
        glLinkProgram(program);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetProgramInfoLog(program, 1024, NULL, infoLog);
            std::cout << infoLog;
            throw std::runtime_error("GL ERROR: Failed to compile shader.");
        }

        // set the block bindings
         uint32_t matrices_block_index = glGetUniformBlockIndex(program, "Matrices");
         glUniformBlockBinding(program, matrices_block_index, MATRICES_BLOCK_BINDING);
 
         int32_t lights_block_index = glGetUniformBlockIndex(program, "Lights");
         glUniformBlockBinding(program, lights_block_index, LIGHTS_BLOCK_BINDING);

    }

    void ShaderProgram::set_property(std::string properyName, int value) const {
        uint32_t uniformLock = glGetUniformLocation(program, properyName.c_str());
        glUniform1i(uniformLock, value);
    }

    void ShaderProgram::set_property(std::string properyName, float value) const {
        uint32_t uniformLock = glGetUniformLocation(program, properyName.c_str());
        glUniform1f(uniformLock, value);
    }

    void ShaderProgram::set_property(std::string properyName, glm::vec3 &&v) const {
        uint32_t uniformLock = glGetUniformLocation(program, properyName.c_str());
        glUniform3f(uniformLock, v.x, v.y, v.z);
    }

    void ShaderProgram::set_property(std::string properyName, glm::mat4 &&m) const {
        uint32_t uniformLock = glGetUniformLocation(program, properyName.c_str());
        glUniformMatrix4fv(uniformLock, 1, GL_FALSE, glm::value_ptr(m));
    }

    void ShaderProgram::set_property(std::string properyName, glm::vec3 &v) const {
        uint32_t uniformLock = glGetUniformLocation(program, properyName.c_str());
        glUniform3f(uniformLock, v.x, v.y, v.z);
    }

    void ShaderProgram::set_property(std::string properyName, glm::mat4 &m) const {
        uint32_t uniformLock = glGetUniformLocation(program, properyName.c_str());
        glUniformMatrix4fv(uniformLock, 1, GL_FALSE, glm::value_ptr(m));
    }
}
