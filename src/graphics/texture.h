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
        virtual ~GpuTextureBase();
        virtual void bind(int slot) const = 0;
    protected:
        uint32_t  id{0};
    };

    class GpuTexture : public GpuTextureBase {
    public:
        int width;
        int height;

        explicit GpuTexture(const std::string& path);
        GpuTexture(int width, int height, uint8_t *buffer);
        // GpuTexture(std::vector<std::string> faces);

        // no copy constructor or assignment, because there is no reason to put same texture on the GPU 2x
        GpuTexture(GpuTexture &&other) = delete;
        GpuTexture& operator=(GpuTexture &&other) = delete;

        void bind(int slot) const override;
    private:
        uint32_t id {0};
    };
}
