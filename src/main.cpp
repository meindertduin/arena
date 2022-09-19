#include "global.h"

#include "core/window.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "input/input.h"

#include "entity/static_render_system.h"
#include "entity/terrain_collision_system.h"

#include "entity/ec_static_mesh.h"
#include "entity/ec_collision_box.h"
#include "entity/ec_physics.h"
#include "game/game_state.h"

#include "physics/physics_system.h"

Global global;

int main () {
    // setting up application core components
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
    global.terrain_renderer = new graphics::TerrainRenderer();

    input::initialize_input(*global.window);

    // setting up ecs and systems
    global.ecs = entity::Ecs::instance();

    auto static_render_system = global.ecs->create_system<entity::StaticRenderSystem>({ entity::EcStaticMeshRenderer::_id });
    auto physics_system = global.ecs->create_system<physics::PhysicsSystem>({ entity::ECPhysics::_id });
    auto terrain_collision_system = global.ecs->create_system<entity::TerrainCollisionSystem>({ entity::ECCollisionBox::_id });

    // initialize game state
    global.game = new game::GameState();
    global.game->init();

    global.material = new graphics::Material({ 0.2f, 0.2f, 0.2f }, { 0.6f, 0.6f, 0.6f }, { 0.2f, 0.2f, 0 }, 0.2f);
    global.texture = global.game->cache.get_resource<graphics::GpuTexture>("assets/container.png");

    while(!global.window->close_requested()) {
        global.input_manager.update();
        physics_system->update();

        terrain_collision_system->update();
        
        global.renderer->before_render();
        global.game->map->render_background();
        // render the different systems
        static_render_system->update();

        global.renderer->after_render();
        global.window->end_frame();
    }

    return 0;
}
