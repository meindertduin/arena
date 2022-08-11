#pragma once

#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/renderer.h"
#include "entity/camera.h"
#include "entity/entity.h"
#include "entity/component_manager.h"

#include <memory>

struct Global {
    core::Window *window;

    graphics::Mesh *mesh;
    entity::Entity entity;

    graphics::Renderer *renderer;
    entity::Camera camera;

    entity::ComponentManager *component_manager;
    entity::EntityManager *entity_manager;

    ~Global() {
        delete window;
        delete renderer;
        delete mesh;
        delete component_manager;
        delete entity_manager;
    }
};

extern Global global;
