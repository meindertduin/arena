#include "loaders.h"

namespace assets {
    std::shared_ptr<graphics::ShaderProgram> load_shader(const std::string &filename) {
        auto vert_shader_filename = filename + ".vert";
        auto frag_shader_filename = filename + ".frag";
        auto shader = std::make_shared<graphics::ShaderProgram>(vert_shader_filename, frag_shader_filename);

        // TODO test code, throw away
        shader->link();

        shader->set_uniform_loc("baseTexture", 0);
        shader->set_uniform_loc("cubeMap", 1);
        return shader;
    }
}