#include "helpers.h"

namespace lua {
    bool execute(lua_State* L, std::string &script, std::string &name, int results_count) {
        if(luaL_loadbuffer(L, script.c_str(), script.length(), name.c_str()) != 0) {
            // TODO add logging
            lua_pop(L, 1);
            return false;
        }

        if (lua_pcall(L, 0, results_count, -2) != 0) {
            lua_pop(L, 1);
            return false;
        }

        lua_pop(L, 0);
        return true;
    }

    void create_system_variable(lua_State *L, const char* system_name, const char* var_name, void* value) {
        lua_getglobal(L, system_name);
        if (lua_type(L, -1) == LUA_TNIL) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_setglobal(L, system_name);
            lua_getglobal(L, system_name);
        }
        lua_pushlightuserdata(L, value);
        lua_setfield(L, -2, var_name);
        lua_pop(L, 1);
    }

    void create_system_variable(lua_State *L, const char* system_name, const char* var_name, int value) {
        lua_getglobal(L, system_name);
        if (lua_type(L, -1) == LUA_TNIL) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_setglobal(L, system_name);
            lua_getglobal(L, system_name);
        }
        lua_pushinteger(L, value);
        lua_setfield(L, -2, var_name);
        lua_pop(L, 1);
    }

    void create_system_function(lua_State *L, const char* system_name, const char* var_name, lua_CFunction function) {
        lua_getglobal(L, system_name);
        if (lua_type(L, -1) == LUA_TNIL) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_setglobal(L, system_name);
            lua_getglobal(L, system_name);
        }
        lua_pushcfunction(L, function);
        lua_setfield(L, -2, var_name);
        lua_pop(L, 1);
    }

    void create_system_closure(lua_State *L, const char* system_name, void* object_ptr, const char* var_name, lua_CFunction function) {
        lua_getglobal(L, system_name);
        if (lua_type(L, -1) == LUA_TNIL) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_setglobal(L, system_name);
            lua_getglobal(L, system_name);
        }
        lua_pushlightuserdata(L, object_ptr);
        lua_pushcclosure(L, function, 1);
        lua_setfield(L, -2, var_name);
        lua_pop(L, 1);
    }
}