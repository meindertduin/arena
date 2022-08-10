#pragma once

#include <stdint.h>
#include "../entity/transform.h"

namespace graphics {
    struct Mesh {
    public:
        Mesh();
        ~Mesh();
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) = delete;

        void render();
        entity::Transform transform;
    private:
        uint32_t VAO;
        uint32_t VBO;
    };
}

