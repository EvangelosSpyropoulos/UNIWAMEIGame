#include "Moving.h"

namespace Game {
    Moving::Moving(position pos, vector<string>* levelMap) {
        currentPosition = pos;
        this->levelMap = levelMap;
    }
    
    direction Moving::move() {
        direction directionToMove;
        do {
            directionToMove = chooseDirection();
        } while (canMove(directionToMove) == false);
        return directionToMove;
    }
    
    direction Moving::move(position targetPosition) {
        this->targetPosition = targetPosition;
        return move();
    }
    
    bool Moving::canMove(direction proposedDirection) {
        if (proposedDirection == undefined) { return false; }
        position newPosition = directionToPosition(currentPosition, proposedDirection);
        
        return ((*levelMap)[newPosition.y][newPosition.x] != WALL);
    }
    
    Moving::~Moving() {}
}
