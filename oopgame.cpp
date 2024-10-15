#include <SFML/Graphics.hpp>
#include <string>

#include "Sans.h"
#include "BulletBoard.h"
#include "Soul.h"

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
        MediumBone* mediumBone;
        BoneWall* boneWall;
        CustomBone* custom;
        TinyBone* tinyBone;
        ShortBone* shortBone;
        LongBone* longBone;

        Cover* shader;

        Clock clock;
        Time time;
        
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            win = new RenderWindow(VideoMode(sizeX, sizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92, 4, 20);
            // replace 80 with board dimensions
            sans = new Sans(sizeX/2.0f, board->getCenter().y - board->getSize().y / 2.0f - 20, 1, "assets/sansFaceEyesClosed.png", "assets/sansTorso.png", "assets/sansLeg.png", "fonts/ComicSans-Pixel.ttf", "ready?");
            mediumBone = new MediumBone(); 
            boneWall = new BoneWall();
            shader = new Cover(board, sizeX, sizeY); 
            custom = new CustomBone(10);
            tinyBone = new TinyBone();
            shortBone = new ShortBone();
            longBone = new LongBone();
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

                // spawn bone
                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    // prevents spamming space to reset position
                    if (!mediumBone->getIsActive()) {
                        mediumBone->spawn(Vector2f(board->getCenter().x + (board->getSize().x / 2.0f), -(mediumBone->getSize().y / 2.0f) + board->getCenter().y + (board->getSize().y / 2)), 0, 0);
                    }

                    if (!boneWall->getIsActive()) {
                        // spawn a bone wall starting from the bottom and going up
                        // boneWall->spawn(Vector2f(board->getCenter().x, board->getCenter().y + board->getSize().y / 2.0f + boneWall->getSize().x / 2.0f), 90, 0);

                        // spawn a bone wall starting from the top and going down
                        // boneWall->spawn(Vector2f(board->getCenter().x, board->getCenter().y - board->getSize().y / 2.0f - boneWall->getSize().x / 2.0f), 90, 2);

                        // spawn a bone wall starting from the left and going right
                        // boneWall->spawn(Vector2f(board->getCenter().x - board->getSize().x / 2.0f - boneWall->getSize().x / 2.0f, board->getCenter().y), 0, 1);

                        // spawn a bone wall starting from the right and going left
                        // boneWall->spawn(Vector2f(board->getCenter().x + board->getSize().x / 2.0f + boneWall->getSize().x / 2.0f, board->getCenter().y), 0, 3);
                    }

                    if (!custom->getIsActive()) {
                        // right now only works for 270 (horizontal) or 0 (vertical)
                        // custom->spawn(Vector2f(winSizeX, board->getCenter().y), 270, 3);
                    }

                    if (!tinyBone->getIsActive()) {
                        // right now only works for 270 (horizontal) or 0 (vertical)
                        tinyBone->spawn(Vector2f(winSizeX, board->getCenter().y), 0, 3);
                    }

                    if (!shortBone->getIsActive()) {
                        // right now only works for 270 (horizontal) or 0 (vertical)
                        shortBone->spawn(Vector2f(winSizeX, board->getCenter().y), 0, 3);
                    }

                    if (!longBone->getIsActive()) {
                        // right now only works for 270 (horizontal) or 0 (vertical)
                        longBone->spawn(Vector2f(winSizeX, board->getCenter().y), 0, 3);
                    }
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

            if (board->checkAnimation()) {
                board->changeIntermission1(winSizeX, winSizeY);
            }

            if (tinyBone->getIsActive()) {
                tinyBone->callAttack(5, 100);
                tinyBone->checkCollision(soul);
            }

            if (shortBone->getIsActive()) {
                shortBone->callAttack(3, 100);
                shortBone->checkCollision(soul);
            }

            if (longBone->getIsActive()) {
                longBone->callAttack(7, 100);
                longBone->checkCollision(soul);
            }

            // cout << soul->getHealth() << endl;

            // move bone
            if (mediumBone->getIsActive()) {
                mediumBone->callAttack(5, 1, board->getCenter().y - board->getSize().y / 2.0f);
                mediumBone->checkCollision(soul);
            }

            if (boneWall->getIsActive()) {
                boneWall->callAttack(15, 0.5, 1.5, 4);
                boneWall->checkCollision(soul);
            }

            if (custom->getIsActive()) {
                custom->callAttack(5, 0, 1, 100);
                custom->checkCollision(soul);
            }



            if (!sans->getIsIdle()) { // check if sans is called to move
                Vector2u winSize = win->getSize();
                sans->dodge((winSize.x/2.0f - winSize.x/6.4), winSize.x/2.0f); // perform his dodge sequence
            }

            
            /*
            if (longBone->checkPlayerMovement(soul)) {
                cout << "player has moved to " << longBone->getSoulPosChecker().x << ", " << longBone->getSoulPosChecker().y << endl;
            }   

            if (longBone->checkCollision(soul)) {
                cout << "player has taken damage" << endl;
            }
            */

             
            win->clear();
       
            boneWall->draw(win);

            // everything above shader will appear behind it
            shader->draw(win);
            shader->updateCover(board);
            // everything below shader will appear above it

            custom->draw(win);
            mediumBone->draw(win);   
            tinyBone->draw(win);  
            shortBone->draw(win);
            longBone->draw(win);

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
            // delete longBone;
            delete mediumBone;
            delete shader;
            delete custom;
            delete tinyBone;
            delete shortBone;
            delete longBone;
        }
};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
}   