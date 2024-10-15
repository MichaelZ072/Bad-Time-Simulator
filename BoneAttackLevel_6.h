#ifndef BONEATTACKLEVEL_6_H
#define BONEATTACKLEVEL_6_H

#include "AttackLevels.h"
#include "BulletBoard.h"
#include "Bones.h"
#include "MediumBone.h"
#include "ShortBone.h"
#include "TinyBone.h"
#include "LongBone.h"

class BoneAttackLevel_6 : public AttackLevels {
    private:
        vector<unique_ptr<Bones>> bones;
        bool inAttack;
        Board* boardCopy;    
    public:
        BoneAttackLevel_6(Board* board) {
            boardCopy = board;

            // Creating the bones
            bones.push_back(make_unique<MediumBone>(1));
            bones.push_back(make_unique<MediumBone>(1));
            bones.push_back(make_unique<MediumBone>(1));
            bones.push_back(make_unique<MediumBone>(1));
            
            inAttack = false;
        }

        // Starts the attack
        void startAttack() {
            inAttack = true;

            // if bones already active, do not spawn the bone again
            for (int i = 0; i < int(bones.size()); i ++) {
                if (!bones.at(i)->getIsActive()) {
                    switch (i) {
                    // spawn a medium bone on bottom from the right moving left
                    case 0:
                        bones.at(i)->spawn(Vector2f(boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f), -(bones.at(i)->getSize().y / 2.0f) + boardCopy->getCenter().y + (boardCopy->getSize().y / 2) + 80), 0, 3);
                        break;

                    // spawn a medium bone on top from the right moving left
                    case 1:
                        bones.at(i)->spawn(Vector2f(boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f),  (bones.at(i)->getSize().y / 2.0f) + boardCopy->getCenter().y - (boardCopy->getSize().y / 2) - 10), 0, 3);
                        break;

                    // spawn a medium bone on bottom from the left moving right
                    case 2: 
                        bones.at(i)->spawn(Vector2f(boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f),  -(bones.at(i)->getSize().y / 2.0f) + boardCopy->getCenter().y + (boardCopy->getSize().y / 2) + 80), 0, 1);
                        break;

                    // spawn a medium bone on top from the left moving right
                    case 3: 
                        bones.at(i)->spawn(Vector2f(boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f),  (bones.at(i)->getSize().y / 2.0f) + boardCopy->getCenter().y - (boardCopy->getSize().y / 2) - 10), 0, 1);
                        break;

                    default:
                        break;
                    }
                }
            }
        }

        
        // Stops the attack
        void stopAttack() {
            inAttack = false;
        }

        // This contains all the code for the attack
        void attack(Soul* soul) {   
            int attackSpeed = 5;
            
            // Once all the blasters are gone, the attack is done
            if (bones.empty()) {
                stopAttack();
            }
            
            // will only perform an attack is the bone is visible on screen (isActive)
            for (int i = 0; i < int(bones.size()); i ++) {
                if (bones.at(i)->getIsActive()) {
                    if (i < 2) {
                        bones.at(i)->callAttack(attackSpeed, boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f));
                    } else {
                        bones.at(i)->callAttack(attackSpeed, boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f));
                    }
                    bones.at(i)->checkCollision(soul);
                }
            }

            // Checks if the bones have finished, and then deletes them
            for (int j = 0; j < int(bones.size());) {
                if (bones.at(j)->getUsed()) {
                    swap(bones.at(j), bones.back());
                    bones.pop_back();
                } else {
                    j++;
                }
            }
        }
                
        // Check if the attack is running
        bool checkAttack() {return inAttack;}

        // Calls the draws for the bones
        void draw(RenderWindow* window) {
            for (int j = 0; j < int(bones.size()); j++) {
                bones[j]->draw(window);
            }
        }

        ~BoneAttackLevel_6() {
            ;
        }
        
};

#endif

