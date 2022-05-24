#include "Potter.h"

#include <ncurses.h>

namespace Game{
        
    Potter::Potter(position pos, vector<string>* levelMap) 
        : Moving(pos, levelMap) {}
        
    direction Potter::chooseDirection() {
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                return north;
            case KEY_DOWN:
                return south;
            case KEY_LEFT:
                return west;
            case KEY_RIGHT:
                return east;
            case ERR:
                return stay;
            default:
                return undefined;
        }
    }
}
