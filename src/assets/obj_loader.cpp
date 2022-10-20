#include "loaders.h"

#include <glm/glm.hpp>
#include <sstream>
#include <memory>
#include <vector>

#include "file_reader.h"
#include "../global.h"
#include "obj_file.h"

namespace assets {
    struct ObjIndex {
        int vertex_index;
        int tex_coord_index;
        int normal_index;
    };

    ObjIndex parse_object_index(std::string token, graphics::MeshData *meshData);

    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename) {
        ObjFileReader file_reader;
        auto obj_file = file_reader.read_from_file(filename);

        auto& first_obj = obj_file->objects()[0];

        return std::make_shared<graphics::Mesh>(first_obj->mesh_data.get());
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
