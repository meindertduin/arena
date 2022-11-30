#pragma once

#include <string>
#include <glm/vec3.hpp>
#include "../logging.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace lua {
    bool execute(lua_State* L, std::string &script, std::string &name, int results_count);

    template<typename T>
    inline bool is_type(lua_State *L, int index) {
        return lua_islightuserdata(L, index) != 0;
    }

    template<>
    inline bool is_type<int>(lua_State *L, int index) {
        return lua_isnumber(L, index) != 0;
    }

    template<>
    inline bool is_type<glm::vec3>(lua_State *L, int index) {
        return lua_istable(L, index) != 0 && luaL_len(L, index) == 3;
    }

    template<>
    inline bool is_type<const char*>(lua_State *L, int index) {
        return lua_isstring(L, index) != 0;
    }

    template<typename T>
    inline T convert_type(lua_State *L, int index) {
        return static_cast<T>(lua_touserdata(L, index));
    }

    template<>
    inline const char* convert_type<const char*>(lua_State *L, int index) {
        return lua_tostring(L, index);
    }

    template<typename T>
    T check_arg(lua_State* L, int index) {
        if (!is_type<T>(L, index)) {
            THROW_ERROR("Argument cannot be converted to type %s", typeid(T).name());
        }

        return convert_type<T>(L, index);
    }

    void create_system_variable(lua_State *L, const char* system_name, const char* var_name, void* value);
    void create_system_variable(lua_State *L, const char* system_name, const char* var_name, int value);
    void create_system_function(lua_State *L, const char* system_name, const char* var_name, lua_CFunction function);
    void create_system_closure(lua_State *L, const char* system_name, void* object_ptr, const char* var_name, lua_CFunction function);
}