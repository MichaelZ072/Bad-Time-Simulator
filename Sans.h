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

        Texture texture;
        Sprite body;
        
    public:
        Sans(int x, int y, int health, string texturefile);
        Sans();

        void draw(RenderWindow* win);

        // void changeSprite(string texturefile);

        // void dodgeLeft(int speed);
        // void dodgeRight(int speed);

        ~Sans();
        
};

#endif