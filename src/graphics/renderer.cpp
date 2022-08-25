#include "renderer.h"

#include <glad/glad.h>

#include "../global.h"

namespace graphics {
    Renderer::Renderer() {
        shader.link();
        render_target = std::make_unique<RenderTarget>();
    }

    void Renderer::render() {
        render_target->bind();
        render_target->clear();

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

        ubo_lights.unbind();

        auto transform = global.ecs.get_component<entity::Transform>(global.entity);

        shader.use();
        global.texture->bind(0);
        shader.set_property("color", { 1.0f, 1.0f, 0 });
        shader.set_property("model", transform.get_transform_4x4());

        shader.set_property("diffuse", global.material.diffuse);
        shader.set_property("specular", global.material.specular);
        shader.set_property("shininess", global.material.shininess);

        global.mesh->render();

        render_target->unbind();
        render_target->render();
    }
}

