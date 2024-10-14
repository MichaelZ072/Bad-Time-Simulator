#ifndef BONES_H
#define BONES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "AttackInterface.h"
#include "Soul.h"
#include "BulletBoard.h"

using namespace std;
using namespace sf;

class Bones : public AttackInterface {
    protected:
        bool isActive;
        int moveDirection; // 0: Up, 1: Right, 2: Down, 3: Left
        
        Texture boneTexture;
        Vector2u boneTextureSize;
        Sprite bone;

        bool used;
        
        // Vector2f bonePosition;
                
    public:
        Bones(int x, int y, string boneTextureFile) {
            moveDirection = 0;
            isActive = false;
            used = false;

            // load texture
            boneTexture.loadFromFile(boneTextureFile);
            // create sprite from texture
            bone.setTexture(boneTexture);

            // set sprite properties
            boneTextureSize = boneTexture.getSize();
            bone.setOrigin(boneTextureSize.x / 2.0f, boneTextureSize.y / 2.0f);
            bone.setPosition(x, y);
        }

        // basic check collision definition for bone class
        // virtual as some bones have a property which makes them blue, whereby the checkCollision function would need to be different
        virtual void checkCollision(Soul *soul) {
            // do not check for collision if bone isn't active
            if (!isActive) {
                return;
            }
            
            // a simple collision detector based on the intersection of sprite bounds
            if (soul->getSoulBounds().intersects(bone.getGlobalBounds())) {
                soul->doDamage(1, 6);
            } else {
                return;
            }
        }

        // set the bone to be active and set up original position, rotation, and direction of bone
        virtual void spawn(Vector2f setPosition, int setRotation, int setDirection) {
            bone.setRotation(setRotation);
            bone.setPosition(setPosition.x, setPosition.y);
            moveDirection = setDirection;
            isActive = true;  
        }

        // move the bone with a certain speed and direction
        virtual void move(int speed, int direction) {
            // define direction of movement based on corner
            switch (direction)
            {
            case 0: // move up
                bone.move(0, -speed);
                break;
            case 1: // move right
                bone.move(speed, 0);
                break;
            case 2: // move down
                bone.move(0, speed);
                break;
            case 3: // move left
                bone.move(-speed, 0);
                break;
            default: // else move upwards as default
                bone.move(0, -speed);
                break;
            }
        }

        // virtual as some bones are made of different components
        virtual void draw(RenderWindow *win) {
            if (!isActive) {
                return;
            } 
            win->draw(bone);
        }

        Vector2u getSize() {
            return boneTexture.getSize();
        }

        void setMoveDirection(int moveDirection) { this->moveDirection = moveDirection; }
        int getMoveDirection() { return moveDirection; }

        bool getIsActive() { return isActive; }
        void setIsActive(bool isActive) { this->isActive = isActive; }

        ~Bones() {
            ;
        }
};

#endif