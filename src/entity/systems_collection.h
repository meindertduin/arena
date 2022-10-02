#include "static_render_system.h"
#include "../physics/physics_system.h"
#include "terrain_collision_system.h"
#include "movement_system.h"

#include <memory>

namespace entity {
    class SystemsCollection {
    public:
        std::shared_ptr<StaticRenderSystem> static_render_system { nullptr };
        std::shared_ptr<physics::PhysicsSystem> physics_system { nullptr };
        std::shared_ptr<TerrainCollisionSystem> terrain_collision_system { nullptr };
        std::shared_ptr<MovementSystem> movement_system { nullptr };

        void init();
        void update();
        void render();
    };
}