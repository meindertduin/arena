#pragma once

#include "../assets/resource.h"

extern "C" {
    #include "lua.h"
}

namespace lua {
    class LuaScript final : public assets::Resource {
    public:
        explicit LuaScript(const Path &path) : assets::Resource(path) {}

        LuaScript(const LuaScript&) = delete;
        LuaScript& operator=(const LuaScript&) = delete;

        void load(std::size_t size, char *data) override;
        void unload() override {}

        constexpr std::string& script() { return m_script; }
    private:
        std::string m_script;
    };
}
