#ifndef COVER_H
#define COVER_H

#include <SFML/Graphics.hpp>
#include "BulletBoard.h"

class Cover {
    private:
        RectangleShape upperShade;
        Vector2f upperShadeSize;

        RectangleShape rightShade;
        Vector2f rightShadeSize;

        RectangleShape bottomShade;
        Vector2f bottomShadeSize;

        RectangleShape leftShade;
        Vector2f leftShadeSize;

        bool isOn;

        Vector2f center;
        Vector2f unshadedSize;

        Vector2f windowSize;
        

    public:
        Cover(Board* board, int winSizeX, int winSizeY) {        
            unshadedSize = board->getSize();
            center = board->getCenter();

            windowSize.x = winSizeX;
            windowSize.y = winSizeY;

            Color shadeColour = Color::Blue;
            
            // upper shade
            upperShadeSize.x = windowSize.x;
            upperShadeSize.y = abs(center.y - unshadedSize.y / 2.0f);
            upperShade.setFillColor(shadeColour);
            upperShade.setSize(upperShadeSize);
            upperShade.setOrigin(upperShadeSize.x / 2.0f, upperShadeSize.y / 2.0f);
            upperShade.setPosition(windowSize.x / 2.0f, upperShadeSize.y / 2.0f);
            
            // right shade
            rightShadeSize.x = abs(windowSize.x - center.x - unshadedSize.x / 2.0f);
            rightShadeSize.y = windowSize.y;
            rightShade.setFillColor(shadeColour);
            rightShade.setSize(rightShadeSize);
            rightShade.setOrigin(rightShadeSize.x / 2.0f, rightShadeSize.y / 2.0f);
            rightShade.setPosition(windowSize.x - rightShadeSize.x / 2.0f, windowSize.y / 2.0f);

            // bottom shade
            bottomShadeSize.x = windowSize.x;
            bottomShadeSize.y = abs(windowSize.y - center.y - unshadedSize.y / 2.0f);
            bottomShade.setFillColor(shadeColour);
            bottomShade.setSize(bottomShadeSize);
            bottomShade.setOrigin(bottomShadeSize.x / 2.0f, bottomShadeSize.y / 2.0f);
            bottomShade.setPosition(windowSize.x / 2.0f, windowSize.y - bottomShadeSize.y / 2.0f);

            // left shade
            leftShadeSize.x = abs(center.x - unshadedSize.x / 2.0f);
            leftShadeSize.y = windowSize.y;
            leftShade.setFillColor(shadeColour);
            leftShade.setSize(leftShadeSize);
            leftShade.setOrigin(leftShadeSize.x / 2.0f, leftShadeSize.y / 2.0f);
            leftShade.setPosition(leftShadeSize.x / 2.0f, windowSize.y / 2.0f);

            isOn = true;
        };

        void toggleOn() { isOn = true; }
        void toggleOff() { isOn = false; }

        void updateCover(Board* board) {
            if (board->getSize() != unshadedSize || board->getCenter() != center) {
                unshadedSize = board->getSize();
                center = board->getCenter();

                Color shadeColour = Color::Blue;
                
                // upper shade
                upperShadeSize.x = windowSize.x;
                upperShadeSize.y = abs(center.y - unshadedSize.y / 2.0f);
                upperShade.setFillColor(shadeColour);
                upperShade.setSize(upperShadeSize);
                upperShade.setOrigin(upperShadeSize.x / 2.0f, upperShadeSize.y / 2.0f);
                upperShade.setPosition(windowSize.x / 2.0f, upperShadeSize.y / 2.0f);
                
                // right shade
                rightShadeSize.x = abs(windowSize.x - center.x - unshadedSize.x / 2.0f);
                rightShadeSize.y = windowSize.y;
                rightShade.setFillColor(shadeColour);
                rightShade.setSize(rightShadeSize);
                rightShade.setOrigin(rightShadeSize.x / 2.0f, rightShadeSize.y / 2.0f);
                rightShade.setPosition(windowSize.x - rightShadeSize.x / 2.0f, windowSize.y / 2.0f);

                // bottom shade
                bottomShadeSize.x = windowSize.x;
                bottomShadeSize.y = abs(windowSize.y - center.y - unshadedSize.y / 2.0f);
                bottomShade.setFillColor(shadeColour);
                bottomShade.setSize(bottomShadeSize);
                bottomShade.setOrigin(bottomShadeSize.x / 2.0f, bottomShadeSize.y / 2.0f);
                bottomShade.setPosition(windowSize.x / 2.0f, windowSize.y - bottomShadeSize.y / 2.0f);

                // left shade
                leftShadeSize.x = abs(center.x - unshadedSize.x / 2.0f);
                leftShadeSize.y = windowSize.y;
                leftShade.setFillColor(shadeColour);
                leftShade.setSize(leftShadeSize);
                leftShade.setOrigin(leftShadeSize.x / 2.0f, leftShadeSize.y / 2.0f);
                leftShade.setPosition(leftShadeSize.x / 2.0f, windowSize.y / 2.0f);
            }          
        }

        void draw(RenderWindow* win) {
            if (isOn) {
                win->draw(upperShade);
                win->draw(rightShade);
                win->draw(bottomShade);
                win->draw(leftShade);
            }
        };

        ~Cover(){
            ;
        }

};

#endif