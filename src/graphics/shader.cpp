#include "shader.h"

#include <glad/glad.h>

#include <iostream>
#include <utility>

#include "../logging.h"
#include "../assets/file_reader.h"

#include "../global.h"
#include "../game/game_state.h"


namespace graphics {
    Shader::Shader(const Path &path) : Resource(path) {}


    Shader::~Shader() {
        glDeleteShader(m_id);
    }

    void Shader::load(std::size_t size, char *data) {
        if (path().path().ends_with("frag"))
            m_id = glCreateShader(GL_FRAGMENT_SHADER);
        else
            m_id = glCreateShader(GL_VERTEX_SHADER);

        assets::FileReader file_reader { path().path() };
        auto file_data = file_reader.get_file_content();

        const char* charData = file_data.c_str();

        glShaderSource(m_id, 1, &charData, nullptr);
        glCompileShader(m_id);

        int success;
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
            std::cout << infoLog;
            THROW_ERROR("GL ERROR: Failed to compile shader with path: %s", path().path());
        }
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(program);
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
            THROW_ERROR("GL ERROR: Failed to link shaders with paths: %s, %s", m_vertex_shader->path().path(), m_fragment_shader->path().path());
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

    void ShaderProgram::set_property(const std::string &property_name, glm::vec4 &&v) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform4f(uniform_lock, v.x, v.y, v.z, v.w);
    }

    void ShaderProgram::set_property(const std::string& property_name, glm::mat4 &&m) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniformMatrix4fv(uniform_lock, 1, GL_FALSE, glm::value_ptr(m));
    }

    void ShaderProgram::set_property(const std::string& property_name, const glm::vec3 &v) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform3f(uniform_lock, v.x, v.y, v.z);
    }

    void ShaderProgram::set_property(const std::string& property_name, const glm::vec4 &v) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniform4f(uniform_lock, v.x, v.y, v.z, v.w);
    }

    void ShaderProgram::set_property(const std::string& property_name, const glm::mat4 &m) const {
        int uniform_lock = glGetUniformLocation(program, property_name.c_str());
        glUniformMatrix4fv(uniform_lock, 1, GL_FALSE, glm::value_ptr(m));
    }

    void ShaderProgram::set_uniform_loc(const std::string& name, int index) const {
        int uniform_lock = glGetUniformLocation(program, name.c_str());
        glUniform1i(uniform_lock, index);
    }

    ShaderProgram::ShaderProgram(const std::string &path) {
        auto vert_shader_filename = path + ".vert";
        auto frag_shader_filename = path + ".frag";

        program = glCreateProgram();

        m_vertex_shader = global.game->cache().get_resource<Shader>(vert_shader_filename);
        m_fragment_shader = global.game->cache().get_resource<Shader>(frag_shader_filename);

        glAttachShader(program, m_vertex_shader->id());
        glAttachShader(program, m_fragment_shader->id());

        // Todo, make this a separate step
        link();
    }
}
