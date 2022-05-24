#ifndef MOVING_H
#define MOVING_H

#include "SharedGameUtils.h"

namespace Game {
    class Moving {
    public:
        Moving(position pos, vector<string>* levelMap);
        virtual ~Moving();
        position getPosition() const { return currentPosition; }
        void setPosition(position newPosition) { currentPosition = newPosition; }
        
        direction move();
        direction move(position targetPosition);
        virtual char getCharRepresentation() = 0;
    protected:
        position currentPosition;
        position targetPosition;
        vector<string>* levelMap;
        
        virtual direction chooseDirection() = 0;
    private:
        bool canMove(direction proposedDirection);
    };
}
#endif
