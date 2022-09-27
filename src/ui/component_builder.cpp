#include "component_builder.h"

namespace ui {
    template<>
    ComponentBuilder<ButtonComponent>& ComponentBuilder<ButtonComponent>::with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
        component->pos = pos;
        component->gl_pos = pos;
        component->gl_pos.y = global.graphic_options->screen_dimensions.y - pos.y - size.y;
        component->size = size;

        component->border.set_pos_and_size(component->gl_pos, component->size);
        component->background.set_pos_and_size({component->gl_pos.x + 2, component->gl_pos.y + 2}, {size.x - 4, size.y - 4});

        return *this;
    }

    template<>
    ComponentBuilder<PlaneComponent>& ComponentBuilder<PlaneComponent>::with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
        component->pos = pos;
        component->gl_pos = pos;
        component->gl_pos.y = global.graphic_options->screen_dimensions.y - pos.y - size.y;
        component->size = size;

        component->background.set_pos_and_size({component->gl_pos.x + 2, component->gl_pos.y + 2}, {size.x - 4, size.y - 4});

        return *this;
    }
}