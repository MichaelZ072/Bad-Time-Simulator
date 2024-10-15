#ifndef SOUL_H
#define SOUL_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "BulletBoard.h"

using namespace sf;
using namespace std;

class Soul {
 private:
  Sprite soul;
  Texture redTexture;
  Texture blueTexture;
  bool isRed;
  int maxHealth;
  int health;
  int karma;
  float speedRed;
  float speedBlue;
  int maxHeight;
  Vector2f gravity;
  Vector2f position;
  int intermissionPositionCount;

 public:
  Soul(Board* board, int setMaxHealth, float setSpeed, int setMaxHeight, int intermissionPositionCount, bool isIntermission) {
    maxHealth = setMaxHealth;
    health = maxHealth;
    karma = 0;
    speedRed = setSpeed;
    maxHeight = setMaxHeight;
    isRed = true;

    redTexture.loadFromFile("./sprites/redSoulSprite.png");
    blueTexture.loadFromFile("./sprites/blueSoulSprite.png");

    if (isIntermission == false) {
      position = board->getCenter();
    } else {
      position = Vector2f(45, 450);
    }

    soul.setTexture(redTexture);
    soul.setOrigin(Vector2f(8, 8));
    soul.setPosition(position);
  }

  // Returns whether the soul is red or not
  bool soulColor() { return isRed; }

  // Changes the soul to the red variant
  void makeRed() {
    soul.setTexture(redTexture);
    isRed = true;
  }

  // Changes the soul to the blue variant
  void makeBlue() {
    soul.setTexture(blueTexture);
    isRed = false;
  }

  // Moves the soul according to the up arrow
  void moveUp() {
    if (isRed) {
      soul.move(Vector2f(0, -speedRed));
    } else {
    }
  }

  // Moves the soul according to the down arrow
  void moveDown() {
    if (isRed) {
      soul.move(Vector2f(0, speedRed));
    } else {
    }
  }

  // Moves the soul according to the left arrow
  void moveLeft() {
    if (isRed) {
      soul.move(Vector2f(-speedRed, 0));
    } else {
    }
  }

  // Moves the soul according to the right arrow
  void moveRight() {
    if (isRed) {
      soul.move(Vector2f(speedRed, 0));
    } else {
    }
  }

  // intermission movement
  //  Moves the soul according to the up arrow intermission
  void intermissionMoveUp() {
    if (isRed) {
      soul.move(Vector2f(0, -speedRed));
    } else {
    }
  }

  // Moves the soul according to the down arrow intermission
  void intermissionMoveDown() {
    if (isRed) {
      soul.move(Vector2f(0, speedRed));
    } else {
    }
  }

  // Moves the soul according to the left arrow intermission
  void intermissionMoveLeft() {
      if (isRed) {
        intermissionPositionCount--;
        if (getIntermissionPositionCount() < 0) {
          intermissionPositionCount = 3;
        }
        switch (intermissionPositionCount) {
          case 0:
            changePosition(Vector2f(47.5f, 450.0f));
            intermissionPositionCount = 0;
            break;

          case 1:
            changePosition(Vector2f(197.5f, 450.0f));
            intermissionPositionCount = 1;
            break;

          case 2:
            changePosition(Vector2f(357.5f, 450.0f));
            intermissionPositionCount = 2;
            break;

          case 3:
            changePosition(Vector2f(507.5f, 450.0f));
            intermissionPositionCount = 3;
            break;

          default:
            break;
        }

      } else {
      }

  }

  // Moves the soul according to the right arrow intermission
  void intermissionMoveRight() {
    if (isRed) {
      intermissionPositionCount++;
      if (getIntermissionPositionCount() > 3) {
        intermissionPositionCount = 0;
      }
      switch (intermissionPositionCount)

      {
        case 0:
          changePosition(Vector2f(47.5f, 450.0f));
          intermissionPositionCount = 0;
          break;

        case 1:
          changePosition(Vector2f(197.5f, 450.0f));
          intermissionPositionCount = 1;
          break;

        case 2:
          changePosition(Vector2f(357.5f, 450.0f));
          intermissionPositionCount = 2;
          break;

        case 3:
          changePosition(Vector2f(507.5f, 450.0f));
          intermissionPositionCount = 3;
          break;

        default:
          break;
      }

    } else {
    }
  }

  int getIntermissionPositionCount() { return intermissionPositionCount; }

  void selectActionPosition(){
    changePosition(Vector2f(70.0f,285.0f));
  }

  void returnActionPosition(int count){
    switch (count)
    {
    case 0:
    changePosition(Vector2f(47.5f,450.0f));
    cout<<"change poition occured" << endl;
      break;

    case 1:
    changePosition(Vector2f(197.5f, 450.0f));
    cout<<"change poition occured" << endl;
  break;
  case 2:
    changePosition(Vector2f(357.5f, 450.0f));
    cout<<"change poition occured" << endl;
  break;
  case 3:
    changePosition(Vector2f(507.5f, 450.0f));
    cout<<"change poition occured" << endl;
  break;
    
    default:
      break;
    }

  }

  // Returns the max health
  int getMaxHealth() { return maxHealth; }

  // Adds health to the player up to the max - karma
  void heal(int addHealth) {
    health += addHealth;

    if (health + karma > maxHealth) {
      health = maxHealth - karma;
    }
  }

  // Returns the current health
  int getHealth() { return health; }

  void doDamage() {}

  // Returns the amount of karma
  int getKarma() { return karma; }

  // Teleports the soul to the specified location
  void changePosition(Vector2f newPosition) {
    position = newPosition;
    soul.setPosition(position);
  }

  // Draws the soul
  void draw(RenderWindow* window) { window->draw(soul); }

  ~Soul() { ; }
};

#endif