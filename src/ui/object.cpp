#include "object.h"

namespace ui {
    void Object::add_child(Object &object) {
        object.parent = this;
        children.push_back(std::make_unique<Object>(std::move(object)));
    }
}