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

    global.ecs.register_component<entity::Transform>();
    global.entity = global.ecs.create_entity();

    entity::Transform entity_transform;

    entity_transform.pos = { 0, 0, -9.0f };
    global.ecs.add_component(global.entity, entity_transform);

    while(!global.window->close_requested()) {
        global.renderer->render();
        global.window->end_frame();
    }

    return 0;
}
