#include <SFML/Graphics.hpp>
#include <string>
#include "Sans.h"

using namespace sf;
using namespace std;

class OOPGame 
{
    private:
        RenderWindow* win;
        Sans* sans;
    
    public:
        OOPGame(int sizeX, int sizeY, string title) {
            win = new RenderWindow(VideoMode(sizeX, sizeY), title);
            sans = new Sans(sizeX/2.0f,sizeY/2.0f,1,"assets/sansDefPos.png");
        }
        void run() {
            while (win->isOpen())
            {
                Event event;
                while (win->pollEvent(event))
                {
                    if(event.type == Event::Closed)
                    {
                        win->close();
                    }
                }
            win->clear();
            sans->draw(win);
            win->display();
            }

        }
        ~OOPGame() {}

};

int main() 
{
    OOPGame game(640, 480, "OOP Game");
    game.run();

    return 0;
}