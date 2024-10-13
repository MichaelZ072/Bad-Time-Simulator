#ifndef BLASTERATTACKLEVEL_2_H
#define BLASTERATTACKLEVEL_2_H

#include <vector>
#include "GasterBlasters.h"
#include "BlasterData.h"

class BlasterAttackLevel_2 {
    private:
        vector<BlasterData> blasters;
        bool inAttack;
    public:
        BlasterAttackLevel_2() {
            // Creating the blasters
            blasters.emplace_back(Vector2f(642, 478), Vector2f(2, 2), 0, Vector2f(450, 440), 5, 135, 1, 0);
            blasters.emplace_back(Vector2f(0, 475), Vector2f(2, 2), 0, Vector2f(184, 435), 5, 225, -1, 0);
            blasters.emplace_back(Vector2f(-3, -3), Vector2f(2, 2), 0, Vector2f(186, 170), 5, 315, -1, 0);
            blasters.emplace_back(Vector2f(642, -3), Vector2f(2, 2), 0, Vector2f(454, 172), 5, 45, 1, 0);
        }

        // Check if the attack is running
        bool checkAttack() {return inAttack;}

        // Starts the attack
        void startAttack() {
            inAttack = true;

            for (auto& blaster : blasters) {
                blaster.gasterBlaster->startAnimation();
            }
        }

        // Stops the attack
        void stopAttack() {
            inAttack = false;

            for (auto& blaster : blasters) {
                blaster.gasterBlaster->stopAnimation();
            }
        }

        // This contains all the code for the attack
        void attack(Soul* soul) {
            for (int i = 0; i < int(blasters.size()); i++) {
                if (blasters.at(i).gasterBlaster->checkAnimation() && !blasters.at(i).gasterBlaster->checkFlownIn()) {
                    blasters.at(i).gasterBlaster->flyIn(blasters.at(i).finalPosition, blasters.at(i).speed, blasters.at(i).finalRotation, blasters.at(i).rotDirection);
                } else if (blasters.at(i).gasterBlaster->checkAnimation() && !blasters.at(i).gasterBlaster->checkFlownOut() && blasters.at(i).deltaFrames > 9) {
                    blasters.at(i).gasterBlaster->flyOut(45, 16);
                    if (blasters.at(i).gasterBlaster->firing()) {
                        blasters.at(i).gasterBlaster->checkCollision(soul);
                    }
                }

                if (blasters.at(i).gasterBlaster->checkFlownIn()) {
                    blasters.at(i).deltaFrames++;
                }
            }

            for (int j = 0; j < int(blasters.size());) {
                if (blasters.at(j).gasterBlaster->checkFired()) {
                    swap(blasters.at(j), blasters.back());
                    blasters.pop_back();
                } else {
                    j++;
                }
            }

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

        ~BlasterAttackLevel_2() {

        }
};

#endif