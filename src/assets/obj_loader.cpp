#include "loaders.h"

#include <sstream>
#include <memory>
#include "obj_file.h"

namespace assets {
    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename) {
        ObjFileReader file_reader;
        auto obj_file = file_reader.read_from_file(filename);

        auto& first_obj = obj_file->objects()[0];

        auto x_half = (first_obj->mesh_data->x_max - first_obj->mesh_data->x_min) * 0.5f;
        auto y_half = (first_obj->mesh_data->y_max - first_obj->mesh_data->y_min) * 0.5f;
        auto z_half = (first_obj->mesh_data->z_max - first_obj->mesh_data->z_min) * 0.5f;

        math::Point3D<float> center {
            first_obj->mesh_data->x_min + x_half,
            first_obj->mesh_data->y_min + y_half,
            first_obj->mesh_data->z_min + z_half,
        };
        glm::vec3 dimensions { x_half, y_half, z_half };
        math::Box3D<float> bounding_box { center, dimensions };

        return std::make_shared<graphics::Mesh>(first_obj->mesh_data.get(), bounding_box);
    }
}
