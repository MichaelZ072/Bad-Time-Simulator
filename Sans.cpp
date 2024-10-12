#include "Sans.h"

#include <cmath>

Sans::Sans(int x, int y, int health, string headTextureFile, string bodyTextureFile, string legTextureFile, string sansFontFile, string dialogueString)
{
    this->health = health;
    isIdle = true;
    dodgeDirection = false;
    
    clock.restart();
    time = clock.getElapsedTime();

    // load textures
    if (!headTexture.loadFromFile(headTextureFile)) {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // create sprite from texture
    head.setTexture(headTexture);

    if (!bodyTexture.loadFromFile(bodyTextureFile)) {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // create sprite from texture
    body.setTexture(bodyTexture);
    
    if (!legTexture.loadFromFile(legTextureFile)) {
        // print error if texture failed to load
        cout << "this texture could not be loaded" << endl; 
    }
    // create sprite from texture
    leg.setTexture(legTexture);

    // change body properties (building sans from bottom to top
    Vector2u legTextureSize = legTexture.getSize();
    leg.setOrigin(legTextureSize.x / 2.0f, legTextureSize.y);  
    leg.setPosition(x, y);

    Vector2u bodyTextureSize = bodyTexture.getSize();
    body.setOrigin(bodyTextureSize.x / 2.0f, bodyTextureSize.y);
    body.setPosition(x, y - legTextureSize.y); // because torso sits on leg

    Vector2u headTextureSize = headTexture.getSize();
    head.setOrigin(headTextureSize.x / 2.0f, headTextureSize.y);
    head.setPosition(x, y - legTextureSize.y - bodyTextureSize.y + (headTextureSize.y / 5.5f)); // because head sits on torso

    // maybe move to talk function
    // preparing font
    font.loadFromFile(sansFontFile);

    // preparing text
    this->dialogueString = dialogueString;
    text.setFont(font);
    text.setString(dialogueString);
    text.setFillColor(Color::Black);
    
    // creating the speech bubble
    speechBubbleTexture.loadFromFile("assets/speechBubble.png"); // replace string with a default constructor string
    speechBubble.setTexture(speechBubbleTexture);

    Vector2u speechBubbleTextureSize = speechBubbleTexture.getSize();
    speechBubble.setOrigin(0, speechBubbleTextureSize.y / 2.0f);
    speechBubble.setPosition(x + bodyTextureSize.x / 2.0f + 8, y - legTextureSize.y - bodyTextureSize.y + 10);

    // text position on top of speech bubble
    text.setCharacterSize(13);
    text.setOrigin(0, text.getCharacterSize() / 2.0f);
    text.setPosition(x + bodyTextureSize.x / 2.0f + 43, y - legTextureSize.y - bodyTextureSize.y - 23);
}

void Sans::draw(RenderWindow *win)
{
    win->draw(leg);
    win->draw(body);
    win->draw(head);
    win->draw(speechBubble);
    win->draw(text);
}

void Sans::talk(RenderWindow *win)
{
    win->draw(speechBubble);
    win->draw(text);
}

void Sans::setText(string dialogueString)
{
    this->dialogueString = dialogueString;
    text.setString(dialogueString);
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

// incorporate variables for dodge deccel
void Sans::dodge(double distance, double endPosition)
{
    //moves Sans according to his set direction
    if (dodgeDirection == false) { // moving left
        moveFull(-dodgeSpeed, 0);
        time = clock.getElapsedTime(); // gets elapsed time
        
        if (dodgeSpeed >= 1) {
            dodgeSpeed -= 0.48;
        }

    // if sans needs to move right, we have to wait (waitTime) second(s) before he can do so
    } else if (clock.getElapsedTime().asSeconds() > time.asSeconds() + waitTime) { // moving right
        moveFull(dodgeSpeed, 0);
        if (dodgeSpeed <= 11) {
            dodgeSpeed += 1;
        }
    }

    //swap Sans' direction of motion when he gets to a certain position
    if (body.getPosition().x <= distance) {
        dodgeDirection = true;
        dodgeSpeed = 2;
    }

    //determines whether sans should stop moving
    if (body.getPosition().x >= endPosition) {
        //forces Sans to return to idle
        body.setPosition(endPosition, body.getPosition().y);
        head.setPosition(endPosition, head.getPosition().y);
        leg.setPosition(endPosition, leg.getPosition().y);
        isIdle = true;
        dodgeDirection = false;
        dodgeSpeed = 10;
    }
}