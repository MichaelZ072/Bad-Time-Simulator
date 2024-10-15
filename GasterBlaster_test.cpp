#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Soul.h"
#include "GasterBlasters.h"

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
        GasterBlasters* blaster;
        Clock clock;
        Time time;
        int deltaFrames;
        bool fired;
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            deltaFrames = 0;
            fired = false;
            win = new RenderWindow(VideoMode(winSizeX, winSizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92);
            blaster = new GasterBlasters(Vector2f(-10, 0), Vector2f(3, 3), 0); // (0, 245), (3, 3), 0
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

            if ((blaster != nullptr)) {
                if (deltaFrames > 60) {
                    blaster->startAnimation();
                }

                if (blaster->checkAnimation() && !blaster->checkFlownIn()) {
                    blaster->flyIn(Vector2f(320, 120), 5, 0, 1); // (140, 305), 5, 270, -1
                } else if (blaster->checkAnimation() && deltaFrames > 100) {
                    blaster->flyOut(45, 16);
                }
            } else {
                //delete blaster;
                //blaster = nullptr;
            }

            deltaFrames++;

            win->clear();
            board->draw(win);
            if ((blaster != nullptr)) {
                blaster->draw(win);
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