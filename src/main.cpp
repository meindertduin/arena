#include <stdio.h>

#include "global.h"

Global global;

int main () {
    auto window_options = core::WindowOptions {
        .width = 1280,
        .height = 720,
        .window_name = "Arena"
    };

    global.window = new core::Window(window_options);
    global.renderer = new graphics::Renderer(window_options.width, window_options.height);

    global.mesh = new graphics::Mesh();

    global.component_manager = new entity::ComponentManager {};
    global.entity_manager = new entity::EntityManager {};

    global.component_manager->register_component<entity::Transform>();

    global.entity = global.entity_manager->create_entity();

    entity::Transform entity_transform;

    entity_transform.pos = { 0, 0, -9.0f };
    global.component_manager->add_component(global.entity, entity_transform);

    while(!global.window->close_requested()) {
        global.renderer->render();
        global.window->end_frame();
    }

    return 0;
}
