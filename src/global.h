#pragma once

#include "input/input_manager.h"

#include <memory>

namespace core {
    struct Window;
}

namespace game {
    struct GameState;
}

namespace graphics {
    struct Renderer;
    struct TerrainRenderer;
    struct GpuTexture;
    struct Material;
    struct GraphicOptions;
}

namespace entity {
    struct Ecs;
}

struct Global {
    core::Window *window;

    input::InputManager input_manager;
    game::GameState *game;
    graphics::Renderer *renderer;
    graphics::TerrainRenderer *terrain_renderer;

    graphics::GraphicOptions *graphic_options;
    graphics::GpuTexture *texture;
    graphics::Material *material;

    entity::Ecs *ecs;
};

extern Global global;
