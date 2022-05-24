#ifndef TRAAL_H
#define TRAAL_H

#include "Moving.h"

namespace Game {
    class Traal : public Moving {
    public:
        Traal(position pos, vector<string>* levelMap);
        char getCharRepresentation() override { return TRAAL; } 
    private:
        direction chooseDirection() override;
    };
}
#endif
