#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "cell.h"
#include "textdisplay.h"
#include "window.h"
#include "graphicsdisplay.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  Colour move = Colour::Black;
  GraphicsDisplay* gd = nullptr;
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      size_t n;
      cin >> n;
      if (n < 4 || (n % 2) != 0) {}
      else {
      delete gd;
      gd = new GraphicsDisplay{n};
      g.setObserver(gd);
      g.init(n);
      move = Colour::Black;
      size_t mid = n/2;
      g.setPiece(mid ,mid ,Colour::Black);
      g.setPiece(mid ,mid-1 ,Colour::White);
      g.setPiece(mid-1,mid,Colour::White);
      g.setPiece(mid-1,mid-1,Colour::Black);
      cout << g;
      }
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      try {
          g.setPiece(r,c,move);
      }
      catch(InvalidMove &IM) { continue; }
      cout << g;
      if (move == Colour::Black) { move = Colour::White; }
      else { move = Colour::Black; }
      if (g.isFull()) {
        if (g.whoWon() == Colour::Black) {
          cout << "Black wins!" << endl;
          break;
        }
        else if (g.whoWon() == Colour::White) {
          cout << "White wins!" << endl;
          break; 
        }
        else {
          cout << "Tie!" << endl;
          break;
        }
      }
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
