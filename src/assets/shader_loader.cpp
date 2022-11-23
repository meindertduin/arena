#include "loaders.h"

namespace assets {
    graphics::ShaderProgram::ShaderProgramData load_shader(const Path &path) {
        auto vert_shader_filename = path.path() + ".vert";
        auto frag_shader_filename = path.path() + ".frag";

        return { vert_shader_filename, frag_shader_filename };
    }
}