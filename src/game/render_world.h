#pragma once

#include <memory>
#include <vector>

#include "world.h"
#include "../platform/platform.h"

namespace entity {
    class Camera;
}

namespace graphics {
    class DirLight;
    class PointLight;
    class Skybox;
    class Renderer;
}

namespace game {
    class Map;
    class Scene;

    class RenderWorld : public IWorld {
    public:
        static std::unique_ptr<RenderWorld> create(Scene &scene, graphics::Renderer &renderer);

        virtual entity::Camera& camera() = 0;
        virtual std::vector<graphics::DirLight>& dir_lights() = 0;
        virtual std::vector<graphics::PointLight>& point_lights() = 0;
        virtual std::unique_ptr<Map>& map() = 0;
        virtual graphics::Skybox& skybox() = 0;
    };
}
