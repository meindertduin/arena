#include "global.h"
#include "graphics/renderer.h"
#include "editor/editor.h"

void Global::init() {
    text_renderer = new graphics::TextRenderer();

    editor = new editor::Editor();
    editor->initialize();
}