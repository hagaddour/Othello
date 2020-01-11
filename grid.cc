#include "grid.h"
#include "observer.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

Grid::~Grid() { 
  delete td;
  delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) {
  this->ob = ob;
}
bool Grid::isFull() const {
  bool isover = true;
  for (size_t i = 0; i < gsize; ++i) {
    for (size_t j = 0; j < gsize; ++j) {
      if (theGrid[i][j].getInfo().colour == Colour::NoColour) {
        isover = false;
        break;
      }
    }
    if (isover == false) {
      break;
    }
  }
  return isover;
}

Colour Grid::whoWon() const {
  int black = 0;
  int white = 0;
  for (size_t i = 0; i < gsize; ++i) {
    for (size_t j = 0; j < gsize; ++j) {
      if (theGrid[i][j].getInfo().colour == Colour::Black) {
        ++black;
      }
      else if (theGrid[i][j].getInfo().colour == Colour::White) {
        ++white;
      }
    }
  }
  if (black > white) {return Colour::Black;}
  else if (black < white) {return Colour::White;}
  else {return Colour::NoColour; }
}

void Grid::init(size_t n) {
  if (gsize > 0) {
    for (size_t i = 0; i < gsize; ++i) {
      theGrid[i].clear();
    } 
    theGrid.clear();
    delete td;
    td = nullptr;
  }
  td = new TextDisplay{n};
  gsize = n;
  for (size_t i = 0; i < n; ++i) {
    std::vector<Cell> temp;
    for (size_t j = 0; j < n; ++j) {
      temp.emplace_back(Cell{i,j});
    }
    theGrid.emplace_back(temp);
  }
  for (size_t rr = 0; rr < n; ++rr) {
    for (size_t cc = 0; cc < n; ++cc) {
      theGrid[rr][cc].attach(ob);
      theGrid[rr][cc].attach(td);
        for (int i = -1; i < 2; ++i) {
          if ((rr > 0) && (cc + i >= 0) && (cc + i <= n-1)) {
            theGrid[rr][cc].attach(&theGrid[rr-1][cc+i]);
          }
        }
        if (cc  > 0) {
          theGrid[rr][cc].attach(&theGrid[rr][cc-1]);
        }
        if (cc < n-1) {
          theGrid[rr][cc].attach(&theGrid[rr][cc+1]);
        }
        for (int i = -1; i < 2; ++i) {
          if ((rr < n-1) && (cc + i >= 0) && (cc + i <= n-1)) {
            theGrid[rr][cc].attach(&theGrid[rr+1][cc+i]);
          }
        }
      }
    }  
  }

void Grid::setPiece(size_t r, size_t c, Colour colour) {
  if (r >= gsize || c >= gsize || theGrid[r][c].getInfo().colour != Colour::NoColour) {
      throw InvalidMove{};
  }
  else {
  theGrid[r][c].setPiece(colour); 
  theGrid[r][c].notifyObservers();
  }
}

void Grid::toggle(size_t r, size_t c) {}


std::ostream &operator<<(std::ostream &out, const Grid &g) {
  out << *g.td;
  return out;
}
