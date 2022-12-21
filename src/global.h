#pragma once

#include "input/input_manager.h"
#include "core/linear_allocator.h"
#include "core/list_allocator.h"
#include "core/telemetrics.h"
#include "core/application.h"

#include <memory>

namespace graphics {
    class GraphicOptions;
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

    graphics::GraphicOptions *graphic_options;

    void init();
};

extern Global global;
