#ifndef PLATFORMLEVEL3_H
#define PLATFORMLEVEL3_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletBoard.h"
#include "platform.h"

class platformLevel_3 : public platform {
 private:
  std::vector<platformLevel_3*> platforms;  
  sf::Clock platformClock;                 
  float platformMediumSpawnDelay;
  float platformLargeSpawnDelay;
  int platformCount;        

 public:
  platformLevel_3(Board* board, float speed) : platform(speed, board) {
    platformMediumCreation(0, board->getCenter().y + (board->getCenter().y * 1 / 12));
    platformLargeCreation(400, board->getCenter().y - (board->getCenter().y * 1 / 12));
    platformMediumSpawnDelay = 2;  
    platformLargeSpawnDelay = 2.5;
  }


 void createNewMediumPlatforms() {
    if (platformCount < 5){
    if (platformClock.getElapsedTime().asSeconds() > platformMediumSpawnDelay) {
      platforms.push_back(new platformLevel_3(board, 0)); 
      platformClock.restart();  
      platformCount++;
    }
    }else{

    }
  }

   void createNewLargePlatforms() {
    if (platformCount < 4){
    if (platformClock.getElapsedTime().asSeconds() > platformLargeSpawnDelay) {
      platforms.push_back(new platformLevel_3(board, 0)); 
      platformClock.restart();  
      platformCount++;
    }
    }else{

    }
  }

  void updatePlatforms(float deltaTime) {
    createNewMediumPlatforms();
    createNewLargePlatforms();
  }

void moveMediumPlatforms(){
for (auto& plat : platforms) {
        plat->moveMedium(2.5,true);
      }
}
void moveLargePlatforms(){
for (auto& plat : platforms) {
        plat->moveLarge(3.5,false);
      }
}

  void renderPlatforms(sf::RenderWindow& window) {
    for (auto& platform : platforms) {
      window.draw(platform->getPlatformMediumGreen());
      window.draw(platform->getPlatformMediumBlack());
      window.draw(platform->getPlatformLargeGreen());
      window.draw(platform->getPlatformLargeBlack());
    }
  }
  
};

#endif
