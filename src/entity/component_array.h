#pragma once

#include "entity.h"
#include "event_manager.h"
#include "../logging.h"

namespace entity {
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entity_destroyed(Entity entity) = 0;
        virtual constexpr void dispatch(void *e, uint32_t event_id) = 0;
        virtual constexpr void dispatch(void *e, uint32_t event_id, Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        std::vector<T*> values() {
            std::vector<T*> result;
            for (auto &[_, component] : components)
                result.push_back(&component);

            return result;
        }

        void insert(Entity entity, T component) {
            if (components.find(entity.id) != components.end()) {
                THROW_ERROR("Cannot insert entity that already exists");
            }

            components.insert({ entity.id, component });

            size++;
        }

        void remove(Entity entity) {
            if (components.find(entity.id) == components.end()) {
                THROW_ERROR("Cannot remove entity that does not exist");
            }

            components.erase(entity.id);

            size--;
        }

        T& get(Entity entity) {
            auto component_it = components.find(entity.id);
            if (component_it == components.end()) {
                THROW_ERROR("Cannot retrieve entity that does not exist");
            }

            return component_it->second;
        }

        T* get_ptr(Entity entity) {
            auto component_it = components.find(entity.id);
            if (component_it == components.end()) {
                THROW_ERROR("Component is not registered for entity.");
            }

            return &component_it->second;
        }

        std::optional<T*> get_opt(Entity entity) {
            auto component_it = components.find(entity.id);
            if (component_it == components.end()) {
                return std::nullopt;
            }

            return &component_it->second;
        }

        bool has_component(Entity entity) {
            return components.contains(entity.id);
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

        // could not make this a template function, that's why e is type void*
        void dispatch(void *e, uint32_t event_id) override {
            if (event_handlers.find(event_id) == event_handlers.end()) {
                return;
            }

            for (auto &[id, component] : components) {
                event_handlers[event_id](&component, e);
            }
        }

        constexpr void dispatch(void *e, uint32_t event_id, Entity entity) override {
            if (event_handlers.find(event_id) == event_handlers.end())
                return;

            auto component_it = components.find(entity.id);
            if (component_it == components.end())
                return

            event_handlers[event_id](&component_it->second, e);
        }

        auto begin() { return components.begin(); }
        auto end() { return components.end(); }
    private:
        std::unordered_map<uint32_t, T> components { 128 };
        std::unordered_map<EventType, std::function<void(T*, void*)>> event_handlers;

        size_t size{0};
    };
}

