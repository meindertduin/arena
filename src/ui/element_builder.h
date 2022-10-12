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

        std::unique_ptr<T> build() {
            return std::move(element);
        }

    private:
        std::unique_ptr<T> element;
    };
}