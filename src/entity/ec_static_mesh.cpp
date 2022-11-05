#include "ec_static_mesh.h"

#include <utility>

#include "../global.h"
#include "../game/game_state.h"

namespace entity {
    EcStaticMeshRenderer::EcStaticMeshRenderer(std::shared_ptr<graphics::Mesh> mesh) : Component<EcStaticMeshRenderer>(),
        mesh{std::move(mesh)}
    {
        // TODO: dont get material and texture from global
        this->material = global.material;
        this->texture = global.texture;
    }
}
