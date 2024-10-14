#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "BulletBoard.h"
#include "Soul.h"

#include "AttackLevels.h"
#include "BlasterAttackLevel_1.h"
#include "BlasterAttackLevel_2.h"
#include "BlasterAttackLevel_3.h"

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
        vector<unique_ptr<AttackLevels>> attacks;
        Clock clock;
        Time time;
        int deltaFrames;
        int level;
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            deltaFrames = 0;
            win = new RenderWindow(VideoMode(winSizeX, winSizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92, 5, 20);

            attacks.push_back(make_unique<BlasterAttackLevel_1>());
            attacks.push_back(make_unique<BlasterAttackLevel_2>());
            attacks.push_back(make_unique<BlasterAttackLevel_1>());
            attacks.push_back(make_unique<BlasterAttackLevel_3>());

            level = -1;
        }

        // This is used to set the framerate of the game, keeping everything consistent
        void timer(){
            while (win->isOpen()) {
                time = clock.getElapsedTime();
                if (time.asMilliseconds() % (1000 / 30) == 0 ) {
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
            }
            
            // Controls player movement using the arrow keys
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                soul->moveUp(board);
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                soul->moveDown(board);
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                soul->moveLeft(board);
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                soul->moveRight(board);
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                level = 0;
                //board->startAnimation();
                //attacks.at(0)->startAttack();
            }

            if (level == 0) {
                attacks.at(0)->startAttack();
                deltaFrames++;
            }

            for (auto& attack : attacks) {
                if (attack->checkAttack()) {
                    attack->attack(soul);
                }
            }

            if (deltaFrames > 26) {
                attacks.at(1)->startAttack();
            }

            if (deltaFrames > 52) {
                attacks.at(2)->startAttack();
            }

            if (deltaFrames > 72) {
                attacks.at(3)->startAttack();
            }

            if (board->checkAnimation()) {
                board->changeIntermission1(winSizeX, winSizeY);
            }

            win->clear();
            board->draw(win);
            soul->draw(win);
            
            for (auto& attack : attacks) {
                attack->draw(win);
            }
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