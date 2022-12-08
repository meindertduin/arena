#pragma once

#include <string>
#include <vector>
#include "../assets/resource.h"

namespace graphics {
    template<typename T>
    class Sprite {
    public:
        int width{0};
        int height{0};
        int channels{0};

        explicit Sprite(const std::string &path);
        ~Sprite();

        Sprite(const Sprite<T> &other) noexcept {
            data = std::copy(other.data, other.data + other.width * other.height, data);
            height = other.height;
            width = other.width;
            channels = other.channels;
        }

        Sprite<T>& operator=(const Sprite<T> &other) noexcept {
            *this = Sprite<T>(other);
            return *this;
        }

        Sprite(Sprite<T> &&other)  noexcept = default;
        Sprite<T>& operator=(Sprite<T> &&other)  noexcept = default;

        constexpr T get_pixel(int x, int y) const {
            return data[4 * (y * width + x) + 0];
        }

        T* get_buffer() { return data; }
    private:
        T* data;
    };

    using Sprite8 = Sprite<unsigned char>;
    using Sprite16 = Sprite<unsigned short>;

    class GpuTextureBase {
    public:
        GpuTextureBase();
        virtual ~GpuTextureBase();
        virtual void bind(int slot) const;
    protected:
        uint32_t  id{0};
    };

    class Texture : public GpuTextureBase, public assets::Resource {
    public:
        int width{};
        int height{};

        explicit Texture(const Path &path) : GpuTextureBase(), assets::Resource(path) {}
        Texture(int width, int height, uint8_t *buffer);

        // no copy constructor or assignment, because there is no reason to put same textures on the GPU 2x
        Texture(Texture &&other) = delete;
        Texture& operator=(Texture &&other) = delete;

    protected:
        friend class assets::Cache;

        void load(std::size_t size, char *data) override;
        void unload() override {}
    };

    class SkyboxTexture : public GpuTextureBase {
    public:
        explicit SkyboxTexture(const std::string &path);

        SkyboxTexture(SkyboxTexture &&other) = delete;
        SkyboxTexture& operator=(SkyboxTexture &&other) = delete;
    };
}
