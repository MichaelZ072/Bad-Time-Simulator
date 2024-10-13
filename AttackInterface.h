#ifndef ATTACKINTERFACE_H
#define ATTACKINTERFACE_H

class AttackInterface {
    public:
        virtual void checkCollision(Soul* soul) = 0;
};

#endif