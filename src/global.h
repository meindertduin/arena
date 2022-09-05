#pragma once

#include "input/input_manager.h"

#include "core/window.h"
#include "entity/camera.h"
#include "game/game_state.h"
#include "entity/ecs.h"

#include "graphics/graphic_options.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "graphics/material.h"

#include <memory>

struct Global {
    core::Window *window;

    input::InputManager input_manager;
    game::GameState *game;
    graphics::Renderer *renderer;

    graphics::GraphicOptions *graphic_options;
    graphics::Texture *texture;
    graphics::Material material;

    entity::Ecs *ecs;

    ~Global() {
        delete window;

        delete graphic_options;
        delete texture;
        delete game;

        delete renderer;
    }
};

extern Global global;
