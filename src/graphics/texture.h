#pragma once

#include <string>
#include <vector>

namespace graphics {
    struct Sprite16 {
    public:
        int width;
        int height;
        int channels;

        Sprite16(std::string path);
        ~Sprite16();

        // TODO implement
        Sprite16(Sprite16 &other) = delete;
        Sprite16& operator=(Sprite16 &other) = delete;

        constexpr unsigned short get_pixel(int x, int y) const {
            return data[4 * (y * width + x) + 0];
        }
        
        unsigned short* get_buffer() const;
    private:
        unsigned short *data;
    };

    struct GpuTexture {
    public:
        int width;
        int height;

        GpuTexture(std::string path);

        // TODO implement
        GpuTexture(const GpuTexture &other) = delete;
        GpuTexture& operator=(const GpuTexture &other) = delete;

        ~GpuTexture();

        void bind(int slot) const;
    private:
        uint32_t id { };
    };
}
