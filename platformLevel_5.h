#ifndef PLATFORMLEVEL5_H
#define PLATFORMLEVEL5_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletBoard.h"
#include "platform.h"

class platformLevel_5 : public platform {
 private:
  std::vector<platformLevel_5*> platforms;  
  sf::Clock platformClock;                 
  float platformSmallSpawnDelay;
  int platformCount;        

 public:
  platformLevel_5(Board* board, float speed) : platform(speed, board) {
    platformSmallCreation_1(0, board->getCenter().y + (board->getCenter().y * 1 / 12));
    platformSmallCreation_2(400, board->getCenter().y - (board->getCenter().y * 1 / 12));
    platformSmallSpawnDelay = 2;  
  }


 void createNewSmallPlatforms_1() {
    if (platformCount < 5){
    if (platformClock.getElapsedTime().asSeconds() > platformSmallSpawnDelay) {
      platforms.push_back(new platformLevel_5(board, 0)); 
      platformClock.restart();  
      platformCount++;
    }
    }else{

    }
  }

   void createNewSmallPlatforms_2() {
    if (platformCount < 4){
    if (platformClock.getElapsedTime().asSeconds() > platformSmallSpawnDelay) {
      platforms.push_back(new platformLevel_5(board, 0)); 
      platformClock.restart();  
      platformCount++;
    }
    }else{

    }
  }

  void updatePlatforms(float deltaTime) {
    createNewSmallPlatforms_1();
    createNewSmallPlatforms_2();
  }

void moveSmallPlatforms_1(){
for (auto& plat : platforms) {
        plat->moveSmall_1(2.5,true);
      }
}
void moveSmallPlatforms_2(){
for (auto& plat : platforms) {
        plat->moveSmall_2(2.5,false);
      }
}

  void renderPlatforms(sf::RenderWindow& window) {
    for (auto& platform : platforms) {
      window.draw(platform->getPlatformSmallGreen_1());
      window.draw(platform->getPlatformSmallBlack_1());
      window.draw(platform->getPlatformSmallGreen_2());
      window.draw(platform->getPlatformSmallBlack_2());
    }
  }
  
};

#endif
