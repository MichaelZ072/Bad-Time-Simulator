#include <SFML/Graphics.hpp>
#include <string>

#include "BulletBoard.h"
#include "Soul.h"

using namespace sf;
using namespace std;

class GameMaster 
{
    private:
        RenderWindow* win;
        Board* board;
        Soul* soul;
        Clock clock;
        Time time;
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            win = new RenderWindow(VideoMode(sizeX, sizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92, 6, 20);
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
                if(event.type == Event::Closed) {
                    win->close();
                }

                if(Keyboard::isKeyPressed(Keyboard::Up)) {
                    soul->moveUp();
                } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    soul->moveDown();
                } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    soul->moveLeft();
                } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    soul->moveRight();
                }
            }

            win->clear();
            board->draw(win);
            soul->draw(win);
            win->display();
        }

        ~GameMaster() {}

};

int main() 
{
    GameMaster game(640, 480, "OOP Game");
    game.timer();

    return 0;
}