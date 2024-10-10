#ifndef ACTIONINTERFACE_H
#define ACTIONINTERFACE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletBoard.h"

using namespace std;
using namespace sf;

class actionInterface {
 protected:
  // Texture sprites
  Texture actIdleTexture;
  Texture fightIdleTexture;
  Texture itemIdleTexture;
  Texture mercyIdleTexture;
  Texture levelTexture;
  Texture bulletBoardTexture;
  Texture redSoulTexture;
  Texture blueSoulTexture;

  // Sprite creation
  Sprite actIdle;
  Sprite fightIdle;
  Sprite itemIdle;
  Sprite mercyIdle;
  Sprite levelSprite;
  Sprite bulletBoardSprite;
  Sprite redSoulSprite;
  Sprite blueSoulSprite;


  int currentHealth;  // An integer that represents the current health
  bool shiftOn;       // A boolean that checks for the shift input
  bool isRed;         // A boolean for whether the soul is red or not
  bool isAttackMode;

 public:
 
  actionInterface(int health, bool isAttackMode) {
    currentHealth = health;

if (isAttackMode == true){
  
  //fight sprite idle
    if (!fightIdleTexture.loadFromFile("./sprites/fightSpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    fightIdle.setTexture(fightIdleTexture);
    fightIdle.setPosition(30, 430);
    fightIdle.scale(0.7f, 0.65);
  //act sprite idle
    if (!actIdleTexture.loadFromFile("./sprites/actSpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    actIdle.setTexture(actIdleTexture);
    actIdle.setPosition(180, 430);
    actIdle.scale(0.7f, 0.65);
  
  //item sprite idle
  if (!itemIdleTexture.loadFromFile("./sprites/itemSpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    itemIdle.setTexture(itemIdleTexture);
    itemIdle.setPosition(340, 430);
    itemIdle.scale(0.7f, 0.65);

  //mercy sprite idle
  if (!mercyIdleTexture.loadFromFile("./sprites/mercySpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    mercyIdle.setTexture(mercyIdleTexture);
    mercyIdle.setPosition(490, 430);
    mercyIdle.scale(0.7f, 0.65);
    
  //level sprite idle
    if (!levelTexture.loadFromFile("./sprites/levelSprite.png")) {
      cout << "This texture is unable to load" << endl;
    }
    levelSprite.setTexture(levelTexture);
    levelSprite.setPosition(25, 395);
    
   //intermission phase 
}else{
  if (!actIdleTexture.loadFromFile("./sprites/actSpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    actIdle.setTexture(actIdleTexture);
    actIdle.setPosition(175, 435);
    actIdle.scale(0.7f, 0.7);

    if (!fightIdleTexture.loadFromFile("./sprites/fightSpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    fightIdle.setTexture(fightIdleTexture);
    fightIdle.setPosition(0, 435);
    fightIdle.scale(0.7f, 0.7);
  
  if (!itemIdleTexture.loadFromFile("./sprites/itemSpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    itemIdle.setTexture(itemIdleTexture);
    itemIdle.setPosition(350, 435);
    itemIdle.scale(0.7f, 0.7);

  if (!mercyIdleTexture.loadFromFile("./sprites/mercySpriteIdle.png")) {
      cout << "This texture is unable to load" << endl;
    }
    mercyIdle.setTexture(mercyIdleTexture);
    mercyIdle.setPosition(525, 435);
    mercyIdle.scale(0.7f, 0.7);
    
    if (!levelTexture.loadFromFile("./sprites/levelSprite.png")) {
      cout << "This texture is unable to load" << endl;
    }
    levelSprite.setTexture(levelTexture);
    levelSprite.setPosition(0, 400);
    
    if (!redSoulTexture.loadFromFile("./sprites/redSoulSprite.png")) {
      cout << "This texture is unable to load" << endl;
    }
    redSoulSprite.setTexture(redSoulTexture);
    redSoulSprite.setPosition(0, 400);

    if (!blueSoulTexture.loadFromFile("./sprites/blueSoulSprite.png")) {
      cout << "This texture is unable to load" << endl;
    }
    blueSoulSprite.setTexture(blueSoulTexture);
    blueSoulSprite.setPosition(0, 400);

}

  }

  // Getter to access the sprite
  sf::Sprite& getActIdle(){
   return actIdle; 
  }
  sf::Sprite& getFightIdle(){
    return fightIdle;
  }
   sf::Sprite& getItemIdle(){
    return itemIdle;
  }
  sf::Sprite& getMercyIdle(){
    return mercyIdle;
  }
sf::Sprite& getLevelSprite(){
    return levelSprite;
  }
sf::Sprite& getBulletBoardSprite(){
    return bulletBoardSprite;
  }
  sf::Sprite& getRedSoulSprite(){
    return redSoulSprite;
  }
  sf::Sprite& getBlueSoulSprite(){
    return blueSoulSprite;
  }

  void intermissionPhase(){
    
  }


  void doAction();
  int afterAttackHealth();
  void returnState();
  bool soulColourCheck();
  void soulColour();
  void soulColourIntermission();
};

#endif
