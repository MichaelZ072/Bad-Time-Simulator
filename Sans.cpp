#include "Sans.h"

Sans::Sans(int x, int y, int health, double scale, string texturefile)
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
    body.setOrigin(textureSize.x / 2.0f, textureSize.y);
    body.setScale(scale, scale);  
    body.setPosition(sf::Vector2f(x,y));

}

void Sans::draw(RenderWindow *win)
{
    win->draw(body);
}

void Sans::setBody(string texturefile)
{

    // load texture
    if (!texture.loadFromFile(texturefile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }

    // replace sprite from texture
    body.setTexture(texture);

    // re-setting origin point
    Vector2u textureSize = texture.getSize();
    body.setOrigin(textureSize.x / 2.0f, textureSize.y);

}

void Sans::dodge(int speed)
{
    body.move(-speed, 0);
}
