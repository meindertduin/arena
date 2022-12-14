#pragma once

#include "event_manager.h"
#include "entity.h"
#include "component_manager.h"
#include "system.h"
#include "../utils/types.h"
#include "component_registry.h"

namespace game {
    class Scene;
}

namespace entity {
    class Ecs {
    public:
        Ecs(game::Scene *scene) : m_scene{scene} {
            component_manager = std::make_unique<ComponentManager>(component_registry);

            systems_manager = std::make_unique<SystemsManager>();
            entity_manager = std::make_unique<EntityManager>();

            entity_manager->initialize_entities(this);
        }

        Ecs(const Ecs &) = delete;
        Ecs(Ecs &&) = delete;
        Ecs& operator=(const Ecs &) = delete;
        Ecs& operator=(Ecs &&) = delete;
        
        Entity create_entity() {
            return entity_manager->create_entity();
        }

        void destroy_entity(Entity entity) {
            entity_manager->destroy(entity);
            component_manager->entity_destroyed(entity);
            systems_manager->entity_destroyed(entity);
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            component.scene = m_scene;
            component_manager->add_component<T>(entity, component);

            auto signature = entity_manager->get_signature(entity);
            signature.set(T::_id, true);
            entity_manager->set_signature(entity, signature);

            systems_manager->entity_signature_changed(entity, signature);
        }

        template<typename T>
        void remove_component(Entity entity) {
            component_manager->remove_component<T>(entity);

            auto signature = entity_manager->get_signature(entity);
            signature.set(T::_id, false);
            entity_manager->set_signature(entity, signature);

            systems_manager->entity_signature_changed(entity, signature);
        }

        template<typename T>
        T& get_component(Entity entity) {
            return component_manager->get_component<T>(entity);
        }

        template<typename T>
        T* get_component_ptr(Entity entity) {
            return component_manager->get_component_ptr<T>(entity);
        }

        template<typename T>
        std::optional<T*> get_component_opt(Entity entity) {
            return component_manager->get_component_opt<T>(entity);
        }

        template<typename T>
        bool has_component(Entity entity) {
            return component_manager->has_component<T>(entity);
        }

        template<typename C>
        std::shared_ptr<ComponentArray<C>> get_component_array() {
            return component_manager->template get_component_array<C>();
        }

        template<typename T>
        std::shared_ptr<T> register_system() {
            return systems_manager->register_system<T>();
        }

        template<typename T>
        std::shared_ptr<T> create_system(const std::set<uint32_t>& component_ids) {
            auto system = register_system<T>();

            entity::Signature col_signature;
            for (auto id : component_ids) {
                col_signature.set(id);
            }

            set_system_signature<T>(col_signature);
            return system;
        }

        template<typename T>
        void set_system_signature(Signature signature) {
            systems_manager->set_signature<T>(signature);
        }

        Signature get_signature(Entity entity) {
            return entity_manager->get_signature(entity);
        }

        template<typename E>
        constexpr void dispatch_event(E *event) {
            component_manager->dispatch_event(event);
        }

        template<typename T>
        static void register_component() {
            component_registry->register_component<T>();
        }

        template<
            typename F,
            typename M = types::member_function_traits<F>,
            typename C = typename M::instance_type,
            typename E = typename M::first_argument>
        static void add_event_handler(F &&f) {
            // TODO maybe use std::forward for f
            component_registry->add_event_handler<C, E>(f);
        }
    private:
        game::Scene *m_scene;

        std::unique_ptr<SystemsManager> systems_manager;
        std::unique_ptr<EntityManager> entity_manager;
        std::unique_ptr<ComponentManager> component_manager;

        static inline std::unique_ptr<ComponentRegistry> component_registry = std::make_unique<ComponentRegistry>();
    };
}
