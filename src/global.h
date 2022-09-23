#pragma once

#include "input/input_manager.h"
#include "core/linear_allocator.h"
#include "core/list_allocator.h"

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
    class TextRenderer;
    struct Texture;
    struct Material;
    struct GraphicOptions;
}

namespace entity {
    struct Ecs;
}

struct Global {
    core::Window *window;
    core::LinearAllocator allocator { 1024 * 1024 };
    core::ListAllocator list_allocator {1024 * 1024 * 2, core::ListAllocator::PlacementPolicy::First };

    input::InputManager input_manager;
    game::GameState *game;
    graphics::Renderer *renderer;
    graphics::TerrainRenderer *terrain_renderer;
    graphics::TextRenderer *text_renderer;

    graphics::GraphicOptions *graphic_options;
    std::shared_ptr<graphics::Texture> texture;
    graphics::Material *material;

    entity::Ecs *ecs;
};

extern Global global;
