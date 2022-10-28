#pragma once

#include "component.h"
#include "../graphics/mesh.h"

namespace entity {
    class ECCollision : public Component<ECCollision> {
    public:
        void init(const std::string &filename);
        constexpr ALWAYS_INLINE std::shared_ptr<graphics::Mesh>& mesh() { return mp_mesh; }
    private:
        std::shared_ptr<graphics::Mesh> mp_mesh;
    };

    DECL_COMPONENT_HEADER(ECCollision);
}

