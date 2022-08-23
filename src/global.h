#pragma once

#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "entity/camera.h"
#include "entity/ecs.h"
#include "graphics/graphic_options.h"

#include <memory>

struct Global {
    core::Window *window;

    graphics::GraphicOptions *graphic_options;
    graphics::Mesh *mesh;
    graphics::Texture *texture;
    entity::Entity entity;

    graphics::Renderer *renderer;
    entity::Camera *camera;

    entity::Ecs ecs;

    ~Global() {
        delete window;

        delete graphic_options;
        delete mesh;
        delete texture;

        delete renderer;
    }
};

extern Global global;
