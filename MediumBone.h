#ifndef MEDIUMBONE_H
#define MEDIUMBONE_H

#include "Bones.h"

class MediumBone : public Bones {
    private:
        bool isWhite;
        Vector2f soulPosChecker;
        
    public:
        MediumBone(int x, int y, int boneSpeed, bool isWhite) : Bones(x, y, boneSpeed, "assets/verticalBoneMedium.png"), isWhite(isWhite), soulPosChecker(0, 0) 
        {
            if (!isWhite) {
                bone.setColor(Color::Cyan);
            }
        }

        bool checkCollision(Soul* soul);
        bool checkPlayerMovement(Soul* soul);
        bool attackSoul(Soul* soul);
        
        Vector2f getSoulPosChecker() { return soulPosChecker; }

        bool getIsWhite() { return isWhite; }
        void setIsWhite(bool isWhite) { this->isWhite = isWhite; }

        ~MediumBone() {
            ;
        }
};

#endif