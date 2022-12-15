#pragma once

#include "input/input_manager.h"
#include "core/linear_allocator.h"
#include "core/list_allocator.h"
#include "core/telemetrics.h"
#include "core/application.h"

#include <memory>

namespace assets {
    class Cache;
}

namespace core {
    class Window;
}

namespace game {
    class GameState;
}

namespace graphics {
    class Renderer;
    class TerrainRenderer;
    class TextRenderer;
    class UIRenderer;
    class Texture;
    class Material;
    class GraphicOptions;
}

namespace entity {
    class Ecs;
    class SystemsCollection;
}

namespace editor {
    class Editor;
}


class Global {
public:
    Application *application;
    core::LinearAllocator allocator { 1024 * 1024 };
    core::ListAllocator list_allocator {1024 * 1024 * 2, core::ListAllocator::PlacementPolicy::First };
    core::Telemetrics telemetrics;

    editor::Editor *editor;

    input::InputManager input_manager;
    game::GameState *game;
    assets::Cache *cache;

    graphics::Renderer *renderer;
    graphics::TextRenderer *text_renderer;
    graphics::UIRenderer *ui_renderer;
    entity::SystemsCollection *systems;

    graphics::GraphicOptions *graphic_options;

    entity::Ecs *ecs;

    void init(Application *app);
};

extern Global global;
