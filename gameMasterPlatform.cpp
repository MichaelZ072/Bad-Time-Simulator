#include <SFML/Graphics.hpp>
#include <string>
#include <vector>  

#include "BulletBoard.h"
#include "Soul.h"
#include "act.h"
#include "actionInterface.h"
#include "actionSelect.h"
#include "fight.h"
#include "platformLevel_1.h"
#include "platformLevel_3.h"
#include "platformLevel_4.h"
#include "platformLevel_5.h"

using namespace sf;
using namespace std;

class GameMaster {
 private:
  RenderWindow* win;
  Clock clock;
  Time time;
  Board* board;
  Soul* soul;
  platform* plat;

  platformLevel_1* plat_1;
  platformLevel_2* plat_3;
  platformLevel_4* plat_4;
  platformLevel_5* plat_5;


 public:
  GameMaster(int sizeX, int sizeY, string title) {
    win = new RenderWindow(VideoMode(sizeX, sizeY), title);
    board = new Board(sizeX, sizeY, 5);
    soul = new Soul(board, 92, 4, 20, 0, true);
    //plat_1 = new platformLevel_1(board, 2.0f);
    plat_3 = new platformLevel_3(board, 5.0f);
    plat_4 = new platformLevel_3(board, 5.0f);
    plat_5 = new platformLevel_5(board, 5.0f);
  }

  void timer() {
    while (win->isOpen()) {
      time = clock.getElapsedTime();
      if (time.asMilliseconds() % (1000 / 30) == 0) {
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
      //plat_1->updatePlatforms(time.asSeconds());  
     // plat_1->moveSmallPlatforms();

      //plat_3->updatePlatforms(time.asSeconds());
      //plat_3->moveMediumPlatforms();
     // plat_3->moveLargePlatforms();

      //plat_4->updatePlatforms(time.asSeconds()); 
      //if(plat_4->getPlatformSmallBlack().getPosition().x<200){
      //plat_4->moveSmallRightPlatforms();
      //}else if(plat_4->getPlatformSmallBlack().getPosition().x>=600){
       // plat_4->moveSmallLeftPlatforms();
      //}

    plat_5->updatePlatforms(time.asSeconds());  
     plat_5->moveSmallPlatforms_1();
     plat_5->moveSmallPlatforms_2();

      board->changeIntermission1(640, 480);

      win->clear();

      //plat_1->renderPlatforms(*win); 
      //plat_3->renderPlatforms(*win); 
      //plat_4->renderPlatforms(*win);
      plat_5->renderPlatforms(*win);

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
