#include "renderer.h"

#include <glad/glad.h>

#include "../global.h"

namespace graphics {
    Renderer::Renderer(uint32_t width, uint32_t height) : width(width), height(height) {
        shader.link();

        glEnable(GL_DEPTH_TEST);
    }

    Renderer::~Renderer() {  }

    void Renderer::render() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        global.mesh->transform.pos = { 0, 0, -9.0f };
        global.camera.transform.pos = { -3, 0, 0 };
        auto model = global.mesh->transform.get_transform_4x4();

        shader.use();
        shader.set_property("color", { 0.5f, 0, 0 });
        shader.set_property("projection", global.camera.projection);
        shader.set_property("view", global.camera.get_view_4x4());
        shader.set_property("model", model);

        global.mesh->render();
    }
}

