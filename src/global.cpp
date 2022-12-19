#include "global.h"
#include "graphics/render_target.h"
#include "graphics/renderer.h"
#include "entity/systems_collection.h"
#include "editor/editor.h"

void Global::init() {
    auto render_target = std::make_shared<graphics::RenderTarget>();

    renderer = new graphics::Renderer(render_target);
    text_renderer = new graphics::TextRenderer();

    editor = new editor::Editor();
    editor->initialize();
}