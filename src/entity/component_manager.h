#pragma once

#include "entity.h"
#include "component_array.h"
#include "../logging.h"

namespace entity {
    class ComponentManager {
    public:
        template<typename T>
        void register_component() {
            if (component_arrays.find(T::_id) != component_arrays.end()) {
                THROW_ERROR("Registered Component of type: %s more than once.", typeid(T).name());
            }

            auto component_array = std::make_shared<ComponentArray<T>>();
            component_arrays.insert({T::_id, component_array});

            next_component_type++;
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

        template<typename T>
        std::optional<T*> get_component_opt(Entity entity) {
            return get_component_array<T>()->get_opt(entity);
        }

        template<typename T>
        bool has_component(Entity entity) {
            return get_component_array<T>()->has_component(entity);
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

        template<typename C, typename E, typename F>
        void add_event_handler(F && f) {
            get_component_array<C>()->template add_event_handler<E>(f);
        }

        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array() {
            if (component_arrays.find(T::_id) == component_arrays.end()) {
                THROW_ERROR("Could not find component of type: %s.", typeid(T).name());
            }

            return std::static_pointer_cast<ComponentArray<T>>(component_arrays[T::_id]);
        }
    private:
        std::unordered_map<uint32_t, std::shared_ptr<IComponentArray>> component_arrays;
        uint32_t next_component_type;
    };
}

