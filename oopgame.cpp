#include <SFML/Graphics.hpp>
#include <string>
#include "Sans.h"

using namespace sf;
using namespace std;

class GameMaster 
{
    private:
        RenderWindow* win;
        Sans* sans;
        Clock clock;
        Time time;
        
        Time sansTimer;
        
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            win = new RenderWindow(VideoMode(sizeX, sizeY), title);
            sans = new Sans(sizeX/2.0f, sizeY/2.0f, 1, "assets/sansFaceEyesClosed.png", "assets/sansTorso.png", "assets/sansLeg.png", "fonts/ComicSans-Pixel.ttf", "ready?");
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
                } else if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    sans->setIsIdle(false);
                }
            }

            if (sans->getIsIdle() == false) { // check if sans is called to move
                Vector2u winSize = win->getSize();
                sans->dodge((winSize.x/2.0f - winSize.x/6.4), winSize.x/2.0f); // perform his dodge sequence
            } 
                 
            win->clear();
            sans->draw(win);
            
            win->display();
        }

        ~GameMaster() {}
};

int main() {
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
}