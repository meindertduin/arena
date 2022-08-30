#pragma once

#include <string>
#include <vector>

namespace graphics {
    struct Texture {
    public:
        int width;
        int height;

        Texture(std::string path);
        Texture(std::vector<std::string> faces);
        ~Texture();

        void bind(int slot) const;
    private:
        uint32_t id;
    };
}
