#ifndef BLASTERBEAMS_H
#define BLASTERBEAMS_H

#include <SFML/Graphics.hpp>
#include "GasterBlasters.h"

class BlasterBeams {
    private:
        RectangleShape beam;
        Vector2f beamScale;
        Vector2f size;
        float rotation;
        bool inAnimation;
        bool fired;
        float transparency;
        int stage;
        float startScale;
        float firstGrowScale;
        float shrinkScale;
        float secondGrowScale;
        float endScale;
        float stageDurations[5];
        float stageStartTimes[5];
        float deltaFrames;
        float totalFrames;
    public:
        BlasterBeams (Sprite blaster, Vector2f setScale) {
            beamScale = setScale;
            inAnimation = false;
            fired = false;
            transparency = 255;
            size = Vector2f(9 * beamScale.x, 1500);

            // Setting the values for the different stages
            stage = 0;
            startScale = 1;
            firstGrowScale = 4;
            shrinkScale = 3;
            secondGrowScale = 4.5;
            endScale = 0;

            // Setting the duration for the stages
            stageDurations[0] = 4;
            stageDurations[1] = 4;
            stageDurations[2] = 4;
            stageDurations[3] = 4;
            stageDurations[4] = 12;
            stageStartTimes[0] = 0;

            // Finding out the start times
            for (int i = 1; i < 5; i++) {
                stageStartTimes[i] = stageStartTimes[i - 1] + stageDurations[i - 1];
            }

            // Setting up change in frames and total frames
            deltaFrames = 0;
            totalFrames = stageStartTimes[4] + stageDurations[4];

            // Creating the beam itself
            beam.setSize(size);
            beam.setScale(beamScale.x,1);
            beam.setFillColor(Color::White);
            beam.setOutlineColor(Color::White);
            beam.setOrigin(Vector2f((beam.getSize().x / 2), (blaster.getOrigin().y + 5)* beamScale.y * -1));
            beam.setPosition(Vector2f(-20,0));
        }

        // Checks if the beam is in an animation
        bool checkAnimation() {return inAnimation;}

        // Starts the animation
        void startAnimation() {inAnimation = true;}

        // Stops the animation
        void stopAnimation() {inAnimation = false;}

        // Checks if the beam has finished and thus is fired
        bool checkFired() {return fired;}

        // This is responsible for all the logic when the beam is fired
        void fire(Sprite blaster) {
            beam.setOrigin(Vector2f((beam.getSize().x / 2), (blaster.getOrigin().y - 5)* beamScale.y * -1));
            beam.setPosition(blaster.getPosition().x, blaster.getPosition().y);
            rotation = blaster.getRotation();
            beam.setRotation(rotation);

            deltaFrames++;

            // Checking which stage of animation it is in currently
            if (deltaFrames >= totalFrames) {
                fired = true;
                inAnimation = false;
                stage = 4;
            } else if (deltaFrames >= stageStartTimes[4]) {
                stage = 4;
            } else if (deltaFrames >= stageStartTimes[3]) {
                stage = 3;
            } else if (deltaFrames >= stageStartTimes[2]) {
                stage = 2;
            } else if (deltaFrames >= stageStartTimes[1]) {
                stage = 1;
            } else {
                stage = 0;
            }

            // A time variable to control the easing based on the stage
            float t;
            t = (deltaFrames - stageStartTimes[stage]) / stageDurations[stage];

            if (t < 0) {
                t = 0;
            }
            
            if (t > 1) {
                t = 1;
            }

            // Value to control the easing
            float easedT;
            if (t < 0.5) {
                easedT = t * t * t;
            } else {
                easedT = t * t;
            }

            float scale = startScale;

            // Changing size using scaling, and transparency
            switch (stage) {
                case 0:
                    scale = startScale + (firstGrowScale - startScale) * easedT;
                    break;
                case 1:
                    scale = firstGrowScale + (shrinkScale - firstGrowScale) * easedT;
                    break;
                case 2:
                    scale = shrinkScale + (secondGrowScale - shrinkScale) * easedT;
                    break;
                case 3:
                    scale = secondGrowScale + (endScale - secondGrowScale) * easedT;
                    transparency = transparency - (float(255) / 10);
                    break;
                case 4:
                    scale = (deltaFrames >= totalFrames) ? endScale : (beam.getScale().x / beamScale.x) * (1.0f - easedT);
                    transparency = transparency - (float(255) / 10);
                    break;
            }

            beam.setScale(scale, 1);

            // Mkaing sure transparency doesn't go into the negatives
            if (transparency < 0) {
                transparency = 0;
            }
            
            // Updating transparency
            beam.setFillColor(sf::Color(255, 255, 255, transparency));
        }

        // Returns the global bounds
        FloatRect getGlobalBounds() {return beam.getGlobalBounds();}

        // Returns the local bounds
        FloatRect getLocalBounds() {return beam.getLocalBounds();}

        // Returns the inverse transform
        Transform getInverseTransform() {return beam.getInverseTransform();}

        // Draws the beam
        void draw(RenderWindow* window) {
            window->draw(beam);
        }
};

#endif