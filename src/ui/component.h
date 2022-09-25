#pragma once

#include <string>
#include "../graphics/geometry.h"

namespace ui {
    struct UIMouseClickEvent;

    class UIComponent {
    public:
        glm::ivec2 pos;
        glm::ivec2 size;
        UIComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : pos{pos}, size{size} { }

        virtual void render() = 0;
        virtual void handle_click(const UIMouseClickEvent &event) { };
    };

    class ButtonComponent : public UIComponent {
    public:
        explicit ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
        void handle_click(const UIMouseClickEvent &event) override;
    private:
        std::string text;
        graphics::GpuPlane background;
        graphics::GpuPlane border;
    };
}