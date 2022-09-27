#pragma once

#include <string>
#include "../graphics/geometry.h"

namespace ui {
    struct UIMouseClickEvent;
    struct UIMouseMoveEvent;

    template<typename T>
    class ComponentBuilder;

    class UIComponent {
    public:
        glm::ivec2 pos;
        glm::ivec2 gl_pos;

        glm::ivec2 size;
        bool is_hovered { false };

        // TODO: Encapsulate and make builder friend
        std::vector<std::unique_ptr<UIComponent>> children;
        UIComponent *parent {nullptr};

        UIComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : pos{pos}, size{size} { }

        virtual void render() {
            for (auto &child : children)
                child->render();
        }

        virtual void handle_click(const UIMouseClickEvent &event) { };
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

        glm::vec4 background_color { 1.0f, 0, 0, 1.0f };
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
        void handle_click(const UIMouseClickEvent &event) override;
    private:
        friend class ComponentBuilder<ButtonComponent>;

        std::string text;
        int text_size = 12;

        graphics::GpuPlane background;
        graphics::GpuPlane border;

        glm::vec4 background_color { 1.0f, 0, 0, 1.0f };
        glm::vec4 border_color { 1.0f, 1.0f, 1.0f, 1.0f };
    };
}