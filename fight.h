#ifndef FIGHT_H
#define FIGHT_H
#include <SFML/Graphics.hpp>

#include "actionInterface.h"
#include "actionSelect.h"

using namespace sf;
using namespace std;

class fight : public actionSelect {
private:
     int attackCount; 

public:
    fight(int count): attackCount(0) {} 

    virtual ~fight() {}
    
    void doAction(){
        attackCount++;
        cout << "fight executed: " << attackCount << endl;
    }

    int getAttacknCount(){
        return attackCount;
    }
};
#endif