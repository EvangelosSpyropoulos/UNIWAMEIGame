#include "SharedGameUtils.h"

namespace Game{
    position directionToPosition(position pos, direction dir) {
        switch (dir) {
            case north:
                return position {pos.x, pos.y - 1};
            case south:
                return position {pos.x, pos.y + 1};
            case west:
                return position {pos.x - 1, pos.y};
            case east:
                return position {pos.x + 1, pos.y};
            case stay:
                return position {pos.x, pos.y};
            default:
                return position {0, 0};
        }
    }
}
