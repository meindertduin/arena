#include "global.h"
#include "graphics/render_target.h"
#include "graphics/renderer.h"
#include "graphics/ui_renderer.h"
#include "entity/systems_collection.h"
#include "game/game_state.h"
#include "editor/editor.h"

void Global::init() {
    auto window_options = core::WindowOptions {
            .width = 1280,
            .height = 720,
            .window_name = "Arena"
    };

    graphic_options = new graphics::GraphicOptions {
            true,
            { window_options.width, window_options.height },
    };

    // Window must be initialized first
    window = new core::Window(window_options);
    editor = new editor::Editor();
    editor->initialize();

    cache = new assets::Cache();
    global.game = new game::GameState();

    auto render_target = std::make_shared<graphics::RenderTarget>();

    renderer = new graphics::Renderer(render_target);
    text_renderer = new graphics::TextRenderer();
    ui_renderer = new graphics::UIRenderer(render_target);
    systems = new entity::SystemsCollection();

    // setting up ecs and systems
    global.ecs = entity::Ecs::instance();

    global.systems->init();

    // initialize game state
    global.game->init();
}