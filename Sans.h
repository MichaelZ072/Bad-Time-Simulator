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
        
        void dodge(int speed);

        ~Sans();
        
};

#endif