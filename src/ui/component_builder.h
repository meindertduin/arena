#pragma once

#include <algorithm>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include "component.h"
#include "../global.h"
#include "../graphics/graphic_options.h"

namespace ui {
    template<typename T>
    class ComponentBuilder {
    public:
        ComponentBuilder() {
            component = std::make_unique<T>(glm::ivec2 { }, glm::ivec2 { });
        }

        ComponentBuilder<T>& with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
            component->pos = pos;
            component->size = size;
            component->pos.y = global.graphic_options->screen_dimensions.y - pos.y - size.y;
            return *this;
        }

        ComponentBuilder<T>& with_rel_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
            if (component->parent != nullptr) {
                glm::ivec2 rel_pos = { pos.x + component->parent->pos.x, component->parent->pos.y - pos.y };
                return with_pos_and_size(rel_pos, size);
            } else {
                return with_pos_and_size(pos, size);
            }
        }

        template<typename C>
        ComponentBuilder& with_child(std::function<void(ComponentBuilder<C>&)> &&builder_setup_callback) {
            auto builder = ComponentBuilder<C>();
            builder_setup_callback(builder);
            auto child_component = builder.build();
            child_component->parent = component.get();
            component->children.push_back(std::move(child_component));

            return *this;
        }

        std::unique_ptr<T> build() {
            return std::move(component);
        }
    private:
        std::unique_ptr<T> component;
    };
}