#include "loaders.h"

#include <memory>
#include "obj_file.h"

namespace assets {
    std::unique_ptr<graphics::MeshData> load_obj(const Path &path) {
        ObjFileReader file_reader;
        auto obj_file = file_reader.read_from_file(path.path());

        auto mesh_data = std::make_unique<graphics::MeshData>();

        auto& first_obj = obj_file->objects()[0];
        auto first_obj_data = first_obj->mesh_data.release();
        mesh_data->vertices = std::move(first_obj_data->vertices);
        mesh_data->max = first_obj_data->max;

        for (auto &object : obj_file->objects()) {
            if (object->obj_name.starts_with("acx_")) {
                auto object_data = object->mesh_data.release();
                mesh_data->collision_data = std::make_unique<graphics::CollisionData>();

                mesh_data->collision_data->vertices = object_data->vertices;
                mesh_data->collision_data->max = object_data->max;
            }
        }

        return std::move(mesh_data);
    }
}
