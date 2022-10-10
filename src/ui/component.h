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
        virtual void on_tick(uint64_t tick) { }

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
    protected:
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
}