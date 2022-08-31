#pragma once

#include "entity.h"
#include "event_manager.h"

namespace entity {
    struct IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entity_destroyed(Entity entity) = 0;
        virtual constexpr void dispatch(void *e, uint32_t event_id) = 0;
        virtual constexpr void dispatch(void *e, uint32_t event_id, Entity entity) = 0;
    };

    template<typename T>
    struct ComponentArray : IComponentArray {
    public:
        void insert(Entity entity, T component) {
            if (entity_index_map.find(entity.id) != entity_index_map.end()) {
                throw std::runtime_error("Cannot insert entity that does not exist");
            }

            // insert a new component at the back of the empty components array
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
            
            // replace the removed component with the last element
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

        template<typename E, typename F>
        void add_event_handler(F &&f) {
            auto handler = [f = std::forward<F>(f)](void *c, void *e) {
                ((reinterpret_cast<T*>(c)->*f)(*reinterpret_cast<const E*>(e)));
            };
            
            event_handlers[E::_id] = handler;
        }

        // could not make this a template function, thats why e is type void*
        constexpr void dispatch(void *e, uint32_t event_id) override {
            if (event_handlers.find(event_id) == event_handlers.end()) {
                return;
            }
            for (auto &component : components) {
                // DO check if it component is not used
                event_handlers[event_id](&component, e);
            }
        }

        constexpr void dispatch(void *e, uint32_t event_id, Entity entity) override {
            if (event_handlers.find(event_id) == event_handlers.end()) {
                return;
            }
            // DO check if it component is not used
            auto &component = components[entity.id];
            event_handlers[event_id](&component, e);
        }
    private:
        // Not very memory efficient with alot of components
        std::array<T, MAX_ENTITIES> components;

        // TODO, make this an array for performance bonus
        std::unordered_map<uint32_t, size_t> entity_index_map;
        std::unordered_map<uint32_t, size_t> index_entity_map;

        std::unordered_map<EventType, std::function<void(T*, void*)>> event_handlers;

        size_t size;
    };
}

