#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "BulletBoard.h"

using namespace std;
using namespace sf;

class platform {
 protected:
  RectangleShape platformSmallBlack_1;
   RectangleShape platformSmallBlack_2;
  RectangleShape platformSmallGreen_2;
  RectangleShape platformSmallGreen_1;
  RectangleShape platformTinyBlack;
  RectangleShape platformTinyGreen;
  RectangleShape platformMediumBlack;
  ;
  RectangleShape platformMediumGreen;
  RectangleShape platformLargeBlack;
  RectangleShape platformLargeGreen;
  Board* board;
  sf::Clock clock;
  float delayDuration;

  float speed;

 public:
  platform(float platformSpeed, Board* gameBoard) {
    speed = platformSpeed;
    board = gameBoard;
  }
  void platformSmallCreation_1(float x, float y) {
    platformSmallBlack_1.setSize(sf::Vector2f(60.0, 3));
    platformSmallBlack_1.setFillColor(Color::Black);
    platformSmallBlack_1.setOutlineThickness(2.0f);
    platformSmallBlack_1.setOutlineColor(sf::Color::White);
    platformSmallBlack_1.setPosition(x, y);

    platformSmallGreen_1.setSize(sf::Vector2f(60.0, 2.5));
    platformSmallGreen_1.setFillColor(Color::Black);
    platformSmallGreen_1.setOutlineThickness(2.0f);
    platformSmallGreen_1.setOutlineColor(sf::Color::Green);
    platformSmallGreen_1.setPosition(x, y - 6);
  }
void platformSmallCreation_2(float x, float y) {
    platformSmallBlack_2.setSize(sf::Vector2f(60.0, 3));
    platformSmallBlack_2.setFillColor(Color::Black);
    platformSmallBlack_2.setOutlineThickness(2.0f);
    platformSmallBlack_2.setOutlineColor(sf::Color::White);
    platformSmallBlack_2.setPosition(x, y);

    platformSmallGreen_2.setSize(sf::Vector2f(60.0, 2.5));
    platformSmallGreen_2.setFillColor(Color::Black);
    platformSmallGreen_2.setOutlineThickness(2.0f);
    platformSmallGreen_2.setOutlineColor(sf::Color::Green);
    platformSmallGreen_2.setPosition(x, y - 6);
  }


  void platformTinyCreation(float x, float y) {
    platformTinyBlack.setSize(sf::Vector2f(40.0, 3));
    platformTinyBlack.setFillColor(Color::Black);
    platformTinyBlack.setOutlineThickness(2.0f);
    platformTinyBlack.setOutlineColor(sf::Color::White);
    platformTinyBlack.setPosition(x, y);

    platformTinyGreen.setSize(sf::Vector2f(40.0, 2.5));
    platformTinyGreen.setFillColor(Color::Black);
    platformTinyGreen.setOutlineThickness(2.0f);
    platformTinyGreen.setOutlineColor(sf::Color::Green);
    platformTinyGreen.setPosition(x, y - 6);
  }

  void platformMediumCreation(float x, float y) {
    platformMediumBlack.setSize(sf::Vector2f(100.0, 3));
    platformMediumBlack.setFillColor(Color::Black);
    platformMediumBlack.setOutlineThickness(2.0f);
    platformMediumBlack.setOutlineColor(sf::Color::White);
    platformMediumBlack.setPosition(x, y);

    platformMediumGreen.setSize(sf::Vector2f(100.0, 2.5));
    platformMediumGreen.setFillColor(Color::Black);
    platformMediumGreen.setOutlineThickness(2.0f);
    platformMediumGreen.setOutlineColor(sf::Color::Green);
    platformMediumGreen.setPosition(x, y - 6);
  }

  void platformLargeCreation(float x, float y) {
    platformLargeBlack.setSize(sf::Vector2f(140.0, 3));
    platformLargeBlack.setFillColor(Color::Black);
    platformLargeBlack.setOutlineThickness(2.0f);
    platformLargeBlack.setOutlineColor(sf::Color::White);
    platformLargeBlack.setPosition(x, y);

    platformLargeGreen.setSize(sf::Vector2f(140.0, 2.5));
    platformLargeGreen.setFillColor(Color::Black);
    platformLargeGreen.setOutlineThickness(2.0f);
    platformLargeGreen.setOutlineColor(sf::Color::Green);
    platformLargeGreen.setPosition(x, y - 6);
  }

  void moveSmall_1(float offset, bool isRight) {
    if (isRight == true) {
      platformSmallBlack_1.move(offset, 0);
      platformSmallGreen_1.move(offset, 0);
    } else {
      platformSmallBlack_1.move(-offset, 0);
      platformSmallGreen_1.move(-offset, 0);
    }
  }

  void moveSmall_2(float offset, bool isRight) {
    if (isRight == true) {
      platformSmallBlack_2.move(offset, 0);
      platformSmallGreen_2.move(offset, 0);
    } else {
      platformSmallBlack_2.move(-offset, 0);
      platformSmallGreen_2.move(-offset, 0);
    }
  }

  void moveTiny(float offset, bool isRight) {
    if (isRight == true) {
      platformTinyBlack.move(offset, 0);
      platformTinyGreen.move(offset, 0);
    } else {
      platformTinyBlack.move(-offset, 0);
      platformTinyGreen.move(-offset, 0);
    }
  }

  void moveMedium(float offset, bool isRight) {
    if (isRight == true) {
      platformMediumBlack.move(offset, 0);
      platformMediumGreen.move(offset, 0);
    } else {
      platformMediumBlack.move(-offset, 0);
      platformMediumGreen.move(-offset, 0);
    }
  }

  void moveLarge(float offset, bool isRight) {
    if (isRight == true) {
      platformLargeBlack.move(offset, 0);
      platformLargeGreen.move(offset, 0);
    } else {
      platformLargeBlack.move(-offset, 0);
      platformLargeGreen.move(-offset, 0);
    }
  }

  sf::RectangleShape& getPlatformSmallBlack_1() { return platformSmallBlack_1; }
  sf::RectangleShape& getPlatformSmallGreen_1() { return platformSmallGreen_1; }
 sf::RectangleShape& getPlatformSmallBlack_2() { return platformSmallBlack_2; }
  sf::RectangleShape& getPlatformSmallGreen_2() { return platformSmallGreen_2; }
  sf::RectangleShape& getPlatformTinyBlack() { return platformTinyBlack; }
  sf::RectangleShape& getPlatformTinyGreen() { return platformTinyGreen; }
  sf::RectangleShape& getPlatformMediumBlack() { return platformMediumBlack; }
  sf::RectangleShape& getPlatformMediumGreen() { return platformMediumGreen; }
  sf::RectangleShape& getPlatformLargeBlack() { return platformLargeBlack; }
  sf::RectangleShape& getPlatformLargeGreen() { return platformLargeGreen; }
};
#endif
