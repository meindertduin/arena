#include "static_render_system.h"
#include "ec_static_mesh.h"

#include "../global.h"
#include "../graphics/renderer.h"

namespace entity {
    void StaticRenderSystem::update() {
        for (auto &entity : entities) {
            auto &ec_static_renderer = entity.get<EcStaticMeshRenderer>();
            auto &transform = entity.get<ECTransform>();

            global.renderer->render(ec_static_renderer.m_model.get(), ec_static_renderer.m_material, transform);
        }
    }
}
