#pragma once

#include <string>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace lua {
    bool execute(lua_State* L, std::string &script, std::string &name, int results_count);

    void create_system_variable(lua_State *L, const char* system_name, const char* var_name, void* value);
    void create_system_variable(lua_State *L, const char* system_name, const char* var_name, int value);
}