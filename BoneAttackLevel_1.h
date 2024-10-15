#ifndef BONEATTACKLEVEL_1_H
#define BONEATTACKLEVEL_1_H

#include "AttackLevels.h"
#include "BoneWall.h"
#include "BulletBoard.h"

class BoneAttackLevel_1 : public AttackLevels { 
    private:
        vector<BoneWall> boneWalls;
        Board* boardCopy;

        int numWall = 1;

        bool inAttack;

    public:
        BoneAttackLevel_1(Board* board) {
            boardCopy = board;           

            boneWalls.emplace_back();

            inAttack = false;
            
        }
        // Check if the attack is running
        bool checkAttack() {return inAttack;}

        // Starts the attack
        void startAttack() {
            inAttack = true;
            
            // if boneWall is already active, do not spawn the bone again
            for (int i = 0; i < int(boneWalls.size()); i++) {
                if (!boneWalls[i].getIsActive()) {
                    // spawn a bone wall starting from the bottom and going up
                    boneWalls[i].spawn(Vector2f(boardCopy->getCenter().x, boardCopy->getCenter().y + boardCopy->getSize().y / 2.0f + boneWalls[i].getSize().x / 2.0f), 90, 0);
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
            // will only perform an attack is the bone is visible on screen (isActive)
            for (int i = 0; i < int(boneWalls.size()); i ++) {
                if (boneWalls[i].getIsActive()) {
                    boneWalls[i].callAttack(15, 0.5, 1.5, 4);
                    boneWalls[i].checkCollision(soul);
                }
            }

            // Checks if the bones have finished, and then deletes them
            for (int j = 0; j < int(boneWalls.size());) {
                if (boneWalls.at(j).getUsed()) {
                    swap(boneWalls.at(j), boneWalls.back());
                    boneWalls.pop_back();
                } else {
                    j++;
                }
            }
        }

        // Calls the draws for the bones
        void draw(RenderWindow* window) {
            for (int j = 0; j < int(boneWalls.size()); j++) {
                boneWalls[j].draw(window);
            }
        }

        ~BoneAttackLevel_1() {
            ;
        }
};

#endif