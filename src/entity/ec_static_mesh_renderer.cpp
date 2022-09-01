#include "ec_static_mesh_renderer.h"

#include "../global.h"

namespace entity {
    EcStaticMeshRenderer::EcStaticMeshRenderer() {
        this->mesh = global.game->cache.get_mesh("assets/cube.obj");
        this->material = &global.material;
        this->texture = global.texture;
    }

    void EcStaticMeshRenderer::render() {

    }
}
