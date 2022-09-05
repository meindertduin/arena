#pragma once

#include "../assets/cache.h"
#include "../graphics/mesh.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_static_mesh.h"

namespace game {
    struct Terrain {
        entity::EcStaticMeshRenderer static_mesh;
        entity::ECTransform transform;

        Terrain(std::string mesh_file) { 
            static_mesh.init(mesh_file);
        }

        void render();
    };

    struct Map {
    public:
        // TODO load map data from file
        Map() {
            terrain = std::make_unique<Terrain>("assets/valley.obj");
        }

        void render_background();
    private:
        std::unique_ptr<Terrain> terrain;
    };
}
