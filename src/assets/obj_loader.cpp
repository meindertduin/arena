#include "loaders.h"

#include <sstream>
#include <memory>
#include "obj_file.h"

namespace assets {
    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename) {
        ObjFileReader file_reader;
        auto obj_file = file_reader.read_from_file(filename);

        auto& first_obj = obj_file->objects()[0];
        math::AABB bounding_box { first_obj->mesh_data->max };

        auto mesh = std::make_shared<graphics::Mesh>(first_obj->mesh_data.release(), bounding_box);
        for (auto &object : obj_file->objects()) {
            if (object->obj_name.starts_with("acx_")) {
                mesh->add_collision_data(object->mesh_data.release());
            }
        }

        return mesh;
    }
}
