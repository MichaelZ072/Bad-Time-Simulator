#ifndef PLATFORMLEVEL2_H
#define PLATFORMLEVEL2_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BulletBoard.h"
#include "platform.h"

class platformLevel_2 : public platform {
 private:
  std::vector<platformLevel_2*> platforms;  
  sf::Clock platformClock;                 
  float platformMediumSpawnDelay;
  float platformLargeSpawnDelay;
  int platformCount;        

 public:
  platformLevel_2(Board* board, float speed) : platform(speed, board) {
    platformMediumCreation(0, board->getCenter().y + (board->getCenter().y * 1 / 12));
    platformLargeCreation(400, board->getCenter().y - (board->getCenter().y * 1 / 12));
    platformMediumSpawnDelay = 2;  
    platformLargeSpawnDelay = 2.5;
  }


 void createNewMediumPlatforms() {
    if (platformCount < 5){
    if (platformClock.getElapsedTime().asSeconds() > platformMediumSpawnDelay) {
      platforms.push_back(new platformLevel_2(board, 0)); 
      platformClock.restart();  
      platformCount++;
    }
    }else{

    }
  }

   void createNewLargePlatforms() {
    if (platformCount < 4){
    if (platformClock.getElapsedTime().asSeconds() > platformLargeSpawnDelay) {
      platforms.push_back(new platformLevel_2(board, 0)); 
      platformClock.restart();  
      platformCount++;
    }
    }else{

    }
  }

  void updatePlatforms() {
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

std::vector<sf::FloatRect> getAllPlatformBounds() override {
    std::vector<sf::FloatRect> bounds;

    bounds.push_back(platformMediumBlack.getGlobalBounds());
    bounds.push_back(platformMediumGreen.getGlobalBounds());
    bounds.push_back(platformLargeBlack.getGlobalBounds());
    bounds.push_back(platformLargeGreen.getGlobalBounds());


    for (auto& plat : platforms) {
      bounds.push_back(plat->getPlatformMediumBlack().getGlobalBounds());
      bounds.push_back(plat->getPlatformMediumGreen().getGlobalBounds());
      bounds.push_back(plat->getPlatformLargeBlack().getGlobalBounds());
      bounds.push_back(plat->getPlatformLargeGreen().getGlobalBounds());
    }

    return bounds; 
  }


};

#endif
