#include "component_builder.h"

namespace ui {
    template<>
    ComponentBuilder<ButtonComponent>& ComponentBuilder<ButtonComponent>::with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
        set_component_pos_and_size(pos, size);

        component->border.set_pos_and_size(component->gl_pos, component->size);
        component->background.set_pos_and_size({component->gl_pos.x + 2, component->gl_pos.y + 2}, {size.x - 4, size.y - 4});

        return *this;
    }

    template<>
    ComponentBuilder<PlaneComponent>& ComponentBuilder<PlaneComponent>::with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
        set_component_pos_and_size(pos, size);

        component->background.set_pos_and_size({component->gl_pos.x + 2, component->gl_pos.y + 2}, {size.x - 4, size.y - 4});

        return *this;
    }

    template<>
    ComponentBuilder<ButtonComponent>& ComponentBuilder<ButtonComponent>::with_border(int pixels, glm::vec4 &&color) {
        component->border_color = color;
        component->border.set_pos_and_size(component->gl_pos, component->size);
        component->background.set_pos_and_size({component->gl_pos.x + pixels, component->gl_pos.y + pixels}, {component->size.x - 2 * pixels, component->size.y - 2 * pixels});
        return *this;
    }

    template<>
    ComponentBuilder<PlaneComponent>& ComponentBuilder<PlaneComponent>::with_border(int pixels, glm::vec4 &&color) {
        component->border_color = color;
        component->border.set_pos_and_size(component->gl_pos, component->size);
        component->background.set_pos_and_size({component->gl_pos.x + pixels, component->gl_pos.y + pixels}, {component->size.x - 2 * pixels, component->size.y - 2 * pixels});
        return *this;
    }
}