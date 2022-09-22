#include "texture.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <filesystem>

#include "../logging.h"
#include "../global.h"

namespace graphics {
    Sprite8::Sprite8(const std::string &path) {
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data) {
            THROW_ERROR("Texture with path: %s could not be loaded correctly", path);
        }
    }

    Sprite8::~Sprite8() {
        stbi_image_free(data);
    }

    Sprite8::Sprite8(const Sprite8 &other) noexcept {
        data = std::copy(other.data, other.data + other.width * other.height, data);
        height = other.height;
        width = other.width;
        channels = other.channels;
    }

    Sprite8 &Sprite8::operator=(const Sprite8 &other) noexcept {
        *this = Sprite8(other);
        return *this;
    }

    unsigned char *Sprite8::get_buffer() const {
        return data;
    }

    Sprite16::Sprite16(const std::string &path) {
        data = stbi_load_16(path.c_str(), &width, &height, &channels, 0);

        if (!data) {
            THROW_ERROR("Texture with path: %s could not be loaded correctly", path);
        }
    }

    Sprite16::~Sprite16() {
        stbi_image_free(data);
    }

    Sprite16::Sprite16(const Sprite16 &other) noexcept {
        data = std::copy(other.data, other.data + other.width * other.height, data);
        height = other.height;
        width = other.width;
        channels = other.channels;
    }

    Sprite16 &Sprite16::operator=(const Sprite16 &other) noexcept {
        *this = Sprite16(other);
        return *this;
    }

    unsigned short *Sprite16::get_buffer() const {
        return data;
    }

    GpuTextureBase::GpuTextureBase() {
        glGenTextures(1, &id);
    }

    GpuTextureBase::~GpuTextureBase() {
        glDeleteTextures(1, &id);
    }

    void GpuTextureBase::bind(int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    Texture::Texture(const std::string &path) : GpuTextureBase() {
        Sprite16 sprite{path};
        this->width = sprite.width;
        this->height = sprite.height;

        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT, sprite.get_buffer());
        glGenerateMipmap(GL_TEXTURE_2D);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::Texture(int width, int height, unsigned char *buffer) : GpuTextureBase(), width{width}, height{height} {
        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    SkyboxTexture::SkyboxTexture(const std::string &path) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        std::vector<std::string> faces_paths;
        for (auto const &entry : std::filesystem::directory_iterator(path))
            faces_paths.push_back(entry.path());

        std::sort(faces_paths.begin(), faces_paths.end());
        for (int i = 0; i < faces_paths.size(); i++) {
            Sprite8 sprite{faces_paths[i]};
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, sprite.width, sprite.height,
                         0, GL_RGB, GL_UNSIGNED_BYTE, sprite.get_buffer());
        }
    }

}
