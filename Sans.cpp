#include "Sans.h"

#include <cmath>

Sans::Sans(int x, int y, int health, double scale, string headTextureFile, string bodyTextureFile, string legTextureFile)
{
    this->health = health;
    isIdle = true;
    dodgeDirection = false;

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
    head.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(headTexture.getSize())));

   
    // re-setting origin point
    Vector2u textureSize = headTexture.getSize();
    head.setOrigin(textureSize.x / 2.0f,textureSize.y);

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
    body.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(bodyTexture.getSize())));

    // re-setting origin point
    Vector2u textureSize = bodyTexture.getSize();
    body.setOrigin(textureSize.x / 2.0f,textureSize.y);
    
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
    leg.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(legTexture.getSize())));

    
    // re-setting origin point
    Vector2u textureSize = legTexture.getSize();
    leg.setOrigin(textureSize.x / 2.0f,textureSize.y);

}

void Sans::moveFull(double offsetX, double offsetY)
{
    head.move(offsetX, offsetY);
    body.move(offsetX, offsetY);
    leg.move(offsetX, offsetY); 
}

void Sans::dodge(double speed, double distance, double endPosition)
{
    if (body.getPosition().x < distance) {
        dodgeDirection = true;
    }
    
    if (dodgeDirection == false) {
        moveFull(-speed, 0);
    } else {
        moveFull(speed, 0);
    }

    //determines whether sans should stop moving
    if (body.getPosition().x > endPosition)
    {
        body.setPosition(endPosition, body.getPosition().y);
        head.setPosition(endPosition, head.getPosition().y);
        leg.setPosition(endPosition, leg.getPosition().y);
        isIdle = true;
        dodgeDirection = false;
    }
}