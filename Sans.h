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

        Texture speechBubbleTexture;
        Sprite speechBubble;

        Font font;
        Text text;
        string dialogueString;

        Clock clock;
        Time time;

        double dodgeSpeed = 7;
        double waitTime = 1;

        bool dialogueVisible;

    public:
        //add all variables to constructor maybe?
        Sans(int x, int y, int health, string headTextureFile, string bodyTextureFile, string legTextureFile, string sansFontFile, string dialogueString);
        Sans();

        void draw(RenderWindow* win);
        void talk(RenderWindow* win);

        void setText(string dialogueString);

        void setHead(string texturefile);
        void setBody(string texturefile);
        void setLeg(string texturefile);
        
        void setIsIdle(bool isIdle) {this->isIdle = isIdle;}
        bool getIsIdle() { return isIdle; }

        // code these up
        void setDialogueVisible();
        bool getDialogueVisible();

        bool getDodgeDirection() { return dodgeDirection; }

        void moveFull(double offsetX, double offsetY); // movement for sans entire body
        void dodge(double distance, double endPosition); // whereby sans will only dodge to the left

        ~Sans();
        
};

#endif