#include "terrain.h"

#include "../global.h"
#include "../game/game_state.h"
#include "../assets/loaders.h"

namespace graphics {

    bool Terrain::get_height(float x, float z, float &y) const {
        auto xmin = (int) (x - m_transform.pos.x);
        auto ymin = (int) (z - m_transform.pos.z);

        if (xmin > this->width - 2 || xmin < 0 || ymin > this->height - 2 || ymin < 0)
            return false;

        glm::vec3 v1, v2, v3;
        if (x >= 1 - z) {
            v1 = this->positions[xmin][ymin + 1]; // bottom left
            v2 = this->positions[xmin + 1][ymin]; // top right
            v3 = this->positions[xmin + 1][ymin + 1]; // bottom right

            y = barry_centric(v1, v2, v3, { x - m_transform.pos.x, z - m_transform.pos.z});
        } else {
            v1 = this->positions[xmin][ymin]; // top left
            v2 = this->positions[xmin + 1][ymin]; // top right
            v3 = this->positions[xmin][ymin + 1]; // bottom left

            y = barry_centric(v1, v2, v3, { x - m_transform.pos.x, z - m_transform.pos.z});
        }

        y += m_transform.pos.y;
        return true;
    }

    float Terrain::barry_centric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos) {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }

    void Terrain::load() {
        auto file = assets::load_terrain(path());

        min_height = file.min_height;
        max_height = file.max_height;

        this->width = file.width;
        this->height = file.height;

        m_transform.pos = file.pos;

        Sprite16 sprite { file.heightmap };

        MeshData mesh_data;

        int touch_vertices[width][height];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                touch_vertices[j][i] = 0;
            }
        }

        this->positions = std::vector<std::vector<glm::vec3>>(height);
        for (auto & position : this->positions) {
            position = std::vector<glm::vec3>(width);
        }

        auto chained = core::ChainedAllocator<core::LinearAllocator>{ &global.list_allocator, 1024 * 1024, 8 };
        core::StdLinearAllocator<core::LinearAllocator> allocator { chained.get(), 0 };

        core::LinearAllocVector<std::vector<Vertex>> vertices(height, allocator);

        for (auto &v_vector : vertices) {
            v_vector = std::vector<Vertex>(width);
        }

        // setting all the vertices
        for (auto y = 0; y < height; y++) {
            for (auto x = 0; x < width; x++) {
                Vertex v{};
                v.pos.x = (float)x;
                auto sprite_x = (float)x * ((float)sprite.width / (float)width);
                auto sprite_y = (float)y * ((float)sprite.height / (float)height);

                // TODO blend the heights when up- or down-scaling
                v.pos.y = ((float)sprite.get_pixel(sprite_x, sprite_y) /  65535.0f) * (max_height - min_height) + min_height;
                v.pos.z = (float)y;
                v.normal = { 0, 0, 0 };
                auto tx = ((float) x / (float) width) * 66535.0f;
                auto ty = ((float) y / (float) height) * 65535.0f;
                v.textcoords = { tx, ty };

                vertices[x][y] = v;
                positions[x][y] = v.pos;
            }
        }

        // dividing heightmap into grid and triangles and calculating normals of vertices
        for (auto y = 0; y < height - 1; y++) {
            for (auto x = 0; x < width - 1; x++) {
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
        for (auto y = 0; y < height; y++) {
            for (auto x = 0; x < width; x++) {
                if (touch_vertices[x][y] >= 0) {
                    auto &v1 = vertices[x][y];
                    v1.normal /= touch_vertices[x][y];
                    v1.normal = glm::normalize(v1.normal);
                }
            }
        }

        // dividing vertices into polygons and adding to the mesh_data
        for (auto y = 0; y < height - 1; y++) {
            for (auto x = 0; x < width - 1; x++) {
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

        m_mesh = std::make_unique<Mesh>(&mesh_data);

        set_mesh_material(file);
    }

    void Terrain::set_mesh_material(const TerrainFile &file) {
        auto cache = global.application->engine()->cache();
        auto material = cache->get_resource<Material>("scripts/terrain_material.lua");

        material->add_texture(cache->get_resource<Texture>(file.background_texture));
        material->add_texture(cache->get_resource<Texture>(file.blendmap));

        material->add_texture(cache->get_resource<Texture>(file.r_texture));
        material->add_texture(cache->get_resource<Texture>(file.g_texture));
        material->add_texture(cache->get_resource<Texture>(file.b_texture));

        auto shader = cache->get_resource<Shader>("scripts/terrain_shader.lua");
        auto &program = shader->program();
        program.use();

        program.set_uniform_loc("baseTexture", 0);
        program.set_uniform_loc("blendMap", 1);
        program.set_uniform_loc("rTexture", 2);
        program.set_uniform_loc("gTexture", 3);
        program.set_uniform_loc("bTexture", 4);

        material->set_shader(shader);
        m_mesh->set_material(material);
    }
}
