#include "loaders.h"

#include <sstream>
#include <memory>
#include "obj_file.h"

namespace assets {
    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename) {
        ObjFileReader file_reader;
        auto obj_file = file_reader.read_from_file(filename);

        auto& first_obj = obj_file->objects()[0];

        return std::make_shared<graphics::Mesh>(first_obj->mesh_data.get());
    }
}
