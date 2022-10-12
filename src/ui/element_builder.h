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

        ElementBuilder<T>& set_parent(UiElement* parent) {
            element->parent = parent;
            return *this;
        }

        template<typename ...Args>
        explicit ElementBuilder(Args&&... args) {
            element = std::make_unique<T>(std::forward<Args>(args)...);
        }

        ElementBuilder<T>& with_relative_pos(const glm::ivec2 &pos) {
            element->display_type = DisplayType::Relative;
            element->pos = element->parent->pos + pos;

            return *this;
        }

        std::unique_ptr<T> build() {
            return std::move(element);
        }
    private:
        std::unique_ptr<T> element;
    };
}