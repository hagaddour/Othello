#include "textdisplay.h"
#include "cell.h"



TextDisplay::TextDisplay(size_t n): gridSize{n} {
  for (size_t i = 0; i < n; ++i) {
  	theDisplay.emplace_back(std::vector<char>(n));
  	for (size_t j = 0; j < n; ++j) {
  		theDisplay[i][j] = '-';
  	}
  }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	Info in = whoNotified.getInfo();
	if (in.colour == Colour::White) {
		theDisplay[in.row][in.col] = 'W';
	}
	else {
		theDisplay[in.row][in.col] = 'B';
	}
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (size_t i = 0; i < td.gridSize; ++i) {
    for (size_t j = 0; j < td.gridSize; ++j) {
      out << td.theDisplay[i][j];
    }
    out << std::endl;
  }
  return out;
}
