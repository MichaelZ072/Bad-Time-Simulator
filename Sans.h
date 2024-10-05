#ifndef SANS_H
#define SANS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class Sans 
{
    private:
        int health;
        bool isIdle;
        bool dodgeDirection; // 0 if left, 1 if right

        Texture headTexture;
        Sprite head;

        Texture bodyTexture;
        Sprite body;

        Texture legTexture;
        Sprite leg;

    public:
        Sans(int x, int y, int health, double scale, string headTextureFile, string bodyTextureFile, string legTextureFile);
        Sans();

        void draw(RenderWindow* win);

        void setHead(string texturefile);
        void setBody(string texturefile);
        void setLeg(string texturefile);

        Vector2f getHeadPosition() { return head.getPosition(); }
        Vector2f getBodyPosition() { return body.getPosition(); }
        Vector2f getLegPosition() { return leg.getPosition(); }
        
        void setIsIdle(bool isIdle) {this->isIdle = isIdle;}
        bool getIsIdle() { return isIdle; }


        void moveFull(double offsetX, double offsetY); // movement for sans entire body
        void dodge(double speed, double distance, double endPosition); // whereby sans will only dodge to the left

        ~Sans();
        
};

#endif