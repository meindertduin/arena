#include "component.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    ButtonComponent::ButtonComponent() {
        background.set_size_and_position({ 100, 30 }, { 10, 10 });
    }

    void ButtonComponent::render() {
        // background.render();
        global.text_renderer->render("Click me!", { 100, 100 });
    }
}
