#include "loaders.h"

namespace assets {
    std::shared_ptr<graphics::ShaderProgram> load_shader(const Path &path) {
        auto vert_shader_filename = path.path() + ".vert";
        auto frag_shader_filename = path.path() + ".frag";
        auto shader = std::make_shared<graphics::ShaderProgram>(vert_shader_filename, frag_shader_filename);

        // TODO test code, throw away
        shader->link();

        shader->set_uniform_loc("baseTexture", 0);
        shader->set_uniform_loc("cubeMap", 1);
        return shader;
    }
}