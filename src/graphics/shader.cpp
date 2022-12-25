#include "shader.h"

#include <glad/glad.h>

#include <iostream>

#include "../logging.h"
#include "../assets/file_reader.h"
#include "../lua/helpers.h"

#include "../global.h"
#include "../lua/lua_script.h"
#include "../assets/cache.h"

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
    static int add_stage(lua_State *L) {
        auto shader = get_shader(L);
        auto path = std::string { lua::check_arg<const char*>(L, 1) };

        Stage new_stage;
        if (path.ends_with(".frag")) {
            new_stage.type = ShaderType::Fragment;
        } else if (path.ends_with(".vert")) {
            new_stage.type = ShaderType::Vertex;
        }

        assets::FileReader file_reader { path };
        new_stage.content = file_reader.get_file_content();
        new_stage.path = path;

        shader->add_stage(new_stage);

        return 0;
    }

    static int set_uniform_loc(lua_State *L) {
        auto shader = get_shader(L);

        auto name = std::string { lua::check_arg<const char*>(L, 1) };
        auto index = lua::check_arg<int>(L, 2);

        shader->add_uniform_loc({ name, index });

        return 0;
    }

    static int uniform(lua_State *L) {
        auto shader = get_shader(L);

        auto name = lua::check_arg<const char*>(L, 1);
        auto type = lua::check_arg<const char*>(L, 2);

        Uniform uniform;
        uniform.name = name;

        static struct {
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
        }

        if (lua_gettop(L) > 2) {
            switch (lua_type(L, 3)) {
                case LUA_TNUMBER:
                    uniform.value.float_value = lua::check_arg<float>(L, 3);
                    break;
                case LUA_TTABLE: {
                    auto len = luaL_len(L, 3);
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

    static lua_State* get_shader_state() {
        static lua_State* L { nullptr };

        if (L == nullptr) {
            L = luaL_newstate();
            luaL_openlibs(L);

            lua_pushcfunction(L, lua_api::add_stage);
            lua_setglobal(L, "addStage");

            lua_pushcfunction(L, lua_api::set_uniform_loc);
            lua_setglobal(L, "setUniformLoc");

            lua_pushcfunction(L, lua_api::uniform);
            lua_setglobal(L, "uniform");
        }

        return L;
    }
}

    Shader::~Shader() {
        for (auto &stage : m_stages) {
            glDeleteShader(stage.id);
        }
    }

    void Shader::load() {
        auto cache = global.application->engine()->cache();
        auto script = cache->get_resource<lua::LuaScript>(path().path());

        auto root_state = lua_api::get_shader_state();
        auto L = lua_newthread(root_state);
        const auto state_ref = luaL_ref(root_state, LUA_REGISTRYINDEX);

        lua_pushlightuserdata(L, this);
        lua_setglobal(L, "this");

        lua::execute(L, script->script(), script->path().path(), 0);

        luaL_unref(root_state, LUA_REGISTRYINDEX, state_ref);

        compile();
    }

    void Shader::compile() {
        for (auto &stage : m_stages) {
            switch (stage.type) {
                case ShaderType::Vertex:
                    stage.id = glCreateShader(GL_VERTEX_SHADER);
                    break;
                case ShaderType::Fragment:
                    stage.id = glCreateShader(GL_FRAGMENT_SHADER);
                    break;
            }

            const char* content_data =  stage.content.c_str();
            glShaderSource(stage.id, 1, &content_data, nullptr);
            glCompileShader(stage.id);

            int success;
            glGetShaderiv(stage.id, GL_COMPILE_STATUS, &success);
            if (!success) {
                GLchar infoLog[1024];
                glGetShaderInfoLog(stage.id, 1024, nullptr, infoLog);
                std::cout << infoLog;
                THROW_ERROR("GL ERROR: Failed to compile shader with path: %s", stage.path);
            }
        }

        // TODO make attaching and linking separate steps
        for (auto &stage : m_stages) {
            m_program.attach(stage);
        }
        m_program.link();

        m_program.use();
        for (auto &uniform_loc : m_uniform_locs) {
            m_program.set_uniform_loc(uniform_loc.name, uniform_loc.index);
        }
    }

    void Shader::add_uniform(const Uniform &uniform) {
        m_uniforms.push_back(uniform);
    }

    void Shader::add_stage(const Stage &stage) {
        m_stages.push_back(stage);
    }

    void Shader::add_uniform_loc(const UniformLoc &loc) {
        m_uniform_locs.push_back(loc);
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
            GLchar info_log[1024];
            glGetProgramInfoLog(program, 1024, nullptr, info_log);
            auto log = std::string {info_log};
            std::cout << info_log;
            THROW_ERROR("GL ERROR: Failed to link shaders");
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

    ShaderProgram::ShaderProgram() {
        program = glCreateProgram();
    }

    void ShaderProgram::attach(const Stage &stage) const {
        glAttachShader(program, stage.id);
    }
}
