#include "entity.h"

namespace entity {
    class ECFactory {
    public:
        static Entity create_player();
        static Entity create_tree();
    };
}

