#include "renderer.h"

#include <utility>

#include "../global.h"
#include "material.h"
#include "../game/game_state.h"
#include "glad/glad.h"

namespace graphics {
    Renderer::Renderer(std::shared_ptr<RenderTarget> render_target) : render_target{std::move( render_target )} {
        shader.link();
    }

    void Renderer::before_render() {
        render_target->bind();
        render_target->clear();

        set_ubo_data();
    }

    void Renderer::render(const Renderable *mesh, const entity::ECTransform &transform) const {
        auto model_4x4 = transform.get_transform_4x4();

        shader.use();
        global.texture->bind(0);
        shader.set_property("color", { 1.0f, 1.0f, 0 });
        shader.set_property("model", model_4x4);

        shader.set_property("diffuse", global.material->diffuse);
        shader.set_property("specular", global.material->specular);
        shader.set_property("shininess", global.material->shininess);

        shader.set_property("viewPos", global.game->camera->transform.pos);

        shader.set_property("invtransmodel", glm::inverse(glm::transpose(model_4x4)));

        mesh->render();
    }

    void Renderer::render_skybox() {
        skybox.render();
    }


    void Renderer::after_render() {
        render_target->unbind();
        render_target->render();
    }

    void Renderer::set_ubo_data() {
        ubo_matrices.reset();
        ubo_lights.reset();

        ubo_matrices.bind();
        ubo_matrices.set_data(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(global.game->camera->projection));
        ubo_matrices.set_data(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(global.game->camera->get_view_4x4()));
        ubo_matrices.unbind();

        ubo_lights.bind();

        auto dir_lights_count = global.game->dir_lights.size();
        auto point_lights_count = global.game->point_lights.size();

        ubo_lights.set_data(16, sizeof(int), &dir_lights_count);
        
        auto uboFilledSizeBefore = ubo_lights.offset;
        for (auto &light : global.game->dir_lights) {
            light.set_data(ubo_lights);
        }

        ubo_lights.set_offset(uboFilledSizeBefore + (DIR_LIGHT_STD140_SIZE * MAX_DIR_LIGHTS));
        ubo_lights.set_data(16, sizeof(int), &point_lights_count);

        for (auto &light : global.game->point_lights) {
            light.set_data(ubo_lights);
        }

        ubo_lights.unbind();
    }

    TerrainRenderer::TerrainRenderer() {
        shader.link();
        shader.use();

        shader.set_uniform_loc("baseTexture", 0);
        shader.set_uniform_loc("blendMap", 1);
        shader.set_uniform_loc("rTexture", 2);
        shader.set_uniform_loc("gTexture", 3);
        shader.set_uniform_loc("bTexture", 4);
    }

    void TerrainRenderer::render(const Terrain &terrain) const {
        auto model_4x4 = terrain.transform.get_transform_4x4();

        shader.use();

        terrain.textures.bind();
        shader.set_property("model", model_4x4);

        shader.set_property("diffuse", global.material->diffuse);
        shader.set_property("specular", global.material->specular);
        shader.set_property("shininess", global.material->shininess);

        shader.set_property("viewPos", global.game->camera->transform.pos);

        shader.set_property("invtransmodel", glm::inverse(glm::transpose(model_4x4)));

        terrain.mesh->render();
    }

    TextRenderer::TextRenderer() {
        shader.link();
    }

    void TextRenderer::render(const std::string& text, const glm::vec2 &pos) {
        float scale = 0.40f;
        auto x = pos.x;

        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->screen_dimensions.x,
                                          0.0f, (float)global.graphic_options->screen_dimensions.y);

        shader.set_property("projection", projection);
        shader.set_property("textColor", { 1.0f, 1.0f, 1.0f });

        for (char c : text) {
            auto &glyph = font.get_glyph(c);

            float xpos = x + static_cast<float>(glyph.bearing.x) * scale;
            float ypos = pos.y - static_cast<float>(glyph.size.y - glyph.bearing.y) * scale;
            float w = static_cast<float>(glyph.size.x) * scale;
            float h = static_cast<float>(glyph.size.y) * scale;

            plane.set_size_and_position({w, h}, {xpos, ypos });
            glyph.texture->bind(0);
            plane.render();

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += static_cast<float>(glyph.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
    }

    UIRenderer::UIRenderer(std::shared_ptr<RenderTarget> render_target) : render_target{std::move( render_target )} {
        shader.link();
    }

    void UIRenderer::render(const Renderable &renderable) {
        glDisable(GL_DEPTH_TEST);
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->screen_dimensions.x,
                                          0.0f, (float)global.graphic_options->screen_dimensions.y);

        shader.set_property("projection", projection);
        shader.set_property("color", { 1.0f, 0.0f, 0.0f, 0.5f });
        renderable.render();
    }

    void UIRenderer::before_ui_rendering() {
        render_target->disable_depth_test();
    }

    void UIRenderer::after_ui_rendering() {
        render_target->enable_depth_test();
    }
}