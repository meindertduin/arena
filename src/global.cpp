#include "global.h"
#include "graphics/renderer.h"
#include "editor/editor.h"

void Global::init() {
    editor = new editor::Editor();
    editor->initialize();
}