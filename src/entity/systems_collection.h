#include "static_render_system.h"
#include "../physics/physics_system.h"
#include "movement_system.h"

#include <memory>

namespace entity {
    class SystemsCollection {
    public:
        void init();
        void update(float ft);
        void render();
    private:
        std::shared_ptr<StaticRenderSystem> pm_static_render_system { nullptr };
        std::shared_ptr<physics::PhysicsSystem> pm_physics_system { nullptr };
        std::shared_ptr<MovementSystem> pm_movement_system { nullptr };
    };
}