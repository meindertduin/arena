#include "rect.h"

#include "../global.h"
#include "graphic_options.h"

namespace graphics {
    IRect convert_to_gl_rect(const IRect &rect) {
        auto converted_pos = IPoint(rect.position().x(), global.graphic_options->size().height() - rect.position().y() - rect.size().height());
        return { converted_pos, rect.size() };
    }

    IPoint convert_to_gl_point(const IPoint &point, const ISize &size) {
        return { point.x(), static_cast<int>(global.graphic_options->size().height() - point.y() - size.height()) };
    }

    IPoint convert_to_gl_point(const IPoint &point, int height) {
        return { point.x(), static_cast<int>(global.graphic_options->size().height() - point.y() - height) };
    }

    IPoint convert_to_gl_point(const IPoint &point) {
        return { point.x(), static_cast<int>(global.graphic_options->size().height() - point.y()) };
    }
}