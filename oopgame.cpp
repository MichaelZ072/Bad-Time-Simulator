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
            sans = new Sans(sizeX/2.0f, sizeY/2.0f, 1, 2, "assets/sansUp.png");
        }
        void run() {
            while (win->isOpen())
            {
                Event event;
                while (win->pollEvent(event))
                {
                    if(event.type == Event::Closed){
                        win->close();
                    } else if (Keyboard::isKeyPressed(Keyboard::Space)){
                        sans->setBody("assets/sansBody.png");
                    }
                }
            win->clear(Color::Black);
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