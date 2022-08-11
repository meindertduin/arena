#pragma once

#include "entity.h"

#include <set>

namespace entity {
    struct System {
    public:
        std::set<Entity> entities;

        virtual void update() = 0;
    };

    struct SystemsManager {
    public:
        template<typename T>
            std::shared_ptr<T> register_system() {
                auto type_name = typeid(T).name();

                if (systems.find(type_name) != systems.end()) {
                    throw std::runtime_error("System already registered");
                }

                auto system = std::make_shared<T>();
                systems.insert({type_name, system});

                return system;
            }

        template<typename T>
        void set_signature(Signature signature) {
            auto type_name = typeid(T).name();

            if (systems.find(type_name) == systems.end()) {
                throw std::runtime_error("System was not registered");
            }

            signatures.insert({type_name, signature});
        }

        void entity_destroyed(Entity entity) {
            for (const auto &pair : systems) {
                pair.second->entities.erase(entity);
            }
        }

        void entity_signature_changed(Entity entity, Signature signature) {
            for (const auto &pair : systems) {
                const auto &type = pair.first;
                const auto &system = pair.second;
                const auto &system_signature = signatures[type];

                if ((signature & system_signature) == system_signature) {
                    system->entities.insert(entity);
                    return;
                }

                system->entities.erase(entity);
            }
        }
    private:
        std::unordered_map<const char*, Signature> signatures;
        std::unordered_map<const char*, std::shared_ptr<System>> systems;
    };
}
