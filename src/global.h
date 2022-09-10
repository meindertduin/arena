#pragma once

#include "core/window.h"
#include "entity/camera.h"
#include "entity/ecs.h"

#include "graphics/graphic_options.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "graphics/material.h"
#include "input/input_manager.h"

#include <memory>

namespace game {
    struct GameState;
}

struct Global {
    core::Window *window;

    input::InputManager input_manager;
    game::GameState *game;
    graphics::Renderer *renderer;
    graphics::TerrainRenderer *terrain_renderer;

    graphics::GraphicOptions *graphic_options;
    graphics::GpuTexture *texture;
    graphics::Material material;

    entity::Ecs *ecs;

    ~Global() {
        delete window;

        delete graphic_options;
        delete texture;

        delete renderer;
        delete terrain_renderer;
    }
};

extern Global global;
