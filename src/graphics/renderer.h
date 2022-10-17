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
        explicit Renderer(std::shared_ptr<RenderTarget> render_target);
        
        void before_render();
        void render(const Renderable *mesh, const entity::ECTransform &transform) const;
        void after_render();

        void set_ubo_data();
        ShaderProgram shader { "shaders/light_shader.vert", "shaders/light_shader.frag" };
    private:
        std::shared_ptr<RenderTarget> render_target;
        SharedDataBuffer ubo_matrices { 0, 2 * sizeof(glm::mat4) };
        SharedDataBuffer ubo_lights { 1, 16 * 2 + (DIR_LIGHT_STD140_SIZE * MAX_DIR_LIGHTS) + (POINT_LIGHT_STD140_SIZE * MAX_POINT_LIGHTS) }; // std140 alignment size: 64 = dirlight, int = 16, 112 = pointLight
    };

    class TerrainRenderer {
    public:
        TerrainRenderer();
        void render(const Terrain &terrain) const;
    private:
        ShaderProgram shader { "shaders/terrain.vert", "shaders/terrain.frag" };
    };

    struct TextRenderOptions {
        int text_size;
        int line_height;
        bool wrap;
        bool center_text_x;
        bool center_text_y;
    };

    class TextRenderer {
    public:
        TextRenderer();
        void render(const std::string &text, const IRect &rect, const TextRenderOptions &options);
    private:
        static constexpr int FontRenderSize = 64;

        int calculate_text_width(const std::string &text, float scale);
        int calculate_text_height(const std::string &text, float scale, const ISize &size, const TextRenderOptions &options);
        int calculate_multi_line_text_height(const std::string &text, float scale, const ISize &size, const TextRenderOptions &options);

        std::vector<std::pair<int, std::string>> split_words(const std::string &text, float scale);

        TrueTypeFont font { "assets/alagard.ttf", FontRenderSize };
        ShaderProgram shader { "shaders/text.vert", "shaders/text.frag" };
        GpuPlane plane;
    };
}