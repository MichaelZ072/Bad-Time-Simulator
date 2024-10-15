#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>

#include "actionSelect.h"
#include "actionInterface.h"
#include "Soul.h"

using namespace sf;
using namespace std;

class item : public actionSelect{
private:
Soul* soul;
int health;

public:
item(int count, Soul* souls){
    soul = souls;
};
virtual ~item(){};

void doAction(){
    health = soul->getHealth() +100;
    cout<< "action exectuted item"<<endl;
}

};
#endif