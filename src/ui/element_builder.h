#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "component.h"

namespace ui {
    template<typename T>
    class ElementBuilder {
    public:
        template<typename ...Args>
        static ElementBuilder<T> get(UiElement *parent, const glm::ivec2 &pos, Args&&... args) {
            return ElementBuilder<T>{ parent, pos, std::forward<Args>(args)... };
        }

        template<typename ...Args>
        explicit ElementBuilder(UiElement *parent, const glm::ivec2 &pos, Args&&... args) {
            element = std::make_unique<T>(pos, std::forward<Args>(args)...);
            element->parent = parent;
            with_relative_pos(pos);
        }

        std::unique_ptr<T> build() {
            return std::move(element);
        }

    private:
        std::unique_ptr<T> element;

        void with_relative_pos(const glm::ivec2 &pos) {
            element->display_type = DisplayType::Relative;
            element->pos = element->parent->pos + pos;
        }
    };
}