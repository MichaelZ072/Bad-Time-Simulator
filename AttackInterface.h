#ifndef ATTACKINTERFACE_H
#define ATTACKINTERFACE_H

#include "Soul.h"

class AttackInterface {
    public:
        virtual bool checkCollision(Soul* player) = 0;
};

#endif