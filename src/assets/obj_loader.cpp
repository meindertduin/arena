#include "loaders.h"

#include <glm/glm.hpp>
#include <sstream>
#include <memory>
#include <vector>

#include "file_reader.h"
#include "../global.h"

namespace assets {
    struct ObjIndex {
        int vertex_index;
        int tex_coord_index;
        int normal_index;
    };

    ObjIndex parse_object_index(std::string token, graphics::MeshData *meshData);

    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename) {
        FileReader file_reader { filename };

        auto mesh_data = std::make_unique<graphics::MeshData>(graphics::MeshData{});

        auto chained = core::ChainedAllocator<core::LinearAllocator>{ &global.list_allocator, 1024 * 1024, 8 };
        core::StdLinearAllocator<core::LinearAllocator> allocator { chained.get(), 0 };

        core::LinearAllocVector<glm::vec3> vertices(allocator);
        core::LinearAllocVector<glm::u16vec2> textcoords(allocator);
        core::LinearAllocVector<glm::vec3> normals(allocator);

        std::string line;
        while(file_reader.next_line(line)) {
            std::stringstream ss;
            std::vector<std::string> tokens;
            ss << line;

            std::string first_token;
            ss >> first_token;

            if (first_token == "v") {
                float x, y, z;
                ss >> x >> y >> z;

                vertices.emplace_back(x, y, z);
            }

            if (first_token == "vt") {
                float x, y;
                ss >> x >> y;

                textcoords.emplace_back(x * 65535.0f, y * 65535.0f);
            }

            if (first_token == "vn") {
                float x, y, z;
                ss >> x >> y >> z;
                normals.emplace_back(x, y, z);
            }

            if (first_token == "f") {
                std::string value;

                while (std::getline(ss, value, ' '))
                    tokens.push_back(value);

                for (int i = 0; i < tokens.size() - 3; i++) {
                    ObjIndex objIndices[3] = {
                            parse_object_index(tokens[3 + i], mesh_data.get()),
                            parse_object_index(tokens[2 + i], mesh_data.get()),
                            parse_object_index(tokens[1], mesh_data.get()),
                    };

                    for (int i = 0; i < 3; i++) {
                        graphics::Vertex vertex{};

                        // set the ordering right
                        auto index = objIndices[2 - i];
                        vertex.pos = vertices[index.vertex_index];
                        vertex.normal = normals[index.normal_index];
                        vertex.textcoords = textcoords[index.tex_coord_index];

                        mesh_data->vertices.push_back(vertex);
                    }
                }
            }
        }

        return std::make_shared<graphics::Mesh>(mesh_data.get());
    }

    ObjIndex parse_object_index(std::string token, graphics::MeshData *mesh_data) {
        ObjIndex result{};
        std::stringstream ss;
        ss << token;

        int i = 0;
        std::string value;

        while (std::getline(ss, value, '/')) {
            if (value.empty()) {
                i++;
                continue;
            }

            if (i == 0) {
                result.vertex_index = std::stoi(value) - 1;
            } else if (i == 1) {
                result.tex_coord_index = std::stoi(value) - 1;
            } else if (i == 2) {
                result.normal_index = std::stoi(value) - 1;
                break;
            }

            i++;
        }

        return result;
    }

}
