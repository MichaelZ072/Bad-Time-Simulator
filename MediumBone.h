#ifndef MEDIUMBONE_H
#define MEDIUMBONE_H

#include "Bones.h"

class MediumBone : public Bones {
    private:
        bool isWhite;
        bool colourSet;
        Vector2f soulPosChecker;
        
        
    public:
        MediumBone(int x, int y, int boneSpeed, bool isWhite) : Bones(x, y, boneSpeed, "assets/verticalBoneMedium.png"), isWhite(isWhite), soulPosChecker(0, 0) 
        {
            // don't necessarily need this one anymore
            if (!isWhite) {
                bone.setColor(Color::Cyan);
            }

            colourSet = false;
        }

        void callAttack(int speed, bool toggleBlue) {
            if (!colourSet) {
                if (toggleBlue) {
                    bone.setColor(Color::Cyan);
                    isWhite = false;
                } else {
                    bone.setColor(Color::White);
                    isWhite = true;
                }
                colourSet = true;
            }

            move(speed, moveDirection);
        };

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