#include "renderer.h"

#include <glad/glad.h>

#include "../global.h"

namespace graphics {
    Renderer::Renderer(uint32_t width, uint32_t height) : width(width), height(height) {
        shader.link();

        screen_vertex_buffer.add_vertex_attribute({ 2, GL_FLOAT, sizeof(float), false });
        screen_vertex_buffer.add_vertex_attribute({ 2, GL_FLOAT, sizeof(float), false });

        glEnable(GL_DEPTH_TEST);
    }

    Renderer::~Renderer() {  }

    void Renderer::render() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // global.camera.transform.pos = { -3, 0, 0 };

        // auto transform = global.ecs.get_component<entity::Transform>(global.entity);

        // shader.use();
        // shader.set_property("color", { 0.5f, 0, 0 });
        // shader.set_property("projection", global.camera.projection);
        // shader.set_property("view", global.camera.get_view_4x4());
        // shader.set_property("model", transform.get_transform_4x4());

        // global.mesh->render();

        screen_shader.use();
        float quad_vertices[] = {
             -1.0f,  1.0f, 0.0f, 1.0f,
             -1.0f, -1.0f, 0.0f, 0.0f,
              1.0f, -1.0f, 1.0f, 0.0f,
             -1.0f,  1.0f, 0.0f, 1.0f,
              1.0f, -1.0f, 1.0f, 0.0f,
              1.0f,  1.0f, 1.0f, 1.0f
         };

        screen_array_buffer.set_data(0, sizeof(quad_vertices), &quad_vertices);
        screen_vertex_buffer.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

