#include "static_render_system.h"
#include "ec_static_model.h"

#include "../global.h"
#include "../graphics/renderer.h"

namespace entity {
    void StaticRenderSystem::update() {
        for (auto &entity : entities) {
            auto &ec_static_renderer = entity.get<ECStaticModel>();
            auto &transform = entity.get<ECTransform>();

            global.renderer->render(ec_static_renderer.model().get(), transform);
        }
    }
}
