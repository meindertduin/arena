#pragma once

#include "entity.h"

namespace entity {
    struct IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entity_destroyed(Entity entity) = 0;
    };

    template<typename T>
    struct ComponentArray : IComponentArray {
    public:
        void insert(Entity entity, T component) {
            if (entity_index_map.find(entity.id) != entity_index_map.end()) {
                throw std::runtime_error("Cannot insert entity that does not exist");
            }

            auto new_index = size;
            entity_index_map[entity.id] = new_index;
            index_entity_map[new_index] = entity.id;
            components[new_index] = component;

            size++;
        }

        void remove(Entity entity) {
            if (entity_index_map.find(entity.id) == entity_index_map.end()) {
                throw std::runtime_error("Cannot remove entity that does not exist");
            }

            auto removed_entity_index = entity_index_map[entity.id];
            auto last_element_index = size - 1;
            components[removed_entity_index] = components[last_element_index];

		    // Update map to point to moved spot
            auto last_element_entity = index_entity_map[last_element_index];
            entity_index_map[last_element_index] = removed_entity_index;
            index_entity_map[removed_entity_index] = last_element_entity;

            entity_index_map.erase(entity.id);
            index_entity_map.erase(last_element_index);

            size--;
        }

        T& get(Entity entity) {
            if (entity_index_map.find(entity.id) == entity_index_map.end()) {
                throw std::runtime_error("Cannot retrieve entity that does not exist");
            }

            return components[entity_index_map[entity.id]];
        }

        void entity_destroyed(Entity entity) override {
            remove(entity);
        }
    private:
        // Not very memory efficient with alot of components
        std::array<T, MAX_ENTITIES> components;

        // TODO, make this an array for performance bonus
        std::unordered_map<uint32_t, size_t> entity_index_map;
        std::unordered_map<uint32_t, size_t> index_entity_map;

        size_t size;
    };
}

