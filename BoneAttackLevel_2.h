#ifndef BONEATTACKLEVEL_2_H
#define BONEATTACKLEVEL_2_H

#include "AttackLevels.h"
#include "BulletBoard.h"
#include "Bones.h"
#include "MediumBone.h"
#include "ShortBone.h"

#include "TinyBone.h"

class BoneAttackLevel_2 : public AttackLevels { 
    private:
        vector<unique_ptr<Bones>> bones;
        bool inAttack;
        Board* boardCopy;
        float posToDestroy = 0;

        int numBones = 6;
        int bonesSpawned = 0;
                
        Clock spawnClock;
        float spawnDelay = 1.5f;
        bool readyToSpawn = false;

    public:
        BoneAttackLevel_2(Board* board) {
            boardCopy = board;

            // Creating the bones
            for (int i = 0; i < numBones; i++) {
                if (i % 2 == 0) {
                    bones.push_back(make_unique<MediumBone>(0));
                } else {
                    bones.push_back(make_unique<ShortBone>());
                }
            }
            inAttack = false;
        }

        // Starts the attack
        void startAttack() {
            inAttack = true;

            // wait for current elapsed time to surpass time of spawnDelay
            if (!readyToSpawn && spawnClock.getElapsedTime().asSeconds() >= spawnDelay) {
                readyToSpawn = true; // Allow the next bone to spawn after time of spawnDelay has been surpassed
            }
            
            // if bones already active, do not spawn the bone again
            for (int i = 0; i < int(bones.size()); i ++) {
                if (!bones.at(i)->getIsActive() && readyToSpawn) {
                    float spawnX = 0;
                    int spawnDirection = 0;
                    if (bonesSpawned >= numBones / 2) {
                        spawnDirection = 1;
                        spawnX = boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f);
                        posToDestroy = boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f);
                    } else {
                        spawnDirection = 3;
                        spawnX = boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f);
                        posToDestroy = boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f);
                    }
                    bones.at(i)->spawn(Vector2f(spawnX, -(bones.at(i)->getSize().y / 2.0f) + boardCopy->getCenter().y + (boardCopy->getSize().y / 2)), 0, spawnDirection);
                    readyToSpawn = false;  // Set to false to start the delay
                    spawnClock.restart(); // Restart the clock for the next bone
                    bonesSpawned++;
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
                    bones.at(i)->callAttack(9, posToDestroy);
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

        ~BoneAttackLevel_2() {
            ;
        }
};

#endif