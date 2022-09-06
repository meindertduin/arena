#include "ec_collision_box.h"

namespace entity {
    DECL_COMPONENT_INIT(ECCollisionBox) {}

    ECCollisionBox::ECCollisionBox(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z) 
            : min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), min_z(min_z), max_z(max_z) {  }
}
