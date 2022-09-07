#include "terrain.h"

#include "../global.h"

#include <glm/gtx/intersect.hpp>

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

        this->vertices = new Vertex*[this->sprite->height];
        for (int i = 0; i < this->sprite->height; i++)
            this->vertices[i] = new Vertex[this->sprite->width];
    
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

    bool Terrain::get_intersect(const glm::vec3 &pos, glm::vec3 &intersect) const {
        auto xmin = (int) (pos.x - this->transform.pos.x);
        auto ymin = (int) (pos.z - this->transform.pos.z);

        auto v1 = vertices[xmin][ymin];
        auto v2 = vertices[xmin + 1][ymin];
        auto v3 = vertices[xmin][ymin + 1];

        glm::vec3 origin = pos - transform.pos;
        glm::vec3 dir = { 0, -1, 0 };
        auto did_intersect = glm::intersectLineTriangle(origin, dir, v3.pos, v2.pos, v1.pos, intersect);

        intersect.y += this->transform.pos.y;
        return did_intersect;
    }

    bool Terrain::get_height(float x, float z, float &height) const {
        auto xmin = (int) (x - this->transform.pos.x);
        auto ymin = (int) (z - this->transform.pos.z);

        auto v1 = vertices[xmin][ymin];
        auto v2 = vertices[xmin + 1][ymin];
        auto v3 = vertices[xmin][ymin + 1];

        glm::vec3 origin = glm::vec3 { x - transform.pos.x, 1000, z - transform.pos.z };
        glm::vec3 dir = { 0, -1, 0 };
        glm::vec3 intersect;
        auto did_intersect = glm::intersectLineTriangle(origin, dir, v1.pos, v2.pos, v3.pos, intersect);

        height = intersect.y + this->transform.pos.y;
        return did_intersect;
    
        // height = (v1.pos.y + v2.pos.y + v3.pos.y) * 0.3333 + this->transform.pos.y;
        // return true;
    }

    bool Terrain::fast_height(float x, float z, float &height) const {
        auto xmin = (int) (x - this->transform.pos.x);
        auto ymin = (int) (z - this->transform.pos.z);

        Vertex v1, v2, v3;
        if (x > z) {
            v1 = vertices[xmin][ymin];
            v2 = vertices[xmin + 1][ymin];
            v3 = vertices[xmin + 1][ymin + 1];
        } else {
            v1 = vertices[xmin][ymin];
            v2 = vertices[xmin + 1][ymin];
            v3 = vertices[xmin][ymin + 1];
        }

        height = (v1.pos.y + v2.pos.y + v3.pos.y) * 0.3333 + this->transform.pos.y;
        return true;
    }
}
