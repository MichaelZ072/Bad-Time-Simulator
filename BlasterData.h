#ifndef BLASTERDATA_H
#define BLASTERDATA_H

#include "GasterBlasters.h"

class BlasterData { // This class is used to store all the data for the attack level classes,
    public:         // to make it more organised and reduce the number of vectors needed
        GasterBlasters* gasterBlaster;
        Vector2f initialPosition;
        Vector2f scale;
        float initialRotation;
        Vector2f finalPosition;
        float speed;
        float finalRotation;
        int rotDirection;
        unsigned int deltaFrames;

        BlasterData(Vector2f setInitialPosition, Vector2f setScale, float setInitialRotation, 
                    Vector2f setFinalPosition, float setSpeed, float setRotation, int setRotDirection) {
            initialPosition = setInitialPosition;
            scale = setScale;
            initialRotation = setInitialRotation;
            finalPosition = setFinalPosition;
            speed = setSpeed;
            finalRotation = setRotation;
            rotDirection = setRotDirection;
            deltaFrames = 0;
            
            gasterBlaster = new GasterBlasters(initialPosition, scale, initialRotation);
        }

        ~BlasterData() {

        }
};

#endif