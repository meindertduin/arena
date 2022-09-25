#include "component.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    ButtonComponent::ButtonComponent() {
        background.set_size_and_position({ 100, 30 }, { 0, 500 });
    }

    void ButtonComponent::render() {
        global.ui_renderer->render(background);
        global.text_renderer->render("Click me!", { 0, 500 });
    }
}