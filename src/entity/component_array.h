#pragma once

#include "entity.h"
#include "event_manager.h"
#include "../logging.h"

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
            if (components.find(entity.id) != components.end()) {
                THROW_ERROR("Cannot insert entity that already exists");
            }

            components[entity.id] = component;

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
            if (components.find(entity.id) == components.end()) {
                THROW_ERROR("Cannot retrieve entity that does not exist");
            }

            return components[entity.id];
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

            if (components.find(entity.id) == components.end())
                return;

            auto &component = components[entity.id];
            event_handlers[event_id](&component, e);
        }
    private:
        std::unordered_map<uint32_t, T> components { 128 };
        std::unordered_map<EventType, std::function<void(T*, void*)>> event_handlers;

        size_t size{0};
    };
}

