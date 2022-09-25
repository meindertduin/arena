#pragma once

#include <cstdint>
#include <memory>

#include "shader.h"
#include "gpu_buffer.h"
#include "render_target.h"
#include "graphic_options.h"

#include "light.h"
#include "terrain.h"
#include "font.h"
#include "geometry.h"
#include "skybox.h"
#include "../entity/ec_transform.h"

namespace graphics {
    struct Renderer {
    public:
        Renderer();
        
        void before_render();
        void render(const Renderable *mesh, const entity::ECTransform &transform) const;
        void render_skybox();
        void after_render();

        void set_ubo_data();
        ShaderProgram shader { "shaders/light_shader.vert", "shaders/light_shader.frag" };
    private:
        std::unique_ptr<RenderTarget> render_target;
        SharedDataBuffer ubo_matrices { 0, 2 * sizeof(glm::mat4) };
        SharedDataBuffer ubo_lights { 1, 16 * 2 + (DIR_LIGHT_STD140_SIZE * MAX_DIR_LIGHTS) + (POINT_LIGHT_STD140_SIZE * MAX_POINT_LIGHTS) }; // std140 alignment size: 64 = dirlight, int = 16, 112 = pointLight
        Skybox skybox;
    };

    class TerrainRenderer {
    public:
        TerrainRenderer();
        void render(const Terrain &terrain) const;
    private:
        ShaderProgram shader { "shaders/terrain.vert", "shaders/terrain.frag" };
    };

    class TextRenderer {
    public:
        TextRenderer();
        void render(const std::string& text, const glm::vec2 &pos);
    private:
        TrueTypeFont font { "assets/alagard.ttf", 64 };
        ShaderProgram shader { "shaders/text.vert", "shaders/text.frag" };
        GpuPlane plane;
    };

    class UIRenderer {
    public:
        UIRenderer();
        void render(const Renderable &renderable);
    private:
        ShaderProgram shader { "shaders/ui.vert", "shaders/ui.frag" };
    };
}
