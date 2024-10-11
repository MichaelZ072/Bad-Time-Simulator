#include <SFML/Graphics.hpp>
#include <string>
#include "actionInterface.h"
#include "BulletBoard.h"
#include "Soul.h"

using namespace sf;
using namespace std;

class GameMaster {
private:
    RenderWindow* win;
    Clock clock;
    Time time;
    actionInterface* action; // Pointer to an actionInterface instance
    Board* board;
    Soul* soul;


public:
    GameMaster(int sizeX, int sizeY, string title) {
        win = new RenderWindow(VideoMode(sizeX, sizeY), title); 
        board = new Board(sizeX, sizeY, 5); 
        soul = new Soul(board, 92, 4, 20,true);
        //create actionInterface object
        action = new actionInterface(5, true, soul); 
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

                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    soul->moveUp();
                }
                
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    soul->moveDown();
                }

                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    soul->intermissionMoveLeft();
                }
                
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    soul->intermissionMoveRight();
                }

                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    board->doAnimation();
                }
            }

        
        while (win->pollEvent(event)) {
            if (event.type == Event::Closed) {
                win->close();
            }
        }

   board->changeIntermission1(640,480);


        win->clear();
        
        // Draw the sprite from actionInterface
        win->draw(action->getAct()); 
        win->draw(action->getFight());
        win->draw(action->getItem());
        win->draw(action->getMercy());
        win->draw(action->getLevelSprite());
        board->draw(win);
        //win->draw(action->getBlueSoulSprite());
        soul->draw(win);
        win->display();
    }

};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();
   
    return 0;
}
