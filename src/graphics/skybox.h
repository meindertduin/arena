#pragma once

#include "gpu_buffer.h"
#include "shader.h"
#include "texture.h"

namespace graphics {
    class Skybox {
    public:
        Skybox();
        void render();
        void bind_texture(int index) const;
    private:
        VertexBuffer vertex_buffer {3 * sizeof(float) };
        ArrayBuffer array_buffer;
        std::shared_ptr<ShaderProgram> m_shader;
        SkyboxTexture texture { "assets/skybox" };
    };
}