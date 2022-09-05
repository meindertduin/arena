#pragma once

#include "entity.h"
#include "component_array.h"
#include "../logging.h"

namespace entity {
    struct ComponentManager {
    public:
        template<typename T>
        void register_component() {
            if (component_types.find(T::_id) != component_types.end()) {
                THROW_ERROR("Registered Component of type: %s more than once.", typeid(T).name());
            }

            component_types.insert({T::_id, next_component_type});
            auto component_array = std::make_shared<ComponentArray<T>>();
            component_arrays.insert({T::_id, component_array});

            next_component_type++;
        }

        // used for setting the component in a signature
        template<typename T>
        ComponentType get_component_type() {
            if (component_types.find(T::_id) == component_types.end()) {
                THROW_ERROR("Could not find component of type: %s.", typeid(T).name());
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

        template<typename E>
        void dispatch_event(E *event, Entity entity) {
            for (auto &component : component_arrays) {
                component.second->dispatch(event, E::_id, entity);
            }
        }

        template<typename C, typename E, typename F>
        void add_event_handler(F && f) {
            get_component_array<C>()->template add_event_handler<E>(f);
        }
    private:
        std::unordered_map<uint32_t, ComponentType> component_types;
        std::unordered_map<uint32_t, std::shared_ptr<IComponentArray>> component_arrays;

        ComponentType next_component_type;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array() {
            if (component_types.find(T::_id) == component_types.end()) {
                THROW_ERROR("Could not find component of type: %s.", typeid(T).name());
            }

            return std::static_pointer_cast<ComponentArray<T>>(component_arrays[T::_id]);
        }
    };
}

