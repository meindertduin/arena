#include "component.h"

namespace ui {
    void Component::mouse_event(UIMouseMoveEvent &events) { }
    void Component::mouse_event(UIMouseClickEvent &events) { }

    void ui::Component::on_tick(uint64_t tick) { }
    void Component::render() { }
}
