#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include "state.h"
#include "info.h"

class Cell;

class GraphicsDisplay: public Observer<Info, State> {
  Xwindow Display; //a graphic display of the game
  const size_t gridSize; 
 public:
  GraphicsDisplay(size_t n); // the ctor for the class

  void notify(Subject<Info, State> &whoNotified) override; // changes the display depending on the user's move

};
#endif
