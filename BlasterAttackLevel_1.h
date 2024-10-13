#ifndef BLASTERATTACKLEVEL_1_H
#define BLASTERATTACKLEVEL_1_H

#include <vector>
#include "GasterBlasters.h"
#include "BlasterData.h"

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
            initialPositions.push_back(Vector2f(642, 481));
            scales.push_back(Vector2f(2, 2));
            initialRotations.push_back(0);

            initialPositions.push_back(Vector2f(642, 481));
            scales.push_back(Vector2f(2, 2));
            initialRotations.push_back(0);

            initialPositions.push_back(Vector2f(-3, -6));
            scales.push_back(Vector2f(2, 2));
            initialRotations.push_back(0);

            initialPositions.push_back(Vector2f(-3, -6));
            scales.push_back(Vector2f(2, 2));
            initialRotations.push_back(0);

            // Creating the blasters
            for (int i = 0; i < 4; i++) { //int(initialPositions.size())
                blasters.emplace_back(initialPositions.at(i), scales.at(i), initialRotations.at(i));
                deltaFrames.push_back(0);
            }

            // Setting final parameters for each blaster
            finalPositions.push_back(Vector2f(452, 366));
            speeds.push_back(5);
            rotations.push_back(90);
            rotDirections.push_back(1);

            finalPositions.push_back(Vector2f(377, 444));
            speeds.push_back(5);
            rotations.push_back(180);
            rotDirections.push_back(-1);

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

            for (auto& blaster : blasters) {
                blaster.startAnimation();
            }
        }

        // Stops the attack
        void stopAttack() {
            inAttack = false;

            for (auto& blaster : blasters) {
                blaster.stopAnimation();
            }
        }

        // This contains all the code for the attack
        void attack(Soul* soul) {
            for (int i = 0; i < int(blasters.size()); i++) {
                if (blasters.at(i).checkAnimation() && !blasters.at(i).checkFlownIn()) {
                    blasters.at(i).flyIn(finalPositions.at(i), speeds.at(i), rotations.at(i), rotDirections.at(i));
                } else if (blasters.at(i).checkAnimation() && !blasters.at(i).checkFlownOut() && deltaFrames.at(i) > 9) {
                    blasters.at(i).flyOut(45, 16);
                    if (blasters.at(i).firing()) {
                        blasters.at(i).checkCollision(soul);
                    }
                }

                if (blasters.at(i).checkFlownIn()) {
                    deltaFrames.at(i)++;
                }
            }

            for (int j = 0; j < int(blasters.size());) {
                if (blasters.at(j).checkFired()) {
                    swap(blasters.at(j), blasters.back());
                    blasters.pop_back();

                    swap(finalPositions.at(j), finalPositions.back());
                    finalPositions.pop_back();

                    swap(speeds.at(j), speeds.back());
                    speeds.pop_back();

                    swap(rotations.at(j), rotations.back());
                    rotations.pop_back();

                    swap(rotDirections.at(j), rotDirections.back());
                    rotDirections.pop_back();

                    swap(deltaFrames.at(j), deltaFrames.back());
                    deltaFrames.pop_back();
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
                blasters.draw(window);
            }
        }

        ~BlasterAttackLevel_1() {

        }
};

#endif