#ifndef SOUL_H
#define SOUL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletBoard.h"

using namespace sf;
using namespace std;

class Soul {
    private:
        Sprite soul;
        Texture redTexture;
        Texture blueTexture;
        bool isRed;
        int maxHealth;
        int health;
        int karma;
        float speedRed;
        float speedBlue;
        int maxHeight;
        Vector2f gravity;
        Vector2f position;
    public:
        Soul(Board* board, int setMaxHealth, float setSpeed, int setMaxHeight) {
            maxHealth = setMaxHealth;
            health = maxHealth;
            karma = 0;
            speedRed = setSpeed;
            maxHeight = setMaxHeight;
            isRed = true;

            redTexture.loadFromFile("assets/red_soul.png");
            blueTexture.loadFromFile("assets/blue_soul.png");

            position = board->getCenter();

            soul.setTexture(redTexture);
            soul.setOrigin(Vector2f(8,8));
            soul.setPosition(position);
        }

        // Returns whether the soul is red or not
        bool soulColor() {return isRed;}

        // Changes the soul to the red variant
        void makeRed() {
            soul.setTexture(redTexture);
            isRed = true;
        }

        // Changes the soul to the blue variant
        void makeBlue() {
            soul.setTexture(blueTexture);
            isRed = false;
        }

        // Moves the soul according to the up arrow
        void moveUp() {
            if (isRed) {
                soul.move(Vector2f(0,-speedRed));
            } else {

            }
        }

        // Moves the soul according to the down arrow
        void moveDown(){
            if (isRed) {
                soul.move(Vector2f(0,speedRed));
            } else {

            }
        }

        // Moves the soul according to the left arrow
        void moveLeft(){
            if (isRed) {
                soul.move(Vector2f(-speedRed,0));
            } else {

            }
        }

        // Moves the soul according to the right arrow
        void moveRight(){
            if (isRed) {
                soul.move(Vector2f(speedRed,0));
            } else {

            }
        }

        // Returns the max health
        int getMaxHealth() {return maxHealth;}

        // Adds health to the player up to the max - karma
        void heal(int addHealth) {
            health += addHealth;

            if (health + karma > maxHealth) {
                health = maxHealth - karma;
            }
        }

        // Returns the current health
        int getHealth() {return health;}

        // Deals with changing values to do with damage
        void doDamage() {
            
        } 

        // Returns the amount of karma
        int getKarma() {return karma;}

        // Teleports the soul to the specified location
        void changePosition(Vector2f newPosition) {
            position = newPosition;
            soul.setPosition(position);
        }

        Vector2f getPosition() {return soul.getPosition();}

        // Draws the soul
        void draw(RenderWindow* window) {
            window->draw(soul);
        }

        ~Soul() {
            ;
        }

};

#endif