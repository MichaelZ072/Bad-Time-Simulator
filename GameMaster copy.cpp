#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Sans.h"
#include "BulletBoard.h"
#include "Soul.h"

#include "actionInterface.h"
#include "actionSelect.h"
#include "fight.h"
#include "act.h"
#include "item.h"
#include "mercy.h"

#include "AttackLevels.h"

#include "BlasterAttackLevel_1.h"
#include "BlasterAttackLevel_2.h"
#include "BlasterAttackLevel_3.h"
#include "BlasterAttackLevel_4.h"
#include "BlasterAttackLevel_5.h"
#include "BlasterAttackLevel_6.h"
#include "BlasterAttackLevel_7.h"

#include "Cover.h"
#include "Bones.h"
#include "BoneWall.h"
#include "LongBone.h"
#include "MediumBone.h"
#include "ShortBone.h"
#include "TinyBone.h"
#include "BoneAttackLevel_1.h"
#include "BoneAttackLevel_2.h"
#include "BoneAttackLevel_3.h"
#include "BoneAttackLevel_4.h"
#include "BoneAttackLevel_5.h"
#include "BoneAttackLevel_6.h"
#include "BoneAttackLevel_7.h"

using namespace sf;
using namespace std;

class GameMaster 
{
    private:
        RenderWindow* win;
        int winSizeX;
        int winSizeY;
        Sans* sans;
        Board* board;
        Soul* soul;
        Cover* cover;
        vector<unique_ptr<AttackLevels>> blasterAttacks;
        vector<unique_ptr<AttackLevels>> boneAttacks;
        vector<FloatRect> platformBounds;
        Clock clock;
        Time time;
        int deltaFrames;
        int level;
        int platformLevel;
        bool intermission;
        bool isFinalPhase;
        actionInterface* action;
        actionSelect* attack;
        actionSelect* inspect;
        actionSelect* spare;
        actionSelect* choose;
    public:
        GameMaster(int sizeX, int sizeY, string title) {
            winSizeX = sizeX;
            winSizeY = sizeY;
            deltaFrames = 0;
            win = new RenderWindow(VideoMode(winSizeX, winSizeY), title);
            board = new Board(sizeX, sizeY, 5);
            sans = new Sans(sizeX/2.0f, board->getCenter().y - board->getSize().y / 2.0f - 20, 1, 
                "assets/sansFaceEyesClosed.png", "assets/sansTorso.png", "assets/sansLeg.png", 
                "fonts/ComicSans-Pixel.ttf", "ready?");
            soul = new Soul(board, 92);
            cover = new Cover(board, winSizeX, winSizeY);

            action = new actionInterface(50, true, soul);
            attack = new fight(10);
            spare = new mercy(10);
            inspect = new act(10);

            blasterAttacks.push_back(make_unique<BlasterAttackLevel_1>());
            blasterAttacks.push_back(make_unique<BlasterAttackLevel_2>());
            blasterAttacks.push_back(make_unique<BlasterAttackLevel_1>());
            blasterAttacks.push_back(make_unique<BlasterAttackLevel_3>());

            blasterAttacks.push_back(make_unique<BlasterAttackLevel_4>());
            blasterAttacks.push_back(make_unique<BlasterAttackLevel_5>());
            blasterAttacks.push_back(make_unique<BlasterAttackLevel_6>());
            blasterAttacks.push_back(make_unique<BlasterAttackLevel_7>());

            boneAttacks.push_back(make_unique<BoneAttackLevel_1>(board));

            for (int i = 0; i < 4; i++) {
                boneAttacks.push_back(make_unique<BoneAttackLevel_5>(board));
            }

            boneAttacks.push_back(make_unique<BoneAttackLevel_2>(board));

            boneAttacks.push_back(make_unique<BoneAttackLevel_4>(board));
            boneAttacks.push_back(make_unique<BoneAttackLevel_5>(board));
            boneAttacks.push_back(make_unique<BoneAttackLevel_6>(board));
            boneAttacks.push_back(make_unique<BoneAttackLevel_7>(board));

            boneAttacks.push_back(make_unique<BoneAttackLevel_3>(board));

            level = -1;
            platformLevel = -1;
            intermission = false;
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
            if (!soul->getAlive()) {
                //level = -2;
            }

            Event event;

            // Checks if the window is closed
            while (win->pollEvent(event)) {
                if (event.type == Event::Closed) {
                    win->close();
                }

                if (intermission) {
                    checkInput();
                }
                }
                if (intermission) {
                    if (action->getIsAnimationEnd() == true) {
                    } else {
                        action->moveAttackBar(action->getIsAnimation(), 20);
                        action->animationCheck();
                    }

                    if(isFinalPhase == true) {
                        finalIntermission();
                        isFinalPhase = false;
                    }
                }

            action->updateHealth(action->getCurrentHealth());

            if (level > -1 && !intermission) {
                checkMovement();
            }
            
            if (level > 6) {
                sans->setHead("assets/sansFaceEyesClosed.png");
                sans->talk("you have won...");

                if (board->getState() == 3) {
                        board->startAnimation();
                        soul->changePosition(Vector2f(winSizeX / 2, board->getCenter().y * 64 / 100));
                }

                if (board->checkAnimation()) {
                    board->changeRed(winSizeX, winSizeY);
                }
            } else if (level > 0) {
                if (intermission) {

                    switch (level) {
                        case 1:
                            for (int i = 1; i < 5; i++) {
                                boneAttacks.at(i) = make_unique<BoneAttackLevel_5>(board);
                            }
                            break;
                        case 2:
                            boneAttacks.at(5) = make_unique<BoneAttackLevel_2>(board);
                            break;
                        case 3:
                            boneAttacks.at(6) = make_unique<BoneAttackLevel_4>(board);
                            boneAttacks.at(7) = make_unique<BoneAttackLevel_5>(board);
                            boneAttacks.at(8) = make_unique<BoneAttackLevel_6>(board);
                            boneAttacks.at(9) = make_unique<BoneAttackLevel_7>(board);
                            break;
                        case 4:
                            blasterAttacks.at(4) = make_unique<BlasterAttackLevel_4>();
                            blasterAttacks.at(4) = make_unique<BlasterAttackLevel_5>();
                            blasterAttacks.at(4) = make_unique<BlasterAttackLevel_6>();
                            blasterAttacks.at(4) = make_unique<BlasterAttackLevel_7>();
                            break;
                        case 5:
                            boneAttacks.at(0) = make_unique<BoneAttackLevel_1>(board);
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_1>();
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_2>();
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_1>();
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_3>();
                            break;
                        case 6:
                            boneAttacks.at(0) = make_unique<BoneAttackLevel_1>(board);
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_1>();
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_2>();
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_1>();
                            blasterAttacks.at(0) = make_unique<BlasterAttackLevel_3>();
                            break;
                    }

                    if (board->getState() == 1) {
                        board->startAnimation();
                        soul->changePosition(Vector2f(-20, -20));
                    }

                    if (board->checkAnimation()) {
                        board->changeIntermission2(winSizeX, winSizeY);
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                        deltaFrames = 0;
                        level++;
                        intermission = false;
                    }
                } else {
                    if (board->getState() == 3) {
                        board->startAnimation();
                        if (level < 6) {
                            soul->changePosition(Vector2f(winSizeX / 2, board->getCenter().y + board->getSize().y / 2 - 8));
                        } else {
                            soul->changePosition(Vector2f(winSizeX / 2, board->getCenter().y * 64 / 100));
                        }
                        
                    }

                    if (board->checkAnimation()) {
                        if (level < 6) {
                            board->changeBlue1(winSizeX, winSizeY);
                        } else {
                            board->changeRed(winSizeX, winSizeY);
                        }
                    }

                    switch (level) {
                        case 1:
                            soul->makeBlue();

                            if (deltaFrames > 280) {
                                intermission = true;
                            } else if (deltaFrames > 180) {
                                boneAttacks.at(4)->startAttack();
                            } else if (deltaFrames > 120) {
                                boneAttacks.at(3)->startAttack();
                            } else if (deltaFrames > 60) {
                                boneAttacks.at(2)->startAttack();
                            } else {
                                boneAttacks.at(1)->startAttack();
                            }

                            for (int i = 1; i < 5; i++) {
                                if (boneAttacks.at(i)->checkAttack()) {
                                    boneAttacks.at(i)->attack(soul);
                                }
                            }
                            break;
                        case 2:
                            soul->makeBlue();
                            if (deltaFrames > 300) {
                                intermission = true;
                            } else {
                                boneAttacks.at(5)->startAttack();
                            }

                            if (boneAttacks.at(5)->checkAttack()) {
                                boneAttacks.at(5)->attack(soul);
                            }
                            break;
                        case 3:
                            soul->makeBlue();
                            if (deltaFrames > 280) {
                                intermission = true;
                            } else if (deltaFrames > 180) {
                                boneAttacks.at(9)->startAttack();
                            } else if (deltaFrames > 120) {
                                boneAttacks.at(8)->startAttack();
                            } else if (deltaFrames > 60) {
                                boneAttacks.at(7)->startAttack();
                            } else {
                                boneAttacks.at(6)->startAttack();
                            }

                            for (int i = 6; i < 10; i++) {
                                if (boneAttacks.at(i)->checkAttack()) {
                                    boneAttacks.at(i)->attack(soul);
                                }
                            }
                            break;
                        case 4:
                            soul->makeRed();

                            if (deltaFrames > 280) {
                                intermission = true;
                            } else if (deltaFrames > 180) {
                                blasterAttacks.at(7)->startAttack();
                            } else if (deltaFrames > 120) {
                                blasterAttacks.at(6)->startAttack();
                            } else if (deltaFrames > 60) {
                                blasterAttacks.at(5)->startAttack();
                            } else {
                                blasterAttacks.at(4)->startAttack();
                            }

                            for (int i = 4; i < 8; i++) {
                                if (blasterAttacks.at(i)->checkAttack()) {
                                    blasterAttacks.at(i)->attack(soul);
                                }
                            }
                            break;
                        case 5:
                            soul->makeBlue();

                            if (deltaFrames > 470) {
                                intermission = true;
                            } else {
                                boneAttacks.at(10)->startAttack();
                            }

                            if (boneAttacks.at(10)->checkAttack()) {
                                boneAttacks.at(10)->attack(soul);
                            }
                            break;
                        case 6:
                            if (deltaFrames > 200) {
                                intermission = true;
                            } else if (deltaFrames > 126) {
                                blasterAttacks.at(3)->startAttack();
                            } else if (deltaFrames > 102) {
                                blasterAttacks.at(2)->startAttack();
                            } else if (deltaFrames > 76) {
                                blasterAttacks.at(1)->startAttack();
                            } else if (deltaFrames > 50) {
                                soul->makeRed();
                                blasterAttacks.at(0)->startAttack();
                            } else if (deltaFrames > 20) {
                                soul->makeBlue();

                                if (!boneAttacks.at(0)->checkAttack()) {
                                soul->throwToBottom();
                                }
                                boneAttacks.at(0)->startAttack();
                            }
                            
                            if (!boneAttacks.at(0)->checkAttack()) {
                                soul->throwToBottom();
                            }

                            for (auto& blasterAttack : blasterAttacks) {
                                if (blasterAttack->checkAttack()) {
                                    blasterAttack->attack(soul);
                                }
                            }

                            for (auto& boneAttack : boneAttacks) {
                                if (boneAttack->checkAttack()) {
                                    boneAttack->attack(soul);
                                }
                            }
                            break;
                    }

                    deltaFrames++;
                }
            } else if (level > -1) {
                if (intermission) {
                    if (board->getState() == 0) {
                        board->startAnimation();
                        soul->changePosition(Vector2f(-20, -20));
                        sans->moveFull(0, 30);
                    }

                    if (board->checkAnimation()) {
                        board->changeIntermission1(winSizeX, winSizeY);
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                        deltaFrames = 0;
                        level++;
                        intermission = false;
                    }
                } else {
                    switch (level) {
                        case 0:
                            if (deltaFrames > 180) {
                                intermission = true;
                            } else if (deltaFrames > 106) {
                                blasterAttacks.at(3)->startAttack();
                            } else if (deltaFrames > 82) {
                                blasterAttacks.at(2)->startAttack();
                            } else if (deltaFrames > 56) {
                                blasterAttacks.at(1)->startAttack();
                            } else if (deltaFrames > 30) {
                                soul->makeRed();
                                blasterAttacks.at(0)->startAttack();
                            } else {
                                soul->makeBlue();

                                if (!boneAttacks.at(0)->checkAttack()) {
                                soul->throwToBottom();
                                }
                                boneAttacks.at(0)->startAttack();
                            }
                            
                            if (!boneAttacks.at(0)->checkAttack()) {
                                soul->throwToBottom();
                            }

                            for (auto& blasterAttack : blasterAttacks) {
                                if (blasterAttack->checkAttack()) {
                                    blasterAttack->attack(soul);
                                }
                            }

                            for (auto& boneAttack : boneAttacks) {
                                if (boneAttack->checkAttack()) {
                                    boneAttack->attack(soul);
                                }
                            }
                            break;
                    }

                    deltaFrames++;
                }
            } else if (level > -2) {
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    level = 0;
                    sans->setHead("assets/sansFace.png");
                    sans->mute();
                }
            } else {
                sans->setHead("assets/sansFaceEyesClosed.png");
                sans->talk("you have died...");
            }

            if (board->checkAnimation()) {
                cover->updateCover(board);
            }

            win->clear();
            if (level > -1) {
                soul->draw(win);
            }
            for (auto& boneAttack : boneAttacks) {
                boneAttack->draw(win);
            }
            cover->draw(win);
            sans->draw(win);

            win->draw(action->getAct());
            win->draw(action->getFight());
            win->draw(action->getItem());
            win->draw(action->getMercy());
            win->draw(action->getLevelSprite());
            action->drawHealth(*win);

            if (intermission == true) {
            win->draw(action->getSansSelect());
            win->draw(action->getAttackBarSprite());
            win->draw(action->getSelectionSprite());
            win->draw(action->getAttackBar());
            soul->draw(win);
            }
            
            if (level > -1) {
                board->draw(win);
            }
            for (auto& blasterAttack : blasterAttacks) {
                blasterAttack->draw(win);
            }
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

        void checkInput() {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (action->getIsSelect() == false) {
                    soul->intermissionMoveLeft();
                    action->updateSpriteTextures(soul->getIntermissionPositionCount());
                    cout << soul->getIntermissionPositionCount() << endl;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (action->getIsSelect() == false) {
                    soul->intermissionMoveRight();
                    action->updateSpriteTextures(soul->getIntermissionPositionCount());
                    cout << soul->getIntermissionPositionCount() << endl;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
                action->returnState();
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (action->getIsSelect() == false && action->getIsChoose() == true) {
                    action->battleSelection(soul->getIntermissionPositionCount());
                } else if (action->getIsSelect() == true && action->getIsChoose() == false &&
                    action->getIsSelected() == false) {
                    action->actionSelection(action->getSelectedNumber());

                    if (action->getSelectedNumber() == 0) {
                        action->attackSelected();
                    } else {
                        isFinalPhase = true;
                    }
                } else if (action->getIsAction() == true && action->getIsAnimation() == true) {
                    action->isAttacked();
                    isFinalPhase = true;
                }
            }
        }

        void finalIntermission(){
            level++;
            action->remove();
            level++;
            
            intermission = false;
        }

        ~GameMaster() {
            delete win;
            delete board;
            delete soul;
        }
};

int main() 
{
    GameMaster game(640, 480, "Bad Time Simulator");
    game.timer();

    return 0;
}