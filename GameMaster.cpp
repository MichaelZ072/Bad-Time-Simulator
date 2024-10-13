#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "BulletBoard.h"
#include "Soul.h"

#include "BlasterAttackLevel_1.h"
#include "BlasterAttackLevel_2.h"

using namespace sf;
using namespace std;

class GameMaster 
{
    private:
        RenderWindow* win;
        int winSizeX;
        int winSizeY;
        Board* board;
        Soul* soul;
        BlasterAttackLevel_1* blasterAttackLevel_1;
        BlasterAttackLevel_2* blasterAttackLevel_2;
        Clock clock;
        Time time;
        int deltaFrames;
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            deltaFrames = 0;
            win = new RenderWindow(VideoMode(winSizeX, winSizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92, 5, 20);
            blasterAttackLevel_1 = new BlasterAttackLevel_1;
            blasterAttackLevel_2 = new BlasterAttackLevel_2;
        }

        void timer(){
            while (win->isOpen()) {
                time = clock.getElapsedTime();
                if (time.asMilliseconds() % (1000 / 30) == 0 ) {
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
                soul->moveUp();
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                soul->moveDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                soul->moveLeft();
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                soul->moveRight();
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                blasterAttackLevel_1->startAttack();
                //board->startAnimation();
            }

            if (blasterAttackLevel_1->checkAttack()) {
                blasterAttackLevel_1->attack(soul);
                deltaFrames++;
            }

            if (blasterAttackLevel_1->checkAttack() && deltaFrames > 26) {
                blasterAttackLevel_2->startAttack();
            }

            if (blasterAttackLevel_2->checkAttack()) {
                blasterAttackLevel_2->attack(soul);
            }

            if (board->checkAnimation()) {
                board->changeIntermission1(winSizeX, winSizeY);
            }

            win->clear();
            board->draw(win);
            soul->draw(win);
            blasterAttackLevel_1->draw(win);
            blasterAttackLevel_2->draw(win);
            win->display();
        }

        ~GameMaster() {}

};

int main() 
{
    GameMaster game(640, 480, "Bad Time Simulator");
    game.timer();

    return 0;
}