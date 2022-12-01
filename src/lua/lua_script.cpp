#include "lua_script.h"
#include "../assets/file_reader.h"

extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace lua {
    void LuaScript::load(std::size_t size, char *data) {
        assets::FileReader reader { path().path() };
        m_script = reader.get_file_content();

        auto file_content = reader.get_file_content();
    }
}
