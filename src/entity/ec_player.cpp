#include "ec_player.h"

#include "transform.h"

namespace entity {
    Entity ECPlayer::create(Entity e) const {
        e.add(Transform());

        return e;
    }
}
