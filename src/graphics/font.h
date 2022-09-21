#pragma once

#include <glm/glm.hpp>
#include <map>

#include "texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace graphics {
    void font_init();
    void font_quit();

    struct Glyph {
        // GpuTexture texture;
        uint32_t texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        int advance;
    };

    class TrueTypeFont {
    public:
        TrueTypeFont(const std::string &path, int size);
        ~TrueTypeFont();

        TrueTypeFont(const TrueTypeFont &other) = delete;
        TrueTypeFont& operator=(const TrueTypeFont &other) = delete;

        [[nodiscard]] Glyph& get_glyph(unsigned char c) const;
    private:
        FT_Face face = nullptr;
        std::map<unsigned char, Glyph> glyphs;
    };
}