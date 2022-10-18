#include "frame.h"

#include <utility>

#include "../global.h"
#include "../graphics/ui_renderer.h"
#include "../graphics/renderer.h"

namespace ui {
    Frame::Frame(std::string text) : text{std::move(text)} {
        auto rect = IRect({ 0, 0 }, { 400, 200 });
        set_rect(rect);
        set_color({ 255, 0, 0 , 255 });
    }

    void Frame::render() {
        global.ui_renderer->draw_rect(rect(), color());
        auto text_rect = IRect({0, 0}, {400, 200});
        graphics::TextRenderOptions options{};
        options.text_size = 40;
        options.wrap = true;
        options.center_text_x = false;
        options.center_text_y = false;
        global.text_renderer->render("ok, multi-line works nicely but needs some tweaks", text_rect, options);
    }
}
