#include "ec_static_mesh_renderer.h"

#include "../global.h"

namespace entity {
    DECL_COMPONENT_INIT(EcStaticMeshRenderer) {}

    EcStaticMeshRenderer::EcStaticMeshRenderer() {
        this->mesh = global.game->cache.get_mesh("assets/cube.obj");
        this->material = &global.material;
        this->texture = global.texture;
    }
}
