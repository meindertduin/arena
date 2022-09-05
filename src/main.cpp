#include <stdio.h>

#include "global.h"
#include "input/input.h"
#include "entity/static_render_system.h"
#include "entity/ec_static_mesh.h"

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

    auto static_render_system = global.ecs->register_system<entity::StaticRenderSystem>();
    static_render_system = global.ecs->register_system<entity::StaticRenderSystem>();
    entity::Signature signature;
    signature.set(global.ecs->get_component_type<entity::EcStaticMeshRenderer>());
    global.ecs->set_system_signature<entity::StaticRenderSystem>(signature);

    global.material = {
        .ambient = { 0.2f, 0.2f, 0.2f },
        .diffuse = { 0.6f, 0.6f, 0.6f },
        .specular = { 0.2f, 0.2f, 0 },
        .shininess = 0.2f,
    };
    global.texture = new graphics::Texture("assets/container.png");

    global.game = new entity::GameState();
    global.game->init();

    while(!global.window->close_requested()) {
        global.input_manager.update();
        
        global.renderer->before_render();
        
        // render the different systems
        static_render_system->update();

        global.renderer->after_render();
        global.window->end_frame();
    }

    return 0;
}
