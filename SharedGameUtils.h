#ifndef SHARED_GAME_UTILS_H
#define SHARED_GAME_UTILS_H

#include <vector>
#include <string>

using namespace std;

#define WALL '*'
#define CORRIDOR ' '
#define SCRIPT 'S'
#define GEM 'D'
#define POTTER 'P'
#define GNOME 'G'
#define TRAAL 'T'

namespace Game {
    
    enum direction {
        north,
        south,
        west,
        east,
        stay,
        undefined
    };
    
    typedef struct { int x,y; } position;
    
    position directionToPosition(position pos, direction dir);
}
#endif
