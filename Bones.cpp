#include "Bones.h"

Bones::Bones(int x, int y, int boneSpeed, string boneTextureFile)
{
    this->boneSpeed = boneSpeed;

    this->isActive = false;

    // load texture
    boneTexture.loadFromFile(boneTextureFile);
    // create sprite from texture
    bone.setTexture(boneTexture);

    // set sprite properties
    Vector2u boneTextureSize = boneTexture.getSize();
    bone.setOrigin(boneTextureSize.x / 2.0f, boneTextureSize.y / 2.0f);
    // bone.setPosition(x, y - (boneTextureSize.y / 2.0f)); // makes sure bottom of bone is at specified y
    bone.setPosition(x, y);
}

/*
void Bones::moveLeft(int speed)
{
    bone.move(-speed, 0);    
}

void Bones::moveRight(int speed)
{
    bone.move(speed, 0);
}

void Bones::moveUp(int speed)
{
    bone.move(0, -speed);
}

void Bones::moveDown(int speed)
{
    bone.move(0, speed);
}
*/

void Bones::move(int speed, int direction)
{
    // define direction of movement based on corner
    switch (direction)
    {
    case 0: // move up
        bone.move(0, -speed);
        break;
    case 1: // move right
        bone.move(speed, 0);
        break;
    case 2: // move down
        bone.move(0, speed);
        break;
    case 3: // move left
        bone.move(-speed, 0);
        break;
    default: // else move upwards as default
        bone.move(0, -speed);
        break;
    }
}

Vector2u Bones::getSize()
{
    return boneTexture.getSize();
}

void Bones::draw(RenderWindow *win)
{
    if (!isActive) {
        return;
    } 
    win->draw(bone);
}