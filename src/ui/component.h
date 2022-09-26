#pragma once

#include <string>
#include "../graphics/geometry.h"

namespace ui {
    struct UIMouseClickEvent;
    struct UIMouseMoveEvent;

    class UIComponent {
    public:
        glm::ivec2 pos;
        glm::ivec2 size;
        std::vector<std::unique_ptr<UIComponent>> children;
        bool is_hovered { false };

        UIComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : pos{pos}, size{size} { }

        virtual void render() = 0;
        virtual void handle_click(const UIMouseClickEvent &event) { };
    protected:
        friend class UI;
        UIComponent *parent {nullptr};
    };

    class RootComponent : public UIComponent {
    public:
        explicit RootComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
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

        // TODO make border and background own component
        glm::vec4 background_color { 1.0f, 0, 0, 1.0f };
    };
}