#include <stdio.h>
#include "entity/move_system.h"

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
    input::initialize_input(*global.window);

    global.renderer = new graphics::Renderer();

    global.game = new entity::GameState();
    global.game->camera = new entity::Camera { window_options.width, window_options.height };

    global.mesh = new graphics::Mesh();
    global.texture = new graphics::Texture("assets/container.png");

    global.material = {
        .ambient = { 0.2f, 0.2f, 0.2f },
        .diffuse = { 0.6f, 0.6f, 0.6f },
        .specular = { 0.2f, 0.2f, 0 },
        .shininess = 0.2f,
    };

    // setting up the ecs
    global.ecs.register_component<entity::Transform>();

    auto move_system = global.ecs.register_system<entity::MoveSystem>();

    entity::Signature signature;
    signature.set(global.ecs.get_component_type<entity::Transform>());
    global.ecs.set_system_signature<entity::MoveSystem>(signature);

    // setting up the entity
    global.entity = global.ecs.create_entity();
    entity::Transform entity_transform;
    entity_transform.pos = { 0, 0, -2.0f };
    global.ecs.add_component(global.entity, entity_transform);

    while(!global.window->close_requested()) {
        move_system->update();
        global.game->camera->update();

        global.renderer->render();
        global.window->end_frame();
    }

    return 0;
}
