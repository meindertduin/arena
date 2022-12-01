#include "shader.h"

#include <glad/glad.h>

#include <iostream>
#include <utility>

#include "../logging.h"
#include "../assets/file_reader.h"
#include "../lua/helpers.h"

#include "../global.h"
#include "../game/game_state.h"

namespace graphics {
    uint32_t Uniform::size() const {
        switch (type) {
            case Int: return sizeof(int);
            case Float: return sizeof(float);
            case Matrix4: return sizeof(glm::mat4);
            case Vec2: return sizeof(glm::vec2);
            case Vec3: return sizeof(glm::vec3);
            case Vec4: return sizeof(glm::vec4);
            default:
                THROW_ERROR("Type is out of range");
        }
    }

    static Shader* get_shader(lua_State *L) {
        lua_getglobal(L, "this");
        auto shader = lua::convert_type<Shader*>(L, -1);
        lua_pop(L, 1);
        return shader;
    }

namespace lua_api {
    static int set_property(lua_State *L) {
        auto shader = get_shader(L);

        auto property_name = lua::check_arg<const char*>(L, 2);
        auto p = lua::check_arg<glm::vec3>(L, 3);

        shader->set_property(std::string { property_name }, p);

        return 0;
    }

    static int uniform(lua_State *L) {
        auto shader = get_shader(L);

        auto name = lua::check_arg<const char*>(L, 1);
        auto type = lua::check_arg<const char*>(L, 2);

        Uniform uniform;
        uniform.name = name;

        const struct {
            std::string name;
            Uniform::Type type;
        } types[] = {
                { "float", Uniform::Float },
                { "int", Uniform::Int },
                { "mat4", Uniform::Matrix4 },
                { "vec2", Uniform::Vec2 },
                { "vec3", Uniform::Vec3 },
                { "vec4", Uniform::Vec4 },
        };

        auto valid = false;
        for (const auto &t: types) {
            if (t.name == type) {
                uniform.type = t.type;
                valid = true;
                break;
            }
        }

        if (!valid) {
            THROW_ERROR("Unknown uniform type");
            return 0;
        }

        if (lua_gettop(L) > 2) {
            switch (lua_type(L, 3)) {
                case LUA_TNUMBER:
                    uniform.value.float_value = lua::check_arg<float>(L, 3);
                    break;
                case LUA_TTABLE: {
                    auto len = luaL_len(L, 4);
                    switch(len) {
                        case 2:
                            uniform.value.v2 = lua::check_arg<glm::vec2>(L, 3);
                            break;
                        case 3:
                            uniform.value.v3 = lua::check_arg<glm::vec3>(L, 3);
                            break;
                        case 4:
                            uniform.value.v4 = lua::check_arg<glm::vec4>(L, 3);
                            break;
                        default:
                            luaL_error(L, "Uniform %s is not supported", name);
                            break;
                    }
                    break;
                }
            }
        }

        if (shader->uniforms().empty()) {
            uniform.offset = 0;
        } else {
            auto last_uniform = shader->uniforms()[shader->uniforms().size() -1];
            uniform.offset = last_uniform.offset + last_uniform.size();
        }

        shader->add_uniform(uniform);
        return 0;
    }
}

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

        auto script = global.game->cache().get_resource<lua::LuaScript>("scripts/lightsVertex.lua");

        auto root_state = global.game->lua_state();
        auto L = lua_newthread(root_state);
        const auto state_ref = luaL_ref(root_state, LUA_REGISTRYINDEX);

        lua_pushlightuserdata(L, this);
        lua_setglobal(L, "this");

        lua_pushcfunction(L, lua_api::set_property);
        lua_setglobal(L, "setProperty");

        lua_pushcfunction(L, lua_api::uniform);
        lua_setglobal(L, "uniform");

        lua::execute(L, script->script(), script->path().path(), 0);

        luaL_unref(root_state, LUA_REGISTRYINDEX, state_ref);
    }

    void Shader::set_property(const std::string &property_name, const glm::vec3 &v) const {
        printf("setting property %s: %f %f %f", property_name.c_str(), v.x, v.y, v.z);
    }

    void Shader::add_uniform(const Uniform &uniform) {
        m_uniforms.push_back(uniform);
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
