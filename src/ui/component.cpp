#include "component.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    ButtonComponent::ButtonComponent() {
        background.set_size_and_position({ 100, 30 }, { 100, 100 });
    }

    void ButtonComponent::render() {
        global.ui_renderer->render(background);
        global.text_renderer->render("Click me!", { 100, 100 });
    }
}