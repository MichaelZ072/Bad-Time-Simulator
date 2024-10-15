#ifndef BONEATTACKLEVEL_3_H
#define BONEATTACKLEVEL_3_H

#include "AttackLevels.h"
#include "BulletBoard.h"
#include "Bones.h"
#include "MediumBone.h"
#include "ShortBone.h"
#include "TinyBone.h"
#include "LongBone.h"

#include <cstdlib>

class BoneAttackLevel_3 : public AttackLevels { 
    private:
        vector<unique_ptr<Bones>> bones;
        bool inAttack;
        Board* boardCopy;

        int numBones = 12;
                
        Clock spawnClock;
        float spawnDelay = 1.2f;
        bool readyToSpawn = false;

    public:

        BoneAttackLevel_3(Board* board) {
            boardCopy = board;

            // Creating the bones
            for (int i = 0; i < numBones; i++) {
                bones.push_back(make_unique<MediumBone>(rand() % 2));
            }
            inAttack = false;
        }

        void updateSpawn() {
            // wait for current elapsed time to surpass time of spawnDelay
            if (!readyToSpawn && spawnClock.getElapsedTime().asSeconds() >= spawnDelay) {
                readyToSpawn = true; // Allow the next bone to spawn after time of spawnDelay has been surpassed
            }
        }

        // Starts the attack
        void startAttack() {
            inAttack = true;
                        
            // if bones already active, do not spawn the bone again
            for (int i = 0; i < int(bones.size()); i ++) {
                if (!bones.at(i)->getIsActive() && readyToSpawn) {
                    bones.at(i)->spawn(Vector2f(boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f), -(bones.at(i)->getSize().y / 2.0f) + boardCopy->getCenter().y + (boardCopy->getSize().y / 2) + (rand() % 50 + 30)), 0, 3);
                    float spawnDelay = (rand() % 2 - 0.5);
                    readyToSpawn = false;  // Set to false to start the delay
                    spawnClock.restart(); // Restart the clock for the next bone
                    break; // Exit the loop to wait for the delay
                }
            }
        }

        // Stops the attack
        void stopAttack() {
            inAttack = false;
        }

        // This contains all the code for the attack
        void attack(Soul* soul) {   
            // Once all the blasters are gone, the attack is done
            if (bones.empty()) {
                stopAttack();
            }
            
            // will only perform an attack is the bone is visible on screen (isActive)
            for (int i = 0; i < int(bones.size()); i ++) {
                if (bones.at(i)->getIsActive()) {
                    bones.at(i)->callAttack(rand() % 5 + 8, boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f));
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

        ~BoneAttackLevel_3() {
            ;
        }
};

#endif