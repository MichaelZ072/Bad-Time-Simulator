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
  float platformSpawnDelay;
  int platformCount;

 public:
  platformLevel_3(Board* board, float speed) : platform(speed, board) {
    platformSmallCreation_1(
        0, board->getCenter().y + board->getCenter().y * 1 / 12);
    platformSpawnDelay = 1.0;
  }

  void createNewSmallPlatforms() {
    if (platformCount < 1) {
      if (platformClock.getElapsedTime().asSeconds() > platformSpawnDelay) {
        platforms.push_back(new platformLevel_4(board, 0));
        platformClock.restart();
        platformCount++;
      }
    } else {
    }
  }

  void updatePlatforms(float deltaTime) { createNewSmallPlatforms(); }

  void moveSmallRightPlatforms() {
    for (auto& plat : platforms) {
      plat->moveSmall_1(2, true);
    }
  }

  void moveSmallLeftPlatforms() {
    for (auto& plat : platforms) {
      plat->moveSmall_1(2, false);
    }
  }

  void renderPlatforms(sf::RenderWindow& window) {
    for (auto& platform : platforms) {
      window.draw(platform->getPlatformSmallGreen_1());
      window.draw(platform->getPlatformSmallBlack_1());
    }
  }

  std::vector<sf::FloatRect> getAllPlatformBounds() override {
    std::vector<sf::FloatRect> bounds;

    bounds.push_back(platformSmallBlack_1.getGlobalBounds());
    bounds.push_back(platformSmallGreen_1.getGlobalBounds());
    bounds.push_back(platformSmallBlack_2.getGlobalBounds());
    bounds.push_back(platformSmallGreen_2.getGlobalBounds());

    for (auto& plat : platforms) {
      bounds.push_back(plat->getPlatformSmallBlack_1().getGlobalBounds());
      bounds.push_back(plat->getPlatformSmallGreen_1().getGlobalBounds());
      bounds.push_back(plat->getPlatformSmallBlack_2().getGlobalBounds());
      bounds.push_back(plat->getPlatformSmallGreen_2().getGlobalBounds());
    }

    return bounds;
  }
};

#endif
