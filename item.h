#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>

#include "actionSelect.h"

using namespace sf;
using namespace std;

class item : public actionSelect{

public:
item(int count){};
virtual ~item(){};

void doAction(){
    cout<< "action exectuted item"<<endl;
}

};
#endif