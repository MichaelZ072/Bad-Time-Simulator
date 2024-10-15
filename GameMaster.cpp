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
        bool intermission;
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
            intermission = true;
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

                if (intermission) {
                    //checkInput();
                }
            }
            
            if (level > 13) {
                // game won
            } else if (level > 6) {
                // phase 2 levels
            } else if (level > -1) {
                if (intermission) {
                    if (board->getState() == 0) {
                        board->startAnimation();
                        soul->changePosition(Vector2f(-20, -20));
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
                            break;
                        case 1:
                            attacks.at(1)->startAttack();
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
                }
            }

            win->clear();
            board->draw(win);
            soul->draw(win);
            
            for (auto& attack : attacks) {
                attack->draw(win);
            }

            win->display();
        }

        ~GameMaster() {
            delete win;
            delete board;
            delete soul;
        }

        // This checks and updates the player based on keypresses
        void checkMovement() {
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
        }

        void checkInput() {
            
        }
};

int main() 
{
    GameMaster game(640, 480, "Bad Time Simulator");
    game.timer();

    return 0;
}