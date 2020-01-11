#include "graphicsdisplay.h"
#include "cell.h"
#include <iostream>


GraphicsDisplay::GraphicsDisplay(size_t n): gridSize{n} {
  int vol = 500/n;
  for (size_t i = 0; i < n; ++i) {
  	for (size_t j = 0; j < n; ++j) {
    Display.fillRectangle(vol*i, vol*j, vol, vol, Xwindow::Blue);
  	}
  }
}

void GraphicsDisplay::notify(Subject<Info, State> &whoFrom) {
  Info in = whoFrom.getInfo();
  int vol = 500/gridSize;
	if (in.colour == Colour::White) {
    Display.fillRectangle(vol*in.col, vol*in.row, vol, vol, Xwindow::White);
	}
	else {
    Display.fillRectangle(vol*in.col, vol*in.row, vol, vol, Xwindow::Black);
	}
}

