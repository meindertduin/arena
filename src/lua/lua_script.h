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

        constexpr std::string& script() { return m_script; }
    protected:
        friend class assets::Cache;

        void load(std::size_t size, char *data) override;
        void unload() override {}
    private:
        std::string m_script;
    };
}
