#ifndef BLASTERATTACKLEVEL_1_H // Change headers when coping
#define BLASTERATTACKLEVEL_1_H

#include <vector>
#include "AttackLevels.h"
#include "GasterBlasters.h"
#include "BlasterData.h"

class BlasterAttackLevel_1 : public AttackLevels { // Change class name and constructor and destructor when copying
    private:
        vector<BlasterData> blasters;
        bool inAttack;
    public:
        BlasterAttackLevel_1() {
            // Creating the blasters
            blasters.emplace_back(Vector2f(642, 481), Vector2f(2, 2), 0, Vector2f(452, 366), 5, 90, 1);
            blasters.emplace_back(Vector2f(642, 481), Vector2f(2, 2), 0, Vector2f(377, 444), 5, 180, -1);
            blasters.emplace_back(Vector2f(-3, -6), Vector2f(2, 2), 0, Vector2f(186, 241), 5, 270, -1);
            blasters.emplace_back(Vector2f(-3, -6), Vector2f(2, 2), 0, Vector2f(257, 163), 5, 0, 1);
        }

        // Check if the attack is running
        bool checkAttack() {return inAttack;}

        // Starts the attack
        void startAttack() {
            inAttack = true;

            // Starts attack for all the blasters
            for (auto& blaster : blasters) {
                blaster.gasterBlaster->startAnimation();
            }
        }

        // Stops the attack
        void stopAttack() {
            inAttack = false;

            // Stops the attack for all the blasters
            for (auto& blaster : blasters) {
                blaster.gasterBlaster->stopAnimation();
            }
        }

        // This contains all the code for the attack
        void attack(Soul* soul) {
            for (int i = 0; i < int(blasters.size()); i++) {
                // Checks if the blaster is not flown in, and then does the fly in animation, else do the fly out animation
                if (blasters.at(i).gasterBlaster->checkAnimation() && !blasters.at(i).gasterBlaster->checkFlownIn()) {
                    blasters.at(i).gasterBlaster->flyIn(blasters.at(i).finalPosition, blasters.at(i).speed, blasters.at(i).finalRotation, blasters.at(i).rotDirection);
                } else if (blasters.at(i).gasterBlaster->checkAnimation() && !blasters.at(i).gasterBlaster->checkFlownOut() && blasters.at(i).deltaFrames > 9) {
                    blasters.at(i).gasterBlaster->flyOut(45, 16);
                    if (blasters.at(i).gasterBlaster->firing()) {
                        blasters.at(i).gasterBlaster->checkCollision(soul);
                    }
                }

                // Once the blasters have flown in, start counting frames for the fly out
                if (blasters.at(i).gasterBlaster->checkFlownIn()) {
                    blasters.at(i).deltaFrames++;
                }
            }

            // Checks if the blasters have finished, and then deletes them
            for (int j = 0; j < int(blasters.size());) {
                if (blasters.at(j).gasterBlaster->checkFired()) {
                    swap(blasters.at(j), blasters.back());
                    blasters.pop_back();
                } else {
                    j++;
                }
            }

            // Once all the blasters are gone, the attack is done
            if (blasters.empty()) {
                stopAttack();
            }
        }

        // Calls the draws for the blasters
        void draw(RenderWindow* window) {
            for (auto& blasters : blasters) {
                blasters.gasterBlaster->draw(window);
            }
        }
};

#endif