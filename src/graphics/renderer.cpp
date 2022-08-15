#include "renderer.h"

#include <glad/glad.h>

#include "../global.h"

namespace graphics {
    Renderer::Renderer(uint32_t width, uint32_t height) : width(width), height(height) {
        shader.link();
        render_target = std::make_unique<RenderTarget>(width, height);
    }

    void Renderer::render() {
        render_target->bind();
        render_target->clear();

        global.camera.transform.pos = { -3, 0, 0 };

        auto transform = global.ecs.get_component<entity::Transform>(global.entity);

        shader.use();
        shader.set_property("color", { 1.0f, 1.0f, 0 });
        shader.set_property("projection", global.camera.projection);
        shader.set_property("view", global.camera.get_view_4x4());
        shader.set_property("model", transform.get_transform_4x4());

        global.mesh->render();

        render_target->unbind();
        render_target->render();
    }
}

