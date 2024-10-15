#ifndef SOUL_H
#define SOUL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletBoard.h"

using namespace sf;
using namespace std;

class Soul {
    private:
        Sprite soul;
        Texture redTexture;
        Texture blueTexture;
        Vector2f position;
        bool isRed;
        int maxHealth;
        int health;
        int karma;
        float speed;
        float velocityY;
        float gravity;
        float jumpVelocity;
        bool onGround;
        bool isJumping;
        bool upPressed;
        bool isAlive;
        int intermissionPositionCount;
        float throwVelocity;
        bool isThrown;
        int totalDamage;
    public:
        Soul(Board* board, int setMaxHealth) {
            // Setting soul parameters
            maxHealth = setMaxHealth;
            health = maxHealth;
            karma = 0;
            isRed = true;
            isAlive = true;
            totalDamage = 0;

            // Setting movement parameters
            speed = 5;
            velocityY = 0;
            gravity = 0.4;
            jumpVelocity = -8;
            onGround = false;
            isJumping = false;
            upPressed = false;
            throwVelocity = 16;
            isThrown = false;

            // Getting the textures
            redTexture.loadFromFile("assets/red_soul.png");
            blueTexture.loadFromFile("assets/blue_soul.png");

            // Creating the soul sprite
            position = board->getCenter();
            soul.setTexture(redTexture);
            soul.setOrigin(Vector2f(8,8));
            soul.setPosition(position);
        }

        bool isOnGround() {return onGround;}

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

        void upPress(bool setUpPress) {
            upPressed = setUpPress;
        }

        // Moves the soul according to the left arrow
        void moveLeft(Board* board){
            soul.setPosition(Vector2f(position.x -= speed, position.y));

            // Checks if the soul is within the board
            boundaryCheck(board);
        }

        // Moves the soul according to the right arrow
        void moveRight(Board* board){    
            soul.setPosition(Vector2f(position.x += speed, position.y));

            // Checks if the soul is within the board
            boundaryCheck(board);
        }

        // Moves the soul according to the up arrow
        void moveUp(Board* board) {
            if (isRed) { // Moves the soul according to the state
                soul.setPosition(Vector2f(position.x, position.y -= speed));
                // Checks if the soul is within the board
                boundaryCheck(board);
            } else {
                if (onGround) {
                    velocityY = jumpVelocity;
                    onGround = false;
                    isJumping = true;
                }
            }
        }

        // Moves the soul according to the down arrow
        void moveDown(Board* board){
            if (isRed) { // Moves the soul according to the state
                soul.setPosition(Vector2f(position.x, position.y += speed));
                // Checks if the soul is within the board
                boundaryCheck(board);
            }
        }

        void throwToBottom() {
            velocityY = throwVelocity; 
            isThrown = true;
        }

        void update(Board* board) { // , vector<FloatRect> bounds
            if (!isRed) {
                if (!onGround) {
                    // Apply gravity
                    velocityY += gravity;
                }

                // Check if the player has released the up arrow during a jump
                if (isJumping && !upPressed && velocityY < 0) {
                    velocityY = -0.8;
                    isJumping = false;
                }

                // Update position
                position.y += velocityY;
                soul.setPosition(position);

                onGround = false;

                // FloatRect soulBounds = soul.getGlobalBounds();

                // Iterate through platform bounds
                /*for (const auto& bound : bounds) {
                    // Only checking when soul is moving downwards
                    if (velocityY > 0) {
                        // Checks if soul is intersecting
                        if (soulBounds.intersects(bound)) {
                            float previousSoulBottom = soulBounds.top + soulBounds.height - velocityY;

                             if (previousSoulBottom <= bound.top) {
                                // Land on platform
                                position.y = bound.top - soul.getOrigin().y;
                                soul.setPosition(position);
                                velocityY = 0;
                                onGround = true;
                                isJumping = false;
                                break; // Stop checking other platforms
                            }
                        }
                    }
                }*/

                boundaryCheck(board);
            }
        }

        void boundaryCheck(Board* board) {
            // Gets the bounds for the soul and board
            FloatRect soulBounds = soul.getGlobalBounds();
            FloatRect boardBounds(board->getBounds().left + board->getThickness(), 
                board->getBounds().top + board->getThickness(), 
                board->getBounds().width - board->getThickness() * 2, 
                board->getBounds().height - board->getThickness() * 2);

            // Checks if the soul is on the boundary of the board, and then stops it
            // Left boundary
            if (soulBounds.left < boardBounds.left) {
                position.x = boardBounds.left + soul.getOrigin().x;
                soul.setPosition(position);
            }

            // Right boundary
            if (soulBounds.left + soulBounds.width > boardBounds.left + boardBounds.width) {
                position.x = boardBounds.left + boardBounds.width - soul.getOrigin().x;
                soul.setPosition(position);
            }

            if (isRed) {
                // Top boundary
                if (soulBounds.top < boardBounds.top) {
                    position.y = boardBounds.top + soul.getOrigin().y;
                    soul.setPosition(position);
                }

                // Bottom boundary
                if (soulBounds.top + soulBounds.height > boardBounds.top + boardBounds.height) {
                    position.y = boardBounds.top + boardBounds.height - soul.getOrigin().y;
                    soul.setPosition(position);
                }
            } else {
                // Ground collision
                if (soulBounds.top + soulBounds.height >= boardBounds.top + boardBounds.height) {
                    position.y = boardBounds.top + boardBounds.height - soul.getOrigin().y;
                    soul.setPosition(position);
                    velocityY = 0;
                    onGround = true;
                    isJumping = false;
                    isThrown = false;
                } else if (!onGround) {
                    onGround = false;
                }

                // Ceiling collision
                if (soulBounds.top <= boardBounds.top) {
                    position.y = boardBounds.top + soul.getOrigin().y;
                    soul.setPosition(position);
                    velocityY = 0;
                    isJumping = false;
                }
            }
        }

        // Moves the soul according to the left arrow intermission
        void intermissionMoveLeft() {
            intermissionPositionCount--;

            if (getIntermissionPositionCount() < 0) {
                intermissionPositionCount = 3;
            }
            switch (intermissionPositionCount) {
                case 0:
                    changePosition(Vector2f(47.5f, 450.0f));
                    intermissionPositionCount = 0;
                    break;
                case 1:
                    changePosition(Vector2f(197.5f, 450.0f));
                    intermissionPositionCount = 1;
                    break;
                case 2:
                    changePosition(Vector2f(357.5f, 450.0f));
                    intermissionPositionCount = 2;
                    break;
                case 3:
                    changePosition(Vector2f(507.5f, 450.0f));
                    intermissionPositionCount = 3;
                    break;
                default:
                    break;
            }
        }

        // Moves the soul according to the right arrow intermission
        void intermissionMoveRight() {
            intermissionPositionCount++;

            if (getIntermissionPositionCount() > 3) {
                intermissionPositionCount = 0;
            }

            switch (intermissionPositionCount) {
                case 0:
                    changePosition(Vector2f(47.5f, 450.0f));
                    intermissionPositionCount = 0;
                    break;
                case 1:
                    changePosition(Vector2f(197.5f, 450.0f));
                    intermissionPositionCount = 1;
                    break;
                case 2:
                    changePosition(Vector2f(357.5f, 450.0f));
                    intermissionPositionCount = 2;
                    break;
                case 3:
                    changePosition(Vector2f(507.5f, 450.0f));
                    intermissionPositionCount = 3;
                    break;
                default:
                    break;
            }
        }

        int getIntermissionPositionCount() {return intermissionPositionCount;}

        void selectActionPosition(){
            changePosition(Vector2f(60,285));
        }

        void returnActionPosition(int count) {
            switch (count) {
                case 0:
                    changePosition(Vector2f(47.5f,450.0f));
                    cout<<"change poition occured" << endl;
                    break;
                case 1:
                    changePosition(Vector2f(197.5f, 450.0f));
                    cout<<"change poition occured" << endl;
                    break;
                case 2:
                    changePosition(Vector2f(357.5f, 450.0f));
                    cout<<"change poition occured" << endl;
                    break;
                case 3:
                    changePosition(Vector2f(507.5f, 450.0f));
                    cout<<"change poition occured" << endl;
                    break;
            
            default:
                break;
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

            if(health>=92){
                health = 92;
            }

            //if (health + karma > maxHealth) {
            //    health = maxHealth - karma;
            //}
        }

        // Deals with changing values to do with damage
        void doDamage(int damage, int addKarma) {
            /*if (health > 1) {
                health -= damage;
                karma += addKarma;
            } else if (health == 1 && karma == 0) {
                isAlive = false;
            } else if (health == 1) {
                karma -= damage;
            }*/

            if (health > 0) {
                health -= damage * 2;
                totalDamage += damage * 2;
            } else {
                isAlive = false;
            }
            cout << health << endl;
            karma = addKarma;
        } 

        int totalDamageTaken() {return totalDamage;}

        // Returns if the soul is alive or dead
        bool getAlive() {return isAlive;}

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