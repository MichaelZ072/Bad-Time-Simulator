#ifndef ACTIONSELECT_H
#define ACTIONSELECT_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "BulletBoard.h"
#include "Soul.h"

using namespace std;
using namespace sf;

class actionSelect {
 protected:
 public:
  virtual void doAction() {};
  virtual ~actionSelect() {};
};

#endif
