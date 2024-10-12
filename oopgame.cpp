#include <SFML/Graphics.hpp>
#include <string>

#include "Sans.h"
#include "BulletBoard.h"
#include "Soul.h"

#include "LongBone.h"
#include "MediumBone.h"

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
                        mediumBone->spawn(Vector2f(board->getCenter().x + (board->getSize().x / 2.0f), -(mediumBone->getSize().y / 2.0f) + board->getCenter().y + (board->getSize().y / 2)), 0);
                    }
                }
            }

            // move bone
            if (mediumBone->getIsActive()) {
                mediumBone->move(5,3);
            }

            if (sans->getIsIdle() == false) { // check if sans is called to move
                Vector2u winSize = win->getSize();
                sans->dodge((winSize.x/2.0f - winSize.x/6.4), winSize.x/2.0f); // perform his dodge sequence
            }

            

            if (mediumBone->attackSoul(soul)) {
                cout << "damage taken!" << endl;
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

            sans->draw(win);
            soul->draw(win);

            mediumBone->draw(win);
            
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
        }
};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
}   