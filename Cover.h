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
        

    public:
        Cover(Board* board, int winSizeX, int winSizeY) {
            unshadedSize = board->getSize();
            center = board->getCenter();

            // upper shade
            upperShadeSize.x = winSizeX;
            upperShadeSize.y = abs(center.y - unshadedSize.y / 2.0f);
            upperShade.setFillColor(Color::Blue);
            upperShade.setSize(upperShadeSize);
            upperShade.setOrigin(upperShadeSize.x / 2.0f, upperShadeSize.y / 2.0f);
            upperShade.setPosition(winSizeX / 2.0f, upperShadeSize.y / 2.0f);
            
            // right shade
            rightShadeSize.x = abs(winSizeX - center.x - unshadedSize.x / 2.0f);
            rightShadeSize.y = winSizeY;
            rightShade.setFillColor(Color::Blue);
            rightShade.setSize(rightShadeSize);
            rightShade.setOrigin(rightShadeSize.x / 2.0f, rightShadeSize.y / 2.0f);
            rightShade.setPosition(winSizeX - rightShadeSize.x / 2.0f, winSizeY / 2.0f);

            // bottom shade
            bottomShadeSize.x = winSizeX;
            bottomShadeSize.y = abs(winSizeY - center.y - unshadedSize.y / 2.0f);
            bottomShade.setFillColor(Color::Blue);
            bottomShade.setSize(bottomShadeSize);
            bottomShade.setOrigin(bottomShadeSize.x / 2.0f, bottomShadeSize.y / 2.0f);
            bottomShade.setPosition(winSizeX / 2.0f, winSizeY - bottomShadeSize.y / 2.0f);

            // left shade
            leftShadeSize.x = abs(center.x - unshadedSize.x / 2.0f);
            leftShadeSize.y = winSizeY;
            leftShade.setFillColor(Color::Blue);
            leftShade.setSize(leftShadeSize);
            leftShade.setOrigin(leftShadeSize.x / 2.0f, leftShadeSize.y / 2.0f);
            leftShade.setPosition(leftShadeSize.x / 2.0f, winSizeY / 2.0f);
            
            isOn = true;
        };

        void toggleOn() { isOn = true; }
        void toggleOff() { isOn = false; }

        void updateCover(Board* board) {
            ;
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