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
        bool isAlive;
    public:
        Soul(Board* board, int setMaxHealth, float setSpeed, int setMaxHeight) {
            maxHealth = setMaxHealth;
            health = maxHealth;
            karma = 0;
            speedRed = setSpeed;
            maxHeight = setMaxHeight;
            isRed = true;
            isAlive = true;

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

        // Returns the current health
        int getHealth() {return health;}

        // Returns the amount of karma
        int getKarma() {return karma;}

        // Adds health to the player up to the max - karma
        void heal(int addHealth) {
            health += addHealth;

            if (health + karma > maxHealth) {
                health = maxHealth - karma;
            }
        }

        // Deals with changing values to do with damage
        void doDamage(int damage, int addKarma) {
            if (health > 1) {
                health -= damage;
                karma += addKarma;
            } else if (health == 1 && karma == 0) {
                isAlive = false;
            } else if (health == 1) {
                karma -= damage;
            }

            cout << health << endl;
        } 

        void updateHealth() {

        }

        // Teleports the soul to the specified location
        void changePosition(Vector2f newPosition) {
            position = newPosition;
            soul.setPosition(position);
        }

        Vector2f getPosition() {return soul.getPosition();}

        FloatRect getSoulBounds() {
            FloatRect soulBounds = soul.getGlobalBounds();
            // Reducing the hitbox by 6 on all sides
            soulBounds.left += 6;
            soulBounds.top += 6;
            soulBounds.width -= 12;
            soulBounds.height -= 12;
            
            return soulBounds;
        }

        // Draws the soul
        void draw(RenderWindow* window) {
            window->draw(soul);
        }

        ~Soul() {
            ;
        }

};

#endif