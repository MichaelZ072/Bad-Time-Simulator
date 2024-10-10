#include <SFML/Graphics.hpp>
#include <string>
#include "actionInterface.h"
#include "BulletBoard.h"

using namespace sf;
using namespace std;

class GameMaster {
private:
    RenderWindow* win;
    Clock clock;
    Time time;
    actionInterface* action; // Pointer to an actionInterface instance
    Board* board;

public:
    GameMaster(int sizeX, int sizeY, string title) {
        win = new RenderWindow(VideoMode(sizeX, sizeY), title); 
        board = new Board(sizeX, sizeY, 5); 
     
        //create actionInterface object
        action = new actionInterface(5, true); 
    }

    void timer() {
        while (win->isOpen()) {
            time = clock.getElapsedTime();
            if (time.asMilliseconds() % 10 == 0) {
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

   board->changeIntermission1(640,480);


        win->clear();
        
        // Draw the sprite from actionInterface
        win->draw(action->getActIdle()); 
        win->draw(action->getFightIdle());
        win->draw(action->getItemIdle());
        win->draw(action->getMercyIdle());
        win->draw(action->getLevelSprite());
        board->draw(win);
        //win->draw(action->getBlueSoulSprite());

        win->display();
    }

};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();
   
    return 0;
}
