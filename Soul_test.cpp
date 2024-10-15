#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Soul.h"

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
        Clock clock;
        Time time;
        int deltaFrames;
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            deltaFrames = 0;
            win = new RenderWindow(VideoMode(winSizeX, winSizeY), title);
            board = new Board(sizeX, sizeY, 5);
            soul = new Soul(board, 92);
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

            //if (deltaFrames < 5) {
            //    soul->moveUp(board);
            //} else if (soul->getPosition().y != board->getCenter().y - 25) {
            //    cout << "Test was unsucessful" << endl;
            //}

            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                soul->makeBlue();
                board->startAnimation();
            }

            if (board->checkAnimation()) {
                board->changeBlue1(winSizeX, winSizeY);
            }

            checkMovement();

            //cout << soul->isOnGround() << endl;

            //deltaFrames++;

            win->clear();
            board->draw(win);
            soul->draw(win);
            win->display();
        }

        // This checks and updates the player based on keypresses
        void checkMovement() {
            soul->upPress(Keyboard::isKeyPressed(Keyboard::Up));
            
            // Controls player movement using the arrow keys
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                soul->moveLeft(board);
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                soul->moveRight(board);
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                soul->moveUp(board);
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                soul->moveDown(board);
            }

            soul->update(board);
        }

        ~GameMaster() {}

};

int main() 
{
    GameMaster game(640, 480, "Bad Time Simulator");
    game.timer();

    return 0;
}