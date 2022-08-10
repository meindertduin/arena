#pragma once

#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "entity/camera.h"

struct Global {
    core::Window *window;
    graphics::Mesh *mesh;
    graphics::Renderer *renderer;
    entity::Camera camera;

    ~Global() {
        delete window;
        delete renderer;
        delete mesh;
    }
};

extern Global global;
