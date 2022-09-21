#pragma once

#include <glm/glm.hpp>
#include <map>

#include "texture.h"

namespace graphics {
    struct Glyph {
        GpuTexture texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        int advance;
    };

}