#pragma once

#include "gpu_buffer.h"
#include "shader.h"
#include "texture.h"

namespace graphics {
    class Skybox {
    public:
        Skybox(GpuTexture *texture, ShaderProgram *shader);
        void draw();
    private:
        VertexBuffer vertex_buffer {3 * sizeof(float) };
        ArrayBuffer array_buffer;
        ShaderProgram *shader;
        GpuTexture *texture;
    };
}