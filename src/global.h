#pragma once

#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "entity/camera.h"
#include "entity/ecs.h"

#include <memory>

struct Global {
    core::Window *window;

    graphics::Mesh *mesh;
    entity::Entity entity;

    graphics::Renderer *renderer;
    entity::Camera camera;

    entity::Ecs ecs;

    ~Global() {
        delete window;
        delete renderer;
        delete mesh;
    }
};

extern Global global;
