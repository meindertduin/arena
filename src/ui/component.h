#pragma once

#include <string>
#include "../graphics/geometry.h"

#include <unordered_map>
#include <map>

namespace ui {
    enum UIEventType {
        MouseButton = 1,
        MouseMove = 2,
    };

    struct UIEvent;

    template<typename T>
    class ComponentBuilder;

    enum class AttributeType {
        Geometry,
        GeometryHovered,
        Border,
        Text,
    };

    class UiAttribute {
    };

    class TextAttribute : public UiAttribute {
    public:
        TextAttribute(const std::string &text) : text{text} { }
        std::string text;
        bool center_text { false };
        bool text_wrap { false };
        int text_size { 12 };
    };

    class GeometryAttribute : public UiAttribute {
    public:
        GeometryAttribute(const glm::vec4 &background_color) : background_color{background_color} { }
        glm::vec4 background_color { 0, 0, 0, 0};

        glm::ivec4 border_size { 0, 0, 0, 0 };
        glm::vec4 border_color { 0, 0, 0, 0 };
    };

    class UiElement {
    public:
        int id;
        glm::ivec2 pos;
        glm::ivec2 size;
        glm::ivec4 padding { 0, 0, 0, 0};
        glm::ivec4 margin { 0, 0, 0, 0 };

        UiElement *parent { nullptr };
        std::vector<std::unique_ptr<UiElement>> children;

        bool is_hovered { false };

        std::map<AttributeType, std::unique_ptr<UiAttribute>> attributes;
        std::unordered_map<UIEventType, std::function<void(UIEvent*)>> event_handlers;

        void handle_event(UIEventType type, UIEvent* event);
        UiElement(const glm::ivec2 &pos, const glm::ivec2 &size) : pos{pos}, size{size} { }
    protected:
    };

    class RootElement : public UiElement {
    public:
        RootElement(const glm::ivec2 &pos, const glm::ivec2 &size) : UiElement(pos, size) { }
    };

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

    class TextElement : public UiElement {
    public:
        TextElement(const glm::ivec2 &pos, const glm::ivec2 &size, const std::string &text);
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
        std::string *text;
    };

    class ButtonComponent : public UIComponent {
    public:
        explicit ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
    private:
        glm::vec4 background_color;
        glm::vec4 border_color;

        std::string text = "Hello world";
    };

    class DebugPanelComponent : public UIComponent {
    public:
        explicit DebugPanelComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
    private:
        glm::vec4 background_color { 0.1f, 0.1f, 0.1f, 0.2f };
        std::string text = "Hello world";
    };
}