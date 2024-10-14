#ifndef ATTACKLEVELS_H
#define ATTACKLEVELS_H

#include <SFML/Graphics.hpp>
#include "Soul.h"

class AttackLevels {
    public:
        AttackLevels() = default;
        virtual ~AttackLevels() = default;
        virtual bool checkAttack() = 0;
        virtual void startAttack() = 0;
        virtual void attack(Soul* soul) = 0;
        virtual void draw(RenderWindow* window) = 0;
};

#endif