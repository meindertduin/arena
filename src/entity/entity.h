#pragma once

#include <stdint.h>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>
#include <memory>

namespace entity {
    const uint32_t MAX_ENTITIES = 2000;
    using Entity = uint32_t;

    using ComponentType = uint8_t;
    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

    struct EntityManager {
    public:
        EntityManager();

        Entity create_entity();
        void destroy(Entity entity);

        void set_signature(Entity entity, Signature signature);
        Signature get_signature(Entity entity) const;
    private:
        std::queue<Entity> available_entries;
        std::array<Signature, MAX_ENTITIES> signatures;
        uint32_t active_entities_count;
    };

    struct IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entity_destroyed(Entity entity) = 0;
    };

    template<typename T>
    struct ComponentArray : IComponentArray {
    public:
        void insert(Entity entity, T component) {
            if (entity_index_map.find(entity) != entity_index_map.end()) {
                throw std::runtime_error("Cannot insert entity that does not exist");
            }

            auto new_index = size;
            entity_index_map[entity] = new_index;
            index_entity_map[new_index] = entity;
            components[new_index] = component;

            size++;
        }

        void remove(Entity entity) {
            if (entity_index_map.find(entity) == entity_index_map.end()) {
                throw std::runtime_error("Cannot remove entity that does not exist");
            }

            auto removed_entity_index = entity_index_map[entity];
            auto last_element_index = size - 1;
            components[removed_entity_index] = components[last_element_index];

		    // Update map to point to moved spot
            auto last_element_entity = index_entity_map[last_element_index];
            entity_index_map[last_element_index] = removed_entity_index;
            index_entity_map[removed_entity_index] = last_element_entity;

            entity_index_map.erase(entity);
            index_entity_map.erase(last_element_index);

            size--;
        }

        T& get(Entity entity) {
            if (entity_index_map.find(entity) == entity_index_map.end()) {
                throw std::runtime_error("Cannot retrieve entity that does not exist");
            }

            return components[entity_index_map[entity]];
        }

        void entity_destroyed(Entity entity) override {
            if (entity_index_map.find(entity) != entity_index_map.end()) {
                remove(entity);
            }
        }
    private:
        std::array<T, MAX_ENTITIES> components;

        // TODO, make this an array for performance bonus
        std::unordered_map<Entity, size_t> entity_index_map;
        std::unordered_map<Entity, size_t> index_entity_map;

        size_t size;
    };

    struct ComponentManager {
    public:
        template<typename T>
        void register_component() {
            auto type_name = typeid(T).name();
            if (component_types.find(type_name) != component_types.end()) {
                throw std::runtime_error("Registered ComponentType more than once");
            }

            component_types.insert({type_name, next_component_type});
            component_arrays.insert({type_name, std::make_shared<ComponentArray<T>>()});

            next_component_type++;
        }

        template<typename T>
        ComponentType get_component_type() {
            auto type_name = typeid(T).name();

            if (component_types.find(type_name) == component_types.end()) {
                throw std::runtime_error("Could not find component type.");
            }

            return component_types[type_name];
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            get_component_array<T>()->insert(entity, component);
        }

        template<typename T>
        void remove_component(Entity entity) {
            get_component_array<T>()->remove(entity);
        }

        template<typename T>
        T& get_component(Entity entity) {
            return get_component_array<T>()->get(entity);
        }

        void entity_destroyed(Entity entity) {
            for (auto const &pair : component_arrays) {
                pair.second->entity_destroyed(entity);
            }
        }
    private:
        std::unordered_map<const char*, ComponentType> component_types;
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> component_arrays;

        ComponentType next_component_type;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array() {
            auto type_name = typeid(T).name();

            if (component_types.find(type_name) == component_types.end()) {
                throw std::runtime_error("Could not find component type.");
            }

            return std::static_pointer_cast<ComponentArray<T>>(component_arrays[type_name]);
        }
    };
}
