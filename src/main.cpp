#include <stdio.h>

#include "global.h"
#include "input/input.h"

Global global;

int main () {
    auto window_options = core::WindowOptions {
        .width = 1280,
        .height = 720,
        .window_name = "Arena"
    };

    global.graphic_options = new graphics::GraphicOptions {
        true,
        { window_options.width, window_options.height },
    };

    global.window = new core::Window(window_options);
    global.renderer = new graphics::Renderer();
    input::initialize_input(*global.window);

    global.ecs = entity::Ecs::instance();

    global.material = {
        .ambient = { 0.2f, 0.2f, 0.2f },
        .diffuse = { 0.6f, 0.6f, 0.6f },
        .specular = { 0.2f, 0.2f, 0 },
        .shininess = 0.2f,
    };
    global.texture = new graphics::Texture("assets/container.png");

    global.game = new entity::GameState();
    global.game->init();

    global.mesh = global.game->cache.get_mesh("assets/cube.obj");

    // setting up the entity
    global.entity = global.ecs->create_entity();
    entity::ECTransform entity_transform;
    entity_transform.pos = { 0, 0, -2.0f };

    global.entity.add(entity_transform);

    entity::TickEvent tick_event;
    tick_event.entity = &global.entity;

    while(!global.window->close_requested()) {
        global.input_manager.update();
        global.ecs->dispatch_event<entity::TickEvent>(&tick_event);

        global.renderer->render();
        global.window->end_frame();
    }

    return 0;
}
