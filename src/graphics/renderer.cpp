#include "renderer.h"

#include <utility>

#include "material.h"
#include "../game/game_state.h"
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

    void TextRenderer::render(const std::string &text, const IRect &rect, const TextRenderOptions &options) {
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->size().width(),
                                          0.0f, (float)global.graphic_options->size().height());

        shader.set_property("projection", projection);
        shader.set_property("textColor", { 1.0f, 1.0f, 1.0f });

        float scale = static_cast<float>(options.text_size) / static_cast<float>(FontRenderSize);
        auto text_width = calculate_text_width(text, scale);

        // text is on one line if text width is smaller than the size or text isn't wrapped
        if (rect.size().width() >= text_width || !options.wrap) {
            render_oneliner(text, scale, rect, options, text_width);
        } else {
            render_multiliner(text, scale, rect, options);
        }
    }

    void TextRenderer::render_oneliner(const std::string &text, float scale, const IRect &rect, const TextRenderOptions &options, int text_width) {
        int x_pos;
        if (options.center_text_x && rect.size().width() > text_width) {
            x_pos = (rect.size().width() - text_width) / 2 + rect.position().x();
        } else {
            x_pos = rect.position().x();
        }

        int y_pos;
        if(options.center_text_y) {
            y_pos = (rect.size().height() / 2 ) + options.text_size / 4 + rect.position().y();
        } else {
            y_pos = rect.position().y();
        }

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

    void TextRenderer::render_multiliner(const std::string &text, float scale, const IRect &rect, const TextRenderOptions &options) {
        auto sentences = split_in_sentences(text, scale, rect.size());

        auto y_pos = rect.position().y();
        for (auto &[sentence_width, sentence] : sentences) {
            IPoint pos = { rect.position().x(), y_pos };
            render_sentence(sentence, scale, pos, rect.size(), options, sentence_width);
            y_pos += options.text_size + options.line_height;
        }
    }


    void TextRenderer::render_sentence(const std::string &sentence, float scale, const IPoint &pos, const ISize &size, const TextRenderOptions &options, int sentence_width) {
        int x_pos;
        if (options.center_text_x && size.width() > sentence_width) {
            x_pos = (size.width() - sentence_width) / 2 + pos.x();
        } else {
            x_pos = pos.x();
        }

        auto gl_pos = convert_to_gl_point({ x_pos, pos.y() });
        auto gl_x_pos = gl_pos.x();

        for (char c : sentence) {
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

    std::vector<std::pair<int, std::string>> TextRenderer::split_in_sentences(const std::string &text, float scale, const ISize &size) {
        int SpaceWidth = static_cast<float>(font.get_glyph(' ').advance >> 6) * scale;

        auto words = split_words(text, scale);
        std::vector<std::pair<int, std::string>> sentences;

        int sentence_width = 0;
        std::string sentence;
        for (auto &[word_width, word] : words) {
            // TODO handle edge case if word is too small to fit in size
            if (sentence_width + word_width + SpaceWidth > size.width()) {
                sentences.emplace_back(sentence_width, std::string{sentence});
                sentence = word;
                sentence_width = word_width;
                continue;
            }

            sentence += " ";
            sentence_width += SpaceWidth;

            sentence += word;
            sentence_width += word_width;
        }
        std::string current_sentence;

        sentences.emplace_back(sentence_width, sentence);

        return sentences;
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

    std::vector<std::pair<int, std::string>> TextRenderer::split_words(const std::string &text, float scale) {
        std::vector<std::pair<int, std::string>> words;
        std::string current_word;

        for (char c : text) {
            if (c == ' ') {
                auto word_width = calculate_text_width(current_word, scale);
                words.emplace_back(word_width, std::string{current_word});
                current_word = "";
                continue;
            }

            current_word += c;
        }

        int word_width = calculate_text_width(current_word, scale);
        words.emplace_back(word_width, current_word);

        return words;
    }
}