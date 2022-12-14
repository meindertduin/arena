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
#include "../entity/ec_transform.h"
#include "model.h"

namespace game {
    class RenderWorld;
}

namespace graphics {
    class Renderer {
    public:
        Renderer() = default;

        void set_render_target(std::shared_ptr<RenderTarget> render_target);

        void before_render();
        void render(game::RenderWorld &render_world, const Model *model, const entity::ECTransform &transform) const;
        void render(game::RenderWorld &render_world, const Mesh *mesh, const entity::ECTransform &transform) const;
        void after_render();

        void set_ubo_data();

        // TODO temporary
        [[nodiscard]] constexpr std::shared_ptr<RenderTarget>& render_target() { return m_render_target; }
    private:
        std::shared_ptr<RenderTarget> m_render_target { nullptr };
        SharedDataBuffer ubo_matrices { 0, 2 * sizeof(glm::mat4) };
        SharedDataBuffer ubo_lights { 1, 16 * 2 + (DIR_LIGHT_STD140_SIZE * MAX_DIR_LIGHTS) + (POINT_LIGHT_STD140_SIZE * MAX_POINT_LIGHTS) }; // std140 alignment m_size: 64 = dirlight, int = 16, 112 = pointLight
    };

    struct TextRenderOptions {
        int text_size;
        int line_height;
        bool wrap;
        bool center_text_x;
        bool center_text_y;
    };
}