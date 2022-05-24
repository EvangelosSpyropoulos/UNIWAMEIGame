#include "Gnome.h"

namespace Game{
    
    Gnome::Gnome(position pos, vector<string>* levelMap)
        : Moving(pos, levelMap) {}
    
    direction Gnome::chooseDirection() {
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
