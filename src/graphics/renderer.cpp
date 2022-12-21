#include "renderer.h"

#include <utility>

#include "material.h"
#include "../game/scene.h"

namespace graphics {
    void Renderer::set_render_target(std::shared_ptr<RenderTarget> render_target) {
        m_render_target = std::move(render_target);
    }

    void Renderer::before_render() {
        m_render_target->bind();
        m_render_target->clear();

        set_ubo_data();
    }

    void Renderer::render(game::RenderWorld &render_world, const Model *model, const entity::ECTransform &transform) const {
        auto model_4x4 = transform.get_transform_4x4();

        for (const auto &mesh : model->meshes()) {
            auto &material = *mesh.material();
            auto &program = material.shader()->program();

            program.use();

            auto i = 0;
            for (auto &texture : material.textures()) {
                texture->bind(i++);
            }

            render_world.skybox().bind_texture(1);

            material.update();
            program.set_property("color", { 1.0f, 1.0f, 0 });
            program.set_property("model", model_4x4);
            program.set_property("viewPos", render_world.camera().transform.pos);
            program.set_property("invtransmodel", glm::inverse(glm::transpose(model_4x4)));

            mesh.render();
        }
    }

    void Renderer::after_render() {
        m_render_target->unbind();
        m_render_target->render();
    }

    void Renderer::set_ubo_data() {
        auto &render_world = *global.application->engine()->active_scene()->render_world();
        ubo_matrices.reset();
        ubo_lights.reset();

        ubo_matrices.bind();
        ubo_matrices.set_data(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(render_world.camera().projection));
        ubo_matrices.set_data(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(render_world.camera().get_view_4x4()));
        ubo_matrices.unbind();

        ubo_lights.bind();

        auto dir_lights_count = render_world.dir_lights().size();
        auto point_lights_count = render_world.point_lights().size();

        ubo_lights.set_data(16, sizeof(int), &dir_lights_count);
        auto uboFilledSizeBefore = ubo_lights.offset();
        for (auto &light : render_world.dir_lights()) {
            light.set_data(ubo_lights);
        }

        ubo_lights.set_offset(uboFilledSizeBefore + (DIR_LIGHT_STD140_SIZE * MAX_DIR_LIGHTS));
        ubo_lights.set_data(16, sizeof(int), &point_lights_count);

        for (auto &light : render_world.point_lights()) {
            light.set_data(ubo_lights);
        }

        ubo_lights.unbind();
    }

    void Renderer::render(game::RenderWorld &render_world, const Mesh *mesh, const entity::ECTransform &transform) const {
        auto &material = *mesh->material();
        auto &program = material.shader()->program();
        auto model_4x4 = transform.get_transform_4x4();

        program.use();

        int texture_index = 0;
        for (const auto &texture : material.textures()) {
            texture->bind(texture_index++);
        }

        program.set_property("model", model_4x4);
        program.set_property("invtransmodel", glm::inverse(glm::transpose(model_4x4)));
        program.set_property("viewPos", render_world.camera().transform.pos);
        material.update();

        mesh->render();
    }
}