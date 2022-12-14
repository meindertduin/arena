#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../graphics/mesh.h"
#include "file_reader.h"

namespace assets {
    struct ObjData {
        float max;
        std::vector<graphics::Vertex> vertices;
    };

    struct ObjObject {
        std::string obj_name;
        std::unique_ptr<ObjData> mesh_data;
    };

    class ObjFile {
    public:
        ObjFile() = default;
        std::vector<std::unique_ptr<ObjObject>>& objects() { return m_objects; }
    private:
        friend class ObjFileReader;

        std::string m_mtl_filename;
        std::vector<std::unique_ptr<ObjObject>> m_objects;
    };

    class ObjFileReader {
    public:
        std::unique_ptr<ObjFile> read_from_file(const std::string &file);
    private:
        FileReader file_reader;
        void read_header(std::unique_ptr<ObjFile> &file);
        void read_objects(std::unique_ptr<ObjFile> &file);
        void read_object(std::unique_ptr<ObjObject> &object, std::vector<glm::vec3> &vertices, std::vector<glm::u16vec2> &textcoords, std::vector<glm::vec3> &normals);
    };
}
