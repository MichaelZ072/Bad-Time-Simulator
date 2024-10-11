#ifndef BLASTERATTACKLEVEL_1_H
#define BLASTERATTACKLEVEL_1_H

#include <vector>
#include "GasterBlasters.h"

class BlasterAttackLevel_1 {
    private:
        vector<GasterBlasters> blasters;
        vector<Vector2f> initialPositions;
        vector<Vector2f> scales;
        vector<float> initialRotations;
        vector<Vector2f> finalPositions;
        vector<float> speeds;
        vector<float> rotations;
        vector<int> rotDirections;
        vector<unsigned int> deltaFrames;
        bool inAttack;
    public:
        BlasterAttackLevel_1() {
            // Setting initial parameters for each blaster
            initialPositions.push_back(Vector2f(-3,-6));
            scales.push_back(Vector2f(2,2));
            initialRotations.push_back(0);

            initialPositions.push_back(Vector2f(-3,-6));
            scales.push_back(Vector2f(2,2));
            initialRotations.push_back(0);

            for (int i = 0; i < 2; i++) {
                blasters.emplace_back(initialPositions.at(i), scales.at(i), initialRotations.at(i));
                deltaFrames.push_back(0);
            }

            // Setting final parameters for each blaster
            finalPositions.push_back(Vector2f(186, 241));
            speeds.push_back(5);
            rotations.push_back(270);
            rotDirections.push_back(-1);

            finalPositions.push_back(Vector2f(257, 163));
            speeds.push_back(5);
            rotations.push_back(0);
            rotDirections.push_back(1);
        }

        // Check if the attack is running
        bool checkAttack() {return inAttack;}

        // Starts the attack
        void startAttack() {
            inAttack = true;

            for (auto& blasters : blasters) {
                blasters.startAnimation();
            }
        }

        // Stops the attack
        void stopAttack() {inAttack = false;}

        // This contains all the code for the attack
        void attack() {
            for (int i = 0; i < int(blasters.size()); i++) {
                if (blasters.at(i).checkAnimation() && !blasters.at(i).checkFlownIn()) {
                    blasters.at(i).flyIn(finalPositions.at(i), speeds.at(i), rotations.at(i), rotDirections.at(i));
                } else if (blasters.at(i).checkAnimation() && !blasters.at(i).checkFlownOut() && deltaFrames.at(i) > 9) {
                    blasters.at(i).flyOut(45, 16);
                }

                if (blasters.at(i).checkFlownIn()) {
                    deltaFrames.at(i)++;
                }
            }
        }

        // Calls the draws for the blasters
        void draw(RenderWindow* window) {
            for (auto& blasters : blasters) {
                blasters.draw(window);
            }
        }

        ~BlasterAttackLevel_1() {

        }
};

#endif