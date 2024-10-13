#include <SFML/Graphics.hpp>
#include <string>

#include "Sans.h"
#include "BulletBoard.h"
#include "Soul.h"

#include "LongBone.h"
#include "MediumBone.h"
#include "BoneWall.h"
#include "Cover.h"


using namespace sf;
using namespace std;

class GameMaster 
{
    private:
        RenderWindow* win;

        Board* board;
        Soul* soul;
        Sans* sans;
        LongBone* longBone;
        MediumBone* mediumBone;
        BoneWall* boneWall;
        Cover* shader;

        Clock clock;
        Time time;
        
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            win = new RenderWindow(VideoMode(sizeX, sizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92, 4, 20);
            // replace 80 with board dimensions
            sans = new Sans(sizeX/2.0f, board->getCenter().y - board->getSize().y / 2.0f - 20, 1, "assets/sansFaceEyesClosed.png", "assets/sansTorso.png", "assets/sansLeg.png", "fonts/ComicSans-Pixel.ttf", "ready?");
            mediumBone = new MediumBone(sizeX / 2.0f, sizeY / 2.0f, 100, 0); 
            boneWall = new BoneWall(sizeX / 2.0f, sizeY / 2.0f, 10);
            shader = new Cover(board, sizeX, sizeY); 
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

                // spawn bone
                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    // prevents spamming space to reset position
                    if (!mediumBone->getIsActive()) {
                        mediumBone->spawn(Vector2f(board->getCenter().x + (board->getSize().x / 2.0f), -(mediumBone->getSize().y / 2.0f) + board->getCenter().y + (board->getSize().y / 2)), 0, 3);
                    }

                    if (!boneWall->getIsActive()) {
                        // spawn a bone wall starting from the bottom and going up
                        // boneWall->spawn(Vector2f(board->getCenter().x, board->getCenter().y + board->getSize().y / 2.0f + boneWall->getSize().x / 2.0f), 90, 0);

                        // spawn a bone wall starting from the top and going down
                        // boneWall->spawn(Vector2f(board->getCenter().x, board->getCenter().y - board->getSize().y / 2.0f - boneWall->getSize().x / 2.0f), 90, 2);

                        // spawn a bone wall starting from the left and going right
                        // boneWall->spawn(Vector2f(board->getCenter().x - board->getSize().x / 2.0f - boneWall->getSize().x / 2.0f, board->getCenter().y), 0, 1);

                        // spawn a bone wall starting from the right and going left
                        boneWall->spawn(Vector2f(board->getCenter().x + board->getSize().x / 2.0f + boneWall->getSize().x / 2.0f, board->getCenter().y), 0, 3);
                    }
                }
            }

            // move bone
            if (mediumBone->getIsActive()) {
                mediumBone->callAttack(5, 1);
                if (mediumBone->attackSoul(soul)) {
                    cout << "damage taken!" << endl;
                }
            }

            if (boneWall->getIsActive()) {
                boneWall->callAttack(15, 0.5, 1.5, 4);
                if (boneWall->checkCollision(soul)) {
                    cout << "damage taken!" << endl;
                }
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

            mediumBone->draw(win);            
            boneWall->draw(win);

            // everything above shader will appear behind it
            shader->draw(win);
            // everything below shader will appear above it

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
        }
};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
}   