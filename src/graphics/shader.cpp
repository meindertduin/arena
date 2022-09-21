#include "shader.h"

#include <glad/glad.h>
#include <memory>

#include <iostream>

#include "../logging.h"
#include "../assets/file_reader.h"

namespace graphics {
    Shader::Shader(ShaderType type, const std::string& path) : type(type), path(path) {
        if (type == ShaderType::Fragment)
            id = glCreateShader(GL_FRAGMENT_SHADER);
        else
            id = glCreateShader(GL_VERTEX_SHADER);

        assets::FileReader file_reader { path };
        auto data = file_reader.get_file_content();

        const char* charData = data.c_str();

        glShaderSource(id, 1, &charData, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::cout << infoLog;
            THROW_ERROR("GL ERROR: Failed to compile shader with path: %s", path);
        }
    }

    Shader::~Shader() {
        glDeleteShader(id);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(program);
    }

    ShaderProgram::ShaderProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
        program = glCreateProgram();

        vertexShader = std::make_unique<Shader>(ShaderType::Vertex, vertex_shader_path);
        fragmentShader = std::make_unique<Shader>(ShaderType::Fragment, fragment_shader_path );

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
            glGetProgramInfoLog(program, 1024, nullptr, infoLog);
            std::cout << infoLog;
            THROW_ERROR("GL ERROR: Failed to link shaders with paths: %s, %s", vertexShader->path, fragmentShader->path);
        }

        // set the block bindings
         uint32_t matrices_block_index = glGetUniformBlockIndex(program, "Matrices");
         glUniformBlockBinding(program, matrices_block_index, MATRICES_BLOCK_BINDING);
 
         int32_t lights_block_index = glGetUniformBlockIndex(program, "Lights");
         glUniformBlockBinding(program, lights_block_index, LIGHTS_BLOCK_BINDING);

    }

    void ShaderProgram::set_property(const std::string& property_name, int value) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform1i(uniform_lock, value);
    }

    void ShaderProgram::set_property(const std::string& property_name, float value) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform1f(uniform_lock, value);
    }

    void ShaderProgram::set_property(const std::string& property_name, glm::vec3 &&v) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform3f(uniform_lock, v.x, v.y, v.z);
    }

    void ShaderProgram::set_property(const std::string& property_name, glm::mat4 &&m) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniformMatrix4fv(uniform_lock, 1, GL_FALSE, glm::value_ptr(m));
    }

    void ShaderProgram::set_property(const std::string& property_name, glm::vec3 &v) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform3f(uniform_lock, v.x, v.y, v.z);
    }

    void ShaderProgram::set_property(const std::string& property_name, glm::mat4 &m) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniformMatrix4fv(uniform_lock, 1, GL_FALSE, glm::value_ptr(m));
    }

    void ShaderProgram::set_uniform_loc(const std::string& name, int index) const {
        glUniform1i(glGetUniformLocation(program, name.c_str()), index);
    }
}
