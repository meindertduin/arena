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
        options.text_size = 20;
        options.wrap = true;
        options.center_text_x = true;
        options.center_text_y = true;
        global.text_renderer->render("ok, multi-line works. But it still needs to be rendered in the middle on the y-axis. Now that is implemented, it still needs to render the text a little bit more correctly.", text_rect, options);
    }
}
