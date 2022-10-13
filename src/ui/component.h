#pragma once

#include "events.h"
#include "object.h"

#include <glm/glm.hpp>

namespace ui {
    class Component : public Object {
    public:
        virtual void mouse_event(UIMouseMoveEvent &events);
        virtual void mouse_event(UIMouseClickEvent &events);
        virtual void on_tick(uint64_t tick);
        virtual void render();
    private:
        bool visible;
        bool enabled;

        glm::ivec2 min_size;
        glm::ivec2 max_size;
    };
}