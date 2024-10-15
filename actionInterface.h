#ifndef ACTIONINTERFACE_H
#define ACTIONINTERFACE_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "BulletBoard.h"
#include "Soul.h"
#include "actionSelect.h"
#include "fight.h"
#include "act.h"
#include "mercy.h"
#include "item.h"

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
  Texture badTimeTexture;
  Texture sansSelectTexture;
  Texture spareSelectTexture;
  Texture attackBarTexture;
  Texture actionCheckTexture;
  Texture foodTexture;

  // Sprite creation
  Sprite actSprite;
  Sprite fightSprite;
  Sprite itemSprite;
  Sprite mercySprite;
  Sprite levelSprite;
  Sprite textSprite;
  Sprite selectSprite;
  Sprite selectedSprite;
  Sprite attackBarSprite;
  Sprite selectionSprite;

  RectangleShape attackBar;

 Font font;
  Text healthText;

  int currentHealth;  
  bool isAttackMode;
  int intermissionPositionCount;
  actionSelect* attack;
  Soul* soul;
  actionSelect* inspect;
  actionSelect* spare;
  actionSelect* choose;
  bool isSelection;
  bool isChoose;
  int selected;
  bool isAction;
  bool isAttacking;
  bool isAnimation;
  bool isAnimationEnd;
  bool isSelected;


 public:
  actionInterface(int health, bool isAttackMode, Soul* souls){
     soul = souls;
    currentHealth = health;
    attack = new fight(10);
    inspect = new act(10);
    spare = new mercy(10);
    choose = new item(10, soul);
   
font.loadFromFile("ut-hp-font.ttf");

    // Initialize health text
    healthText.setFont(font);
    healthText.setCharacterSize(13.5);
    healthText.setFillColor(Color::White);
    healthText.setPosition(220, 405);  // Position the text on the screen
    healthText.setString( "HP: "+std::to_string(currentHealth)+"92");

    fightIdleTexture.loadFromFile("./sprites/fightSpriteIdle.png");
    fightSelectedTexture.loadFromFile("./sprites/fightSpriteSelected.png");
    actIdleTexture.loadFromFile("./sprites/actSpriteIdle.png");
    actSelectedTexture.loadFromFile("./sprites/actSpriteSelected.png");
    itemIdleTexture.loadFromFile("./sprites/itemSpriteIdle.png");
    itemSelectedTexture.loadFromFile("./sprites/itemSpriteSelected.png");
    mercyIdleTexture.loadFromFile("./sprites/mercySpriteIdle.png");
    mercySelectedTexture.loadFromFile("./sprites/mercySpriteSelected.png");
    levelTexture.loadFromFile("./sprites/levelSprite.png");
    badTimeTexture.loadFromFile("./sprites/badTimeSprite.png");
    sansSelectTexture.loadFromFile("./sprites/sansSelect.png");
    spareSelectTexture.loadFromFile("./sprites/spareSelect.png");
    attackBarTexture.loadFromFile("./sprites/attackBarSprite.png");
    actionCheckTexture.loadFromFile("./sprites/actionCheckSprite.png");
    foodTexture.loadFromFile("./sprites/foodSprite.png");

    fightSprite.setPosition(30, 430);
    fightSprite.scale(0.85f, 0.775);
    actSprite.setPosition(180, 430);
    actSprite.scale(0.85f, 0.775);
    itemSprite.setPosition(340, 430);
    itemSprite.scale(0.85f, 0.775);
    mercySprite.setPosition(490, 430);
    mercySprite.scale(0.85f, 0.775);
    levelSprite.setPosition(25, 395);
    textSprite.setPosition(65, 265);
    selectSprite.setPosition(1000, 1000);
    attackBarSprite.setPosition(1000,1000);
    attackBarSprite.scale(0.43f,0.43);
    selectionSprite.setPosition(1000,1000);

    if (isAttackMode == true) {
      // fight sprite idle
      fightSwitchIdle();

      // act sprite idle
      actSwitchIdle();

      // item sprite idle
      itemSwitchIdle();
      // mercy sprite idle
      mercySwitchIdle();

      // level sprite idle
      levelSprite.setTexture(levelTexture);

      // intermission phase
    } else {
      levelSprite.setTexture(levelTexture);
    }
  }

void updateHealth(int newHealth) {
    currentHealth = newHealth;  
    healthText.setString("HP: "+std::to_string(currentHealth)+"/92"); 
}

  void fightSwitchIdle() { fightSprite.setTexture(fightIdleTexture); }

  void fightSwitchSelected() { fightSprite.setTexture(fightSelectedTexture); }
  void actSwitchIdle() { actSprite.setTexture(actIdleTexture); }

  void actSwitchSelected() { actSprite.setTexture(actSelectedTexture); }

  void itemSwitchIdle() { itemSprite.setTexture(itemIdleTexture); }

  void itemSwitchSelected() { itemSprite.setTexture(itemSelectedTexture); }

  void mercySwitchSelected() { mercySprite.setTexture(mercySelectedTexture); }

  void mercySwitchIdle() { mercySprite.setTexture(mercyIdleTexture); }

  void textBadTimeSwitch() { textSprite.setTexture(badTimeTexture); }

  void textFightActSwitch() { 
    selectSprite.setTexture(sansSelectTexture);
    }


  void attackBarLoad(){attackBarSprite.setTexture(attackBarTexture);}

  void actionCheckLoad(){selectionSprite.setTexture(actionCheckTexture);}

  void foodLoad(){selectSprite.setTexture(foodTexture);}

  void textSpareSwitch(){ selectSprite.setTexture(spareSelectTexture);   }

  void updateSpriteTextures(int count) {
    switch (count) {
      case 0:
        fightSwitchSelected();
        actSwitchIdle();
        itemSwitchIdle();
        mercySwitchIdle();
        isChoose = true;
        isSelection = false;
        break;
      case 1:
        fightSwitchIdle();
        actSwitchSelected();
        itemSwitchIdle();
        mercySwitchIdle();
        isChoose = true;
        isSelection = false;
        break;
      case 2:
        fightSwitchIdle();
        actSwitchIdle();
        itemSwitchSelected();
        mercySwitchIdle();
        isChoose = true;
        isSelection = false;
        break;
      case 3:
        fightSwitchIdle();
        actSwitchIdle();
        itemSwitchIdle();
        mercySwitchSelected();
        isChoose = true;
        isSelection = false;
        break;

      default:
        fightSwitchIdle();
        actSwitchIdle();
        itemSwitchIdle();
        mercySwitchIdle();
        break;
    }
  }

  void fightActSelect(){
        textFightActSwitch();
  };

  void spareSelect(){
      textSpareSwitch();
  };

  void foodSelect(){
    foodLoad();
  };

void moveSelectSprite(int x, int y){
    selectSprite.setPosition(x, y);
  }

  void returnState(){
    if(getIsSelect() == true && getIsAction() == false){
      soul->returnActionPosition(soul->getIntermissionPositionCount());
      selectSprite.setPosition(1000, 1000); 

        isSelection = false; 
    }
  }

void battleSelection(int count){
switch (count){

case 0:
fightActSelect();
soul->selectActionPosition();
moveSelectSprite(75,265);
isSelection = true;
isChoose = false;
selected = 0;
  break;

case 1:
fightActSelect();
soul->selectActionPosition();
moveSelectSprite(75,265);
isSelection = true;
isChoose = false;
selected =1;
break;

case 2:
foodSelect();
soul->selectActionPosition();
moveSelectSprite(75,265);
isSelection = true;
isChoose = false;
selected=2;
break;

case 3:
spareSelect();
soul->selectActionPosition();
moveSelectSprite(75,265);
isSelection = true;
isChoose = false;
selected =3;
break;

default:
  break;
}
}

void moveAttackBarSprite(){
    attackBarSprite.setPosition(37.5,250);
  }

  void moveSelectionSprite(){
    selectionSprite.setPosition(65,260);

  }

void actionSelection(int selected){
switch(selected){

case 0:
attackBarLoad();
moveSelectSprite(1000,1000);
soul->changePosition(Vector2f(1000.0f, 1000.0f));
fightSwitchIdle();
moveAttackBarSprite();
isAction = true;
isAttacking = true;
isSelected = true;
break;


case 1:
inspect->doAction();
actionCheckLoad();
moveSelectSprite(1000,1000);
soul->changePosition(Vector2f(1000.0f, 1000.0f));
actSwitchIdle();
moveSelectionSprite();
isAction = true;
isAttacking = true;
isSelected = true;
break;

case 2:
choose->doAction();
itemSwitchIdle();

// end intermission
isAction = true;
isAttacking = true;
isSelected = true;
break;

case 3:
spare->doAction();
mercySwitchIdle();
isAction = true;
isAttacking = true;
isSelected = true;
break;
}
}

void attackBarCreation(){
  attackBar.setSize(sf::Vector2f(3, 130));
    attackBar.setFillColor(Color::White);
    attackBar.setOutlineThickness(2.0f);
    attackBar.setOutlineColor(sf::Color::Black);
    attackBar.setPosition(30,260);
}

void moveAttackBar(bool isAnimation,int x){
  if(isAnimation == true ){
  attackBar.move(x,0);}
  else{}
}

void animationCheck(){ 
  if(attackBar.getPosition().x>=570 || getIsAnimationEnd() == true){
    isAnimation = false;
  }else{
    isAnimation = true;
  } 
}


void attackSelected(){
attackBarCreation();
isAnimation = true;
}


void isAttacked(){
moveAttackBar(false,0);
attack->doAction();
isAnimation = false;
isAnimationEnd = true;
}



void intermissionEnd(){
isAttackMode = true;
}

  // Getter to access the sprite
  sf::Sprite& getAct() { return actSprite; }
  sf::Sprite& getFight() { return fightSprite; }
  sf::Sprite& getItem() { return itemSprite; }
  sf::Sprite& getMercy() { return mercySprite; }
  sf::Sprite& getLevelSprite() { return levelSprite; }
  sf::Sprite& getTextSprite() { return textSprite; }
  sf::Sprite& getSansSelect() {return selectSprite;}
  sf::Sprite& getAttackBarSprite() {return attackBarSprite;}
  sf::Sprite& getSelectionSprite() {return selectionSprite;}
  sf::RectangleShape& getAttackBar(){return attackBar;}  

   void drawHealth(RenderWindow& window) {
    window.draw(healthText); 
  }
 
 int getCurrentHealth(){
  return currentHealth;
 }

  bool getIsSelect(){
    return isSelection;
  }
  bool getIsChoose(){
    return isChoose;
  }

  int getSelectedNumber(){
    return selected;
  }

  bool getIsAction(){
    return isAction;
  }

  bool getIsAnimation(){
    return isAnimation;
  }

  bool getIsAnimationEnd(){
    return isAnimationEnd;
  }

bool getIsSelected(){
  return isSelected;
}


};
#endif