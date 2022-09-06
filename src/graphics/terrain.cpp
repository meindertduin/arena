#include "terrain.h"

#include "../global.h"

namespace graphics {
    Terrain::Terrain(std::string heightmap_path) {
        this->sprite = std::make_unique<Sprite16>(heightmap_path);
        
        MeshData mesh_data;

        for (auto y = 0; y < this->sprite->height; y++)
            for (auto x = 0; x < this->sprite->width; x++) {
                Vertex v1;
                v1.pos.x = x;
                v1.pos.y = ((float)this->sprite->get_pixel(x, y) /  65535.0f) * (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT; 
                v1.pos.z = y;
                v1.normal = { 0, 1, 0 };

                Vertex v2;
                v2.pos.x = x + 1;
                v2.pos.y = ((float)this->sprite->get_pixel(x + 1, y) /  65535.0f) * (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT; 
                v2.pos.z = y;
                v2.normal = { 0, 1, 0 };

                Vertex v3;
                v3.pos.x = x;
                v3.pos.y = ((float)this->sprite->get_pixel(x, y + 1) /  65535.0f) * (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT; 
                v3.pos.z = y + 1;
                v3.normal = { 0, 1, 0 };

                Vertex v4;
                v4.pos.x = x + 1;
                v4.pos.y = ((float)this->sprite->get_pixel(x + 1, y + 1) /  65535.0f) * (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT; 
                v4.pos.z = y + 1;
                v4.normal = { 0, 1, 0 };
                
                mesh_data.vertices.push_back(v3);
                mesh_data.vertices.push_back(v2);
                mesh_data.vertices.push_back(v1);

                mesh_data.vertices.push_back(v3);
                mesh_data.vertices.push_back(v4);
                mesh_data.vertices.push_back(v2);
            }

        this->mesh = std::make_unique<Mesh>(&mesh_data);
        this->transform.pos.y = -20;
    }

    void Terrain::render() {
        global.renderer->render(this->mesh.get(), transform);
    }
}
