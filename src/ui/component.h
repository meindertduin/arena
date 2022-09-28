#pragma once

#include <string>
#include "../graphics/geometry.h"

#include "unordered_map"

namespace ui {
    enum UIEventType {
        MouseButton = 1,
        MouseMove = 2,
    };

    struct UIEvent;

    template<typename T>
    class ComponentBuilder;

    class UIComponent {
    public:
        glm::ivec2 pos;
        glm::ivec2 gl_pos;

        glm::ivec2 size;
        bool is_hovered { false };

        std::vector<std::unique_ptr<UIComponent>> children;
        UIComponent *parent {nullptr};

        UIComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : pos{pos}, size{size} { }

        virtual void render() {
            for (auto &child : children)
                child->render();
        }

        void handle_event(UIEventType type, UIEvent* event);
    protected:
        std::unordered_map<UIEventType, std::function<void(UIEvent*)>> event_handlers;
    };

    class RootComponent : public UIComponent {
    public:
        explicit RootComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
    };

    class PlaneComponent : public UIComponent {
    public:
        explicit PlaneComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
    private:
        friend class ComponentBuilder<PlaneComponent>;

        graphics::GpuPlane background;
        graphics::GpuPlane border;

        glm::vec4 *background_color;
        glm::vec4 border_color { 1.0f, 1.0f, 1.0f, 1.0f };
    };

    class TextComponent : public UIComponent {
    public:
        explicit TextComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
    private:
        friend class ComponentBuilder<TextComponent>;

        int text_size = 12;
        std::string text;
    };

    class ButtonComponent : public UIComponent {
    public:
        explicit ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        ~ButtonComponent() {
            printf("destructor called\n");
        }
        void render() override;
    private:
        glm::vec4 background_color;
        glm::vec4 border_color;
    };
}