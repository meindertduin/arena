#pragma once

#include "entity.h"
#include "component_array.h"

namespace entity {
    struct ComponentManager {
    public:
        template<typename T>
        void register_component() {
            if (component_types.find(T::_id) != component_types.end()) {
                throw std::runtime_error("Registered ComponentType more than once");
            }

            component_types.insert({T::_id, next_component_type});
            auto component_array = std::make_shared<ComponentArray<T>>();
            component_arrays.insert({T::_id, component_array});

            T::_p = component_array.get();

            next_component_type++;
        }

        // used for setting the component in a signature
        template<typename T>
        ComponentType get_component_type() {
            if (component_types.find(T::_id) == component_types.end()) {
                throw std::runtime_error("Could not find component type.");
            }

            return component_types[T::_id];
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            component.entity = entity;
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

        template<typename E>
        void dispatch_event(E *event) {
            for (auto &component : component_arrays) {
                component.second->dispatch(event, E::_id);
            }
        }
    private:
        std::unordered_map<uint32_t, ComponentType> component_types;
        std::unordered_map<uint32_t, std::shared_ptr<IComponentArray>> component_arrays;

        ComponentType next_component_type;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array() {
            if (component_types.find(T::_id) == component_types.end()) {
                throw std::runtime_error("Could not find component type.");
            }

            return std::static_pointer_cast<ComponentArray<T>>(component_arrays[T::_id]);
        }
    };
}

