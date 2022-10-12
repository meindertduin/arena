#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "component.h"

namespace ui {

    template<typename T>
    class ElementBuilder {
    public:
        template<typename ...Args>
        static ElementBuilder<T> get(Args&&... args) {
            return ElementBuilder<T>{std::forward<Args>(args)...};
        }

        template<typename ...Args>
        explicit ElementBuilder(Args&&... args) {
            element = std::make_unique<T>(std::forward<Args>(args)...);
        }

        ElementBuilder<T>& with_relative_pos(UiElement* rel_element, const glm::ivec2 &pos) {
            element->display_type = DisplayType::Relative;
            element->pos = rel_element->pos + pos;
        }

        std::unique_ptr<T> build() {
            return std::move(element);
        }
    private:
        std::unique_ptr<T> element;
    };
}