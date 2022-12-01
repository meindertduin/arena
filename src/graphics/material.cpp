#include "material.h"
#include "../assets/file_reader.h"

#include "../lua/helpers.h"
#include "../global.h"
#include "../game/game_state.h"

namespace graphics {
namespace lua_api {
    static Material* get_material(lua_State *L) {
        lua_getglobal(L, "this");
        auto material = lua::convert_type<Material*>(L, 1);
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
                        uniform.v2 = lua::check_arg<glm::vec2>(L, 3);
                        break;
                    case 3:
                        uniform.v3 = lua::check_arg<glm::vec3>(L, 4);
                        break;
                    case 4:
                        uniform.v4 = lua::check_arg<glm::vec4>(L, 4);
                        break;
                    default:
                        luaL_error(L, "Uniform %s is not supported", name);
                        break;
                }
        }

        // TODO remove this once uniforms are implemented
        if (uniform.name == "diffuse") {
            material->diffuse = uniform.v3;
        } else if (uniform.name == "ambient") {
            material->ambient = uniform.v3;
        } else if (uniform.name == "specular") {
            material->specular = uniform.v3;
        } else if (uniform.name == "shininess") {
            material->shininess = uniform.float_value;
        }

        material->add_uniform(uniform);
    }
}

    void Material::load(std::size_t size, char *data) {
        assets::FileReader file_reader { path().path() };
        auto file_content = file_reader.get_file_content();

        auto L = global.game->lua_state();

        lua_pushlightuserdata(L, this);
        lua_setglobal(L, "this");

        lua_pushcfunction(L, lua_api::uniform);
        lua_setglobal(L, "uniform");
    }
}