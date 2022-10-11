#include "ui.h"
#include "../global.h"
#include "../graphics/ui_renderer.h"

namespace ui {
    UI::UI() {

    }

    void UI::handle_mouse_move_event() {
        auto mouse_pos = input::get_mouse_position();
        UIMouseMoveEvent event = { .mouse_pos = mouse_pos };
        view.handle_mouse_move(event);
    }

    void UI::handle_mouse_button_event(const input::KeyCombination &combi) {
        if (combi.action == input::KEY_PRESS) {
            auto mouse_pos = input::get_mouse_position();
            UIMouseClickEvent event = { .button = combi.key, .mouse_pos = mouse_pos };
            view.handle_mouse_click(event);
        }
    }

    void UI::handle_key_event(const input::KeyCombination &combi) {
        // TODO implement
    }

    void UI::render() {
        global.ui_renderer->before_ui_rendering();
        view.render();
        global.ui_renderer->after_ui_rendering();
    }

    void UI::open_dev_info() {

    }

    void UI::open_edit_tools() {

    }

    void UI::on_tick(uint64_t tick) {
        // every 5 ticks update the ui
        if (tick % 5 == 0) {
            view.on_tick(tick);
        }
    }
}
