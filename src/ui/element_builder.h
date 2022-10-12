#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "component.h"

namespace ui {
    template<typename T>
    class ElementBuilder {
    public:
        template<typename ...Args>
        static ElementBuilder<T> get(UiElement *parent, Args&&... args) {
            return ElementBuilder<T>{ parent, std::forward<Args>(args)... };
        }

        template<typename ...Args>
        explicit ElementBuilder(UiElement *parent, Args&&... args) {
            element = std::make_unique<T>(std::forward<Args>(args)...);
            element->parent = parent;

            element->display_type = DisplayType::Relative;
        }

        template<typename C, typename ...Args>
        ElementBuilder<T>& add_attribute(AttributeType type, Args&&... args) {
            element->template add_attribute<C>(type, std::forward<Args>(args)...);
            return *this;
        }

        ElementBuilder<T>& add_event_handler(std::pair<UIEventType, std::function<void(UIEvent*)>> &&insert_pair) {
            element->event_handlers.insert(insert_pair);
            return *this;
        }

        ElementBuilder<T>& with_display(bool value) {
            element->display = value;
            return *this;
        }

        ElementBuilder<T>& with_display_type(DisplayType display_type) {
            element->display_type = display_type;
            return *this;
        }

        std::unique_ptr<T> build() {
            return std::move(element);
        }

    private:
        std::unique_ptr<T> element;
    };
}