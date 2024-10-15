#ifndef ACT_H
#define ACT_H
#include <SFML/Graphics.hpp>

#include "actionSelect.h"

using namespace sf;
using namespace std;

class act : public actionSelect {
 public:
  act(int count) {};
  virtual ~act() {};

  void doAction() {  }
};
#endif