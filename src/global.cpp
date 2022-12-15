#include "global.h"
#include "graphics/render_target.h"
#include "graphics/renderer.h"
#include "graphics/ui_renderer.h"
#include "entity/systems_collection.h"
#include "game/game_state.h"
#include "editor/editor.h"

void Global::init(Application *app) {
    application = app;

    graphic_options = new graphics::GraphicOptions {
            true,
            { 640, 480 },
    };

    auto render_target = std::make_shared<graphics::RenderTarget>();

    renderer = new graphics::Renderer(render_target);
    text_renderer = new graphics::TextRenderer();
    ui_renderer = new graphics::UIRenderer(render_target);
    systems = new entity::SystemsCollection();

    // setting up ecs and systems
    global.ecs = entity::Ecs::instance();

    global.systems->init();

    editor = new editor::Editor();
    editor->initialize();
}