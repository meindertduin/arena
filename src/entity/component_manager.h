#pragma once

#include "entity.h"
#include "component_array.h"

namespace entity {
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

        // used for setting the component in a signature
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
            component.entity_id = entity.id;
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

        template<typename T, typename E>
        void dispatch_event(E *event) {
            get_component_array<T>()->dispatch(event);
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

