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

        ubo_matrices.bind();
        ubo_matrices.set_data(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(global.game->camera->projection));
        ubo_matrices.set_data(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(global.game->camera->get_view_4x4()));
        ubo_matrices.unbind();

        auto transform = global.ecs.get_component<entity::Transform>(global.entity);

        shader.use();
        global.texture->bind(0);
        shader.set_property("color", { 1.0f, 1.0f, 0 });
        shader.set_property("model", transform.get_transform_4x4());

        global.mesh->render();

        render_target->unbind();
        render_target->render();
    }
}

