#pragma once

#include "entity.h"
#include "component_array.h"
#include "../logging.h"
#include "component_registry.h"

namespace entity {
    class ComponentManager {
    public:
        explicit ComponentManager(std::unique_ptr<ComponentRegistry> &component_registry) {
            auto components_data = component_registry->components_data();
            for (auto &[component_id, component_data] : components_data) {
                component_arrays.insert({ component_id, component_data->create_component_array() });
            }
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
        T* get_component_ptr(Entity entity) {
            return get_component_array<T>()->get_ptr(entity);
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

        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array() {
            if (component_arrays.find(T::_id) == component_arrays.end()) {
                THROW_ERROR("Could not find component of m_type: %s.", typeid(T).name());
            }

            return std::static_pointer_cast<ComponentArray<T>>(component_arrays[T::_id]);
        }
    private:
        std::unordered_map<uint32_t, std::shared_ptr<IComponentArray>> component_arrays;
    };
}

