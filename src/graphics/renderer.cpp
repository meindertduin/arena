#include "renderer.h"

#include "../global.h"

namespace graphics {
    Renderer::Renderer() {
        shader.link();
        render_target = std::make_unique<RenderTarget>();
    }

    void Renderer::before_render() {
        render_target->bind();
        render_target->clear();

        set_ubo_data();
    }

    void Renderer::render(const Mesh *mesh, const entity::ECTransform &transform) const {
        auto model_4x4 = transform.get_transform_4x4();

        shader.use();
        global.texture->bind(0);
        shader.set_property("color", { 1.0f, 1.0f, 0 });
        shader.set_property("model", model_4x4);

        shader.set_property("diffuse", global.material.diffuse);
        shader.set_property("specular", global.material.specular);
        shader.set_property("shininess", global.material.shininess);

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
}

