#include "renderer.h"

#include <utility>

#include "../global.h"
#include "material.h"
#include "../game/game_state.h"
#include "glad/glad.h"
#include "ui_renderer.h"


namespace graphics {
    Renderer::Renderer(std::shared_ptr<RenderTarget> render_target) : render_target{std::move( render_target )} {
        shader.link();

        shader.set_uniform_loc("baseTexture", 0);
        shader.set_uniform_loc("cubeMap", 1);
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
        global.game->skybox.bind_texture(1);

        shader.set_property("color", { 1.0f, 1.0f, 0 });
        shader.set_property("model", model_4x4);

        shader.set_property("diffuse", global.material->diffuse);
        shader.set_property("specular", global.material->specular);
        shader.set_property("shininess", global.material->shininess);

        shader.set_property("viewPos", global.game->camera->transform.pos);

        shader.set_property("invtransmodel", glm::inverse(glm::transpose(model_4x4)));

        mesh->render();
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

    void TextRenderer::render(const std::string& text, const glm::vec2 &pos, int text_size) {
        float scale = static_cast<float>(text_size) / static_cast<float>(FontRenderSize);
        auto x = pos.x;

        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->size().width(),
                                          0.0f, (float)global.graphic_options->size().height());

        shader.set_property("projection", projection);
        shader.set_property("textColor", { 1.0f, 1.0f, 1.0f });

        for (char c : text) {
            auto &glyph = font.get_glyph(c);

            float xpos = x + static_cast<float>(glyph.bearing.x) * scale;
            float ypos = pos.y - static_cast<float>(glyph.size.y - glyph.bearing.y) * scale;
            float w = static_cast<float>(glyph.size.x) * scale;
            float h = static_cast<float>(glyph.size.y) * scale;

            plane.set_pos_and_size({xpos, ypos}, {w, h});
            glyph.texture->bind(0);
            plane.render();

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += static_cast<float>(glyph.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
    }

    void TextRenderer::render(const std::string &text, const IRect &rect, const TextRenderOptions &options) {
        float scale = static_cast<float>(options.text_size) / static_cast<float>(FontRenderSize);

        auto text_width = calculate_text_width(text, scale);

        int x_pos;
        if (options.center_text_x && rect.size().width() > text_width) {
            x_pos = (rect.size().width() - text_width) / 2 + rect.position().x();
        } else {
            x_pos = rect.position().x();
        }

        auto text_height = calculate_text_height(text, scale, rect.size(), options);

        int y_pos;
        if(options.center_text_y) {
            y_pos = (rect.size().height() / 2 ) + text_height / 4 + rect.position().y();
        } else {
            y_pos = rect.position().y();
        }

        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->size().width(),
                                          0.0f, (float)global.graphic_options->size().height());

        shader.set_property("projection", projection);
        shader.set_property("textColor", { 1.0f, 1.0f, 1.0f });
        auto gl_pos = convert_to_gl_point({x_pos, y_pos});
        auto gl_x_pos = gl_pos.x();

        for (char c : text) {
            auto &glyph = font.get_glyph(c);

            float xpos = gl_x_pos + static_cast<float>(glyph.bearing.x) * scale;
            float ypos = gl_pos.y() - static_cast<float>(glyph.size.y - glyph.bearing.y) * scale;
            float w = static_cast<float>(glyph.size.x) * scale;
            float h = static_cast<float>(glyph.size.y) * scale;

            plane.set_pos_and_size({xpos, ypos}, {w, h});
            glyph.texture->bind(0);
            plane.render();

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            gl_x_pos += static_cast<float>(glyph.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
    }

    int TextRenderer::calculate_text_width(const std::string &text, float scale) {
        int text_width = 0;

        auto text_length = text.length();

        for (auto i = 0; i < text_length - 1; i++) {
            auto &glyph = font.get_glyph(text[i]);
            text_width += glyph.advance >> 6;
        }
        auto &glyph = font.get_glyph(text[text_length - 1]);
        text_width += glyph.size.x;

        return static_cast<int>(std::round((float) text_width * scale));
    }

    int TextRenderer::calculate_text_height(const std::string &text, float scale, const ISize &size, const TextRenderOptions &options) {
        int text_width = calculate_text_width(text, scale);

        if (size.width() < text_width) {
            return 0;
        }

        return options.text_size;
    }
}