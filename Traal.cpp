#include "Traal.h"

namespace Game{
    
    Traal::Traal(position pos, vector<string>* levelMap)
        : Moving(pos, levelMap) {}
    
    direction Traal::chooseDirection() {
        switch(rand() % 4) {
            case(0):
                return north;
            case(1):
                return south;
            case(2):
                return west;
            case(3):
                return east;
            default:
                return undefined;
        }
    }
}
