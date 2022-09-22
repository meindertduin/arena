#include "font.h"

#include "../logging.h"

#include <glad/glad.h>

namespace graphics {
    constexpr int MaxCharacters = 128;

    inline FT_Library library;

    void font_init() {
        if (FT_Init_FreeType(&library)) {
            THROW_ERROR("font_init: Failed to initialize FreeType font.");
        }
    }

    void font_quit() {
        FT_Done_FreeType(library);
    }

    TrueTypeFont::TrueTypeFont(const std::string &path, int size) {
        FT_New_Face(library, path.c_str(), 0, &face);
        FT_Set_Pixel_Sizes(face, 0, size);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for(unsigned char c = 0; c < MaxCharacters; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                THROW_ERROR("TrueTypeFont::TrueTypeFont: could not load glyph %s", std::to_string(c));
            }

            Glyph glyph = {
                new GpuTexture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer),
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<int>(face->glyph->advance.x)
            };

            glyphs.insert(std::pair<unsigned char, Glyph>(c, glyph));
        }
    }

    TrueTypeFont::~TrueTypeFont() {
        FT_Done_Face(face);
        for (auto &[c, glyph] : glyphs)
            delete glyph.texture;
    }

    Glyph& TrueTypeFont::get_glyph(unsigned char c) {
        return this->glyphs[c];
    }
}