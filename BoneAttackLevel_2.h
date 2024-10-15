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
        vector<MediumBone> mediumBones;
        vector<ShortBone> shortBones;
        bool inAttack;
        Board* boardCopy;

        int mediumNum = 1;
        int shortNum = 1;
        
        Clock spawnClock;
        float spawnDelay = 1.0f;
        bool readyToSpawn = false;

    public:

        BoneAttackLevel_2(Board* board) {
            boardCopy = board;

            // Creating the mediumBones
            for (int i = 0; i < mediumNum; i++) {
                mediumBones.emplace_back();
            }

            // Creating the shortBones
            for (int i = 0; i < shortNum; i++) {
                shortBones.emplace_back();
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
            for (int i = 0; i < int(mediumBones.size()); i ++) {
                if (!mediumBones[i].getIsActive() && readyToSpawn) {
                    mediumBones[i].spawn(Vector2f(boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f), -(mediumBones[i].getSize().y / 2.0f) + boardCopy->getCenter().y + (boardCopy->getSize().y / 2)), 0, 3);
                    readyToSpawn = false;  // Set to false to start the delay
                    spawnClock.restart(); // Restart the clock for the next bone
                    break; // Exit the loop to wait for the delay
                }
            }

            for (int i = 0; i < int(shortBones.size()); i ++) {
                if (!shortBones[i].getIsActive() && readyToSpawn) {
                    shortBones[i].spawn(Vector2f(boardCopy->getCenter().x + (boardCopy->getSize().x / 2.0f), -(shortBones[i].getSize().y / 2.0f) + boardCopy->getCenter().y + (boardCopy->getSize().y / 2)), 0, 3);
                    readyToSpawn = false;  // Set to false to start the delay
                    spawnClock.restart(); // Restart the clock for the next bone
                    break; // Exit the loop to wait for the delay
                }
            }
        }

        // Stops the attack
        void stopAttack() {
            inAttack = false;
            // disable pointer objects assosciated with this attack
        }

        // This contains all the code for the attack
        void attack(Soul* soul) {   
            // Once all the blasters are gone, the attack is done
            if (mediumBones.empty()) {
                stopAttack();
            }
            
            // will only perform an attack is the bone is visible on screen (isActive)
            for (int i = 0; i < int(mediumBones.size()); i ++) {
                if (mediumBones[i].getIsActive()) {
                    mediumBones[i].callAttack(9, 1, boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f));
                    mediumBones[i].checkCollision(soul);
                }
            }

            // Checks if the bones have finished, and then deletes them
            for (int j = 0; j < int(mediumBones.size());) {
                if (mediumBones.at(j).getUsed()) {
                    swap(mediumBones.at(j), mediumBones.back());
                    mediumBones.pop_back();
                } else {
                    j++;
                }
            }

            // will only perform an attack is the bone is visible on screen (isActive)
            for (int i = 0; i < int(shortBones.size()); i ++) {
                if (shortBones[i].getIsActive()) {
                    shortBones[i].callAttack(9, boardCopy->getCenter().x - (boardCopy->getSize().x / 2.0f));
                    shortBones[i].checkCollision(soul);
                }
            }

            // Checks if the bones have finished, and then deletes them
            for (int j = 0; j < int(shortBones.size());) {
                if (shortBones.at(j).getUsed()) {
                    swap(shortBones.at(j), shortBones.back());
                    shortBones.pop_back();
                } else {
                    j++;
                }
            }
        }
                
        // Check if the attack is running
        bool checkAttack() {return inAttack;}

        // Calls the draws for the bones
        void draw(RenderWindow* window) {
            for (int j = 0; j < int(mediumBones.size()); j++) {
                mediumBones[j].draw(window);
            }

            for (int j = 0; j < int(shortBones.size()); j++) {
                shortBones[j].draw(window);
            }
        }

        ~BoneAttackLevel_2() {
            ;
        }
};

#endif