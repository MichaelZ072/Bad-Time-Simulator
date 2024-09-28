#include "Sans.h"

Sans::Sans(int x, int y, int health, string texturefile)
{
    this->health = health;

    // load texture
    if (!texture.loadFromFile(texturefile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }

    // create sprite from texture
    body.setTexture(texture);
    
    // change body properties
    Vector2u textureSize = texture.getSize();
    body.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    body.setScale(0.7f, 0.7f);  
    body.setPosition(sf::Vector2f(x,y));

}

void Sans::draw(RenderWindow *win)
{
    win->draw(body);
}

