#pragma once

#include <string>
#include "../graphics/geometry.h"

#include <unordered_map>
#include <map>
#include <utility>
#include <optional>

namespace ui {
    enum UIEventType {
        MouseButton = 1,
        MouseMove = 2,
    };

    struct UIEvent;

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
        explicit TextAttribute(std::string text) : text{std::move(text)} { }
        explicit TextAttribute(std::string text, int text_size, bool centered = false) : text{std::move(text)},
            text_size{text_size}, center_text{centered} { }

        std::string text;
        bool center_text { false };
        bool text_wrap { false };
        int text_size { 12 };
    };

    class GeometryAttribute : public UiAttribute {
    public:
        GeometryAttribute(const glm::vec4 &background_color) : background_color{background_color} { }
        GeometryAttribute(const glm::vec4 &background_color, const glm::vec4 &border_color, int border_size)
            : background_color{background_color}, border_color{border_color}, border_size{border_size} { }

        glm::vec4 background_color { 0, 0, 0, 0};

        int border_size;
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

        std::unordered_map<UIEventType, std::function<void(UIEvent*)>> event_handlers;

        UiElement(const glm::ivec2 &pos, const glm::ivec2 &size) : pos{pos}, size{size} { }

        template<typename T>
        T* get_attribute(AttributeType type) {
            return reinterpret_cast<T*>(this->attributes[type].get());
        }

        template<typename T>
        std::optional<T*> get_attribute_opt(AttributeType type) {
            if (this->attributes.contains(type)) {
                return std::optional<T*>{ get_attribute<T>(type) };
            }

            return std::nullopt;
        }

        template<typename T, typename ...Args>
        void add_attribute(AttributeType type, Args&&... args) {
            attributes.insert({ type, std::make_unique<T>(std::forward<Args>(args)...) });
        }

        template<typename T>
        void add_attribute(AttributeType type, std::unique_ptr<T> &&attribute) {
            attributes.insert({ type, std::forward<std::unique_ptr<T>>(attribute) });
        }

        void handle_event(UIEventType type, UIEvent* event);
        virtual void on_tick(uint64_t tick) { }
    protected:
        std::map<AttributeType, std::unique_ptr<UiAttribute>> attributes;
    };

    class RootElement : public UiElement {
    public:
        RootElement(const glm::ivec2 &pos, const glm::ivec2 &size) : UiElement(pos, size) { }
    };

    class TextElement : public UiElement {
    public:
        TextElement(const glm::ivec2 &pos, const glm::ivec2 &size, const std::string &text);
    };

    class FrameTimeCounter : public UiElement {
    public:
        FrameTimeCounter(const glm::ivec2 &pos, const glm::ivec2 &size, int text_size);
        void on_tick(uint64_t tick) override;
    private:
        static std::string get_frame_time_string();
    };

    class Button : public UiElement {
    public:
        Button(const glm::ivec2 &pos, const glm::ivec2 &size, std::string text, std::function<void(UIEvent*)>&& on_click);
    };

    class Component {
    public:
        Component();
        virtual void render() = 0;
    };

    class Drawer : public UiElement {
    public:
        Drawer(const glm::ivec2 &pos, const glm::ivec2 &size);
    private:
        bool expanded { false };
        glm::ivec2 folded_size;
        glm::ivec2 expanded_size;
    };
}