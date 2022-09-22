#pragma once

#include <string>
#include <vector>

namespace graphics {
    class Sprite16 {
    public:
        int width{};
        int height{};
        int channels{};

        Sprite16(const std::string& path);
        ~Sprite16();

        Sprite16(const Sprite16 &other) noexcept;
        Sprite16& operator=(const Sprite16 &other) noexcept;

        Sprite16(Sprite16 &&other) = default;
        Sprite16& operator=(Sprite16 &&other) = default;

        [[nodiscard]] constexpr unsigned short get_pixel(int x, int y) const {
            return data[4 * (y * width + x) + 0];
        }
        
        [[nodiscard]] unsigned short* get_buffer() const;
    private:
        unsigned short *data;
    };

    class GpuTextureBase {
    public:
        GpuTextureBase();
        virtual ~GpuTextureBase();
        virtual void bind(int slot) const;
    protected:
        uint32_t  id{0};
    };

    class Texture : public GpuTextureBase {
    public:
        int width;
        int height;

        explicit Texture(const std::string& path);
        Texture(int width, int height, uint8_t *buffer);

        // no copy constructor or assignment, because there is no reason to put same texture on the GPU 2x
        Texture(Texture &&other) = delete;
        Texture& operator=(Texture &&other) = delete;
    };

    class SkyboxTexture : public GpuTextureBase {
    public:
        explicit SkyboxTexture(const std::string &path);

        SkyboxTexture(SkyboxTexture &&other) = delete;
        SkyboxTexture& operator=(SkyboxTexture &&other) = delete;
    };
}
