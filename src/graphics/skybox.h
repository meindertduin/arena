#pragma once

#include "gpu_buffer.h"
#include "shader.h"
#include "texture.h"

namespace graphics {
    class Skybox {
    public:
        Skybox(Texture *texture);
        void draw();
    private:
        VertexBuffer vertex_buffer {3 * sizeof(float) };
        ArrayBuffer array_buffer;
        ShaderProgram shader { "shaders/skybox.vert", "shaders/skybox.frag" };
        Texture *texture;
    };
}