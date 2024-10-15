  #include <SFML/Graphics.hpp>
  #include <string>

  #include "BulletBoard.h"
  #include "Soul.h"
  #include "act.h"
  #include "actionInterface.h"
  #include "actionSelect.h"
  #include "fight.h"

  using namespace sf;
  using namespace std;

  class GameMaster {
  private:
    RenderWindow* win;
    Clock clock;
    Time time;
    actionInterface* action;
    Board* board;
    Soul* soul;
    actionSelect* attack;
    actionSelect* inspect;
    actionSelect* spare;

  public:
    GameMaster(int sizeX, int sizeY, string title) {
      win = new RenderWindow(VideoMode(sizeX, sizeY), title);
      board = new Board(sizeX, sizeY, 5);
      soul = new Soul(board, 92, 4, 20, 0, true);
      // create actionInterface object
      action = new actionInterface(5, true, soul);
      attack = new fight(10);
      spare = new mercy(10);
      inspect = new act(10);
    }

    void timer() {
      while (win->isOpen()) {
        time = clock.getElapsedTime();
        if (time.asMilliseconds() % (2000 / 30) == 0) {
          run();
        }
      }
    }

    void run() {
      Event event;

      while (win->pollEvent(event)) {
        if (event.type == Event::Closed) {
          win->close();
        }
      }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
          if (action->getIsChoose() == true || action->getIsSelect() == true) {
          } else {
            soul->moveUp();
          }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
          if (action->getIsChoose() == true || action->getIsSelect() == true) {
          } else {
            soul->moveDown();
          }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
         if(action->getEndIntermission() == false){ 
          if (action->getIsSelect() == false) {
            soul->intermissionMoveLeft();
            action->updateSpriteTextures(soul->getIntermissionPositionCount());
            cout << soul->getIntermissionPositionCount() << endl;
          }
        }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
         if(action->getEndIntermission() == false){ 
          if (action->getIsSelect() == false) {
            soul->intermissionMoveRight();
            action->updateSpriteTextures(soul->getIntermissionPositionCount());
            cout << soul->getIntermissionPositionCount() << endl;
          }
        }}

        if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
         if(action->getEndIntermission() == false){ 
          action->returnState();
        }}

        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
          if (action->getIsSelect() == false && action->getIsChoose() == true) {
            action->battleSelection(soul->getIntermissionPositionCount());
          } else if (action->getIsSelect() == true && action->getIsChoose() == false && action->getIsSelected() == false) {
          
            action->actionSelection(action->getSelectedNumber());
            
            if(action->getSelectedNumber() == 0){
            action->attackSelected();

            }


          }else if(action->getIsAction() == true && action->getIsAnimation() == true){
              action->isAttacked();
              
          }
    }
    if(action->getIsAnimationEnd() == true){


    }else{
      action->moveAttackBar(action->getIsAnimation(),20);
      action->animationCheck();
    }

        while (win->pollEvent(event)) {
          if (event.type == Event::Closed) {
            win->close();
          }
        }

        board->changeIntermission1(640, 480);

        win->clear();

        // Draw the sprite from actionInterface
        win->draw(action->getAct());
        win->draw(action->getFight());
        win->draw(action->getItem());
        win->draw(action->getMercy());
        win->draw(action->getLevelSprite());
        win->draw(action->getTextSprite());
        win->draw(action->getSansSelect());
        win->draw(action->getAttackBarSprite());
        win->draw(action->getSelectionSprite());
        win->draw(action->getAttackBar());
        board->draw(win);
        soul->draw(win);

        win->display();
    }
  };

  int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
  }
