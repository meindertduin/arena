#include "obj_loader.h"

#include <glm/glm.hpp>

#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <stdexcept>

namespace assets {
    struct ObjIndex {
        int vertex_index;
        int tex_coord_index;
        int normal_index;
    };

    ObjIndex parse_object_index(std::string token, graphics::MeshData *meshData);

    std::unique_ptr<graphics::MeshData> load_obj(std::string filename) {
        std::ifstream fs(filename);

        auto mesh_data = std::unique_ptr<graphics::MeshData>(new graphics::MeshData {  });

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> textcoords;
        std::vector<glm::vec3> normals;

        if (!fs.is_open())
            throw std::runtime_error("IO ERROR: Could not open filename: " + filename);

        while(!fs.eof()) {
            char line[128];

            fs.getline(line, sizeof(line));

            std::stringstream ss;
            std::vector<std::string> tokens;
            ss << line;

            std::string first_token;
            ss >> first_token;

            if (first_token == "v") {
                float x, y, z;
                ss >> x >> y >> z;

                vertices.push_back(glm::vec3(x, y, z));
            }

            if (first_token == "vt") {
                float x, y;
                ss >> x >> y;

                textcoords.push_back(glm::vec2(x, y));
            }

            if (first_token == "vn") {
                float x, y, z;
                ss >> x >> y >> z;
                normals.push_back(glm::vec3(x, y, z));
            }

            if (first_token == "f") {
                std::vector<std::string> tokens;
                std::string value;

                while(std::getline(ss, value, ' '))
                    tokens.push_back(value);

                for (int i = 0; i < tokens.size() - 3; i++) {
                    ObjIndex objIndices[3] = {
                        parse_object_index(tokens[3 + i], mesh_data.get()),
                        parse_object_index(tokens[2 + i], mesh_data.get()),
                        parse_object_index(tokens[1], mesh_data.get()),
                    };

                    for (int i = 0; i < 3; i++) {
                        graphics::Vertex vertex;

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


        fs.close();

        return std::move(mesh_data);
    }

    ObjIndex parse_object_index(std::string token, graphics::MeshData *mesh_data) {
        ObjIndex result;
        std::stringstream ss;
        ss << token;

        int i = 0;
        std::string value;

        while(std::getline(ss, value, '/')) {
            if (value == "") {
                i++;
                continue;
            }

            if (i == 0) {
                result.vertex_index = std::stoi(value) - 1;
            } else if (i == 1) {
                result.tex_coord_index = std::stoi(value) - 1;
            } else if(i == 2) {
                result.normal_index = std::stoi(value) - 1;
                break;
            }

            i++;
        }

        return result;
    }

}
