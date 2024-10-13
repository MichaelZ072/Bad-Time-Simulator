#ifndef BONEWALL_H
#define BONEWALL_H

#include "Bones.h"

class BoneWall : public Bones {
    private:
        bool indicatorTimerStarted;
        bool attackTimerStarted;
        bool showIndicator;
        bool reverseMovement;

        bool indicatorSet;

        RectangleShape indicator;
        Vector2f indicatorOriginalSize;
        Vector2f indicatorPosition;

        double heightTracker;

        Clock clock;
        Time indicatorTime;
        Time attackTime;

    public:
        BoneWall(int x, int y, int boneSpeed) : Bones(x, y, boneSpeed, "assets/verticalBoneWall.png") {
            //set properties of indicator so that is starts out contained in the bullet board        
            indicatorOriginalSize.x = 158;
            indicatorOriginalSize.y = 158;

            indicator.setSize(indicatorOriginalSize);
            indicator.setFillColor(Color::Transparent);
            indicator.setOutlineColor(Color::Red);
            indicator.setOutlineThickness(2);
            indicator.setPosition(320,307);
            indicator.setOrigin(indicatorOriginalSize.x / 2, indicatorOriginalSize.y / 2);

            heightTracker = 0;

            showIndicator = false;
            indicatorTimerStarted = false;
            attackTimerStarted = false;
            reverseMovement = false;
            indicatorSet = false;
        }

        bool checkCollision(Soul *soul)
        {
            if (!isActive) {
                return false;
            }

            if (soul->getSprite().getGlobalBounds().intersects(bone.getGlobalBounds())) {
                return true;
            } else {
                return false;
            }
        }

        void draw(RenderWindow* win) {
            if (!isActive) {
                return;
            } 

            win->draw(bone);

            if (showIndicator) {
                win->draw(indicator);
            }   
        }

        // for this to work accurately the height has to be a multiple of the speed
        void callAttack(int speed, double warningDuration, double attackDuration, int steps) {
            int height = steps * speed;

            if (!indicatorSet) {
                // set the indicator's dimensions
                if (moveDirection % 2 == 0) {
                    indicator.setSize(Vector2f(158, height));
                    indicator.setOrigin(indicator.getSize().x / 2.0f, indicator.getSize().y / 2.0f);
                } else {
                    indicator.setSize(Vector2f(height, 158));
                    indicator.setOrigin(indicator.getSize().x / 2.0f, indicator.getSize().y / 2.0f);
                }

                // x or y from indicatorOriginalSize does not matter as it is square
                double offsett = indicatorOriginalSize.x / 2 - height / 2;
                // set the offsett position of indicator
                switch (moveDirection)
                {
                case 0:
                    indicator.move(0, offsett);
                    break;
                case 1:
                    indicator.move(-offsett, 0);
                    break;
                case 2:
                    indicator.move(0, -offsett);
                    break;
                case 3:
                    indicator.move(offsett, 0);
                    break;
                default:
                    indicator.move(0, offsett);
                    break;
                }
                indicatorSet = true;
            }

            // begin warning timer when called
            if (!indicatorTimerStarted) {
                indicatorTimerStarted = true;
                indicatorTime = clock.getElapsedTime();
            }
           
            // for first few seconds (warningDurtion), show the warning indicator
            if (clock.getElapsedTime().asSeconds() < (indicatorTime.asSeconds() + warningDuration)) {
                showIndicator = true;
                return;

            // then we turn off indicator and start displaying the bones
            } else {
                showIndicator = false;
                
                // track the height that the bone has travelled
                // keep adding to height so long as travelled height is less than the specified height
                if (heightTracker < height && !reverseMovement) {
                    move(speed, moveDirection);
                    heightTracker += speed;
                
                // after the bone is in its specified height, switch direction of motion and attack timer begins
                } else {
                    if (!attackTimerStarted) {
                        attackTimerStarted = true;
                        attackTime = clock.getElapsedTime();
                        reverseMovement = true;
                    }

                    // when attackDuration is over bone will start moving in reverse
                    if (clock.getElapsedTime().asSeconds() > (attackTime.asSeconds() + attackDuration) &&  reverseMovement) {
                        if (heightTracker > 0) {
                            move(-speed, moveDirection);
                            heightTracker -= speed;
                        
                        // reset changed attributes after attack has ended 
                        } else {
                            indicatorTimerStarted = false;
                            attackTimerStarted = false;
                            heightTracker = 0;
                            reverseMovement = false;
                            isActive = false;
                            indicatorSet = false;
                            indicator.setPosition(320,307);
                        }
                    }
                }                
            }


            
        }


};

#endif