#include "octree.h"

#include "collision.h"

namespace physics {
    glm::vec3 create_octal_center(OctalPart part, const glm::vec3 &center, float quarter_size) {
        switch (part) {
            case LeftUpperFurthest:
                return { center.x - quarter_size, center.y + quarter_size, center.z + quarter_size };
            case RightUpperFurthest:
                return { center.x + quarter_size, center.y + quarter_size, center.z + quarter_size };
            case LeftLowerFurthest:
                return { center.x - quarter_size, center.y - quarter_size, center.z + quarter_size };
            case RightLowerFurthest:
                return { center.x + quarter_size, center.y - quarter_size, center.z + quarter_size };
            case LeftUpperClosest:
                return { center.x - quarter_size, center.y + quarter_size, center.z - quarter_size };
            case RightUpperClosest:
                return { center.x + quarter_size, center.y + quarter_size, center.z - quarter_size };
            case LeftLowerClosest:
                return { center.x - quarter_size, center.y - quarter_size, center.z - quarter_size };
            case RightLowerClosest:
                return { center.x + quarter_size, center.y - quarter_size, center.z - quarter_size };
        }
    }

    int get_max_layer(float smallest_half, int max_layer, float grid_size) {
        if (smallest_half > grid_size) {
            max_layer--;
            grid_size*= 2;
            get_max_layer(smallest_half, max_layer, grid_size);
        }

        return max_layer;
    }
}