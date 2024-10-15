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
int pie;

public:
item(int count, Soul* souls){
    soul = souls;
};
virtual ~item(){};

void doAction(){
    pie= 100;
    soul->heal(pie);
}

};

#endif