#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "AttackLevels.h"
#include "BlasterAttackLevel_1.h"
#include "BlasterAttackLevel_2.h"
#include "BlasterAttackLevel_3.h"
#include "BulletBoard.h"
#include "Sans.h"
#include "Soul.h"
#include "act.h"
#include "actionInterface.h"
#include "actionSelect.h"
#include "fight.h"
#include "item.h"
#include "mercy.h"
#include "platform.h"
#include "platformLevel_1.h"
#include "platformLevel_2.h"
#include "platformLevel_3.h"

using namespace sf;
using namespace std;

class GameMaster {
 private:
  RenderWindow* win;
  int winSizeX;
  int winSizeY;
  Sans* sans;
  Board* board;
  Soul* soul;
  vector<unique_ptr<AttackLevels>> attacks;
  vector<unique_ptr<platform>> platforms;
  vector<FloatRect> platformBounds;
  Clock clock;
  Time time;
  int deltaFrames;
  int level;
  int platformLevel;
  bool intermission;
  bool isFinalPhase;
  actionInterface* action;
  actionSelect* attack;
  actionSelect* inspect;
  actionSelect* spare;
  actionSelect* choose;

 public:
  GameMaster(int sizeX, int sizeY, string title) {
    winSizeX = sizeX;
    winSizeY = sizeY;
    deltaFrames = 0;
    win = new RenderWindow(VideoMode(winSizeX, winSizeY), title);
    board = new Board(sizeX, sizeY, 5);
    sans = new Sans(
        sizeX / 2.0f, board->getCenter().y - board->getSize().y / 2.0f - 20, 1,
        "assets/sansFaceEyesClosed.png", "assets/sansTorso.png",
        "assets/sansLeg.png", "fonts/ComicSans-Pixel.ttf", "ready?");
    soul = new Soul(board, 92);
    action = new actionInterface(50, true, soul);
    attack = new fight(10);
    spare = new mercy(10);
    inspect = new act(10);

    attacks.push_back(make_unique<BlasterAttackLevel_1>());
    attacks.push_back(make_unique<BlasterAttackLevel_2>());
    attacks.push_back(make_unique<BlasterAttackLevel_1>());
    attacks.push_back(make_unique<BlasterAttackLevel_3>());

    platforms.push_back(make_unique<platformLevel_1>(board, 0));
    platforms.push_back(make_unique<platformLevel_2>(board, 0));
    platforms.push_back(make_unique<platformLevel_3>(board, 0));

    level = -1;
    platformLevel = -1;
    intermission = false;
  }

  // This is used to set the framerate of the game, keeping everything
  // consistent
  void timer() {
    while (win->isOpen()) {
      time = clock.getElapsedTime();
      if (time.asMilliseconds() % (1000 / 30) == 0) {
        run();
      }
    }
  }

  // Runs the game
  void run() {
    Event event;

    // Checks if the window is closed
    while (win->pollEvent(event)) {
      if (event.type == Event::Closed) {
        win->close();
      }

      if (intermission) {
        checkInput();
      }
    }
    if (intermission) {
      if (action->getIsAnimationEnd() == true) {
      } else {
        action->moveAttackBar(action->getIsAnimation(), 20);
        action->animationCheck();
      }
    if(isFinalPhase == true){
        finalIntermission();
        isFinalPhase = false;
      }
    }
    action->updateHealth(action->getCurrentHealth());
    if (level > 13) {
      // game won
    } else if (level > 6) {
      if (intermission) {
        if (board->getState() == 1) {
          board->startAnimation();
          soul->changePosition(Vector2f(-20, -20));
        }

        if (board->checkAnimation()) {
          board->changeIntermission2(winSizeX, winSizeY);
        }

        // logic to do with menu
      } else {
        if (board->getState() == 3) {
          board->startAnimation();
          soul->changePosition(Vector2f(
              winSizeX / 2, board->getCenter().y + board->getSize().y / 2 - 8));
          soul->makeBlue();
        }

        if (board->checkAnimation()) {
          board->changeBlue1(winSizeX, winSizeY);
        }

        checkMovement();

        if (deltaFrames > 300) {
          intermission = true;
        }

        deltaFrames++;
      }
    } else if (level > -1) {
      if (intermission) {
        if (board->getState() == 0) {
          board->startAnimation();
          soul->changePosition(Vector2f(-20, -20));
          sans->moveFull(0, 30);
        }

        if (board->checkAnimation()) {
          board->changeIntermission1(winSizeX, winSizeY);
        }

        // logic to do with menu

      } else {
        checkMovement();

        if (deltaFrames > 150) {
          intermission = true;
        } else if (deltaFrames > 78) {
          level = 3;
        } else if (deltaFrames > 52) {
          level = 2;
        } else if (deltaFrames > 26) {
          level = 1;
        }

        switch (level) {
          case 0:
            attacks.at(0)->startAttack();
            // soul->makeBlue();
            break;
          case 1:
            attacks.at(1)->startAttack();
            // soul->makeRed();
            break;
          case 2:
            attacks.at(2)->startAttack();
            break;
          case 3:
            attacks.at(3)->startAttack();
            break;
          case 4:
            attacks.at(3)->startAttack();
            break;
          case 5:
            attacks.at(3)->startAttack();
            break;
          case 6:
            attacks.at(3)->startAttack();
            break;
        }

        for (auto& attack : attacks) {
          if (attack->checkAttack()) {
            attack->attack(soul);
          }
        }

        deltaFrames++;
      }
    } else {
      if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        level = 0;
        intermission = false;
        sans->setHead("assets/sansFace.png");
        sans->mute();
      }
    }

    win->clear();
    sans->draw(win);
    board->draw(win);
    soul->draw(win);
    win->draw(action->getAct());
    win->draw(action->getFight());
    win->draw(action->getItem());
    win->draw(action->getMercy());
    win->draw(action->getLevelSprite());
    action->drawHealth(*win);

    if (intermission == true) {
      win->draw(action->getSansSelect());
      win->draw(action->getAttackBarSprite());
      win->draw(action->getSelectionSprite());
      win->draw(action->getAttackBar());
      soul->draw(win);
    }

    for (auto& attack : attacks) {
      attack->draw(win);
    }

    win->display();
  }

  // This checks and updates the player based on keypresses
  void checkMovement() {
    soul->upPress(Keyboard::isKeyPressed(Keyboard::Up));

    // Controls player movement using the arrow keys
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      soul->moveLeft(board);
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      soul->moveRight(board);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
      soul->moveUp(board);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
      soul->moveDown(board);
    }

    if (platformLevel == -1) {
      vector<FloatRect> empty({FloatRect(0, 0, 0, 0)});
      platformBounds = empty;
    } else {
      platformBounds = platforms.at(platformLevel)->getAllPlatformBounds();
    }

    soul->update(board, platformBounds);
  }

  void checkInput() {
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      if (action->getIsSelect() == false) {
        soul->intermissionMoveLeft();
        action->updateSpriteTextures(soul->getIntermissionPositionCount());
        cout << soul->getIntermissionPositionCount() << endl;
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      if (action->getIsSelect() == false) {
        soul->intermissionMoveRight();
        action->updateSpriteTextures(soul->getIntermissionPositionCount());
        cout << soul->getIntermissionPositionCount() << endl;
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
      action->returnState();
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
      if (action->getIsSelect() == false && action->getIsChoose() == true) {
        action->battleSelection(soul->getIntermissionPositionCount());

      } else if (action->getIsSelect() == true &&
                 action->getIsChoose() == false &&
                 action->getIsSelected() == false) {
        action->actionSelection(action->getSelectedNumber());


        if (action->getSelectedNumber() == 0) {
          action->attackSelected();
        }else{
        isFinalPhase = true;
        }

      } else if (action->getIsAction() == true &&
                 action->getIsAnimation() == true) {
        action->isAttacked();
        isFinalPhase = true;
    }
  }
  }

void finalIntermission(){
    level++;
    action->remove();
    level++;
    
    intermission = false;
}

  ~GameMaster() {
    delete win;
    delete board;
    delete soul;
  }
};

int main() {
  GameMaster game(640, 480, "Bad Time Simulator");
  game.timer();

  return 0;
}