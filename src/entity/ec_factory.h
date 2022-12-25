#include "entity.h"

namespace entity {
    class ECFactory {
    public:
        static Entity create_player(Entity e);
        static Entity create_tree(Entity e);
    };
}

