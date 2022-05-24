#ifndef POTTER_H
#define POTTER_H

#include "Moving.h"

namespace Game {
    class Potter : public Moving {
    public:
        Potter(position pos, vector<string>* levelMap);
        char getCharRepresentation() override { return POTTER; } 
    private:
        direction chooseDirection() override;
    };
}
#endif
