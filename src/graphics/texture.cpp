#include "texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "../logging.h"

namespace graphics {
    Sprite16::Sprite16(std::string path) {
        data = stbi_load_16(path.c_str(), &width, &height, &channels, 0);

        if (!data) {
            THROW_ERROR("Texture with path: %s could not be loaded correctly", path);
        }  
    }

    Sprite16::~Sprite16() {
        stbi_image_free(data);
    }

    unsigned short* Sprite16::get_buffer() const {
        return data;
    }

    GpuTexture::GpuTexture(std::string path) {
        glGenTextures(1, &id);

        glBindTexture(GL_TEXTURE_2D, id);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Sprite16 sprite { path };
        this->width = sprite.width;
        this->height = sprite.height;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT, sprite.get_buffer());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    GpuTexture::~GpuTexture() {
        glDeleteTextures(1, &id);
    }

    void GpuTexture::bind(int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }
}















