#pragma once

#include "texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <map>
#include <memory>

namespace graphics {
    void font_init();
    void font_quit();

    struct Glyph {
        std::shared_ptr<GpuTexture> texture;
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

        Glyph& get_glyph(unsigned char c);
    private:
        FT_Face face = nullptr;
        std::map<unsigned char, Glyph> glyphs;
    };
}