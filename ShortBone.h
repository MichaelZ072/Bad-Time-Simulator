#ifndef SHORTBONE_H
#define SHORTBONE_H

#include "Bones.h"

class ShortBone : public Bones {
    public:
        ShortBone(int x, int y, int boneSpeed) : Bones(x, y, boneSpeed, "assets/verticalBoneShort.png") { }
        
        bool checkCollision(Soul* soul) {
            if (soul->getSprite().getGlobalBounds().intersects(bone.getGlobalBounds())) {
                return true;
            } else {
                return false;
            }
        }
        
        ~ShortBone() {
            ;
        }      
};

#endif