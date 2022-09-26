#include "component_builder.h"

namespace ui {
    template<>
    ComponentBuilder<ButtonComponent>& ComponentBuilder<ButtonComponent>::with_pos_and_size(const glm::ivec2 &pos, const glm::ivec2 &size) {
        component->pos = pos;
        component->size = size;
        component->border.set_pos_and_size({pos.x, pos.y}, {size.x, size.y});
        component->background.set_pos_and_size({pos.x + 2, pos.y + 2}, {size.x - 4, size.y - 4});

        return *this;
    }
}