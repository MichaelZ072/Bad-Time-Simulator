#ifndef MERCY_H
#define MERCY_H
#include <SFML/Graphics.hpp>

#include "actionInterface.h"
#include "actionSelect.h"

using namespace sf;
using namespace std;

class mercy : public actionSelect {
 public:
  mercy(int count) {};
  virtual ~mercy() {};

  void doAction() {  }
};
#endif