#ifndef GASTERBLASTERS_H
#define GASTERBLASTERS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "AttackInterface.h"
#include "BlasterBeams.h"
#include "Soul.h"

using namespace std;
using namespace sf;

class GasterBlasters : public AttackInterface {
    private:
        BlasterBeams* beam;
        Sprite blaster;
        Texture* texture;
        int currentTexture;
        Vector2f scale;
        Vector2u size;
        Vector2f position;
        Vector2f newPos;
        Vector2f velocity;
        Vector2f maxVelocity;
        Vector2f totDistance;
        float rotationVelocity;
        float maxRotVelocity;
        float rotation;
        float totRotation;
        float newRotation;
        bool inAnimation;
        bool flownIn;
        bool flownOut;
        bool fired;
        float deltaFrames;
    public:
        GasterBlasters(Vector2f setPosition, Vector2f setScale, float setRotation) {
            position = setPosition;
            scale = setScale;
            rotation = setRotation;
            texture = new Texture[6];
            currentTexture = 0;
            inAnimation = false;
            flownIn = false;
            flownOut = false;
            fired = false;

            // Using a for loop to load all the textures
            for (int i = 0; i < 6; i++) {
                string filename = "assets/gasterblaster_" + to_string(i) + ".png";
                texture[i].loadFromFile(filename);
            }

            blaster.setTexture(texture[currentTexture]);
            blaster.setScale(scale);
            size = texture[currentTexture].getSize();
            blaster.setOrigin(Vector2f(float(size.x) / 2, float(size.y) / 2));
            blaster.setPosition(position);
            blaster.setRotation(rotation);

            beam = new BlasterBeams(blaster, scale);
        }

        // Changes to the texture in the array specified by the iteration
        void changeTexture(int i) {
            currentTexture = i;
            blaster.setTexture(texture[currentTexture]);
            size = texture[currentTexture].getSize();
            Vector2f temp = blaster.getOrigin();
            blaster.setOrigin(Vector2f(float(size.x) / 2, float(size.y) / 2));
            blaster.move(blaster.getOrigin() - temp);
        }

        bool checkAnimation() {return inAnimation;}

        void startAnimation() {inAnimation = true;}

        void stopAnimation() {inAnimation = false;}

        bool checkFlownIn() {return flownIn;}

        bool checkFlownOut() {return flownOut;}

        bool checkFired() {return fired;}

        bool firing() {return beam->checkAnimation();}

        // Does the animation for the blaster flying in
        void flyIn(Vector2f setNewPos, float setSpeed, float setRotation, int setRotDirection) {
            // Checks if the rotation passed is different to what current
            if (setRotation != newRotation) {
                if (setRotDirection == 1) {
                    newRotation = setRotation;
                    totRotation = abs(newRotation - rotation);
                    maxRotVelocity = totRotation / setSpeed;
                    rotationVelocity = maxRotVelocity;
                } else if (setRotDirection == -1) {
                    newRotation = setRotation;
                    totRotation = 360 - abs(newRotation - rotation);
                    maxRotVelocity = (totRotation / setSpeed) * setRotDirection;
                    rotationVelocity = maxRotVelocity;
                }
                
            }

            // Checks if the position passed is different to what current
            if (setNewPos.x != newPos.x || setNewPos.y != newPos.y) {
                newPos = setNewPos;
                totDistance = newPos - position;
                maxVelocity.x = totDistance.x / setSpeed;
                maxVelocity.y = totDistance.y / setSpeed;
                velocity.x = maxVelocity.x;
                velocity.y = maxVelocity.y;
                totDistance.x = abs(totDistance.x);
                totDistance.y = abs(totDistance.y);
            }

            // These temporary variables are used to stop the blaster from overshooting the new position and rotation
            float rotationDiff = abs(newRotation - rotation);
            float distanceX = abs(newPos.x - position.x);
            float distanceY = abs(newPos.y - position.y);

            // This defines how far the blaster is through the animation
            float progressRot = rotationDiff / (totRotation / 2);
            float progressX = distanceX / (totDistance.x / 2);
            float progressY = distanceY / (totDistance.y / 2);

            if (progressRot < 0.05) {
                progressRot = 0.05;
            }

            if (progressRot > 1) {
                progressRot = 1;
            }

            if (progressX < 0.05) {
                progressX = 0.05;
            }

            if (progressX > 1) {
                progressX = 1;
            }

            if (progressY < 0.05) {
                progressY = 0.05;
            }

            if (progressY > 1) {
                progressY = 1;
            }

            // Applying the easing
            float easingRot = maxRotVelocity * progressRot;
            float easingX = maxVelocity.x * progressX;
            float easingY = maxVelocity.y * progressY;

            float rotationSpeed = abs((rotationVelocity / rotationVelocity) * easingRot);
            float speedX = abs((velocity.x / velocity.x) * easingX);
            float speedY = abs((velocity.y / velocity.y) * easingY);

            // If the blaster is about to overshoot, set position and/or rotation to final position 
            if (rotationDiff <= rotationSpeed) {
                rotation = newRotation;
            }

            if (distanceX <= speedX) {
                position.x = newPos.x;
            }

            if (distanceY <= speedY) {
                position.y = newPos.y;
            }

            // If the rotation is different, change it
            if (rotation != newRotation) {
                if (rotation >= 360) {   // Making sure it doesn't go over 360
                    rotation -= 360;
                } else if (rotation < 0) {
                    rotation += 360;    // Making sure it doesn't go under 360
                }
                rotation += (rotationSpeed / rotationSpeed) * easingRot;
                blaster.setRotation(rotation);
            } else {
                blaster.setRotation(rotation);
            }

            // If the x coordinate is different, move it
            if (position.x != newPos.x) {
                position.x += (velocity.x / velocity.x) * easingX;
                blaster.setPosition(position.x, position.y);
            } else {
                blaster.setPosition(position.x, position.y);
            }

            // If the y coordinate is different, move it
            if (position.y != newPos.y) {
                position.y += (velocity.y / velocity.y) * easingY;
                blaster.setPosition(position.x, position.y);
            } else {
                blaster.setPosition(position.x, position.y);
            }

            // Checks if the current parameters match the new ones, it ends
            if (rotation == newRotation && position == newPos) {
                flownIn = true;
            }
        }

        void flyOut(float maxSpeed, float maxFrames) {
            switch (currentTexture) {
                case 0:
                    changeTexture(1);
                    break;
                case 1:
                    changeTexture(2);
                    break;
                case 2:
                    changeTexture(3);
                    break;
                case 3:
                    changeTexture(4);
                    break;
                case 4:
                    changeTexture(5);
                    break;
                case 5:
                    changeTexture(4);
                    break;
                default:
                    changeTexture(0);
                    break;
            }

            if (currentTexture > 3) {
                beam->startAnimation();
            }

            if (beam->checkAnimation()) {
                beam->fire(blaster);

                float oppositeRotation;
                oppositeRotation = (blaster.getRotation()  - 90);

                if (oppositeRotation < 0) {
                    oppositeRotation += 360;
                }

                Vector2f direction;
                direction.x = cos(oppositeRotation * (3.14159265 / double(180))) * maxSpeed;
                direction.y = sin(oppositeRotation * (3.14159265 / double(180))) * maxSpeed;

                float t = deltaFrames / maxFrames;
                if (t < 0) {
                    t = 0;
                }
                
                if (t > 1) {
                    t = 1;
                }

                float speed = t * t;
                blaster.move(direction * speed);
                fired = beam->checkFired();
                deltaFrames++;
            }
        }

        // Returns the size of the blaster
        Vector2u getSize() {return texture[currentTexture].getSize();}

        // Returns the position of the blaster
        Vector2f getPosition() {return blaster.getPosition();}

        // Returns the origin of the blaster
        Vector2f getOrigin() {return blaster.getOrigin();}

        float getRotation() {return blaster.getRotation();}

        // Checks for collisions between the attacks and the player
        void checkCollision(Soul *soul) {
            if (!fired) {
                if (soul->getSoulBounds().intersects(beam->getGlobalBounds())) {
                    soul->doDamage(1,6);
                }
            }
        }

        // Draws the Gaster Blaster
        void draw(RenderWindow* window){
            if (inAnimation) {
                window->draw(blaster);
            }

            if (beam->checkAnimation()) {
                beam->draw(window);
            }
        }

        ~GasterBlasters() {

        }
};

#endif