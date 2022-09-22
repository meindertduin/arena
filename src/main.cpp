#include "global.h"

#include "core/window.h"
#include "core/program_time.h"
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

    Logger::debug("Starting application");

    graphics::font_init();

    global.window = new core::Window(window_options);
    global.renderer = new graphics::Renderer();
    global.terrain_renderer = new graphics::TerrainRenderer();
    global.text_renderer = new graphics::TextRenderer();

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
    global.texture = global.game->cache.get_resource<graphics::Texture>("assets/container.png");

    int frame_time_ms;
    core::Timer program_timer;
    while(!global.window->close_requested()) {
        program_timer.start();

        global.input_manager.update();
        physics_system->update();

        terrain_collision_system->update();

        global.renderer->before_render();
        global.game->map->render_background();
        // render the different systems
        static_render_system->update();
        global.text_renderer->render(std::to_string(frame_time_ms) + " ms", { 10, global.graphic_options->screen_dimensions.y - 150});

        global.renderer->after_render();
        global.window->end_frame();

        program_timer.stop();
        auto difference_ms = program_timer.difference_ms();
        int delay_time_ms = static_cast<int>(1000.0f / 60.0f) - difference_ms;
        frame_time_ms = difference_ms;
        if (delay_time_ms > 0)
            core::delay(delay_time_ms);
    }

    graphics::font_quit();

    return 0;
}
