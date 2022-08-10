#include "entity.h"

namespace entity {
    EntityManager::EntityManager() {
        for (auto entity = 0; entity < MAX_ENTITIES; ++entity) {
            available_entries.push(entity);
        }
    }

    Entity EntityManager::create_entity() {
        if (active_entities_count > MAX_ENTITIES) {
            throw std::runtime_error("Max amount of entities exceeded");
        }
        auto id = available_entries.front();
        available_entries.pop();

        active_entities_count++;

        return id;
    }

    void EntityManager::destroy(Entity entity) {
        if (entity > MAX_ENTITIES) {
            throw std::runtime_error("Entity cannot be above the MAX_ENTITIES amount");
        }

        signatures[entity].reset();
        available_entries.push(entity);

        active_entities_count--;
    }

    void EntityManager::set_signature(Entity entity, Signature signature) {
        if (entity > MAX_ENTITIES) {
            throw std::runtime_error("Entity cannot be above the MAX_ENTITIES amount");
        }

        signatures[entity] = signature;
    }

    Signature EntityManager::get_signature(Entity entity) const {
        return signatures[entity];
    }
}
