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

        template<typename ...Args>
        ComponentBuilder(Args&&... args) {
            component = std::make_unique<T>(std::forward<Args>(args)...);
        }

        ComponentBuilder<T>& with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
            set_component_pos_and_size(pos, size);
            return *this;
        }

        ComponentBuilder<T>& with_rel_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
            if (component->parent != nullptr) {
                glm::ivec2 rel_pos = { pos.x + component->parent->pos.x, component->parent->pos.y + pos.y };
                return with_pos_and_size(rel_pos, size);
            } else {
                return with_pos_and_size(pos, size);
            }
        }

        ComponentBuilder<T>& with_background(glm::vec4 *color) {
            component->background_color = color;
            component->background.set_pos_and_size({component->gl_pos.x, component->gl_pos.y}, {component->size.x, component->size.y});
            return *this;
        }

        ComponentBuilder<T>& with_parent(UIComponent *parent) {
            component->parent = parent;
            return *this;
        }

        template<typename C>
        ComponentBuilder& with_child(std::function<void(ComponentBuilder<C>&)> &&builder_setup_callback) {
            auto builder = ComponentBuilder<C>();
            builder.with_parent(component.get());
            builder_setup_callback(builder);
            auto child_component = builder.build();
            component->children.push_back(std::move(child_component));

            return *this;
        }

        template<typename C, typename ...Args>
        ComponentBuilder& with_child(glm::ivec2 &&pos, glm::ivec2 &&size, Args&&... args) {
            pos += component->pos;
            auto new_child = std::make_unique<C>(pos, size, std::forward<Args>(args)...);
            new_child->parent = component.get();
            component->children.push_back(std::move(new_child));

            return *this;
        }

        template<typename C, typename ...Args>
        ComponentBuilder& with_child(std::function<void(ComponentBuilder<C>&)> &&builder_setup_callback, glm::ivec2 &&pos, glm::ivec2 &&size, Args&&... args) {
            pos += component->pos;
            auto builder = ComponentBuilder<C>(pos, size, std::forward<Args>(args)...);
            builder.with_parent(component.get());
            builder_setup_callback(builder);
            auto child_component = builder.build();
            component->children.push_back(std::move(child_component));

            return *this;
        }

        ComponentBuilder<T> &with_border(int pixels, glm::vec4 &&color);

        ComponentBuilder<T>& with_text(std::string *text, int size) {
            component->text_size = size;
            component->text = text;
            return *this;
        }

        ComponentBuilder<T>& center_text() {
            auto parent_pos = component->parent->pos;
            auto parent_size = component->parent->size;

            // These algorithms are quite weird, but do work consistently
            component->pos.x = parent_pos.x + ((parent_size.x - component->text_size * component->text->length()) / 2) + component->text_size * 1.25f;
            component->pos.y = parent_pos.y + (parent_size.y / 2 + (component->text_size / 2)) - component->text_size / 5;
            set_component_pos_and_size(component->pos, component->size);
        }

        ComponentBuilder<T>& center_text_x() {
            auto parent_pos = component->parent->pos;
            auto parent_size = component->parent->size;

            component->pos.x = parent_pos.x + ((parent_size.x - component->text_size * component->text.length()) / 2) + component->text_size * 1.25f;
            set_component_pos_and_size(component->pos, component->size);
        }

        ComponentBuilder<T>& center_text_y() {
            auto parent_pos = component->parent->pos;
            auto parent_size = component->parent->size;

            component->pos.y = parent_pos.y + (parent_size.y / 2 + (component->text_size / 2));
            set_component_pos_and_size(component->pos, component->size);
        }

        std::unique_ptr<T> build() {
            return std::move(component);
        }
    private:
        std::unique_ptr<T> component;

        void set_component_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
            component->pos = pos;
            component->gl_pos = pos;
            component->gl_pos.y = global.graphic_options->screen_dimensions.y - pos.y - size.y;
            component->size = size;
        }
    };
}