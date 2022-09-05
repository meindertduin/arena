#pragma once

#include "component.h"
#include <glm/glm.hpp>
#include "ec_transform.h"

namespace entity {
    struct ECCollisionBox : public Component<ECCollisionBox> {
        union {
            std::array<float, 6> points;
            struct {
                float min_x;
                float max_x;

                float min_y;
                float max_y;

                float min_z;
                float max_z;
            };
        };    

        ECCollisionBox() = default;

        ECCollisionBox(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z) 
            : min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), min_z(min_z), max_z(max_z) {  }

        ECCollisionBox(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z, const ECTransform &transform) 
            : min_x(transform.pos.x  + min_x), max_x(transform.pos.x + max_x), 
            min_y(transform.pos.y + min_y), max_y(transform.pos.y + max_y), 
            min_z(transform.pos.z + min_z), max_z(transform.pos.z + max_z) {  }

        constexpr bool is_inside(glm::vec3 point) {
            return min_x <= point.x && max_x >= point.x &&
                min_y <= point.y && max_y >= point.y &&
                min_z <= point.z && max_z >= point.z;
        }
    };

    DECL_COMPONENT_HEADER(ECCollisionBox);
}
