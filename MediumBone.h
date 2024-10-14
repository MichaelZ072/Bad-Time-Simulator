#ifndef MEDIUMBONE_H
#define MEDIUMBONE_H

#include "Bones.h"

class MediumBone : public Bones {
    private:
        bool isWhite;
        bool colourSet;
        Vector2f soulPosChecker;
        
    public:
        // construct a medium bone using a set texture
        MediumBone() : Bones(0, 0, "assets/verticalBoneMedium.png") { 
            isWhite = true;
            colourSet = false;

            // default the soulPosChecker to (0, 0) until it is actually being used
            soulPosChecker.x = 0;
            soulPosChecker.y = 0;
        }

        // we will specify the speed of the attack and mode
        void callAttack(int speed, bool toggleBlue, int finalPosition) {
            // the colour of the sprite changes depending on the mode set
            if (!colourSet) {
                if (toggleBlue) {
                    bone.setColor(Color::Cyan);
                    isWhite = false;
                } else {
                    bone.setColor(Color::White);
                    isWhite = true;
                }
                // after the colour has been set we do not need to reset it
                colourSet = true;
            }

            // end the attack after it reaches/goes past finalPosition
            switch (moveDirection)
            {
            case 0: // moving up case
                if (bone.getPosition().y < finalPosition) {
                    isActive = false;
                    used = true;
                }
                break;
            case 1: // right case
                if (bone.getPosition().x > finalPosition) {
                    isActive = false;
                    used = true;
                }
                break;
            case 2: // down case
                if (bone.getPosition().y > finalPosition) {
                    isActive = false;
                    used = true;
                }
                break;
            case 3: // left case
                if (bone.getPosition().x < finalPosition) {
                    isActive = false;
                    used = true;
                }
                break;
            default:
                if (bone.getPosition().y < finalPosition) {
                    isActive = false;
                    used = true;
                }
                break;
            }

            // the bone moves depending on the give speed and spawned direction
            move(speed, moveDirection);
        }

        // returns true if player is moving
        bool checkPlayerMovement(Soul* soul) {
            // firstly update the position checker if the soul's position does not match it 
            if (soulPosChecker != soul->getPosition()) {
                // if there was a change in position checker, return true
                soulPosChecker = soul->getPosition();
                return true;

            // don't need to update position checker if soul is not moving
            } else {
                // so we therefore return false
                return false; 
            }
        }

        // modified check collision function as this bone has various colours
        void checkCollision(Soul* soul) {
            // do not check for collision if bone isn't active
            if (!isActive) {
                return;
            }

            switch (isWhite) {
            // normal collision detect for a white bone using basic collision checker
            case 1:
                if (soul->getSoulBounds().intersects(bone.getGlobalBounds())) {
                    soul->doDamage(1, 6);
                } else {
                    // if there is no collision, update the soul's position checker
                    soulPosChecker = soul->getPosition();
                }
                break;
            
            // alternate collision detect for a blue bone using basic collision checker combined with movement checker
            case 0:
                if ((soul->getSoulBounds().intersects(bone.getGlobalBounds())) && checkPlayerMovement(soul)) {
                    soul->doDamage(1, 6);
                } else {
                    // if there is no collision, update the soul's position checker
                    soulPosChecker = soul->getPosition();
                }
                break;
            }
        }

        Vector2f getSoulPosChecker() { return soulPosChecker; }

        bool getIsWhite() { return isWhite; }
        void setIsWhite(bool isWhite) { this->isWhite = isWhite; }

        ~MediumBone() {
            ;
        }
};

#endif