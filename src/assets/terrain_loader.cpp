#include <vector>
#include <sstream>
#include "loaders.h"
#include "file_reader.h"

#include "../graphics/terrain.h"
#include "cache.h"

namespace assets {
    std::shared_ptr<graphics::Terrain> load_terrain(const std::string &filename) {
        FileReader file_reader { filename };
        graphics::TerrainFile terrain_file;

        std::string line;

        while(file_reader.next_line(line)) {
            std::stringstream ss;
            std::vector<std::string> tokens;
            ss << line;

            std::string first_token;
            ss >> first_token;

            if (first_token == "hm")
                ss >> terrain_file.heightmap;

            if (first_token == "bm")
                ss >> terrain_file.blendmap;

            if (first_token == "dt")
                ss >> terrain_file.background_texture;

            if (first_token == "rt")
                ss >> terrain_file.r_texture;

            if (first_token == "gt")
                ss >> terrain_file.g_texture;

            if (first_token == "bt") {
                ss >> terrain_file.b_texture;
            }

            if (first_token == "p") {
                float x, y, z;
                ss >> x >> y >> z;

                terrain_file.pos = {x, y, z };
            }

            if (first_token == "wh") {
                int width, height;
                ss >> width >> height;

                terrain_file.width = width;
                terrain_file.height = height;
            }

            if (first_token == "mh") {
                float min_height, max_height;
                ss >> min_height >> max_height;

                terrain_file.min_height = min_height;
                terrain_file.max_height = max_height;
            }

            if (first_token == "mt") {
                ss >> terrain_file.material;
            }
        }

        return std::make_shared<graphics::Terrain>(terrain_file);
    }
}