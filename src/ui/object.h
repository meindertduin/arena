#pragma once

#include <vector>
#include <memory>

namespace ui {
    class Object {
    public:
        void add_child(Object&);
        std::vector<std::unique_ptr<Object>>& get_children() { return children; }
    private:
        Object *parent;
        std::vector<std::unique_ptr<Object>> children;
    };
}