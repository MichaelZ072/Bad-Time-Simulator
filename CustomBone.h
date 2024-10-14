#ifndef CUSTOMBONE_H
#define CUSTOMBONE_H

#include "Bones.h"

class CustomBone : public Bones {
    private:
        int boneHeight;
        
        bool toggleTop;
        bool toggleBottom;

        RectangleShape body;
        Vector2f bodySize;
        double verticalBodyOffset;

        Texture boneAddonTexture;
        Sprite boneAddon;
        double verticalAddonOffset;

    public:
        CustomBone(int height) : Bones(0, 0, "assets/boneBottom.png") {
            boneHeight = height;
            bodySize.x = boneTextureSize.x - 4;
            bodySize.y = boneHeight;
            
            // custom bone is made of three sprites, we set the bone as the bottom sprite, the body as the middle, and the boneAddon as the top
            body.setSize(bodySize);
            body.setFillColor(Color::White);
            body.setOrigin(bodySize.x / 2, bodySize.y / 2);
            verticalBodyOffset = - (boneHeight / 2.0f) - (boneTextureSize.y / 2);
            body.setPosition(0, verticalBodyOffset);

            // for boneAddon
            // load texture
            boneAddonTexture.loadFromFile("assets/boneTop.png");
            // create sprite from texture
            boneAddon.setTexture(boneAddonTexture);
            Vector2u addonSize = boneAddonTexture.getSize();
            boneAddon.setOrigin(addonSize.x / 2.0f, addonSize.y / 2.0f);
            verticalAddonOffset = - (addonSize.y / 2.0f) - boneHeight - (boneTextureSize.y / 2);
            boneAddon.setPosition(0, verticalAddonOffset);

            isActive = false;
            toggleTop = true;
            toggleBottom = true;
        }

        void draw(RenderWindow *win) {
            if (!isActive) {
                return;
            } 

            // only draw the endParts of the bone if they are toggled
            if (toggleTop) {
                win->draw(boneAddon);
            }

            win->draw(body);
            
            if (toggleBottom) {
                win->draw(bone);
            }   
        }

        // move all bone components a certain speed and direction
        void move(int speed, int direction) {
            // define direction of movement based on corner
            switch (direction)
            {
            case 0: // move up
                boneAddon.move(0, -speed);
                body.move(0, -speed); 
                bone.move(0, -speed);
                break;
            case 1: // move right
                boneAddon.move(speed, 0);
                body.move(speed, 0); 
                bone.move(speed, 0);
                break;
            case 2: // move down
                boneAddon.move(0, speed);
                body.move(0, speed); 
                bone.move(0, speed);
                break;
            case 3: // move left
                boneAddon.move(-speed, 0);
                body.move(-speed, 0); 
                bone.move(-speed, 0);
                break;
            default: // else move upwards as default
                boneAddon.move(0, -speed);
                body.move(0, -speed); 
                bone.move(0, -speed);
                break;
            }
        }

        // we will specify the speed of the attack and show bone components
        void callAttack(int speed, bool showTop, bool showBottom, int finalPosition) {
            // update bone components
            toggleTop = showTop;
            toggleBottom = showBottom;

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

        // set up and configurate initial position of all bone components
        void spawn(Vector2f setPosition, int setRotation, int setDirection) {
            boneAddon.setRotation(setRotation);
            body.setRotation(setRotation);
            bone.setRotation(setRotation);
            
            // perform offsett depending on rotational value
            if (setRotation == 0 || (setRotation % 180 == 0)) { // if bone is still vertical
                boneAddon.setPosition(setPosition.x, setPosition.y + verticalAddonOffset);
                body.setPosition(setPosition.x, setPosition.y + verticalBodyOffset);
                bone.setPosition(setPosition.x, setPosition.y);
            } else { // if bone is horizontal apply offsett in x direction
                boneAddon.setPosition(setPosition.x  + verticalAddonOffset, setPosition.y);
                body.setPosition(setPosition.x + verticalBodyOffset, setPosition.y);
                bone.setPosition(setPosition.x, setPosition.y);
            }

            bone.setPosition(setPosition.x, setPosition.y);
            moveDirection = setDirection;
            isActive = true;  
        }

        void checkCollision(Soul *soul) {
            // do not check for collision if bone isn't active
            if (!isActive) {
                return;
            }

            // a simple collision detector based on the intersection of all sprite
            if (soul->getSoulBounds().intersects(boneAddon.getGlobalBounds())  
                || soul->getSoulBounds().intersects(body.getGlobalBounds())   
                || soul->getSoulBounds().intersects(bone.getGlobalBounds())) {
                soul->doDamage(1, 6);
            } else {
                return;
            }
        }
};

#endif