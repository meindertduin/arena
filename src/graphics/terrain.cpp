#include "terrain.h"

#include "../global.h"
#include "../physics/parametrics.h"

namespace graphics {
    Terrain::Terrain(std::string heightmap_path) {
        this->sprite = std::make_unique<Sprite16>(heightmap_path);
        
        MeshData mesh_data;
        
        int touch_vertices[this->sprite->width][this->sprite->height];
        for (int i = 0; i < this->sprite->height; i++) {
            for (int j = 0; j < this->sprite->width; j++) {
                touch_vertices[j][i] = 0;
            }
        }
        Vertex vertices[this->sprite->width][this->sprite->height];
    
        // setting all the vertices
        for (auto y = 0; y < this->sprite->height; y++) {
            for (auto x = 0; x < this->sprite->width; x++) {
                Vertex v;
                v.pos.x = x;
                v.pos.y = ((float)this->sprite->get_pixel(x, y) /  65535.0f) * (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT; 
                v.pos.z = y;
                v.normal = { 0, 0, 0 };
                v.textcoords = { 0, 0 };

                vertices[x][y] = v;
            }
        }

        // dividing heightmap into grid and triangles and calculating normals of vertices
        for (auto y = 0; y < this->sprite->height - 1; y++) {
            for (auto x = 0; x < this->sprite->width - 1; x++) {
                auto &v1 = vertices[x][y];
                auto &v2 = vertices[x + 1][y];
                auto &v3 = vertices[x][y + 1];
                auto &v4 = vertices[x + 1][y + 1];

                auto line1 = v3.pos - v2.pos;
                auto line2 = v3.pos - v1.pos;
                auto normal = glm::cross(line1, line2);

                v1.normal += normal;
                v2.normal += normal;
                v3.normal += normal;

                touch_vertices[x][y]++;
                touch_vertices[x + 1][y]++;
                touch_vertices[x][y + 1]++;

                line1 = v3.pos - v4.pos;
                line2 = v3.pos - v2.pos;
                normal = glm::cross(line1, line2);

                v2.normal += normal;
                v3.normal += normal;
                v4.normal += normal;

                touch_vertices[x + 1][y]++;
                touch_vertices[x][y + 1]++;
                touch_vertices[x + 1][y + 1]++;
            }
        }

        // normalizing vector normals
        for (auto y = 0; y < this->sprite->height; y++) {
            for (auto x = 0; x < this->sprite->width; x++) {
                if (touch_vertices[x][y] >= 0) {
                    auto &v1 = vertices[x][y];
                    v1.normal /= touch_vertices[x][y];
                    v1.normal = glm::normalize(v1.normal);
                }
            }
        }

        // deviding vertices into polygons and adding to the mesh_data
        for (auto y = 0; y < this->sprite->height - 1; y++) {
            for (auto x = 0; x < this->sprite->width - 1; x++) {
                auto &v1 = vertices[x][y];
                auto &v2 = vertices[x + 1][y];
                auto &v3 = vertices[x][y + 1];
                auto &v4 = vertices[x + 1][y + 1];

                mesh_data.vertices.push_back(v3);
                mesh_data.vertices.push_back(v2);
                mesh_data.vertices.push_back(v1);

                mesh_data.vertices.push_back(v3);
                mesh_data.vertices.push_back(v4);
                mesh_data.vertices.push_back(v2);
            }
        }
        
        this->mesh = std::make_unique<Mesh>(&mesh_data);
        this->transform.pos.y = -20;
        this->transform.pos.x = -200;
        this->transform.pos.z = -200;
    }

    void Terrain::render() {
        global.renderer->render(this->mesh.get(), transform);
    }

    float Terrain::get_height(float x, float z) const {
        auto xmin = (int) x;
        auto ymin = (int) z;

        auto v1 = map_points[xmin][ymin];
        auto v2 = map_points[xmin + 1][ymin];
        auto v3 = map_points[xmin][ymin + 1];

        auto line1 = v3 - v2;
        auto line2 = v3 - v1;
        auto normal = glm::cross(line1, line2);

        auto par = physics::Parametric3D({ x, 10000, z }, { x, -10000, z });
        auto plane = physics::Plane3D({0, 0, 0}, normal, 1);

        float t;
        glm::vec3 intersect;
        plane.get_intersect(par, t, intersect);

        return intersect.y;
    }
}
