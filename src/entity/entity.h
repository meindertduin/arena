#pragma once

#include <stdint.h>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>
#include <memory>

namespace entity {
    const uint32_t MAX_ENTITIES = 2000;
    using Entity = uint32_t;

    using ComponentType = uint8_t;
    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

    struct EntityManager {
    public:
        EntityManager();

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
