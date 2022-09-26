#pragma once

#include <algorithm>
#include <memory>
#include <functional>
#include <glm/glm.hpp>

namespace ui {
    template<typename T>
    class ComponentBuilder {
    public:
        ComponentBuilder() {
            component = std::make_unique<T>(glm::ivec2 { }, glm::ivec2 { });
        }

        ComponentBuilder<T>& with_pos(const glm::ivec2 &pos) {
            component->pos = pos;
            return *this;
        }

        ComponentBuilder<T>& with_size(const glm::ivec2 &size) {
            component->size = size;
            return *this;
        }

        template<typename C>
        ComponentBuilder& with_child(const std::function<void(ComponentBuilder<C>&)> &builder_setup_callback) {
            auto builder = ComponentBuilder<C>();
            builder_setup_callback(builder);
            auto child_component = builder.build();
            child_component->parent = component.get();
            component.children.push_back(std::move(child_component));

            return *this;
        }

        std::unique_ptr<T> build() {
            return std::move(component);
        }
    private:
        std::unique_ptr<T> component;
    };
}