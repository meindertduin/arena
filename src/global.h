#pragma once

#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"

struct Global {
    core::Window *window;
    graphics::Mesh *mesh;
    graphics::Renderer *renderer;

    ~Global() {
        delete window;
        delete renderer;
        delete mesh;
    }
};

extern Global global;
