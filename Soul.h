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

            // Getting the textures
            redTexture.loadFromFile("assets/red_soul.png");
            blueTexture.loadFromFile("assets/blue_soul.png");

            // Creating the soul sprite
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
        void moveUp(Board* board) {
            if (isRed) {
                soul.setPosition(Vector2f(position.x, position.y -= speedRed));
            } else {

            }

            // Checks if the soul is within the board
            boundaryCheck(board);
        }

        // Moves the soul according to the down arrow
        void moveDown(Board* board){
            if (isRed) {
                soul.setPosition(Vector2f(position.x, position.y += speedRed));
            } else {

            }

            // Checks if the soul is within the board
            boundaryCheck(board);
        }

        // Moves the soul according to the left arrow
        void moveLeft(Board* board){
            if (isRed) {
                soul.setPosition(Vector2f(position.x -= speedRed, position.y));
            } else {

            }

            // Checks if the soul is within the board
            boundaryCheck(board);
        }

        // Moves the soul according to the right arrow
        void moveRight(Board* board){
            if (isRed) {
                soul.setPosition(Vector2f(position.x += speedRed, position.y));
            } else {

            }

            // Checks if the soul is within the board
            boundaryCheck(board);
        }

        void boundaryCheck(Board* board) {
            // Gets the bounds for the soul and board
            FloatRect soulBounds = soul.getGlobalBounds();
            FloatRect boardBounds(board->getBounds().left + board->getThickness(), 
                board->getBounds().top + board->getThickness(), 
                board->getBounds().width - board->getThickness() * 2, 
                board->getBounds().height - board->getThickness() * 2);

            // Checks if the soul is on the boundary of the board, and then stops it
            if (soulBounds.left < boardBounds.left) {
                soul.setPosition(Vector2f(position.x = boardBounds.left + soul.getOrigin().x, position.y));
            }

            if (soulBounds.top < boardBounds.top) {
                soul.setPosition(Vector2f(position.x, position.y = boardBounds.top + soul.getOrigin().y));
            }

            if (soulBounds.left + soulBounds.width > boardBounds.left + boardBounds.width) {
                soul.setPosition(Vector2f(position.x = boardBounds.left + boardBounds.width - soul.getOrigin().x, position.y));
            }

            if (soulBounds.top + soulBounds.height > boardBounds.top + boardBounds.height) {
                soul.setPosition(Vector2f(position.x, position.y = boardBounds.top + boardBounds.height - soul.getOrigin().y));
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
        } 

        // Used to update the health shown in the ui
        void updateHealth() {

        }

        // Teleports the soul to the specified location
        void changePosition(Vector2f newPosition) {
            position = newPosition;
            soul.setPosition(position);
        }

        // Gets the position of the soul
        Vector2f getPosition() {return soul.getPosition();}

        // Returns a modified version of the soul's global bounds to give a little grace during attacks
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
};

#endif