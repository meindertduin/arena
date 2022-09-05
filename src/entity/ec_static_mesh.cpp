#include "ec_static_mesh.h"

#include "../global.h"

namespace entity {
    DECL_COMPONENT_INIT(EcStaticMeshRenderer) {}

    void EcStaticMeshRenderer::init(std::string filename) {
        this->mesh = { filename };
        this->material = &global.material;
        this->texture = global.texture;
    }
}
