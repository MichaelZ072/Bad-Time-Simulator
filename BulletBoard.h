#ifndef BULLETBOARD_H
#define BULLETBOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

class Board {
    private:
        RectangleShape board;
        Vector2f size; // Red Soul = (160,160), Blue Soul = (0,0), Intermission = (570,130)
        Vector2f position; // Red Soul = (winSizeX / 2, winSizeY * 64 / 100), Blue Soul = (Same,+15), Intermission (Same,Same)
        float thickness;
        Vector2f newSize;
        Vector2f newPos;
        Vector2f velocitySize;
        Vector2f velocityPos;
        bool inAnimation;
    public:
        Board(int winSizeX, int winSizeY, float setThickness){
            size.x = 160;
            size.y = 160;
            position.x = winSizeX / 2;
            position.y = winSizeY * 64 / 100;
            thickness = setThickness;
            inAnimation = false;

            // Setting the parameters of the board based on what was passed
            board.setSize(size);
            board.setFillColor(Color::Transparent);
            board.setOutlineColor(Color::White);
            board.setOutlineThickness(thickness);
            board.setOrigin(Vector2f(size.x / 2, size.y / 2));
            board.setPosition(position);
        }

        // Check if the board is currently doing an animation
        bool checkAnimation() {return inAnimation;}

        // Change the bool to state the board is in an animation
        void startAnimation() {inAnimation = true;}

        // Change the bool to state the board is not in an animation
        void stopAnimation() {inAnimation = false;}

        // Changes the board to a new size and position through an animation
        void changeSize(Vector2f setNewSize, Vector2f setNewPos, int xSpeed, int ySpeed) {
            // Checks if the size passed is different to what current
            if (setNewSize.x != newSize.x || setNewSize.y != newSize.y) {
                newSize = setNewSize;
                velocitySize = newSize - size;
                velocitySize.x /= xSpeed;
                velocitySize.y /= ySpeed;
            }

            // Checks if the position passed is different to what current
            if (setNewPos.x != newPos.x || setNewPos.y != newPos.y) {
                newPos = setNewPos;
                velocityPos = newPos - position;
                velocityPos.x /= xSpeed;
                velocityPos.y /= ySpeed;
            }

            // These temporary variables are used to stop the board from overshooting its desired size
            float sizeDiffX = abs(newSize.x - size.x);
            float sizeSpeedX = abs(velocitySize.x);
            float sizeDiffY = abs(newSize.y - size.y);
            float sizeSpeedY = abs(velocitySize.y);

            // If the board is about to overshoot, set position to final size
            if (sizeDiffX <= sizeSpeedX) {
                size.x = newSize.x;
            }

            if (sizeDiffY <= sizeSpeedY) {
                size.y = newSize.y;
            }

            // Same but for position
            float distanceX = abs(newPos.x - position.x);
            float speedX = abs(velocityPos.x);
            float distanceY = abs(newPos.y - position.y);
            float speedY = abs(velocityPos.y);

            if (distanceX <= speedX) {
                position.x = newPos.x;
            }

            if (distanceY <= speedY) {
                position.y = newPos.y;
            }

            // If the height of the board is different, resize it
            if (size.x != newSize.x) {
                size.x += velocitySize.x;
                board.setSize(Vector2f(size.x, size.y));
            }

            // If the width of the board is different, resize it
            if (size.y != newSize.y) {
                size.y+= velocitySize.y;
                board.setSize(Vector2f(size.x, size.y));
            }

            // If the x coordinate is different, move it
            if (position.x != newPos.x) {
                position.x += velocityPos.x;
                board.setPosition(position.x, position.y);
            }

            // If the y coordinate is different, move it
            if (position.y != newPos.y) {
                position.y += velocityPos.y;
                board.setPosition(position.x, position.y);
            }

            // Checks if the current parameters match the new ones, and ends animation
            if (size == newSize && position == newPos) {
                inAnimation = false;
                Vector2f temp = board.getOrigin();
                board.setOrigin(size.x / 2, size.y / 2);
                board.move(board.getOrigin() - temp);
            }
        }

        // Change to red board
        void changeRed() {

        }

        // Change to blue board
        void changeBlue() {

        }

        // Change to intermission size from red board
        void changeIntermission1(int winSizeX, int winSizeY) {
            changeSize(Vector2f(570, 130),Vector2f(winSizeX / 2 - 205, winSizeY * 64 / 100 + 30), 14, 2);
        }

        // Change to intermission size from blue board
        void changeIntermission2() {

        }

        // Get the center of the board
        Vector2f getCenter() {
            return board.getPosition();
        }

        // Get the size of the board
        Vector2f getSize() {
            return board.getSize();
        }

        // Draw the board
        void draw(RenderWindow* window){
            window->draw(board);
        }
        
        ~Board(){
            ;
        }
};

#endif