#include "frame.h"

#include <utility>

#include "../global.h"
#include "../graphics/ui_renderer.h"
#include "../graphics/renderer.h"

namespace ui {
    Frame::Frame(std::string text) : text{std::move(text)} {
        auto rect = IRect({ 0, 0 }, { 200, 200 });
        set_rect(rect);
        set_color({ 255, 0, 0 , 255 });
    }

    void Frame::render() {
        global.ui_renderer->draw_rect(rect(), color());
        auto text_rect = IRect({0, 0}, {200, 200});
        graphics::TextRenderOptions options{};
        options.text_size = 20;
        options.wrap = true;
        options.center_text_x = true;
        options.center_text_y = true;
        global.text_renderer->render("Ok, multi-line sentences do kind of work now and its amazing!", text_rect, options);
    }
}
