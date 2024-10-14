/*
#include "LongBone.h"

// checks collision based on intersection of sprite boundaries
bool LongBone::checkCollision(Soul *soul)
{
    if (soul->getSprite().getGlobalBounds().intersects(bone.getGlobalBounds())) {
        return true;
    } else {
        return false;
    }
}

// used in combination with checkColision for blue bones (should only be called when player is touch the bone)
bool LongBone::checkPlayerMovement(Soul *soul)
{
    if (soulPosChecker != soul->getPosition()) {
        soulPosChecker = soul->getPosition(); // update position checker
        return true;
    } else {
        return false; // don't need to update position checker if soul is not moving
    }
}

bool LongBone::attackSoul(Soul *soul)
{
    switch (isWhite)
    {
    // white bone attack
    case 1:
        if (checkCollision(soul)) {
            return true;
        } else {
            return false;
        }
        break;
    
    // blue bone attack
    case 0:
        if (checkCollision(soul) && checkPlayerMovement(soul)) {
            return true;
        } else {
            return false;
        }
    }
}
*/