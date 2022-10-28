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
    class Renderer {
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
        using WidthStringPairs = std::vector<std::pair<int, std::string>>;
        static constexpr int FontRenderSize = 64;

        void render_oneliner(const std::string &text, float scale, const IRect &rect, const TextRenderOptions &options, int text_width);
        void render_multiliner(const std::string &text, float scale, const IRect &rect, const TextRenderOptions &options);
        void render_line(const std::string &line, const IPoint2D &pos, float scale);

        int calculate_text_width(const std::string &text, float scale);
        static int calculate_text_height(WidthStringPairs &sentences, const TextRenderOptions &options);

        void render_sentence(const std::string &sentence, float scale, const IPoint2D &pos, const ISize &size, const TextRenderOptions &options, int sentence_width);

        WidthStringPairs split_words(const std::string &text, float scale);
        WidthStringPairs split_in_sentences(const std::string &text, float scale, const ISize &size);

        TrueTypeFont font { "assets/alagard.ttf", FontRenderSize };
        ShaderProgram shader { "shaders/text.vert", "shaders/text.frag" };
        GpuPlane plane;
    };
}