#include "obj_file.h"

#include <glm/glm.hpp>
#include <sstream>

#include "../global.h"

namespace assets {
    struct ObjIndex {
        int vertex_index;
        int tex_coord_index;
        int normal_index;
    };

    ObjIndex parse_object_index(const std::string& token) {
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

    std::unique_ptr<ObjFile> ObjFileReader::read_from_file(const std::string &file) {
        file_reader.open_file(file);
        auto obj_file = std::make_unique<ObjFile>();
        read_header(obj_file);
        read_objects(obj_file);

        return obj_file;
    }


    void ObjFileReader::read_header(std::unique_ptr<ObjFile> &file) {
        bool read_header;
        std::string line;

        while(!read_header || file_reader.end_of_file()) {
            file_reader.next_line(line);
            std::stringstream ss;
            ss << line;
            std::string first_token;
            ss >> first_token;

            if (first_token == "mtllib") {
                std::string mtl_filename;
                ss >> mtl_filename;
                file->m_mtl_filename = mtl_filename;
            }

            if (first_token == "o") {
                read_header = true;
            }
        }
    }

    void ObjFileReader::read_objects(std::unique_ptr<ObjFile> &file) {
        bool has_next_object = true;
        std::string last_line;
        while (has_next_object) {
            last_line = file_reader.get_last_line();

            std::stringstream ss;
            std::vector<std::string> tokens;
            ss << last_line;

            std::string first_token;
            ss >> first_token;

            if (first_token == "o") {
                auto object = std::make_unique<ObjObject>();
                ss >> object->obj_name;

                read_object(object);
                file->objects().push_back(std::move(object));
            } else {
                has_next_object = false;
            }
        }
    }

    void ObjFileReader::read_object(std::unique_ptr<ObjObject> &object) {
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

            if (first_token == "o") {
                break;
            }

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

                if (mesh_data->x_min >= x) {
                    mesh_data->x_min = x;
                } else if(mesh_data->x_max <= x) {
                    mesh_data->x_max = x;
                }

                if (mesh_data->y_min >= y) {
                    mesh_data->y_min = y;
                } else if(mesh_data->y_max <= y) {
                    mesh_data->y_max = y;
                }

                if (mesh_data->z_min >= z) {
                    mesh_data->z_min = z;
                } else if(mesh_data->z_max <= z) {
                    mesh_data->z_max = z;
                }

                normals.emplace_back(x, y, z);
            }

            if (first_token == "f") {
                std::string value;

                while (std::getline(ss, value, ' '))
                    tokens.push_back(value);

                for (int i = 0; i < tokens.size() - 3; i++) {
                    ObjIndex objIndices[3] = {
                            parse_object_index(tokens[3 + i]),
                            parse_object_index(tokens[2 + i]),
                            parse_object_index(tokens[1]),
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

        object->mesh_data = std::move(mesh_data);
    }
}
