#pragma once

#include "core/window.h"
#include "entity/camera.h"
#include "entity/ecs.h"

#include "graphics/graphic_options.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "graphics/material.h"

#include "entity/game_state.h"

#include <memory>

struct Global {
    core::Window *window;

    graphics::GraphicOptions *graphic_options;
    graphics::Mesh *mesh;
    graphics::Texture *texture;
    graphics::Material material;
    entity::Entity entity;
    entity::GameState *game;

    graphics::Renderer *renderer;
    entity::Ecs ecs;

    ~Global() {
        delete window;

        delete graphic_options;
        delete mesh;
        delete texture;
        delete game;

        delete renderer;
    }
};

extern Global global;
