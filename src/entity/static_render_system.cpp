#include "static_render_system.h"
#include "ec_static_mesh.h"

#include "../global.h"
#include "../graphics/renderer.h"

namespace entity {
    void StaticRenderSystem::update(float ft) {
        for (auto &entity : entities) {
            auto &ec_static_renderer = entity.get<EcStaticMeshRenderer>();
            auto &transform = entity.get<ECTransform>();

            global.renderer->render(ec_static_renderer.mesh.get(), transform);
        }
    }
}
