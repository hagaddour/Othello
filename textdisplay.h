#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
class Cell;
// it's an observer
class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
  const size_t gridSize; //maybe return it back to int
 public:
  TextDisplay(size_t n); //maybe return it back to int

  void notify(Subject<Info, State> &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
