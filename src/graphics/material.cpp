#include "material.h"
#include "../assets/file_reader.h"

#include "../lua/helpers.h"
#include "../global.h"
#include "../game/game_state.h"

namespace graphics {
namespace lua_api {
    static Material* get_material(lua_State *L) {
        lua_getglobal(L, "this");
        auto material = lua::convert_type<Material*>(L, -1);
        lua_pop(L, 1);
        return material;
    }

    static int uniform(lua_State *L) {
        auto material = get_material(L);

        auto name = lua::check_arg<const char*>(L, 1);
        Material::Uniform uniform;
        uniform.name = name;

        switch (lua_type(L, 2)) {
            case LUA_TNUMBER:
                uniform.float_value = lua::check_arg<float>(L, 2);
                break;
            case LUA_TTABLE:
                auto len = luaL_len(L, 2);
                switch (len) {
                    case 2:
                        uniform.v2 = lua::check_arg<glm::vec2>(L, 2);
                        break;
                    case 3:
                        uniform.v3 = lua::check_arg<glm::vec3>(L, 2);
                        break;
                    case 4:
                        uniform.v4 = lua::check_arg<glm::vec4>(L, 2);
                        break;
                    default:
                        luaL_error(L, "Uniform %s is not supported", name);
                        break;
                }
        }

        material->add_uniform(uniform);
    }
}

    void Material::load() {
        assets::FileReader file_reader { path().path() };
        auto file_content = file_reader.get_file_content();

        auto root_state = global.game->lua_state();
        auto L = lua_newthread(root_state);
        const auto state_ref = luaL_ref(root_state, LUA_REGISTRYINDEX);

        lua_pushlightuserdata(L, this);
        lua_setglobal(L, "this");

        lua_pushcfunction(L, lua_api::uniform);
        lua_setglobal(L, "uniform");

        lua::execute(L, file_content, path().path(), 0);

        luaL_unref(root_state, LUA_REGISTRYINDEX, state_ref);
    }

    void Material::update() {
        auto &program = m_shader->program();

        for (auto &uniform : m_uniforms) {
            for (auto &shader_uniform : m_shader->uniforms()) {
                if (uniform.name == shader_uniform.name) {
                    switch (shader_uniform.type) {
                        case graphics::Uniform::Int:
                            program.set_property(uniform.name, uniform.int_value);
                            break;
                        case graphics::Uniform::Float:
                            program.set_property(uniform.name, uniform.float_value);
                            break;
                        case graphics::Uniform::Matrix4:
                            program.set_property(uniform.name, uniform.matrix);
                            break;
                        case graphics::Uniform::Vec3:
                            program.set_property(uniform.name, uniform.v3);
                            break;
                        default:
                            THROW_ERROR("Uniform type not implemented");
                    }
                    break;
                }
            }
        }
    }
}