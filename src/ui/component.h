#pragma once

#include "events.h"
#include "object.h"
#include "../graphics/rect.h"
#include "../graphics/color.h"

#include <glm/glm.hpp>

using graphics::IRect;
using graphics::Color;

namespace ui {
    class Component : public Object {
    public:
        virtual void mouse_event(UIMouseMoveEvent &events);
        virtual void mouse_event(UIMouseClickEvent &events);
        virtual void on_tick(uint64_t tick);
        virtual void render();

        [[nodiscard]] constexpr ALWAYS_INLINE IRect rect() const { return m_rect; }
        [[nodiscard]] constexpr ALWAYS_INLINE Color color() const { return m_color; }

        void set_rect(const IRect &rect);
        void set_color(const Color &color);
    private:
        bool visible { true };
        bool enabled { true };

        glm::ivec2 min_size;
        glm::ivec2 max_size;

        IRect m_rect;
        Color m_color;
    };
}