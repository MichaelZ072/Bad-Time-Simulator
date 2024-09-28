#include "Sans.h"

Sans::Sans(int x, int y, int health, double scale, string headTextureFile, string bodyTextureFile, string legTextureFile)
{
    this->health = health;

    // load textures
    if (!headTexture.loadFromFile(headTextureFile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // create sprite from texture
    head.setTexture(headTexture);

    if (!bodyTexture.loadFromFile(bodyTextureFile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // create sprite from texture
    body.setTexture(bodyTexture);
    
    if (!legTexture.loadFromFile(legTextureFile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // create sprite from texture
    leg.setTexture(legTexture);

    
    
    // change body properties (building sans from bottom to top
    Vector2u legTextureSize = legTexture.getSize();
    leg.setScale(scale, scale);
    leg.setOrigin(legTextureSize.x / 2.0f, legTextureSize.y);  
    leg.setPosition(sf::Vector2f(x, y));

    Vector2u bodyTextureSize = bodyTexture.getSize();
    body.setScale(scale, scale);
    body.setOrigin(bodyTextureSize.x / 2.0f, bodyTextureSize.y);
    body.setPosition(sf::Vector2f(x, y - legTextureSize.y * scale)); // because torso sits on leg

    Vector2u headTextureSize = headTexture.getSize();
    head.setScale(scale, scale);
    head.setOrigin(headTextureSize.x / 2.0f, headTextureSize.y);
    head.setPosition(sf::Vector2f(x, y - legTextureSize.y * scale - bodyTextureSize.y * scale + (headTextureSize.y * scale / 5.5f))); // because head sits on torso



}

void Sans::draw(RenderWindow *win)
{
    win->draw(leg);
    win->draw(body);
    win->draw(head);
}

void Sans::setHead(string texturefile)
{

    // load texture
    if (!headTexture.loadFromFile(texturefile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // replace sprite from texture
    head.setTexture(headTexture);
    
    // re-setting origin point
    Vector2u textureSize = headTexture.getSize();

}

void Sans::setBody(string texturefile)
{

    Vector2u oldTextureSize = bodyTexture.getSize();    

    // load texture
    if (!bodyTexture.loadFromFile(texturefile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // replace sprite from texture
    body.setTexture(bodyTexture);

    // re-setting origin point
    Vector2u textureSize = bodyTexture.getSize();
}

void Sans::setLeg(string texturefile)
{
    
    // load texture
    if (!legTexture.loadFromFile(texturefile))     
    {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // replace sprite from texture
    leg.setTexture(legTexture);
    
    // re-setting origin point
    Vector2u textureSize = legTexture.getSize();

}

void Sans::dodge(int speed)
{
    body.move(-speed, 0);
}
