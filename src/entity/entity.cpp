#include "entity.h"

#include "ecs.h"
#include "../logging.h"

namespace entity {
    EntityManager::EntityManager() {
    }

    void EntityManager::initialize_entities(Ecs *manager) {
        for (auto entity = 0u; entity < MaxEntities; ++entity) {
            available_entries.push({ Entity { entity, manager }});
        }
    }

    Entity EntityManager::create_entity() {
        if (active_entities_count > MaxEntities) {
            THROW_ERROR("Max amount of entities exceeded");
        }
        auto id = available_entries.front();
        available_entries.pop();

        active_entities_count++;

        return id;
    }

    void EntityManager::destroy(Entity entity) {
        if (entity.id > MaxEntities) {
            THROW_ERROR("Entity cannot be above the MaxEntities amount");
        }

        signatures[entity.id].reset();
        available_entries.push(entity);

        active_entities_count--;
    }

    void EntityManager::set_signature(Entity entity, Signature signature) {
        if (entity.id > MaxEntities) {
            THROW_ERROR("Entity cannot be above the MaxEntities amount");
        }

        signatures[entity.id] = signature;
    }

    Signature EntityManager::get_signature(Entity entity) const {
        return signatures[entity.id];
    }
}
