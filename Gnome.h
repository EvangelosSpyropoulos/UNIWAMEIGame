#ifndef GNOME_H
#define GNOME_H

#include "Moving.h"

namespace Game {
    class Gnome : public Moving {
    public:
        Gnome(position pos, vector<string>* levelMap);
        char getCharRepresentation() override { return GNOME; }
    private:
        direction chooseDirection() override;
    };
}
#endif
