#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"

namespace entity {
    struct EcStaticMeshRenderer {
    public:
        EcStaticMeshRenderer();
        void render();
    private:
        graphics::Mesh *mesh;
        graphics::Material *material;
        graphics::Texture *texture;
    };
}
