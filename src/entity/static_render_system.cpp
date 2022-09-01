#include "static_render_system.h"
#include "ec_static_mesh_renderer.h"
#include "../global.h"

namespace entity {
    void StaticRenderSystem::update() {
        for (auto &entity : entities) {
            auto &ec_static_renderer = entity.get<EcStaticMeshRenderer>();
            auto &transform = entity.get<ECTransform>();

            global.renderer->render(ec_static_renderer.mesh, transform);
        }
    }
}
