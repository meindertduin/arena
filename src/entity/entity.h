#pragma once

#include <cstdint>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>
#include <memory>

namespace entity {
    struct Ecs;

    static constexpr uint32_t MaxEntities = 2000;
    static constexpr uint32_t MaxComponents = 64;

    using Signature = std::bitset<MaxComponents>;

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

        template<typename C>
        inline void add(C component) const {
            this->p->template add_component<C>(*this, component);
        }

        template<typename C>
        inline void remove() {
            this->p->template remove_component<C>(*this);
        }

        inline auto operator==(const Object &rhs) const {
            return this->id == rhs.id;
        }

        inline auto operator<=>(const Object &rhs) const {
            return this->id <=> rhs.id;
        }

        inline void destory() const {
            this->p->template destroy_entity(*this);
        }

        inline Signature& signature() const {
            return this->p->template get_signature(*this);
        } 
    };

    using Entity = Object<Ecs>;

    struct EntityManager {
    public:
        EntityManager();

        void initialize_entities(Ecs *manager);
        Entity create_entity();
        void destroy(Entity entity);

        void set_signature(Entity entity, Signature signature);
        Signature get_signature(Entity entity) const;
    private:
        std::queue<Entity> available_entries;
        std::array<Signature, MaxEntities> signatures;
        uint32_t active_entities_count;
    };

}
