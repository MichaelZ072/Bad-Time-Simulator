#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Sans.h"
#include "BulletBoard.h"
#include "Soul.h"

#include "AttackLevels.h"
#include "BoneAttackLevel_1.h"
#include "BoneAttackLevel_2.h"

#include "Bones.h"
#include "LongBone.h"
#include "MediumBone.h"
#include "BoneWall.h"
#include "CustomBone.h"
#include "TinyBone.h"
#include "ShortBone.h"

#include "Cover.h"

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
        Sans* sans;
        Cover* shader;
        // vector<unique_ptr<AttackLevels>> attacks;
        BoneAttackLevel_2* attack;
        
        Clock clock;
        Time time;
        int level;
        
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            win = new RenderWindow(VideoMode(sizeX, sizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92, 4, 20);
            sans = new Sans(sizeX/2.0f, board->getCenter().y - board->getSize().y / 2.0f - 20, 1, "assets/sansFaceEyesClosed.png", "assets/sansTorso.png", "assets/sansLeg.png", "fonts/ComicSans-Pixel.ttf", "ready?");
            shader = new Cover(board, sizeX, sizeY);
            // attacks.push_back(make_unique<BoneAttackLevel_1>(board));
            attack = new BoneAttackLevel_2(board);
            level = -1;
        }

        void timer() {
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
                if(event.type == Event::Closed) {
                    win->close();
                } else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    sans->setIsIdle(false);
                    
                }

                if (Keyboard::isKeyPressed(Keyboard::Q)) {
                    board->startAnimation();
                }

                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    level = 0;
                    //board->startAnimation();
                    //attacks.at(0)->startAttack();
                }
            }

            
            // player movement
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

            if (Keyboard::isKeyPressed(Keyboard::P)) {
                level = 1;
            }
            
            if (level == 0) {
                attack->updateSpawn(); // ensure that bones arent spawned simultaneously
                attack->startAttack();
            }

            if (board->checkAnimation()) {
                board->changeIntermission1(winSizeX, winSizeY);
            }

            win->clear();
        
            if (attack->checkAttack()) {
                attack->attack(soul);
            }
        
            // everything above shader will appear behind it    
            shader->draw(win);
            shader->updateCover(board);
            // everything below shader will appear above it

            
            attack->draw(win);

            sans->draw(win);
            soul->draw(win);
            board->draw(win);
                  
            win->display();
        }

        ~GameMaster() {
            delete win;
            delete board;
            delete soul;
            delete sans;
            delete shader;

            /*
            delete mediumBone;
            
            delete custom;
            delete tinyBone;
            delete shortBone;
            delete longBone;
            */
        }
};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
}   