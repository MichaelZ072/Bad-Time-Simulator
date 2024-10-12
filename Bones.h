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
        //bool isWhite;

        bool isActive;
        int boneSpeed;
        
        Texture boneTexture;
        Sprite bone;
        
        // Vector2f bonePosition;
        
        // 
        /*
        RectangleShape warningBox;
        Vector2f warningBoxSize;
        Vector2f warningBoxPosition;
        */
                              
    public:
        Bones(int x, int y, int boneSpeed, string boneTextureFile);
        Bones();

        // void setBoneSpeed(int boneSpeed) { this->boneSpeed = boneSpeed; }
        // bool getBoneSpeed() { return boneSpeed; }

        void spawn(Vector2f setPosition, float setRotation)
        {
            // spawn and set up original position of bone
            bone.setRotation(setRotation);
            bone.setPosition(setPosition.x, setPosition.y);
            isActive = true;  
        }

        /*
        void moveLeft(int speed);
        void moveRight(int speed);
        void moveUp(int speed);
        void moveDown(int speed);
        */

        void move(int speed, int direction);

        bool getIsActive() { return isActive; }
        void setIsActive(bool isActive) { this->isActive = isActive; }

        Vector2u getSize();

        virtual void draw(RenderWindow* win);

        ~Bones() {
            ;
        }
};

#endif