#include "terrain.h"

#include "../global.h"

namespace graphics {
    TerrainTexturePack::TerrainTexturePack() {
        background_texture = std::make_unique<GpuTexture>("assets/grass.png");
        blendmap = std::make_unique<GpuTexture>("assets/blendmap.png");

        r_texture = std::make_unique<GpuTexture>("assets/bricks.png");
        g_texture = std::make_unique<GpuTexture>("assets/dirt.png");
        b_texture = std::make_unique<GpuTexture>("assets/bricks.png");
    }

    void TerrainTexturePack::bind() const {
        int i = 0;
        background_texture->bind(i++);
        blendmap->bind(i++);

        r_texture->bind(i++);
        g_texture->bind(i++);
        b_texture->bind(i);
    }

    Terrain::Terrain(const std::string& heightmap_path) {
        Sprite16 sprite { heightmap_path };
        this->width = sprite.width;
        this->height = sprite.height;
        
        MeshData mesh_data;
        
        int touch_vertices[sprite.width][sprite.height];
        for (int i = 0; i < sprite.height; i++) {
            for (int j = 0; j < sprite.width; j++) {
                touch_vertices[j][i] = 0;
            }
        }

        this->positions = std::vector<std::vector<glm::vec3>>(sprite.height);
        for (auto & position : this->positions) {
            position = std::vector<glm::vec3>(sprite.width);
        }

        Vertex vertices[sprite.width][sprite.height];

        // setting all the vertices
        for (auto y = 0; y < sprite.height; y++) {
            for (auto x = 0; x < sprite.width; x++) {
                Vertex v{};
                v.pos.x = (float)x;
                v.pos.y = ((float)sprite.get_pixel(x, y) /  65535.0f) * (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT;
                v.pos.z = (float)y;
                v.normal = { 0, 0, 0 };
                auto tx = ((float) x / (float) sprite.width) * 66535.0f;
                auto ty = ((float) y / (float) sprite.height) * 65535.0f;
                v.textcoords = { tx, ty };

                vertices[x][y] = v;
                positions[x][y] = v.pos;
            }
        }

        // dividing heightmap into grid and triangles and calculating normals of vertices
        for (auto y = 0; y < sprite.height - 1; y++) {
            for (auto x = 0; x < sprite.width - 1; x++) {
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
        for (auto y = 0; y < sprite.height; y++) {
            for (auto x = 0; x < sprite.width; x++) {
                if (touch_vertices[x][y] >= 0) {
                    auto &v1 = vertices[x][y];
                    v1.normal /= touch_vertices[x][y];
                    v1.normal = glm::normalize(v1.normal);
                }
            }
        }

        // dividing vertices into polygons and adding to the mesh_data
        for (auto y = 0; y < sprite.height - 1; y++) {
            for (auto x = 0; x < sprite.width - 1; x++) {
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

    bool Terrain::fast_height(float x, float z, float &y) const {
        auto xmin = (int) (x - this->transform.pos.x);
        auto ymin = (int) (z - this->transform.pos.z);

        if (xmin > this->width - 2 || xmin < 0 || ymin > this->height - 2 || ymin < 0)
            return false;

        glm::vec3 v1, v2, v3;
        if (x >= 1 - z) {
            v1 = this->positions[xmin][ymin + 1]; // bottom left
            v2 = this->positions[xmin + 1][ymin]; // top right
            v3 = this->positions[xmin + 1][ymin + 1]; // bottom right

            y = barry_centric(v1, v2, v3, { x - this->transform.pos.x, z - this->transform.pos.z});
        } else {
            v1 = this->positions[xmin][ymin]; // top left
            v2 = this->positions[xmin + 1][ymin]; // top right
            v3 = this->positions[xmin][ymin + 1]; // bottom left

            y = barry_centric(v1, v2, v3, { x - this->transform.pos.x, z - this->transform.pos.z});
        }

        y += this->transform.pos.y;
        return true;
    }

    float Terrain::barry_centric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos) {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }
}
