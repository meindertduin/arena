#pragma once

#include "entity.h"
#include "component_manager.h"
#include "system.h"
#include "event_manager.h"

namespace entity {
    struct Ecs {
    public:
        Ecs() {
            component_manager = std::make_unique<ComponentManager>();
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

        void destory_entity(Entity entity) {
            entity_manager->destroy(entity);
            component_manager->entity_destroyed(entity);
            systems_manager->entity_destroyed(entity);
        }

        template<typename T>
        void register_component() {
            component_manager->register_component<T>();
        }

        template<typename T>
        void add_component(Entity entity, T component) {
            component_manager->add_component<T>(entity, component);

            auto signature = entity_manager->get_signature(entity);
            signature.set(component_manager->get_component_type<T>(), true);
            entity_manager->set_signature(entity, signature);

            systems_manager->entity_signature_changed(entity, signature);
        }

        template<typename T>
        void remove_component(Entity entity) {
            component_manager->remove_component<T>(entity);

            auto signature = entity_manager->get_signature(entity);
            signature.set(component_manager->get_component_type<T>(), false);
            entity_manager->set_signature(entity, signature);

            systems_manager->entity_signature_changed(entity, signature);
        }

        template<typename T>
        T& get_component(Entity entity) {
            return component_manager->get_component<T>(entity);
        }

        template<typename T>
        ComponentType get_component_type() {
            return component_manager->get_component_type<T>();
        }

        template<typename T>
        std::shared_ptr<T> register_system() {
            return systems_manager->register_system<T>();
        }

        template<typename T>
        void set_system_signature(Signature signature) {
            systems_manager->set_signature<T>(signature);
        }

        Signature get_signature(Entity entity) {
            return entity_manager->get_signature(entity);
        }

        template<typename C, typename E>
        void dispatch_event(E *event) {
            component_manager->dispatch_event<C>(event);
        }

    private:
        std::unique_ptr<SystemsManager> systems_manager;
        std::unique_ptr<EntityManager> entity_manager;
        std::unique_ptr<ComponentManager> component_manager;
    };
}
