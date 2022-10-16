#include "rect.h"

#include "../global.h"
#include "graphic_options.h"

namespace graphics {
    IRect convert_to_gl_rect(const IRect &rect) {
        auto converted_pos = graphics::Point<int>(rect.position().x(), global.graphic_options->size().height() - rect.position().y() - rect.size().height());
        return { converted_pos, rect.size() };
    }
}