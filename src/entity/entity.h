#pragma once

#include <stdint.h>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>
#include <memory>


namespace entity {
    const uint32_t MAX_ENTITIES = 2000;

    struct ComponentManager;

    template<typename T>
    struct Object {
        uint32_t id;
        T *p;

        Object() = default;
        Object(uint32_t id, T *p) : id(id), p(p) {}

        template<typename C> 
        inline C& get() const {
            return this->p->template get_component<C>(*this);
        }

        inline auto operator==(const Object &rhs) const {
            return this->id == rhs.id;
        }

        inline auto operator<=>(const Object &rhs) const {
            return this->id <=> rhs.id;
        }
    };

    using Entity = Object<ComponentManager>;

    using ComponentType = uint8_t;
    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

    struct EntityManager {
    public:
        EntityManager();

        void initialize_entities(ComponentManager *manager);
        Entity create_entity();
        void destroy(Entity entity);

        void set_signature(Entity entity, Signature signature);
        Signature get_signature(Entity entity) const;
    private:
        std::queue<Entity> available_entries;
        std::array<Signature, MAX_ENTITIES> signatures;
        uint32_t active_entities_count;
    };

}
