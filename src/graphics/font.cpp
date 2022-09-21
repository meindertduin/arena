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

        for(unsigned char c = 0; c < MaxCharacters; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                THROW_ERROR("TrueTypeFont::TrueTypeFont: could not load character %s", std::to_string(c));
            }

            uint32_t texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Glyph character = {
                std::make_shared<GpuTexture>(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer),
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<int>(face->glyph->advance.x)
            };

            glyphs.insert(std::pair<char, Glyph>(c, character));
        }
    }

    TrueTypeFont::~TrueTypeFont() {
        FT_Done_Face(face);
    }

    Glyph& TrueTypeFont::get_glyph(unsigned char c) {
        return this->glyphs[c];
    }
}