#ifndef LONGBONE_H
#define LONGBONE_H

#include "Bones.h"

class LongBone : public Bones {
    public:
        LongBone() : Bones(0, 0, "assets/verticalBoneLong.png") { }

        void callAttack(int speed, int finalPosition) {
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
        
        ~LongBone() {
            ;
        }

};

#endif