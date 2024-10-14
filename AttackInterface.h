#ifndef ATTACKINTERFACE_H
#define ATTACKINTERFACE_H

#include "Soul.h"

class AttackInterface {
    public:
        virtual void checkCollision(Soul* soul) = 0;
};

#endif