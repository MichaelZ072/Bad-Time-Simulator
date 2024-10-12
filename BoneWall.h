#ifndef BONEWALL_H
#define BONEWALL_H

#include "Bones.h"

class BoneWall {
    private:
        bool isHorizontal;
        bool showIndicator;

        RectangleShape indicator;
        Vector2f indicatorSize;
        Vector2f indicatorPosition;

    public:
        void spawn(Vector2f setPosition, float setRotation);

};

#endif