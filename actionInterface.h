#ifndef ACTIONINTERFACE_H
#define ACTIONINTERFACE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletBoard.h"
#include "Soul.h"

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
  Texture actSelectedTexture;
  Texture fightSelectedTexture;
  Texture itemSelectedTexture;
  Texture mercySelectedTexture;

  // Sprite creation
  Sprite actSprite;
  Sprite fightSprite;
  Sprite itemSprite;
  Sprite mercySprite;
  Sprite levelSprite;


  int currentHealth;  // An integer that represents the current health
  bool shiftOn;       // A boolean that checks for the shift input
  bool isAttackMode;
  int intermissionPositionCount;
  bool isFightIdle;
  bool isActIdle;
  bool isItemIdle;
  bool isMercyIdle;


 public:
 
  actionInterface(int health, bool isAttackMode, Soul* soul) {
    currentHealth = health;

if (isAttackMode == true){
  
  //fight sprite idle
    loadFromFile("./sprites/fightSpriteIdle.png");
    fightSprite.setTexture(fightIdleTexture);
    fightSprite.setPosition(30, 430);
    fightSprite.scale(0.7f, 0.65);
  //act sprite idle
    actSprite.setTexture(actIdleTexture);
    actSprite.setPosition(180, 430);
    actSprite.scale(0.7f, 0.65);
  
  //item sprite idle
    itemSprite.setTexture(itemIdleTexture);
    itemSprite.setPosition(340, 430);
    itemSprite.scale(0.7f, 0.65);

  //mercy sprite idle
    mercySprite.setTexture(mercyIdleTexture);
    mercySprite.setPosition(490, 430);
    mercySprite.scale(0.7f, 0.65);
    
  //level sprite idlew
    levelSprite.setTexture(levelTexture);
    levelSprite.setPosition(25, 395);
    
   //intermission phase 
}else{
  switch (soul->getIntermissionPositionCount())
  {
  case 1:
    fightSprite.setTexture(fightSelectedTexture);
    fightSprite.setPosition(30, 430);
    fightSprite.scale(1.05, 0.925);
    break;

 // default:
   // break;
  }
  cout<<soul->getIntermissionPositionCount()<< endl;
  //fight sprite idle
    //fightSprite.setTexture(fightIdleTexture);
    //fightSprite.setPosition(30, 430);
    //fightSprite.scale(0.7f, 0.65);
  //act sprite idle
    actSprite.setTexture(actIdleTexture);
    actSprite.setPosition(180, 430);
    actSprite.scale(0.7f, 0.65);
  
  //item sprite idle
    itemSprite.setTexture(itemIdleTexture);
    itemSprite.setPosition(340, 430);
    itemSprite.scale(0.7f, 0.65);

  //mercy sprite idle
    mercySprite.setTexture(mercyIdleTexture);
    mercySprite.setPosition(490, 430);
    mercySprite.scale(0.7f, 0.65);
    
  //level sprite idlew
    levelSprite.setTexture(levelTexture);
    levelSprite.setPosition(25, 395);

  }
  }
void fightSwitchIdle() {
    fightSprite.setTexture(fightIdleTexture);
    fightSprite.setPosition(30, 430);
    fightSprite.scale(0.7f, 0.65);
        }

void fightSwitchSelected(){
  fightSprite.setTexture(fightSelectedTexture);
    fightSprite.setPosition(30, 430);
    fightSprite.scale(1.05, 0.925);
}


  // Getter to access the sprite
  sf::Sprite& getAct(){
   return actSprite; 
  }
  sf::Sprite& getFight(){
    return fightSprite;
  }
   sf::Sprite& getItem(){
    return itemSprite;
  }
  sf::Sprite& getMercy(){
    return mercySprite;
  }
sf::Sprite& getLevelSprite(){
    return levelSprite;
  }



  void doAction();
  int afterAttackHealth();
  void returnState();
  bool soulColourCheck();
  void soulColour();
  void soulColourIntermission();
};

#endif
