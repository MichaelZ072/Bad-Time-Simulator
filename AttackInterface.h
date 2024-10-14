#ifndef ATTACKINTERFACE_H
#define ATTACKINTERFACE_H

class AttackInterface {
    public:
        AttackInterface() = default;
        virtual ~AttackInterface() = default;
        virtual void checkCollision(Soul* soul) = 0;
};

#endif